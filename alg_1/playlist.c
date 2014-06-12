#include "defs_imp.h"

Song* mk_song(char* name, int len) {
	Song* temp = (Song*) malloc(sizeof(Song));
	temp->name = name;
	temp->len = len;
	return temp;
}

void rm_song(Song* song) {
	free(song->name);
	free(song);
}

int song_compare(const void* a, const void* b) {
	if ((*(double*) a - *(double*) b) > 0)
		return 1;
	else 
		return 0;
}

void sort(Song* songs, int len) {
	qsort(songs, len, sizeof(Song), song_compare);
}

void print_songs(Playlist* list) {
	int min;
	int sec;
	for (int i = 0; i < list->num_songs; i++) {
		min = (int) (list->songs[i]->len) / 60;
		sec = (list->songs[i]->len) % 60;
		printf("%d:%d\n", min, sec);
	}
}

/*
 *  Tries to generate songs that follows realistic songs lengths
 */
 //TODO: Test functions and refine, decided to use real songs first
/*Playlist* generate_songs(int len) {
	Playlist* temp = (Playlist*) malloc(sizeof(Playlist));
	temp->songs = (Song*) malloc(sizeof(Song)*len);
	temp->num_songs = len;
	srand(time(NULL));
	int song_length = 0;
	for (int i = 0; i < len; i++) {
		if (rand() > .9) {
			// Extreme upper bound is seeded at 7 minutes
			song_length = (6.5*60);
		}
		else if (rand() < .1) {
			// Extreme lower bound is seeded at 1.75 minutes
			song_length = (1.5 * 60);
		}
		else {
			// Average song length is seeded at 3.5 minutes
			song_length = (3.5*60);
		}

		// Scales the seeded 
		song_length *= (100 + (rand()%60) - 30) / 100;
		temp->songs[i]->len = song_length;
	}
	return temp;
}
*/
int check_format(char* text, int len) {
	//Index of the colon
	int idx = -1;
	if (len < 3) return -1;
	for (int i = 0; i < len; i++) {
		if (text[i] == '\0') return idx;
		if (text[i] == ':' && idx == -1) {
			idx = i;
		}
		if (text[i] < '0' || text[i] > '9') {
			return -1;
		}
	}
}

void add_new_song(char* line, int len, Playlist* list) {
	int idx = check_format(line, len);
	if (idx != -1) {
		int min = (int) strtol(line, NULL, 10);
		int sec = (int) strtol(line[idx+1], NULL, 10);
		int song_len = (min*60) + sec;
		list->num_songs++;
		//TODO: Relloc
	}
}

void add_song(Playlist* list, Song* song) {
	//TODO: Update with new song structure (update cur length)
}

Song* select_random_song(Playlist* list) {
	//TODO: Update with new song structure
}

Song* get_song(Playlist* list, int idx) {
	//TODO: Update with new song structure
}

void remove_song(Playlist* list, Song* song) {
	//TODO: Update with new song structure
}

Playlist* create_list() {
	//TODO: Update with new song structure (and figure out what to set values)
	Playlist* out = (Playlist*) malloc(sizeof(Playlist));
	out->songs = (Song*) malloc(sizeof(Song));	
}

/*
 * Reads in a file of song lengths, with each time on a new line and of the
 * format "MINUTES:SECONDS"
 */
Playlist* read_in(Table* args, char* file) {
	FILE* fp;

	if (ca_defined("file", args))
		fp = fopen(file, "r");
	else
		return NULL;

	//TODO: Switch to create_list()
	Playlist* temp = (Playlist*) malloc(sizeof(Playlist));
	temp->num_songs = 0;
	temp->songs = (Song*) malloc(sizeof(Song)*(num_songs + 1);

	char* line = (char*) malloc(sizeof(char)*10);
	int len;
	int cycling = 1;
	while (cycling) {
		//Resets length to zero
		len = 0;
		int c;

		/*For every char that's not a \n add the char to line_temp
		 * if the char is an EOF and it just started filling, don't continue
		 * if the char is just EOF, finish cycle
		 */
		while ((c = fgetc(fp)) != '\n' && cycling) {
			if (c == EOF && len == 0) {
				cycling = 0;
				break;
			}
			if (c == EOF)
				cycling = 0;
			else {
				line[len++] = c;
			}
		}
		line[len] = '\0';
		add_song(line, len, temp);
	}
}