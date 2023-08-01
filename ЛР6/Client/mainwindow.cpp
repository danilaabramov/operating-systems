#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _socket;
    delete file;
}


void MainWindow::on_pushButton_clicked()
{
    if(0 < ui->textEdit->document()->toPlainText().toInt() && 0 < ui->textEdit_2->document()->toPlainText().toInt()){
        qDebug() << "Данные введены корректно";
        qDebug() << "Количество пчёл: " << ui->textEdit->document()->toPlainText();
        qDebug() << "Количество глотков горшке: " << ui->textEdit_2->document()->toPlainText();
        if (file->open(QIODevice::Append)) {
            file->write("Данные введены корректно\n");
            file->write(("Количество пчёл: " + ui->textEdit->document()->toPlainText() + "\n").toUtf8());
            file->write(("Количество глотков горшке: " + ui->textEdit_2->document()->toPlainText() + "\n").toUtf8());
            file->close();
        }
    }
    else {
        qDebug() <<  "Данные введены некорректно";
        if (file->open(QIODevice::Append)) file->write("Данные введены некорректно\n");
        file->close();
    }

    ba = (ui->textEdit->document()->toPlainText() + " " + ui->textEdit_2->document()->toPlainText()).toUtf8();
    _socket->write(ba);
}
