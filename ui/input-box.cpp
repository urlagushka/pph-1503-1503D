#include "input-box.h"

#include <QHBoxLayout>
#include <QLabel>

InputBox::InputBox(QWidget* parent, text_t article, text_t btn) :
    QWidget(parent),
    button_(new QPushButton(btn, parent)),
    field_(new QLineEdit())
{
    auto* vbox = new QVBoxLayout;
    auto* hbox_field = new QHBoxLayout;
    auto* label = new QLabel(article, parent);
    field_->setFixedSize(200, 30);
    button_->setFixedSize(80, 30);
    label->setBuddy(field_);

    hbox_field->addWidget(button_);
    hbox_field->addWidget(field_);
    hbox_field->addStretch(1);

    vbox->addWidget(label);
    vbox->addLayout(hbox_field);
    vbox->addStretch(1);

    setLayout(vbox);
}
