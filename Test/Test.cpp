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
//#include <vtkCameraActor.h>
//#include <QDebug>
//#include <vtkRendererCollection.h>
//#include <vtkInformation.h>

//#include <vtkDataSetMapper.h>
//#include <vtkPolyData.h>
//#include <vtkCellPicker.h>
//#include <vtkIdTypeArray.h>
//#include <vtkSelectionNode.h>
//#include <vtkSelection.h>
//#include <vtkExtractSelection.h>
//#include <vtkUnstructuredGrid.h>
//#include <vtkSphereSource.h>
//#include <vtkLight.h>
//#include <vtkLightCollection.h>
//#include <vtkLightActor.h>
//#include <vtkSphereSource.h>
//#include <vtkPlaneSource.h>
//#include <vtkCellLocator.h>
//#include <vtkDoubleArray.h>
//#include <vtkPointData.h>
//#include <vector>
//#include <vtkAnimationCue.h>
//#include <vtkAnimationScene.h>
//#include <vtkConeSource.h>






////***************    2  “观察者”         双view 实现联动    <方法2>         *************************//


class myInteractorStyle:public vtkInteractorStyleTrackballCamera
{
public:

    static myInteractorStyle* New()
    {
        return new myInteractorStyle;
    }
    
    void    SetLeftRender(vtkRenderer *render)
    {
        this->m_leftRender = render;
    }
    
    void    SetRightRender(vtkRenderer *render)
    {
        this->m_rightRender = render;
    }
       
    void    OnMouseMove()
    {
        vtkInteractorStyleTrackballCamera::OnMouseMove();
        this->CameraSynchronous();
    }
   
    void OnLeftButtonDown()
    {
        vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
        this->CameraSynchronous();
    }

    void OnLeftButtonUp()
    {
        vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
        this->CameraSynchronous();
    }

    void OnMiddleButtonDown()
    {
        vtkInteractorStyleTrackballCamera::OnMiddleButtonDown();
        this->CameraSynchronous();
    }

    void OnMiddleButtonUp()
    {
        vtkInteractorStyleTrackballCamera::OnMiddleButtonUp();
        this->CameraSynchronous();
    }

    void OnRightButtonDown()
    {
        vtkInteractorStyleTrackballCamera::OnRightButtonDown();
        this->CameraSynchronous();
    }

    void OnRightButtonUp()
    {
        vtkInteractorStyleTrackballCamera::OnRightButtonUp();
        this->CameraSynchronous();
    }

    void OnMouseWheelForward()
    {
        vtkInteractorStyleTrackballCamera::OnMouseWheelForward();
        this->CameraSynchronous();
    }

    void OnMouseWheelBackward()
    {
        vtkInteractorStyleTrackballCamera::OnMouseWheelBackward();
        this->CameraSynchronous();
    }
    
    
    
    void Rotate()
    {
        vtkInteractorStyleTrackballCamera::Rotate();
        this->CameraSynchronous();
    }

    void Spin()
    {
        vtkInteractorStyleTrackballCamera::Spin();
        this->CameraSynchronous();
    }

    void Pan()
    {
        vtkInteractorStyleTrackballCamera::Pan();
        this->CameraSynchronous();
    }

    void Dolly()
    {
        vtkInteractorStyleTrackballCamera::Dolly();
        this->CameraSynchronous();
    }
    
    
    
    
private:
    void    CameraSynchronous()
    {
        vtkCamera *leftCamera = m_leftRender->GetActiveCamera();
        vtkCamera *rightCamera = m_rightRender->GetActiveCamera();
        
        //获取窗口大小
        int *winSize = this->GetInteractor()->GetRenderWindow()->GetSize();
        
        //获取事件窗口位置
        int eventStation[3];
        this->GetInteractor()->GetEventPosition(eventStation);
        
        if (eventStation[0] < winSize[0]/2)
        {
            rightCamera->SetPosition(leftCamera->GetPosition());
            rightCamera->SetFocalPoint(leftCamera->GetFocalPoint());
            rightCamera->SetViewUp(leftCamera->GetViewUp());
            m_rightRender->ResetCameraClippingRange();
        
        }
        else
        {
            leftCamera->SetPosition(rightCamera->GetPosition());
            leftCamera->SetViewUp(rightCamera->GetViewUp());
            leftCamera->SetFocalPoint(rightCamera->GetFocalPoint());
            m_leftRender->ResetCameraClippingRange();
                       
        }
        
        
        this->GetInteractor()->GetRenderWindow()->Render();
    }
    
private:
    vtkRenderer     *m_leftRender;
    vtkRenderer     *m_rightRender;

};


int main(int, char *[])
{

    vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
    cube->SetCenter(0, 0, 0);
    cube->SetXLength(1);
    cube->SetYLength(1);
    cube->SetZLength(1);
    cube->Update();
    
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(cube->GetOutputPort());
    
    vtkSmartPointer<vtkActor> actor1 = vtkSmartPointer<vtkActor>::New();
    actor1->SetMapper(mapper);
    actor1->GetProperty()->SetColor(.2, .3, .4);
    
    vtkSmartPointer<vtkActor> actor2 = vtkSmartPointer<vtkActor>::New();
    actor2->SetMapper(mapper);
    actor2->GetProperty()->SetColor(.4, .5, .6);

    
    double leftViewStation[4] = {0.0, 0.0, 0.5, 1.0};
    double rightViewStation[4] = {0.5, 0.0, 1.0, 1.0};
    
    vtkSmartPointer<vtkRenderer>leftRender = vtkSmartPointer<vtkRenderer>::New();
    
    leftRender->AddActor(actor1);
    leftRender->SetBackground(.6, .5, .4);
    leftRender->SetViewport(leftViewStation);

    vtkSmartPointer<vtkRenderer>rightRender = vtkSmartPointer<vtkRenderer>::New();
    rightRender->AddActor(actor2);
    rightRender->SetBackground(.2, .4, .6);
    rightRender->SetViewport(rightViewStation);
    
    
    vtkSmartPointer<vtkRenderWindow>renwindow = vtkSmartPointer<vtkRenderWindow>::New();
    renwindow->AddRenderer(leftRender);
    renwindow->AddRenderer(rightRender);
    renwindow->SetSize(600, 300);
    renwindow->Render();
    
    
    
    vtkSmartPointer<vtkRenderWindowInteractor>interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
      
    
    vtkSmartPointer<myInteractorStyle> style = vtkSmartPointer<myInteractorStyle>::New();
    style->SetLeftRender(leftRender);
    style->SetRightRender(rightRender);
    interactor->SetInteractorStyle(style);
    
    
    renwindow->SetInteractor(interactor);
    
    interactor->Initialize();
    interactor->Start();
    
    
    return EXIT_SUCCESS;
}



////***************    2  “观察者”         双view 实现联动    <方法一>      *************************//
/// 
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

    
//    double leftViewStation[4] = {0.0, 0.0, 0.5, 1.0};
//    double rightViewStation[4] = {0.5, 0.0, 1.0, 1.0};
    
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


////////////////////****************************************//////////////////////////////

////////////////////****************************************//////////////////////////////

////////////////////****************************************//////////////////////////////




//////***************   7  “动画”  AnimateActors    *************************//

//class ActorAnimator
//{
//public:
//    ActorAnimator()
//    {
//        this->m_actor = 0;
//        this->m_observer = AnimationCueObserver::New();
//        this->m_observer->m_animator = this;
//        this->m_startPosition.resize(3);
//        this->m_startPosition.insert(m_startPosition.begin(), 3, 0.0);
//        this->m_endPosition.resize(3);
//        this->m_endPosition.insert(m_endPosition.begin(), 3, 0.5);
//    }
    
//    ~ActorAnimator()
//    {
//        if (this->m_actor)
//        {
//            this->m_actor->UnRegister(0);
//            this->m_actor = 0;
//        }
//        this->m_observer->UnRegister(0);
//    }
    
//    void SetActor(vtkActor *actor)
//    {
//        if (this->m_actor)
//        {
//            this->m_actor->UnRegister(0);
//            this->m_actor = 0;
//        }
//        this->m_actor = actor;
//        this->m_actor->Register(0);
//    }
    
//    void SetStartPosition(std::vector<double> position)
//    {
//        this->m_startPosition = position;
//    }
    
//    void SetEndPosition(std::vector<double> position)
//    {
//        this->m_endPosition = position;
//    }
    
//    void AddObserversToCue(vtkAnimationCue *cue)
//    {
//        cue->AddObserver(vtkCommand::StartAnimationCueEvent, this->m_observer);
//        cue->AddObserver(vtkCommand::EndAnimationCueEvent, this->m_observer);
//        cue->AddObserver(vtkCommand::AnimationCueTickEvent, this->m_observer);
//    }
    
//    void Start(vtkAnimationCue::AnimationCueInfo *vtkNotUsed(info))//vtkNotUsed这个宏用来屏蔽编译器位使用参数的警告
//    {
//        this->m_actor->SetPosition(m_startPosition[0], m_startPosition[1], m_startPosition[2]);
//    }
    
//    void Tick(vtkAnimationCue::AnimationCueInfo *info)
//    {
//        double t = (info->AnimationTime - info->StartTime)/(info->EndTime - info->StartTime);
//        double position[3];
//        for (int i = 0; i < 3; ++i)
//        {
//            position[i] = this->m_startPosition[i] + (this->m_endPosition[i] - this->m_startPosition[i])*t;
//        }
//        this->m_actor->SetPosition(position);
        
//    }
    
//    void End(vtkAnimationCue::AnimationCueInfo *vtkNotUsed(info))
//    {
//        this->m_actor->SetPosition(m_endPosition[0], m_endPosition[1], m_endPosition[2]);
//    }
    
//protected:
//    class AnimationCueObserver:public vtkCommand
//    {
//    public:
//        static AnimationCueObserver *New()
//        {
//            return new AnimationCueObserver;
//        }
        
//        virtual void Execute(vtkObject *vtkNotUsed(caller), unsigned long eventId, void *callData)
//        {
//            if (this->m_animator != 0)
//            {
//                vtkAnimationCue::AnimationCueInfo *info = static_cast<vtkAnimationCue::AnimationCueInfo*>(callData);
//                switch(eventId)
//                {
//                case vtkCommand::StartAnimationCueEvent:
//                    this->m_animator->Start(info);
//                    break;
//                case vtkCommand::EndAnimationCueEvent:
//                    this->m_animator->End(info);
//                    break;
//                case vtkCommand::AnimationCueTickEvent:
//                    this->m_animator->Tick(info);
//                    break;               
//                }
//            }
//        }
        
//        AnimationCueObserver()
//        {
//            this->m_animator = 0;
//        }
        
//    public:
//        ActorAnimator   *m_animator;
        
//    };
    
    
//protected:
//    vtkActor                *m_actor;
//    AnimationCueObserver    *m_observer;
//    std::vector<double>     m_startPosition;
//    std::vector<double>     m_endPosition;    
//};


//class AnimationSceneObserver : public vtkCommand
//{
//public:
//    static AnimationSceneObserver *New()
//    {
//        return new AnimationSceneObserver;
//    }
    
//    void SetRenderWindow(vtkRenderWindow *renwin)
//    {
//        if (this->m_renWindow)
//        {
//            this->m_renWindow->UnRegister(this);
//        }
//        this->m_renWindow = renwin;
//        this->m_renWindow->Register(this);
//    }
    
//    virtual void Execute(vtkObject *vtkNotUsed(caller), unsigned long eventId, void *vtkNotUsed(callData))
//    {
//        if (this->m_renWindow != 0)
//        {
//            switch(eventId)
//            {
//            case vtkCommand::AnimationCueTickEvent:
//                this->m_renWindow->Render();
//                break;
//            }
//        }
//    }
    
    
//protected:
//    AnimationSceneObserver()
//    {
//        this->m_renWindow = 0;
//    }
    
//    ~AnimationSceneObserver()
//    {
//        if (this->m_renWindow != 0)
//        {
//            this->m_renWindow->UnRegister(this);
//            this->m_renWindow = 0;
//        }
//    }
    
//    vtkRenderWindow *m_renWindow;
//};

//int main(int argc, char *argv[])
//{
//    vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
//    vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
//    sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
//    sphereActor->SetMapper(sphereMapper);
    
//    vtkSmartPointer<vtkConeSource> coneSource = vtkSmartPointer<vtkConeSource>::New();
//    vtkSmartPointer<vtkPolyDataMapper> coneMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    vtkSmartPointer<vtkActor> coneActor = vtkSmartPointer<vtkActor>::New();
//    coneMapper->SetInputConnection(coneSource->GetOutputPort());
//    coneActor->SetMapper(coneMapper);
    
//    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
//    vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();
//    vtkSmartPointer<vtkRenderWindowInteractor> interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    
//    render->AddActor(sphereActor);
//    render->AddActor(coneActor);
//    renWin->AddRenderer(render);
//    interactor->SetRenderWindow(renWin);
    
//    //动画场景
//    vtkSmartPointer<vtkAnimationScene> scene = vtkSmartPointer<vtkAnimationScene>::New();
    
//    scene->SetModeToSequence(); //场景mode为序列模式
//    scene->SetLoop(0);          //动画不循环，默认为此值
//    scene->SetFrameRate(5);     //每秒读帧数
//    scene->SetStartTime(0);
//    scene->SetEndTime(20);
    
//    vtkSmartPointer<AnimationSceneObserver> sceneObserver = vtkSmartPointer<AnimationSceneObserver>::New();
//    sceneObserver->SetRenderWindow(renWin);
//    scene->AddObserver(vtkCommand::AnimationCueTickEvent, sceneObserver);
    
//    vtkSmartPointer<vtkAnimationCue> cue1 = vtkSmartPointer<vtkAnimationCue>::New();
//    vtkSmartPointer<vtkAnimationCue> cue2 = vtkSmartPointer<vtkAnimationCue>::New();
    
//    cue1->SetStartTime(5);
//    cue1->SetEndTime(23);
    
//    cue2->SetStartTime(1);
//    cue2->SetEndTime(10);
    
//    scene->AddCue(cue1);
//    scene->AddCue(cue2);
    
//    ActorAnimator animateSphere;
//    ActorAnimator animateCone;
    
//    animateSphere.SetActor(sphereActor);
//    animateSphere.AddObserversToCue(cue1);
    
//    std::vector<double> coneEndStation(3);
//    coneEndStation[0] = -1;
//    coneEndStation[1] = -1;
//    coneEndStation[2] = -1;
    
//    animateCone.SetEndPosition(coneEndStation);
//    animateCone.SetActor(coneActor);
//    animateCone.AddObserversToCue(cue2);
    
//    renWin->Render();
//    render->ResetCamera();          
//    render->GetActiveCamera()->Dolly(0.5);      //伸缩镜头
//    render->ResetCameraClippingRange();         //重置摄像机剪裁范围
    
//    scene->Play();
//    scene->Stop();
    
    
//    interactor->Initialize();
//    interactor->Start();
    
    
    
    
    
    
//    return EXIT_SUCCESS;
//}







////***************   6  “获取”  点法线    *************************//


//int main(int, char*[])
//{
//    vtkSmartPointer<vtkPoints>points = vtkSmartPointer<vtkPoints>::New();
//    points->InsertNextPoint(1.0, 0.0, 0.0);
//    points->InsertNextPoint(0.0, 0.0, 0.0);
//    points->InsertNextPoint(1.0, 1.0, 0.0);
    
//    vtkSmartPointer<vtkPolyData>polyData = vtkSmartPointer<vtkPolyData>::New();
//    polyData->SetPoints(points);
    
//     //设置点法线
//    vtkSmartPointer<vtkDoubleArray> normalsArray = vtkSmartPointer<vtkDoubleArray>::New();
//    normalsArray->SetNumberOfComponents(3);//3d normals
//    normalsArray->SetNumberOfTuples(polyData->GetNumberOfPoints());//tuple:元祖

//    //构造法向量
//    double pN1[3] = {1.0, 0.0, 0.0};
//    double pN2[3] = {0.0, 1.0, 0.0};
//    double pN3[3] = {0.0, 0.0, 1.0};
    
//    normalsArray->SetTuple(0, pN1);
//    normalsArray->SetTuple(1, pN2);
//    normalsArray->SetTuple(2, pN3);
    
//    //将法线添加进polydata中
//    polyData->GetPointData()->SetNormals(normalsArray);
    
//    //通过设置数据打印
//    qDebug() <<"NumberOfTuples:" << normalsArray->GetNumberOfTuples();
//    for(vtkIdType i = 0; i < normalsArray->GetNumberOfTuples(); i++)
//    {
//      double pN[3];
//      normalsArray->GetTuple(i, pN); //Tuple：元祖
//      qDebug() << i <<":" << pN[0] << pN[1] << pN[2];
//    }
    
//    //取出数据再次打印
//    vtkSmartPointer<vtkDoubleArray>arrayRetrieved = vtkDoubleArray::SafeDownCast(polyData->GetPointData()->GetNormals());
//    if (arrayRetrieved)
//    {    
//        qDebug() <<"NumberOfTuples:" << normalsArray->GetNumberOfTuples();
//        for(vtkIdType i = 0; i < normalsArray->GetNumberOfTuples(); i++)
//        {
//          double pN[3];
//          normalsArray->GetTuple(i, pN); //Tuple：元祖
//          qDebug() << i <<":" << pN[0] << pN[1] << pN[2];
//        }
        
//    }
//    else
//    {
//        qDebug() << "No point normals.";
//    }
    

//}




////***************   5  “获取”      实现：获取最近点    *************************//



//int main(int, char *[])
//{  
//  vtkSmartPointer<vtkCubeSource>cubeSource = vtkSmartPointer<vtkCubeSource>::New();
//  cubeSource->SetCenter(0, 0, 0);
//  cubeSource->SetXLength(1);
//  cubeSource->SetYLength(1);
//  cubeSource->SetZLength(1);
//  cubeSource->Update();
  
//  vtkSmartPointer<vtkCellLocator>cellLocator2 = vtkSmartPointer<vtkCellLocator>::New();
//  cellLocator2->SetDataSet(cubeSource->GetOutput());
//  cellLocator2->BuildLocator();
  
//  double testPoint3[3] = {1, 0, 0};
//  double closestPoint3[3];  //最近点的坐标将返回到这里
//  double closestPointDist3; //到最近点的平方距离会返回到这里
//  vtkIdType cellId3;        //包含最近点的单元ID将返回到这里
//  int subId3;               //这种方法很少使用，可能只在三角形中使用
  
//  cellLocator2->FindClosestPoint(testPoint3, closestPoint3, cellId3, subId3, closestPointDist3);
  
//  qDebug() << "closestPoint3: " << closestPoint3[0] << closestPoint3[1] << closestPoint3[2];
//  qDebug() << "closestPointDist3: " << closestPointDist3;
//  qDebug() << "cellId3: " << cellId3;//此处获取为1
//  qDebug() << "subId3: " << subId3; //此处获取为0

  
//  return EXIT_SUCCESS;
//}



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






////***************  3   “拾取”      实现：正方体选取一个面    *************************//
/// 
//class MouseInteractorStyle:public vtkInteractorStyleTrackballCamera
//{
//public:
//    static MouseInteractorStyle *New();
    
//    MouseInteractorStyle()
//    {
//        m_selectedMapper = vtkSmartPointer<vtkDataSetMapper>::New();
//        m_selectedActor = vtkSmartPointer<vtkActor>::New();
//    }
    
//    virtual void OnLeftButtonDown()
//    {
//        int *eventPosition = this->GetInteractor()->GetEventPosition();//事件坐标
//        vtkSmartPointer<vtkCellPicker> picker = vtkSmartPointer<vtkCellPicker>::New();
//        picker->SetTolerance(0.0005);
//        picker->Pick(eventPosition[0], eventPosition[1], eventPosition[2], this->GetDefaultRenderer());
        
//        double *worldPosition = picker->GetPickPosition();              //全局坐标
//        if (picker->GetCellId() != -1) //拾取到了单元格
//        {
//            vtkSmartPointer<vtkIdTypeArray> ids = vtkSmartPointer<vtkIdTypeArray>::New();
//            ids->SetNumberOfComponents(1); //设置组件尺寸
//            ids->InsertNextValue(picker->GetCellId());
            
//            vtkSmartPointer<vtkSelectionNode>selectionNode = vtkSmartPointer<vtkSelectionNode>::New();//选择节点
//            selectionNode->SetFieldType(vtkSelectionNode::CELL);
//            selectionNode->SetContentType(vtkSelectionNode::INDICES);
//            selectionNode->SetSelectionList(ids);
            
//            vtkSmartPointer<vtkSelection>selection = vtkSmartPointer<vtkSelection>::New();//选择
//            selection->AddNode(selectionNode);
            
//            vtkSmartPointer<vtkExtractSelection>extractSelection = vtkSmartPointer<vtkExtractSelection>::New();//提取选择
                 
//            extractSelection->SetInputData(0, this->m_polyData);    
//            extractSelection->SetInputData(1, selection);
//            extractSelection->Update(); //setInputData()不建立管道，需手动更新
            
//            vtkSmartPointer<vtkUnstructuredGrid>selected = vtkSmartPointer<vtkUnstructuredGrid>::New();//任何单元格类型的任何组合
//            selected->ShallowCopy(extractSelection->GetOutput());
            
//            m_selectedMapper->SetInputData(selected);
            
//            m_selectedActor->SetMapper(m_selectedMapper);
//            m_selectedActor->GetProperty()->EdgeVisibilityOn();
//            m_selectedActor->GetProperty()->SetEdgeColor(1, 0, 0);
//            m_selectedActor->GetProperty()->SetLineWidth(3);
            
//            this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(m_selectedActor);  
            
//        }
        
//        vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
        
//    }
    
//    vtkSmartPointer<vtkPolyData>        m_polyData;
//    vtkSmartPointer<vtkDataSetMapper>   m_selectedMapper;
//    vtkSmartPointer<vtkActor>           m_selectedActor;
//};


//vtkStandardNewMacro(MouseInteractorStyle);


//int main(int, char *[])
//{
//    vtkSmartPointer<vtkCubeSource> cube = vtkSmartPointer<vtkCubeSource>::New();
//    cube->SetCenter(1, 1, 1);
//    cube->Update();
    
//    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
//    mapper->SetInputConnection(cube->GetOutputPort());
    
//    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
//    actor->SetMapper(mapper);
//    actor->GetProperty()->SetColor(0.2, 0.3, 0.4);
    
//    vtkSmartPointer<vtkRenderer> render = vtkSmartPointer<vtkRenderer>::New();
//    render->AddActor(actor);
//    render->SetBackground(0.4, 0.5, 0.6);
    
//    vtkSmartPointer<vtkRenderWindow>renwindow = vtkSmartPointer<vtkRenderWindow>::New();
//    renwindow->AddRenderer(render);
//    renwindow->SetSize(600, 600);
    
    
//    vtkSmartPointer<vtkRenderWindowInteractor>interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
//    interactor->SetRenderWindow(renwindow);
    
    
    
    
//    vtkSmartPointer<MouseInteractorStyle>style = vtkSmartPointer<MouseInteractorStyle>::New();
//    style->SetDefaultRenderer(render);
//    style->m_polyData = cube->GetOutput();
//    interactor->SetInteractorStyle(style);

    
//    interactor->Initialize();
//    interactor->Start();
    
    
//    return EXIT_SUCCESS;
//}







////***************    2  “观察者”         双view 实现联动          *************************//
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
        
//        double *buff = nullptr;
//        double *tmp = nullptr;
        
//        //set camera position
//        buff = camera->GetPosition();
//        tmp = leftCamera->GetPosition();
//        if (isSame(buff, tmp)) {
//            ;
//        } else {
//            leftCamera->SetPosition(buff);
//        }
//        tmp = rightCamera->GetPosition();
//        if (isSame(buff, tmp)) {
//            ;
//        } else {
//            rightCamera->SetPosition(buff);
//        }
        
//        //set camera focalPoint
//        buff = camera->GetFocalPoint();
//        tmp = leftCamera->GetFocalPoint();
//        if (isSame(buff, tmp)) {
//            ;
//        } else {
//            leftCamera->SetFocalPoint(buff);
//        }
//        tmp = rightCamera->GetFocalPoint();
//        if (isSame(buff, tmp)) {
//            ;
//        } else {
//            rightCamera->SetFocalPoint(buff);
//        }
        
//        //set camera viewUp
//        buff = camera->GetViewUp();
//        tmp = leftCamera->GetViewUp();
//        if (isSame(buff, tmp)) {
//            ;
//        } else {
//            leftCamera->SetViewUp(buff);
//        }
//        tmp = rightCamera->GetViewUp();
//        if (isSame(buff, tmp)) {
//            ;
//        } else {
//            rightCamera->SetViewUp(buff);
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
//    vtkRenderer *m_leftRender;
//    vtkRenderer *m_rightRender;
    
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

    
//    double leftViewStation[4] = {0.0, 0.0, 0.5, 1.0};
//    double rightViewStation[4] = {0.5, 0.0, 1.0, 1.0};
    
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
