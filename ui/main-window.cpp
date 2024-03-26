#include "main-window.h"

#include <QVBoxLayout>
#include <QMessageBox>
#include <stdexcept>

#include "connection.h"
#include "signals.h"

MainWindow::MainWindow(QWidget *parent):
    QWidget(parent),
    power_switch_(new ToggleButton(parent, "Power")),
    ip_input_(new InputBox(parent, "IP address", "Connect")),
    voltage_input_(new InputBox(parent, "Voltage", "Send")),
    amperage_input_(new InputBox(parent, "Amperage", "Send")),
    voltage_output_(new OutputBox(parent)),
    amperage_output_(new OutputBox(parent)),
    connection_(nullptr)
{
    auto* voltage_box = new QVBoxLayout;
    voltage_box->addWidget(voltage_input_, 0, Qt::AlignTop);
    voltage_box->addWidget(voltage_output_, 0, Qt::AlignTop);

    auto* amperage_box = new QVBoxLayout;
    amperage_box->addWidget(amperage_input_, 0, Qt::AlignTop);
    amperage_box->addWidget(amperage_output_, 0, Qt::AlignTop);

    auto* vbox = new QVBoxLayout;
    vbox->addWidget(power_switch_);
    vbox->addWidget(ip_input_);
    vbox->addLayout(voltage_box);
    vbox->addLayout(amperage_box);
    setLayout(vbox);

    connect(voltage_input_->button_, &QPushButton::clicked, this, &MainWindow::set_voltage);
    connect(amperage_input_->button_, &QPushButton::clicked, this, &MainWindow::set_amperage);
    connect(voltage_output_->button_, &QPushButton::clicked, this, &MainWindow::get_voltage);
    connect(amperage_output_->button_, &QPushButton::clicked, this, &MainWindow::get_amperage);
    connect(ip_input_->button_, &QPushButton::clicked, this, &MainWindow::connect_ip);
    connect(power_switch_->button_, &QPushButton::clicked, this, &MainWindow::switch_power);
}

MainWindow::~MainWindow()
{
    delete power_switch_;
    delete ip_input_;
    delete voltage_input_;
    delete amperage_input_;
    delete voltage_output_;
    delete amperage_output_;
    delete connection_;
}

void MainWindow::get_voltage() {
    if (connection_ == nullptr) {
        QMessageBox::critical(this, "Error", "No connection", QMessageBox::Ok);
        return;
    }

    try {
        const char * cmd = get_signals("get_voltage");
        connection_->safe_send(cmd);
        Connection::msg_t buffer;
        constexpr size_t buffer_size = 1024;
        connection_->safe_read(buffer, buffer_size);
        voltage_output_->label_->setText(buffer);
    }
    catch (const std::runtime_error& error) {
        QMessageBox::critical(this, "Error", error.what(), QMessageBox::Ok);
    }
    catch (const std::out_of_range& error) {
        QMessageBox::critical(this, "Error", error.what(), QMessageBox::Ok);
    }
}

void MainWindow::set_voltage() {
    if (connection_ == nullptr) {
        QMessageBox::critical(this, "Error", "No connection", QMessageBox::Ok);
        return;
    }

    try {
        std::string cmd = get_signals("set_voltage");
        cmd.append(voltage_input_->field_->text().toLocal8Bit().data());
        connection_->safe_send(cmd.c_str());
    }
    catch (const std::runtime_error& error) {
        QMessageBox::critical(this, "Error", error.what(), QMessageBox::Ok);
    }
    catch (const std::out_of_range& error) {
        QMessageBox::critical(this, "Error", error.what(), QMessageBox::Ok);
    }
}

void MainWindow::get_amperage() {
    if (connection_ == nullptr) {
        QMessageBox::critical(this, "Error", "No connection", QMessageBox::Ok);
        return;
    }

    try {
        const char * cmd = get_signals("get_amperage");
        connection_->safe_send(cmd);
        Connection::msg_t buffer;
        constexpr size_t buffer_size = 1024;
        connection_->safe_read(buffer, buffer_size);
        amperage_output_->label_->setText(buffer);
    }
    catch (const std::runtime_error& error) {
        QMessageBox::critical(this, "Error", error.what(), QMessageBox::Ok);
    }
    catch (const std::out_of_range& error) {
        QMessageBox::critical(this, "Error", error.what(), QMessageBox::Ok);
    }
}

void MainWindow::set_amperage() {
    if (connection_ == nullptr) {
        QMessageBox::critical(this, "Error", "No connection", QMessageBox::Ok);
        return;
    }

    try {
        std::string cmd = get_signals("set_amperage");
        cmd.append(amperage_input_->field_->text().toLocal8Bit().data());
        connection_->safe_send(cmd.c_str());
    }
    catch (const std::runtime_error& error) {
        QMessageBox::critical(this, "Error", error.what(), QMessageBox::Ok);
    }
    catch (const std::out_of_range& error) {
        QMessageBox::critical(this, "Error", error.what(), QMessageBox::Ok);
    }
}

void MainWindow::connect_ip() {
    delete connection_;
    connection_ = new Connection(ip_input_->field_->text().toLocal8Bit().data());
    try {
        connection_->safe_connect();
    }
    catch (const std::runtime_error& error) {
        QMessageBox::critical(this, "Error", error.what(), QMessageBox::Ok);
        delete connection_;
        connection_ = nullptr;
    }
}

void MainWindow::switch_power() {
    if (connection_ == nullptr) {
        QMessageBox::critical(this, "Error", "No connection", QMessageBox::Ok);
        return;
    }

    try {
        const char * cmd = get_signals((power_switch_->status_) ? "on" : "off");
        connection_->safe_send(cmd);
    }
    catch (const std::runtime_error& error) {
        QMessageBox::critical(this, "Error", error.what(), QMessageBox::Ok);
    }
    catch (const std::out_of_range& error) {
        QMessageBox::critical(this, "Error", error.what(), QMessageBox::Ok);
    }
}
