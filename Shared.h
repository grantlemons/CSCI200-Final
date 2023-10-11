#ifndef SHARED
#define SHARED

enum CellOwner {
    None,
    Player1,
    Player2,
};

typedef char LLCell;

void print_owner(const CellOwner OWNER);

// Helper functions
unsigned int negative_mod(int a, int b);
void horizontal_others(const int INDEX, int &other1, int &other2);
void vertical_others(const int INDEX, int &other1, int &other2);
void diagonal_fours_others(const int INDEX, int &other1, int &other2);
void diagonal_twos_others(const int INDEX, int &other1, int &other2);

#endif // !SHARED
