#ifndef WHILE_NOT_H
# define WHILE_NOT_H
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <curl/curl.h>
# include <curl/easy.h>
# include <cJSON.h>
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

typedef struct response_struct
{
    char    *string;
    size_t  size;
} response_t;

typedef struct game
{
    Texture2D   background;
    Font        font;
} game_t;

extern game_t game;

int	initialize_api();
size_t	write_chunk(void *data, size_t size, size_t nmemb, void *userdata);
char	*parse_response_json_to_text(response_t response);
char	*make_json_payload(char *input);

#endif
