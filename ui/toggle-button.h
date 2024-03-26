#ifndef TOGGLE_BUTTON_H
#define TOGGLE_BUTTON_H

#include <QPushButton>
#include <QWidget>

class ToggleButton : public QWidget {
    friend class MainWindow;
public:
    using text_t = const char*;

    explicit ToggleButton(QWidget* parrent = nullptr, text_t title = nullptr);
private:
    QPushButton* button_;
    bool status_;

    void change_status();
};

#endif
