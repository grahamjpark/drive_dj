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