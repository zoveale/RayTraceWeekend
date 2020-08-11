#ifndef VEC3_080720_H
#define VEC3_080720_H

#include <cmath>


namespace rtm { class vec3; }
class rtm::vec3 {
public:
  vec3() : values{ 0.0f, 0.0f, 0.0f }, x(values[0]), y(values[1]), z(values[2]){}
  vec3(float xx, float yy, float zz) :values{ xx, yy, zz }, x(values[0]), y(values[1]), z(values[2]) {}
  vec3(float xx) :values{ xx, xx, xx }, x(values[0]), y(values[1]), z(values[2]) {}
  vec3 operator-() const { return vec3(-values[0], -values[1], -values[2]); }
  float operator[](int i) const { return values[i]; }
  float& operator[](int i) { return values[i]; }

  vec3& operator+=(const vec3& v) {
    values[0] += v[0];
    values[1] += v[1];
    values[2] += v[2];
    return *this;
  }

  vec3& operator*=(const float v) {
    values[0] *= v;
    values[1] *= v;
    values[2] *= v;
    return *this;
  }

  vec3& operator/=(const float u) { return *this *= (1.0f / u); }

  float Length() const {
    return std::sqrt(LengthSquared());
  }
  ~vec3() {};

  float LengthSquared() const {
    return pow(values[0], 2) + pow(values[1], 2) + pow(values[2], 2);
  }

  //copy constructor
  inline vec3& operator=(const vec3& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
  }

  

public:
  float values[3];
  float& x;
  float& y;
  float& z;
private:
  //LengthSquared()
};

namespace rtm {

  inline vec3 operator+(const vec3& u, const vec3& v) {
    return vec3(u.values[0] + v.values[0],
      u.values[1] + v.values[1],
      u.values[2] + v.values[2]);
  }

  inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.values[0] - v.values[0],
      u.values[1] - v.values[1],
      u.values[2] - v.values[2]);
  }

  inline vec3 operator*(const vec3& u, const vec3& v) {
    return vec3(u.values[0] * v.values[0],
      u.values[1] * v.values[1],
      u.values[2] * v.values[2]);
  }

  inline vec3 operator*(float u, const vec3& v) {
    return vec3(u * v.values[0], u * v.values[1], u * v.values[2]);
  }

  inline vec3 operator*(const vec3& v, float u) {
    return u * v;
  }

  inline vec3 operator/(vec3 v, float u) {
    return (1.0f / u) * v;
  }

  

  inline float dot(const vec3& u, const vec3& v) {
    return u.values[0] * v.values[0]
      + u.values[1] * v.values[1]
      + u.values[2] * v.values[2];
  }

  inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.values[1] * v.values[2] - u.values[2] * v.values[1],
      u.values[2] * v.values[0] - u.values[0] * v.values[2],
      u.values[0] * v.values[1] - u.values[1] * v.values[0]);
  }


  inline vec3 unitVector(vec3 v) {
    return v / v.Length();
  }

  inline vec3 reflect(const rtm::vec3& v, const rtm::vec3& n) {
    return v - (2.0f * dot(v, n) * n);
  }
}


#endif // !VEC3_080720_H



