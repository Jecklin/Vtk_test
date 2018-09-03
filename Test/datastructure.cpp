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

//////***************    8  vtk数据结构    "几何结构"   "拓扑结构"         *************************//

//int main(int argc, char *argv[])
//{

    
////////////****  增加标量属性 ,获取标量属性值 ******///  
 
//    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
//    points->InsertNextPoint(0, 0, 0);
//    points->InsertNextPoint(1, 0, 0);
    
//    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
//    polydata->SetPoints(points);
    
//    vtkSmartPointer<vtkDoubleArray>scalar = vtkSmartPointer<vtkDoubleArray>::New();
//    scalar->SetNumberOfValues(2);
//    scalar->SetValue(0, 1);
//    scalar->SetValue(1, 2);
    
//    polydata->GetPointData()->SetScalars(scalar);
    
//    double scalar1 = vtkDoubleArray::SafeDownCast(
//                polydata->GetPointData()->GetScalars())->GetValue(0);
    
//    double scalar2 = vtkDoubleArray::SafeDownCast(
//                polydata->GetPointData()->GetScalars())->GetValue(1);
    
//    qDebug() << "scalar1:" << scalar1;
//    qDebug() << "scalar2:" << scalar2;
    
//    vtkActor *actor;
//    actor->GetBounds;
    
    
    
 //////////****  增加line 线形的拓扑结构  ******///   
//    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
//    points->InsertNextPoint(1.0, 0.0, 0.0);
//    points->InsertNextPoint(0.0, 0.0, 1.0);
//    points->InsertNextPoint(0.0, 0.0, 0.0);

//    vtkSmartPointer<vtkLine> line0 = vtkSmartPointer<vtkLine>::New();
//    line0->GetPointIds()->SetId(0, 0);
//    line0->GetPointIds()->SetId(1, 1);
    
//    vtkSmartPointer<vtkLine> line1 = vtkSmartPointer<vtkLine>::New();
//    line1->GetPointIds()->SetId(0, 1);
//    line1->GetPointIds()->SetId(1, 2);
    
//    vtkSmartPointer<vtkLine> line2 = vtkSmartPointer<vtkLine>::New();
//    line2->GetPointIds()->SetId(0, 2);
//    line2->GetPointIds()->SetId(1, 0);
    
//    vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
//    lines->InsertNextCell(line0);
//    lines->InsertNextCell(line1);
//    lines->InsertNextCell(line2);
    
//    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
//    polydata->SetPoints(points);
//    polydata->SetLines(lines);

//    vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
//    writer->SetFileName("TriangelLines.vtk");
//    writer->SetInputData(polydata);
//    writer->Write();





    
//////////****  增加vertice顶点类型的拓扑结构  ******///
    
//    double X[3] = {1.0, 0.0, 0.0};
//    double Y[3] = {0.0, 0.0, 1.0};
//    double Z[3] = {0.0, 0.0, 0.0};
    
//    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
//    vtkSmartPointer<vtkCellArray> vertices = vtkSmartPointer<vtkCellArray>::New();
    
//    for (unsigned int i = 0; i < 3; ++i)
//    {
//        vtkIdType pid[1];        
//        pid[0] = points->InsertNextPoint(X[i], Y[i], Z[i]);       
//        vertices->InsertNextCell(1, pid);
//    }
    
//    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
//    polydata->SetPoints(points);
//    polydata->SetVerts(vertices);
    
//    vtkSmartPointer<vtkPolyDataWriter>writer = vtkSmartPointer<vtkPolyDataWriter>::New();
//    writer->SetFileName("TriangelVerts.vtk");
//    writer->SetInputData(polydata);
//    writer->Write();
    
    
    
    
    
    
//////////****  仅创建几何结构，给polyData创建了3个点  ******///
    
//    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
//    points->InsertNextPoint(1.0, 0.0, 0.0);
//    points->InsertNextPoint(0.0, 0.0, 0.0);
//    points->InsertNextPoint(0.0, 1.0, 0.0);
    
//    vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
//    polydata->SetPoints(points);
    
//    vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
//    writer->SetFileName("triangle.vtk");
//    writer->SetInputData(polydata);
//    writer->Write();
        
    
//    return 0;
//}
