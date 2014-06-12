#include "defs_imp.h"


int main(int argc, char *argv[]) {
	Table* args = ca_init(argc, argv);

	if (ca_defined("file", args))
		Playlist* in = read_in(args, ca_str_value("file", args))
	else
		Playlist* in = generate_songs(5);

	Playlist* out = create_list();
	out->cur_len = 0;
	num_songs = 0;

	if (ca_defined("time", args))
		out->desired_len = ca_int_value("time", args);
	else
		out->desired_len = 5;

	generate_list(in, out);
}