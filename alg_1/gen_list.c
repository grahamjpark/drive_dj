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
		total += (double) (get_song(list, i))->len;
	return total / list->num_songs;
}

Song* recur_fill(Song* cur, Song* tail, double buffer) {
	if (cur == tail)
		return cur;

	double dif = abs(cur->len - buffer);
	Song* best = recur_fill(cur->next, tail, buffer);
	if (dif < abs(best->len - buffer))
		return cur;
	else
		return best;

}

Song* recur_replace(Song* cur, Song* tail, Song* replacing, double buffer) {
	double dif;
	if (cur == tail) {
		dif = abs(buffer - (cur->len - replacing->len))
		if (abs(buffer) < dif)
			return replacing;
		else
			return cur;
	}

	dif = abs(buffer - (cur->len - replacing->len))
	Song* best = recur_fill(cur->next, tail, replacing, buffer);
	if (dif < abs(buffer - (best->len - replacing->len)))
		return cur;
	else
		return best;
}
//TODO: can not update songs next and prev pointers until out of list (aka, can't linked list output till finished)
//TODO: if song is close to twice the average length try replacing it with two songs
void generate_list(Playlist* in, Playlist* out) {
	double buffer = out->desired_len;
	double average_len = average(in);
	Song* temp;
	while (buffer > average_len) {
		temp = pick_rand_song(in);
		add_song(out, temp);
		remove_song(in, temp);
		buffer = out->desired_len - out->cur_len;
	}

	Song* best = recur_fill(in->head, in->tail, buffer);

	add_song(out, best);
	remove_song(in, best);
	buffer = out->desired_len - out->cur_len;

	if (check_thresh(out))
		return;

	for (int i = 0; i < out->num_songs; i++) {
		Song* best = recur_replace(in->head, in->tail, get_song(out, i), buffer);
		//TODO: Designate which song to replace?
		replace_song(out, in, best);
		buffer = out->desired_len - out->cur_len;
		if (check_thresh(out))
			return;
		}
	}

	//If it makes it this far, it means all songs are optimized and it didn't meet threshold
	// Now will attempt with allowing repeats
	repopulate(in);

	for (int i = 0; i < out->num_songs; i++) {
		Song* best = recur_replace(in->head, in->tail, get_song(out, i), buffer);
		replace_song(out, in, best);
		buffer = out->desired_len - out->cur_len;
		if (check_thresh(out))
			return;
		}
	}
}