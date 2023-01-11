#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tinyexpr.h"
#include <iostream>

std::string EquaActual="";
bool UltimIgual=true;
bool EqValid=true;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);

    //connect de tots els botons
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
    if(UltimIgual){
        ui->visor->setText("");
        UltimIgual = false;
    }
    QPushButton* obj = (QPushButton*) sender();
    QString text = obj->text();
    if(text=="."){
        coma();
    }
    if(text=="X"){ text="*"; }
    if(EquaActual.length()>10){
        ui->visor->setText("..." + ui->visor->text());
    }
    else{
        ui->visor->setText(ui->visor->text() + obj->text());
    }
    if(EquaActual != "nan"){
       EquaActual=EquaActual+text.toStdString();
    }
}

void MainWindow::coma ()
{
    char ultimVal=' ';
    if(EquaActual.length()>0){
        ultimVal=EquaActual[EquaActual.length()-1];
    }
    // La equacio .3+2.3 és invalida ja que . ha d'anar seguit d'un numero, això ho mirem aquí
    if((EquaActual=="") || (ultimVal=='+')|| (ultimVal=='-')|| (ultimVal=='*')|| (ultimVal=='/')){
        EqValid=false;
    }
}

void MainWindow::eliminar ()
{
    ui->visor->setText("0");
    //Eliminar equacio a dalt
    UltimIgual=true;
    EquaActual="";
}

void MainWindow::calcular ()
{
    const char *StringCalcular = EquaActual.c_str();
    QString qstr = QString::fromStdString(EquaActual);
    ui->visor->setText(qstr+" = "+"\n");
    double resultat = te_interp(StringCalcular, 0);
    QString resultatStr = QString::number(resultat);
    if(resultatStr=="nan" || EqValid==false){
        resultatStr="Error";
        EqValid=true;
    }
    ui->visor->setText(ui->visor->text()+resultatStr);
    EquaActual="";
    UltimIgual=true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

