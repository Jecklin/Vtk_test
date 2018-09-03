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
#include <QtAlgorithms>


////***************    2  “观察者”         双view 实现联动    <方法3>         *************************//


//class myInteractorStyle:public vtkInteractorStyleTrackballCamera
//{
//public:

//    static myInteractorStyle* New()
//    {
//        return new myInteractorStyle;
//    }
    
//    void    SetLeftRender(vtkRenderer *render)
//    {
//        this->m_leftRender = render;
//    }
    
//    void    SetRightRender(vtkRenderer *render)
//    {
//        this->m_rightRender = render;
//    }
    
//    void    SetCamera(vtkCamera *camera)
//    {
//        this->m_camera = camera;
//    }

//    void OnMouseWheelForward()
//    {
//        vtkInteractorStyleTrackballCamera::OnMouseWheelForward();
//        this->CameraSynchronous();
//    }

//    void OnMouseWheelBackward()
//    {
//        vtkInteractorStyleTrackballCamera::OnMouseWheelBackward();
//        this->CameraSynchronous();
//    }
    

//    void Rotate()
//    {
//        vtkInteractorStyleTrackballCamera::Rotate();
//        this->CameraSynchronous();
//    }

//    void Spin()
//    {
//        vtkInteractorStyleTrackballCamera::Spin();
//        this->CameraSynchronous();
//    }

//    void Pan()
//    {
//        vtkInteractorStyleTrackballCamera::Pan();
//        this->CameraSynchronous();
//    }

//    void Dolly()
//    {
//        vtkInteractorStyleTrackballCamera::Dolly();
//        this->CameraSynchronous();
//    }
    
    
    
    
//public:
//    void    CameraSynchronous()
//    {
//        vtkCamera *camera = this->GetCurrentRenderer()->GetActiveCamera();
        
//        this->m_leftRender->SetActiveCamera(camera);
//        this->m_leftRender->ResetCameraClippingRange();
        
//        this->m_rightRender->SetActiveCamera(camera);
//        this->m_rightRender->ResetCameraClippingRange();
        
//        this->GetInteractor()->GetRenderWindow()->Render();

//    }

            
//private:
//    vtkRenderer     *m_leftRender;
//    vtkRenderer     *m_rightRender;
//    vtkCamera       *m_camera;

//};


//int main(int, char *[])
//{

//    vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
//    cube->SetXLength(1);
//    cube->SetYLength(1);
//    cube->SetZLength(1);
//    cube->Update();
    
//    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    mapper->SetInputConnection(cube->GetOutputPort());
    
//    vtkSmartPointer<vtkActor> actor1 = vtkSmartPointer<vtkActor>::New();
//    actor1->SetMapper(mapper);
//    actor1->GetProperty()->SetColor(.2, .3, .4);
    
//    vtkSmartPointer<vtkActor> actor2 = vtkSmartPointer<vtkActor>::New();
//    actor2->SetMapper(mapper);
//    actor2->GetProperty()->SetColor(.4, .5, .6);

    
//    double leftViewStation[4] = {0.0, 0.0, 0.4, 1.0};
//    double rightViewStation[4] = {0.4, 0.0, 1.0, 1.0};
    
//    vtkSmartPointer<vtkRenderer>leftRender = vtkSmartPointer<vtkRenderer>::New();
    
//    leftRender->AddActor(actor1);
//    leftRender->SetBackground(.6, .5, .4);
//    leftRender->SetViewport(leftViewStation);


//    vtkSmartPointer<vtkRenderer>rightRender = vtkSmartPointer<vtkRenderer>::New();
//    rightRender->AddActor(actor2);
//    rightRender->SetBackground(.2, .4, .6);
//    rightRender->SetViewport(rightViewStation);

//    vtkSmartPointer<vtkCamera> camera = vtkSmartPointer<vtkCamera>::New();
//    camera->SetPosition(4, 4, 4);
//    rightRender->SetActiveCamera(camera);
//    leftRender->SetActiveCamera(camera);
    
//    vtkSmartPointer<vtkRenderWindow>renwindow = vtkSmartPointer<vtkRenderWindow>::New();
//    renwindow->AddRenderer(leftRender);
//    renwindow->AddRenderer(rightRender);
//    renwindow->SetSize(600, 300);
//    renwindow->Render();
    

    
//    vtkSmartPointer<vtkRenderWindowInteractor>interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    
    
//    vtkSmartPointer<myInteractorStyle> style = vtkSmartPointer<myInteractorStyle>::New();
//    style->SetLeftRender(leftRender);
//    style->SetRightRender(rightRender);
//    style->SetCamera(camera);
    
//    interactor->SetInteractorStyle(style);
    
    
//    renwindow->SetInteractor(interactor);
    
//    interactor->Initialize();
//    interactor->Start();
    
    
//    return EXIT_SUCCESS;
//}

///// ********************   获得事件差值  **********************///

//****   动左边，改右边  ***//
int main(int, char *[])
{
    //***创建一个正方体的基本信息
    vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    vtkSmartPointer<vtkRenderer>render = vtkSmartPointer<vtkRenderer>::New();  
    vtkSmartPointer<vtkRenderWindow>renwindow = vtkSmartPointer<vtkRenderWindow>::New();    
    vtkSmartPointer<vtkRenderWindowInteractor>interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
    interactor->SetInteractorStyle(style);
    
    cube->Update();
    mapper->SetInputConnection(cube->GetOutputPort()); 
    actor->SetMapper(mapper);
    render->AddActor(actor);
    renwindow->AddRenderer(render);
    interactor->SetRenderWindow(renwindow);
 
    //***下面开始是获得坐标的方式
    
    //获得event 的world坐标
    int dis_int[3];
    interactor->GetEventPosition(dis_int);
    
    double dis_double[3] = {dis_int[0],dis_int[1],dis_int[2]};    
    render->SetDisplayPoint(dis_double);
    render->DisplayToWorld();
    
    double event_world[4];
    render->GetWorldPoint(event_world);
    
    //获得last event 的 world 坐标
    int dis_int2[3];
    interactor->GetLastEventPosition(dis_int2);
    
    double dis_double2[3] = {dis_int2[0],dis_int2[1],dis_int2[2]};    
    render->SetDisplayPoint(dis_double2);
    render->DisplayToWorld();
    
    double lastEvent_world[4];
    render->GetWorldPoint(lastEvent_world);
    
    //获得差值
    double index[3];
    for (int i = 0; i < 3; ++i)
    {
        index[i] = lastEvent_world[i] - event_world[i];
    }


/// ***********                  相机差值               ****************** ///
    vtkCamera *leftCamera = m_leftRender->GetActiveCamera();
    vtkCamera *rightCamera = m_rightRender->GetActiveCamera();
    vtkCamera *camera = this->GetCurrentRenderer()->GetActiveCamera();
    
    //当前相机状态
    double *act_position     = camera->GetPosition();

    
    //上次左相机
    double *left_position     = this->m_leftCamera->GetPosition();

    
    //上次右相机
    double *right_position     = this->m_rightCamera->GetPosition();

    
    //要设置的值
    double position[3];

    
    
    for (int i = 0; i < 3; ++i)
    {                
        position[i]   = act_position[i]     - left_position[i]         + right_position[i];
        
    }
    
    
    interactor->Initialize();
    interactor->Start();
    
    return EXIT_SUCCESS;
    
}


////***************    2  “观察者”         双view 实现联动    <方法2>         *************************//


//class myInteractorStyle:public vtkInteractorStyleTrackballCamera
//{
//public:

//    static myInteractorStyle* New()
//    {
//        return new myInteractorStyle;
//    }
    
//    void    SetLeftRender(vtkRenderer *render)
//    {
//        this->m_leftRender = render;
//    }
    
//    void    SetRightRender(vtkRenderer *render)
//    {
//        this->m_rightRender = render;
//    }
    

//    void OnMouseWheelForward()
//    {
//        vtkInteractorStyleTrackballCamera::OnMouseWheelForward();
//        this->CameraSynchronous();
//    }

//    void OnMouseWheelBackward()
//    {
//        vtkInteractorStyleTrackballCamera::OnMouseWheelBackward();
//        this->CameraSynchronous();
//    }
    

//    void Rotate()
//    {
//        vtkInteractorStyleTrackballCamera::Rotate();
//        this->CameraSynchronous();
//    }

//    void Spin()
//    {
//        vtkInteractorStyleTrackballCamera::Spin();
//        this->CameraSynchronous();
//    }

//    void Pan()
//    {
//        vtkInteractorStyleTrackballCamera::Pan();
//        this->CameraSynchronous();
//    }

//    void Dolly()
//    {
//        vtkInteractorStyleTrackballCamera::Dolly();
//        this->CameraSynchronous();
//    }
    

////    void    CameraSynchronous()
////    {
////        vtkCamera *leftCamera = m_leftRender->GetActiveCamera();
////        vtkCamera *rightCamera = m_rightRender->GetActiveCamera();
        
////        //获取窗口大小
////        int *winSize = this->GetInteractor()->GetRenderWindow()->GetSize();
        
////        //获取事件窗口位置
////        int eventStation[3];
////        this->GetInteractor()->GetEventPosition(eventStation);
        
////        if (eventStation[0] < winSize[0]/2)
////        {
////            rightCamera->SetPosition(leftCamera->GetPosition());
////            rightCamera->SetFocalPoint(leftCamera->GetFocalPoint());
////            rightCamera->SetViewUp(leftCamera->GetViewUp());
////            m_rightRender->ResetCameraClippingRange();
        
////        }
////        else
////        {
////            leftCamera->SetPosition(rightCamera->GetPosition());
////            leftCamera->SetViewUp(rightCamera->GetViewUp());
////            leftCamera->SetFocalPoint(rightCamera->GetFocalPoint());
////            m_leftRender->ResetCameraClippingRange();
                       
////        }
        
        
////        this->GetInteractor()->GetRenderWindow()->Render();
////    }
    
    
    
//private:
//    vtkRenderer     *m_leftRender;
//    vtkRenderer     *m_rightRender;



//};


//int main(int, char *[])
//{

//    vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
//    cube->SetCenter(0, 0, 0);
//    cube->SetXLength(1);
//    cube->SetYLength(1);
//    cube->SetZLength(1);
//    cube->Update();
    
//    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    mapper->SetInputConnection(cube->GetOutputPort());
    
//    vtkSmartPointer<vtkActor> actor1 = vtkSmartPointer<vtkActor>::New();
//    actor1->SetMapper(mapper);
//    actor1->GetProperty()->SetColor(.2, .3, .4);
    
//    vtkSmartPointer<vtkActor> actor2 = vtkSmartPointer<vtkActor>::New();
//    actor2->SetMapper(mapper);
//    actor2->GetProperty()->SetColor(.4, .5, .6);

    
//    double leftViewStation[4] = {0.0, 0.0, 0.4, 1.0};
//    double rightViewStation[4] = {0.4, 0.0, 1.0, 1.0};
    
//    vtkSmartPointer<vtkRenderer>leftRender = vtkSmartPointer<vtkRenderer>::New();
    
//    leftRender->AddActor(actor1);
//    leftRender->SetBackground(.6, .5, .4);
//    leftRender->SetViewport(leftViewStation);

//    vtkSmartPointer<vtkRenderer>rightRender = vtkSmartPointer<vtkRenderer>::New();
//    rightRender->AddActor(actor2);
//    rightRender->SetBackground(.2, .4, .6);
//    rightRender->SetViewport(rightViewStation);
    
    
//    vtkSmartPointer<vtkRenderWindow>renwindow = vtkSmartPointer<vtkRenderWindow>::New();
//    renwindow->AddRenderer(leftRender);
//    renwindow->AddRenderer(rightRender);
//    renwindow->SetSize(600, 300);
//    renwindow->Render();
    
    
    
//    vtkSmartPointer<vtkRenderWindowInteractor>interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
      
    
//    vtkSmartPointer<myInteractorStyle> style = vtkSmartPointer<myInteractorStyle>::New();
//    style->SetLeftRender(leftRender);
//    style->SetRightRender(rightRender);
//    interactor->SetInteractorStyle(style);
    
    
//    renwindow->SetInteractor(interactor);
    
//    interactor->Initialize();
//    interactor->Start();
    
    
//    return EXIT_SUCCESS;
//}


//***************    2  “观察者”         双view 实现联动    <方法一>      *************************//

//class myCallbackFunc:public vtkCommand
//{
//public:
//    static  myCallbackFunc *New()
//    {
//        return new myCallbackFunc;
//    }
    
//    void SetLeftRender(vtkRenderer *leftRender)
//    {
//        this->m_leftRender = leftRender;
//    }
//    void SetRightRender(vtkRenderer *rightRender)
//    {
//        this->m_rightRender = rightRender;
//    }
    
  
//    virtual void Execute(vtkObject *caller, unsigned long eventId, void* callData)
//    {
//        vtkCamera *camera = reinterpret_cast<vtkCamera*>(caller);
//        vtkCamera *leftCamera = m_leftRender->GetActiveCamera();
//        vtkCamera *rightCamera = m_rightRender->GetActiveCamera();
 
//        double *act_position     = camera->GetPosition();
//        double *act_FocalPoint   = camera->GetFocalPoint();
//        double *act_ViewUp       = camera->GetViewUp();
      
//        if (    (isSame(act_position, leftCamera->GetPosition()))
//              &&(isSame(act_FocalPoint, leftCamera->GetFocalPoint()))
//              &&(isSame(act_ViewUp,leftCamera->GetViewUp())))
//        {
//            rightCamera->SetPosition(act_position);
//            rightCamera->SetFocalPoint(act_FocalPoint);
//            rightCamera->SetViewUp(act_ViewUp);
//            this->m_rightRender->ResetCameraClippingRange();
//        }
//        else
//        {
//            leftCamera->SetPosition(act_position);
//            leftCamera->SetFocalPoint(act_FocalPoint);
//            leftCamera->SetViewUp(act_ViewUp);
//            this->m_leftRender->ResetCameraClippingRange();
//        }
                               
//    }
    
//private:
    
//    //计算获取到的相机是否为leftRender或rightRender的相机
//    static bool isSame(double *value0, double *value1) {
//        bool result = true;
//        for (int idx = 0; idx != 3; ++idx) {
//            result = result && qFuzzyCompare(value0[idx], value1[idx]);
//        }
//        return result;
//    }
    
//private:
//    //此处为双view，若为多view，可设置数组，通过提供参数进行设置
//    vtkRenderer     *m_leftRender;
//    vtkRenderer     *m_rightRender;
    
//};


//int main(int, char *[])
//{

//    vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
//    cube->SetCenter(1, 1, 1);
//    cube->Update();
    
//    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    mapper->SetInputConnection(cube->GetOutputPort());
    
//    vtkSmartPointer<vtkActor> actor1 = vtkSmartPointer<vtkActor>::New();
//    actor1->SetMapper(mapper);
//    actor1->GetProperty()->SetColor(.2, .3, .4);
    
//    vtkSmartPointer<vtkActor> actor2 = vtkSmartPointer<vtkActor>::New();
//    actor2->SetMapper(mapper);
//    actor2->GetProperty()->SetColor(.4, .5, .6);

    
//    double leftViewStation[4] = {0.0, 0.0, 0.4, 1.0};
//    double rightViewStation[4] = {0.4, 0.0, 1.0, 1.0};
    
//    vtkSmartPointer<vtkRenderer>leftRender = vtkSmartPointer<vtkRenderer>::New();
    
//    leftRender->AddActor(actor1);
//    leftRender->SetBackground(.6, .5, .4);
//    leftRender->SetViewport(leftViewStation);

//    vtkSmartPointer<vtkRenderer>rightRender = vtkSmartPointer<vtkRenderer>::New();
//    rightRender->AddActor(actor2);
//    rightRender->SetBackground(.2, .4, .6);
//    rightRender->SetViewport(rightViewStation);
    
    
//    vtkSmartPointer<vtkRenderWindow>renwindow = vtkSmartPointer<vtkRenderWindow>::New();
//    renwindow->AddRenderer(leftRender);
//    renwindow->AddRenderer(rightRender);
//    renwindow->SetSize(600, 300);
//    renwindow->Render();
    
    
    
//    vtkSmartPointer<vtkRenderWindowInteractor>interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    
//    vtkSmartPointer<myCallbackFunc>callback = vtkSmartPointer<myCallbackFunc>::New();
    
//    callback->SetLeftRender(leftRender);
//    callback->SetRightRender(rightRender);

//    leftRender->GetActiveCamera()->AddObserver(vtkCommand::ModifiedEvent,callback);
//    rightRender->GetActiveCamera()->AddObserver(vtkCommand::ModifiedEvent,callback);
    
    
//    //用户通过控制相机对物体旋转、放大、缩小等操作。
//    vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
//    interactor->SetInteractorStyle(style);
    
    
//    renwindow->SetInteractor(interactor);
    
//    interactor->Initialize();
//    interactor->Start();
    
    
//    return EXIT_SUCCESS;
//}


