extern "C" {
  #include "tinyPTC/tinyptc.h"
}

#include "util/typeAliases.hpp"

namespace ECS {

class RenderSystem
{
public:

  explicit RenderSystem(size_type width = 800, size_type height = 600)
  : _width  {width}
  , _height {height}
  , _screen {std::make_unique<pixel_type[]>(_width * _height)}
  {
    ptc_open("Juego", _width, _height);
    std::fill(_screen.get(), _screen.get() + _width * _height, greenColor);
  }

  ~RenderSystem()
  {
    ptc_close();
  }

  void update()
  {
    ptc_update(_screen.get());
  }

private:
  const size_type _width {}, _height {};
  std::unique_ptr<pixel_type[]> _screen{};
};

} // namespace ECS