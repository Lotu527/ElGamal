#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800,600);
    //生成密匙
    connect(ui->pb_key_produce,SIGNAL(clicked()),this,SLOT(pb_key_produce()));
    //导出密匙
    connect(ui->pb_key_export,SIGNAL(clicked()),this,SLOT(pb_key_export()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pb_key_produce()
{
    this->key = new Key(32);
    ui->log->appendPlainText("公钥:");
    ui->log->appendPlainText(this->key->getPub().c_str());
    ui->log->appendPlainText("私钥:");
    ui->log->appendPlainText(this->key->getPriv().c_str());
}

void MainWindow::pb_key_export()
{
    if(this->key){
        ui->log->appendPlainText("\n已导出文件:");
        this->key->getPriv().
    }else{
        ui->log->appendPlainText(QString("\n还未生成有效密匙，请点击按钮:") + ui->pb_key_produce->text());
    }
}

