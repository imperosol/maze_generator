//
// Created by thgir on 11/02/2021.
//

#include <stdlib.h>
#include <stdio.h>
#include "maze_stack.h"

boxInStack_t* stack_push(box_t* currentBox, boxInStack_t* previousStackElement, const int* position)
{
    boxInStack_t* newBox = NULL;
    newBox = (boxInStack_t*) malloc(sizeof(boxInStack_t));
    if (newBox == NULL) {
        fprintf(stderr, "Impossible allocation for a box");
        return NULL;
    }
    newBox->box = currentBox;
    newBox->previous = previousStackElement;
    for (int i = 0; i < 2; ++i) {
        newBox->position[i] = position[i];
    }
    return newBox;
}

boxInStack_t* stack_pop(boxInStack_t* currentBox)
{
    boxInStack_t * previous = currentBox->previous;
    //free(currentBox);
    return previous;
}
