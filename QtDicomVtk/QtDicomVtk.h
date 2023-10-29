#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtDicomVtk.h"

class QtDicomVtk : public QMainWindow
{
    Q_OBJECT

public:
    QtDicomVtk(QWidget *parent = nullptr);
    ~QtDicomVtk();

private:
    Ui::QtDicomVtkClass ui;
};
