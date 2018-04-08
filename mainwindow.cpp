#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);
    this->key = nullptr;
    //生成密匙
    connect(ui->pb_key_produce,SIGNAL(clicked()),this,SLOT(pb_key_produce()));
    //导出密匙
    connect(ui->pb_key_export,SIGNAL(clicked()),this,SLOT(pb_key_export()));

    //解密和加密
    //导入明文文件
    connect(ui->pb_file_import,SIGNAL(clicked()),this,SLOT(pb_file_import()));
    //导入公钥文件
    connect(ui->pb_pub_key_import,SIGNAL(clicked()),this,SLOT(pb_pub_key_import()));
    //加密
    connect(ui->pb_encrypt,SIGNAL(clicked()),this,SLOT(pb_encrypt()));
    //导入密文文件
    connect(ui->pb_secret_file_import,SIGNAL(clicked()),this,SLOT(pb_secret_file_import()));
    //导入私钥文件
    connect(ui->pb_priv_key_import,SIGNAL(clicked()),this,SLOT(pb_priv_key_import()));
    //解密
    connect(ui->pb_decrypt,SIGNAL(clicked()),this,SLOT(pb_decrypt()));

    //数字签名
    //导入明文文件
    connect(ui->pb_sign_file_import,SIGNAL(clicked()),this,SLOT(pb_file_import()));
    //导入签名文件
    connect(ui->pb_signature_import,SIGNAL(clicked()),this,SLOT(pb_sign_import()));
    //生成签名
    connect(ui->pb_sign_produce,SIGNAL(clicked()),this,SLOT(pb_sign_produce()));
    //验证身份
    connect(ui->pb_check,SIGNAL(clicked()),this,SLOT(pb_sign_check()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pb_key_produce()
{
    //设置密钥长度
    this->key = new Key(32);
    ui->log->appendPlainText("公钥:");
    ui->log->appendPlainText(this->key->getPub().c_str());
    ui->log->appendPlainText("私钥:");
    ui->log->appendPlainText(this->key->getPriv().c_str());
}

void MainWindow::pb_key_export()
{
    if(this->key){
        QString dir = QFileDialog::getExistingDirectory();
        ui->log->appendPlainText("\n已选择目录:");
        ui->log->appendPlainText(dir);
        if(this->key->save(dir.toStdString()))
            ui->log->appendPlainText("导出成功：公钥-key.pub,私钥-key.priv");
        else{
            ui->log->appendPlainText("导出失败！");
        }
    }else{
        ui->log->appendPlainText(QString("\n还未生成有效密匙，请点击按钮:") + ui->pb_key_produce->text());
    }
}

void MainWindow::pb_file_import()
{
    if(this->key == nullptr){
        this->key = new Key("","");
    }
    QString filename = QFileDialog::getOpenFileName();
    if(!filename.isEmpty()){
        ui->log->appendPlainText("导入明文文件:"+filename);
        key->ReadPlaintext(filename.toStdString().c_str());
        ui->log->appendPlainText("明文内容:");
        ui->log->appendPlainText(key->getPlain().c_str());
    }else{
        ui->log->appendPlainText("未选择明文文件");
    }

}

void MainWindow::pb_encrypt()
{
    if(this->key == nullptr || this->key->getPlain().empty() || this->key->getPub().empty()){
        ui->log->appendPlainText("还未导入明文文件或公钥文件");
        return;
    }
    bigNumber* C = this->key->encrypt();
    ui->log->appendPlainText("加密完成");
    ui->log->appendPlainText("C1:");
    ui->log->appendPlainText(C[0].GetString());
    ui->log->appendPlainText("C2:");
    ui->log->appendPlainText(C[1].GetString());
}

void MainWindow::pb_decrypt()
{
    if(this->key == nullptr || this->key->getCipher().empty() || this->key->getPriv().empty()){
        ui->log->appendPlainText("还未导入密文文件或私钥文件");
        return;
    }
    std::string s = this->key->decrypt();
    ui->log->appendPlainText("解密完成");
    ui->log->appendPlainText(s.c_str());
}

void MainWindow::pb_secret_file_import()
{
    if(this->key == nullptr){
        this->key = new Key();
    }
    QString filename = QFileDialog::getOpenFileName();
    if(!filename.isEmpty()){
        ui->log->appendPlainText("导入密文文件:"+filename);
        key->ReadCiphertext(filename.toStdString().c_str());
        ui->log->appendPlainText("密文内容:");
        ui->log->appendPlainText(key->getCipher().c_str());
    }else{
        ui->log->appendPlainText("未选择密文文件");
    }

}

void MainWindow::pb_pub_key_import()
{
    ui->log->appendPlainText("未选择公钥文件");
    if(this->key==nullptr){
        this->key = new Key();
    }
    QString filename = QFileDialog::getOpenFileName();
    if(!filename.isEmpty()){
        ui->log->appendPlainText("导入公钥文件:"+filename);
        key->ReadPubKey(filename.toStdString().c_str());
        ui->log->appendPlainText("公钥内容:");
        ui->log->appendPlainText(key->getPub().c_str());
    }else{
        ui->log->appendPlainText("未选择公钥文件");
    }
}

void MainWindow::pb_priv_key_import()
{
    if(this->key == nullptr){
        this->key = new Key();
    }
    QString filename = QFileDialog::getOpenFileName();
    if(!filename.isEmpty()){
        ui->log->appendPlainText("导入私钥文件:"+filename);
        key->ReadPrivKey(filename.toStdString().c_str());
        ui->log->appendPlainText("私钥内容:");
        ui->log->appendPlainText(key->getPriv().c_str());
    }else{
        ui->log->appendPlainText("未选择私钥文件");
    }
}

void MainWindow::pb_sign_check()
{
    if(this->key == nullptr || this->key->getPlain().empty() || this->key->getSign().empty()){
        ui->log->appendPlainText("还未导入明文文件,标签文件或公钥文件");
        return;
    }
    if(this->key->Check()){
        ui->log->appendPlainText("签名验证成功!");
    }else{
        ui->log->appendPlainText("签名验证失败!");
    }
}

void MainWindow::pb_sign_produce()
{
    if(this->key == nullptr || this->key->getPlain().empty()){
        ui->log->appendPlainText("还未导入明文文件");
        return;
    }
    bigNumber* sign = this->key->SignProduce();
    ui->log->appendPlainText("签名生成:");
    ui->log->appendPlainText("R:");
    ui->log->appendPlainText(sign[0].GetString());
    ui->log->appendPlainText("S:");
    ui->log->appendPlainText(sign[1].GetString());
}

void MainWindow::pb_sign_import()
{
    if(this->key == nullptr){
        this->key = new Key();
    }
    QString filename = QFileDialog::getOpenFileName();
    if(!filename.isEmpty()){
        ui->log->appendPlainText("导入签名文件:"+filename);
        key->ReadSign(filename.toStdString().c_str());
        ui->log->appendPlainText("签名内容:");
        ui->log->appendPlainText(key->getSign().c_str());
    }else{
        ui->log->appendPlainText("未选择签名文件");
    }
}

