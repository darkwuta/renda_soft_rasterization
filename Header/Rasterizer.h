//
// Created by dark兽 on 2021/4/23.
//

#ifndef RENDER_RASTERIZER_H
#define RENDER_RASTERIZER_H
#include<Eigen/Eigen>
#include"global.h"
#include"Triangle.h"
namespace rst
{
    class Rasterizer
    {
    public:
        Rasterizer(int w,int h);
        void reshape();
        void display();
        void draw(std::vector<tri::Triangle> &objects);
        void setPixel(const Eigen::Vector3f point, const Eigen::Vector3i color);
        //MVP
        void setModel();
        void setView(Eigen::Vector3f eyePos);
        void setProjection(float eyeFov, float ratio, float zNear, float zFar);
        void setViewPort();

        void setFrameBuffer(Eigen::Vector3i backGround);

        void setDepthBuffer();

    private:
        int width;
        int height;
        Eigen::Matrix4f model;
        Eigen::Matrix4f view;
        Eigen::Matrix4f projection;
        Eigen::Matrix4f viewPort;
        std::vector<std::vector<float>> *depth_buf;

        cv::Mat *frame_buf;
        int getIndex(int x, int y);
        bool insideTriangle(Eigen::Vector3f point,tri::Triangle t);


    };
}
#endif //RENDER_RASTERIZER_H
