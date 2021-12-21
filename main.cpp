#include <iostream>
#include <memory>
#include <cstring>
#include <signal.h>
#include <cstdint>
extern "C" {
  #include "tinyPTC/tinyptc.h"
}

#include "slotMap.h"

bool keepRunning { true };
constexpr std::size_t WIDTH{ 800 }, HEIGHT{ 600 }, SCREEN_BUFFER_SIZE{ WIDTH * HEIGHT};
constexpr uint32_t redColor   { 0x00FF0000 };
constexpr uint32_t greenColor { 0x0000FF00 };
constexpr uint32_t blueColor  { 0x000000FF };
uint32_t *screen { nullptr };

void initScreen()
{
  screen = new uint32_t[SCREEN_BUFFER_SIZE];

  std::fill(screen, screen + SCREEN_BUFFER_SIZE, greenColor);
  


}

void sigintHandler(int dummy)
{
  std::cout << "handler sigint \n";
  keepRunning = false;
}

int game(void)
{
  int returnValue{0};

  returnValue = ptc_open("My Juego", WIDTH, HEIGHT);
  initScreen();

  while(keepRunning)
  {
    ptc_update(screen);
  }

  delete[] screen;
  ptc_close();

  return returnValue;
}

int main()
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
