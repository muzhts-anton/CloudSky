#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
//#include <arrray>
#include "postgresql/libpq-fe.h"


int main(int argc, char *argv[]){
    const char *conninfo;
    PGconn * conn;
    PGresult *res;
    std::array<int,5> wCol = {4,15,1,8,12};

    // step 1 : setup to setting connect string, default : dbname=postgres
    conninfo = "dbname = postgres";

    // step 2 : Make a connection to the database
    conn = PQconnectdb(conninfo);
    if (PQstatus(conn) == CONNECTION_BAD){
        printf("Connection to database failed %s", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    // Start a transaction block
    res = PQexec(conn, "BEGIN");
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        printf("BEGIN command failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    // Do PQclear
    PQclear(res);

    // Declare quary CURSOR of databases
    //res = PQexec(conn,"DECLARE myCURSOR CURSOR FOR select id,name,membership, gender, level from player");
    res = PQexec(conn,"DECLARE myCURSOR CURSOR FOR select level from player where name = 'Tom Ricci'");
    if (PQresultStatus(res) != PGRES_COMMAND_OK){
        printf("DECLARE CURSOR failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
    PQclear(res);

    //Fetch quaring of CURSOR
    res = PQexec(conn, "FETCH ALL in myCURSOR");
    if (PQresultStatus(res)!= PGRES_TUPLES_OK){
        printf("FETCH ALL failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    //first, get total rows and total columns each row
    int totCols = PQnfields(res);
    int totRows = PQntuples(res);

    // first? print out the column header names
    std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
    std::cout<<"|";
    for(int j =0; j < totCols; ++j){
        std::cout<<std::setfill(' ')<<std::setw(wCol[j])<< std::left<< PQfname(res,j)<<"|";
    }
    std::cout<<std::endl;
    std::cout<<"--------------------------------------------------------------------------------"<<std::endl;

    // next, print out the retrieved value of rows
    for (int i = 0; i <totRows; ++i){
        std::cout<<"|";
        for(int j = 0; j < totCols; ++j){
            std::cout<< std::setfill(' ')<< std::setw(wCol[i])<< std::left << PQgetvalue(res,i,j)<< "|";
        }
        std::cout<<std::endl;
    }

    std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
    std::cout<< "Total Rows Retrieved : "<<totRows << " ";
    std::cout<< "Total columns of Row : "<<totCols << std::endl;

    PQclear(res);

    // close the portal
    res = PQexec(conn, "CLOSE myCURSOR");
    PQclear(res);

    // end the transaction
    res = PQexec(conn,"END");
    PQclear(res);

    //Close the conndection
    PQfinish(conn);

    return 0;
}