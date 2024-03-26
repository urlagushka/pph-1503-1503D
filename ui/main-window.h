#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtWidgets/QWidget>

#include "input-box.h"
#include "output-box.h"
#include "toggle-button.h"
#include "connection.h"

class MainWindow : public QWidget
{
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    ToggleButton* power_switch_;
    InputBox* ip_input_;
    InputBox* voltage_input_;
    InputBox* amperage_input_;
    OutputBox* voltage_output_;
    OutputBox* amperage_output_;
    Connection* connection_;

    void get_voltage();
    void set_voltage();
    void get_amperage();
    void set_amperage();
    void connect_ip();
    void switch_power();
};

#endif
