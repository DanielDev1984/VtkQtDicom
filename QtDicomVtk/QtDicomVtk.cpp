#include "QtDicomVtk.h"
#include <vtkSphereSource.h>
#include <vtkActor.h>
#include <vtkFileOutputWindow.h>
#include <vtkImageActor.h>
#include <vtkCamera.h>
#include <vtkImageData.h>
#include <vtkImageHistogram.h>
#include <vtkImageSlice.h>
#include <vtkImageSliceMapper.h>
#include <vtkImageProperty.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkDICOMImageReader.h>
#include <vtkSTLReader.h>
#include <vtkTransform.h>

#include <sstream>

QtDicomVtk::QtDicomVtk(QWidget *parent)
    : QMainWindow(parent),
    m_renderWindow{vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New()},
    m_renderer_fg{vtkSmartPointer<vtkRenderer>::New()},    
    m_renderer_bg{ vtkSmartPointer<vtkRenderer>::New() },
    m_renderer_bg_left{ vtkSmartPointer<vtkRenderer>::New() },
    m_renderer_bg_right{ vtkSmartPointer<vtkRenderer>::New() },
    m_interactor{ vtkSmartPointer<QVTKInteractor>::New() },
    m_interactorStyle{ vtkSmartPointer<vtkInteractorStyle>::New() },
    m_actor_bG{ vtkSmartPointer<vtkImageActor>::New() },
    m_actor_bG_left{ vtkSmartPointer<vtkImageActor>::New() },
    m_actor_bG_right{ vtkSmartPointer<vtkImageActor>::New() },
    m_actor_polyData{ vtkSmartPointer<vtkActor>::New() }
{
    ui.setupUi(this);
    

    m_graphicsView = new QGraphicsView(ui.centralWidget);
    m_graphicsView->setGeometry(QRect(315, 100, 130, 130));
    QBrush test1{ QColor(127,127,0,127) };
    m_graphicsView->setBackgroundBrush(test1);
    m_graphicsView->setStyleSheet("background: transparent");
    m_scene = new QGraphicsScene(ui.centralWidget);
    m_graphicsView->setScene(m_scene);
    QBrush test{ QColor(127,127,127,127) };
    //m_scene->setBackgroundBrush(test);
    QPen outlinePen(Qt::black);
    QBrush blueBrush{QColor(127,0,0,50) };
    
    m_rectItem = m_scene->addRect(-100, 0, 40, m_graphicsView->height()-5, outlinePen, blueBrush);
    
    auto boundingRect = m_scene->itemsBoundingRect();
    m_scene->setSceneRect(0, 0, boundingRect.right(), boundingRect.bottom());
    


    //m_scene->addRect(100, 0, 80, 100, Qt::black, Qt::blue);

    // setup rendering
    /*const auto i{ 1 };
    m_renderer_fg->SetViewport(0.5 * (i & 1), 0.0, 0.5 + 0.5 * (i & 1), 1.0);*/

    m_renderWindow->AddRenderer(m_renderer_fg);
    //m_renderWindow->AddRenderer(m_renderer_bg);
    m_renderWindow->SetInteractor(m_interactor);
    m_renderWindow->SetNumberOfLayers(2);
    m_renderer_bg->SetLayer(0);
    m_renderer_fg->SetLayer(1);
    ui.openGLWidget->setRenderWindow(m_renderWindow);
    m_interactor->SetInteractorStyle(m_interactorStyle);
    m_interactor->Initialize();


    // setup bg-color
    m_renderer_bg->SetBackground(0.8, 0.3, 0.3);

    // set ui-connection
    QObject::connect(ui.pushButton, &QPushButton::clicked, this, &QtDicomVtk::onDrawSphereClicked);
    QObject::connect(ui.Slider_Level, &QSlider::valueChanged, this, &QtDicomVtk::onChangeLevel);
    QObject::connect(ui.Slider_Window, &QSlider::valueChanged, this, &QtDicomVtk::onChangeWindow);
    QObject::connect(ui.SliderZRotation, &QSlider::valueChanged, this, &QtDicomVtk::onChangeZRotation);
    QObject::connect(ui.Slider_ZPosition, &QSlider::valueChanged, this, &QtDicomVtk::onChangeZPosition);

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
    const auto level{ histogram->GetBinOrigin() };
    m_levelRange = level;
    const auto width{level + (nbins - 1) * histogram->GetBinSpacing()};
    m_windowRange = width;

    std::stringstream ss;
    ss << "initial level: " << level << "initial width: " << width;
    const std::string tmp = ss.str();
    const char* cstr = tmp.c_str();
    vtkOutputWindow::GetInstance()->DisplayText(cstr);
    
    
    const auto histogramData_bG{ histogram->GetOutput() };

    vtkCamera* camera_left = m_renderer_bg_left->GetActiveCamera();
    m_renderer_bg_left->SetViewport(0.0, 0.0, 0.5 , 1.0);
    m_renderer_bg_left->SetLayer(0);
    m_renderer_bg_left->SetBackground(0.0, 0.3, 0.3);
    m_renderWindow->AddRenderer(m_renderer_bg_left);
    vtkNew<vtkImageSliceMapper> imageMapper_left;
    double yd_left;
    imageMapper_left->SetInputConnection(imageReader_bG->GetOutputPort());
    int extent_left[6];
    imageReader_bG->GetOutput()->GetExtent(extent_left);
    yd_left = (extent_left[3] - extent_left[2] + 1);
    const double* bounds_left = imageMapper_left->GetBounds();
    double point_left[3];
    point_left[0] = 0.5 * (bounds_left[0] + bounds_left[1]);
    point_left[1] = 0.5 * (bounds_left[2] + bounds_left[3]);
    point_left[2] = 0.5 * (bounds_left[4] + bounds_left[5]);

    camera_left->SetFocalPoint(point_left);
    point_left[imageMapper_left->GetOrientation()] += 1000;
    camera_left->SetPosition(point_left);
    camera_left->SetViewUp(0.0, 1.0, 0.0);
    camera_left->ParallelProjectionOn();
    // Set scale so that vertical dimension fills the window
    camera_left->SetParallelScale(0.5 * yd_left);

    m_actor_bG_left->SetMapper(imageMapper_left);
    m_renderer_bg_left->AddViewProp(m_actor_bG_left);

    m_actor_bG_left->GetProperty()->SetColorWindow(width);
    m_actor_bG_left->GetProperty()->SetColorLevel(level);
    m_renderer_bg_left->ResetCamera();


    vtkCamera* camera_right = m_renderer_bg_right->GetActiveCamera();
    m_renderer_bg_right->SetViewport(0.5, 0.0, 0.5 + 0.5, 1.0);
    m_renderer_bg_right->SetLayer(0);
    m_renderer_bg_right->SetBackground(0.8, 0.3, 0.3);
    m_renderWindow->AddRenderer(m_renderer_bg_right);
    vtkNew<vtkImageSliceMapper> imageMapper_right;
    double yd_right;
    imageMapper_right->SetInputConnection(histogram->GetOutputPort());
    int extent_right[6];
    histogram->GetOutput()->GetExtent(extent_right);
    yd_right = (extent_right[3] - extent_right[2] + 1);
    const double* bounds_right = imageMapper_right->GetBounds();
    double point_right[3];
    point_right[0] = 0.5 * (bounds_right[0] + bounds_right[1]);
    point_right[1] = 0.5 * (bounds_right[2] + bounds_right[3]);
    point_right[2] = 0.5 * (bounds_right[4] + bounds_right[5]);

    camera_right->SetFocalPoint(point_right);
    point_right[imageMapper_right->GetOrientation()] += 1000;
    camera_right->SetPosition(point_right);
    camera_right->SetViewUp(0.0, 1.0, 0.0);
    camera_right->ParallelProjectionOn();
    // Set scale so that vertical dimension fills the window
    camera_right->SetParallelScale(0.5 * yd_right);

    m_actor_bG_right->SetMapper(imageMapper_right);
    m_renderer_bg_right->AddViewProp(m_actor_bG_right);

    m_actor_bG_right->GetProperty()->SetColorWindow(255.0);
    m_actor_bG_right->GetProperty()->SetColorLevel(127.0);
    m_renderer_bg_right->ResetCamera();


    


    /*vtkNew<vtkImageSliceMapper> imageMapper;
    imageMapper->SetInputConnection(imageReader_bG->GetOutputPort());
    int extent[6];
    imageReader_bG->GetOutput()->GetExtent(extent);
    auto yd = (extent[3] - extent[2] + 1);

    vtkSmartPointer<vtkImageActor> actor_bG{ vtkSmartPointer<vtkImageActor>::New() };
    
    //m_actor_bG->SetInputData(imageData_bG);
    m_actor_bG->SetMapper(imageMapper);

    m_actor_bG->GetProperty()->SetColorWindow(width);
    m_actor_bG->GetProperty()->SetColorLevel(level);
    
    m_renderer_bg->AddViewProp(m_actor_bG);
    m_renderer_bg->ResetCamera();*/


    vtkSmartPointer<vtkSTLReader> reader{ vtkSmartPointer<vtkSTLReader>::New() };
    constexpr auto fN_polyData{ ".\\armstl\\arm.stl" };
    reader->SetFileName(fN_polyData);
    reader->Update();
    auto polyData = reader->GetOutput();
    vtkSmartPointer<vtkPolyDataMapper> stlDataMapper{ vtkSmartPointer<vtkPolyDataMapper>::New() };
    stlDataMapper->SetInputData(polyData);
    //vtkSmartPointer<vtkActor> polyDataActor{ vtkSmartPointer<vtkActor>::New() };
    
    //polyDataActor->RotateZ(45);
    //polyDataActor->SetOrigin(-100, 0, 0);

    


    //vtkTransform* myTrans = vtkTransform::New();
    //myTrans->Translate(100, 0, 0);
    //polyDataActor->SetUserTransform(myTrans);
    //m_actor_polyData->SetUserTransform(myTrans);

    //polyDataActor->SetPosition(-100, 0, 0);

    m_actor_polyData->GetProperty()->SetOpacity(0.8);
    m_actor_polyData->GetProperty()->SetColor(0.5, 0.5, 0.5);
    m_actor_polyData->GetProperty()->SetSpecularColor(1.0, 0.0, 0.0);
    m_actor_polyData->GetProperty()->SetAmbientColor(0.5, 0.0, 0.0);
    
    m_actor_polyData->SetMapper(stlDataMapper);

    // create sphere
    vtkSmartPointer<vtkSphereSource> sphereSource{ vtkSmartPointer<vtkSphereSource>::New() };
    //sphereSource->SetRadius(1);
    sphereSource->SetCenter(50, 0, 0);
    sphereSource->Update();
    
    // create sphere actor
    vtkSmartPointer<vtkPolyDataMapper> sphereMapper{ vtkSmartPointer<vtkPolyDataMapper>::New() };
    sphereMapper->SetInputData(sphereSource->GetOutput());

    vtkSmartPointer<vtkActor> sphere{ vtkSmartPointer<vtkActor>::New() };
    //sphere->SetOrigin(0.0, 0.0, 0.0);
    sphere->GetProperty()->SetOpacity(0.5);
    
    sphere->SetMapper(sphereMapper);
    // add sphere actor to OpenGL
    //m_renderer_fg->AddViewProp(sphere);
    m_renderer_fg->AddViewProp(m_actor_polyData);
    m_renderer_fg->ResetCamera();
    m_renderWindow->Render();
    
}

void QtDicomVtk::onChangeLevel() 
{

    

    const auto sliderVal{ ui.Slider_Level->value() };
    
    

    const auto relativeVal{ (sliderVal - m_levelSliderMin) / m_levelSliderMax };
    
    const auto sliderVal_Window{ ui.Slider_Window->value() };
    const auto relativeValWindow{ (sliderVal_Window - m_windowSliderMin) / m_windowSliderMax };

    
    //todo: atm this is just a poc, and not reflecting the actual values of the histogram
    //-> make this more robust / working correctly
    m_rectItem->setRect(-100 + relativeVal*100, 0, relativeValWindow*40, m_graphicsView->height() - 5);
    

    m_actor_bG_left->GetProperty()->SetColorLevel(relativeVal * m_levelRange);

    std::stringstream ss;
    ss << "level: " << m_actor_bG_left->GetProperty()->GetColorLevel() << "\n";
    const std::string tmp = ss.str();
    const char* cstr = tmp.c_str();
    vtkOutputWindow::GetInstance()->DisplayText(cstr);

    m_renderer_bg->AddViewProp(m_actor_bG_left);
    m_renderer_bg->ResetCamera();
    m_renderWindow->Render();
}

void QtDicomVtk::onChangeWindow() 
{
    const auto sliderVal{ ui.Slider_Window->value() };

    const auto relativeVal{ (sliderVal - m_windowSliderMin) / m_windowSliderMax };


    const auto sliderVal_Level{ ui.Slider_Level->value() };
    const auto relativeValLevel{ (sliderVal_Level - m_levelSliderMin) / m_levelSliderMax };
    //todo: atm this is just a poc, and not reflecting the actual values of the histogram
    //-> make this more robust / working correctly
    m_rectItem->setRect(-100 + relativeValLevel * 100, 0, relativeVal*40, m_graphicsView->height() - 5);
    
    m_actor_bG_left->GetProperty()->SetColorWindow(relativeVal * m_windowRange);

    std::stringstream ss;
    ss << "window: " << m_actor_bG_left->GetProperty()->GetColorWindow() << "\n";
    const std::string tmp = ss.str();
    const char* cstr = tmp.c_str();
    vtkOutputWindow::GetInstance()->DisplayText(cstr);

    m_renderer_bg->AddViewProp(m_actor_bG_left);
    m_renderer_bg->ResetCamera();
    m_renderWindow->Render();
}

void QtDicomVtk::onChangeZRotation()
{
    const auto sliderVal{ ui.SliderZRotation->value() };

    m_actor_polyData->RotateZ(sliderVal);
    
    
    m_renderer_bg->AddViewProp(m_actor_polyData);
    m_renderer_bg->ResetCamera();
    m_renderWindow->Render();
}

void QtDicomVtk::onChangeZPosition()
{
    // todo: why is it not / how is it possible to initially place the polydata(actor) in a certain place (e.g. left-bottom corner)?
    const auto sliderVal{ ui.Slider_ZPosition->value() };
    m_actor_polyData->SetPosition(1, 1, sliderVal * 3);
    m_renderer_bg->AddViewProp(m_actor_polyData);
    m_renderer_bg->ResetCamera();
    m_renderWindow->Render();
}