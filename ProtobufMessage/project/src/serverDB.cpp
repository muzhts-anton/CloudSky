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
    std::vector<std::pair<std::string, int>> games { { ViktorDev::firstGameName, ViktorDev::firstGamePrice },
        { ViktorDev::secondGameName, ViktorDev::secondGamePrice },
        { ViktorDev::thirdGameName, ViktorDev::thirdGamePrice } };
    ViktorDev::authorizationHandler autHandler;
    autHandler.requestAuthorization("President");
    bool wantedGames[ViktorDev::gameQuanity] { false, false, true };
    ViktorDev::transactionHandlerServer transactionHandler(wantedGames);
    transactionHandler.requestTransactionPeek("President");
    std::string filePath = "dbInformation.bin";
    std::string username = "President";
    std::string password = "mypasswordDT1";

    // Test reglog
    dbInteraction::registrationOrLogIn regOrLogMessage;
    regOrLogMessage.set_regorlog(true);
    ViktorDev::printRegOrLogMessage(regOrLogMessage);
    ViktorDev::ClientRegOrLog sender(filePath, regOrLogMessage);
    sender.sendIt();
    ViktorDev::ServerRegOrLog receiver(filePath);
    receiver.receiveIt();

    //Test authorization

    dbInteraction::clientAuthInformation message;
    message.set_username(username);
    message.set_password(password);
    ViktorDev::ClientAuthorizationHandler clientAuth(filePath, message);
    clientAuth.sendIt();
    std::cout << "sended message:" << std::endl<< std::endl;
    clientAuth.printMessage();


    dbInteraction::clientAuthInformation receivedMessage;
    ViktorDev::ServerAuthorizationHandler serverAuth(filePath, receivedMessage);
    serverAuth.receiveIt();
    std::cout << "received message:" << std::endl<< std::endl;
    serverAuth.printMessage();
    serverAuth.check();
    serverAuth.sendIt();
    serverAuth.printResult();
    clientAuth.receiveIt();
    clientAuth.printResult();

    // Test registration
    std::string email = "Masha@mail.ru";
    username = "Masha";
    password = "passwordMasha";
    std::string country = "Russia";
    std::string firstname = "Masha";
    std::string secondname = "Romanova"; // 
    int coins = 0;
    bool availableGames[3]{false,false,false};
    int age = 20;
    //id
    //FPS

    dbInteraction::registrationInfo regMessage;
    regMessage.set_email(email);
    regMessage.set_username(username);
    regMessage.set_password(password);
    regMessage.set_country(country);
    regMessage.set_firstname(firstname);
    regMessage.set_secondname(secondname);
    regMessage.set_coins(coins);
    for(int i = 0; i < ViktorDev::gameQuanity; ++i){
        regMessage.add_availablegames(availableGames[i]);
    }
    regMessage.set_age(age);
    
    std::cout<<"11111"<<std::endl;
    
    ViktorDev::ClientRegistrationHandler clientReg(filePath, regMessage);
    std::cout<<"222222222"<<std::endl;
    clientReg.sendIt();
    std::cout << "sended message:" << std::endl<< std::endl;
    clientReg.printMessage();


    dbInteraction::registrationInfo receivedRegMessage;
    ViktorDev::ServerRegistrationHandler serverReg(filePath, receivedRegMessage);
    serverReg.receiveIt();
    std::cout << "received message:" << std::endl<< std::endl;
    serverReg.printMessage();
    serverReg.check();
    serverReg.sendIt();
    serverReg.printResult();
    clientReg.receiveIt();
    clientReg.printResult();


    // dbInteraction::registrationInfo sendedRegMessage;
    // ViktorDev::ClientRegistrationHandler clientReg(filePath, sendedRegMessage);
    // clientReg.printResult();
    // clientReg.sendIt();

    // dbInteraction::registrationInfo receivedRegMessage;
    // ViktorDev::ServerRegistrationHandler serverReg(filePath, receivedRegMessage);
    // serverReg.receiveIt();
    // std::cout << "received message:" << std::endl<< std::endl;
    // serverReg.printMessage();
    // serverReg.check();
    // serverReg.sendIt();
    // serverReg.printResult();
    // clientReg.receiveIt();
    // clientReg.printResult();
}
// void showBinaryResults(PGresult *res) {
//     /* узнали кол-во записей (строк) в результатах запроса */
//     int nTuples = PQntuples(res);
//     fprintf(stdout, "Tuples count: %i\n", nTuples);
//     /* узнали кол-во полей (колонок) в результатах запроса */
//     int nFields = PQnfields(res);
//     fprintf(stdout, "Fields count: %i\n", nFields);

//     /* узнали формат результата: бинарный или текстовый?? */
//     int binaryTuples = PQbinaryTuples(res);
//     if (binaryTuples == 1)
//         fprintf(stdout, "Binary data\n");
//     else
//         fprintf(stdout, "Text data\n");

//     /* в циклах по всем строкам и столбцам */
//     for (int tuple = 0; tuple < nTuples; tuple++) {
//         fprintf(stdout, "Row#%i\n", tuple);
//         for (int field = 0; field < nFields; field++) {
//             /* узнали имя поля (колонки) */
//             char* fieldname = PQfname(res, field);
//             /* узнали указатели на значение */
//             char* value = PQgetvalue(res, tuple, field);
//             /* Узнали длину в байтах, сколько занимает значение */
//             int length = PQgetlength(res, tuple, field);
//             /* вывели значение */
//             fprintf(stdout, "\t%s = %s (%i)\n", fieldname, value, length); //for parcing int: %d   value[0] + value[1] + value[2] + value[3]
//         }
//     }
//     /* ВАЖНО!!! Данная функция не рассчитана на вывод
//        параметров отличных от строк. Их нужно разбирать
//        по типу. Например для integer будет распечатано
//        intfield= (4) */
// }

// int main() {
//     /* Устанавливаем соединение с базой данных.
//        На входе строка вида: "dbname=mydb user=myuser"
//        подробности в описании функции в документации */
//     const char * conninfo = "dbname = serverdb";
//     PGconn* conn = PQconnectdb(conninfo);
//     if (PQstatus(conn) != CONNECTION_OK) {
//         fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
//         PQfinish(conn); exit(1);
//     }

//     /* Готовим данные для выполнения запроса */
//     const char* sql1 = "SELECT firstname, secondname, coins, availablegames FROM Clients WHERE username = $1";
//     std::string username = "President";
//     const char* sql1param = username.c_str();

//     /* Запускаем запрос. Параметры по порядку:
//        1. conn - указатель соединения
//        2. sql1 - текст запроса (параметры запроса пронумерованы в текст запроса $1, $2 ....)
//        3. 1 - передаем один параметр (в тексте всего один $)
//        4. NULL - пусть сервер сам догадывается о типах данных подставляемых параметров
//        5. указатель на память, где лежат указатели на значения параметров
//            или массив, где лежат указатели на значения параметров
//        6. массив размеров значений (по указателям из №5)
//        7. массив форматов значений параметров
//            либо текстовый, тогда просто строка символов, заканчивающаяся 0, длина не нужна
//            либо бинарный, тогда длина учитывается
//        7. ожидаем результаты в двоичном виде */
//     PGresult* res = PQexecParams(conn, sql1, 1, NULL, &sql1param, NULL, NULL, 1);
//     ExecStatusType resStatus = PQresultStatus(res);
//     if (resStatus != PGRES_TUPLES_OK) {
//         fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
//         PQclear(res); PQfinish(conn); exit(1);
//     }

//     /* вывели строку статуса результата запроса */
//     char* resStatusStr = PQresStatus(resStatus);
//     fprintf(stdout, "Query Result Status: %s\n", resStatusStr);
//     /* выводим сами данные результата */
//     showBinaryResults(res);
//     PQclear(res);

//     /* Закрыли соединение */
//     PQfinish(conn);

//     return 0;
// }

// int main(int argc, char *argv[]){
//     const char *conninfo;
//     PGconn * conn;
//     PGresult *res;
//     std::array<int,5> wCol = {4,15,1,8,12};

//     std::string sUsername = "Ninja";
//     const char username[30] = "Ninja";
//     const char * pUsername = username;
//     //std::string password = "mypassword1";

//     // step 1 : setup to setting connect string, default : dbname=postgres
//     conninfo = "dbname = serverdb";

//     // step 2 : Make a connection to the database
//     conn = PQconnectdb(conninfo);
//     if (PQstatus(conn) == CONNECTION_BAD){
//         printf("Connection to database failed %s", PQerrorMessage(conn));
//         PQfinish(conn);
//         exit(1);
//     }

//     // Start a transaction block
//     res = PQexec(conn, "BEGIN");
//     if (PQresultStatus(res) != PGRES_COMMAND_OK){
//         printf("BEGIN command failed: %s", PQerrorMessage(conn));
//         PQclear(res);
//         PQfinish(conn);
//         exit(1);
//     }

//     // Do PQclear
//     PQclear(res);

//     // Declare quary CURSOR of databases
//     //res = PQexec(conn,"DECLARE myCURSOR CURSOR FOR select Email, Username, FirstName, Country from clients where id > 1");
//     std::string insert = "DECLARE myCURSOR CURSOR FOR select Password from clients where Username = " + "\""+ sUsername.c_str +"\"";
//     res = PQexec(conn,"DECLARE myCURSOR CURSOR FOR select Password from clients where Username = " + "\""+ sUsername.c_str +"\"");
//     if (PQresultStatus(res) != PGRES_COMMAND_OK){
//         printf("DECLARE CURSOR failed: %s", PQerrorMessage(conn));
//         PQclear(res);
//         PQfinish(conn);
//         exit(1);
//     }
//     PQclear(res);

//     //Fetch quaring of CURSOR
//     res = PQexec(conn, "FETCH ALL in myCURSOR");
//     if (PQresultStatus(res)!= PGRES_TUPLES_OK){
//         printf("FETCH ALL failed: %s", PQerrorMessage(conn));
//         PQclear(res);
//         PQfinish(conn);
//         exit(1);
//     }

//     //first, get total rows and total columns each row
//     int totCols = PQnfields(res);
//     int totRows = PQntuples(res);

//     // first? print out the column header names
//     std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
//     std::cout<<"|";
//     for(int j =0; j < totCols; ++j){
//         std::cout<<std::setfill(' ')<<std::setw(wCol[j])<< std::left<< PQfname(res,j)<<"|";
//     }
//     std::cout<<std::endl;
//     std::cout<<"--------------------------------------------------------------------------------"<<std::endl;

//     // next, print out the retrieved value of rows
//     for (int i = 0; i <totRows; ++i){
//         std::cout<<"|";
//         for(int j = 0; j < totCols; ++j){
//             std::cout<< std::setfill(' ')<< std::setw(wCol[i])<< std::left << PQgetvalue(res,i,j)<< "|";
//         }
//         std::cout<<std::endl;
//     }

//     std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
//     std::cout<< "Total Rows Retrieved : "<<totRows << " ";
//     std::cout<< "Total columns of Row : "<<totCols << std::endl;

//     PQclear(res);

//     // close the portal
//     res = PQexec(conn, "CLOSE myCURSOR");
//     PQclear(res);

//     // end the transaction
//     res = PQexec(conn,"END");
//     PQclear(res);

//     //Close the conndection
//     PQfinish(conn);

//     return 0;
// }