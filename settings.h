/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef SETTINGS_H
#define SETTINGS_H
#include "mainwindow.h"

class Settings : public QDialog{
    Q_OBJECT
public:
    Settings( QWidget *parent = 0);
    void reject();
    void setState();
    void revertState();
    void alterState();
    void readSettings();
    void writeSettings();

signals:
    void fullScreen(bool);
    void bgmAdjust(int);
    void sfxAdjust(int);

private slots:
    void bgmChanged();
    void sfxChanged();
    void confirm();

private:
    bool full;
    bool window;
    int bgm;
    int sfx;
    QLabel *label;
    QLabel *bgmLabel;
    QLabel *sfxLabel;
    QLabel *screenSize;
    QLineEdit *lineEdit;
    QSlider *bgmSlider;
    QSlider *sfxSlider;
    QSpinBox *bgmSpinBox;
    QSpinBox *sfxSpinBox;
    QPushButton *confirmButton;
    QPushButton *cancelButton;
    QRadioButton *windowedView;
    QRadioButton *fullScreenView;
};
#endif // SETTINGS_H
