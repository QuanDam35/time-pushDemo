#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->Output->setText("");
    ui->progressBar->setMaximum(MAXPROGRESS);
    timer = new QTimer(this);
    runTime = 0;
    unPressTime = 0;
    ui->Time->setText(QString::number(runTime));
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    connect(ui->pushButton,SIGNAL(pressed()),this,SLOT(pushButtonPressed()));
    connect(ui->pushButton,SIGNAL(released()),this,SLOT(pushButtonReleased()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete ui;
}

void MainWindow::updateTime(){
    ui->Time->setText(QString::number(runTime++));
    if(!ui->pushButton->isDown()){
        ++unPressTime;
    }
    if(unPressTime >= MAXUNPRESSTIME){
        ui->Output->setText("NO REGISTER");
    }
}


void MainWindow::pushButtonPressed()
{
    int v;
    while(ui->pushButton->isDown()){
        unPressTime = 0;
        v = ui->progressBar->value()+1;
        ui->progressBar->setValue(v);
        QCoreApplication::processEvents();
    }
}

void MainWindow::pushButtonReleased(){
    int v = ui->progressBar->value();
    if(v <= NOREGIST){
        ui->Output->setText("NO REGISTER");
    }else if(v <= GOODTOGO){
        ui->Output->setText("PUSH HARDER");
    }else{
        ui->Output->setText("GOOD PUSH");
    }
    ui->progressBar->setValue(0);
}
