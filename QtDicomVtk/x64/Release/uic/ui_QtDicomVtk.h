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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qvtkopenglnativewidget.h"

QT_BEGIN_NAMESPACE

class Ui_QtDicomVtkClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QVTKOpenGLNativeWidget *openGLWidget;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtDicomVtkClass)
    {
        if (QtDicomVtkClass->objectName().isEmpty())
            QtDicomVtkClass->setObjectName(QString::fromUtf8("QtDicomVtkClass"));
        QtDicomVtkClass->resize(449, 400);
        centralWidget = new QWidget(QtDicomVtkClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        openGLWidget = new QVTKOpenGLNativeWidget(centralWidget);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));

        verticalLayout->addWidget(openGLWidget);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        QtDicomVtkClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtDicomVtkClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 449, 22));
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
        pushButton->setText(QCoreApplication::translate("QtDicomVtkClass", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtDicomVtkClass: public Ui_QtDicomVtkClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTDICOMVTK_H
