#include "QtDicomVtk.h"
#include <vtkSphereSource.h>
#include <vtkActor.h>
#include <vtkImageActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkPNMReader.h>

QtDicomVtk::QtDicomVtk(QWidget *parent)
    : QMainWindow(parent),
    m_renderWindow{vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()},
    m_renderer_fg{vtkSmartPointer<vtkRenderer>::New()},
    m_renderer_bg{ vtkSmartPointer<vtkRenderer>::New() },
    m_interactor{ vtkSmartPointer<QVTKInteractor>::New() },
    m_interactorStyle{ vtkSmartPointer<vtkInteractorStyle>::New() }
{
    ui.setupUi(this);

    // setup rendering
    m_renderWindow->AddRenderer(m_renderer_fg);
    m_renderWindow->AddRenderer(m_renderer_bg);
    m_renderWindow->SetInteractor(m_interactor);
    m_renderWindow->SetNumberOfLayers(2);
    m_renderer_bg->SetLayer(0);
    m_renderer_fg->SetLayer(1);
    ui.openGLWidget->setRenderWindow(m_renderWindow);
    m_interactor->SetInteractorStyle(m_interactorStyle);
    m_interactor->Initialize();


    // setup bg-color
    m_renderer_bg->SetBackground(1.0, 0.0, 0.0);

    // set ui-connection
    QObject::connect(ui.pushButton, &QPushButton::clicked, this, &QtDicomVtk::onDrawSphereClicked);
}

QtDicomVtk::~QtDicomVtk()
{}

void QtDicomVtk::onDrawSphereClicked()
{
    vtkSmartPointer<vtkPNMReader> imageReader_bG{ vtkSmartPointer<vtkPNMReader>::New() };
    constexpr auto fN_bG{ "C:\\Users\\strai\\source\\TDD_raytracer\\TDD_Raytracer\\renderedImage.ppm" };
    imageReader_bG->SetFileName(fN_bG);
    imageReader_bG->Update();
    const auto imageData_bG{ imageReader_bG->GetOutput() };
    vtkSmartPointer<vtkImageActor> actor_bG{ vtkSmartPointer<vtkImageActor>::New() };
    actor_bG->SetInputData(imageData_bG);
    m_renderer_bg->AddViewProp(actor_bG);
    m_renderer_bg->ResetCamera();

    // create sphere
    vtkSmartPointer<vtkSphereSource> sphereSource{ vtkSmartPointer<vtkSphereSource>::New() };
    sphereSource->SetRadius(5);
    sphereSource->Update();
    // create sphere actor
    vtkSmartPointer<vtkPolyDataMapper> sphereMapper{ vtkSmartPointer<vtkPolyDataMapper>::New() };
    sphereMapper->SetInputData(sphereSource->GetOutput());
    vtkSmartPointer<vtkActor> sphere{ vtkSmartPointer<vtkActor>::New() };
    sphere->SetMapper(sphereMapper);
    // add sphere actor to OpenGL
    m_renderer_fg->AddViewProp(sphere);
    m_renderer_fg->ResetCamera();
    m_renderWindow->Render();
    
}