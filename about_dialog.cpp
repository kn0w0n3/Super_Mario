/*
 * Author: equati0n
 * Date: December 2016
*/

#include "about_dialog.h"
#include "ui_about_dialog.h"
#include <QDesktopWidget>
#include <QFile>

About_Dialog::About_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About_Dialog)
{
    ui->setupUi(this);

    //this->setMaximumWidth(350);
    this->setFixedSize(350,530);

    this->setWindowTitle("Mario: About");

    this->mainVBox = new QVBoxLayout;

    this->logo = new QPixmap(":/images/AD_Mario_Logo_Bar.png");
    logoLbl = new QLabel;
    logoLbl->setPixmap(*logo);
    logoLbl->setContentsMargins(0,0,0,2);

    this->spacerBar = new QPixmap(":/images/AD_Spacer_Bar.png");
    this->spacerLabel = new QLabel;
    spacerLabel->setPixmap(*spacerBar);
    spacerLabel->setContentsMargins(55,8,0,3);

    this->schoolInfo = new QLabel;
    this->classInfo = new QLabel;
    this->groupMember1 = new QLabel;
    this->groupMember2 = new QLabel;
    this->groupMember3 = new QLabel;
    this->groupMember4 = new QLabel;
    this->groupMember5 = new QLabel;
    this->groupMember6 = new QLabel;
    this->groupMember7 = new QLabel;
    this->groupMember8 = new QLabel;

    this->setLayout(mainVBox);
    mainVBox->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    mainVBox->addWidget(logoLbl);
    logoLbl->show();

    mainVBox->addWidget(schoolInfo);
    mainVBox->addWidget(classInfo);
    mainVBox->addWidget(spacerLabel);
    mainVBox->addWidget(groupMember1);
    mainVBox->addWidget(groupMember2);
    mainVBox->addWidget(groupMember3);
    mainVBox->addWidget(groupMember4);
    mainVBox->addWidget(groupMember5);
    mainVBox->addWidget(groupMember6);
    mainVBox->addWidget(groupMember7);
    mainVBox->addWidget(groupMember8);

    schoolInfo->show();
    schoolInfo->setAlignment(Qt::AlignCenter);
    schoolInfo->setText("RCC | Fall 2016");
    schoolInfo->setTextFormat(Qt::RichText);
    schoolInfo->setTextInteractionFlags(Qt::TextBrowserInteraction);
    schoolInfo->setOpenExternalLinks(true);
    schoolInfo->setContentsMargins(0,0,14,0);

    classInfo->show();
    classInfo->setAlignment(Qt::AlignCenter);
    classInfo->setText("CIS 17B | <a href = \"https://github.com/zzDeagle545zz/CSC-17B_Mario\"> Group Project </a>");
    classInfo->setTextFormat(Qt::RichText);
    classInfo->setTextInteractionFlags(Qt::TextBrowserInteraction);
    classInfo->setOpenExternalLinks(true);

    groupMember1->show();
    groupMember1->setAlignment(Qt::AlignCenter);
    groupMember1->setText("Jonathan Baird  : <a href = \"https://github.com/equati0n\"> GitHub </a> ");
    groupMember1->setTextFormat(Qt::RichText);
    groupMember1->setTextInteractionFlags(Qt::TextBrowserInteraction);
    groupMember1->setOpenExternalLinks(true);
    groupMember1->setContentsMargins(14,0,0,0);

    groupMember2->show();
    groupMember2->setAlignment(Qt::AlignCenter);
    groupMember2->setText("Jacob Aragon  : <a href = \"https://github.com/Ka0t1k\"> GitHub </a> ");
    groupMember2->setTextFormat(Qt::RichText);
    groupMember2->setTextInteractionFlags(Qt::TextBrowserInteraction);
    groupMember2->setOpenExternalLinks(true);
    groupMember2->setContentsMargins(20,0,0,0);

    groupMember3->show();
    groupMember3->setAlignment(Qt::AlignCenter);
    groupMember3->setText("Nhat Nguyen  : <a href = \"https://github.com/nn2410841\"> GitHub </a> ");
    groupMember3->setTextFormat(Qt::RichText);
    groupMember3->setTextInteractionFlags(Qt::TextBrowserInteraction);
    groupMember3->setOpenExternalLinks(true);
    groupMember3->setContentsMargins(24,0,0,0);

    groupMember4->show();
    groupMember4->setAlignment(Qt::AlignCenter);
    groupMember4->setText("Christopher Garcia  : <a href = \"https://github.com/zzDeagle545zz\"> GitHub </a> ");
    groupMember4->setTextFormat(Qt::RichText);
    groupMember4->setTextInteractionFlags(Qt::TextBrowserInteraction);
    groupMember4->setOpenExternalLinks(true);
    groupMember4->setContentsMargins(0,0,10,0); 

}

About_Dialog::~About_Dialog(){
    delete ui;
}
