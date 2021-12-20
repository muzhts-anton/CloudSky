#include "dbOperations.h"

void ViktorDev::authorizationHandler::printClient()
{
    std::cout << std::endl
              << "firstName = " << firstName << std::endl
              << "secondName = " << secondName << std::endl
              << "coins = " << coins << std::endl
              << "availableGames = " << availableGames[0] << ' ' << availableGames[1] << ' ' << availableGames[2] << std::endl;
};

void ViktorDev::authorizationHandler::parseRequestAuth(PGresult* res)
{
    int nTuples = PQntuples(res);
    fprintf(stdout, "Tuples count: %i\n", nTuples);
    int nFields = PQnfields(res);
    fprintf(stdout, "Fields count: %i\n", nFields);
    for (int tuple = 0; tuple < PQntuples(res); tuple++) {
        firstName.assign(PQgetvalue(res, 0, 0), PQgetlength(res, 0, 0));
        secondName.assign(PQgetvalue(res, 0, 1), PQgetlength(res, 0, 1));
        int factor = 1;
        for (int i = PQgetlength(res, 0, 2) - 1; i >= 0; --i) {
            coins += int((PQgetvalue(res, 0, 2)[i] - '0') * factor);
            factor *= 10;
        }
        for (int i = 0; i < gameQuanity; ++i) {
            if (PQgetvalue(res, 0, 3)[2 * i + 1] == 't') {
                availableGames[i] = true;
            } else {
                availableGames[i] = false;
            }
        }
    }
}
void ViktorDev::authorizationHandler::showBinaryResults(PGresult* res)
{
    /* узнали формат результата: бинарный или текстовый?? */
    int binaryTuples = PQbinaryTuples(res);
    if (binaryTuples == 1)
        fprintf(stdout, "Binary data\n");
    else
        fprintf(stdout, "Text data\n");
    parseRequestAuth(res);
    printClient();
}

void ViktorDev::setConnection(PGconn** conn)
{
    if (PQstatus(*conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(*conn));
        PQfinish(*conn);
        exit(1);
    }
}
void ViktorDev::authorizationHandler::requestAuthorization(std::string username)
{
    /* Устанавливаем соединение с базой данных.
       На входе строка вида: "dbname=mydb user=myuser"
       подробности в описании функции в документации */
    const char* conninfo = connectionInfo;
    PGconn* conn = PQconnectdb(conninfo);
    setConnection(&conn);

    const char* sql1 = "SELECT firstname, secondname, coins, availablegames FROM Clients WHERE username = $1";
    const char* sql1param = username.c_str();
    PGresult* res = PQexecParams(conn, sql1, 1, NULL, &sql1param, NULL, NULL, 0);
    ExecStatusType resStatus = PQresultStatus(res);
    if (resStatus != PGRES_TUPLES_OK) {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
    char* resStatusStr = PQresStatus(resStatus);
    fprintf(stdout, "Query Result Status: %s\n", resStatusStr);
    parseRequestAuth(res);
    printClient();

    PQclear(res);
    PQfinish(conn);
}

ViktorDev::transactionHandlerServer::transactionHandlerServer(bool wantedGames[gameQuanity])
{
    for (int i = 0; i < gameQuanity; ++i) {
        availableGames[i] = wantedGames[i];
    }
}

void ViktorDev::transactionHandlerServer::printTransaction()
{
    std::cout << std::endl
              << "coins = " << coins << std::endl
              << "availableGames = " << availableGames[0] << ' ' << availableGames[1] << ' ' << availableGames[2] << std::endl;
};

void ViktorDev::transactionHandlerServer::parseRequestTransaction(PGresult* res)
{
    int nTuples = PQntuples(res);
    fprintf(stdout, "Tuples count: %i\n", nTuples);
    int nFields = PQnfields(res);
    fprintf(stdout, "Fields count: %i\n", nFields);
    for (int tuple = 0; tuple < PQntuples(res); tuple++) {
        int factor = 1;
        for (int i = PQgetlength(res, 0, 0) - 1; i >= 0; --i) {
            coins += int((PQgetvalue(res, 0, 0)[i] - '0') * factor);
            factor *= 10;
        }
        for (int i = 0; i < gameQuanity; ++i) {
            if (PQgetvalue(res, 0, 1)[2 * i + 1] == 't') {
                availableGames[i] = true;
            } else {
                availableGames[i] = false;
            }
        }
    }
}

void ViktorDev::transactionHandlerServer::doTransaction(std::vector<std::pair<std::string, int>> games)
{
    int gameId = -1;
    for (int i = 0; i < gameQuanity; ++i) {
        if (wantedGames[i] == true) {
            gameId = i;
        };
    }
    //TransactionResult
    if (coins < games[gameId].second) {
        // send protobuf message
        return;
    }
    if (availableGames[gameId] == true) {
        //send protobuf message
        return;
    }
    // do transaction
    //send protobuf message
};

void ViktorDev::transactionHandlerServer::requestTransactionPeek(std::string username)
{
    const char* conninfo = connectionInfo;
    PGconn* conn = PQconnectdb(conninfo);
    setConnection(&conn);

    const char* sql1 = "SELECT coins, availablegames FROM Clients WHERE username = $1";
    const char* sql1param = username.c_str();
    PGresult* res = PQexecParams(conn, sql1, 1, NULL, &sql1param, NULL, NULL, 0);
    ExecStatusType resStatus = PQresultStatus(res);
    if (resStatus != PGRES_TUPLES_OK) {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
    char* resStatusStr = PQresStatus(resStatus);
    fprintf(stdout, "Query Result Status: %s\n", resStatusStr);
    parseRequestTransaction(res);
    printTransaction();

    PQclear(res);
    PQfinish(conn);
};