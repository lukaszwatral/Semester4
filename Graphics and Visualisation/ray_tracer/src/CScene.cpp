//
//  CScene.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"

#include<fstream>

/// \fn create(void)
/// \brief Adds components to the scene.
///
void CScene::create(const std::string &name) {
    
    lightList.clear(); // clears vector with the light data
    objectList.clear(); // clears vector of pointers to objects

    //kamera 1
    if(name =="camera1") {
        cam.eyep = glm::vec3(0, 0, 10);
        cam.lookp = glm::vec3(0, 0, 0);
        cam.up = glm::vec3(0, 1, 0);
        cam.fov = 50;
        cam.width = 500;
        cam.height = 400;
    };

    //kamera2
    if(name == "camera2") {
    cam.eyep = glm::vec3(2, 5, 10);
    cam.lookp = glm::vec3(-2, 1, 0);
    cam.up = glm::vec3(0, 1, 0);
    cam.fov = 50;
    cam.width = 500;
    cam.height = 400;
    }
    // add camera, light sources, and objects
    if(name == "cw16"){
        cam.eyep = glm::vec3(0, -4, 10);
        cam.lookp = glm::vec3(0, 0, 0);
        cam.up = glm::vec3(0, 1, 0);
        cam.fov = 50;
        cam.width = 500;
        cam.height = 400;
    }

    /// Tworzenie kul i dodanie ich do listy obiektów
//    CSphere* sphere1 = new CSphere({-2.5, 1.3, -3}, 1);
//    //objectList.push_back(sphere1);
//    CSphere* sphere2 = new CSphere({0, 0, 0}, 1.6);
//    //objectList.push_back(sphere2);
//    /// tworzenie trójkąta i dodanie go do listy obiektów
//    CTriangle* triangle1 = new CTriangle({3, 3, -5}, {-3, 3, -10}, {-3, -3, -8});
//    //objectList.push_back((triangle1));
//    /// tworzenie źródła światła
//    CLight light1(glm::vec3(-3, -2, 8));
//    light1.color = {0.6, 0.6, 0.6};
//    lightList.push_back(light1);
//    CSphere* sphere = new CSphere({0, 0 ,0}, 1.6);
//    sphere->matAmbient = {0.1, 0, 0};
//    sphere->matDiffuse = {0.6, 0, 0};
//    sphere->matSpecular = {0.7, 0.7, 0.7};
//    sphere->matShininess = 30;
//    sphere->reflectance = 0;
//    sphere->isTexture = true;
//    sphere->texture = CImage::createTexture(400, 400);
//    objectList.push_back(sphere);

/// ćwiczenie 14
//    CLight light(glm::vec3(-3, -2, 8));
//    light.color = {0.6, 0.6, 0.6};
//    lightList.push_back(light);
//
//    CSphere* sphere1 = new CSphere({-1, 0, 3}, 0.4);
//    sphere1->matAmbient = {0, 0.1, 0};
//    sphere1->matDiffuse = {0, 0.6, 0};
//    sphere1->matSpecular = {0.7, 0.7, 0.7};
//    sphere1->matShininess = 30;
//    sphere1->reflectance = 0;
//
//    CSphere* sphere2 = new CSphere({0, 0, 0}, 1.6);
//    sphere2->matAmbient = {0.1, 0, 0};
//    sphere2->matDiffuse = {0.6, 0, 0};
//    sphere2->matSpecular = {0.7, 0.7, 0.7};
//    sphere2->matShininess = 30;
//    sphere2->reflectance = 0;
//
//    CSphere* sphere3 = new CSphere({-3, -2, -2}, 0.6);
//    sphere3->matAmbient = {0, 0, 0.1};
//    sphere3->matDiffuse = {0, 0, 0.6};
//    sphere3->matSpecular = {0.7, 0.7, 0.7};
//    sphere3->matShininess = 30;
//    sphere3->reflectance = 0;
//
//    CTriangle* triangle1 = new CTriangle({5, 5, -5}, {-5, 5, -5}, {-5, -5, -5});
//    triangle1->matAmbient = {0.1, 0.1, 0.1};
//    triangle1->matDiffuse = {0.4, 0.4, 0.4};
//    triangle1->matSpecular = {0, 0, 0};
//    triangle1->matShininess = 0;
//    triangle1->reflectance = 0;
//
//    CTriangle* triangle2 = new CTriangle({5, 5, -5}, {-5, -5, -5}, {5, -5, -5});
//    triangle2->matAmbient = {0.1, 0.1, 0.1};
//    triangle2->matDiffuse = {0.4, 0.4, 0.4};
//    triangle2->matSpecular = {0, 0, 0};
//    triangle2->matShininess = 0;
//    triangle2->reflectance = 0;
//
//    objectList.push_back(sphere1);
//    objectList.push_back(sphere2);
//    objectList.push_back(sphere3);
//    objectList.push_back(triangle1);
//    objectList.push_back(triangle2);

/// ćwiczenie 16
//    CLight light;
//    light.pos = {-3, -2, 8};
//    light.color = {0.6, 0.6, 0.6};
//    lightList.push_back(light);
//
//    CSphere* sphere = new CSphere({0, 0, 0}, 1.6);
//    sphere->matAmbient = {0.1, 0, 0};
//    sphere->matDiffuse = {0.6, 0, 0};
//    sphere->matSpecular = {0.7, 0.7, 0.7};
//    sphere->matShininess = 30;
//    sphere->reflectance = 0;
//
//    CTriangle* triangle1 = new CTriangle({5, 5, -5}, {-5, 5, -5}, {-5, -5, -5});
//    triangle1->matAmbient = {0.1, 0.1, 0.1};
//    triangle1->matDiffuse = {0.4, 0.4, 0.4};
//    triangle1->matSpecular = {0, 0, 0};
//    triangle1->matShininess = 0;
//    triangle1->reflectance = 1;
//
//    CTriangle* triangle2 = new CTriangle({5, 5, -5}, {-5, -5, -5}, {5, -5, -5});
//    triangle2->matAmbient = {0.1, 0.1, 0.1};
//    triangle2->matDiffuse = {0.4, 0.4, 0.4};
//    triangle2->matSpecular = {0, 0, 0};
//    triangle2->matShininess = 0;
//    triangle2->reflectance = 1;
//
//    objectList.push_back(sphere);
//    objectList.push_back(triangle1);
//    objectList.push_back(triangle2);

/// ćwiczenie 16b

    CLight light1;
    CLight light2;
    light1.pos = {-3, -2, 8};
    light1.color = {0.6, 0.6, 0.6};
    light2.pos = {5, -2, 8};
    light2.color = {0.3, 0.3, 0.3};
    lightList.push_back(light1);
    lightList.push_back(light2);

    CSphere* sphere1 = new CSphere({-1, 0, 3}, 0.4);
    sphere1->matAmbient = {0, 0.1, 0};
    sphere1->matDiffuse = {0, 0.6, 0};
    sphere1->matSpecular = {0.7, 0.7, 0.7};
    sphere1->matShininess = 30;
    sphere1->reflectance = 0;

    CSphere* sphere2 = new CSphere({0, 0, 0}, 1.6);
    sphere2->matAmbient = {0.1, 0 ,0};
    sphere2->matDiffuse = {0.6, 0, 0};
    sphere2->matSpecular = {0.7, 0.7, 0.7};
    sphere2->matShininess = 30;
    sphere2->reflectance = 0;
    CSphere* sphere3 = new CSphere({-3, -2, -2}, 0.6);
    sphere3->matAmbient = {0, 0, 0.1};
    sphere3->matDiffuse = {0, 0, 0.6};
    sphere3->matSpecular = {0.7, 0.7, 0.7};
    sphere3->matShininess = 30;
    sphere3->reflectance = 0;

    CTriangle* triangle1 = new CTriangle({5, 5, -5}, {-5, 5, -5}, {-5, -5, -5});
    triangle1->matAmbient = {0.1, 0.1, 0.1};
    triangle1->matDiffuse = {0.4, 0.4, 0.4};
    triangle1->matSpecular = {0, 0, 0};
    triangle1->matShininess = 0;
    triangle1->reflectance = 1;

    CTriangle* triangle2 = new CTriangle({5, 5, -5}, {-5, -5, -5}, {5, -5, -5});
    triangle2->matAmbient = {0.1, 0.1, 0.1};
    triangle2->matDiffuse = {0.4, 0.4, 0.4};
    triangle2->matSpecular = {0, 0, 0};
    triangle2->matShininess = 0;
    triangle2->reflectance = 1;

    objectList.push_back(sphere1);
    objectList.push_back(sphere2);
    objectList.push_back(sphere3);
    objectList.push_back(triangle1);
    objectList.push_back(triangle2);


//    std::string typ = "Blinn-Phong";
//    if(typ == "ambient") {
//        sphere2->matAmbient = {0.5, 0, 0};
//        sphere2->matDiffuse = {0, 0, 0};
//        sphere2->matSpecular = {0, 0, 0};
//        sphere2->matShininess = 30;
//        sphere2->reflectance = 0;
//        sphere2->isTexture = 0;
//    }
//
//    if(typ == "diffuse") {
//        sphere2->matAmbient = {0, 0, 0};
//        sphere2->matDiffuse = {0.7, 0, 0};
//        sphere2->matSpecular = {0, 0, 0};
//        sphere2->matShininess = 0;
//        sphere2->reflectance = 0;
//        sphere2->isTexture = 0;
//    }
//
//    if(typ == "specular") {
//        sphere2->matAmbient = {0, 0, 0};
//        sphere2->matDiffuse = {0, 0, 0};
//        sphere2->matSpecular = {0.7, 0.7, 0.7};
//        sphere2->matShininess = 30;
//        sphere2->reflectance = 0;
//        sphere2->isTexture = 0;
//    }
//
//    if(typ=="Blinn-Phong") {
//        sphere2->matAmbient = {0.1, 0, 0};
//        sphere2->matDiffuse = {0.6, 0, 0};
//        sphere2->matSpecular = {0.7, 0.7, 0.7};
//        sphere2->matShininess = 50;
//        sphere2->reflectance = 0;
//        sphere2->isTexture = 0;
//    }
}

