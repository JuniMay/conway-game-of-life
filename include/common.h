#include <memory>

#define WIDTH 80
#define HEIGHT 50
#define SCALE 15
#define ON_COLOR 0x66D9EF
#define OFF_COLOR 0x272822

typedef std::unique_ptr<uint32_t[]> cells_output_t;