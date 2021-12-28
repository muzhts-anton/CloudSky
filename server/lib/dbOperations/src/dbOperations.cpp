#include "dbOperations.h"
#include "dbMessages.pb.h"

void ViktorDev::authorizationHandler::printClient()
{
    std::cout << std::endl
              << "firstName = " << firstName << std::endl
              << "secondName = " << secondName << std::endl
              << "coins = " << coins << std::endl
              << "availableGames = " << availableGames[0] << ' ' << availableGames[1] << ' ' << availableGames[2] << std::endl;
}

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

    const char* sql1 = "SELECT firstname, secondname, coins, availablegames FROM clients WHERE username = $1";
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

dbInteraction::transactionRequst& ViktorDev::TransactionHandlerClient::getRequestMessage()
{
    return requestMessage;
}

dbInteraction::transactionAnswer& ViktorDev::TransactionHandlerClient::getAnswerMessage()
{
    return answerMessage;
}
ViktorDev::TransactionHandlerClient::TransactionHandlerClient(std::string filePath, dbInteraction::transactionRequst message)
{
    this->filePath = filePath;
    this->requestMessage = message;
}
int ViktorDev::TransactionHandlerClient::sendIt()
{
    out.open(filePath, std::ios_base::binary);
    if (!out) {
        std::cout << "FILE DOES NOT OPENED!" << std::endl;
        assert(ViktorDev::errorWithFile);
        exit(ViktorDev::errorWithFile);
    }
    if (!requestMessage.SerializePartialToOstream(&out)) {
        std::cout << "ERRORSEND IT !" << std::endl;
        return ViktorDev::errorSerializeMessage;
    };
    out.close();
    return ViktorDev::success;
}
int ViktorDev::TransactionHandlerClient::receiveIt()
{
    in.open(filePath, std::ios_base::binary);
    if (!in) {
        assert(errorWithFile);
        in.close();
        exit(errorWithFile);
    };
    if (!answerMessage.ParseFromIstream(&in)) {
        return ViktorDev::errorParseMessage;
    };
    if (answerMessage.transactionstatus() == 0) {
        result = ViktorDev::TransactionResult::SUCCESS;
    } else {
        if (answerMessage.transactionstatus() == 1) {
            result = ViktorDev::TransactionResult::NOT_ENOUGH_COINS;
        } else {
            result = ViktorDev::TransactionResult::ALREADY_PURCHASED;
        }
    }
    in.close();
    return ViktorDev::success;
}

void ViktorDev::TransactionHandlerClient::printRequestMessage()
{
    std::cout << "productID = " << getRequestMessage().productid() << std::endl;
    std::cout << "username = " << getRequestMessage().username() << std::endl;
}
void ViktorDev::TransactionHandlerClient::printAnswerMessage()
{
    std::cout << "transactionStatus = " << getAnswerMessage().transactionstatus() << std::endl;
    std::cout << "currentCoins = " << getAnswerMessage().coins() << std::endl;
    for (int i = 0; i < gameQuanity; ++i) {
        std::cout << "gameAccess " << i << " = " << getAnswerMessage().gameaccess()[i] << std::endl;
    }
}

ViktorDev::TransactionHandlerServer::TransactionHandlerServer(dbInteraction::transactionAnswer message) {
    answerMessage = message;
}


void ViktorDev::TransactionHandlerServer::printTransaction()
{
    std::cout << std::endl
              << "coins = " << coins << std::endl
              << "availableGames = " << availableGames[0] << ' ' << availableGames[1] << ' ' << availableGames[2] << std::endl;
}

void ViktorDev::TransactionHandlerServer::parseRequestTransaction(PGresult* res)
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

dbInteraction::transactionRequst& ViktorDev::TransactionHandlerServer::getRequestMessage(){
    return requestMessage;
}
dbInteraction::transactionAnswer& ViktorDev::TransactionHandlerServer::getAnswerMessage(){
    return answerMessage;
}
void ViktorDev::TransactionHandlerServer::requestTransactionPeek()
{
    const char* conninfo = connectionInfo;
    PGconn* conn = PQconnectdb(conninfo);
    setConnection(&conn);

    const char* sql1 = "SELECT coins, availablegames FROM clients WHERE username = $1";
    const char* sql1param = getRequestMessage().username().c_str();
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
}

void ViktorDev::TransactionHandlerServer::doTransaction()
{   
    int prices [gameQuanity] {firstGamePrice, secondGamePrice, thirdGamePrice};
    if(coins < prices[getRequestMessage().productid()]){
        resultCode = 1;
        return;
    }
    if(availableGames[getRequestMessage().productid()] ==1){
        resultCode = 2;
        return;
    }

    const char* conninfo = connectionInfo;
    PGconn* conn = PQconnectdb(conninfo);
    setConnection(&conn);

    const char* sql1 = "UPDATE clients SET coins = $1 WHERE username = $2";
    const char* sql1param = getRequestMessage().username().c_str();
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
}

void ViktorDev::TransactionHandlerServer::sendToClient(){    
    out.open(filePath, std::ios_base::binary);
    if (!out) {
        std::cout << "FILE DOES NOT OPENED!" << std::endl;
        assert(ViktorDev::errorWithFile);
        exit(ViktorDev::errorWithFile);
    }
    if (!answerMessage.SerializePartialToOstream(&out)) {
        std::cout << "ERRORSEND IT !" << std::endl;
    };
    out.close();
}

dbInteraction::authInformation& ViktorDev::ClientAuthorizationHandler::getMessage()
{
    return message;
}

dbInteraction::registrationInfo& ViktorDev::ClientAuthorizationHandler::getmessageRegistration()
{
    return messageRegistration;
}

ViktorDev::ClientAuthorizationHandler::ClientAuthorizationHandler(std::string filePath, dbInteraction::authInformation message)
{
    this->filePath = filePath;
    this->getMessage() = message;
}
int ViktorDev::ClientAuthorizationHandler::sendIt()
{
    out.open(filePath, std::ios_base::binary);
    if (!out) {
        std::cout << "FILE DOES NOT OPENED!" << std::endl;
        assert(ViktorDev::errorWithFile);
        exit(ViktorDev::errorWithFile);
    }
    if (!message.SerializePartialToOstream(&out)) {
        std::cout << "ERRORSEND IT !" << std::endl;
        return ViktorDev::errorSerializeMessage;
    };
    out.close();
    return ViktorDev::success;
}

void ViktorDev::ClientAuthorizationHandler::printMessage()
{
    std::cout << "username = " << getMessage().username() << std::endl;
    std::cout << "password = " << getMessage().password() << std::endl;
}

dbInteraction::authInformation& ViktorDev::ServerAuthorizationHandler::getMessage()
{
    return message;
}
dbInteraction::registrationInfo& ViktorDev::ServerAuthorizationHandler::getmessageRegistration()
{
    return messageRegistration;
}

void ViktorDev::ClientAuthorizationHandler::printMessageRegistration(){
    std::cout << std::endl<< "Received message registration:"<< std::endl;
    std::cout << "email = " << getmessageRegistration().email() << std::endl;
    std::cout << "username = " << getmessageRegistration().username() << std::endl;
    std::cout << "password = " << getmessageRegistration().password() << std::endl;
    std::cout << "country = " << getmessageRegistration().country() << std::endl;
    std::cout << "firstName = " << getmessageRegistration().firstname() << std::endl;
    std::cout << "secondName = " << getmessageRegistration().secondname() << std::endl;
}

int ViktorDev::ClientAuthorizationHandler::receiveUserInfo(){
    in.open(filePath, std::ios_base::binary);
    if (!in) {
        assert(errorWithFile);
        in.close();
        exit(errorWithFile);
    };
    if (!messageRegistration.ParseFromIstream(&in)) {
        return ViktorDev::errorParseMessage;
    };
    in.close();
    return ViktorDev::success;
}

int ViktorDev::ClientAuthorizationHandler::receiveIt()
{
    in.open(filePath, std::ios_base::binary);
    if (!in) {
        assert(errorWithFile);
        in.close();
        exit(errorWithFile);
    };
    if (!answerMessage.ParseFromIstream(&in)) {
        return ViktorDev::errorParseMessage;
    };
    if (answerMessage.authorizationstatus() == 0) {
        result = ViktorDev::AuthorizationResult::SUCCESS;

    } else {
        if (answerMessage.authorizationstatus() == 1) {
            result = ViktorDev::AuthorizationResult::WRONG_USERNAME;
        } else {
            result = ViktorDev::AuthorizationResult::WRONG_PASSWORD;
        }
    }
    in.close();
    return ViktorDev::success;
}

void ViktorDev::ClientAuthorizationHandler::printResult()
{
    if (result == ViktorDev::AuthorizationResult::SUCCESS) {
        std::cout << "Authorization: success" << std::endl;
    } else {
        if (result == ViktorDev::AuthorizationResult::WRONG_USERNAME) {
            std::cout << "Authorization: wrong username" << std::endl;
        } else {
            std::cout << "Authorization: wrong password" << std::endl;
        }
    }
}

ViktorDev::ServerAuthorizationHandler::ServerAuthorizationHandler(std::string filePath, dbInteraction::authInformation message)
{
    this->filePath = filePath;
    this->message = message;
    in.open(filePath, std::ios_base::binary);
    if (!in) {
        std::cout << "errorWithFile in ServerAuthorizationHandler constructor";
        assert(ViktorDev::errorWithFile);
        in.close();
        exit(ViktorDev::errorWithFile);
    };
}

int ViktorDev::ServerAuthorizationHandler::receiveIt()
{
    if (!message.ParseFromIstream(&in)) {
        return ViktorDev::errorParseMessage;
    };
    return ViktorDev::success;
}

void ViktorDev::ServerAuthorizationHandler::printMessage()
{
    std::cout << "username = " << getMessage().username() << std::endl;
    std::cout << "password = " << getMessage().password() << std::endl;
}

void ViktorDev::ServerAuthorizationHandler::printMessageRegistration(){
    std::cout << std::endl<< "Send message registration:"<< std::endl;
    std::cout << "email = " << getmessageRegistration().email() << std::endl;
    std::cout << "username = " << getmessageRegistration().username() << std::endl;
    std::cout << "password = " << getmessageRegistration().password() << std::endl;
    std::cout << "country = " << getmessageRegistration().country() << std::endl;
    std::cout << "firstName = " << getmessageRegistration().firstname() << std::endl;
    std::cout << "secondName = " << getmessageRegistration().secondname() << std::endl;
}

void ViktorDev::ServerAuthorizationHandler::parseRequestCheck(PGresult* res)
{
    int nTuples = PQntuples(res);
    fprintf(stdout, "Tuples count: %i\n", nTuples);
    int nFields = PQnfields(res);
    fprintf(stdout, "Fields count: %i\n", nFields);

    std::string passwordDB;
    passwordDB.assign(PQgetvalue(res, 0, 2), PQgetlength(res, 0, 2));
    std::cout << "passwordDB = " << passwordDB << std::endl;

    if (passwordDB == "") {
        checkingResult = ViktorDev::AuthorizationResult::WRONG_USERNAME;
    } else {
        if (passwordDB == getMessage().password()) {
            checkingResult = ViktorDev::AuthorizationResult::SUCCESS;

            std::string emailDB;
            emailDB.assign(PQgetvalue(res, 0, 0), PQgetlength(res, 0, 0));
            getmessageRegistration().set_email(emailDB);

            std::string usernameDB;
            usernameDB.assign(PQgetvalue(res, 0, 1), PQgetlength(res, 0, 1));
            getmessageRegistration().set_username(usernameDB);

            getmessageRegistration().set_password(passwordDB);

            std::string countryDB;
            countryDB.assign(PQgetvalue(res, 0, 3), PQgetlength(res, 0, 3));
            getmessageRegistration().set_country(countryDB);

            std::string firstnameDB;
            firstnameDB.assign(PQgetvalue(res, 0, 4), PQgetlength(res, 0, 4));
            getmessageRegistration().set_firstname(firstnameDB);

            std::string secondnameDB;
            secondnameDB.assign(PQgetvalue(res, 0, 5), PQgetlength(res, 0, 5));
            getmessageRegistration().set_secondname(secondnameDB);

            getmessageRegistration().set_coins(0);
            for(int i = 0; i <gameQuanity; ++i){
                getmessageRegistration().add_availablegames(0);
            }
            getmessageRegistration().set_fps(60);
            

        } else {
            checkingResult = ViktorDev::AuthorizationResult::WRONG_PASSWORD;
        }
    }
}

void ViktorDev::ServerAuthorizationHandler::check()
{
    const char* conninfo = connectionInfo;
    PGconn* conn = PQconnectdb(conninfo);
    setConnection(&conn);

    const char* sql1 = "SELECT email, username, password, country, firstname, secondname, coins, availablegames, id, fps FROM clients WHERE username = $1";
    const char* sql1param = getMessage().username().c_str();
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
    parseRequestCheck(res);

    PQclear(res);
    PQfinish(conn);
}

int ViktorDev::ServerAuthorizationHandler::sendIt()
{
    dbInteraction::serverAuthInformation answerMessage;
    answerMessage.set_userinfo(555);
    answerMessage.set_serverinfo(777);
    if (checkingResult == ViktorDev::AuthorizationResult::SUCCESS) {
        answerMessage.set_authorizationstatus(0);
    } else {
        if (checkingResult == ViktorDev::AuthorizationResult::WRONG_USERNAME) {
            answerMessage.set_authorizationstatus(1);
        } else {
            answerMessage.set_authorizationstatus(2);
        }
    }
    out.open(filePath, std::ios_base::binary);
    if (!out) {
        std::cout << "FILE DOES NOT OPENED!" << std::endl;
        assert(ViktorDev::errorWithFile);
        exit(ViktorDev::errorWithFile);
    }
    if (!answerMessage.SerializePartialToOstream(&out)) {
        std::cout << "ERRORSEND IT !" << std::endl;
        return ViktorDev::errorSerializeMessage;
    };
    out.close();
    return ViktorDev::success;
}

int ViktorDev::ServerAuthorizationHandler::sendUserInfo()
{
    
    out.open(filePath, std::ios_base::binary);
    if (!out) {
        std::cout << "FILE DOES NOT OPENED!" << std::endl;
        assert(ViktorDev::errorWithFile);
        exit(ViktorDev::errorWithFile);
    }
    if (!messageRegistration.SerializePartialToOstream(&out)) {
        std::cout << "ERROR send user info  !" << std::endl;
        return ViktorDev::errorSerializeMessage;
    };
    printMessageRegistration();
    out.close();
    return ViktorDev::success;
}

void ViktorDev::ServerAuthorizationHandler::printResult()
{
    if (checkingResult == ViktorDev::AuthorizationResult::SUCCESS) {
        std::cout << "Authorization: success" << std::endl;
    } else {
        if (checkingResult == ViktorDev::AuthorizationResult::WRONG_USERNAME) {
            std::cout << "Authorization: wrong username" << std::endl;
        } else {
            std::cout << "Authorization: wrong password" << std::endl;
        }
    }
}

ViktorDev::ClientRegOrLog::ClientRegOrLog(std::string filePath, dbInteraction::registrationOrLogIn message)
{
    this->message.set_regorlog(message.regorlog());
    this->filePath = filePath;
}

void ViktorDev::printRegOrLogMessage(dbInteraction::registrationOrLogIn message)
{
    if (message.regorlog() == 0) {
        std::cout << "Registration" << std::endl;
    } else {
        std::cout << "Log in" << std::endl;
    }
}

int ViktorDev::ClientRegOrLog::sendIt()
{
    out.open(filePath, std::ios_base::binary);
    if (!out) {
        std::cout << "FILE DOES NOT OPENED!" << std::endl;
        assert(ViktorDev::errorWithFile);
        exit(ViktorDev::errorWithFile);
    }
    if (!message.SerializePartialToOstream(&out)) {
        std::cout << "ERRORSEND IT !" << std::endl;
        return ViktorDev::errorSerializeMessage;
    };
    out.close();
    printRegOrLogMessage(message);
    return ViktorDev::success;
}

ViktorDev::ServerRegOrLog::ServerRegOrLog(std::string filePath)
{
    this->filePath = filePath;
}
int ViktorDev::ServerRegOrLog::receiveIt()
{
    in.open(filePath, std::ios_base::binary);
    if (!in) {
        assert(errorWithFile);
        in.close();
        exit(errorWithFile);
    };
    if (!message.ParseFromIstream(&in)) {
        return ViktorDev::errorParseMessage;
    };
    if (message.regorlog() == 0) {
        status = false;
    } else {
        status = true;
    }
    in.close();
    printRegOrLogMessage(message);
    return ViktorDev::success;
}

// REFGISTRATION CLIENT PART

dbInteraction::registrationInfo& ViktorDev::ClientRegistrationHandler::getMessage()
{
    return message;
}
ViktorDev::ClientRegistrationHandler::ClientRegistrationHandler(std::string filePath, dbInteraction::registrationInfo message)
{
    this->filePath = filePath;
    this->getMessage() = message;
}
int ViktorDev::ClientRegistrationHandler::sendIt()
{
    out.open(filePath, std::ios_base::binary);
    if (!out) {
        std::cout << "FILE DOES NOT OPENED!" << std::endl;
        assert(ViktorDev::errorWithFile);
        exit(ViktorDev::errorWithFile);
    }
    if (!message.SerializePartialToOstream(&out)) {
        std::cout << "ERRORSEND IT !" << std::endl;
        return ViktorDev::errorSerializeMessage;
    };
    out.close();
    return ViktorDev::success;
}

void ViktorDev::ClientRegistrationHandler::printMessage()
{
    std::cout << "email = " << getMessage().email() << std::endl;
    std::cout << "username = " << getMessage().username() << std::endl;
    std::cout << "password = " << getMessage().password() << std::endl;
    std::cout << "country = " << getMessage().country() << std::endl;
    std::cout << "firstName = " << getMessage().firstname() << std::endl;
    std::cout << "secondName = " << getMessage().secondname() << std::endl;
    std::cout << "coins = " << getMessage().coins() << std::endl;
    std::cout << "availableGames = ";
    for (int i = 0; i < ViktorDev::gameQuanity; ++i) {
        std::cout << getMessage().availablegames()[i] << ' ';
    }
    std::cout << std::endl;
    std::cout << "age = " << getMessage().age() << std::endl;
    std::cout << "FPS = " << getMessage().fps() << std::endl;
}

int ViktorDev::ClientRegistrationHandler::receiveIt()
{
    in.open(filePath, std::ios_base::binary);
    if (!in) {
        assert(errorWithFile);
        in.close();
        exit(errorWithFile);
    };
    if (!answerMessage.ParseFromIstream(&in)) {
        return ViktorDev::errorParseMessage;
    };
    if (answerMessage.authorizationstatus() == 0) {
        result = ViktorDev::RegistrationResult::SUCCESS;
        std::cout << "Registration result = success" << std::endl;
    } else {
        result = ViktorDev::RegistrationResult::DUPLICATED_INFO;
        std::cout << "Registration result = duplicated info" << std::endl;
    }
    in.close();
    return ViktorDev::success;
}

void ViktorDev::ClientRegistrationHandler::printResult()
{
    if (result == ViktorDev::RegistrationResult::SUCCESS) {
        std::cout << "Registration result = success" << std::endl;
    } else {
        if (result == ViktorDev::RegistrationResult::DUPLICATED_INFO) {
            std::cout << "Registration result = duplicated info" << std::endl;
        }
    }
}

// REGISTRATION SERVER PART

ViktorDev::ServerRegistrationHandler::ServerRegistrationHandler(std::string filePath, dbInteraction::registrationInfo message)
{
    this->filePath = filePath;
    this->message = message;
}

int ViktorDev::ServerRegistrationHandler::receiveIt()
{
    in.open(filePath, std::ios_base::binary);
    if (!in) {
        std::cout << "errorWithFile in ServerAuthorizationHandler constructor";
        assert(ViktorDev::errorWithFile);
        in.close();
        exit(ViktorDev::errorWithFile);
    };
    if (!message.ParseFromIstream(&in)) {
        return ViktorDev::errorParseMessage;
    };
    in.close();
    return ViktorDev::success;
}
dbInteraction::registrationInfo& ViktorDev::ServerRegistrationHandler::getMessage()
{
    return message;
}
void ViktorDev::ServerRegistrationHandler::printMessage()
{
    std::cout << "email = " << getMessage().email() << std::endl;
    std::cout << "username = " << getMessage().username() << std::endl;
    std::cout << "password = " << getMessage().password() << std::endl;
    std::cout << "country = " << getMessage().country() << std::endl;
    std::cout << "firstName = " << getMessage().firstname() << std::endl;
    std::cout << "secondName = " << getMessage().secondname() << std::endl;
    std::cout << "coins = " << getMessage().coins() << std::endl;
    std::cout << "availableGames = ";
    for (int i = 0; i < ViktorDev::gameQuanity; ++i) {
        std::cout << getMessage().availablegames()[i] << ' ';
    }
    std::cout << std::endl;
    std::cout << "age = " << getMessage().age() << std::endl;
    std::cout << "FPS = " << getMessage().fps() << std::endl;
}

void ViktorDev::ServerRegistrationHandler::updateInt(dbInteraction::registrationInfo addMessage)
{
    (void)addMessage;
    const char* conninfo = connectionInfo;
    PGconn* conn = PQconnectdb(conninfo);
    setConnection(&conn);
    const int paramsQuanity = 0;
    const char* sql1 = "UPDATE clients SET coins = 0, age  = 20";
    PGresult* res = PQexecParams(conn, sql1, paramsQuanity, NULL, NULL, NULL, NULL, 3); //0 - text, 1 - bin
    ExecStatusType resStatus = PQresultStatus(res);

    char* resStatusStr = PQresStatus(resStatus);
    fprintf(stdout, "Query Result Status: %s\n", resStatusStr);

    PQclear(res);
    PQfinish(conn);
}
void ViktorDev::ServerRegistrationHandler::parseRequestCheck(PGresult* res)
{
    int nTuples = PQntuples(res);
    fprintf(stdout, "Tuples count: %i\n", nTuples);
    int nFields = PQnfields(res);
    fprintf(stdout, "Fields count: %i\n", nFields);

    std::string passwordDB;
    passwordDB.assign(PQgetvalue(res, 0, 0), PQgetlength(res, 0, 0));
    std::cout << "passwordDB = " << passwordDB << std::endl;

    if (passwordDB == "") {
        checkingResult = ViktorDev::RegistrationResult::SUCCESS;
    } else {
        checkingResult = ViktorDev::RegistrationResult::DUPLICATED_INFO;
    }
}
void ViktorDev::ServerRegistrationHandler::addRecord(dbInteraction::registrationInfo addMessage)
{
    const char* conninfo = connectionInfo;
    PGconn* conn = PQconnectdb(conninfo);
    setConnection(&conn);
    const int paramsQuanity = 6;
    const char* sql1 = "INSERT INTO clients (Email, Username, Password, FirstName, SecondName, availablegames) VALUES ($1, $2, $3, $4, $5, $6)";
    const char* AvailableGames = "{f,f,f}";
    const char* sql1param[paramsQuanity] { addMessage.email().c_str(), addMessage.username().c_str(), addMessage.password().c_str(), addMessage.firstname().c_str(), addMessage.secondname().c_str(), AvailableGames }; 
    PGresult* res = PQexecParams(conn, sql1, paramsQuanity, NULL, sql1param, NULL, NULL, 1); //0 - text, 1 - bin
    ExecStatusType resStatus = PQresultStatus(res);
    char* resStatusStr = PQresStatus(resStatus);
    fprintf(stdout, "Query Result Status: %s\n", resStatusStr);

    PQclear(res);
    PQfinish(conn);
    updateInt(addMessage);
}
void ViktorDev::ServerRegistrationHandler::check()
{
    const char* conninfo = connectionInfo;
    PGconn* conn = PQconnectdb(conninfo);
    setConnection(&conn);

    const char* sql1 = "SELECT password FROM clients WHERE email = $1 or username = $2";
    const char* sql1param[2] { getMessage().email().c_str(), getMessage().username().c_str() }; 
    PGresult* res = PQexecParams(conn, sql1, 2, NULL, sql1param, NULL, NULL, 0);
    ExecStatusType resStatus = PQresultStatus(res);
    if (resStatus != PGRES_TUPLES_OK) {
        fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
    char* resStatusStr = PQresStatus(resStatus);
    fprintf(stdout, "Query Result Status: %s\n", resStatusStr);
    parseRequestCheck(res);
    if (checkingResult == ViktorDev::RegistrationResult::SUCCESS) {
        addRecord(getMessage());
    }

    PQclear(res);
    PQfinish(conn);
}

int ViktorDev::ServerRegistrationHandler::sendIt()
{
    dbInteraction::serverRegInformation answerMessage;
    if (checkingResult == ViktorDev::RegistrationResult::SUCCESS) {
        answerMessage.set_authorizationstatus(0);
    } else {
        if (checkingResult == ViktorDev::RegistrationResult::DUPLICATED_INFO) {
            answerMessage.set_authorizationstatus(1);
        }
    }
    out.open(filePath, std::ios_base::binary);
    if (!out) {
        std::cout << "FILE DOES NOT OPENED!" << std::endl;
        assert(ViktorDev::errorWithFile);
        exit(ViktorDev::errorWithFile);
    }
    if (!answerMessage.SerializePartialToOstream(&out)) {
        std::cout << "ERRORSEND IT !" << std::endl;
        return ViktorDev::errorSerializeMessage;
    };
    out.close();
    return ViktorDev::success;
}

void ViktorDev::ServerRegistrationHandler::printResult()
{
    if (checkingResult == ViktorDev::RegistrationResult::SUCCESS) {
        std::cout << "Registration: success" << std::endl;
    } else {
        if (checkingResult == ViktorDev::RegistrationResult::DUPLICATED_INFO) {
            std::cout << "Registration: duplicated information" << std::endl;
        }
    }
}