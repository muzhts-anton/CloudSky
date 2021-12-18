#ifndef emulationConstants_H
#define emulationConstants_H

constexpr int buttonQuanityEm = 9;
constexpr int coordQuanityEm = 2;
constexpr int mouseButtonsQuanity = 2;
constexpr int uiSetEvbit = 100;
constexpr int UiSetKeybit = 101;
constexpr int UiSetRelbit = 102;
constexpr int ioDeviceInitSleep = 550000;
constexpr int uidevIdVendor = 0x1;
constexpr int uidevIdProduct = 0x1;
constexpr int uidevIdVersion = 1;
constexpr int uinputPathLength = 12;
constexpr char uinputPath[uinputPathLength] = "/dev/uinput";
constexpr char ioctlError = 1;
constexpr char writeError = 2;
constexpr char fdError = 2;

#endif // emulationConstants_H