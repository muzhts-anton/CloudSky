#include<iostream>
#include "postgresql/libpq-fe.h"


/*

*/
int main(int argc, char *argv[]){
    const char *conninfo;
    PGconn * conn;
    // step 1 : setup to setting connect string, default : dbname=postgres
    conninfo = "dbname = postgres";

    // step 2 : Make a connection to the database
    conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK){
        printf("Connection to database failed %s", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    std::cout<< "HostPort : " << PQport(conn)<<std::endl;
    std::cout<< "ServPath : " << PQhost(conn)<<std::endl;
    std::cout<< "DataBase : " << PQdb(conn)<<std::endl;
    std::cout<< "Login ID : " << PQuser(conn)<<std::endl;
    std::cout<< "Proc PID : " << PQbackendPID(conn)<<std::endl;
    
    int ver = PQserverVersion((const PGconn *)conn);
    int verMajor = int(ver/10000);
    int verMinor = (ver/10000);
    std::cout << "Version : " << verMajor << "." << verMinor<<std::endl;

    // close the connection to db and cleanup
    PQfinish(conn);
    return 0;
}