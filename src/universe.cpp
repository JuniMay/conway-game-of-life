#include <cstdint>
#include <iostream>

#include <common.h>
#include <universe.h>

using namespace std;

Universe::Universe(uint32_t _height, uint32_t _width)
    : height(_height), width(_width) {}

Universe::~Universe() {}

void Universe::set_cell(uint32_t row, uint32_t col, Cell state) {
  cells[get_index(row, col)] = state;
}


Cell Universe::get_cell(uint32_t row, uint32_t col) {
  return cells[get_index(row, col)];
}

uint32_t Universe::get_index(uint32_t row, uint32_t col) const {
  return (row * width + col);
}

bool Universe::valid(uint32_t row, uint32_t col) {
  return (row >= 0 && col >= 0 && row < height && col < width);
}

uint32_t Universe::count(uint32_t row, uint32_t col, const vector<Cell> &gen) {
  uint32_t cnt = 0;

  if (valid(row - 1, col - 1)) {
    cnt += gen[get_index(row - 1, col - 1)];
  }
  if (valid(row - 1, col)) {
    cnt += gen[get_index(row - 1, col)];
  }
  if (valid(row - 1, col + 1)) {
    cnt += gen[get_index(row - 1, col + 1)];
  }
  if (valid(row, col - 1)) {
    cnt += gen[get_index(row, col - 1)];
  }
  if (valid(row, col + 1)) {
    cnt += gen[get_index(row, col + 1)];
  }
  if (valid(row + 1, col - 1)) {
    cnt += gen[get_index(row + 1, col - 1)];
  }
  if (valid(row + 1, col)) {
    cnt += gen[get_index(row + 1, col)];
  }
  if (valid(row + 1, col + 1)) {
    cnt += gen[get_index(row + 1, col + 1)];
  }

  return cnt;
}

void Universe::evolve() {
  vector<Cell> _cells(cells);

  for (uint32_t row = 0; row < height; row++) {
    for (uint32_t col = 0; col < width; col++) {
      uint32_t cnt = count(row, col, _cells);
      uint32_t idx = get_index(row, col);

      if (_cells[idx] == Alive) {
        if (cnt < 2) {
          cells[idx] = Dead;
        } else if (cnt == 2 || cnt == 3) {
          cells[idx] = Alive;
        } else {
          cells[idx] = Dead;
        }
      } else {
        if (cnt == 3) {
          cells[idx] = Alive;
        }
      }
    }
  }
}

cells_output_t Universe::output(uint32_t on, uint32_t off) {
  cells_output_t cells_output(new uint32_t[height * width]);
  for (uint32_t row = 0; row < height; row++) {
    for (uint32_t col = 0; col < width; col++) {
      uint32_t idx = get_index(row, col);
      if (cells[idx] == Alive) {
        cells_output[idx] = on;
      } else {
        cells_output[idx] = off;
      }
    }
  }
  return cells_output;
}

ostream &operator<<(ostream &stream, const Universe &u) {
  for (uint32_t row = 0; row < u.height; row++) {
    for (uint32_t col = 0; col < u.width; col++) {
      stream << (u.cells[u.get_index(row, col)] ? "◼" : "◻");
    }
    stream << endl;
  }
  return stream;
}