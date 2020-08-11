#ifndef UTILITY_080920_H
#define UTILITY_080920_H

#include <random>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Common Headers
#include "rtm/vec3.h"
#include "rtm/ray.h"
#include "rtm/geometry.h"
#include "rtm/material.h"

//.png image
namespace image {
  static constexpr float aspectRatio = 16.0f / 9.0f;
  static constexpr unsigned int width = 1 << 9;
  static constexpr unsigned int height = static_cast<unsigned int>(width / aspectRatio);
  //static constexpr unsigned int height = 1 << 8;
  static constexpr unsigned int channels = 4; //3::RGB, 4::RGBA
  static constexpr unsigned int pixelSamples = 100;
  static constexpr unsigned int maxDepth = 50;
}

namespace camera {
  static float viewportHeight = 2.0f;
  static float viewportWidth = image::aspectRatio * viewportHeight;
  static float focalLength = 1.0f;

  static rtm::vec3 origin{ 0.0f, 0.0f, 0.0f };
  static rtm::vec3 horizontal{ viewportWidth, 0.0f, 0.0f };
  static rtm::vec3 vertical{ 0.0f, viewportHeight, 0.0f };
  static rtm::vec3 lowerLeftCorner = origin - (horizontal / 2.0f) -
    (vertical / 2.0f) - rtm::vec3(0.0f, 0.0f, focalLength);

  inline static rtm::ray getRay(float u, float v) {
    rtm::vec3 rayOrgin{ origin };
    rtm::vec3 rayDirection{ lowerLeftCorner + (u * horizontal) + (v * vertical) - origin };
    return rtm::ray(rayOrgin, rayDirection);
  }
}

namespace constants {
  constexpr float infinity = std::numeric_limits<float>::infinity();
  constexpr float pi = 3.1415926535897932385f;
}

namespace utility {
  inline float degreesToRadians(float degree) {
    return (degree * constants::pi / 180.0f);
  }

  inline float clamp(const float x, const float min, const float max) {
    return std::clamp(x, min, max);
  }

  inline float randomFloat() {
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
  }

  inline float randomFloat(float min, float max) {
    return min + ((max - min) * randomFloat());
  }

  inline static rtm::vec3 random() {
    return  rtm::vec3(utility::randomFloat(), utility::randomFloat(), utility::randomFloat());
  }

  inline static rtm::vec3 random(float min, float max) {
    return  rtm::vec3(utility::randomFloat(min, max), utility::randomFloat(min, max), utility::randomFloat(min, max));
  }

  inline static rtm::vec3 randomInUnitSphere() {
    while (true) {
      rtm::vec3 p = random(-1.0f, 0.0f);
      if (p.LengthSquared() >= 1) continue;
      return p;
    }
  }

  inline static rtm::vec3 randomUnitVector() {
    float a = randomFloat(0.0f, 2.0f * constants::pi);
    float z = randomFloat(-1.0f, 1.0f);
    float r = std::sqrt(1.0f - std::pow(z, 2));

    return rtm::vec3(r * std::cos(a), r * std::sin(a), z);
  }

  inline static rtm::vec3 randomInHemisphere(const rtm::vec3& normal) {
    rtm::vec3 inUnitSphere = randomInUnitSphere();

    if (rtm::dot(inUnitSphere, normal) > 0.0f)
      return inUnitSphere;
    else
      return -inUnitSphere;
  }
}

#endif // !UTILITY_080920_H
