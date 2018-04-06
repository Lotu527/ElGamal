#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "key.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void pb_key_produce();
    void pb_key_export();
private:
    Ui::MainWindow *ui;
    Key* key;
};

#endif // MAINWINDOW_H
