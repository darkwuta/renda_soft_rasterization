//
// Created by dark兽 on 2021/4/23.
//

#ifndef RENDER_TRIANGLE_H
#define RENDER_TRIANGLE_H


#include<Eigen/Eigen>
#include<iostream>
#include<vector>
#include<global.h>
namespace tri
{
    class Triangle
    {
    public:
        //Triangle(float x, float y, float z);
        Triangle();
        Triangle(Eigen::Vector3f vertexs[3]);
        void SetColor(int R, int G, int B);
        void SetColor(float r, float g, float b);
        //void SetColor(float r, float g, float b);//�ı�����ɫ

        void RotateX(float angle);
        void RotateY(float angle);
        void RotateZ(float angle);

        void TranslateY(float distance);

        std::tuple<float,float,float> computeBarycentric(int x,int y);

        Eigen::Vector4f position[3];
        Eigen::Vector3i vertexColor[3];

    };

}


#endif //RENDER_TRIANGLE_H
