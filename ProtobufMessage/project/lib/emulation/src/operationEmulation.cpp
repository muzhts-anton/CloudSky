#include "operationEmulation.h"
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <linux/input.h>
#include <linux/uinput.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void ViktorDev::EmelationKeyBoard::initKeyboard(uinput_user_dev& devFakeKeyboard)
{

    if (ioctl(fdKeyEmulator, UI_SET_EVBIT, EV_KEY)) {
        std::cout << "Error in ioctl : UI_SET_EVBIT : EV_KEY : " << strerror(errno) << std::endl;
        exit(ioctlError);
    }

    // enable set of KEY events here
    for (auto it = pressedButtons.cbegin(); it != pressedButtons.cend(); ++it) {
        if (ioctl(fdKeyEmulator, UI_SET_KEYBIT, it->first)) {
            std::cout << "Error in ioctl : UI_SET_KEYBIT : " << strerror(errno) << std::endl;
            exit(ioctlError);
        }
    }

    // enable synchronization event
    if (ioctl(fdKeyEmulator, UI_SET_EVBIT, EV_SYN)) {
        std::cout << "Error in ioctl : UI_SET_EVBIT : EV_SYN : " << strerror(errno) << std::endl;
        exit(ioctlError);
    }

    // now write the uinput_user_dev structure into uinput file descriptor
    if (write(fdKeyEmulator, &devFakeKeyboard, sizeof(uinput_user_dev)) < 0) {
        std::cout << "Error in write(): uinput_user_dev struct into uinput file descriptor: " << strerror(errno) << std::endl;
        exit(writeError);
    }

    // create the device via an IOCTL call
    if (ioctl(fdKeyEmulator, UI_DEV_CREATE)) {
        std::cout << "Error in ioctl : UI_DEV_CREATE : " << strerror(errno) << std::endl;
        exit(ioctlError);
    }
}
void ViktorDev::EmelationKeyBoard::initEmulateKeyboard()
{
    pressedButtons.reserve(buttonQuanityEm);
    for (int i = 0; i < buttonQuanityEm; ++i) {
        pressedButtons.push_back({ kbEncoding[i], false });
    }

    fdKeyEmulator = open(uinputPath, O_WRONLY | O_NONBLOCK);
    if (fdKeyEmulator < 0) {
        std::cout << "error in open : " << strerror(errno) << std::endl;
        exit(fdError);
    }

    // uinput_user_dev struct for fake keyboard
    struct uinput_user_dev devFakeKeyboard;
    memset(&devFakeKeyboard, 0, sizeof(uinput_user_dev));
    snprintf(devFakeKeyboard.name, UINPUT_MAX_NAME_SIZE, "kb-emulator");
    devFakeKeyboard.id.bustype = BUS_USB;
    devFakeKeyboard.id.vendor = 0x01;
    devFakeKeyboard.id.product = 0x01;
    devFakeKeyboard.id.version = 1;
    initKeyboard(devFakeKeyboard);
    usleep(ioDeviceInitSleep); // time to initialize the I / O device descriptor
    // now fdKeyEmulator represents the end-point file descriptor of the new input device.
}
ViktorDev::EmelationKeyBoard::EmelationKeyBoard()
{
    initEmulateKeyboard();
}

void ViktorDev::EmelationKeyBoard::setKeyboard(const KeyboardMouse::ButtonsCoords& message)
{
    int i = 0;
    for (auto it = pressedButtons.begin(); it != pressedButtons.end(); ++it, ++i) {
        it->second = (message.buttonpressed())[i];
    };
    std::cout << "Readed bools: ";
    for (auto it = pressedButtons.cbegin(); it != pressedButtons.cend(); ++it) {
        std::cout << it->second << ' ';
    }
    std::cout << std::endl;
    i = 0;
}

void ViktorDev::EmelationKeyBoard::synKeyboard()
{
    memset(&keyInputEvent, 0, sizeof(input_event));
    keyInputEvent.type = EV_SYN;
    keyInputEvent.code = SYN_REPORT;
    keyInputEvent.value = 0;

    // now write to the file descriptor
    if (write(fdKeyEmulator, &keyInputEvent, sizeof(input_event)) < 0) {
        std::cout << "Error write : EV_SYN for key press : " << strerror(errno) << std::endl;
        exit(writeError);
    }
}

void ViktorDev::EmelationKeyBoard::emulateKeyboard()
{
    auto setKeyboard = [&](std::pair<int, bool> codeValue) {
        memset(&keyInputEvent, 0, sizeof(input_event));
        keyInputEvent.type = EV_KEY;
        keyInputEvent.code = codeValue.first;
        keyInputEvent.value = codeValue.second;

        // now write to the file descriptor
        if (write(fdKeyEmulator, &keyInputEvent, sizeof(input_event)) < 0) {
            std::cout << "Error write : KEY_A press : " << strerror(errno) << std::endl;
            exit(writeError);
        }
    };

    std::for_each(pressedButtons.begin(), pressedButtons.end(), setKeyboard);
    synKeyboard();
    // time between ticks
}

bool ViktorDev::EmelationKeyBoard::getCurrentButtonState(int symbol)
{
    for (int i = 0; i < buttonQuanityEm; ++i) {
        if ((pressedButtons[i]).first == symbol) {
            return pressedButtons[i].second;
        }
    }
    return false;
}

void ViktorDev::EmulationMouse::initEmulateMouse()
{
    coords.first = coords.second = 0;
    previousCoords.first = previousCoords.second = 0;
    mouseButtons.resize(2);
    for (auto it = mouseButtons.begin(); it != mouseButtons.end(); ++it) {
        it->second = 0;
    }
    fdMouse = open(uinputPath, O_WRONLY | O_NONBLOCK);
    if (fdMouse < 0) {
        perror("error: open");
        exit(ioctlError);
    }
    auto setSignal = [fdMouse = this->fdMouse](int signalType, int signal) {
        if (ioctl(fdMouse, _IOW(UINPUT_IOCTL_BASE, signalType, int), signal) < 0) {
            perror("error: ioctl");
            exit(ioctlError);
        }
    };
    setSignal(uiSetEvbit, EV_KEY);
    setSignal(UiSetKeybit, BTN_LEFT);
    setSignal(UiSetKeybit, BTN_RIGHT);
    setSignal(uiSetEvbit, EV_REL);
    setSignal(UiSetRelbit, REL_X);
    setSignal(UiSetRelbit, REL_Y);
    setSignal(UiSetKeybit, BTN_MOUSE);

    memset(&uidev, 0, sizeof(uidev));
    snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "uinput-sample");
    uidev.id.bustype = BUS_USB;
    uidev.id.vendor = uidevIdVendor;
    uidev.id.product = uidevIdProduct;
    uidev.id.version = uidevIdVersion;

    if (write(fdMouse, &uidev, sizeof(uidev)) < 0) {
        perror("error: write");
        exit(writeError);
    }

    if (ioctl(fdMouse, UI_DEV_CREATE) < 0) {
        perror("error: ioctl");
        exit(ioctlError);
    }

    usleep(ioDeviceInitSleep); //time to initialize the I / O device descriptor

    return;
}

void ViktorDev::EmulationMouse::setCoordsButtons(const KeyboardMouse::ButtonsCoords& message)
{
    coords.first = message.xcoord();
    coords.second = message.ycoord();
    int i = 0;
    for (auto it = mouseButtons.begin(); it != mouseButtons.end(); ++it, ++i) {
        it->second = (message.mousebuttons())[i];
    }
}

void ViktorDev::EmulationMouse::emulateMouseMovement(int coordX, int coordY)
{
    memset(&event, 0, sizeof(struct input_event));
    event.type = EV_REL;
    event.code = REL_X;
    event.value = coordX;
    if (write(fdMouse, &event, sizeof(struct input_event)) < 0) {
        perror("error: write");
        exit(writeError);
    }

    memset(&event, 0, sizeof(struct input_event));
    event.type = EV_REL;
    event.code = REL_Y;
    event.value = coordY;
    if (write(fdMouse, &event, sizeof(struct input_event)) < 0) {
        perror("error: write");
        exit(writeError);
    }
}

void ViktorDev::EmulationMouse::emulateMouseButtons(std::vector<std::pair<int, bool>> mouseButton)
{
    memset(&event, 0, sizeof(struct input_event));
    gettimeofday(&event.time, 0);
    event.type = EV_KEY;
    event.code = BTN_LEFT;
    event.value = mouseButtons[0].second;
    if (write(fdMouse, &event, sizeof(struct input_event)) < 0) {
        perror("error: write");
        exit(writeError);
    }
    memset(&event, 0, sizeof(struct input_event));
    event.type = EV_KEY;
    event.code = BTN_RIGHT;
    event.value = mouseButtons[1].second;
    if (write(fdMouse, &event, sizeof(struct input_event)) < 0) {
        perror("error: write");
        exit(writeError);
    }
}

void ViktorDev::EmulationMouse::synMouse()
{
    memset(&event, 0, sizeof(struct input_event));
    event.type = EV_SYN;
    event.code = 0;
    event.value = 0;
    if (write(fdMouse, &event, sizeof(struct input_event)) < 0) {
        perror("error: write");
        exit(writeError);
    }
    previousCoords.first = coords.first;
    previousCoords.second = coords.second;
}
void ViktorDev::EmulationMouse::emulateMouse()
{

    std::pair<int, int> delta;
    delta.first = coords.first - previousCoords.first;
    delta.second = coords.second - previousCoords.second;
    emulateMouseMovement(delta.first, delta.second);
    emulateMouseButtons(mouseButtons);

    memset(&event, 0, sizeof(struct input_event));
    gettimeofday(&event.time, 0);
    synMouse();
    //usleep(10000); //time between ticks
    return;
}
ViktorDev::EmulationMouse::EmulationMouse()
{
    initEmulateMouse();
}
int ViktorDev::EmulationMouse::getCurrentXCoord()
{
    return coords.first;
}
int ViktorDev::EmulationMouse::getCurrentYCoord()
{
    return coords.second;
}
