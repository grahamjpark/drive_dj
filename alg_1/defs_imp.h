#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include "read_args.h"

typedef struct Song {
	//char* name;
	//Length of song in seconds
	unsigned int len;

	//Use pointers to skip song once it's been added to list
	//NOTE: pointers can only be used in one list, therefore they can only
	//		be reference when using them in the input list
	struct Song* prev;
	struct Song* next;
} Song;

typedef struct playlist {
	// Specified and current length
	double desired_len;
	double cur_len;
	//Array of songs
	Song** songs;
	// Number of songs
	int num_songs;
	// Number of songs when full
	int full_num_songs;

	//Current first and last song of the list
	Song* head;
	Song* tail;
} Playlist;