#include "material.h"
#include "geometry.h"
#include "utility.h"

bool rtm::maya::scatter(const rtm::ray& rayIn, const rtm::hitRecord& record, rtm::vec3& attenuation, rtm::ray& scattered) const {
  rtm::vec3 scatterDirection = record.normal + utility::randomUnitVector();
  scattered = std::move(rtm::ray(record.point, scatterDirection));
  attenuation = albedo;
  return true;
}

bool rtm::lambertian::scatter(const rtm::ray& rayIn, const rtm::hitRecord& record, rtm::vec3& attenuation, rtm::ray& scattered) const {
  rtm::vec3 scatterDirection = record.normal + utility::randomUnitVector();
  scattered = std::move(rtm::ray(record.point, scatterDirection));
  attenuation = albedo;
  return true;
}

bool rtm::metal::scatter(const rtm::ray& rayIn, const rtm::hitRecord& record, rtm::vec3& attenuation, rtm::ray& scattered) const {
  rtm::vec3 reflected = rtm::reflect(rtm::unitVector(rayIn.direction), record.normal);
  scattered = std::move(rtm::ray(record.point, reflected + roughness * utility::randomInUnitSphere()));
  attenuation = albedo;
  return rtm::dot(scattered.direction, record.normal) > 0.0f;
}
