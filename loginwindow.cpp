/*
 * Author: equati0n
 * Date: December 2016
*/

#include "loginwindow.h"
#include "ui_loginwindow.h"

#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow(){
    delete ui;
}

//RegEx username test. Must be an email address
bool LoginWindow::regExUsernameTest(){

   bool emailAddress = false;
   userRegEx = new QRegularExpression("^([a-z0-9_\\.-]+)@([\\da-z\\.-]+)\\.([a-z\\.]{2,6})$");
   userMatch = new QRegularExpressionMatch(userRegEx->match(ui->USERNAME->text()));
   emailAddress = userMatch->hasMatch();

   if(emailAddress){
       return true;
   }
   else
   return false;
}

//Check Password using regEx. Can Contain A-Z upper or lowercase, 0-9, _underscore, and -hyphen. Max length 20.
bool LoginWindow::regExPasswordTest(){
    bool passSatisfied = false;
    passRegEx = new QRegularExpression("^[a-zA-Z0-9_-]{7,20}$");
    passMatch = new QRegularExpressionMatch(passRegEx->match(ui->PASSWORD->text()));
    passSatisfied = passMatch->hasMatch();

    if(passSatisfied){
        return true;
    }
    else
    return false;
}

//Push button to activate regex testing, connect to database and register user.
void LoginWindow::on_pushButton_clicked(){

    //Connect to Database
    //createConnection();
    DataB::DBConnect(DBase);
    //Gather Input
    Query uInput;
    uInput.uName=ui->USERNAME->text();
    uInput.pass=ui->PASSWORD->text();

    if(ui->USERNAME->text().isEmpty()){

        QMessageBox::warning(this, "Warning", "You must enter a username to register");
        return;
    }
    if(regExUsernameTest()== false){

        QMessageBox::warning(this, "Warning", "That is not a valid email address");
        return;
    }
    if(ui->PASSWORD->text().isEmpty()){

        QMessageBox::warning(this, "Warning", "You must enter a password to register");
        return;
    }
    if(regExPasswordTest()== false){

        QMessageBox::warning(this, "Warning", "Password may contain A-Z upper or lowercase, 0-9, _underscore, and -hyphen. Max length is 20. Minimum length is 7.Please try again.");
        return;
    }
    qDebug() << uInput.uName;
    qDebug() << uInput.pass;
    //Try to Register User
    if(DataB::regUsr(uInput,DBase.db)){
        QMessageBox::information(this, "Success"," Registration was successful. You may now login");
        LoginWindow::reject();
    }
    else{

        //Username Taken
        QMessageBox::warning(this, "Warning", " Username is already taken. Please try again.");
    }
}


//Close window if press cancel button
void LoginWindow::on_pushButton_2_clicked()
{
    LoginWindow::reject();
}

//Set echo mode for password with radio button
void LoginWindow::on_radioButton_clicked(bool checked){
    if(checked){
        ui->PASSWORD->setEchoMode(QLineEdit::Normal);
    }
    else{
        ui->PASSWORD->setEchoMode(QLineEdit::Password);
    }
}


