//
// Created by dark兽 on 2021/4/23.
//

#include "Triangle.h"

tri::Triangle::Triangle(Eigen::Vector3f *vertexs) {

}

tri::Triangle::Triangle() {
    position[0]<<0,1,0,1;
    position[1]<<1,0,0,1;
    position[2]<<-1,0,0,1;
    vertexColor[0]<<255,0,0;
    vertexColor[1]<<0,255,0;
    vertexColor[2]<<0,0,255;

}

std::tuple<float, float, float> tri::Triangle::computeBarycentric(int x, int y) {
    float c1 = (x*(position[1].y() - position[2].y()) + (position[2].x() - position[1].x())*y + position[1].x()*position[2].y() - position[2].x()*position[1].y()) / (position[0].x()*(position[1].y() - position[2].y()) + (position[2].x() - position[1].x())*position[0].y() + position[1].x()*position[2].y() - position[2].x()*position[1].y());
    float c2 = (x*(position[2].y() - position[0].y()) + (position[0].x() - position[2].x())*y + position[2].x()*position[0].y() - position[0].x()*position[2].y()) / (position[1].x()*(position[2].y() - position[0].y()) + (position[0].x() - position[2].x())*position[1].y() + position[2].x()*position[0].y() - position[0].x()*position[2].y());
    float c3 = (x*(position[0].y() - position[1].y()) + (position[1].x() - position[0].x())*y + position[0].x()*position[1].y() - position[1].x()*position[0].y()) / (position[2].x()*(position[0].y() - position[1].y()) + (position[1].x() - position[0].x())*position[2].y() + position[0].x()*position[1].y() - position[1].x()*position[0].y());
    return {c1,c2,c3};
}

void tri::Triangle::RotateZ(float angle) {
    Eigen::Matrix4f rotate;
    angle = angle/360 *2*PI;
    rotate <<std::cos(angle),-std::sin(angle),0,0,
            std::sin(angle),std::cos(angle),0,0,
            0,0,1,0,
            0,0,0,1;
    for(int i=0;i<3;i++)
        position[i]=rotate*position[i];
}

void tri::Triangle::RotateY(float angle) {
    Eigen::Matrix4f rotate;
    angle = angle/360 *2*PI;
    rotate <<std::cos(angle),0,std::sin(angle),0,
            0,1,0,0,
            -std::sin(angle),0,std::cos(angle),0,
            0,0,0,1;
    for(int i=0;i<3;i++)
        position[i]=rotate*position[i];
}

void tri::Triangle::SetColor(int R, int G, int B) {
    vertexColor[0]<<R,G,B;
    vertexColor[1]<<R,G,B;
    vertexColor[2]<<R,G,B;
}
