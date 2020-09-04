#ifndef SCREEN_H
#define SCREEN_H

#include "project.h"

#define MESSAGE_ROWS 2
#define MESSAGE_CHARACTERS_PER_ROW 16
#define MESSAGE_ON_SCREEN_TIME_MS 500

/* Function definitions */
void Screen_Setup(); void Screen_PrintMessage(
    char Message[MESSAGE_ROWS][MESSAGE_CHARACTERS_PER_ROW + 1]);

#endif