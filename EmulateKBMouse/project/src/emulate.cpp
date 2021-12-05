/*
#! /bin/bash
# move the mouse  x    y
xdotool mousemove 1800 500
# left click
xdotool click 1
# right click
xdotool click 3


Reading mouse coords
# cat /dev/input/mice | od -t x1 -w3 




#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/input.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

int main() {
  struct input_event event, event_end;

  int fd = open("/dev/input/event10", O_RDWR);
  if (fd < 0) {
    printf("Errro open mouse:%s\n", strerror(errno));
    return -1;
  }
  memset(&event, 0, sizeof(event));
  memset(&event, 0, sizeof(event_end));
  gettimeofday(&event.time, NULL);
  event.type = EV_REL;
  event.code = REL_X;
  event.value = 100;
  gettimeofday(&event_end.time, NULL);
  event_end.type = EV_SYN;
  event_end.code = SYN_REPORT;
  event_end.value = 0;
  for (int i=0; i<5; i++) {
    write(fd, &event, sizeof(event));// Move the mouse
    write(fd, &event_end, sizeof(event_end));// Show move
    sleep(1);// wait
  }
  close(fd);
  return 0;
}
*/

#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <iostream>

#include <time.h>
#include <string>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    // create uinput file descriptor
    int fdKeyEmulator;                                                                    

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
    int kbSet[3]{KEY_A, KEY_B, KEY_C};
    // enable set of KEY events here
    for(int i = 0; i < 3; ++i){
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
    struct input_event keyInputEvent;

    bool kbSetBool[3]{1,1,1};
    //bool *pkb_set_bool = kbSetBool;
    // FILE * buttons;
    // if ((buttons=fopen("pressed_butons.txt", "wb"))==NULL) {
    //     printf ("Cannot open file.\n");
    //     exit(1);
    // }
    //fwrite(kbSetBool, sizeof(bool), 3,buttons);
    //fclose(buttons);

    // if ((buttons=fopen("pressed_butons.txt", "rb"))==NULL) {
    //     printf ("Cannot open file.\n");
    //     exit(1);
    // }
    //for(int i = 0; i < 1; ++i){
    //fread(kbSetBool, sizeof(bool), 3,buttons);
    //fclose(buttons);
    //}
    cout<<"Readed bools: ";
    for (int i = 0; i< 3; ++i){
        cout<<(kbSetBool[i]);
    }
    cout<<endl;

    //if((int)'0'-48) cout<<"!!!!!!!!!!";
    for(int i = 0; i < 3; ++i){

        if (kbSetBool[i]){
            memset(&keyInputEvent, 0, sizeof(input_event));

            // key press event for 'a'
            keyInputEvent.type = EV_KEY;
            keyInputEvent.code = kbSet[i];
            keyInputEvent.value = kbSetBool[i];

            // now write to the file descriptor
            if(write(fdKeyEmulator, &keyInputEvent, sizeof(input_event)) < 0)
            {
                std::cout << "Error write : KEY_A press : " << strerror(errno) << std::endl;
            }

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
            sleep (1);
        }
    }
    return 0;
}