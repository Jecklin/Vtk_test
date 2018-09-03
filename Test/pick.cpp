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
