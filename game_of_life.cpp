#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int ROWS = 20;
const int COLS = 20;

void generate_initial_state(std::vector<std::vector<int>>& grid) {
    srand(time(0));
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            grid[i][j] = rand() % 2;
        }
    }
}

int count_neighbors(const std::vector<std::vector<int>>& grid, int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int r = row + i;
            int c = col + j;
            if (r >= 0 && r < ROWS && c >= 0 && c < COLS) {
                count += grid[r][c];
            }
        }
    }
    return count;
}

void update_grid(std::vector<std::vector<int>>& grid) {
    std::vector<std::vector<int>> new_grid = grid;
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int neighbors = count_neighbors(grid, i, j);
            if (grid[i][j] == 1) {
                if (neighbors < 2 || neighbors > 3) {
                    new_grid[i][j] = 0;
                }
            } else {
                if (neighbors == 3) {
                    new_grid[i][j] = 1;
                }
            }
        }
    }
    grid = new_grid;
}

void print_grid(const std::vector<std::vector<int>>& grid) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            std::cout << (grid[i][j] ? '*' : ' ') << ' ';
        }
        std::cout << '\n';
    }
}

int main() {
    std::vector<std::vector<int>> grid(ROWS, std::vector<int>(COLS, 0));
    generate_initial_state(grid);

    while (true) {
        print_grid(grid);
        update_grid(grid);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::system("clear");
    }

    return 0;
}
