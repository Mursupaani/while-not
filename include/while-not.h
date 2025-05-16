#ifndef WHILE_NOT_H
# define WHILE_NOT_H
# include <stdio.h>
# include <unistd.h>
# include "raylib.h"
# include "raymath.h"

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

typedef enum gamestate
{
    START,
    GAME,
    END
}   state_t;

typedef struct game
{
    Texture2D   background;
    Font        font;
} game_t;

extern game_t game;

#endif
