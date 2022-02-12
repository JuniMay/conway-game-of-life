#include <cstdint>
#include <iostream>
#include <vector>

#include <common.h>

using namespace std;

enum Cell {
  Dead = 0,
  Alive = 1,
};

class Universe {
 private:
  uint32_t height, width;
  vector<Cell> cells{vector<Cell>(height * width, Dead)};

 public:
  Universe(uint32_t _width, uint32_t _height);
  ~Universe();

  void set_cell(uint32_t row, uint32_t col, Cell state);
  Cell get_cell(uint32_t row, uint32_t col);
  uint32_t get_index(uint32_t row, uint32_t col) const;
  bool valid(uint32_t row, uint32_t col);
  uint32_t count(uint32_t row, uint32_t col, const vector<Cell> &gen);
  void evolve();

  cells_output_t output(uint32_t on, uint32_t off);

  friend ostream &operator<<(ostream &stream, const Universe &u);
};
