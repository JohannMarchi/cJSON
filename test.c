/*
  Copyright (c) 2009 Dave Gamble

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

/* Parse text to JSON, then render back to text, and print! */
void doit(char *text)
{
	char* out;
	char* out2;
	cJSON* json;

	json=cJSON_Parse(text);
	if (!json) {
		printf("Error before: [%s]\n",cJSON_GetErrorPtr());
	}
	else
	{

		out=cJSON_Print(json);

		//Retrieve the array of JSON elements
		//cJSON* Schedules_array = cJSON_GetObjectItem(json,"Schedules");


		//At this level, we explore the array



		int	 nb_json_elements =  cJSON_GetArraySize(json);


		cJSON* current_json_item;
		int i=0;
		for (i = 0; i < nb_json_elements; i++) {


			//Retrieve the JSON element
			current_json_item = cJSON_GetArrayItem(json, i);
			out=cJSON_Print(current_json_item);

			if (out != NULL){

				////Print the current JSON element
				//printf("%s\n",out);

				//Retrieve + Print the DataMax from Current JSON element
				//char* test = cJSON_GetObjectItem(current_json_item,"SD")->valuestring;
				//printf("%s\n",test);



				//Get the array "StayDurations"
				cJSON* current_SD = cJSON_GetObjectItem(current_json_item, "StayDurations");
				out=cJSON_Print(current_SD);
				//printf("%s\n",out);


				//Print the number of elements in the array "StayDurations"
				int	 nb_StayDurations =  cJSON_GetArraySize(current_SD);
				//printf("%i\n", nb_StayDurations);



				//Try to print all elements from the StayDurations array
				int j=0;
				for (j = 0; j < nb_StayDurations; j++) {
					current_json_item = cJSON_GetArrayItem(current_SD, j);
					out=cJSON_Print(current_json_item);
					printf("%s\n",out);
				}
				printf("-------------------\n");



				free(out);

			}
			else{
				break;
			}


		}


		/* Delete the root (takes care of everything else) */
		cJSON_Delete(json);


	}
}

/* Read a file, parse, render back, etc. */
void dofile(char *filename)
{
	FILE *f;
	long len;
	char *data;

	// Get the text
	f=fopen(filename,"rb");fseek(f,0,SEEK_END);len=ftell(f);fseek(f,0,SEEK_SET);
	data=(char*)malloc(len+1);fread(data,1,len,f);data[len]='\0';fclose(f);


	//Call the interesting function
	//printf("%s\n", data);
	doit(data);
	free(data);

}

/* Used by some code below as an example datatype. */
struct record {const char *precision;double lat,lon;const char *address,*city,*state,*zip,*country; };



int main (int argc, const char * argv[]) {

	/* Parse standard testfiles: */
	dofile("tests/test2");


	return 0;
}
