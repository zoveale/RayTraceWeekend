#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "utility.h"


/*function prototypes*/
void WritePixels(const int width, const int height,
  rtm::vec3 pixelColor, std::int_least8_t* pixels,
  int& index);
rtm::vec3 RayColor(const rtm::ray& ray, const rtm::polygon& world, int depth);


int main(int argc, char** argv) {
  int pixelDepth = image::channels; // 4 bytes for each pixel
  int pixelTotal = image::width * image::height; //total number of pixels
  int pixelMemory = pixelDepth * pixelTotal; //total bytes needed 
  //std::int_least8_t* pixels = new std::int_least8_t[pixelMemory];//total number of chars needed for image
  std::vector< int_least8_t> pixels(pixelMemory);

  std::shared_ptr<rtm::metal> matOne{ std::make_shared<rtm::metal>(rtm::vec3(0.8f, 0.8f, 0.0f), 0.3f) };
  auto matTwo{ std::make_shared<rtm::metal>(rtm::vec3(0.7f, 0.3f, 0.3f), 1.0f) };
  auto matThree{ std::make_shared<rtm::lambertian>(rtm::vec3(0.8f, 0.8f, 0.8f)) };
  auto matFour{ std::make_shared<rtm::lambertian>(rtm::vec3(0.8f, 0.6f, 0.2f)) };

  rtm::polygonList world;
  world.add((std::make_shared<rtm::sphere>(rtm::vec3(0.0f, -100.5f, -1.0f), 100.0f, matThree)));
  world.add((std::make_shared<rtm::sphere>(rtm::vec3(0.0f, 0.0f, -1.0f), 0.5f, matFour)));
  world.add((std::make_shared<rtm::sphere>(rtm::vec3(-1.0f, 0.0f, -1.0f), 0.5f, matOne)));
  world.add((std::make_shared<rtm::sphere>(rtm::vec3(1.0f, 0.0f, -1.0f), 0.5f, matTwo)));
  // Render
  int index = 0;
  for (int j = image::height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines remaining: " << j << ' ';// << std::flush;
    for (int i = 0; i < image::width; ++i) {
      rtm::vec3 pixelColor(0.0f);
      for(int k = 0; k < image::pixelSamples; ++k){

        float u{ float(i + utility::randomFloat()) / (image::width - 1) };
        float v{ float(j + utility::randomFloat()) / (image::height - 1) };

        rtm::ray ray{ camera::getRay(u, v) };

        pixelColor += RayColor(ray, world, image::maxDepth);
      }

      WritePixels(image::width, image::height, pixelColor, &pixels[0], index);
    }
  }

  stbi_write_png("image.png",
    image::width,
    image::height,
    image::channels, //RGB = 3, RGBA = 4
    &pixels[0], //the pixel data
    //distance in bytes from the first byte of a row of pixels to 
    //the first byte of the next row of pixels
    image::width * image::channels);

  //delete[] pixels;
  std::cerr << "\nDone.\n";


  //temp solution console keeps closing
  //fixed it was the command line >image.ppm
  //getchar();
  return 0;
}

void WritePixels(const int width, const int height,
  rtm::vec3 pixelColor, std::int_least8_t* pixels,
  int& index) {
    {//temp image.ppm file info
      float r{ pixelColor.x };
      float g{ pixelColor.y };
      float b{ pixelColor.z };

      float scale = 1.0f / (float)image::pixelSamples;
      r = std::sqrt(scale * r);
      g = std::sqrt(scale * g);
      b = std::sqrt(scale * b);

      r = std::move(256.0f * utility::clamp(r, 0.0f, 0.999f));
      g = std::move(256.0f * utility::clamp(g, 0.0f, 0.999f));
      b = std::move(256.0f * utility::clamp(b, 0.0f, 0.999f));

      pixels[index++] = static_cast<int_least8_t>(r);
      pixels[index++] = static_cast<int_least8_t>(g);
      pixels[index++] = static_cast<int_least8_t>(b);
      //alpha placeholder, 255 is max visibility 
      pixels[index++] = static_cast<int_least8_t>(255);
    }
}

rtm::vec3 RayColor(const rtm::ray& ray, const rtm::polygon& world, int depth) {
  rtm::hitRecord record;
  if (depth <= 0)
    return rtm::vec3(1.0f);

  if (world.hit(ray, 0.001f, constants::infinity, record)) {
    //rtm::vec3 target = record.point + record.normal + utility::randomInUnitSphere();
    //rtm::vec3 target = record.point + record.normal + utility::randomUnitVector();
    //rtm::vec3 target = record.point + record.normal + utility::randomInHemisphere(record.normal);
    //return 0.5f * (RayColor(rtm::ray(record.point, target - record.point), world, depth - 1));

    rtm::ray scattered;
    rtm::vec3 attenuation;
    if (record.materialPointer->scatter(ray, record, attenuation, scattered))
      return attenuation * (RayColor(scattered, world, depth - 1));
    return rtm::vec3(0.0f);
  }

  rtm::vec3 unitDirection = rtm::unitVector(ray.direction);
  float t = 0.5f * (unitDirection.y + 1.0f);
  return ((1.0f - t) * rtm::vec3(1.0f, 1.0f, 1.0f)) + (t * rtm::vec3(0.5f, 0.7f, 1.0f));
}
