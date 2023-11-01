/********************************************************************************
** Form generated from reading UI file 'QtDicomVtk.ui'
**
** Created by: Qt User Interface Compiler version 6.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTDICOMVTK_H
#define UI_QTDICOMVTK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qvtkopenglnativewidget.h"

QT_BEGIN_NAMESPACE

class Ui_QtDicomVtkClass
{
public:
    QWidget *centralWidget;
    QVTKOpenGLNativeWidget *openGLWidget;
    QPushButton *pushButton;
    QSlider *Slider_Level;
    QSlider *Slider_Window;
    QLabel *label;
    QLabel *label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtDicomVtkClass)
    {
        if (QtDicomVtkClass->objectName().isEmpty())
            QtDicomVtkClass->setObjectName(QString::fromUtf8("QtDicomVtkClass"));
        QtDicomVtkClass->resize(569, 492);
        centralWidget = new QWidget(QtDicomVtkClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        openGLWidget = new QVTKOpenGLNativeWidget(centralWidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setGeometry(QRect(110, 0, 361, 331));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 290, 75, 23));
        Slider_Level = new QSlider(centralWidget);
        Slider_Level->setObjectName(QString::fromUtf8("Slider_Level"));
        Slider_Level->setGeometry(QRect(10, 342, 201, 22));
        Slider_Level->setOrientation(Qt::Horizontal);
        Slider_Window = new QSlider(centralWidget);
        Slider_Window->setObjectName(QString::fromUtf8("Slider_Window"));
        Slider_Window->setGeometry(QRect(9, 396, 201, 22));
        Slider_Window->setOrientation(Qt::Horizontal);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(11, 317, 47, 16));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 370, 47, 16));
        QtDicomVtkClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtDicomVtkClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 569, 21));
        QtDicomVtkClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtDicomVtkClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtDicomVtkClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtDicomVtkClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtDicomVtkClass->setStatusBar(statusBar);

        retranslateUi(QtDicomVtkClass);

        QMetaObject::connectSlotsByName(QtDicomVtkClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtDicomVtkClass)
    {
        QtDicomVtkClass->setWindowTitle(QCoreApplication::translate("QtDicomVtkClass", "QtDicomVtk", nullptr));
        pushButton->setText(QCoreApplication::translate("QtDicomVtkClass", "DisplyScan", nullptr));
        label->setText(QCoreApplication::translate("QtDicomVtkClass", "Level", nullptr));
        label_2->setText(QCoreApplication::translate("QtDicomVtkClass", "Window", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtDicomVtkClass: public Ui_QtDicomVtkClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTDICOMVTK_H
