#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    //-----------------------------
public slots:
    /**
     * @brief set_capacity
     * Setea la capacidad del tanke mediante un LineEdit.
     */
    void set_capacity();
    /**
     * @brief set_Qin
     * Setea el caudal máximo de entrada meidante un LineEdit.
     */
    void set_Qin();
    /**
     * @brief set_Qout
     * Setea el caudal máximo de salida meidante un LineEdit.
     */
    void set_Qout();
    /**
     * @brief inlet_valve
     * Guarda el caudal de entrada mediante la válvula (Dial)
     * @param value
     * recibe la posicion del Dial
     */
    void inlet_valve(int value);
    /**
     * @brief outlet_valve
     * Guarda el caudal de salida mediante la válvula (Dial)
     * @param value
     * recibe la posicion del Dial
     */
    void outlet_valve(int value);
    /**
     * @brief simulation
     * Simula, incrementando o disminuyendo el nivel del tanque,
     * mediante el clock.
     */
    void simulation();
private:
    QTimer timer;
    int capacity_tank;
    int Qin, Qout;
    double inlet_flow, outlet_flow;
    double level;
};
#endif // MAINWINDOW_H
