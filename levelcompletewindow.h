/*
 * Author: equati0n
 * Date: December 2016
*/

#ifndef LEVELCOMPLETEWINDOW_H
#define LEVELCOMPLETEWINDOW_H

#include <QDialog>

namespace Ui {
class LevelCompleteWindow;
}

class LevelCompleteWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LevelCompleteWindow(QWidget *parent = 0);
    ~LevelCompleteWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::LevelCompleteWindow *ui;
};

#endif // LEVELCOMPLETEWINDOW_H
