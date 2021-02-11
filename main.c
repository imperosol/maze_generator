#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "struct.h"
#include "maze_stack.h"


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"

void display_maze(const maze_t maze);
void initialize_maze(maze_t* maze);
int get_potential_directions(freeBox_t* freeBox, const maze_t maze, const int line, const int column);
void update_position(int* currentPosition, const boxWall_e direction);
boxWall_e get_direction(const int nbrOfPotential, const bool* arrayOfPotential);


int main() {
    srand(time(NULL));

    freeBox_t potentialDirections;
    int emptyBoxes = LINE * COLUMN - 1;
    int randomDirection;
    boxWall_e direction;
    maze_t maze;
    int currentPosition[2] = {0, 0};

    initialize_maze(&maze);

    boxInStack_t* maze_stack = NULL;
    maze_stack = stack_push(&(maze.box[0][0]), NULL, currentPosition);
    maze_stack->box->hasBeenVisited = true;

    while (emptyBoxes){
        if (get_potential_directions(&potentialDirections,
                                     maze,
                                     currentPosition[0],
                                     currentPosition[1])) {
            direction = get_direction(potentialDirections.nbrOfEmptyBoxes, potentialDirections.isBoxEmpty);
            maze_stack->box->isWallSolid[direction] = false;
            update_position(currentPosition, direction);
            maze_stack = stack_push(&(maze.box[currentPosition[0]][currentPosition[1]]), maze_stack, currentPosition);
            maze_stack->box->hasBeenVisited = true;
            maze_stack->box->isWallSolid[(direction + 2) % 4] = false;
            emptyBoxes--;
        } else {
            while (!get_potential_directions(&potentialDirections,
                                             maze,
                                             currentPosition[0],
                                             currentPosition[1])) {
                maze_stack = stack_pop(maze_stack);
                for (int i = 0; i < 2; ++i) {
                    currentPosition[i] = maze_stack->position[i];
                }
            }
        }
    }
    display_maze(maze);
    printf("%d\n", emptyBoxes);
    while (getchar() != '\n');
    return 0;
}

void update_position(int* currentPosition, const boxWall_e direction)
{
    if (direction % 2) {
        /* The direction is either LEFT or RIGHT */
        currentPosition[1] -= direction - 2;
    } else {
        /* The direction is either TOP or BOTTOM */
        currentPosition[0] += direction - 1;
    }
}
boxWall_e get_direction(const int nbrOfPotential, const bool* arrayOfPotential)
{
    int randomDirection = rand() % nbrOfPotential;
    boxWall_e direction;
    for (int i = 0; i < 4; ++i) {
        if (arrayOfPotential[i]) {
            if (!randomDirection) {
                return i;
            } else {
                randomDirection--;
            }
        }
    }
    return 0;
}
int get_potential_directions(freeBox_t* freeBox, const maze_t maze, const int line, const int column)
{
    int arrayInd = 0;
    freeBox->nbrOfEmptyBoxes = 0;
    for (int i = -1; i < 2; i += 2) {
        if (line + i < 0 || line + i >= LINE) {
            /* The box is out of the maze */
            freeBox->isBoxEmpty[arrayInd] = false;
        } else if (maze.box[line+i][column].hasBeenVisited) {
            freeBox->isBoxEmpty[arrayInd] = false;
        } else {
            freeBox->isBoxEmpty[arrayInd] = true;
            freeBox->nbrOfEmptyBoxes++;
        }
        arrayInd++;

        if (column - i < 0 || column - i >= COLUMN) {
            /* The box is out of the maze */
            freeBox->isBoxEmpty[arrayInd] = false;
        } else if (maze.box[line][column-i].hasBeenVisited) {
            freeBox->isBoxEmpty[arrayInd] = false;
        } else {
            freeBox->isBoxEmpty[arrayInd] = true;
            freeBox->nbrOfEmptyBoxes++;
        }
        arrayInd++;
    }
    for (int i = 0; i < 4; ++i) {
        if (freeBox->isBoxEmpty[i]) {
            return 1;
        }
    }
    return 0;
}
void initialize_maze(maze_t* maze)
{
    /*Begin by declaring all the maze boxes as empty from all sides*/
    for (int i = 0; i < LINE; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            for (int k = 0; k < 4; ++k) {
                maze->box[i][j].isWallSolid[k] = true;
                maze->box[i][j].hasBeenVisited = false;
            }
        }
    }
    maze->box[0][0].isWallSolid[TOP] = false;
    /* make the top of the maze solid
    for (int i = 1; i < COLUMN; ++i) {
        maze->box[0][i].isWallSolid[TOP] = true;
    }

    Left and right side
    for (int i = 0; i < LINE; ++i) {
        maze->box[i][0].isWallSolid[LEFT] = true;
        maze->box[i][COLUMN-1].isWallSolid[RIGHT] = true;
    }

    Bottom side
    for (int i = 0; i < COLUMN; ++i) {
        maze->box[LINE-1][i].isWallSolid[BOTTOM] = true;
    } */

    puts("Maze initialized");
}
void display_maze(const maze_t maze)
{
    printf("\n");
    for (int i = 0; i < LINE; ++i) {
        for (int j = 0; j < COLUMN; ++j) {
            if (maze.box[i][j].isWallSolid[TOP]) {
                printf("+----+");
            } else {
                printf("+    +");
            }
        }
        printf("\n");
        for (int j = 0; j < COLUMN; ++j) {
            if (maze.box[i][j].isWallSolid[LEFT]) {
                printf("|    ");
            } else {
                printf("     ");
            }
            if (maze.box[i][j].isWallSolid[RIGHT]) {
                printf("|");
            } else {
                printf(" ");
            }
        }
        printf("\n");
        for (int j = 0; j < COLUMN; ++j) {
            if (maze.box[i][j].isWallSolid[BOTTOM]) {
                printf("+----+");
            } else {
                printf("+    +");
            }
        }
        printf("\n");
    }
}

#pragma clang diagnostic pop