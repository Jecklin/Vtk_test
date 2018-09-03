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

