#include"iostream"
#include"Header/Rasterizer.h"
#include"Header/Scene.h"
#include"Header/Camera.h"
#include"Header/Triangle.h"
#include"fstream"
int main()
{
    int width = 700;
    int height = 700;
    Camera camera0;
    camera0.SetProjection(CAMERA_PROJECTION, 45.f, float(height) / float(width), 0.1, 100.f);//只支持角度制
    Scene::Scene scene(width,height,0);
    tri::Triangle t1;
    tri::Triangle t2;
    t1.RotateY(60);
    t2.SetColor(100,100,100);
    //t.Scale(3);
    //t.TranslateX(5);
    scene.add(camera0);
    scene.add(t1);
    scene.add(t2);
    scene.show();
    return 0;
}