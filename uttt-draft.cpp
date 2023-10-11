#include <iostream>
#include <math.h>

using namespace std;

enum CellOwner {
  None,
  Player1,
  Player2,
};
typedef char LLCell;

class Board {
public:
  CellOwner winner;

public:
  Board();
  virtual bool check_win(const int INDEX, const CellOwner OWNER) const;
  virtual void set_cell_owner(const int INDEX, const CellOwner OWNER);
};

class SubBoard : virtual public Board {
private:
  LLCell cells[9];

public:
  SubBoard();
  bool check_win(const int INDEX, const CellOwner OWNER) const;
  void set_cell_owner(const int INDEX, const CellOwner OWNER);
};

class MainBoard : virtual public Board {
private:
  SubBoard cells[9];

public:
  MainBoard();
  bool check_win(const int INDEX, const CellOwner OWNER) const;
  void set_cell_owner(const int INDEX, const CellOwner OWNER);
};

// Helper functions
unsigned int negative_mod(int a, int b) {
  return a - (b * floor((double)a / b));
}

void horizontal_others(const int INDEX, int &other1, int &other2) {
  other1 = negative_mod(INDEX - 1, 3);
  other2 = (INDEX + 1) % 3;
}
void vertial_others(const int INDEX, int &other1, int &other2) {
  other1 = negative_mod(INDEX - 3, 9);
  other2 = (INDEX + 3) % 9;
}
void diagonal_fours_others(const int INDEX, int &other1, int &other2) {
  other1 = negative_mod(INDEX - 4, 12);
  other2 = (INDEX + 4) % 12;
}
void diagonal_twos_others(const int INDEX, int &other1, int &other2) {
  other1 = negative_mod(INDEX - 2, 10);
  other2 = (INDEX + 2) % 10;
}

// constructors
Board::Board() { this->winner = None; }
SubBoard::SubBoard() : Board() {}
MainBoard::MainBoard() : Board() {}

void SubBoard::set_cell_owner(const int INDEX, const CellOwner OWNER) {}
void MainBoard::set_cell_owner(const int INDEX, const CellOwner OWNER) {}

// check victory
bool SubBoard::check_win(const int INDEX, const CellOwner OWNER) const {
  int horizontal_other1, horizontal_other2;
  int vertical_other1, vertical_other2;

  horizontal_others(INDEX, horizontal_other1, horizontal_other2);
  vertial_others(INDEX, vertical_other1, vertical_other2);

  // set diagonal_other indexes
  // diagonals are only sometimes valid:
  // |0| |2|
  // | |4| |
  // |6| |8|
  bool include_diagonals2 = true;
  bool include_diagonals4 = true;
  int diagonal_other1, diagonal_other2;
  int diagonal_other3, diagonal_other4;
  if (INDEX % 2 != 0) {
    include_diagonals2 = false;
    include_diagonals4 = false;
  } else if (INDEX == 4) {
    diagonal_twos_others(INDEX, diagonal_other1, diagonal_other2);
    diagonal_fours_others(INDEX, diagonal_other3, diagonal_other4);
  } else if (INDEX % 4) {
    include_diagonals2 = false;
    diagonal_fours_others(INDEX, diagonal_other3, diagonal_other4);
  } else {
    include_diagonals4 = false;
    diagonal_twos_others(INDEX, diagonal_other1, diagonal_other2);
  }

  return this->cells[INDEX] == OWNER &&
         (this->cells[horizontal_other1] == OWNER &&
              this->cells[horizontal_other2] == OWNER ||
          this->cells[vertical_other1] == OWNER &&
              this->cells[vertical_other2] == OWNER ||
          include_diagonals2 && this->cells[diagonal_other1] == OWNER &&
              this->cells[diagonal_other2] == OWNER ||
          include_diagonals4 && this->cells[diagonal_other3] == OWNER &&
              this->cells[diagonal_other4] == OWNER);
}

bool MainBoard::check_win(const int INDEX, const CellOwner OWNER) const {
  int horizontal_other1, horizontal_other2;
  int vertical_other1, vertical_other2;

  horizontal_others(INDEX, horizontal_other1, horizontal_other2);
  vertial_others(INDEX, vertical_other1, vertical_other2);

  // set diagonal_other indexes
  // diagonals are only sometimes valid:
  // |0| |2|
  // | |4| |
  // |6| |8|
  bool include_diagonals2 = true;
  bool include_diagonals4 = true;
  int diagonal_other1, diagonal_other2;
  int diagonal_other3, diagonal_other4;
  if (INDEX % 2 != 0) {
    include_diagonals2 = false;
    include_diagonals4 = false;
  } else if (INDEX == 4) {
    diagonal_twos_others(INDEX, diagonal_other1, diagonal_other2);
    diagonal_fours_others(INDEX, diagonal_other3, diagonal_other4);
  } else if (INDEX % 4) {
    include_diagonals2 = false;
    diagonal_fours_others(INDEX, diagonal_other3, diagonal_other4);
  } else {
    include_diagonals4 = false;
    diagonal_twos_others(INDEX, diagonal_other1, diagonal_other2);
  }

  return this->cells[INDEX].winner == OWNER &&
         (this->cells[horizontal_other1].winner == OWNER &&
              this->cells[horizontal_other2].winner == OWNER ||
          this->cells[vertical_other1].winner == OWNER &&
              this->cells[vertical_other2].winner == OWNER ||
          include_diagonals2 && this->cells[diagonal_other1].winner == OWNER &&
              this->cells[diagonal_other2].winner == OWNER ||
          include_diagonals4 && this->cells[diagonal_other3].winner == OWNER &&
              this->cells[diagonal_other4].winner == OWNER);
}
