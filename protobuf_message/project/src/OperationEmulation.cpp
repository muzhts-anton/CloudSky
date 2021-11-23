#include "../include/OperationEmulation.h"

EmulateInteraction::EmulateInteraction(std::string filePath, KeyboardMouse::ButtonsCoords message)
    : ReceiveInteraction(filePath, message) {

    };
EmulateInteraction::EmulateInteraction(std::string filePath, bool buttonPressed[BUTTON_QUANITY], int coords[2])
    : ReceiveInteraction(filePath, buttonPressed, coords) {

    };
EmulateInteraction::~EmulateInteraction()
{
    fclose(sourceFile);
};
// int readInteraction() { // just use receiveIt()

// };
int EmulateInteraction::emulateInteraction(bool* pressedKeys, int coordX, int coordY) {

};
void EmulateInteraction::emulateMouseMovement(int coordX, int coordY) {

};
void EmulateInteraction::emulateKeyboard(bool* pressedKeys) {

};
int EmulateInteraction::getCurrentXCoord() {

};
int EmulateInteraction::getCurrentYCoord() {

};
bool EmulateInteraction::getCurrentButtonState(char button_symbol) {

};
void EmulateInteraction::initFD(int kb_set[3])
{
    //int fdKeyEmulator;
    fdKeyEmulator = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (fdKeyEmulator < 0) {
        std::cout << "error in open : " << strerror(errno) << std::endl;
    }
    snprintf(devFakeKeyboard.name, UINPUT_MAX_NAME_SIZE, "kb-emulator");
    devFakeKeyboard.id.bustype = BUS_USB;
    devFakeKeyboard.id.vendor = 0x01;
    devFakeKeyboard.id.product = 0x01;
    devFakeKeyboard.id.version = 1;
    if (ioctl(fdKeyEmulator, UI_SET_EVBIT, EV_KEY)) {
        std::cout << "Error in ioctl : UI_SET_EVBIT : EV_KEY : " << strerror(errno) << std::endl;
    }
    for (int i = 0; i < 3; ++i) {
        (this->kb_set)[i] = kb_set[i];
    }
    for (int i = 0; i < 3; ++i) {
        if (ioctl(fdKeyEmulator, UI_SET_KEYBIT, (this->kb_set)[i])) {
            std::cout << "Error in ioctl : UI_SET_KEYBIT" << strerror(errno) << std::endl;
        }
    }
    if (ioctl(fdKeyEmulator, UI_SET_EVBIT, EV_SYN)) {
        std::cout << "Error in ioctl : UI_SET_EVBIT : EV_SYN : " << strerror(errno) << std::endl;
    }
    if (write(fdKeyEmulator, &devFakeKeyboard, sizeof(uinput_user_dev)) < 0) {
        std::cout << "Error in write(): uinput_user_dev struct into uinput file descriptor: " << strerror(errno) << std::endl;
    }
    // create the device via an IOCTL call
    if (ioctl(fdKeyEmulator, UI_DEV_CREATE)) {
        std::cout << "Error in ioctl : UI_DEV_CREATE : " << strerror(errno) << std::endl;
    }
    sleep(1);
    // now fdKeyEmulator represents the end-point file descriptor of the new input device.

    const char* filePathC = filePath.c_str();
    if ((sourceFile = fopen(filePathC, "rb")) == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
};
void EmulateInteraction::readFile()
{
    fread(kbSetBool, sizeof(bool), 3, sourceFile);
    cout << "Readed bools: ";
    for (int i = 0; i < 3; ++i) {
        cout << (kbSetBool[i]);
    }
    cout << endl;
}
void EmulateInteraction::emulateKeyboard()
{
    for (int i = 0; i < 3; ++i) {
        if (kbSetBool[i]) {
            memset(&keyInputEvent, 0, sizeof(input_event));

            // key press event for 'a'
            keyInputEvent.type = EV_KEY;
            keyInputEvent.code = kb_set[i];
            keyInputEvent.value = kbSetBool[i];

            // now write to the file descriptor
            if (write(fdKeyEmulator, &keyInputEvent, sizeof(input_event)) < 0) {
                std::cout << "Error write : KEY_A press : " << strerror(errno) << std::endl;
            }

            memset(&keyInputEvent, 0, sizeof(input_event));
            // EV_SYN for key press event
            keyInputEvent.type = EV_SYN;
            keyInputEvent.code = SYN_REPORT;
            keyInputEvent.value = 0;

            // now write to the file descriptor
            if (write(fdKeyEmulator, &keyInputEvent, sizeof(input_event)) < 0) {
                std::cout << "Error write : EV_SYN for key press : " << strerror(errno) << std::endl;
            }
            sleep(1);
        }
    }
}