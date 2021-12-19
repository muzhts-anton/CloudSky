#ifndef DBOPERATIONS_H
#define DBOPERATIONS_H
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
#include <vector>
#include <string>

namespace ViktorDev {
constexpr int gameQuanity = 3;
constexpr int gameNameLength = 50;
constexpr char* connectionInfo = "dbname = serverdb";
constexpr char firstGameName[gameNameLength] = "game1";
constexpr char secondGameName[gameNameLength] = "game2";
constexpr char thirdGameName[gameNameLength] = "game3";
constexpr int firstGamePrice = 1000;
constexpr int secondGamePrice = 600;
constexpr int thirdGamePrice = 500;

enum class transactionResult{
    SUCCESS = 0,
    NOT_ENOUGH_COINS = 1,
    ALREADY_PURCHASED = 2,
};


void setConnection( PGconn** conn);
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
    bool availableGames[gameQuanity] = {false,false,false};
    void parseRequestAuth(PGresult* res);
    void requestAuthorization( PGconn** conn);

};

// class transactionHandlerClient { // Надо с протобафом это сделать
// public:
//     //transactionHandlerClient();
//     //~transactionHandlerClient();
//     void sendToServer();

// private:
//     int productID;
// };

class transactionHandlerServer { // Надо с протобафом это сделать
public:
    transactionHandlerServer(bool wantedGames[gameQuanity]);
    void requestTransactionPeek(std::string username);
    void doTransaction( std::vector<std::pair<std::string, int>> games);
    void sendToClient();
private:
    std::string username;
    int resultCode = 0; // CHANGE TO ENUM! SUCCESS = 0; not enough coins = 1; the product has already been purchased = 2
    int coins = 0; //quanity of coins after transaction
    bool availableGames[gameQuanity] = {false,false,false};
    bool wantedGames[gameQuanity] = {false,false,false};
    void printTransaction();
    void parseRequesTransaction(PGresult* res);
};

class selectedGameHandler {
    selectedGameHandler(int gameId);
    ~selectedGameHandler();
    void sendToServer();
};

}
#endif //DBOPERATIONS_H