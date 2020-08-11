#ifndef MATERIAL_081020_H
#define MATERIAL_081020_H

#include "vec3.h"
#include "ray.h"

namespace rtm { struct hitRecord; }
class rtm::ray;
class rtm::vec3;

namespace rtm { class material; }
class rtm::material {
public:
  virtual bool scatter(const rtm::ray& rayIn, const rtm::hitRecord& record,
    rtm::vec3& attenuation, rtm::ray& scattered) const = 0;

};

namespace rtm { class maya; }
class rtm::maya : public rtm::material{
public:
  maya(const rtm::vec3& albedo = rtm::vec3(127.5f)):albedo(albedo){}

  bool scatter(const rtm::ray& rayIn, const rtm::hitRecord& record,
    rtm::vec3& attenuation, rtm::ray& scattered) const;
  
public:
  rtm::vec3 albedo;
};

namespace rtm { class lambertian; }
class rtm::lambertian : public rtm::material {
public:
  lambertian(const rtm::vec3& albedo) :albedo(albedo) {}

  bool scatter(const rtm::ray& rayIn, const rtm::hitRecord& record,
    rtm::vec3& attenuation, rtm::ray& scattered) const;

public:
  rtm::vec3 albedo;
};

namespace rtm { class metal; }
class rtm::metal : public rtm::material {
public:
  metal(const rtm::vec3& albedo, float roughness) :albedo(albedo),
    roughness(roughness < 1.0f ? roughness : 1.0f){}

  bool scatter(const rtm::ray& rayIn, const rtm::hitRecord& record,
    rtm::vec3& attenuation, rtm::ray& scattered) const;

public:
  rtm::vec3 albedo;
  float roughness;
};

#endif // !MATERIAL_081020_H
