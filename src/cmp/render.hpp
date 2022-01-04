#include "utility/typeAliases.hpp"

namespace ECS {

class RenderComponent 
{
  explicit RenderComponent(size_type x, size_type y,
                           size_type width, size_type height)
  : _x{x}, _y{y}, _width{width} ,_height{height}
  , _sprite{ std::make_unique<pixel_type>(_width * _height)}
  {
    std::fill(_sprite.get(), _sprite.get() + _width * _height, blueColor);
  }

private:
  std::unique_ptr<pixel_type[]> _sprite{};
  size_type _x{}, _y{};
  const size_type _width{}, _height{}; 
}

} // namespace ECS
