#include "Worker.h"
#include "KeyboardMouseMessage.pb.h"
#include "messageOperations.h"
#include "operationEmulation.h"
#include "ScreenRecorder.h"

using namespace ViktorDev;

int main(int argc, char *argv[])
{
    if (argc != 3)
        return -1;
    Worker worker(argv[1], argv[2]);
    worker.start();
    ScreenRecorder recorder;
    recorder.initScreenGrabber();
    recorder.captureVideoData(&worker);
    return 0;
}