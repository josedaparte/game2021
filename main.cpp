#include <iostream>
#include <memory>
#include <cstring>
#include <signal.h>
#include <cstdint>


#include "slotMap.h"
#include "sys/render.hpp"

bool keepRunning { true };



void sigintHandler(int dummy)
{
  std::cout << "handler sigint \n";
  keepRunning = false;
}

int game(void)
{
  int returnValue{0};

  ECS::RenderSystem renderSystem{800, 600};

  while(keepRunning)
  {
    renderSystem.update();
  }


  return returnValue;
}

int main(int argc, char** argv)
{

  signal(SIGINT, sigintHandler);

  SlotMap components{};


  try
  {
    if (!game())
      std::cout << "Fallo en abrir la ventana\n";
  }
  catch (std::exception const &e)
  {
    std::cerr << "[EXCEPTION]: " << e.what() << "\n";
  }

  return 0;
}
