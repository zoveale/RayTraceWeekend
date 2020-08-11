#include "utility.h"

namespace image {
  constexpr float aspectRatio = 16.0f / 9.0f;
  constexpr unsigned int width = 1 << 9;
  constexpr unsigned int height = static_cast<unsigned int>(width / aspectRatio);
  //constexpr unsigned int height = 1 << 8;
  constexpr unsigned int channels = 4; //3::RGB, 4::RGBA
  constexpr unsigned int pixelSamples = 100;
  constexpr unsigned int maxDepth = 50;
}

namespace camera {
  float viewportHeight = 2.0f;
  float viewportWidth = image::aspectRatio * viewportHeight;
  float focalLength = 1.0f;

  rtm::vec3 origin{ 0.0f, 0.0f, 0.0f };
  rtm::vec3 horizontal{ viewportWidth, 0.0f, 0.0f };
  rtm::vec3 vertical{ 0.0f, viewportHeight, 0.0f };
  rtm::vec3 lowerLeftCorner = origin - (horizontal / 2.0f) -
    (vertical / 2.0f) - rtm::vec3(0.0f, 0.0f, focalLength);

  inline rtm::ray getRay(float u, float v) {
    rtm::vec3 rayOrgin{ origin };
    rtm::vec3 rayDirection{ lowerLeftCorner + (u * horizontal) + (v * vertical) - origin };
    return rtm::ray(rayOrgin, rayDirection);
  }
}