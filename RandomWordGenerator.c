#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <stdbool.h>
#include <unistd.h>

int getWord(void *ptr) {
	// Assumes empty text file.
	FILE *f = fopen("words.txt", "a");
	fputs(ptr, f);
	fputs("\n", f);
}

int main(int argc, char * argv[]) {
	int i;
	int numOfWords;
	int opt;
	bool wordsgenerated = false;

	//printf("Enter the number of words you would like to generate!\n");
	
	//scanf("%d", &numOfWords);

	while((opt=getopt(argc, argv, "hn:f:")) != -1) {
		switch(opt) {
			case 'n':
				numOfWords=atoi(optarg);
				break;
			case 'h':
				fprintf(stderr, "-i Choose number of lines to print\n");
				exit(EXIT_SUCCESS);
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

	// A new get request to obtain every word.
	for(i=0;i<numOfWords;i++){
		CURL *curl;
		CURLcode res;
		curl = curl_easy_init();

		if(curl) {
			curl_easy_setopt(curl, CURLOPT_URL, "http://randomword.setgetgo.com/get.php");
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, getWord);
			res = curl_easy_perform(curl);
	    		curl_easy_cleanup(curl);
	  	}
		
		wordsgenerated = true;
	}

	if(wordsgenerated){
		printf("%d random words generated!\n", numOfWords);
	}

  return 0;
}
