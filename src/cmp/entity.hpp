#include "util/typeAliases.hpp"
#include "render.hpp"

namespace ECS {

class Entity
{
public:
  size_type id { return _id };
  RenderComponent* renderComponent() { return _render };


private:
  inline size_type _id{ ++_nextId };
  inline static size_type _nextId{ 0 };
  
  RenderComponent* _render{};


}

}