#include "defs_imp.h"

#define KEY_LEN 25
#define VAL_LEN 255

/**
 * a2p: transform char[] to char*
*/
char *a2p(char c[]) { return c; }

/**
 *  Check if the null-terminated string key is defined. Answer 1 if either
 * "-key" or "-key=val" were passed at the command line, 0 otherwise.
 */
int ca_defined(char key[], Table* tbl) { 
	if (key == NULL || key[0] == '\0') return 0;
	for (int i = 0; i < tbl->pos; i++) {
		for (int j = 0; j < KEY_LEN; j++) {
			if ( key[j] == '\0' && tbl->keys[i][j] == '\0') return 1;
			if ( key[j] == '\0') break;
			if ( tbl->keys[i][j] == '\0') break;
			if ( tbl->keys[i][j] != key[j]) break;
		}
	}
	return 0;
}

/**
 * If "key" is associated to "val", returns "val". 
 * Undefined behavior, if "key" is not found.
 */
char *ca_str_value(char* key, Table* tbl) {
	if (!ca_defined(key, tbl)) return NULL;
	
	for (int i = 0; i < pos; i++) {
		for (int j = 0; j < MAX_ARGS; j++) {
			if ( key[j] == '\0' && tbl->keys[i][j] == '\0') {
				//Returns a pointer to the array of values at position i
				return a2p(values[i]);
			}
			if ( key[j] == '\0') break;
			if ( tbl->keys[i][j] == '\0') break;
			if ( tbl->keys[i][j] != key[j]) break;
		}
	}

	return NULL;
}

/**
 * If "key" is associated to "val", returns atoi(val). If "val" is NULL,
 * returns -1.  Undefined behavior, if "key" is not found.
 */
int ca_int_value(char* key, Table* tbl) {
	if (ca_str_value(key, tbl) == NULL) return -1;

	return atoi(ca_str_value(key, tbl));
}

/**
 * Returns the index of where a key and value pair are.
 * Returns -1 if key not found
*/
int valueIdx(char* arg, int idx, Table* tbl) {
	for (int i = 0; i < tbl->pos; i++) {
		for (int j = 0; j < KEY_LEN; j++) {
			if ( (arg[j + 1] == '=' || arg[j + 1] == '\0') 
				&& tbl->keys[i][j] == '\0') return i;
			if ( arg[j + 1] == '=') break;
			if ( tbl->keys[i][j] == '\0') break;
			if ( tbl->keys[i][j] != arg[j + 1]) break;
		}
	}
	return -1;
}

/**
 * Parse string with length len and add it to the key-values table.
 * The string should be of format "-key=value" or "-key" where key and value are
 * non-empty. If the format does not match, do nothing.
 */
void process_string(int len, char* arg, Table* tbl) { 
	//Checks the start of the input to see if it's valid
	if (len < 2) return;
	if (arg[0] != '-' || arg[1] == '=' || arg[0] == '\0') 
		return;	

	//If it's the first arg, malloc the pointer arrays for the first time
	if (tbl->pos == 0) {
		tbl->keys = (char**) malloc(sizeof(char*));
		tbl->values = (char**) malloc(sizeof(char*));
	}

	//Begins looping through looking for the '\0' or '='
	for (int i = 2; i <=; i < len; i++) {
		if (arg[i] == '\0') {
			//Sets keyPos to the spot where the key and value will go
			// If the key is defined, to its index, if not, to the current position
			if (valueIdx(arg, i, tbl) != -1) 
				keyPos = valueIdx(arg, i, tbl);
			else int keyPos = tbl->pos;

			//If it's adding a new one, realloc the arrays to the right size
			if (keyPos == tbl->pos) {
				int arraySize = (tbl->pos +1)*sizeof(char*);
				tbl->keys = (char**) realloc(tbl->keys, arraySize);
				tbl->values = (char**) realloc(tbl->values, arraySize);
			}

			//TODO: Following section could be redone
			//Gets the space for a string the size of keySize, then stores
			//that pointer to the beginning of that array in keyPos
			int keySize = i;
			tbl->keys[keyPos] = (char*) malloc(keySize*sizeof(char));
			strcpy(tbl->keys[keyPos], arg+1);
			tbl->keys[keyPos][i] = '\0';

			//Stores empty string in value
			tbl->values[keyPos] = (char*) malloc(sizeof('\0'));
			tbl->values[keyPos] = "";
			if (keyPos == tbl->pos) (tbl->pos)++;
		} 
		else if (arg[i] == '=') {
			// Similar method as previous block
			if ((i + 1) !=  len) {
				if (valueIdx(arg, i, tbl) != -1) 
					valPos = valueIdx(arg, i, tbl);
				else int valPos = tbl->pos;

				if (valuePos == tbl->pos) {
					int arraySize = (tbl->pos +1)*sizeof(char*);
					tbl->keys = (char**) realloc(tbl->keys, arraySize);
					tbl->values = (char**) realloc(tbl->values, arraySize);
				}

				int keySize = i;
				tbl->keys[valuePos] = (char*) malloc(keySize);
				strncpy(tbl->keys[valuePos], arg+1, i -1);
				tbl->keys[valuePos][i] = '\0';

				int valSize = len - i;
				tbl->values[valuePos] = (char*) malloc(valSize);
				strcpy(tbl->values[valuePos], (arg + i + 1));

				tbl->values[valuePos][len +1] = '\0';
		
				if (valuePos == tbl->pos) (tbl->pos)++;
			}
			return;
		}
	}
}

/**
 * Read and parse command line arguments.
 * The format is "-key" or "-key=val" where "key" and "val" are sequences of
 * alpha-numeric characters. All other string are silently discarded.  For
 * any key, only its last definition is retained.  "-key" has a NULL value.
 */
Table* ca_init(int argc, char **argv) 
{
	if (argc == 0 || argv == NULL) return;

	Table* tbl = (Table*) malloc(sizeof(Table));
	tbl->pos = 0;
	tbl->keys = tbl->values = NULL;

	for (int i = 1; i < argc; i++)
		process_string(strlen(argv[i]), argv[i], tbl);

	return tbl;
}
