#ifndef RAY_080820_H
#define RAY_080820_H

#include <array>

#include "vec3.h"


namespace rtm { class ray; }
namespace rtm { class polygon; }
namespace rtm { class sphere ; }



class rtm::ray {
public:
  ray(){}
  ray(const rtm::vec3 origin, const rtm::vec3 direction): origin(origin), direction(direction){}
  //standard position of ray function : P(t)

  rtm::vec3 at(float t) const { return origin + (t * direction); }


  //static rtm::vec3 color(const rtm::ray& ray, const rtm::polygon& shapes);
public:
  rtm::vec3 origin;
  rtm::vec3 direction;
};
#endif // !RAY_080820_H
