#include "../include/while-not.h"

game_t	game;

void	initialize_game()
{
	Image	background = LoadImage("Assets/Background/mountains.jpg");
	ImageResize(&background, SCREEN_WIDTH, SCREEN_HEIGHT);
	game.background = LoadTextureFromImage(background);
}

int	main()
{    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.example.com/data");

        // For a POST request:
        // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "key1=value1&key2=value2");

        // Set headers if needed:
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Authorization: Bearer YOUR_TOKEN_HERE");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Perform the request
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        // Cleanup
        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }
    curl_global_cleanup();
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "while(not) presents");
	SetTargetFPS(60);
	// 1. Texture loader?
	// 2. Initialize game?
	initialize_game();
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawTexture(game.background, 0, 0, WHITE);
		EndDrawing();
	}
	return (0);
}
