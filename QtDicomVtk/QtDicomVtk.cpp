#include "QtDicomVtk.h"
#include <vtkSphereSource.h>
#include <vtkActor.h>
#include <vtkFileOutputWindow.h>
#include <vtkImageActor.h>
#include <vtkImageHistogram.h>
#include <vtkImageSlice.h>
#include <vtkImageProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkDICOMImageReader.h>

#include <sstream>

QtDicomVtk::QtDicomVtk(QWidget *parent)
    : QMainWindow(parent),
    m_renderWindow{vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()},
    m_renderer_fg{vtkSmartPointer<vtkRenderer>::New()},
    m_renderer_bg{ vtkSmartPointer<vtkRenderer>::New() },
    m_interactor{ vtkSmartPointer<QVTKInteractor>::New() },
    m_interactorStyle{ vtkSmartPointer<vtkInteractorStyle>::New() },
    m_actor_bG{ vtkSmartPointer<vtkImageActor>::New() }
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
    m_renderer_bg->SetBackground(0.3, 0.3, 0.3);

    // set ui-connection
    QObject::connect(ui.pushButton, &QPushButton::clicked, this, &QtDicomVtk::onDrawSphereClicked);
    QObject::connect(ui.Slider_Level, &QSlider::valueChanged, this, &QtDicomVtk::onChangeLevel);
    QObject::connect(ui.Slider_Window, &QSlider::valueChanged, this, &QtDicomVtk::onChangeWindow);

    m_windowSliderMax = ui.Slider_Window->maximum();
    m_windowSliderMin = ui.Slider_Window->minimum();
    m_levelSliderMax = ui.Slider_Level->maximum();
    m_levelSliderMin = ui.Slider_Level->minimum();
    
}

QtDicomVtk::~QtDicomVtk()
{}

void QtDicomVtk::onDrawSphereClicked()
{


    vtkSmartPointer<vtkDICOMImageReader> imageReader_bG{ vtkSmartPointer<vtkDICOMImageReader>::New() };
    // todo: make it possible to select files manually
    constexpr auto fN_bG{ ".\\data\\vhf29.dcm" };
    imageReader_bG->SetFileName(fN_bG);
    imageReader_bG->Update();
    const auto imageData_bG{ imageReader_bG->GetOutput() };

    vtkNew<vtkImageHistogram> histogram;
    histogram->SetInputConnection(imageReader_bG->GetOutputPort());
    histogram->GenerateHistogramImageOn();
    histogram->SetHistogramImageSize(256, 256);
    histogram->SetHistogramImageScaleToSqrt();
    histogram->AutomaticBinningOn();
    histogram->Update();

    vtkIdType nbins = histogram->GetNumberOfBins();
    double range[2];
    const auto level{ histogram->GetBinOrigin() };
    m_levelRange = level;
    const auto width{level + (nbins - 1) * histogram->GetBinSpacing()};
    m_windowRange = width;

    std::stringstream ss;
    ss << "level: " << level << "width: " << width;
    const std::string tmp = ss.str();
    const char* cstr = tmp.c_str();
    vtkOutputWindow::GetInstance()->DisplayText(cstr);
    
    
    const auto histogramData_bG{ histogram->GetOutput() };


    vtkSmartPointer<vtkImageActor> actor_bG{ vtkSmartPointer<vtkImageActor>::New() };
    
    m_actor_bG->SetInputData(imageData_bG);
    m_actor_bG->GetProperty()->SetColorWindow(width);
    m_actor_bG->GetProperty()->SetColorLevel(level);
    
    m_renderer_bg->AddViewProp(m_actor_bG);
    m_renderer_bg->ResetCamera();

    // create sphere
    vtkSmartPointer<vtkSphereSource> sphereSource{ vtkSmartPointer<vtkSphereSource>::New() };
    sphereSource->SetRadius(1);
    sphereSource->Update();
    // create sphere actor
    vtkSmartPointer<vtkPolyDataMapper> sphereMapper{ vtkSmartPointer<vtkPolyDataMapper>::New() };
    sphereMapper->SetInputData(sphereSource->GetOutput());
    vtkSmartPointer<vtkActor> sphere{ vtkSmartPointer<vtkActor>::New() };
    sphere->SetMapper(sphereMapper);
    // add sphere actor to OpenGL
    //m_renderer_fg->AddViewProp(sphere);
    m_renderer_fg->ResetCamera();
    m_renderWindow->Render();
    
}

void QtDicomVtk::onChangeLevel() 
{
    const auto sliderVal{ ui.Slider_Level->value() };
    
    const auto relativeVal{ (sliderVal - m_levelSliderMin) / m_levelSliderMax };
    m_actor_bG->GetProperty()->SetColorLevel(relativeVal * m_levelRange);

    std::stringstream ss;
    ss << "level: " << m_actor_bG->GetProperty()->GetColorLevel() << "\n";
    const std::string tmp = ss.str();
    const char* cstr = tmp.c_str();
    vtkOutputWindow::GetInstance()->DisplayText(cstr);

    m_renderer_bg->AddViewProp(m_actor_bG);
    m_renderer_bg->ResetCamera();
    m_renderWindow->Render();
}

void QtDicomVtk::onChangeWindow() 
{
    const auto sliderVal{ ui.Slider_Window->value() };

    const auto relativeVal{ (sliderVal - m_windowSliderMin) / m_windowSliderMax };
    m_actor_bG->GetProperty()->SetColorWindow(relativeVal * m_windowRange);

    std::stringstream ss;
    ss << "level: " << m_actor_bG->GetProperty()->GetColorWindow() << "\n";
    const std::string tmp = ss.str();
    const char* cstr = tmp.c_str();
    vtkOutputWindow::GetInstance()->DisplayText(cstr);

    m_renderer_bg->AddViewProp(m_actor_bG);
    m_renderer_bg->ResetCamera();
    m_renderWindow->Render();
}