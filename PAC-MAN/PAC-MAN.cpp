#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h> // For _getch() and _kbhit()
using namespace std;

const int WIDTH = 20;  // Width of the maze
const int HEIGHT = 10; // Height of the maze

// Characters for the maze
const char WALL = '#';
const char EMPTY = ' ';
const char DOT = '.';
const char PACMAN = 'P'; // Represents Pac-Man
const char GHOST = 'G';// Represents the ghost

// Directions
enum Direction { STOP, UP, DOWN, LEFT, RIGHT };
Direction pacmanDir = STOP;

// Maze array
char maze[HEIGHT][WIDTH];

// Positions
int pacmanX, pacmanY;
int ghostX, ghostY;
char ghostLast = DOT; // Stores what was in the ghost's previous position

// Game variables
bool gameOver = false;
int dotsLeft = 0;

// Function to initialize the maze
void initializeMaze() {
    srand(time(0)); // Seed random number generator

    // Create maze with walls and dots
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1) {
                maze[i][j] = WALL; // Boundary walls
            }
            else {
                maze[i][j] = DOT;  // Fill the maze with dots
                dotsLeft++;
            }
        }
    }

    // Place Pac-Man at a random position
    pacmanX = rand() % (HEIGHT - 2) + 1;
    pacmanY = rand() % (WIDTH - 2) + 1;
    maze[pacmanX][pacmanY] = PACMAN;
    dotsLeft--;

    // Place Ghost at a random position
    do {
        ghostX = rand() % (HEIGHT - 2) + 1;
        ghostY = rand() % (WIDTH - 2) + 1;
    } while (maze[ghostX][ghostY] != DOT); // Ensure ghost doesn't overwrite Pac-Man
    ghostLast = DOT; // The ghost starts on a dot
    maze[ghostX][ghostY] = GHOST;
}

// Function to display the maze
void displayMaze() {
    system("cls"); // Clear the screen
    cout << " PAC-MAN C++ GAME. " << endl;
    cout << " Instruction: \n P = Pac-man, G = Ghost. \n Use w = up , s = down , a = left , d = right. \n";
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cout << maze[i][j];
        }
        cout << endl;
    }
    cout << "Dots left: " << dotsLeft << endl;
}

// Function to handle input
void handleInput() {
    if (_kbhit()) { // Check if a key was pressed
        switch (_getch()) {
        case 'w': pacmanDir = UP; break;
        case 's': pacmanDir = DOWN; break;
        case 'a': pacmanDir = LEFT; break;
        case 'd': pacmanDir = RIGHT; break;
        }
    }
}

// Function to update Pac-Man's position
void updatePacman() {
    maze[pacmanX][pacmanY] = EMPTY; // Clear old position

    switch (pacmanDir) {
    case UP: if (maze[pacmanX - 1][pacmanY] != WALL) pacmanX--; break;
    case DOWN: if (maze[pacmanX + 1][pacmanY] != WALL) pacmanX++; break;
    case LEFT: if (maze[pacmanX][pacmanY - 1] != WALL) pacmanY--; break;
    case RIGHT: if (maze[pacmanX][pacmanY + 1] != WALL) pacmanY++; break;
    default: break;
    }

    if (maze[pacmanX][pacmanY] == DOT) {
        dotsLeft--; // Collect dot
    }
    maze[pacmanX][pacmanY] = PACMAN; // Update new position
}

// Function to update Ghost's position
void updateGhost() {
    maze[ghostX][ghostY] = ghostLast; // Restore what was in the ghost's old position

    // Random movement for the ghost
    int move = rand() % 4;
    switch (move) {
    case 0: if (maze[ghostX - 1][ghostY] != WALL && maze[ghostX - 1][ghostY] != PACMAN) ghostX--; break;
    case 1: if (maze[ghostX + 1][ghostY] != WALL && maze[ghostX + 1][ghostY] != PACMAN) ghostX++; break;
    case 2: if (maze[ghostX][ghostY - 1] != WALL && maze[ghostX][ghostY - 1] != PACMAN) ghostY--; break;
    case 3: if (maze[ghostX][ghostY + 1] != WALL && maze[ghostX][ghostY + 1] != PACMAN) ghostY++; break;
    }

    // Check for collision
    if (ghostX == pacmanX && ghostY == pacmanY) {
        gameOver = true; // Pac-Man is caught
    }

    ghostLast = maze[ghostX][ghostY]; // Save what the ghost is overwriting
    maze[ghostX][ghostY] = GHOST;    // Update new position
}

// Main game loop
void gameLoop() {
    while (!gameOver && dotsLeft > 0) {
        displayMaze();
        handleInput();
        updatePacman();
        updateGhost();
    }

    // Game over messagew
    displayMaze();
    if (gameOver) {
        cout << "Game Over! Pac-Man was caught by the ghost." << endl;
    }
    else {
        cout << "Congratulations! Pac-Man collected all the dots!" << endl;
    }
}

int main() {
    initializeMaze();
    gameLoop();

    // Pause before exiting
    cout << "Press any key to exit..." << endl;
    _getch(); // Wait for the user to press a key
    return 0;
}
