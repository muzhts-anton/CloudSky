#ifndef emulationConstants_H
#define emulationConstants_H

constexpr int buttonQuanity = 9;
constexpr int coordQuanity = 2;
constexpr int mouseButtonsQuanity = 2;
constexpr int uiSetEvbit = 100;
constexpr int UiSetKeybit = 101;
constexpr int UiSetRelbit = 102;
constexpr int ioDeviceInitSleep = 150000;
constexpr int uidevIdVendor = 0x1;
constexpr int uidevIdProduct = 0x1;
constexpr int uidevIdVersion = 1;
constexpr int uinputPathLength = 12;
constexpr char uinputPath[uinputPathLength] = "/dev/uinput";

#endif // emulationConstants_H