#include "ray.h"
#include "geometry.h"


//rtm::vec3 rtm::ray::color(const rtm::ray& ray, const rtm::polygon& shapes) {
//  {
//    //float 
//    rtm::hitRecord record;
//     bool t{ shapes.hit(ray, 0.0f, 1.0f, record) };
//    
//    if (shapes.hit(ray, 0.0f, )) {
//      rtm::vec3 normal{ rtm::unitVector(ray.at(t) - shapes.center())};
//      rtm::vec3 pixelColor(normal.x + 1.0f, normal.y + 1.0f, normal.z + 1.0f);
//      return 0.5f * pixelColor;
//    }
//
//    rtm::vec3 unitDirection(rtm::unitVector(ray.direction));
//    t = 0.5f * (unitDirection.y + 1.0f);
//
//    //liner interpolate function, lerp 
//    return ((1.0f - t) * rtm::vec3(1.0f, 1.0f, 1.0f)) + (t * rtm::vec3(0.5f, 0.7f, 1.0f));
//  }
//}
