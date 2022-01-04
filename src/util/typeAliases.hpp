#include <cstdint>

namespace ECS
{
// data types
  using pixel_type = std::size_t;
  using size_type = std::size_t;

// Basic colors
  static constexpr pixel_type redColor   { 0x00FF0000 };
  static constexpr pixel_type greenColor { 0x0000FF00 };
  static constexpr pixel_type blueColor  { 0x000000FF };

}