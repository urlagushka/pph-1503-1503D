#include "main-window.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow window;
    window.setFixedSize(330, 400);
    window.show();
    return a.exec();
}
