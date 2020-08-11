#ifndef GEOMETRY_080920_H
#define GEOMETRY_080920_H

#include <vector>
#include <memory>


#include "ray.h"
#include "vec3.h"
#include "material.h"

namespace rtm { class material; }
namespace rtm { struct hitRecord; }

struct rtm::hitRecord {
  rtm::vec3 point;
  rtm::vec3 normal;
  std::shared_ptr<rtm::material> materialPointer;
  float t;
  bool frontFace;

  inline void SetFaceNormal(const rtm::ray& ray, const rtm::vec3& outwardNormal) {
    frontFace = static_cast<bool>(rtm::dot(ray.direction, outwardNormal) < 0);
    normal = frontFace ? outwardNormal : -outwardNormal;
  }
};

namespace rtm { class polygon; }
class rtm::polygon {
public:
  virtual bool hit(const rtm::ray& ray,
    const float tMin,
    const float tMax,
    rtm::hitRecord& record) const = 0;

  virtual rtm::vec3 color() const = 0;
  virtual rtm::vec3 center() const = 0;
protected:
  rtm::vec3 baseColor;
  rtm::vec3 origin;

private:
  
};

/*
List of all polygons
*/

namespace rtm { class polygonList; }
class rtm::polygonList : public rtm::polygon{
public:
  polygonList() {}
  polygonList(std::shared_ptr<polygon> object) { add(object); }

  void clear() { objects.clear(); }
  void add(std::shared_ptr<polygon> object) { objects.push_back(object); }

  bool hit(const rtm::ray& ray, const float tMin, const float tMax,
    rtm::hitRecord& record) const{

    rtm::hitRecord tempRecord;
    bool hitAny{ false };
    float closestSoFar{ tMax };
    
    for (const auto& object : objects) {
      if (object->hit(ray, tMin, closestSoFar, tempRecord)) {
        hitAny = true;
        closestSoFar = tempRecord.t;
        record = tempRecord;
      }
    }
    return hitAny;
  }


  rtm::vec3 color() const { return rtm::vec3(); }
  rtm::vec3 center() const { return rtm::vec3(); }
public:
  std::vector<std::shared_ptr<polygon>> objects;
};

/*
sphere  polygon
*/
namespace rtm { class sphere ; }
class rtm::sphere  : public rtm::polygon {
public:

  sphere (rtm::vec3 origin, float radius, std::shared_ptr<rtm::material> materialPointer) :
    origin(origin), radius(radius), materialPointer(materialPointer) {}

  bool hit(const rtm::ray& ray,
              const float tMin,
              const float tMax,
              rtm::hitRecord& record) const {
    /*
    //t == time
    //RD == ray direction (vector)
    //A == ray orgin(vector)
    //C == sphere center(vector)
    //r == sphere radius
    //vector * vector == dot
    //t*t*(RD*RD) + 2*t*(RD*(A-C)) + ((A-C) * (A-C)) - r*r = 0
    //into simplified quadratic form 
    */
    rtm::vec3 AminusC{ray.origin - origin};
    float a{ray.direction.LengthSquared()};
    float half_b{rtm::dot(AminusC, ray.direction) };
    float c{AminusC.LengthSquared() - std::pow(radius, 2)};
    float discriminant{ std::pow(half_b, 2) - a*c };

    //if discriminant > 0 there was a hit
    if (discriminant > 0.0f) {
      float root{ std::sqrt(discriminant) };

      float temp{ ((-half_b - root) / a) };
      if (temp < tMax && temp > tMin) {
        record.t = temp;
        record.point = ray.at(record.t);
        record.normal = (record.point - origin) / radius;
        rtm::vec3 outwardNormal{(record.point - origin) / radius};
        record.SetFaceNormal(ray, outwardNormal);
        record.materialPointer = materialPointer;
        return true;
      }

      temp = std::move((-half_b + root / a));
      if (temp < tMax && temp > tMin) {
        record.t = temp;
        record.point = ray.at(record.t);
        record.normal = (record.point - origin) / radius;
        rtm::vec3 outwardNormal{ (record.point - origin) / radius };
        record.SetFaceNormal(ray, outwardNormal);
        record.materialPointer = materialPointer;
        return true;
      }
    }
    return false;
  }
  rtm::vec3 color() const { return baseColor; }
  rtm::vec3 center() const { return origin; }
public:

private:
  rtm::vec3 origin;
  float radius;
  std::shared_ptr<rtm::material> materialPointer;
  //unused
  rtm::vec3 baseColor;

};

#endif // !GEOMETRY_080920_H

