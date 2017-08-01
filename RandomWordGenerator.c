#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

typedef struct CallbackData {
	char* fileName;
} CallbackData;

int getWord(void* ptr, size_t size, size_t nmemb, void* data) {
	// Assumes empty text file.
	CallbackData* callbackData = (CallbackData*) data;
	FILE* f = fopen(callbackData -> fileName, "a");
	fputs(ptr, f);
	fputs("\n", f);
}

int main(int argc, char* argv[]) {
	int i;
	int numOfWords;
	int opt;
	bool wordsGenerated = false;
	bool file = false;
	CallbackData fileInfo;
	char* url = malloc(strlen("http://www.setgetgo.com/randomword/get.php?len=") + 3);
	strcpy(url, "http://www.setgetgo.com/randomword/get.php?len=");

	while ((opt = getopt(argc, argv, "hn:f:l:")) != -1) {
		switch (opt) {
			case 'n':
				numOfWords = atoi(optarg);
				break;
			case 'l':
				if ((atoi(optarg) < 3) || (atoi(optarg) > 20)) {
					printf("Argument to -l must by between 3 and 20!\n\n");
				}
				strcat(url, optarg);
				break;
			case 'h':
				fprintf(stderr, "-i Choose number of lines to print\n-f Choose file to write to\n-l Choose length for each word in characters\n");
				exit(EXIT_SUCCESS);
				break;
			case 'f':
				fileInfo.fileName = optarg;
				file = true;
				break;
			default:
				fprintf(stderr, "Inappropriate input.");
				exit(EXIT_FAILURE);
		}
	}

	if (argc == 1) {
		fprintf(stderr, "Expected argument after options.\n");
		exit(EXIT_FAILURE);
	}

	if (file == false) {
		printf("Please enter a file name: \n");

		scanf("%ms", &fileInfo.fileName);
	}

	// A new get request to obtain every word.
	for (i = 0; i < numOfWords; i++) {
		CURL* curl;
		CURLcode res;
		curl = curl_easy_init();

		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, url);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getWord);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*) &fileInfo);
			res = curl_easy_perform(curl);
	    	curl_easy_cleanup(curl);
	  	}

		wordsGenerated = true;
	}

	if (wordsGenerated) {
		printf("%d random words generated in %s!\n", numOfWords, fileInfo.fileName);
	}

	return 0;
}
