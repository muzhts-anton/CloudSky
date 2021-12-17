#include <chrono>
#include <thread>

#include "Worker.h"
#include "KeyboardMouseMessage.pb.h"
#include "messageOperations.h"
#include "operationEmulation.h"
#include "ScreenRecorder.h"


int main(int argc, char *argv[])
{
    if (argc != 3)
        return -1;
    Worker worker(argv[1], argv[2]);
    ScreenRecorder recorder;
    recorder.Start(&worker);
    std::this_thread::sleep_for(std::chrono::seconds(10000));  
    return 0;
}