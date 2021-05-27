//
// Created by dark兽 on 2021/4/23.
//

#ifndef RENDER_SCENE_H
#define RENDER_SCENE_H
#include "Rasterizer.h"
#include "Camera.h"
#include "Triangle.h"
#include <vector>

namespace Scene
{
    class Scene
    {
    public:
        Scene();
        Scene(int w,int h,int cameraIndex);
        void add(tri::Triangle object);
        void add(Camera camera);
        void show(Eigen::Vector3i backGround = Eigen::Vector3i(255,255,255));


    private:
        rst::Rasterizer* rasterizer;
        std::vector<Camera> cameras;
        std::vector<tri::Triangle> objects;
        int cameraIndex;
    };

}


#endif //RENDER_SCENE_H
