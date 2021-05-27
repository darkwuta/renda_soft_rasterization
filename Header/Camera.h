//
// Created by dark兽 on 2021/4/23.
//

#ifndef RENDER_CAMERA_H
#define RENDER_CAMERA_H
#include"global.h"

class Camera {
public:
    Camera();
    void SetProjection(int pattern, float angle, float ratio, float near,float far);
    float angle;
    float ratio;
    float near;
    float far;
    Eigen::Vector3f position;
private:



};


#endif //RENDER_CAMERA_H
