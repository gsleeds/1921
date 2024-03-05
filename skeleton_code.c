#include <stdio.h>
#include <stdlib.h>

#define MAX_HEIGHT 100
#define MIN_HEIGHT 5
#define MAX_WIDTH 100
#define MIN_WIDTH 5

// Struct definition for a maze
typedef struct {
    char** cells;
    int height;
    int width;
    int playerRow;
    int playerCol;
} Maze;

// Function to initialize the maze structure
Maze* initializeMaze(char* filename);

// Function to display the maze
void displayMaze(const Maze* maze);

// Function to handle player movement
void movePlayer(Maze* maze, char direction);

// Function to check if the player has reached the exit
int hasReachedExit(const Maze* maze);

// Function to free memory allocated for the maze
void freeMaze(Maze* maze);

// Main function
int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <maze_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Load maze from the command line argument
    Maze* maze = initializeMaze(argv[1]);

    if (maze == NULL) {
        fprintf(stderr, "Error loading maze from file.\n");
        return EXIT_FAILURE;
    }

    // Main game loop
    char userInput;
    do {
        displayMaze(maze);
        printf("Enter your move (W/A/S/D/M): ");
        scanf(" %c", &userInput);

        movePlayer(maze, userInput);

        if (hasReachedExit(maze)) {
            printf("Congratulations! You've reached the exit.\n");
            break;
        }
    } while (userInput != 'Q' && userInput != 'q'); // Assume 'Q' or 'q' to quit

    // Free allocated memory
    freeMaze(maze);

    return EXIT_SUCCESS;
}