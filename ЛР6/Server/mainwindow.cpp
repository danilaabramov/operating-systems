#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete file;
}

void MainWindow::on_pushButton_clicked()
{
    if(flag) close();
    else {
        if (file->open(QIODevice::Append)) {file->write("Данные от клиента не получины\n");file->close();}
        ui->listWidget->addItem("Данные от клиента не получины");
    }
}
