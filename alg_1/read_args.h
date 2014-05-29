typedef struct table {
	// The current size of the list (also the next postion for element to be added)
	int pos;
	//Arrays of keys and values
	char** keys;
	char** values;
} Table;
/*
 * Read and parse command line arguments. argv is an array of argc strings.
 * The format is "-key" or "-key=val" where "key" and "val" are sequences of
 * alpha-numeric characters. All other string are silently discarded.  For
 * any key, only its last definition is retained.  "-key" has a NULL value.
 */
Table* ca_init(int argc, char **argv);

/*
 * Check is the null-terminated string key is defined. Answer true if either
 * "-key" or "-key=val" were passed at the command line.
 */
int ca_defined(char *key, Table* tbl);

/*
 * If "key" is associated to "val", returns atoi(val). If "val" is NULL,
 * returns -1.  Undefined behavior, if "key" is not found.
 */
int ca_int_value(char *key, Table* tbl);

/*
 * If "key" is associated to "val", returns val. Undefined behavior, if
 * "key" is not found.
 */
char *ca_str_value(char *key, Table* tbl);
