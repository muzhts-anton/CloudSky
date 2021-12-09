#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

#include "gtest/gtest.h"
#include "Worker.h"
#include "createFilesToSend.h"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    std::vector<std::string> filesToSend;
    createFilesToSend(&filesToSend);
    std::vector<std::string> filesToReceive;
    Worker worker("8080", "0.0.0.0");
    worker.start();
    for (size_t i = 0; i < filesToSend.size(); i++)
    {
        filesToReceive.push_back(std::to_string(i));
        try {
            worker.getInteraction(filesToReceive.at(i));
            usleep(50000);
            worker.sendFile(filesToSend.at(i));
            compareFiles(filesToSend.at(i), filesToReceive.at(i));
        } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        }
    }
    return RUN_ALL_TESTS();
}