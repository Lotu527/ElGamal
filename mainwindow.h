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
public slots://槽函数
    void pb_key_produce();//生成密钥
    void pb_key_export();//导出密钥

    void pb_file_import();//文件导入
    void pb_encrypt();//加密明文
    void pb_decrypt();//解密密文
    void pb_secret_file_import();//密文导入
    void pb_pub_key_import();//公钥导入
    void pb_priv_key_import();//私钥导入

    void pb_sign_check();//签名检查
    void pb_sign_produce();//签名产生
    void pb_sign_import();//签名导入
private:
    Ui::MainWindow *ui;
    Key* key;
};

#endif // MAINWINDOW_H
