#include "mainwindow.h"
#include "des.h"
#include "./ui_mainwindow.h"

#include <QString>
#include <QFileDialog>
#include <QDebug>

#include <string>
#include <fstream>

/*
 * TODO: Scritte fatte bene
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->cryptButton, &QPushButton::released, this, &MainWindow::encrypt);
    connect(ui->saveFile, &QPushButton::released, this, &MainWindow::saveToFile);
    connect(ui->fileReadButton, &QPushButton::released, this, &MainWindow::readFromFile);
    connect(ui->swapButton, &QPushButton::released, this, &MainWindow::swapTextBoxes);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::encrypt()
{
    //Wrapper per la funzione DES() di des.h
    std::string _message = ui->userMessageBox->toPlainText().toStdString();
    std::string _finalResult = DES(_message, ui->invertCheckBox->isChecked());
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

void MainWindow::readFromFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Save File"),
                               "",
                               tr("Text File (*.txt)"));
    std::string tempLine;
    std::string fullLine;
    fstream fileStream (fileName.toStdString(), ios::in);
    while(getline(fileStream, tempLine))
    {
        fullLine+=tempLine+"\n";
    }
    ui->userMessageBox->setText(QString::fromStdString(fullLine));
}
void MainWindow::swapTextBoxes()
{
    ui->userMessageBox->setText(ui->convertedLabel->toPlainText());
}

