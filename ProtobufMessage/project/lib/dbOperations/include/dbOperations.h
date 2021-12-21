#ifndef DBOPERATIONS_H
#define DBOPERATIONS_H
#include "dbConstants.h"
#include "dbMessages.pb.h"
#include "postgresql/libpq-fe.h"
#include <arpa/inet.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <vector>

namespace ViktorDev {

enum class AuthorizationResult {
    SUCCESS,
    WRONG_USERNAME,
    WRONG_PASSWORD
};
enum class RegistrationResult {
    SUCCESS,
    DUPLICATED_INFO
};

enum class TransactionResult {
    SUCCESS = 0,
    NOT_ENOUGH_COINS = 1,
    ALREADY_PURCHASED = 2,
};

void setConnection(PGconn** conn);
class authorizationHandler {
public:
    void showBinaryResults(PGresult* res);
    void requestAuthorization(std::string username);
    void printClient();

private:
    std::string dbName;
    std::string username;
    const char* conninfo = "dbname = serverdb";
    std::string firstName;
    std::string secondName;
    int coins = 0;
    bool availableGames[gameQuanity] = { false, false, false };
    void parseRequestAuth(PGresult* res);
    void requestAuthorization(PGconn** conn);
};

class TransactionHandlerServer {
public:
    std::ofstream out;
    std::ifstream in;
    TransactionHandlerServer(dbInteraction::transactionAnswer message);
    void requestTransactionPeek(std::string username);
    void requestTransactionPeek();
    void sendToClient();
    std::string filePath;
    dbInteraction::transactionRequst& getRequestMessage();
    dbInteraction::transactionAnswer& getAnswerMessage();

private:
    std::string username;
    int resultCode = 0; // CHANGE TO ENUM! SUCCESS = 0; not enough coins = 1; the product has already been purchased = 2
    int coins = 0; //quanity of coins after transaction
    bool availableGames[gameQuanity] = { false, false, false };
    bool wantedGames[gameQuanity] = { false, false, false };
    void printTransaction();
    void parseRequestTransaction(PGresult* res);
    void doTransaction();
    dbInteraction::transactionRequst requestMessage;
    dbInteraction::transactionAnswer answerMessage;
};

class TransactionHandlerClient {
public:
    std::ofstream out;
    std::ifstream in;
    std::string filePath;
    TransactionResult result;

    dbInteraction::transactionRequst& getRequestMessage();
    dbInteraction::transactionAnswer& getAnswerMessage();
    TransactionHandlerClient() = delete;
    TransactionHandlerClient(std::string filePath, dbInteraction::transactionRequst message);
    int sendIt();
    int receiveIt();
    void printRequestMessage();
    void printAnswerMessage();

private:
    dbInteraction::transactionRequst requestMessage;
    dbInteraction::transactionAnswer answerMessage;
};

class selectedGameHandler {
    selectedGameHandler(int gameId);
    //~selectedGameHandler();
    void sendToServer();
};

class ClientAuthorizationHandler {
public:
    std::ofstream out;
    std::ifstream in;
    std::string filePath;
    AuthorizationResult result;

    dbInteraction::clientAuthInformation& getMessage();
    ClientAuthorizationHandler() = delete;
    ClientAuthorizationHandler(std::string filePath, dbInteraction::clientAuthInformation message);
    int sendIt();
    int receiveIt();
    void printMessage();
    void printResult();

private:
    dbInteraction::clientAuthInformation message;
    dbInteraction::serverAuthInformation answerMessage;
};

class ServerAuthorizationHandler {
public:
    std::ifstream in;
    std::ofstream out;
    std::string filePath;
    AuthorizationResult checkingResult;

    dbInteraction::clientAuthInformation& getMessage();
    ServerAuthorizationHandler() = delete;
    ServerAuthorizationHandler(std::string filePath, dbInteraction::clientAuthInformation message);
    //~ServerAuthorizationHandler();
    int receiveIt();
    void printMessage();
    void printResult();
    void parseRequestCheck(PGresult* res);
    void check();
    int sendIt();

private:
    dbInteraction::clientAuthInformation message;
};

class ClientRegistrationHandler {
public:
    std::ofstream out;
    std::ifstream in;
    std::string filePath;
    RegistrationResult result;

    dbInteraction::registrationInfo& getMessage();
    ClientRegistrationHandler() = delete;
    ClientRegistrationHandler(std::string filePath, dbInteraction::registrationInfo message);
    int sendIt();
    int receiveIt();
    void printMessage();
    void printResult();

private:
    dbInteraction::registrationInfo message;
    dbInteraction::serverAuthInformation answerMessage;
};

class ServerRegistrationHandler {
public:
    std::ifstream in;
    std::ofstream out;
    std::string filePath;
    RegistrationResult checkingResult;

    dbInteraction::registrationInfo& getMessage();
    ServerRegistrationHandler() = delete;
    ServerRegistrationHandler(std::string filePath, dbInteraction::registrationInfo message);
    //~ServerAuthorizationHandler();
    int receiveIt();
    void printMessage();
    void printResult();
    void parseRequestCheck(PGresult* res);
    void check();
    void addRecord(dbInteraction::registrationInfo addMessage);
    int sendIt();

private:
    void updateInt(dbInteraction::registrationInfo addMessage);
    dbInteraction::registrationInfo message;
};

class CheckUser {
public:
    CheckUser() = delete;
    CheckUser(std::string username, std::string password);
    void check();
    void parseRequestCheck(PGresult* res);
    AuthorizationResult result;

private:
    std::string username;
    std::string password;
};

class ClientRegOrLog {
public:
    std::ofstream out;
    dbInteraction::registrationOrLogIn message;
    std::string filePath;
    ClientRegOrLog(std::string filePath, dbInteraction::registrationOrLogIn message);
    int sendIt();
};

class ServerRegOrLog {
public:
    std::string filePath;
    std::ifstream in;
    bool status;
    dbInteraction::registrationOrLogIn message;
    ServerRegOrLog(std::string filePath);
    int receiveIt();
};
void printRegOrLogMessage(dbInteraction::registrationOrLogIn message);

}

#endif //DBOPERATIONS_H