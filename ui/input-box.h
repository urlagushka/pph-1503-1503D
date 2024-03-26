#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class InputBox : public QWidget {
    friend class MainWindow;
public:
    using text_t = const char*;

    explicit InputBox(QWidget* parent = nullptr, text_t article = nullptr, text_t btn = nullptr);
private:
    QPushButton* button_;
    QLineEdit* field_;
};

#endif
