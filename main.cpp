#include "music.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Music w;
    w.show();
    return a.exec();
}
