#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include "textreader.h"
#include "documenthandler.h"
#include "documentanalyser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->chooseInputButton,SIGNAL(pressed()),this,SLOT(chooseInputFile()));
    connect(ui->chooseOutputButton,SIGNAL(pressed()),this,SLOT(chooseOutputFile()));

    connect(ui->action_Save,SIGNAL(triggered()),this,SLOT(chooseOutputFile()));
    connect(ui->action_Open,SIGNAL(triggered()),this,SLOT(chooseInputFile()));
    connect(ui->action_Quit,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->action_About,SIGNAL(triggered(bool)),this,SLOT(about()));

    connect(ui->inputLineEdit,SIGNAL(returnPressed()),this,SLOT(research()));
    connect(ui->outputLineEdit,SIGNAL(returnPressed()),this,SLOT(research()));

    connect(ui->checkAll,SIGNAL(toggled(bool)),SLOT(allCheck(bool)));

    connect(ui->lanchButton,SIGNAL(pressed()),this,SLOT(research()));

    ui->resultPlainText->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::chooseInputFile(void){
    QString string=QFileDialog::getOpenFileName(this,tr("Open Input File"));
    ui->inputLineEdit->setText(string);
}

void MainWindow::allCheck(bool checked){
    if(checked){
        ui->checkLetters->setEnabled(false);
        ui->checkWords->setEnabled(false);
        ui->checkLetters->setChecked(false);
        ui->checkWords->setChecked(false);
        ui->checkDouble->setEnabled(false);
        ui->checkTriple->setEnabled(false);
        ui->checkDouble->setChecked(false);
        ui->checkTriple->setChecked(false);
    }
    else{
        ui->checkDouble->setEnabled(true);
        ui->checkTriple->setEnabled(true);
        ui->checkLetters->setEnabled(true);
        ui->checkWords->setEnabled(true);
    }
}

void MainWindow::chooseOutputFile(void){
    QString string=QFileDialog::getOpenFileName(this,tr("Open Input File"), "/home/");
    ui->outputLineEdit->setText(string);
}

void MainWindow::research(){
    QString input=ui->inputLineEdit->text();
    ui->resultPlainText->insertPlainText(input);
    ui->resultPlainText->insertPlainText("\n");

    DocumentHandler text(input);
    DocumentAnalyser analyser(ui->checkOrder->isChecked(),ui->checkPie->isChecked(),ui->checkCharts->isChecked(),ui->regexLineEdit->text());

    if(ui->checkCase->isChecked()){
        analyser.analysis(text.getAll());
    }
    else{
        analyser.analysis(text.getAll().toLower());
    }

    ui->resultPlainText->clear();

    if(ui->checkAll->isChecked()){
        ui->resultPlainText->insertPlainText(analyser.getAllStatistics());
    }
    if(ui->checkLetters->isChecked()){
        ui->resultPlainText->insertPlainText(analyser.getLettersStatistics());
    }
    if(ui->checkWords->isChecked()){
        ui->resultPlainText->insertPlainText(analyser.getWordsStatistics());
    }
    if(ui->checkDouble->isChecked()){
        ui->resultPlainText->insertPlainText(analyser.getDoubleStatistics());
    }
    if(ui->checkTriple->isChecked()){
        ui->resultPlainText->insertPlainText(analyser.getTripleStatistics());
    }
    if(ui->checkRegex->isChecked()){
        ui->resultPlainText->insertPlainText(analyser.getRegexStatistics());
    }
    if(ui->checkCSV->isChecked()){
        ui->resultPlainText->insertPlainText(analyser.getCSVStatistics(text.getAll()));
    }

    if(ui->outputLineEdit->text() != ""){
        QString output=ui->outputLineEdit->text();
        QFile *outputFile = new QFile(output);
        outputFile->open(QIODevice::WriteOnly);
        QTextStream outputStream(outputFile);
        outputStream<<ui->resultPlainText->toPlainText();
        outputFile->close();
    }
}

void MainWindow::about(){
    QMessageBox *message=new QMessageBox(this);
    message->setText("This software was created by Pierre-Erik Lay for Patrick Bours\n Contact: Pierre-Erik Lay, pierre-erik.lay@orange.fr");
    message->exec();
}
