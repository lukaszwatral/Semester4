//
//  CRayTrace.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"

/// \fn compPrimaryRayMatrix(CCamera cam, glm::mat3& m)
/// \brief Computation of the projection matrix.
/// \param cam Camera parameters.
/// \param m Output projection matrix.
///
bool CRayTrace::compPrimaryRayMatrix(const CCamera& cam, glm::mat3& m) {
    //obliczanie macierzy rzutowania
    glm::vec3 look = cam.lookp - cam.eyep;
    glm::vec3 u = glm::cross(cam.up, look)/glm::length(glm::cross(cam.up, look));
    glm::vec3 v = glm::cross(u, look)/glm::length(glm::cross(u, look));
    glm::vec3 o = (look/glm::length(look))*float(cam.width)/(2*tan(cam.fov*3.14f/180.0f/2))-(float(cam.width)/2*u+(float(cam.height)/2*v));
    m = {{u[0], u[1], u[2]}, {v[0], v[1], v[2]}, {o[0], o[1], o[2]}};
   return true;
}


/// \fn rayTrace(CScene scene, CRay& ray, COutput& out)
/// \brief Traces single ray.
/// \param scene Object with all scene components including a camera.
/// \param ray Ray parameter (primary and secondary rays).
/// \param out Object with output color and parameters used in recursion.
///


bool CRayTrace::rayTrace(const CScene& scene, CRay& ray, COutput& out) {
    const float MAX_RAY_TREE = 1;
    const float MIN_RAY_ENERGY = 0.01;
    float tmin = FLT_MAX;
    float EPS = 0.0001;
    bool is_intersection = false;
    bool intersection_exists = false;
    CObject* hit_obj;
    /// looks for the closest object along the ray path
    /// returns false if there are no intersection
    for (auto obj: scene.objectList) { // for each object in CScene::objectList
        float t = obj->intersect(ray);
        if (t > EPS && t < tmin) {
            tmin = t;
            is_intersection = true;
            hit_obj = obj;
        }
    }
    if(is_intersection) {
        glm::vec3 p = ray.pos + tmin * ray.dir;
        CRay shadow_ray;
        for (auto light: scene.lightList) {
            out.col = out.col + out.energy * light.color * hit_obj->matAmbient;
            tmin = FLT_MAX;
            shadow_ray.pos = p;
            shadow_ray.dir = glm::normalize(light.pos - p);

            for (auto obj: scene.objectList) {
                intersection_exists = false;
                float t = obj->intersect(shadow_ray);
                if (t > EPS && t < tmin) {
                    intersection_exists = true;
                    break;
                }
            }
            if (intersection_exists) {
                continue;
            }
            glm::vec3 V = -ray.dir;
            glm::vec3 n = hit_obj->normal(p);
            glm::vec3 L = glm::normalize(light.pos - p);
            float cos_angle = glm::dot(n, L);

            if (cos_angle > 0.001) {
                out.col = out.col + out.energy * light.color * hit_obj->matDiffuse * cos_angle;
                glm::vec3 h = glm::normalize(L + V);
                float cos_beta = glm::dot(n, h);
                if (cos_beta > 0.001) {
                    out.col = out.col + out.energy * light.color * hit_obj->matSpecular * pow(cos_beta, hit_obj->matShininess);
                }
            }
            if (hit_obj->isTexture) {
                glm::vec2 uv = hit_obj->textureMapping(n);
                glm::vec3 tex_col = CImage::getTexel(hit_obj->texture, uv.x, uv.y);
                out.col = out.col * tex_col;
            }
            if (hit_obj->reflectance > 0 && out.tree < MAX_RAY_TREE && out.energy > MIN_RAY_ENERGY) {
                out.tree++;
                out.energy = out.energy * hit_obj->reflectance;
                CRay secondary_ray = reflectedRay(ray, n, p);
                rayTrace(scene, secondary_ray, out);
            }
        }
    }

    /// computes normal vector at intersection point

    /// for each light source defined in the scene

        /// computes if the intersection point is in the shadows

        /// computes diffuse color component

        /// computes specular color component

    /// adds texture for textured spheres

    /// computes ambient color component

    /// if the surface is reflective

        /// if out.tree >= MAX_RAY_TREE return from function

        /// computes the secondary ray parameters (reflected ray)

        /// recursion
        //   rayTrace(scene, secondary_ray, out);


    return is_intersection;
}


/// \fn reflectedRay(CRay ray, glm::vec3 n, glm::vec3 pos)
/// \brief Computes parameters of the ray reflected at the surface point with given normal vector.
/// \param ray Input ray.
/// \param n Surface normal vector.
/// \param pos Position of reflection point.
/// \return Reflected ray.
///
CRay CRayTrace::reflectedRay(const CRay& ray, const glm::vec3& n, const glm::vec3& pos) {
    CRay reflected_ray;
    reflected_ray.pos = pos;
    glm::vec3 v = ray.dir;
    glm::vec3 r = v - (2*glm::dot(v, n)*n);
    reflected_ray.dir = glm::normalize(r);
    //std::cout << "ray_reflected.dir = [" << reflected_ray.dir.x << " " << reflected_ray.dir.y << " " << reflected_ray.dir.z << "]\n";
    //std::cout << "ray_reflected.pos = [" << reflected_ray.pos.x << " " << reflected_ray.pos.y << " " << reflected_ray.pos.z << "]\n";
    return reflected_ray;
}

