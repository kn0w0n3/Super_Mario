/*
 * Author: equati0n
 * Date: December 2016
*/

//User Libraries
#include "database.h"

namespace DataB{

//*****************************************************************************
//*****************************************************************************
//                          Register User
//Inputs
//  --> SQL Query
//Outputs
//  <-- True/false-False on failure
///////////////////////////////////////////////////////////////////////////////
bool regUsr(Query Input,QSqlDatabase db){
//Check user input against the database
    QString insert;
    QSqlQuery Q(db);
    if(chkUsr(Input,db)){
    //Define SQL Query
        insert="INSERT INTO mario_table (username,password) VALUES "
               "('"+Input.uName+"', SHA1('"+Input.pass+"'))";
        Q.exec(insert);
        db.close();
        return true;
    //Upon Failure
    }else{db.close(); return false;}
}
//*****************************************************************************
//*****************************************************************************
//                          Check Username
//Inputs
//  --> SQL Query
//Outputs
//  <-- True/false-False on failure
///////////////////////////////////////////////////////////////////////////////
bool chkUsr(Query Input,QSqlDatabase db){
    QSqlQuery Q(db);
    QString select;
//Setup a boolean
    bool valid=true;
//Define the Query
    select="SELECT username FROM mario_table WHERE username='"
            +Input.uName+"'";
    Q.exec(select);
    if(Q.size()==1){ return false; }
//Upon Success
    else{ return valid; }
}
//*****************************************************************************
//*****************************************************************************
//                          Coonects To Database
//Inputs
//  --> Connection Structure
//Outputs
//  <-- True/false-False on failure
///////////////////////////////////////////////////////////////////////////////
bool DBConnect(Connection C){
//Connect to database
    C.db = QSqlDatabase::addDatabase("QMYSQL");
    C.db.setHostName("209.129.8.7");
    C.db.setDatabaseName("48037");
    C.db.setUserName("48037");
    C.db.setPassword("48037cis17b");
//Check Connection
    if(!C.db.open()){
        C.connected=false;
        return C.connected;
    }
//Successful Connection
    C.connected=true;
    return C.connected;
}
//*****************************************************************************
//*****************************************************************************
//                          Check Username and Password
//Inputs
//  --> SQL Query
//Outputs
//  <-- True/false-False on failure
///////////////////////////////////////////////////////////////////////////////
bool cUsrPas(Query Input,QSqlDatabase db){
    QSqlQuery Q(db);
    QString select;
//Setup a boolean
    bool valid=true;
//Define the Query
    select="SELECT username FROM mario_table WHERE username='"
            +Input.uName+"' AND password=SHA1('"+Input.pass+"')";
    Q.exec(select);
//Check for a match
    if(Q.size()!=1){ return false; }
//Upon Success
    else{ return valid; }
}



}
