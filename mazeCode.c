#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HEIGHT 100
#define MIN_HEIGHT 5
#define MAX_WIDTH 100
#define MIN_WIDTH 5

typedef struct {
    char** cells;
    int height;
    int width;
    int playerRow;
    int playerCol;
} Maze;

void freeMaze(Maze* maze);
int validateMove(const Maze* maze, int newRow, int newCol);
int hasReachedExit(const Maze* maze);
void displayMaze(const Maze* maze, int showPlayer);
Maze* initializeMaze(char* filename);
int validateMaze(const Maze* maze);

Maze* initializeMaze(char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    char line[1024];
    int height = 0, max_width = 0;
    while (fgets(line, sizeof(line), file)) {
        size_t len = strlen(line);
        if (line[len - 1] == '\n') line[len - 1] = '\0';
        if ((int)strlen(line) > max_width) max_width = strlen(line);
        height++;
    }

    rewind(file);
    Maze* maze = malloc(sizeof(Maze));
    maze->height = height;
    maze->width = max_width;
    maze->cells = malloc(height * sizeof(char*));
    
    for (int i = 0; i < height; i++) {
        maze->cells[i] = malloc((max_width + 1) * sizeof(char));
        fgets(maze->cells[i], max_width + 2, file);
        if (maze->cells[i][strlen(maze->cells[i]) - 1] == '\n')
            maze->cells[i][strlen(maze->cells[i]) - 1] = '\0';
        
        // Set player starting position
        char* start_pos = strchr(maze->cells[i], 'S');
        if (start_pos != NULL) {
            maze->playerRow = i;
            maze->playerCol = start_pos - maze->cells[i];
        }
    }
    fclose(file);
    return maze;
}

void freeMaze(Maze* maze) {
    if (maze) {
        for (int i = 0; i < maze->height; i++) {
            free(maze->cells[i]);
        }
        free(maze->cells);
        free(maze);
    }
}

int validateMove(const Maze* maze, int newRow, int newCol) {
    if (newRow < 0 || newRow >= maze->height || newCol < 0 || newCol >= maze->width ||
        maze->cells[newRow][newCol] == '#') {
        printf("Invalid move!\n");
        return 0;
    }
    return 1;
}

int hasReachedExit(const Maze* maze) {
    return maze->cells[maze->playerRow][maze->playerCol] == 'E';
}

void displayMaze(const Maze* maze, int showPlayer) {
    for (int i = 0; i < maze->height; i++) {
        for (int j = 0; j < maze->width; j++) {
            if (showPlayer && i == maze->playerRow && j == maze->playerCol)
                printf("X ");
            else
                printf("%c ", maze->cells[i][j]);
        }
        printf("\n");
    }
}

int validateMaze(const Maze* maze) {
    if (!maze) return 0;
    int startCount = 0, exitCount = 0;
    for (int i = 0; i < maze->height; i++) {
        for (int j = 0; j < maze->width; j++) {
            if (maze->cells[i][j] == 'S') startCount++;
            if (maze->cells[i][j] == 'E') exitCount++;
        }
    }
    return startCount == 1 && exitCount == 1;
}

void movePlayer(Maze* maze, int newRow, int newCol) {
    if (validateMove(maze, newRow, newCol)) {
        // Move the player if the new position is valid
        maze->playerRow = newRow;
        maze->playerCol = newCol;
    } else {
        printf("Move blocked by a wall or out of bounds.\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <maze_file>\n", argv[0]);
        return 1;
    }

    Maze* maze = initializeMaze(argv[1]);
    if (!maze) return 2;
    if (!validateMaze(maze)) {
        freeMaze(maze);
        return 3;
    }

    char input;
    int gameRunning = 1;
    while (gameRunning) {
        printf("Enter command (WASD to move, M to show map, Q to quit): ");
        scanf(" %c", &input);
        switch (input) {
            case 'w': case 'W':
                movePlayer(maze, maze->playerRow - 1, maze->playerCol);
                break;
            case 's': case 'S':
                movePlayer(maze, maze->playerRow + 1, maze->playerCol);
                break;
            case 'a': case 'A':
                movePlayer(maze, maze->playerRow, maze->playerCol - 1);
                break;
            case 'd': case 'D':
                movePlayer(maze, maze->playerRow, maze->playerCol + 1);
                break;
            case 'm': case 'M':
                displayMaze(maze, 1);
                break;
            case 'q': case 'Q':
                gameRunning = 0;
                break;
        }
        if (hasReachedExit(maze)) {
            printf("Congratulations! You've reached the exit!\n");
            gameRunning = 0;
        }
    }

    freeMaze(maze);
    return 0;
}