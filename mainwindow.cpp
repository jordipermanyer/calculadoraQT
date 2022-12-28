#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tinyexpr.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->button1, SIGNAL(clicked()), this, SLOT(nombre()));
    connect(ui->button2, SIGNAL(clicked()), this, SLOT(nombre()));
    connect(ui->button3, SIGNAL(clicked()), this, SLOT(nombre()));
    connect(ui->button4, SIGNAL(clicked()), this, SLOT(nombre()));
    connect(ui->button5, SIGNAL(clicked()), this, SLOT(nombre()));
    connect(ui->button6, SIGNAL(clicked()), this, SLOT(nombre()));
    connect(ui->button7, SIGNAL(clicked()), this, SLOT(nombre()));
    connect(ui->button8, SIGNAL(clicked()), this, SLOT(nombre()));
    connect(ui->button9, SIGNAL(clicked()), this, SLOT(nombre()));
    connect(ui->button0, SIGNAL(clicked()), this, SLOT(nombre()));
    connect(ui->buttonParentessisLeft, SIGNAL(clicked()), this, SLOT(nombre()));
    connect(ui->buttonParentessisRight, SIGNAL(clicked()), this, SLOT(nombre()));
    connect(ui->buttonDiv, SIGNAL(clicked()), this, SLOT(nombre()));
    connect(ui->buttonComa, SIGNAL(clicked()), this, SLOT(nombre()));
    connect(ui->buttonSuma, SIGNAL(clicked()), this, SLOT(nombre()));
    connect(ui->buttonRest, SIGNAL(clicked()), this, SLOT(nombre()));
    connect(ui->buttonMult, SIGNAL(clicked()), this, SLOT(nombre()));
    connect(ui->buttonAC, SIGNAL(clicked()), this, SLOT(eliminar()));
    connect(ui->buttonIgual, SIGNAL(clicked()), this, SLOT(calcular()));
}

void MainWindow::nombre ()
{
    //Ens guardem quin ha sigut el boto clicat i imprimim el seu valor en el objecte visor (el concatenem '+', volem que s'afegeixi no sobreposar)
    QPushButton* obj = (QPushButton*) sender();
    ui->visor->setText(ui->visor->toPlainText() + obj->text());
}

void MainWindow::eliminar ()
{
    ui->visor->setText("0");
}

void MainWindow::calcular ()
{
    double resultat;
    resultat = te_interp("3+3", 0); //S'ha de guardar en un string tota la equacio aqui he posat 3+3 per tenir un exemple
    QString resultatStr = QString::number(resultat); //Transformem el double a Qstring
    ui->visor->setText(resultatStr);
}

MainWindow::~MainWindow()
{
    delete ui;
}

