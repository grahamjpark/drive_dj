#include "defs_imp.h"


int main(int argc, char *argv[]) {
	Table* args = ca_init(argc, argv);

	if (ca_defined("file", args)) {
		Playlist* in = read_in(ca_str_value("file", args))
		sort(in->songs, in->num_songs);
		link_list(in);
	}
	else {
		//Playlist* in = generate_songs(5);
		printf("Please designate an input song file using \"file=*your file* \"\n");
	}

	Playlist* out = create_list();
	out->cur_len = 0;

	if (ca_defined("time", args))
		out->desired_len = ca_int_value("time", args);
	else {
		printf("Please designate a target drive time using \"time=*your time* \"\n");
		return
	}
	generate_list(in, out);
}