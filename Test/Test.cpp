#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkProperty.h>
#include <vtkCallbackCommand.h>
#include <vtkTransform.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkCamera.h>
#include <QDateTime>
#include <vtkCameraActor.h>
#include <QDebug>
#include <vtkRendererCollection.h>
#include <vtkInformation.h>

#include <vtkDataSetMapper.h>
#include <vtkPolyData.h>
#include <vtkCellPicker.h>
#include <vtkIdTypeArray.h>
#include <vtkSelectionNode.h>
#include <vtkSelection.h>
#include <vtkExtractSelection.h>
#include <vtkUnstructuredGrid.h>
#include <vtkSphereSource.h>
#include <vtkLight.h>
#include <vtkLightCollection.h>
#include <vtkLightActor.h>
#include <vtkSphereSource.h>
#include <vtkPlaneSource.h>
#include <vtkCellLocator.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>
#include <vector>
#include <vtkAnimationCue.h>
#include <vtkAnimationScene.h>
#include <vtkConeSource.h>
#include <vtkPolyDataWriter.h>
#include <vtkCellArray.h>
#include <vtkLine.h>
#include <vtkDoubleArray.h>
#include <vtkImageCanvasSource2D.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vtkMetaImageReader.h>
#include <vtkBMPReader.h>
#include <vtkImageActor.h>
#include <vtkInteractorStyleImage.h>
#include <vtkJPEGReader.h>
#include <vtkImageBlend.h>
#include <vtkExtractVOI.h>
#include <vtkActor2D.h>
#include <vtkMapper2D.h>
#include <vtkInteractorStyleTrackballActor.h>

//////***************    11  同一个view中 挪动不同物体      *************************  


//int main (int, char *[])
//{


    
//    vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
//    vtkSmartPointer<vtkPolyDataMapper> cubeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    vtkSmartPointer<vtkActor> cubeActor = vtkSmartPointer<vtkActor>::New();
//    cube->Update();
//    cubeMapper->SetInputConnection(cube->GetOutputPort());
//    cubeActor->SetMapper(cubeMapper);
//    cubeActor->SetPosition(0, 0, 0);
    
    
//    vtkSmartPointer<vtkSphereSource>sphere = vtkSmartPointer<vtkSphereSource>::New();
//    vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
//    sphere->Update();
//    sphereMapper->SetInputConnection(sphere->GetOutputPort());
//    sphereActor->SetMapper(sphereMapper);
//    sphereActor->SetPosition(2, 2, 2);
    
    
//    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
//    vtkSmartPointer<vtkRenderWindow>renwindow = vtkSmartPointer<vtkRenderWindow>::New();
//    vtkSmartPointer<vtkRenderWindowInteractor>interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    
//    render->AddActor(cubeActor);
//    render->AddActor(sphereActor);
    
//    renwindow->AddRenderer(render);
//    renwindow->SetSize(600, 600);
    
//    interactor->SetRenderWindow(renwindow);
    
    
//    vtkSmartPointer<vtkInteractorStyleTrackballActor> style = vtkSmartPointer<vtkInteractorStyleTrackballActor>::New();
//    interactor->SetInteractorStyle(style);
    
    
    
    
    
    
    
    
    
    
//    interactor->Initialize();
//    interactor->Start();
    
    
    
    
    
    
    
    
  //////***************    10  vtk 图形图像应用4， 7， 8       *************************  
    
    
    
    
  /////*******************  三维图像切片提取   vtkImageReslice***********************//   
    
    
    
    
    /////*******************  提取感兴趣区域   vtkExtractVOI ***********************// 
    
//    vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();
//    reader->SetFileName("picture.bmp");
//    reader->Update();
    
//    int dims[3];
//    reader->GetOutput()->GetDimensions(dims);
    
//    vtkSmartPointer<vtkExtractVOI> extractVOI = vtkSmartPointer<vtkExtractVOI>::New();
//    extractVOI->SetInputConnection(reader->GetOutputPort());
//    extractVOI->SetVOI(dims[0]/4.0, 3*dims[0]/4.0, dims[1]/4.0, 3*dims[1]/4.0, 0, 0);
//    extractVOI->Update();
   
    
    
    
    
    
    
    
    
    
    
//    vtkSmartPointer<vtkMapper> mapper = vtkSmartPointer<vtkMapper>::New();
//    mapper->SetInputConnection(extractVOI->GetOutputPort());
    
//    vtkSmartPointer<vtkActor2D> actor = vtkSmartPointer<vtkActor2D>::New();
//    actor->SetMapper(mapper);
    
//    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
//    render->AddActor2D(actor);
    
//    vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
//    renWin->AddRenderer(render);
    
//    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//    interactor->SetRenderWindow(renWin);
    
//    interactor->Initialize();
//    interactor->Start();
    
    
    
    
    
    
    
    
//    return EXIT_SUCCESS;
//}






//////***************    9  vtk 图形图像应用1        *************************

//int main (int, char *[])
//{

    /////*******************  图像融合    ***********************//
    
//    vtkSmartPointer<vtkJPEGReader>reader = vtkSmartPointer<vtkJPEGReader>::New();
//    reader->SetFileName("picture.jpg");
//    reader->Update();

//    vtkSmartPointer<vtkImageCanvasSource2D> imgSou = vtkSmartPointer<vtkImageCanvasSource2D>::New();
//    imgSou->SetNumberOfScalarComponents(1);
//    imgSou->SetScalarTypeToUnsignedChar();
//    imgSou->SetExtent(0, 512, 0, 512, 0, 0);
//    imgSou->SetDrawColor(0.0);    
//    imgSou->FillBox(0, 512, 0, 512);
//    imgSou->SetDrawColor(255.0);
//    imgSou->FillBox(100, 400, 100, 400);
//    imgSou->Update();
    
//    vtkSmartPointer<vtkImageBlend> blend = vtkSmartPointer<vtkImageBlend>::New();
//    //这里函数接口有变动
////    blend->SetInputConnection(0, reader->GetOutputPort());
////    blend->SetInputConnection(1, imgSou->GetOutputPort());
////    blend->SetInputData(reader->GetOutputDataObject(0));
////    blend->SetInputData(reader->GetOutputDataObject(1));
//    blend->SetInputDataObject(reader->GetOutputDataObject(0));
    
//    blend->SetOpacity(0, 0.4);
//    blend->SetOpacity(1, 0.6);
//    blend->Update();
    
    
    
    
    
    
    /////*******************  vtkImageActor    ***********************//    
    
//    vtkSmartPointer<vtkBMPReader> reader = vtkSmartPointer<vtkBMPReader>::New();
//    reader->SetFileName("picture.bmp");
//    reader->Update();
    
//    vtkSmartPointer<vtkImageActor>imgActor = vtkSmartPointer<vtkImageActor>::New();
//    imgActor->SetInputData(reader->GetOutput());
    
//    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
//    render->AddActor(imgActor);
//    render->SetBackground(.4, .5, .6);
    
//    vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
//    renWin->SetSize(500, 500);
//    renWin->AddRenderer(render);

//    vtkSmartPointer<vtkRenderWindowInteractor> interactor= vtkSmartPointer<vtkRenderWindowInteractor>::New();
    
//    vtkSmartPointer<vtkInteractorStyleImage> style =  vtkSmartPointer<vtkInteractorStyleImage>::New();
      
//    interactor->SetInteractorStyle(style);
    
//    interactor->SetRenderWindow(renWin);
//    interactor->Initialize();
    
    
    
//    interactor->Start();
    
    
    
    
    
    
    
    
/////*******************  创建图像(示例中接口有变)  ***********************//

//    vtkSmartPointer<vtkImageData> img = vtkSmartPointer<vtkImageData>::New();
//    img->SetDimensions(10, 10, 10);
//    //img->SetScalarType();//这个方法在vtk8.1中没有
//    //img->SetNumberOfScalarComponents(1);//这个方法在vtk8.1中参数有变动
//    //img->AllocateScalars(); 接口有变动
    
//    unsigned char *ptr = (unsigned char*)img->GetScalarPointer();
//    for (int i = 0; i < 10*10*10; ++i)
//    {
//        *ptr ++= i %256;
//    }
            
            
    
/////*******************  通过画布进行绘制  ***********************//

//    vtkSmartPointer<vtkImageCanvasSource2D> canvas = vtkSmartPointer<vtkImageCanvasSource2D>::New();
//    canvas->SetScalarTypeToUnsignedChar();   //设置画布像素类型
//    canvas->SetNumberOfScalarComponents(1);  //设置像素成分数目
//    canvas->SetExtent(0, 100, 0, 100, 0, 0); //设置画布大小
    
//    canvas->SetDrawColor(0, 0, 0, 0);
//    canvas->FillBox(0, 100, 0, 100);         //绘制填充矩形
    
//    canvas->SetDrawColor(255, 0, 0, 0);
//    canvas->FillBox(20, 40, 20, 40);
    
//    canvas->Update();
    
    
//    return 0;
//}









////***************    1  “基本单元”         单正方体显示            *************************//

//int main(int, char *[])
//{
//    vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
//    cube->SetCenter(1, 1, 1);
//    cube->Update();
    
//    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    mapper->SetInputConnection(cube->GetOutputPort());
    
//    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
//    actor->SetMapper(mapper);
    
//    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
//    render->AddActor(actor);
    
//    vtkSmartPointer<vtkRenderWindow>renwindow = vtkSmartPointer<vtkRenderWindow>::New();
//    renwindow->AddRenderer(render);
//    renwindow->SetSize(600, 300);
    
    
//    vtkSmartPointer<vtkRenderWindowInteractor>interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//    interactor->SetRenderWindow(renwindow);
    
    
//    interactor->Initialize();
//    interactor->Start();
    
    
//    return EXIT_SUCCESS;
//}
