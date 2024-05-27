#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int gridSize = 5;
const int numShips = 3;

void initializeGrid(char grid[gridSize][gridSize]) {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            grid[i][j] = '~'; // '~' represents water
        }
    }
}

void placeShips(char grid[gridSize][gridSize]) {
    srand(time(0));
    int placedShips = 0;
    while (placedShips < numShips) {
        int x = rand() % gridSize;
        int y = rand() % gridSize;
        if (grid[x][y] != 'S') {
            grid[x][y] = 'S'; // 'S' represents a ship
            placedShips++;
        }
    }
}

void displayGrid(char grid[gridSize][gridSize], bool revealShips = false) {
    cout << "  ";
    for (int i = 0; i < gridSize; ++i) {
        cout << i << " ";
    }
    cout << endl;
    for (int i = 0; i < gridSize; ++i) {
        cout << i << " ";
        for (int j = 0; j < gridSize; ++j) {
            if (revealShips) {
                cout << grid[i][j] << " ";
            } else {
                if (grid[i][j] == 'S') {
                    cout << '~' << " ";
                } else {
                    cout << grid[i][j] << " ";
                }
            }
        }
        cout << endl;
    }
}

bool takeShot(char grid[gridSize][gridSize], int x, int y) {
    if (grid[x][y] == 'S') {
        grid[x][y] = 'H'; // 'H' represents a hit ship
        return true;
    } else if (grid[x][y] == '~') {
        grid[x][y] = 'M'; // 'M' represents a miss
    }
    return false;
}

bool allShipsSunk(char grid[gridSize][gridSize]) {
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (grid[i][j] == 'S') {
                return false;
            }
        }
    }
    return true;
}

int main() {
    char grid[gridSize][gridSize];
    initializeGrid(grid);
    placeShips(grid);

    int x, y;
    int shots = 0;

    cout << "Welcome to Battleship!" << endl;
    while (!allShipsSunk(grid)) {
        displayGrid(grid);
        cout << "Enter coordinates to fire (row and column): ";
        cin >> x >> y;
        
        if (x < 0 || x >= gridSize || y < 0 || y >= gridSize) {
            cout << "Invalid coordinates. Try again." << endl;
            continue;
        }

        if (takeShot(grid, x, y)) {
            cout << "Hit!" << endl;
        } else {
            cout << "Miss!" << endl;
        }
        shots++;
    }

    cout << "Congratulations! You've sunk all the ships in " << shots << " shots." << endl;
    displayGrid(grid, true);
    return 0;
}

