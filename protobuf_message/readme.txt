    Предварительно потребуется установить prorobuf, вот подробная инструкция, как это сделать:
https://github.com/protocolbuffers/protobuf/blob/master/src/README.md

Comands:
Create pb.cc file:
protoc --cpp_out=. keyboard_mouse_message.proto

for compiling files:
g++ -std=c++17 send_receive_message.cpp keyboard_mouse_message.pb.cc -o send_receive_keyb_m `pkg-config --cflags --libs protobuf`

for execute binary file:
./send_receive_keyb_m

watching in buttons_coords.bin:
hd buttons_coords.bin 

