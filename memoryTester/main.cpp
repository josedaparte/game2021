#include <cstdio>
#include <cstdint>
#include <vector>

constexpr std::size_t defaultWidth{16};

std::size_t calculateLines(const std::size_t size, const std::size_t width = defaultWidth)
{
  auto const lines{size / width};
  return (size & 0xF) != 0 ? lines + 1 : lines;
}

void showMemoryLine(const uint8_t*mem, const std::size_t width = defaultWidth)
{
  printf("%16p || ", (void *)mem);
  for(std::size_t i{}; i < width; i++)
    printf(" %02X", mem[i]);

  printf(" || ");

  for(std::size_t i{}; i < width; i++)
  {
    auto c = (mem[i] > 31 && mem[i] < 128) ? mem[i] : '.';
    printf(" %c", c);
  }

  printf("\n");
}

// mem:   start memory addres to show
// size:  bytes to show
// width: width of a line of memory (default 16 bytes)
void printMemory(const uint8_t*mem, const std::size_t size, const std::size_t width = defaultWidth)
{
  const auto lines{calculateLines(size, width)};
  printf("     ADDRESS     ||  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\n");
  printf("-----------------||-------------------------------------------------\n");
  for (std::size_t i{}; i < lines; i++)
  {
    showMemoryLine(mem, width);
    mem += width;
  }
  printf("-----------------||-------------------------------------------------\n");
}

int main()
{
  std::vector<int> a{1, 2, 4, 8, 16, 32};
  
  // printf("%d ", *a.begin());
  // printf("%lu\n", sizeof(a));
  auto *p = reinterpret_cast<const uint8_t*>(&a);
  printMemory(p, 48);
  printf("\n");
  
  printMemory(reinterpret_cast<const uint8_t*>(a.begin().base()), sizeof(a));

  return 0;
}