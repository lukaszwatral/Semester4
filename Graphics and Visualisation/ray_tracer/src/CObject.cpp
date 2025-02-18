//
//  CObject.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"
#include "CObject.hpp"


/// \fn intersect(CRay ray)
/// \brief Computes intersection between ray and sphere.
/// \param ray Ray parameters.
/// \return Distance from camera position to the closest intersection point, or negative value.
///
float CSphere::intersect(const CRay& ray) {
    float t = -1; /// w przypadku braku przecięcia
    glm::vec3 v = ray.pos - this->pos;
    float A = glm::dot(ray.dir, ray.dir);
    float B = 2 * glm::dot(v, ray.dir);
    float C = glm::dot(v, v)-this->r*this->r;
    float delta = B*B-4*A*C;
    float t1 = (-B-sqrt(delta))/(2*A);
    float t2 = (-B+sqrt(delta))/(2*A);
    /// znalezienie najmniejszej, ale większej od zera wartości t
    if(t1 <= t2 && t1 > 0){
        t = t1;
    }
    else if(t2 < t1 && t2 > 0){
        t = t2;
    }
    return t;
}


/// Normal vector to the sphere surface
/// \fn normal(glm::vec3 hit_pos)
/// \brief Surface normal vector at the intersection point.
/// \param hit_pos Intersection point.
/// \return Normal vector parameters.
///
glm::vec3 CSphere::normal(const glm::vec3& hit_pos) {
    glm::vec3 n = {0,0,0};
    n = glm::normalize(hit_pos-this->pos);
    return n;
}

/// Computes texture mapping coordinates (u,v).
/// \param normal_vec Normalized normal vector at intersection point.
/// \return (u,v) texture coordinates in <0,1> range.
glm::vec2 CSphere::textureMapping(const glm::vec3& normal_vec) {
    float u = 0.5 + glm::asin(normal_vec.x)/M_PI;
    float v = 0.5 - glm::asin(normal_vec.y)/M_PI;
    glm::vec2 uv = {u, v};
    return uv;
}



/// \fn intersect(CRay ray)
/// \brief Computes intersection between triangle and sphere.
/// \param ray Ray parameters.
/// \return Distance from camera position to the closest intersection point, or negative value.
///
float CTriangle::intersect(const CRay& ray) {
    float t = -1;
    float tt;
    glm::vec3 hit_pos;
    glm::vec3 tmp = v0;
    bool test = glm::intersectRayTriangle(ray.pos, ray.dir, this->v0, this->v1, this->v2, hit_pos);
    if(test){
        glm::vec3 n = this->normal(hit_pos);
        glm::intersectRayPlane(ray.pos, ray.dir, tmp, n, tt);
        t = tt;
    }
    return t;
}


/// \fn normal(glm::vec3 hit_pos)
/// \brief Surface normal vector at the intersection point.
/// \param hit_pos Intersection point (not used for triangle).
/// \return Normal vector parameters.
///
glm::vec3 CTriangle::normal(const glm::vec3& hit_pos) {
    glm::vec3 n;
    glm::vec3 u = this->v1-this->v0;
    glm::vec3 v = this->v2 - this->v0;
    n = glm::normalize(glm::cross(u, v));
    return n;
}



