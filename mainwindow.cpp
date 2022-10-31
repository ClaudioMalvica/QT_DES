#include "mainwindow.h"
#include "des.h"
#include "./ui_mainwindow.h"

#include <QString>
#include <QFileDialog>
#include <QDebug>

#include <string>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->cryptButton, &QPushButton::released, this, &MainWindow::encrypt);
    connect(ui->saveFile, &QPushButton::released, this, &MainWindow::saveToFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::encrypt()
{
    //Wrapper per la funzione DES di des.h
    std::string _message = ui->userMessageBox->toPlainText().toStdString();
    std::string _finalResult = DES(_message, false);
    ui->convertedLabel->setText(QString::fromStdString(_finalResult));
}

void MainWindow::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "",
                               tr("Text File (*.txt)"));

    if(fileName.indexOf(".txt", 0, Qt::CaseInsensitive) != fileName.size()-4)
    {
        fileName.append(".txt");
    }

    std::fstream fileStream(fileName.toStdString(), ios::out);
    qDebug()<<ui->convertedLabel->toPlainText();
    fileStream<<ui->convertedLabel->toPlainText().toStdString();
    fileStream.close();

}
