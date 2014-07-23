#include "defs_imp.h"

/*
 *  This file generates the playlist based on the input length and song list
 */

int check_thresh(Playlist* list) {
	if (abs(list->desired_len - list->cur_len) <= list->threshold)
		return 1;
	else
		return 0;
}

double average(Playlist* list) {
	//TODO: may be able to simplify if update playlist in length
	double total = 0;
	for (int i = 0; i < list->num_songs; i++)
		total += (get_song(list, i))->len;
	return total / list->num_songs;
}

void generate_list(Playlist* in, Playlist* out) {
	double buffer = out->desired_len;
	double average_len = average(in);
	while (buffer > average_len) {
		//TODO: Change to add_ran_song so i can know to remove song from in
		// and have access to out incase of need to repopulate in
		add_song(out, select_random_song(in));
		buffer = out->desired_len - out->cur_len;
	}

	double best_dif;
	int best_idx;
	double dif;
	for (int i = 0; i < in->num_songs; i++) {
		dif = abs(get_song(in, i)->len - buffer);
		if (i == 0 || dif < best_dif) {
			best_dif = dif;
			best_idx = i;
		}
	}

	//TODO: change for same reason listed above
	add_song(out, get_song(in, best_idx));
	buffer = out->desired_len - out->cur_len;

	if (check_thresh(out))
		return;

	for (int i = 0; i < out->num_songs; i++) {
		for (int j = 0; j < in->num_songs) {
			dif = abs(buffer - (get_song(in, j)->len - get_song(out, i)->len));
			if (j == 0 || dif < best_dif) {
				best_dif = dif;
				best_idx = i;
			}
			replace_song(out, i, in, j);
			buffer = out->desired_len - out->cur_len;

			if (check_thresh(out))
				return;
		}
	}

	//If it makes it this far, it means all songs are optimized and it didn't meet threshold
	// Now will attempt with allowing repeats
	repopulate(in, out);

	for (int i = 0; i < out->num_songs; i++) {
		for (int j = 0; j < in->num_songs) {
			dif = abs(buffer - (get_song(in, j)->len - get_song(out, i)->len));
			if (j == 0 || dif < best_dif) {
				best_dif = dif;
				best_idx = i;
			}
			replace_song(out, i, in, j);
			buffer = out->desired_len - out->cur_len;

			if (check_thresh(out))
				return;
		}
	}
}