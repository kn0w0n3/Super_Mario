/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

/*
 * Author: equati0n
 * Date: December 2016
*/

#include <QDialog>
#include "database.h"
#include <QSql>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog{
    Q_OBJECT
private:
    Connection DBase;

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    void connectDatabase();
    bool regExUsernameTest();
    bool regExPasswordTest();
    Connection createConnection();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_radioButton_clicked(bool checked);

private:
    Ui::LoginWindow *ui;
    QRegularExpression *userRegEx;
    QRegularExpressionMatch *userMatch;
    QRegularExpression *passRegEx;
    QRegularExpressionMatch *passMatch;

};

#endif // LOGINWINDOW_H
