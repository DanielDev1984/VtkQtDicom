#include "QtDicomVtk.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtDicomVtk w;
    w.show();
    return a.exec();
}
