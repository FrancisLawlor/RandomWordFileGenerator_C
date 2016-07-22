#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct callbackdata {
	char* filename;
} callbackdata;

int getWord(void *ptr, size_t size, size_t nmemb, void *data) {
	// Assumes empty text file.
	callbackdata *test = (callbackdata *) data;
	FILE *f = fopen(test->filename, "a");
	fputs(ptr, f);
	fputs("\n", f);
}

int main(int argc, char * argv[]) {
	int i;
	int numOfWords;
	int opt;
	bool wordsgenerated=false, file = false;
	callbackdata fileinfo;

	while((opt=getopt(argc, argv, "hn:f:")) != -1) {
		switch(opt) {
			case 'n':
				numOfWords=atoi(optarg);
				break;
			case 'h':
				fprintf(stderr, "-i Choose number of lines to print\n-f Choose file to write to\n");
				exit(EXIT_SUCCESS);
				break;
			case 'f':
				fileinfo.filename=optarg;
				file=true;
				break;
			default:
				fprintf(stderr, "Inappropriate input.");
				exit(EXIT_FAILURE);
		}
	}

	if(argc==1) {
		fprintf(stderr, "Expected argument after options.\n");
		exit(EXIT_FAILURE);
	}

	if(file==false) {
		printf("Please enter a file name: \n");
		
		scanf("%ms", &fileinfo.filename);
	}

	// A new get request to obtain every word.
	for(i=0;i<numOfWords;i++) {
		CURL *curl;
		CURLcode res;
		curl = curl_easy_init();
		

		if(curl) {
			curl_easy_setopt(curl, CURLOPT_URL, "http://randomword.setgetgo.com/get.php");
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getWord);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&fileinfo);
			res = curl_easy_perform(curl);
	    		curl_easy_cleanup(curl);
	  	}
			
		wordsgenerated = true;
	}

	if(wordsgenerated) {
		printf("%d random words generated in %s!\n", numOfWords, fileinfo.filename);
	}

	return 0;
}
