#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <time.h>
#include "read_args.h"

typedef struct song {
	char* name;
	//Length of song in seconds
	double len;
	//TODO: Implement rating weight. Will try to optimize to find most likeable playlist
	//int rating;
} Song;

typedef struct playlist {
	// Specified and current length
	double desired_len;
	double cur_len;
	//Array of songs
	Song* list;
	// Number of songs
	int num_songs;
} Playlist;