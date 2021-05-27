//
// Created by dark兽 on 2021/4/23.
//

#include "Scene.h"


Scene::Scene::Scene(int w, int h, int CameraIndex) {
    rasterizer = new rst::Rasterizer(w,h);
    cameraIndex = CameraIndex;

}

void Scene::Scene::add(tri::Triangle object) {
    objects.push_back(object);
}

void Scene::Scene::add(Camera camera) {
    cameras.push_back(camera);
}

void Scene::Scene::show(Eigen::Vector3i backGround) {
    rasterizer->setModel();
    rasterizer->setView(cameras.back().position);
    rasterizer->setProjection(cameras.at(cameraIndex).angle,cameras.at(cameraIndex).ratio,
                              cameras.at(cameraIndex).near,cameras.at(cameraIndex).far);
    rasterizer->setViewPort();
    rasterizer->setFrameBuffer(backGround);
    rasterizer->setDepthBuffer();
    rasterizer->draw(objects);
}
