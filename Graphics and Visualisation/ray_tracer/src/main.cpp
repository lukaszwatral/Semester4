
#include <iostream>


#include "rt.h"

extern void draw_robot();
extern void draw_triangles();

///
int main (int argc, char * const argv[]) {
    //10.04.24 - dodane wartości kamery w pliku CScene.cpp,
    // zrobiona metoda obliczająca macierz rzutowania w pliku CRayTrace.cpp
    // przeciążona funkcja CScene::create() umożliwiająca wybranie nazwy kamery, której chcemy użyć

//    draw_triangles();
//    return 0;
    //draw_robot();
    std::cout << "ray tracing ... \n";

    CScene scene;

    scene.create("cw16"); // defines sample scene parameters
    if(scene.cam.width == 0) {
        std::cout << "WARNING: scene not defined" << std::endl;
        return -1;
    }
    CRayTrace rt;
    CRay ray;
    COutput results;
    /// computes primary ray matrix
//     glm::mat3 ray_matrix;
//     CRayTrace::compPrimaryRayMatrix(scene.cam, ray_matrix);
    // std::cout << "Camera projection matrix:" << std::endl;
     //PRINT_MAT3(ray_matrix);


    /// computes ray direction for sample pixel positions
//    float fx = scene.cam.width/2-1+0.5;
//    float fy = scene.cam.height/2-1+0.5;

    //tablica utworzona, aby wyświetlić wszystkie pięć przypadków z zadania
//    float fx[5] = {float(scene.cam.width/2-1+0.5), 0.5, float(scene.cam.width/2-1+0.5), 0.5, float(scene.cam.width-1+0.5)};
//    float fy[5] = {float(scene.cam.height/2-1+0.5), 0.5, 0.5, float(scene.cam.height/2-1+0.5), float(scene.cam.height-1+0.5)};
//    ray.pos = scene.cam.eyep;
//    for(int i = 0; i<5; i++) {
//        ray.dir = (ray_matrix * glm::vec3(fx[i], fy[i], 1.0f));
//        ray.dir = glm::normalize(ray.dir);
//        std::cout << fx[i] << ", " << fy[i] << " -> ";
////        PRINT_VEC3("ray.dir: ", ray.dir);
//    }
    /// creates raster image object
//     CImage image(scene.cam.width, scene.cam.height);
//     CImage imageR(scene.cam.width, scene.cam.height);
//     CImage imageG(scene.cam.width, scene.cam.height);
//     CImage imageB(scene.cam.width, scene.cam.height);
//
//    /// main loop
//
//
//            for(int j = 0; j < scene.cam.height; j++){
//                for(int i =0; i < scene.cam.width; i++){
//                    /// position of the image point
//                    float fx = (float)i + 0.5f;
//                    float fy = (float)j + 0.5f;
//
//                    /// obliczanie kierunku promienia pierwotnego
//                    ray.dir = (ray_matrix * glm::vec3(fx, fy, 1.0f));
//                    ray.dir = glm::normalize(ray.dir);
//
//                    /// macierze rgb
//                    glm :: vec3 rgb (0.0f ,0.0f ,0.0f );
//                    glm :: vec3 rgbR (0.0f ,0.0f ,0.0f );
//                    glm :: vec3 rgbG (0.0f ,0.0f ,0.0f );
//                    glm :: vec3 rgbB (0.0f ,0.0f ,0.0f );
//
//                    /// red
//                    rgbR.x = (ray.dir.x + 1.0f)/2.0f ; // conversion from <−1,1> to <0,1>
//                    imageR.setPixel(i , j , rgbR);
//                    /// green
//                    rgbG.y = (ray.dir.y + 1.0f)/2.0f ; // conversion from <−1,1> to <0,1>
//                    imageG.setPixel(i , j , rgbG);
//                    /// blue
//                    rgbB.z = (ray.dir.z + 1.0f)/2.0f ; // conversion from <−1,1> to <0,1>
//                    imageB.setPixel(i , j , rgbB);
//                    /// mix
//                    rgb.x = (ray.dir.x + 1.0f)/2.0f ; // conversion from <−1,1> to <0,1>
//                    rgb.y = (ray.dir.y + 1.0f)/2.0f ; // conversion from <−1,1> to <0,1>
//                    rgb.z = (ray.dir.z + 1.0f)/2.0f ; // conversion from <−1,1> to <0,1>
//                    image.setPixel(i, j, rgb);
//                }
//            }

            /// tworzenie kuli
//            CSphere* sphere = new CSphere({0, 0, 0}, 5);
//            ray.pos = {0, 0, 10};
//            ray.dir = {0.3, 0.3, -1};
//            /// obliczanie przecięcia promienia z kulą
//            std::cout << "\n" << sphere->intersect(ray);




            /// primary ray
            /// ...

            /// background color
            // results.col = {0,0,0};
            /// secondary ray counter
            // results.tree = 0;
            /// ray energy
            // results.energy = 1.0f;
            
            /// rendering
            /// rt.rayTrace(scene, ray, results);

            /// handles pixel over-saturation
            // if(results.col.x > 1 || results.col.y > 1 || results.col.z > 1) {
            //    results.col = {1,1,1};
            //}

            /// writes pixel to output image
            // image.setPixel(i, j, results.rgb);

        CImage image(scene.cam.width, scene.cam.height);

        // computes projection matrix in CRayTrace::comRayMatrix()
        glm::mat3 ray_matrix;
        CRayTrace::compPrimaryRayMatrix(scene.cam, ray_matrix);
        for(int j = 0; j < scene.cam.height; j++){
            for(int i = 0; i < scene.cam.width; i++){

                // position of the image point
                float fx = (float)i + 0.5f;
                float fy = (float)j + 0.5f;

                //computes ray.pos and normalized ray.dir using projection matrix
                ray.pos = scene.cam.eyep;
                ray.dir = (ray_matrix * glm::vec3(fx, fy, 1.0f));
                ray.dir = glm::normalize(ray.dir);

                // sets background color
                results.col = {0, 0, 0};
                results.energy = 1.0f;
                results.tree = 0;
                // ray tracing
                rt.rayTrace(scene, ray, results);

                // handles pixel over-saturation
                if(results.col.x > 1 || results.col.y > 1 || results.col.z > 1){
                    results.col = {1, 1, 1};
                }

                // writes pixel to output image
                image.setPixel(i, j, results.col);
            }
        }
        image.plotCalibChart();
        // shows image
        cv::imshow("output", image.getImage());
        cv::waitKey();

        // writes image to disk file
        //image.save("output.png", true);

//        ray.pos = {0, 0, 0};
//        ray.dir = {0.5f, 0.5f, 0.0f};
//        glm::vec3 n = {0, 1.0, 0};
//        glm::vec3 pos = {0, 0 ,0};
//        CRay reflected_ray = rt.reflectedRay(ray, n, pos);
    /// writes image to disk file with gamma correction
//     imageR.save("red.png", false);
//     imageG.save("green.png", false);
//     imageB.save("blue.png", false);

     /// wyświetlanie w okienkach
//     cv::imshow("Red", imageR.getImage());
//    cv::waitKey();
//     cv::imshow("Green", imageG.getImage());
//    cv::waitKey();
//     cv::imshow("Blue", imageB.getImage());
//     cv::waitKey();
//    cv::imshow("Mix", image.getImage());
//    cv::waitKey();
    std::cout << std::endl << std::endl;
    return 0;
}


/// Draws two trianges
void draw_triangles() {

    CImage img(1000, 1000);
    
    glm::vec3 color1(0.9,0.1,0.1); // red
    glm::vec3 color2(0.1,0.9,0.1); // green
    
    // draw circle
    glm::vec3 pp(0.0,0.0,1.0);
    float radius = 0.1f;
//    img.drawCircle(pp, radius, color1);
    
    // triangle vertices
    glm::vec3 pp0(0.4, 0.3, 1);
    glm::vec3 pp1(-0.4, 0.3, 1);
    glm::vec3 pp2(0.4, -0.3, 1);
    
    // draws triangle in 2D
    img.drawLine(pp0, pp1, color1);
    img.drawLine(pp1, pp2, color1);
    img.drawLine(pp2, pp0, color1);
    
    // translation
    float tX = 0.2f; // OX translation
    float tY = 0.1f; // OY translation
    glm::mat3x3 mTrans {{1,0,0}, {0,1,0}, {tX,tY,1}}; // translation matrix
    PRINT_MAT3(mTrans);

    // translation of vertices
    pp0 = mTrans * pp0;
    pp1 = mTrans * pp1;
    pp2 = mTrans * pp2;

    // draws triangle after translation
    img.drawLine(pp0, pp1, color2);
    img.drawLine(pp1, pp2, color2);
    img.drawLine(pp2, pp0, color2);

    img.save("robot.png");
    cv::imshow("ROBOT", img.getImage());
    cv::waitKey();

}

/// Draws robot.
void draw_robot() {

    CImage img(1000, 1000);

    // wierzchołki
    glm::vec3 pp0(0.15, 0.3, 1);
    glm::vec3 pp1(-0.15, 0.3, 1);
    glm::vec3 pp2(0.15, -0.3, 1);
    glm::vec3 pp3(-0.15, -0.3, 1);
    glm::vec3 pp4(0, 0.45, 1);
    glm::vec3 color1(0.9,0.4,0.1); // orange

    // rysuje tułów i głowę
    img.drawLine(pp0, pp1, color1);
    img.drawLine(pp0, pp2, color1);
    img.drawLine(pp1, pp3, color1);
    img.drawLine(pp2, pp3, color1);
    img.drawCircle(pp4, 0.1, color1);

    float tX = -0.4f; // translacja OX
    float tY = 0.25f; // translacja OY
    float sX = 0.35f; // skalowanie OX
    float sY = 0.7f; // skalowanie OY
    float fi = M_PI*90/180; // kąt obrotu
    glm::mat3x3 mScale {{sX, 0, 0}, {0, sY, 0}, {0, 0, 1}}; //macierz skalowania
    glm::mat3x3 mRot{{cos(fi), sin(fi), 0}, {-sin(fi), cos(fi), 0}, {0, 0, 1}}; // macierz obrotu
    glm::mat3x3 mTrans {{1,0,0}, {0,1,0}, {tX,tY,1}}; // macierz translacji
    glm::mat3x3 mRes = mTrans * mRot * mScale; // macierz przekształceń złożonych

    pp0 = mRes* pp0;
    pp1 = mRes * pp1;
    pp2 = mRes * pp2;
    pp3 = mRes * pp3;

    // rysuje prawe ramię
    img.drawLine(pp0, pp1, color1);
    img.drawLine(pp0, pp2, color1);
    img.drawLine(pp1, pp3, color1);
    img.drawLine(pp2, pp3, color1);

    tX = 0.8f; // translacja OX
    tY = 0.0f; // translacja OY
    sX = 1.0f; // skalowanie OX
    sY = 1.0f; // skalowanie OY
    fi = 0*M_PI/180; // kąt obrotu
    mScale = {{sX, 0, 0}, {0, sY, 0}, {0, 0, 1}}; //macierz skalowania
    mRot = {{cos(fi), sin(fi), 0}, {-sin(fi), cos(fi), 0}, {0, 0, 1}}; // macierz obrotu
    mTrans = {{1,0,0}, {0,1,0}, {tX,tY,1}}; // macierz translacji
    mRes = mTrans * mRot * mScale; // macierz przekształceń złożonych

    pp0 = mRes * pp0;
    pp1 = mRes * pp1;
    pp2 = mRes * pp2;
    pp3 = mRes * pp3;

    // rysuje lewe ramię
    img.drawLine(pp0, pp1, color1);
    img.drawLine(pp0, pp2, color1);
    img.drawLine(pp1, pp3, color1);
    img.drawLine(pp2, pp3, color1);

    tX = -0.15f; // translacja OX
    tY = -0.3f; // translacja OY
    sX = 1.0f; // skalowanie OX
    sY = 1.0f; // skalowanie OY
    fi = -60*M_PI/180; // kąt obrotu
    mScale = {{sX, 0, 0}, {0, sY, 0}, {0, 0, 1}}; //macierz skalowania
    mRot = {{cos(fi), sin(fi), 0}, {-sin(fi), cos(fi), 0}, {0, 0, 1}}; // macierz obrotu
    mTrans = {{1,0,0}, {0,1,0}, {tX,tY,1}}; // macierz translacji
    mRes = mTrans * mRot * mScale; // macierz przekształceń złożonych
    
    pp0 = mRes * pp0;
    pp1 = mRes * pp1;
    pp2 = mRes * pp2;
    pp3 = mRes * pp3;

    // rysuje lewą nogę
    img.drawLine(pp0, pp1, color1);
    img.drawLine(pp0, pp2, color1);
    img.drawLine(pp1, pp3, color1);
    img.drawLine(pp2, pp3, color1);


    tX = -0.6f; // translacja OX
    tY = -1.0f; // translacja OY
    sX = 1.0f; // skalowanie OX
    sY = 1.0f; // skalowanie OY
    fi = 120*M_PI/180; // kąt obrotu
    mScale = {{sX, 0, 0}, {0, sY, 0}, {0, 0, 1}}; //macierz skalowania
    mRot = {{cos(fi), sin(fi), 0}, {-sin(fi), cos(fi), 0}, {0, 0, 1}}; // macierz obrotu
    mTrans = {{1,0,0}, {0,1,0}, {tX,tY,1}}; // macierz translacji
    mRes = mTrans * mRot * mScale; // macierz przekształceń złożonych

    pp0 = mRes * pp0;
    pp1 = mRes * pp1;
    pp2 = mRes * pp2;
    pp3 = mRes * pp3;

    // rysuje prawą nogę
    img.drawLine(pp0, pp1, color1);
    img.drawLine(pp0, pp2, color1);
    img.drawLine(pp1, pp3, color1);
    img.drawLine(pp2, pp3, color1);


    img.save("robot.png");
    cv::imshow("ROBOT", img.getImage());
    cv::waitKey();
}
