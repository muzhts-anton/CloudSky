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
    int fd_key_emulator;                                                                    

    // open file descriptor
    /*
    Uinput is a kernel module that makes it possible to emulate input devices from userspace. By writing to /dev/uinput
    device, a process can create a virtual input device with specific capabilities. Once this virtual device is created, 
    the process can send events through it, that will be delivered to userspace and in-kernel consumers.
    */
    fd_key_emulator = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
    if(fd_key_emulator < 0)
    {
        std::cout << "error in open : " << strerror(errno) << std::endl;
    }

    // uinput_user_dev struct for fake keyboard
    struct uinput_user_dev dev_fake_keyboard;
    memset(&dev_fake_keyboard, 0, sizeof(uinput_user_dev));
    snprintf(dev_fake_keyboard.name, UINPUT_MAX_NAME_SIZE, "kb-emulator");
    dev_fake_keyboard.id.bustype = BUS_USB;
    dev_fake_keyboard.id.vendor = 0x01;
    dev_fake_keyboard.id.product = 0x01;
    dev_fake_keyboard.id.version = 1;

    /**configure the input device to send type of events, inform to subsystem which 
     * type of input events we are using via ioctl calls. 
     * UI_SET_EVBIT ioctl request is used to applied on uinput descriptor to enable a type of event.
     **/
    // enable key press/release event
    if(ioctl(fd_key_emulator, UI_SET_EVBIT, EV_KEY))
    {
        std::cout << "Error in ioctl : UI_SET_EVBIT : EV_KEY : " << strerror(errno) << std::endl;
    }
    int kb_set[3]{KEY_A, KEY_B, KEY_C};
    // enable set of KEY events here
    for(int i = 0; i < 3; ++i){
      if(ioctl(fd_key_emulator, UI_SET_KEYBIT, kb_set[i]))
      {
          std::cout << "Error in ioctl : UI_SET_KEYBIT : KEY_A : " << strerror(errno) << std::endl;
      }
    }

    // enable synchronization event
    if(ioctl(fd_key_emulator, UI_SET_EVBIT, EV_SYN))
    {
        std::cout << "Error in ioctl : UI_SET_EVBIT : EV_SYN : " << strerror(errno) << std::endl;
    }

    // now write the uinput_user_dev structure into uinput file descriptor
    if(write(fd_key_emulator, &dev_fake_keyboard, sizeof(uinput_user_dev)) < 0)
    {
        std::cout << "Error in write(): uinput_user_dev struct into uinput file descriptor: " << strerror(errno) << std::endl;
    }

    // create the device via an IOCTL call 
    if(ioctl(fd_key_emulator, UI_DEV_CREATE))
    {
        std::cout << "Error in ioctl : UI_DEV_CREATE : " << strerror(errno) << std::endl;
    }
    sleep (1);
    // now fd_key_emulator represents the end-point file descriptor of the new input device. 


    // struct member for input events
    struct input_event key_input_event;

    bool kb_set_bool[3]{1,1,0};
    bool *pkb_set_bool = kb_set_bool;
    FILE * buttons;
    if ((buttons=fopen("pressed_butons.txt", "wb"))==NULL) {
        printf ("Cannot open file.\n");
        exit(1);
    }
    fwrite(kb_set_bool, sizeof(bool), 3,buttons);
    fclose(buttons);

    if ((buttons=fopen("pressed_butons.txt", "rb"))==NULL) {
        printf ("Cannot open file.\n");
        exit(1);
    }
    //for(int i = 0; i < 1; ++i){
    fread(kb_set_bool, sizeof(bool), 3,buttons);
    fclose(buttons);
    //}
    cout<<"Readed bools: ";
    for (int i = 0; i< 3; ++i){
        cout<<(kb_set_bool[i]);
    }
    cout<<endl;

    //if((int)'0'-48) cout<<"!!!!!!!!!!";
    for(int i = 0; i < 3; ++i){

        if (kb_set_bool[i]){
            memset(&key_input_event, 0, sizeof(input_event));

            // key press event for 'a'
            key_input_event.type = EV_KEY;
            key_input_event.code = kb_set[i];
            key_input_event.value = kb_set_bool[i];

            // now write to the file descriptor
            if(write(fd_key_emulator, &key_input_event, sizeof(input_event)) < 0)
            {
                std::cout << "Error write : KEY_A press : " << strerror(errno) << std::endl;
            }

            memset(&key_input_event, 0, sizeof(input_event));
            // EV_SYN for key press event
            key_input_event.type = EV_SYN;
            key_input_event.code = SYN_REPORT;
            key_input_event.value = 0;

            // now write to the file descriptor
            if(write(fd_key_emulator, &key_input_event, sizeof(input_event)) < 0)
            {
                std::cout << "Error write : EV_SYN for key press : " << strerror(errno) << std::endl;
            }
            sleep (1);
        }
    }


    return 0;
}