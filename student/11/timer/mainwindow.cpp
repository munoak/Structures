#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    timer(new QTimer(this)),

    ui(new Ui::MainWindow),
     min_(0),sec_(0)
{
    ui->setupUi(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(second_gone()));
    ui->lcdNumberMin->setStyleSheet("background-color: green");
    ui->lcdNumberSec->setStyleSheet("background-color: darkcyan");
     connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(on_stopButton_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    timer->start(1000);
}

void MainWindow::second_gone()
{
    ++sec_;
    if (sec_>= 60){
        ++min_;
        sec_ =0;
    }
    ui->lcdNumberSec->display(sec_);
    ui->lcdNumberMin->display(min_);
}

void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}

void MainWindow::on_resetButton_clicked()
{
    sec_ =0;
    min_=0;
    ui->lcdNumberSec->display(sec_);
    ui->lcdNumberMin->display(min_);
}
