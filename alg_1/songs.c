#include "defs_imp.h"

Song* mk_song(char* name, int len) {
	Song* temp = (Song*) malloc(sizeof(Song));
	temp.name = name;
	temp.len = len;
	return temp;
}

void rm_song(Song* song) {
	free(song.temp);
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
		min = (int) list->songs[i]->len / 60;
		sec = list->songs[i]->len % 60;
		printf("%d:%d\n", min, sec);
	}
}

Playlist* generate(int len) {
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
		song_length *= (100 + (rand()%60) - 30) / 100
		temp->songs[i]->len = song_length;
	}
	return temp;
}