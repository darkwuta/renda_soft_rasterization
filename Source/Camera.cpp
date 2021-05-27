//
// Created by dark兽 on 2021/4/23.
//

#include "Camera.h"

void Camera::SetProjection(int pattern, float a, float ra, float n, float f) {
    angle = a;
    ratio = ra;
    near = n;
    far = f;
}

Camera::Camera() {
    position<<0,0,-5;
}

