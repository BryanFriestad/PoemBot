/*___________________________
PoemBot
Created by Bryan Friestad
v1.2.0
2/19/2018 22:48
___________________________*/

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define DEBUG 0

//function prototypes here
void generateLine(char line[], char* nouns[], int numNouns, char* adjs[], int numAdjs, char* verbs[], int numVerbs); //generates a line using weighted preferences for certain line formats
void printPoem(char poem[][100], int numOfLines); //prints the formatted poem to stdout
int isVowel(char c); //returns 1 if character is a vowel, 0 if anything else
void printPoemToFile(char poem[][100], int numOfLines, FILE* outFile); //same as print poem, the only difference is this is meant to print to a file defined in the code

//GLOBAL VARIABLES
/*LINE TYPES*/
	char style_1[] = "%s is like %s %s %s\n"; //noun, a/an, adjective, noun
	char style_2[] = "%s\n"; //just a noun
	char style_3[] = "the %s %ss\n"; //noun, verb
	char style_4[] = "and the %s, it is %sing\n"; //noun, verb
	char style_5[] = "%s: %s %s feels like %s %s, %s\n"; //adjective, a/an, noun, a/an, noun, adjective
	char style_6[] = "%s? no, we all %s...\n"; //noun, verb 
	char style_7[] = "\n"; 
	char style_8[] = "why %s when you can %s?\n"; //verb, verb 
	char style_9[] = "just like %s %s, the %s %ss\n"; //a/an, noun, noun, verb
	char style_10[] = "everything %ss\n"; //verb 


int main(void){
	
	clock_t start, end;
	double cpu_time_used;
	start = clock();
	
	//seed the random function
	srand(time(NULL));
	
	//get about 50 more words for each
	const int numNouns = 61; //must match the number of strings in the following array
	char* nouns[] = {"dog", "cat", "bird", "frog", "love", "bus", "sun", "moon", "earth", "heart", "eye", "death",
					 "satellite", "salmon", "safety", "sage", "anxiety", "anteater", "beast", "battle", "war",
					 "beach", "breath", "brain", "lung", "breeze", "actress", "act", "affair", "addiction", "apparatus",
					 "captain", "picture", "photograph", "town", "tramp", "trade", "key", "lock", "toilet", "tear",
					 "valley", "wheelchair", "walker", "crutch", "plane", "tombstone", "wall", "vessel", "thunderstorm",
					 "kiss", "chain", "tumor", "serpent", "sleep", "bed", "ocean", "eagle", "rain", "tissue", "light"};
	
	const int numVerbs = 32; //must match the number of strings in the following array
	char* verbs[] = {"expound", "expand", "assume", "justify", "ironize", "multiply", "denounce", "account",
						   "illuminate", "review", "perceive", "link", "address", "diagnose", "agree", "censure",
						   "expose", "problematize", "detect", "manipulate", "contend", "position", "guide",
						   "configure", "depict", "descend", "inform", "instruct", "isolate", "succeed", "maintain",
						   "persuade"};

	const int numAdjs = 24; //must match the number of strings in the following array
	char* adjectives[] = {"blue", "red", "dead", "lonely", "sad", "happy", "pretty", "fast", "adamant", "adriot",
						  "amatory", "contumacious", "incendiary", "hubristic", "limpid", "pendulous", "risible",
						  "tenacious", "zealous", "voracious", "withering", "loud", "nefarious", "mendacious"};
	
	//print out "enter the number of poems you want to created
	printf("How many poems do you want to make?\n");
	//scan in %d
	int numPoems;
	scanf(" %d",&numPoems);
	
	FILE* outputFile = NULL;
	
	//ALL OF THIS INSIDE OF A FOR LOOP
	int i;
	for(i = 1; i <= numPoems; i++){
		//number of lines in the poem. minimum of 5 lines plus 2 for the title and empty line
		int numOfLines = (rand() % 20) + 5 + 2;
		if(DEBUG) printf("Number of lines: %d\n", numOfLines); //prints out the integer numOfLines so the developer can check that the poem printed correct number of lines
		
		if(DEBUG) printf("word lists created\n"); //informs the developer that that no errors occured when trying to create the word arrays
		
		//poem with numOfLines lines
		char poem[numOfLines][100];
		
		int j;
		//for each line, starting at line j = 2 (to leave room for title and a blank line)
		//generate line by line
		for(j = 2; j < numOfLines; ++j){
			generateLine(poem[j], nouns, numNouns, adjectives, numAdjs, verbs, numVerbs);
		}
		
		if(DEBUG) printf("poem generated successfully.\n"); //informs the developer that that no errors occured when trying to generate and copy lines into the main poem variable
		
		//FIXME: Come up with a creative way to make the name of the poem - possibly find the most common word
		strcpy(poem[0], "The Robot by Robot\n");
		strcpy(poem[1], "\n");
		
		char fileName[25];
		char numString[10];
		if(DEBUG) printf("%d", i);
		sprintf(numString, "%d", i);
		strcpy(fileName, "poems/poem");
		strcat(fileName, numString);
		strcat(fileName, ".txt");
		outputFile = fopen(fileName, "w");
		
		printPoemToFile(poem, numOfLines, outputFile);
		fclose(outputFile);
	}
	
	end = clock();
	printf("Total program time for %d poems: %lf seconds.\n", numPoems, ((double) (end - start)) / CLOCKS_PER_SEC);
	
	return 0;
}

//define functions here
void generateLine(char line[], char* nouns[], int numNouns, char* adjs[], int numAdjs, char* verbs[], int numVerbs){
	
	int lineType = rand() % 50;
	int nounIndex, verbIndex, adjIndex;
	
	//odds of getting this are 14 in 50
	if(lineType >= 0 && lineType < 14){
		
		nounIndex = rand() % numNouns;
		adjIndex = rand() % numAdjs;
		
		if(DEBUG) printf("noun index: %d\n", nounIndex); //informs the developer if the nounIndex is out of bounds for the noun array
		
		strcpy(line, nouns[nounIndex]);
		strcat(line, " is like a ");
		strcat(line, adjs[adjIndex]);
		nounIndex = rand() % numNouns;
		if(DEBUG) printf("noun index: %d\n", nounIndex); //informs the developer if the nounIndex is out of bounds for the noun array
		strcat(line, " ");
		strcat(line, nouns[nounIndex]);
		strcat(line, "\n");
	}
	//odds of getting this are 2 in 50
	else if(lineType >= 14 && lineType < 16){
		
		nounIndex = rand() % numNouns;
		if(DEBUG) printf("noun index: %d\n", nounIndex); //informs the developer if the nounIndex is out of bounds for the noun array
		strcpy(line, nouns[nounIndex]);
		strcat(line, "\n");
	}
	//odds of getting this are 8 in 50
	else if(lineType >= 16 && lineType < 24){
		nounIndex = rand() % numNouns;
		strcpy(line, "the ");
		strcat(line, nouns[nounIndex]);
		strcat(line, " ");
		verbIndex = rand() % numVerbs;
		strcat(line, verbs[verbIndex]);
		strcat(line, "s\n");
	}
	//odds of getting this are 10 in 50
	else if(lineType >= 24 && lineType < 34){
		strcpy(line, "and the ");
		nounIndex = rand() % numNouns;
		strcat(line, nouns[nounIndex]);
		strcat(line, ", it is ");
		verbIndex = rand() % numVerbs;
		strcat(line, verbs[verbIndex]);
		strcat(line, "ing\n");
	}
	//odds of getting this are 6 in 50
	else if(lineType >= 34 && lineType < 40){
		adjIndex = rand() % numAdjs;
		strcpy(line, adjs[adjIndex]);
		strcat(line, ": ");
		nounIndex = rand() % numNouns;
		char temp = nouns[nounIndex][0];
		if(isVowel(temp) == 1){
			strcat(line, "an ");
		}
		else{
			strcat(line, "a ");
		}
		strcat(line, nouns[nounIndex]);
		strcat(line, " feels like ");
		nounIndex = rand() % numNouns;
		temp = nouns[nounIndex][0];
		if(isVowel(temp) == 1){
			strcat(line, "an ");
		}
		else{
			strcat(line, "a ");
		}
		strcat(line, nouns[nounIndex]);
		strcat(line, ", ");
		strcat(line, adjs[adjIndex]);
		strcat(line, "\n");
	}
	//odds of getting this are 2 in 50
	else if(lineType >= 40 && lineType < 42){
		nounIndex = rand() % numNouns;
		strcpy(line, nouns[nounIndex]);
		strcat(line, "? no, we all ");
		verbIndex = rand() % numVerbs;
		strcat(line, verbs[verbIndex]);
		strcat(line, "...\n");
	}
	//odds of getting this are 8 in 50
	else if(lineType >= 42){
		strcpy(line, "\n");
	}
}

void printPoem(char poem[][100], int numOfLines){
	
	int i;
	for(i = 0; i < numOfLines; ++i){
		printf("%s", poem[i]);
	}
	fflush(stdout);
}

void printPoemToFile(char poem[][100], int numOfLines, FILE* outFile){
	
	int i;
	for(i = 0; i < numOfLines; ++i){
		fprintf(outFile, "%s", poem[i]);
	}
}

int isVowel(char c){
	if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
		return 1;
	}
	else if(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'){
		return 1;
	}
	else{
		return 0;
	}
}