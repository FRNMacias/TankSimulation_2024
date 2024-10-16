#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //inicialización de variables.
    capacity_tank = 100;
    level = 0;
    Qin = 0;
    Qout = 0;
    inlet_flow = 0;
    outlet_flow = 0;
    ui->Kin->setValue(0);
    ui->Kout->setValue(0);
    //ui->tank->setFixedSize(2000,5000);
    timer.start(100); //1ms por pulso.


    connect(ui->capacity,
            SIGNAL(editingFinished()),
            this,
            SLOT(set_capacity()));
    connect(ui->Qin,
            SIGNAL(editingFinished()),
            this,
            SLOT(set_Qin()));
    connect(ui->Qout,
            SIGNAL(editingFinished()),
            this,
            SLOT(set_Qout()));
    connect(ui->Kin,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(inlet_valve(int)));
    connect(ui->Kout,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(outlet_valve(int)));
    connect(&timer,
            SIGNAL(timeout()),
            this,
            SLOT(simulation()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::set_capacity(){
    capacity_tank = ui->capacity->text().toInt();
    ui->tank->setRange(0, capacity_tank);
    level = ui->tank->value();
    if(level > capacity_tank){
        level = capacity_tank;
    }
    ui->tank->setValue(level);
    qDebug() << "Nueva capacidad seteada: " << capacity_tank;
}
void MainWindow::set_Qin(){
    Qin = ui->Qin->text().toInt();
    qDebug() << "Nuevo caudal de entrada maximo: " << Qin;
}
void MainWindow::set_Qout(){
    Qout = ui->Qout->text().toInt();
    qDebug() << "Nuevo caudal de salida maximo: " << Qout;
}
void MainWindow::inlet_valve(int value){
    /*inlet_flow = Qin*(value/100.0); al ser value un entero,
                                    debería convertirlo a double*/
    Qout = ui->Qout->text().toInt();
    inlet_flow = Qin * (static_cast<double>(value)/100.0);
    qDebug()<< "Caudal de salida " <<value<< "%, inlet_flow: " <<inlet_flow;
}
void MainWindow::outlet_valve(int value){
    //outlet_flow = Qout*(value/100.0)
    Qout = ui->Qout->text().toInt();
    outlet_flow = Qout * (static_cast<double>(value)/100.0);
    qDebug()<< "Caudal de entrada " <<value<< "%, outlet_flow: " <<outlet_flow;
}
void MainWindow::simulation(){
    level = ui->tank->value();
    //double clock=((timer.interval())/100.0);
    double aux =((inlet_flow - outlet_flow)*0.1);// _flow son por seg
    double level_new = level+(aux);
    qDebug() << "Dif"<<aux<<"level new "<< level_new;
    if(level_new > capacity_tank){
        level_new = capacity_tank;
    }else if(level_new < 0){
        level_new = 100;
    }
    ui->tank->setValue(level_new);
    level = ui->tank->value();
    //qDebug() << "tank level " << level;
}
