#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

getWord(void *ptr) {
	// Assumes empty text file.
	FILE *f = fopen("words.txt", "a");
	fputs(ptr, f);
	fputs("\n", f);
}

int main(void) {
	int i;
	int numOfWords;

	printf("Enter the number of words you would like to generate!\n");
	
	scanf("%d", &numOfWords);

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
	}

	printf("Word generation complete!\n");

  return 0;
}
