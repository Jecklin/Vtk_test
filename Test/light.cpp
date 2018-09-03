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

////***************   4  “灯光”      实现：灯光、灯光原点平面、灯光远点球形    *************************//



//int main(int, char *[])
//{
 
//    vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
//    cube->SetCenter(0, 0, 0);
//    cube->Update();
    
//    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    mapper->SetInputConnection(cube->GetOutputPort());
    
//    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
//    actor->SetMapper(mapper);
////    actor->GetProperty()->SetRepresentationToWireframe();
//    actor->GetProperty()->SetColor(0.2, 0.3, 0.4);
    
//    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
////    render->AddActor(actor);
    
//    vtkSmartPointer<vtkRenderWindow>renwindow = vtkSmartPointer<vtkRenderWindow>::New();
//    renwindow->AddRenderer(render);
//    renwindow->SetSize(600, 300);
    
//    vtkLightCollection *originalLights = render->GetLights();
//    qDebug() << "originalLights number: " << originalLights->GetNumberOfItems();
    
//    renwindow->Render();
    
    
    
//    double lightPosition[3] = {0, 0, 1};
//    double lightFocalPoint[3] = {0, 0, 0};
//    vtkSmartPointer<vtkLight> light1 = vtkSmartPointer<vtkLight>::New();
//    light1->SetLightTypeToSceneLight();
//    light1->SetPosition(lightPosition[0], lightPosition[1], lightPosition[2]);
//    light1->SetPositional(true);
//    light1->SetConeAngle(10);
//    light1->SetFocalPoint(lightFocalPoint[0], lightFocalPoint[1],lightFocalPoint[2]);
//    light1->SetDiffuseColor(1, 0, 0);
//    light1->SetAmbientColor(0, 1, 0);
//    light1->SetSpecularColor(0, 0, 1);
    
//    double lightPosition2[3] = {0, 0, -1};
//    vtkSmartPointer<vtkLight> light2 = vtkSmartPointer<vtkLight>::New();
//    light2->SetLightTypeToSceneLight();
//    light2->SetPosition(lightPosition2[0], lightPosition2[1], lightPosition2[2]);
//    light2->SetPositional(true);
//    light2->SetConeAngle(10);
//    light2->SetFocalPoint(lightFocalPoint[0], lightFocalPoint[1],lightFocalPoint[2]);
//    light2->SetDiffuseColor(1, 0, 0);
//    light2->SetAmbientColor(0, 1, 0);
//    light2->SetSpecularColor(0, 0, 1);
    
    
//    qDebug() << "originalLights number: " << originalLights->GetNumberOfItems();
    
//    vtkSmartPointer<vtkLightActor>lightActor = vtkSmartPointer<vtkLightActor>::New();
//    lightActor->SetLight(light1);
//    render->AddViewProp(lightActor);
    

//    qDebug() << "originalLights number: " << originalLights->GetNumberOfItems();
    
//    vtkSmartPointer<vtkLightActor>lightActor2 = vtkSmartPointer<vtkLightActor>::New();
//    lightActor2->SetLight(light2);
//    render->AddLight(light2);
    

//    qDebug() << "originalLights number: " << originalLights->GetNumberOfItems();
    
//    //*lightFocalPoint
//    vtkSmartPointer<vtkSphereSource>lightFocalPointSphere = vtkSmartPointer<vtkSphereSource>::New();
//    lightFocalPointSphere->SetCenter(lightFocalPoint);
//    lightFocalPointSphere->SetRadius(.1);
//    lightFocalPointSphere->Update();
    
//    vtkSmartPointer<vtkPolyDataMapper>lightFocalPointMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    lightFocalPointMapper->SetInputConnection(lightFocalPointSphere->GetOutputPort());
    
//    vtkSmartPointer<vtkActor>lightfocalPointActor = vtkSmartPointer<vtkActor>::New();
//    lightfocalPointActor->SetMapper(lightFocalPointMapper);
//    lightfocalPointActor->GetProperty()->SetColor(1.0, 1.0, 0.0);
//    render->AddViewProp(lightfocalPointActor);
    
//    //*plane
//    vtkSmartPointer<vtkPlaneSource>planeSource = vtkSmartPointer<vtkPlaneSource>::New();
//    planeSource->SetResolution(100, 100);
//    planeSource->Update();
    
//    vtkSmartPointer<vtkPolyDataMapper>planMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    planMapper->SetInputConnection(planeSource->GetOutputPort());
    
//    vtkSmartPointer<vtkActor>planeActor = vtkSmartPointer<vtkActor>::New();
//    planeActor->SetMapper(planMapper);
//    render->AddActor(planeActor);
    
    
//    vtkSmartPointer<vtkRenderWindowInteractor>interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//    interactor->SetRenderWindow(renwindow);
    
    
//    interactor->Initialize();
//    interactor->Start();
    
    
//    return EXIT_SUCCESS;
//}

