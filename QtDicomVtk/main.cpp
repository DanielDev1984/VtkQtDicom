#include "QtDicomVtk.h"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile styleFile(":/QtDicomVtk/style.qss");
    styleFile.open(QFile::ReadOnly);
    //a.setStyleSheet("QPushButton { background-color: yellow }");
    // Apply the loaded stylesheet
    QString style(styleFile.readAll());
    a.setStyleSheet(style);
    QtDicomVtk w;
    w.show();
    return a.exec();
}
