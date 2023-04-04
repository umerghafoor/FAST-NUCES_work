#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

int*** init(int dimension);
void print_reward_locations(int*** matrix, int dimension);
void play_game(int*** matrix, int dimension);

int main() {
    int dimension;
    cout << "Enter dimension (length, breadth and height) of the matrix: ";
    cin >> dimension;
    int*** matrix = init(dimension);
    bool quit = false;
    int choice;
    while (!quit) {
        cout << "Enter choice:\n1. Initialize\n2. Print matrix\n3. Play\n4. Quit\n";
        cin >> choice;
        switch (choice) {
        case 1:
            matrix = init(dimension);
            break;
        case 2:
            print_reward_locations(matrix, dimension);
            break;
        case 3:
            play_game(matrix, dimension);
            break;
        case 4:
            quit = true;
            break;
        default:
            cout << "Invalid choice!\n";
            break;
        }
    }
    return 0;
}

int*** init(int dimension) {
    // Allocate memory for the 4D matrix
    int*** matrix = new int** [dimension];
    for (int i = 0; i < dimension; i++) {
        matrix[i] = new int* [dimension];
        for (int j = 0; j < dimension; j++) {
            matrix[i][j] = new int[3];
            for (int k = 0; k < 3; k++) {
                matrix[i][j][k] = rand() % 10 < 4 ? rand() % 10 + 1 : 0;
            }
        }
    }
    return matrix;
}

void print_reward_locations(int*** matrix, int dimension) {
    cout << "Reward Locations:\n";
    int reward_count = 0;
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            for (int k = 0; k < 3; k++) {
                if ((matrix[i][j][k]) > 0) {
                    cout << "Reward_" << ++reward_count << ": " << i << "," << j << "," << k << ",";
                    switch (k) {
                    case 0:
                        cout << "PAST";
                        break;
                    case 1:
                        cout << "PRESENT";
                        break;
                    case 2:
                        cout << "FUTURE";
                        break;
                    }
                    cout << endl;
                }
            }
        }
    }
}

void play_game(int*** matrix, int dimension) {
    int moves;
    cout << "Enter number of moves: ";
    cin >> moves;
    int x = rand() % dimension;
    int y = rand() % dimension;
    int z = 1; // start in the present
    int score = 0;
    for (int i = 0; i < moves; i++) {
        cout << "Current position: (" << x << ", " << y << ", ";
        switch (z) {
        case 0:
            cout << "PAST";
            break;
        case 1:
            cout << "PRESENT";
            break;
        case 2:
            cout << "FUTURE";
            break;
        }
        cout << ")\n";
        score += matrix[x][y][z];
        if (matrix[x][y][z] > 0) {
            cout << "Reward found! +" << matrix[x][y][z] << " points\n";
        }
        int direction;
        cout << "Enter direction (0 = left, 1 = right, 2 = up, 3 = down, 4 = back, 5 = forward): ";
        cin >> direction;
        switch (direction) {
        case 0:
            x--;
            break;
        case 1:
            x++;
            break;
        case 2:
            y--;
            break;
        case 3:
            y++;
            break;
        case 4:
            z--;
            break;
        case 5:
            z++;
            break;
        default:
            cout << "Invalid direction!\n";
            break;
        }
        if (x < 0 || x >= dimension || y < 0 || y >= dimension || z < 0 || z >= 3) {
            cout << "Out of bounds!\n";
            break;
        }
    }
    cout << "Final score: " << score << "\n";
}
