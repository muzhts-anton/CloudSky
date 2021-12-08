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
#include "operationEmulation.h"

using namespace std;
using namespace ViktorDev;

#define die(str, args...)   \
    do {                    \
        perror(str);        \
        exit(EXIT_FAILURE); \
    } while (0)

void ViktorDev::EmulateInteraction::printEm(){
    cout<<"Hello from operationEmulation";
}

EmulateInteraction::EmulateInteraction(){
    initEmulateKbMouse();
}
EmulateInteraction::~EmulateInteraction()
{
    
    if (ioctl(fd, UI_DEV_DESTROY) < 0)
        die("error: cannot destroy uinput device ");
    close(fd);
    //fclose(sourceFile);
};

void ViktorDev::EmulateInteraction::initEmulateMouse() {
    coordX = coordY = 0;
    previousCoordX = previousCoordY = 0;
    for(int i = 0; i < mouseButtonsQuanity; ++i){
        mouseButtons[i]=0;
    }
    fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if (fd < 0)
        die("error: open");
    if (ioctl(fd, UI_SET_EVBIT, EV_KEY) < 0)
        die("error: ioctl");
    if (ioctl(fd, UI_SET_KEYBIT, BTN_LEFT) < 0)
        die("error: ioctl");
    if (ioctl(fd, UI_SET_KEYBIT, BTN_RIGHT) < 0)
        die("error: ioctl");

    if (ioctl(fd, UI_SET_EVBIT, EV_REL) < 0)
        die("error: ioctl");
    if (ioctl(fd, UI_SET_RELBIT, REL_X) < 0)
        die("error: ioctl");
    if (ioctl(fd, UI_SET_RELBIT, REL_Y) < 0)
        die("error: ioctl");

    if (ioctl(fd, UI_SET_KEYBIT, BTN_MOUSE) < 0)
        die("error: ioctl");

    memset(&uidev, 0, sizeof(uidev));
    snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "uinput-sample");
    uidev.id.bustype = BUS_USB;
    uidev.id.vendor = 0x1;
    uidev.id.product = 0x1;
    uidev.id.version = 1;

    if (write(fd, &uidev, sizeof(uidev)) < 0)
        die("error: write");

    if (ioctl(fd, UI_DEV_CREATE) < 0)
        die("error: ioctl");

    usleep(150000);

    int coords[5][2];
    for (int i = 0; i < 5; ++i) {
        coords[i][0] = 200;
        coords[i][1] = 200;
    }

    return;
}
void ViktorDev::EmulateInteraction::emulateMouseMovement() {

        int deltaX = coordX - previousCoordX;
        int deltaY = coordY - previousCoordY;
        memset(&ev, 0, sizeof(struct input_event));
        gettimeofday(&ev.time, 0);
        ev.type = EV_KEY;
        ev.code = BTN_LEFT;
        ev.value = mouseButtons[0];
        if (write(fd, &ev, sizeof(struct input_event)) < 0)
            die("error: write");
        memset(&ev, 0, sizeof(struct input_event));
        ev.type = EV_REL;
        ev.code = REL_X;
        ev.value = deltaX;
        if (write(fd, &ev, sizeof(struct input_event)) < 0)
            die("error: write");

        memset(&ev, 0, sizeof(struct input_event));
        ev.type = EV_REL;
        ev.code = REL_Y;
        ev.value = deltaY;
        if (write(fd, &ev, sizeof(struct input_event)) < 0)
            die("error: write");

        memset(&ev, 0, sizeof(struct input_event));
        ev.type = EV_KEY;
        ev.code = BTN_RIGHT;
        ev.value = mouseButtons[1];
        if (write(fd, &ev, sizeof(struct input_event)) < 0)
            die("error: write");
        
        memset(&ev, 0, sizeof(struct input_event));
        ev.type = EV_SYN;
        ev.code = 0;
        ev.value = 0;
        if (write(fd, &ev, sizeof(struct input_event)) < 0)
            die("error: write");
        previousCoordX = coordX;
        previousCoordY = coordY;
    return;
};



void ViktorDev::EmulateInteraction::initEmulateKeyboard(){
    for(int i = 0; i < buttonQuanity;i++){
        kbSetBool[i] = 0;
    }
    kbSet[0] = KEY_A;
    kbSet[1] = KEY_W;
    kbSet[2] = KEY_S;
    kbSet[3] = KEY_D;
    kbSet[4] = KEY_SPACE;
    kbSet[5] = KEY_Q;
    kbSet[6] = KEY_E;
    kbSet[7] = KEY_F;
    kbSet[8] = KEY_ESC;
    // create uinput file descriptor
    //int fdKeyEmulator;                                                                    

    // open file descriptor
    /*
    Uinput is a kernel module that makes it possible to emulate input devices from userspace. By writing to /dev/uinput
    device, a process can create a virtual input device with specific capabilities. Once this virtual device is created, 
    the process can send events through it, that will be delivered to userspace and in-kernel consumers.
    */
    fdKeyEmulator = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if(fdKeyEmulator < 0)
    {
        std::cout << "error in open : " << strerror(errno) << std::endl;
    }

    // uinput_user_dev struct for fake keyboard
    struct uinput_user_dev devFakeKeyboard;
    memset(&devFakeKeyboard, 0, sizeof(uinput_user_dev));
    snprintf(devFakeKeyboard.name, UINPUT_MAX_NAME_SIZE, "kb-emulator");
    devFakeKeyboard.id.bustype = BUS_USB;
    devFakeKeyboard.id.vendor = 0x01;
    devFakeKeyboard.id.product = 0x01;
    devFakeKeyboard.id.version = 1;

    /**configure the input device to send type of events, inform to subsystem which 
     * type of input events we are using via ioctl calls. 
     * UI_SET_EVBIT ioctl request is used to applied on uinput descriptor to enable a type of event.
     **/
    // enable key press/release event
    if(ioctl(fdKeyEmulator, UI_SET_EVBIT, EV_KEY))
    {
        std::cout << "Error in ioctl : UI_SET_EVBIT : EV_KEY : " << strerror(errno) << std::endl;
    }
    //int kbSet[3]{KEY_A, KEY_B, KEY_C};


    // enable set of KEY events here
    for(int i = 0; i < buttonQuanity; ++i){
      if(ioctl(fdKeyEmulator, UI_SET_KEYBIT, kbSet[i]))
      {
          std::cout << "Error in ioctl : UI_SET_KEYBIT : KEY_A : " << strerror(errno) << std::endl;
      }
    }

    // enable synchronization event
    if(ioctl(fdKeyEmulator, UI_SET_EVBIT, EV_SYN))
    {
        std::cout << "Error in ioctl : UI_SET_EVBIT : EV_SYN : " << strerror(errno) << std::endl;
    }

    // now write the uinput_user_dev structure into uinput file descriptor
    if(write(fdKeyEmulator, &devFakeKeyboard, sizeof(uinput_user_dev)) < 0)
    {
        std::cout << "Error in write(): uinput_user_dev struct into uinput file descriptor: " << strerror(errno) << std::endl;
    }

    // create the device via an IOCTL call 
    if(ioctl(fdKeyEmulator, UI_DEV_CREATE))
    {
        std::cout << "Error in ioctl : UI_DEV_CREATE : " << strerror(errno) << std::endl;
    }
    sleep (1);
    // now fdKeyEmulator represents the end-point file descriptor of the new input device. 


    // struct member for input events
    //struct input_event keyInputEvent;

    cout<<endl;

}

void ViktorDev::EmulateInteraction::initEmulateKbMouse(){
    initEmulateMouse();
    initEmulateKeyboard();
}
void ViktorDev::EmulateInteraction::setKeysCoords(const KeyboardMouse::ButtonsCoords &message){
    coordX = message.xcoord();
    coordY = message.ycoord();

    for (int i =0; i < buttonQuanity; i++) {
        kbSetBool[i] = (message.buttonpressed())[i];
    };
    cout<<"Readed bools: ";
    for (int i = 0; i< buttonQuanity; ++i){
        cout<<(kbSetBool[i])<<' ';
    }
    cout<<endl;
    mouseButtons[0] = (message.mousebuttons())[0];
    mouseButtons[1] = (message.mousebuttons())[1];
}
void ViktorDev::EmulateInteraction::setKeyboard(int keyCode, bool isPressed){
    memset(&keyInputEvent, 0, sizeof(input_event));

    // key press event for 'a'
    keyInputEvent.type = EV_KEY;
    keyInputEvent.code = keyCode; //kbSet[i];
    keyInputEvent.value = isPressed; //kbSetBool[i];

    // now write to the file descriptor
    if(write(fdKeyEmulator, &keyInputEvent, sizeof(input_event)) < 0)
    {
        std::cout << "Error write : KEY_A press : " << strerror(errno) << std::endl;
    }
}
void ViktorDev::EmulateInteraction::synKeyboard(){
    memset(&keyInputEvent, 0, sizeof(input_event));
    // EV_SYN for key press event
    keyInputEvent.type = EV_SYN;
    keyInputEvent.code = SYN_REPORT;
    keyInputEvent.value = 0;

    // now write to the file descriptor
    if(write(fdKeyEmulator, &keyInputEvent, sizeof(input_event)) < 0)
    {
        std::cout << "Error write : EV_SYN for key press : " << strerror(errno) << std::endl;
    }
}

void ViktorDev::EmulateInteraction::emulateKeyboard(){ 
    for(int i = 0; i < buttonQuanity; ++i){
        setKeyboard(kbSet[i], kbSetBool[i]);
    }
    synKeyboard();
    sleep(1); // time between ticks
};
void ViktorDev::EmulateInteraction::emulateKbMouse(){
    emulateKeyboard();
    emulateMouseMovement();
}
