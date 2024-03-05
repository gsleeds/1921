#include <stdio.h>
#include <stdlib.h>

#define MAX_HEIGHT 100
#define MIN_HEIGHT 5
#define MAX_WIDTH 100
#define MIN_WIDTH 5

// Struct def
typedef struct {
    char** cells;
    int height;
    int width;
    int playerRow;
    int playerCol;
} Maze;

// Func to initialize the maze structure
Maze* initializeMaze(char* filename);

// Func to display the maze
void displayMaze(const Maze* maze);

// Func to handle player movement
void movePlayer(Maze* maze, char direction);

// Func to validate player move
int validateMove(const Maze* maze, int newRow, int newCol);

// Func to check if the player has reached the exit
int hasReachedExit(const Maze* maze);

// Func to validate the maze
int validateMaze(const Maze* maze);

// Func to free memory allocated for the maze
void freeMaze(Maze* maze);

// Main Func
int main(int argc, char* argv[]) {
    // Init maze
    Maze* maze = initializeMaze(argv[1]);

    // Check if maze init was successful
    if (maze == NULL) {
        fprintf(stderr, "Error loading maze from file.\n");
        return EXIT_FAILURE;
    }

    // Validate the maze
    if (!validateMaze(maze)) {
        fprintf(stderr, "Invalid maze.\n");
        freeMaze(maze);
        return EXIT_FAILURE;
    }

    // Main game loop
    char userInput;
    do {
        // Display the maze
        displayMaze(maze);

        // Get user input
        printf("Enter your move (W/A/S/D/M): ");
        scanf(" %c", &userInput);

        // Handle player movement
        movePlayer(maze, userInput);

        // Check if the player has reached the exit
        if (hasReachedExit(maze)) {
            printf("Congratulations! You've reached the exit.\n");
            break;
        }
    } while (userInput != 'Q' && userInput != 'q'); // Assume 'Q' or 'q' to quit

    // Free allocated memory
    freeMaze(maze);

    return EXIT_SUCCESS;
}