//
// Created by dark兽 on 2021/4/23.
//

#include "Rasterizer.h"

rst::Rasterizer::Rasterizer(int w, int h) {
    width = w;
    height = h;
    frame_buf=new cv::Mat(height,width,CV_8UC3);
    depth_buf=new std::vector<std::vector<float>>(height,std::vector<float>(width, 0));
}


void rst::Rasterizer::setModel() {
    model = Eigen::Matrix4f::Identity();
    //std::cout<<model;
}

void rst::Rasterizer::setProjection(float eyeFov, float ratio, float zNear, float zFar) {
    projection=Eigen::Matrix4f::Identity();
    float eyeAngel = eyeFov/180*PI;
    float t, b, l, r;
    t=zNear*std::tan(eyeAngel/2);
    b=-t;
    r=t*ratio;
    l=-r;
    Eigen::Matrix4f orthoScale;
    Eigen::Matrix4f orthoTranslate;
    orthoScale<<2/(r-l),0,0,0,
                0,2/(t-b),0,0,
                0,0,2/(zFar-zNear),0,
                0,0,0,1;
    std::cout<<"orthoScale:"<<orthoScale<<std::endl;
    orthoTranslate<<1,0,0,-(r+l)/2,
                    0,1,0,-(t+b)/2,
                    0,0,1,-(zFar+zNear)/2,
                    0,0,0,1;
    projection<<zNear,0,0,0,
                0,zNear,0,0,
                0,0,zNear+zFar,-zNear*zFar,
                0,0,1,0;
    projection=orthoScale*orthoTranslate*projection;
    //std::cout<<projection;
}

void rst::Rasterizer::setView(Eigen::Vector3f eyePos) {
    view = Eigen::Matrix4f::Identity();
    Eigen::Matrix4f translate;
    translate<<1,0,0,-eyePos[0],
                0,1,0,-eyePos[1],
                0,0,1,-eyePos[2],
                0,0,0,1;
    view *=translate;
}

void rst::Rasterizer::draw(std::vector<tri::Triangle> &objects) {
    //std::cout<<"M"<<model<<std::endl;
    //std::cout<<"V"<<view<<std::endl;
    //std::cout<<"P"<<projection<<std::endl;
    Eigen::Matrix4f MVP=projection*view*model;
    viewPort=viewPort*MVP;
    //std::cout<<"MVP"<<MVP<<std::endl;
    //std::cout<<"viewPost"<<viewPort<<std::endl;
    for(auto t : objects)
    {
        t.position[0]=viewPort*t.position[0];
        t.position[1]=viewPort*t.position[1];
        t.position[2]=viewPort*t.position[2];
        t.position[0]/=t.position[0].w();
        t.position[1]/=t.position[1].w();
        t.position[2]/=t.position[2].w();
        //求得包围盒
        int xmin=0;
        int xmax=width;
        int ymin=0;
        int ymax=height;
        float xminf = t.position[0].x();
        float xmaxf = t.position[0].x();
        float yminf = t.position[0].y();
        float ymaxf = t.position[0].y();
        //std::cout<<t.position[0];
        //std::cout<<t.position[1];
        //std::cout<<t.position[2];
        for(int i=0;i<3;i++)
        {

            if(xminf>t.position[i].x())xminf=t.position[i].x();
            if(xmaxf<t.position[i].x())xmaxf=t.position[i].x();
            if(yminf>t.position[i].y())yminf=t.position[i].y();
            if(ymaxf<t.position[i].y())ymaxf=t.position[i].y();
        }
        xmin = xminf;
        xmax = xmaxf + 1;
        ymin = yminf;
        ymax = ymaxf + 1;
        std::cout<<"vertex0"<<t.vertexColor[0]<<std::endl;
        std::cout<<"vertex1"<<t.vertexColor[1]<<std::endl;
        std::cout<<"vertex2"<<t.vertexColor[2]<<std::endl;
        for(int x=xmin;x<xmax;x++)
        {
            for(int y=ymin;y<ymax;y++)
            {
                Eigen::Vector3f point(x+0.5,y+0.5,0);
                Eigen::Vector3i color(255,0,0);
                if(insideTriangle(point, t))
                {
                    auto [alpha,beta,gamma] = t.computeBarycentric(x,y);
                    float w_reciprocal = 1.0/(alpha+beta+gamma);
                    float z_interpolated = alpha*t.position[0].z()+beta*t.position[1].z()+gamma*t.position[2].z();

                    if(z_interpolated<depth_buf->at(x)[y])
                    {
                        depth_buf->at(x)[y]=z_interpolated;
                        color<<alpha*t.vertexColor[0].x()+beta*t.vertexColor[1].x()+gamma*t.vertexColor[2].x(),
                                alpha*t.vertexColor[0].y()+beta*t.vertexColor[1].y()+gamma*t.vertexColor[2].y(),
                                alpha*t.vertexColor[0].z()+beta*t.vertexColor[1].z()+gamma*t.vertexColor[2].z();
                        //std::cout<<"color"<<color.x()<<" "<<color.y()<<" "<<color.z()<<std::endl;
                        setPixel(point,color);
                    }
                }
            }
        }
    }
    cv::imshow("hello renda",*frame_buf);
    cv::waitKey(100000);
}

void rst::Rasterizer::setViewPort() {
    viewPort<<width/2,0,0,width/2,
                0,height/2,0,height/2,
                0,0,1,0,
                0,0,0,1;
}

bool rst::Rasterizer::insideTriangle(Eigen::Vector3f point, tri::Triangle t) {
    Eigen::Vector3f v0(t.position[0].x(), t.position[0].y(),0);
    Eigen::Vector3f v1(t.position[1].x(), t.position[1].y(),0);
    Eigen::Vector3f v2(t.position[2].x(), t.position[2].y(),0);

    Eigen::Vector3f s0 = (point - v0).cross(v1 - v0);
    Eigen::Vector3f s1 = (point - v1).cross(v2 - v1);
    Eigen::Vector3f s2 = (point - v2).cross(v0 - v2);

    return s0.dot(s1) > 0 && s1.dot(s2) > 0 && s2.dot(s0) > 0;
}

void rst::Rasterizer::setPixel(const Eigen::Vector3f point, const Eigen::Vector3i color) {
        int y=(int)point.x();
        int x=(int)point.y();
        uchar r =(uchar)color.x();
        uchar g =(uchar)color.y();
        uchar b =(uchar)color.z();
        frame_buf->at<cv::Vec3b>(x,y)[0]=r;
        frame_buf->at<cv::Vec3b>(x,y)[1]=g;
        frame_buf->at<cv::Vec3b>(x,y)[2]=b;
}

void rst::Rasterizer::setFrameBuffer(Eigen::Vector3i backGround) {
    for(int x=0;x<width;x++)
    {
        for(int y = 0;y<height;y++)
        {
            frame_buf->at<cv::Vec3b>(x,y)[0]=backGround.x();
            frame_buf->at<cv::Vec3b>(x,y)[1]=backGround.y();
            frame_buf->at<cv::Vec3b>(x,y)[2]=backGround.z();
        }
    }
}

void rst::Rasterizer::setDepthBuffer() {
    for(int x=0;x<width;x++)
    {
        for(int y = 0;y<height;y++)
        {
            depth_buf->at(x)[y] = std::numeric_limits<float>::infinity();
        }
    }
}


