#include <iostream>
#include <memory>

#include <irrlicht/irrlicht.h>

#include "slotMap.h"

void destroyDevice(irr::IrrlichtDevice *p)
{
  p->drop();
}
using DEVICEDESTRUCTORTYPE = void (*)(irr::IrrlichtDevice *);

int game(void)
{
  int returnValue{0};

  std::unique_ptr<irr::IrrlichtDevice, DEVICEDESTRUCTORTYPE> device{
      irr::createDevice(irr::video::EDT_SOFTWARE,
                        irr::core::dimension2d<irr::u32>(640, 480),
                        16, false, false, false, 0),
      destroyDevice};

  if (!device.get())
    returnValue = 1;

  return returnValue;
}

int main()
{

  SlotMap components{};
  std::vector<SlotMap::key_type> k;

  k.push_back(components.push_back(1));
  k.push_back(components.push_back(2));
  k.push_back(components.push_back(3));
  k.push_back(components.push_back(4));

 std::cout << "Borrando elemento " << components.erase(k[0]) << "\n";
 std::cout << "Borrando elemento " << components.erase(k[1]) << "\n";
 auto kk = components.push_back(88);
 k.push_back(components.push_back(90));
 components.erase(kk);
 k.push_back(components.push_back(77));

  for (auto it : components.data_)
  {
    std::cout << it << " ";
  }


  // try
  // {
  //   if (game())
  //     std::cout << "Fallo en abrir la ventana\n";
  // }
  // catch (std::exception const &e)
  // {
  //   std::cerr << "[EXCEPTION]: " << e.what() << "\n";
  // }

  return 0;
}
