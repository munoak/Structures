#include "mainwindow.hh"
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
}

void MainWindow::on_countButton_clicked()
{
    QString weight = ui->weightLineEdit->text();
    QString height = ui->heightLineEdit->text();

    double weight_ = weight.toDouble();
    double height_ = height.toDouble();

    double bmi = weight_/(height_*height_*0.0001);

    ui->resultLabel->setText(QString::number(bmi));

    if (bmi <= 18.5)
        ui->infoTextBrowser->setText("You are underweight.");

    if(bmi >= 25)
        ui->infoTextBrowser->setText("You are overweight.");

    else
        ui->infoTextBrowser->setText("Your weight is normal.");
}
