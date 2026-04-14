#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "word_count.h"
#include "hashmap.h"

/*
 * Sequential Baseline Version for Lab 5
 * -------------------------------------
 * This program implements a basic (single-threaded) word count.
 * It is provided as a *starting point* for your concurrent MapReduce design.
 *
 * Your task:
 *   - Transform this sequential code into a concurrent MapReduce-style program.
 *   - Use m mapper threads and r reducer threads.
 *   - Use the bounded buffer implementation from Lab 4 for communication
 *     between mappers and reducers.
 *   - Replace strtok() with the thread-safe strtok_r().
 *   - Each reducer should receive all words whose hash % r equals its index.
 *   - Ensure proper termination and that there are no memory leaks.
 *
 * Note: Do NOT simply wrap this code in threads — rethink the data flow
 *       (mappers → bounded buffers → reducers). You may keep parts of
 *       the parsing logic, but thread management and synchronization
 *       are entirely up to you.
 */


int print_result(char*, int);

void word_count(int m, int r, char **text){
    /* Here I am providing a sequential version.
       You need to change it into a map reduce version*/
    const char delimiter[2] = " ";
    char *token;
    map_t mymap;
    int error;
    
/* This lab includes a working hashmap implementation (hashmap.c / hashmap.h)
 * for you to use in counting word frequencies.
 * You do NOT need to download or modify any external libraries.
 *
 * Optional resource:
 *   For those interested in exploring alternative hashmap designs,
 *   you may review this MIT-licensed educational example:
 *   https://github.com/tidwall/hashmap.c
 * This external resource is not required for completing the lab.
 */

    mymap = hashmap_new();
    for(int i=0; i<m; i++){
        /*strtok can extract one word from a string.
	  Note it is not thread-safe. Try to find out
	  why and the thread-safe version.*/
	token = strtok(text[i], delimiter);
	while( token != NULL ) {
	    int count;
	    /* If there exists a count for this word,
	       add the count by 1. Otherwise, set count
	       to 1*/
	    error = hashmap_get(mymap, token, &count);
	    if(error==MAP_OK)
		hashmap_put(mymap, token, count+1);
	    else
		hashmap_put(mymap, token, 1);
      	    token = strtok(NULL, delimiter);
   	}
    }
    printf("Result:\n");
    hashmap_iterate(mymap, print_result);	
	
}

int print_result(char *key, int value){
    printf("count of %s = %d\n", key, value);
    return 0;
}


