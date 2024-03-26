#include "output-box.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

OutputBox::OutputBox(QWidget* parent) :
    QWidget(parent),
    button_(new QPushButton("Receive", parent)),
    label_(new QLabel("Null", parent))
{
    auto* hbox = new QHBoxLayout(parent);
    button_->setFixedSize(80, 30);

    hbox->addWidget(button_);
    hbox->addWidget(label_);
    hbox->addStretch(1);

    setLayout(hbox);
}
