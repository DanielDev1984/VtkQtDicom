#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtDicomVtk.h"
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <QVTKInteractor.h>
#include <vtkInteractorStyle.h>

class QtDicomVtk : public QMainWindow
{
    Q_OBJECT

public:
    QtDicomVtk(QWidget *parent = nullptr);
    ~QtDicomVtk();
public slots:
    void onDrawSphereClicked(); 
    void onChangeLevel();
    void onChangeWindow();
private:
    Ui::QtDicomVtkClass ui;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_renderWindow;
    vtkSmartPointer<vtkRenderer> m_renderer_fg;
    vtkSmartPointer<vtkRenderer> m_renderer_bg;
    vtkSmartPointer<QVTKInteractor> m_interactor;
    vtkSmartPointer<vtkInteractorStyle> m_interactorStyle;
};
