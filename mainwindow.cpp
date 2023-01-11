#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tinyexpr.h"
#include <iostream>

std::string EquaActual="";
bool UltimIgual=false;
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

    //visualitzacio dreta-esquerra
    /*
    ui->visor->setLayoutDirection(Qt::RightToLeft);

    // aligned to the right
    Text {
        text: "خامل"
        horizontalAlignment: Text.AlignLeft
        LayoutMirroring.enabled: true
        width: 200
    }
    */
    /*ui->visor->setStyleSheet("horizontalAlignment: Text.AlignLeft");
    ui->visor->setStyleSheet("LayoutMirroring.enabled: true");
    ui->visor->setStyleSheet("text-align: right;");*/

}

void MainWindow::nombre ()
{
    if(UltimIgual){ //Volem sobrescriure el text en cas de que es comenci nova equacio
        ui->visor->setText("");
        ui->visor2->setText("");
        UltimIgual = false;
    }
    //Ens guardem quin ha sigut el boto clicat i imprimim el seu valor en el objecte visor (el concatenem '+', volem que s'afegeixi no sobreposar)
    QPushButton* obj = (QPushButton*) sender();
    QString text = obj->text();
    if(text=="."){
        coma();
    }
    if(text=="X"){ text="*"; }
    ui->visor2->setText(ui->visor2->toPlainText() + obj->text());
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
        EquaActual="nan";
    }
}

void MainWindow::eliminar ()
{
    ui->visor->setText("");
    ui->visor2->setText("0");
    //Eliminar equacio a dalt
    UltimIgual=true;
    EquaActual="";
}

void MainWindow::calcular ()
{
    const char *StringCalcular = EquaActual.c_str();
    QString EquaAdalt = QString::fromStdString(EquaActual);
    ui->visor->setText(EquaAdalt); //Un cop fet el calcul posarem en el vsior d'adalt la equacio i en el d'abaix el resultat
    double resultat = te_interp(StringCalcular, 0);
    QString resultatStr = QString::number(resultat); //Transformem el double a Qstring
    if(resultatStr=="nan"){
        resultatStr="Error";
    }
    ui->visor2->setText(resultatStr); //Imprimir equacio abaix
    EquaActual="";
    UltimIgual=true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

