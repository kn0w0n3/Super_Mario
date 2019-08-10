//Authors: equati0n,ka0t1k,zzDeagle545zz

#ifndef DATABASE_H
#define DATABASE_H
#include <QSql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>

//Structures
struct Connection{
    QSqlDatabase db;
    bool connected;
};
//SQL Query
struct Query{
    QString uName;
    QString pass;
};

namespace DataB{

//*****************************************************************************
//*****************************************************************************
//                          SQL and Database Functions
//
//
//Registers the User if valid
bool regUsr(Query,QSqlDatabase);
//Checks to see if the username is taken
bool chkUsr(Query,QSqlDatabase);
//Checks to see if a Username and password Match in database
bool cUsrPas(Query,QSqlDatabase);
//Connects to Database
bool DBConnect(Connection);

}
#endif // DATABASE_H
