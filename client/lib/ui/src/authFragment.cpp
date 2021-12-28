#include "authFragment.h"
#include "fragmentThemeStyle.h"
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
namespace fragment {

constexpr const char *serverIP = "10.147.18.164";
constexpr int serverPort = 8085;

AuthFragment::AuthFragment()
    : _explanLabel(new QLabel("Input your data to confirm authorization"))
    , _userName(new QLineEdit(this))
    , _userPassword(new QLineEdit(this))
    , _authBut(new QPushButton("Authorization"))
    , _backBut(new QPushButton("Back"))
{
    TCPSocket->activateSocket();
    usleep(100000);
    _explanLabel->setStyleSheet(themestyle::fixed.value(themestyle::Type::CAPITALLABEL));
    _userName->setStyleSheet(themestyle::fixed.value(themestyle::Type::LINEEDIT) + themestyle::active.value(themestyle::Type::LINEEDIT));
    _userPassword->setStyleSheet(themestyle::fixed.value(themestyle::Type::LINEEDIT) + themestyle::active.value(themestyle::Type::LINEEDIT));
    _authBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::MAINBUTTON));
    _backBut->setStyleSheet(themestyle::fixed.value(themestyle::Type::SECONDBUTTON));

    _userName->setPlaceholderText("User Name");
    _userPassword->setPlaceholderText("Password");
    _userPassword->setEchoMode(QLineEdit::Password);
    _backBut->setFixedWidth(75);

    _buttsHL = new QHBoxLayout;
    _buttsHL->addWidget(_backBut);
    _buttsHL->addWidget(_authBut);

    _mainVL = new QVBoxLayout(this);
    _mainVL->addWidget(_explanLabel);
    _mainVL->addWidget(_userName);
    _mainVL->addWidget(_userPassword);
    _mainVL->addLayout(_buttsHL);

    _mainVL->setAlignment(Qt::AlignCenter);

    connect(_authBut, &QPushButton::clicked, this, &AuthFragment::onAuth);
    connect(_backBut, &QPushButton::clicked, this, &AuthFragment::onBack);
}

bool AuthFragment::checkData()
{
    // TODO(Tony, Viktor): implement with DB
    return true;
}

void AuthFragment::onResume()
{
    emit back();
}

// slots
void AuthFragment::onAuth()
{
    if(!this->checkData())
        return;

    infoSocket = new TCPClient::TCPClientSocket(8090, serverIP);
    infoSocket->activateSocket();
    
    std::string filename = "authRegistrtionInfo.bin";
    dbInteraction::registrationOrLogIn regOrLogMessage;
    regOrLogMessage.set_regorlog(true);
    ViktorDev::printRegOrLogMessage(regOrLogMessage);
    ViktorDev::ClientRegOrLog sender(filename, regOrLogMessage);
    sender.sendIt();
    infoSocket->transmitFile(filename);

    dbInteraction::authInformation message;
    message.set_username(_userName->text().toStdString());
    message.set_password(_userPassword->text().toStdString());
    ViktorDev::ClientAuthorizationHandler clientAuth(filename, message);
    clientAuth.sendIt();
    
    infoSocket->transmitFile(filename);

    std::cout << std::endl<< std::endl<< "sended message:"<< std::endl;
    clientAuth.printMessage();
    usleep(1000000);
    infoSocket->receiveFile(filename);
    clientAuth.receiveIt();
    clientAuth.printResult();
    
    if (clientAuth.result == ViktorDev::AuthorizationResult::SUCCESS){
        infoSocket->receiveFile(filename);
        int receiveUserInfoResult = clientAuth.receiveUserInfo();
        if(receiveUserInfoResult != 0){
            std::cout<< "[LOG] : Error with receiving user info" << std::endl;
            exit(ViktorDev::errorParseMessage);
        }
        clientAuth.printMessageRegistration();
    }
    else
        return;
    
    delete infoSocket;
    emit navigateTo(screens::ScreenNames::MAIN);
}

void AuthFragment::onBack()
{
    emit back();
}

} // namespace fragment
