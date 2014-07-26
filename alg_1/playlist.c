#include "defs_imp.h"

/* 
 * This file does most of the background work on the playlist, including creating,
 * modifying, and deleting.
 */

Song* mk_song(char* name, int len) {
	Song* temp = (Song*) malloc(sizeof(Song));
	temp->len = len;
	temp->prev = NULL;
	temp->next = NULL;
	return temp;
}

void free_song(Song* song) {
	//free(song->name);
	free(song);
}

int song_compare(const void* a, const void* b) {
	Song* ptr_a = *(Song**)a;
	Song* ptr_b = *(Song**)b;
	if (ptr_a->len > ptr_b->len)
		return 1;
	else if (ptr_a->len < ptr_b->len)
		return -1;
	else 
		return 0;
}


void sort(Song** songs, int len) {
	qsort(songs, len, sizeof(Song*), song_compare);
}

void link_list(Playlist* in) {
	int num_songs = in->num_songs;
	in->head = in->songs[0];
	in->tail = in->songs[num_songs -1];
	for(int i = 0; i < num_songs; i++) {
		if(i != 0)
			in->songs[i]->prev = in->songs[i-1];

		if(i != num_songs - 1) 
			in->songs[i]->next = in->songs[i+1];
	}
}

void print_songs(Playlist* list) {
	int min;
	int sec;
	printf("Printing %i song(s):\n", list->num_songs);
	for (int i = 0; i < list->num_songs; i++) {
		min = (int) (list->songs[i]->len) / 60;
		sec = (int) (list->songs[i]->len) % 60;
		printf("%d:%d\n", min, sec);
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

int check_format(char* text, int len) {
	//Index of the colon
	int idx = -1;

	if (len < 4) return -1;

	//Parses through line, recording index of the colon.
	//Non-numeric characters, 3 digits after colon, two colons are recorded, returns -1
	for (int i = 0; i <= len; i++) {
		if (text[i] == '\0') return idx;
		else if (text[i] == ':' && idx == -1) {
			idx = i;
			if (len - idx != 3) return -1;
		}
		else if (text[i] < '0' || text[i] > '9') {
			return -1;
		}
	}
	return -1;
}

int add_new_song(char* line, int len, Playlist* list) {
	int idx = check_format(line, len);
	if (idx != -1) {
		int min = (int) strtol(line, NULL, 10);
		int sec = (int) strtol(&(line[idx+1]), NULL, 10);
		unsigned int song_len = (min*60) + sec;
		if (song_len > 2147483647 || song_len < 0) {
			printf("Error processing song length.\n");
			return 1;
		}
		list->num_songs += 1;

		Song** temp = (Song**) realloc(list->songs, list->num_songs * sizeof(Song*));
		if (temp != NULL) {
			list->songs = temp;
		}
		else {
			printf("Error reallocating memory to add new song.\n");
			list->num_songs -= 1;
			return 1;
		}

		Song* new_song = (Song*) malloc(sizeof(Song));
		new_song->len = song_len;
		list->songs[list->num_songs - 1] = new_song;
	}
	else {
		return -1;
	}
}

Playlist* create_list() {
	Playlist* temp = (Playlist*) malloc(sizeof(Playlist));
	temp->num_songs = 0;
	temp->songs = (Song**) malloc(sizeof(Song*));
	temp->head = NULL;
	temp->tail = NULL;
	return temp;
}

/*
 * Reads in a file of song lengths, with each time on a new line and of the
 * format "MINUTES:SECONDS"
 */
Playlist* read_in(char* file) {
	FILE* fp;

	fp = fopen(file, "r");

	Playlist* in = create_list();

	char* line = (char*) malloc(sizeof(char)*10);
	int len;
	int cycling = 1;
	int err;
	int err_count = 0;

	while (cycling == 1) {
		err = 1;
		len = 0;
		int c;

		/*For every char that's not a \n add the char to line_temp
		 * if the char is an EOF and it just reading this line, don't continue
		 * if the char is just EOF but there was something before it, finish cycle
		 */
		while ((c = fgetc(fp)) != '\n' && cycling == 1) {
			if (c == EOF && len == 0) {
				cycling = -1;
				break;
			}
			else if (c == EOF)
				cycling = 0;
			else {
				line[len++] = c;
			}
		}
		line[len] = '\0';
		err = add_new_song(line, len, in);
		if (err == -1)
			err_count++;
	}
	printf("%i song(s) recorded with %i line(s) ommited\n", in->num_songs, err_count);
	return in;
}

int main(int argc, char *argv[]) {
	Table* args = ca_init(argc, argv);

	//if (ca_defined("file", args)) {
		Playlist* in = read_in("songs.txt");//ca_str_value("file", args));
		sort(in->songs, in->num_songs);
		print_songs(in);
/*		fprintf(stderr, "4\n");
		link_list(in);
		fprintf(stderr, "5\n");*/
	//}
/*	else {
		//Playlist* in = generate_songs(5);
		printf("Please designate an input song file using \"file=*your file* \"\n");
	}*/
}