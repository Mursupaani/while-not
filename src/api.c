#include "../include/while-not.h"
#include <cJSON.h>
#include <stdio.h>

int	initialize_api()
{
	const char	*api_key = "AIzaSyAX9aNaTm3mp2JnEhfEDC5q4TY1hitwpn8";
	CURL		*curl;
	CURLcode	result;
	char		url[2048];
	char		*json_payload;
	response_t	response;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	if (!curl)
	{
		fprintf(stderr, "HTTP request failed.\n");
		return (-1);
	}
	json_payload = make_json_payload("Hi! How are you?");
	struct curl_slist *headers = NULL;
	response.string = malloc(1);
	if (!response.string)
		return (0);
	response.size = 0;

	sprintf(url, "https://generativelanguage.googleapis.com/v1beta/models/gemini-2.0-flash:generateContent?key=%s", api_key);

	headers = curl_slist_append(headers, "Content-Type: application/json");

	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_chunk);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response);
	result = curl_easy_perform(curl);
	if (result != CURLE_OK)
	{
		fprintf(stderr, "Error: %s\n", curl_easy_strerror(result));
		return (-1);
	}
	printf("%s\n", parse_response_json_to_text(response));
	curl_easy_cleanup(curl);
	free(response.string);
	free(json_payload);

	return (1);
}

char	*make_json_payload(char *input)
{
	char	*json_payload = malloc(1024);
	if (!json_payload)
		return (NULL);

	sprintf(json_payload, "{" "  \"contents\": [{" "    \"parts\": [{\"text\": \"%s\"}]" "  }]" "}", input);
	return (json_payload);
}

char	*parse_response_json_to_text(response_t response)
{
	cJSON		*root;
	cJSON		*text;
	root = cJSON_Parse(response.string);
	text = cJSON_GetObjectItemCaseSensitive(
        cJSON_GetArrayItem(
            cJSON_GetObjectItemCaseSensitive(
                cJSON_GetObjectItemCaseSensitive(
                    cJSON_GetArrayItem(
                        cJSON_GetObjectItemCaseSensitive(root, "candidates"), 0
                    ),
                    "content"
                ),
                "parts"
            ),
            0
        ),
        "text"
    );
	return (text->valuestring);
}

size_t	write_chunk(void *data, size_t size, size_t nmemb, void *userdata)
{
	size_t real_size = size * nmemb;
	response_t *response = (response_t *) userdata;
	char *ptr = realloc(response->string, response->size + real_size + 1);
	if (!ptr)
	{
		printf("Not enough memory (realloc returned NULL)\n");
		return (0);
	}

	response->string = ptr;
	memcpy(&(response->string[response->size]), data, real_size);
	response->size += real_size;
	response->string[response->size] = '\0';
	return (real_size);
}
