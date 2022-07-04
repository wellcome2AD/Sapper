#include <QApplication>
#include "gameinterface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameInterface w(5, 5);
    w.show();
    return a.exec();
}
