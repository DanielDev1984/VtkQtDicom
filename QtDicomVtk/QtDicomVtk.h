#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLabel>

#include <QtWidgets/QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

#include "ui_QtDicomVtk.h"
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkRenderer.h>
#include <QVTKInteractor.h>
#include <vtkInteractorStyle.h>
#include <vtkImageActor.h>
#include <vtkImageViewer2.h>

class QtDicomVtk : public QMainWindow
{
    Q_OBJECT

public:
    QtDicomVtk(QWidget *parent = nullptr);
    ~QtDicomVtk();
public slots:
    void onDrawSphereClicked(); 
    void onDisplaySeriesClicked();
    void onChangeLevel();
    void onChangeWindow();
    void onChangeZRotation();
    void onChangeZPosition();
    void onIncreaseSliceNoChange();
private:
    Ui::QtDicomVtkClass ui;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_renderWindow;
    vtkSmartPointer<vtkRenderer> m_renderer_fg;    
    vtkSmartPointer<vtkRenderer> m_renderer_bg;
    vtkSmartPointer<vtkRenderer> m_renderer_bg_left;
    vtkSmartPointer<vtkRenderer> m_renderer_bg_right;
    vtkSmartPointer<QVTKInteractor> m_interactor;
    vtkSmartPointer<vtkInteractorStyle> m_interactorStyle;
    vtkSmartPointer<vtkImageActor> m_actor_bG;
    vtkSmartPointer<vtkImageActor> m_actor_bG_left;
    vtkSmartPointer<vtkImageActor> m_actor_bG_right;
    vtkSmartPointer<vtkActor> m_actor_polyData;

    vtkNew<vtkImageViewer2> m_imageViewer;

    QGraphicsScene* m_scene;
    QGraphicsView* m_graphicsView;
    QGraphicsRectItem* m_rectItem;

    double m_windowRange;
    double m_windowSliderMax;
    double m_windowSliderMin;

    double m_levelRange;
    double m_levelSliderMax;
    double m_levelSliderMin;
    
};
