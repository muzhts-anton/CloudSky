#include "dbMessages.pb.h"
#include "dbOperations.h"
#include "postgresql/libpq-fe.h"
#include <arpa/inet.h>
#include <iomanip>
#include <iostream>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main()
{
    //TEST requestAuthorization
    std::vector<std::pair<std::string, int>> games { { ViktorDev::firstGameName, ViktorDev::firstGamePrice },
        { ViktorDev::secondGameName, ViktorDev::secondGamePrice },
        { ViktorDev::thirdGameName, ViktorDev::thirdGamePrice } };
    ViktorDev::authorizationHandler autHandler;
    autHandler.requestAuthorization("arbuzik");

    std::string filePath = "dbInformation.bin";
    std::string username = "President";
    std::string password = "mypasswordDT1";

    // Test reglog
    std::cout<<std::endl<<std::endl<<"TEST: reglog"<<std::endl<<std::endl;
    dbInteraction::registrationOrLogIn regOrLogMessage;
    regOrLogMessage.set_regorlog(false);
    ViktorDev::printRegOrLogMessage(regOrLogMessage);
    ViktorDev::ClientRegOrLog sender(filePath, regOrLogMessage);
    sender.sendIt();
    ViktorDev::ServerRegOrLog receiver(filePath);
    receiver.receiveIt();

    //Test authorization
    std::cout<<std::endl<<std::endl<<"TEST: authorization"<<std::endl<<std::endl;
    dbInteraction::authInformation message;
    message.set_username(username);
    message.set_password(password);
    ViktorDev::ClientAuthorizationHandler clientAuth(filePath, message);
    clientAuth.sendIt();
    std::cout << std::endl<< std::endl<< "sended message:"<< std::endl;
    clientAuth.printMessage();

    dbInteraction::authInformation receivedMessage;
    ViktorDev::ServerAuthorizationHandler serverAuth(filePath, receivedMessage);
    serverAuth.receiveIt();
    std::cout << std::endl<< std::endl<< "received message:"<< std::endl;
    serverAuth.printMessage();
    serverAuth.check();
    serverAuth.sendIt();
    serverAuth.printResult();
    clientAuth.receiveIt();
    clientAuth.printResult();

    // Test registration
    std::cout<<std::endl<<std::endl<<"TEST: registration"<<std::endl<<std::endl;
    std::string email = "Masha@mail.ru";
    username = "Masha";
    password = "passwordMasha";
    std::string country = "Russia";
    std::string firstname = "Masha";
    std::string secondname = "Romanova"; //
    int coins = 0;
    bool availableGames[3] { false, false, false };
    int age = 20;


    dbInteraction::registrationInfo regMessage;
    regMessage.set_email(email);
    regMessage.set_username(username);
    regMessage.set_password(password);
    regMessage.set_country(country);
    regMessage.set_firstname(firstname);
    regMessage.set_secondname(secondname);
    regMessage.set_coins(coins);
    for (int i = 0; i < ViktorDev::gameQuanity; ++i) {
        regMessage.add_availablegames(availableGames[i]);
    }
    regMessage.set_age(age);

    ViktorDev::ClientRegistrationHandler clientReg(filePath, regMessage);
    clientReg.sendIt();
    std::cout << std::endl<< "sended message:" << std::endl;
    clientReg.printMessage();

    dbInteraction::registrationInfo receivedRegMessage;
    ViktorDev::ServerRegistrationHandler serverReg(filePath, receivedRegMessage);
    serverReg.receiveIt();
    std::cout << std::endl<< "received message:" << std::endl;
    serverReg.printMessage();
    serverReg.check();
    serverReg.sendIt();
    serverReg.printResult();
    clientReg.receiveIt();
    clientReg.printResult();
}
    