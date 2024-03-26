#include "toggle-button.h"

#include <QPushButton>
#include <QVBoxLayout>

ToggleButton::ToggleButton(QWidget* parrent, const char* title) :
    button_(new QPushButton(title, this)),
    status_(false)
{
    button_->setFixedSize(80, 30);
    button_->setCheckable(true);
    button_->setStyleSheet("background-color : red");
    connect(button_, &QPushButton::clicked, this, &ToggleButton::change_status);

    auto* vbox = new QVBoxLayout;
    vbox->addWidget(button_);
    setLayout(vbox);
}

void ToggleButton::change_status() {
    if (button_->isChecked()) {
        status_ = true;
        button_->setStyleSheet("background-color : green");
    }
    else {
        status_ = false;
        button_->setStyleSheet("background-color : red");
    }
}


