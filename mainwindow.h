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

    void pb_file_import();
    void pb_encrypt();
    void pb_decrypt();
    void pb_secret_file_import();
    void pb_pub_key_import();
    void pb_priv_key_import();
private:
    Ui::MainWindow *ui;
    Key* key;
};

#endif // MAINWINDOW_H
