#include "database.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Database w;
    w.show();
    return a.exec();
}
