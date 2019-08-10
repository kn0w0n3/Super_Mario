/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef ABOUT_DIALOG_H
#define ABOUT_DIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPixmap>
#include <QSpacerItem>
namespace Ui {
class About_Dialog;
}

class About_Dialog : public QDialog
{

    Q_OBJECT

public:
    explicit About_Dialog(QWidget *parent = 0);
    ~About_Dialog();

private:
    Ui::About_Dialog *ui;
    QVBoxLayout * mainVBox;

    QLabel * schoolInfo, * classInfo, * groupMember1,
           * groupMember2, * groupMember3, * groupMember4,
           * groupMember5, * groupMember6, * groupMember7,
           * groupMember8, * logoLbl, * spacerLabel;

    QPixmap * logo, * spacerBar;

};

#endif // ABOUT_DIALOG_H
