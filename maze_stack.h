//
// Created by thgir on 11/02/2021.
//

#ifndef MAZE_GENERATOR_MAZE_STACK_H
#define MAZE_GENERATOR_MAZE_STACK_H

#include "struct.h"

boxInStack_t* stack_push(box_t* currentBox, boxInStack_t* previousStackElement, const int* position);
boxInStack_t* stack_pop(boxInStack_t* currentBox);

#endif //MAZE_GENERATOR_MAZE_STACK_H
