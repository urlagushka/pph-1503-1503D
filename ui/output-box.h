#ifndef OUTPUT_BOX_H
#define OUTPUT_BOX_H

#include <QLabel>
#include <QPushButton>
#include <QWidget>

class OutputBox : public QWidget {
    friend class MainWindow;
public:
    explicit OutputBox(QWidget* parent = nullptr);
private:
    QPushButton* button_;
    QLabel* label_;
};

#endif
