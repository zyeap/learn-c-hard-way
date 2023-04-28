#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// Modification of heap vs stack allocation to allow MAX_DATA and MAX_ROWS to be arbitrarily sized

struct Address {
	int id;
	int set;
	char *name; // string pointer
	char *email;
};

struct Database {
	int MAX_ROWS;
	int MAX_DATA;
	struct Address *rows; 
};

struct Connection {
	FILE *file;
	struct Database *db;
};

void Database_close(struct Connection *conn) {
	if (conn) {
		// size_t is unsigned data type 
		for(size_t i = 0; i < conn->db->MAX_ROWS; i++) {
			struct Address *row = &conn->db->rows[i];

			if (row->name) free(row->name);
			if (row->email) free(row->email);
		}

		if (conn->db->rows) free(conn->db->rows);
		if (conn->db) free(conn->db);
		if (conn->file) free(conn->file);

		free(conn);
	}
}

void die(char *message, struct Connection *conn) {
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	Database_close(conn);
	exit(1);
}

void diec(char *message) {
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	exit(1);
}

void Address_print(struct Address *addr) {
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

// load database into memory
void Database_load(struct Connection *conn) {
	assert(conn->db && conn->file);

	// fread(pointer location in program memory, size of data, items of data, input file stream)
	// fread returns number of items read (in this case, 1)
	if(fread(conn->db, sizeof(struct Database), 1, conn->file) != 1)
		die("Failed to load database", conn);

	conn->db->rows = (struct Address*)malloc(sizeof(struct Address) * conn->db->MAX_ROWS);

	for (size_t i = 0; conn->db->MAX_ROWS; i++) {
		struct Address *row = &conn->db->rows[i];

		if (fread(&row->id, sizeof(int), 1, conn->file) != 1)
			die("Failed to load id\n", conn);
		if (fread(&row->set, sizeof(int), 1, conn->file) != 1)
			die("Failed to load set\n", conn);

		row->name = malloc(conn->db->MAX_DATA);
		row->email = malloc(conn->db->MAX_DATA);

		if (fread(row->name, conn->db->MAX_DATA, 1, conn->file) != 1)
			die("Failed to load name\n", conn);
		if (fread(row->email, conn->db->MAX_DATA, 1, conn->file) != 1)
			die("Failed to load email\n", conn);
	}
}

// Establish database connection by allocating sufficient memory and opening the database file
struct Connection *Database_open(const char *filename, char mode) {
	struct Connection *conn = malloc(sizeof(struct Connection));
	if (!conn) die("Memory error", conn);

	conn->db = malloc(sizeof(struct Database));
	if(!conn->db) die("Memory error", conn);
	
	if (mode == 'c') {
		// w truncates file to 0 length or creates text file for writing
		conn->file = fopen(filename, "w");
	} else {
		// r+ opens for r/w with stream positioned at beginning of file
		conn->file = fopen(filename, "r+");
		if (conn->file) {
			Database_load(conn);
		}
	}

	if (!conn->file) die("Failed to open file", conn);
	return conn;
}

// Initialize empty database with sufficient memory for rows
void Database_create(struct Connection *conn) {
	printf("MAX_ROWS: ");
	// read user input and store it at memory address of MAX_ROWS
	scanf("%d", &conn->db->MAX_ROWS);
	if (conn->db->MAX_ROWS<=0) die("MAX_ROWS must be positive", conn);

	printf("MAX_DATA: ");
	// read user input and store it at memory address of MAX_DATA
	scanf("%d", &conn->db->MAX_DATA);
	if (conn->db->MAX_DATA<=0) die("MAX_DATA must be positive", conn);

	conn->db->rows = (struct Address*)malloc(sizeof(struct Address)*conn->db->MAX_ROWS);

	for (size_t i = 0; i < conn->db->MAX_ROWS; i++) {
		char *a = (char*)malloc(conn->db->MAX_DATA);
		// memset(pointer, int value, size_t length of data to write)
		// write len bytes of int value to pointer location in memory
		memset(a, 0, conn->db->MAX_DATA);
		char *b = (char*)malloc(conn->db->MAX_DATA);
		memset(b, 0, conn->db->MAX_DATA);

		// struct prototype with initial values
		struct Address addr = {.id = i, .set = 0, .name = a, .email = b};
		conn->db->rows[i] = addr;
	}
}

// write database info in memory to file
void Database_write(struct Connection *conn) {
	// rewind sets file position indicator for stream to beginning of the file
	// rewind returns no value
	rewind(conn->file);

	if (fwrite(conn->db, sizeof(struct Database), 1, conn->file) != 1) {
		die("Failed to write database, conn", conn);
	}

	for (size_t i = 0; i < conn->db->MAX_ROWS; i++) {
		if (fwrite(&((conn->db->rows[i]).id), sizeof(int), 1, conn->file) != 1)
			die("Failed to write id.", conn);
		if (fwrite(&((conn->db->rows[i]).set), sizeof(int), 1, conn->file) != 1)
			die("Failed to write set.", conn);
		if (fwrite(&((conn->db->rows[i]).name), conn->db->MAX_DATA, 1, conn->file) != 1)
			die("Failed to write name.", conn);
		if (fwrite(&((conn->db->rows[i]).email), conn->db->MAX_DATA, 1, conn->file) != 1)
			die("Failed to write email.", conn);
	}

	fflush(conn->file);
}

// set data (user input) into database
void Database_set(struct Connection *conn, int id, char *name, char *email) {
	struct Address *addr = &conn->db->rows[id];
	if (addr->set) die("ID already set", conn);

	addr->set = 1;

	// set last character to null byte for both name and email
	name[conn->db->MAX_DATA - 1] = '\0';
	email[conn->db->MAX_DATA - 1] = '\0';

	// strncpy(destination, source, size_t len)
	strncpy(addr->name, name, conn->db->MAX_DATA);
	strncpy(addr->email, email, conn->db->MAX_DATA);
}

// get/print user info from database
void Database_get(struct Connection *conn, int id) {
	struct Address *addr = &conn->db->rows[id];

	if (addr->set){
		Address_print(addr);
	} else {
		die("ID not set", conn);
	}
}

// delete row from database
void Database_delete(struct Connection *conn, int id) {
	char *a = (char*)malloc(conn->db->MAX_DATA);
	char *b = (char*)malloc(conn->db->MAX_DATA);

	free(conn->db->rows[id].name);
	free(conn->db->rows[id].email);

	struct Address addr = {.id = id, .set = 0, .name = a, .email = b};
	conn->db->rows[id] = addr;
}

// list all records in the database
void Database_list(struct Connection *conn) {
	for (size_t i = 0; i < conn->db->MAX_ROWS; i++) {
		if (conn->db->rows[i].set){
			Address_print(&(conn->db->rows[i]));
		}
	}
}

// find database record with maching keyword
void Database_find(struct Connection *conn, char *keyword) {
	int i = 0;
	int count = 0;

	// 2 loops to cover all rows in db
	// nested loop will break once one match is found
	// outer loop will continue from last found match id and search for other matches
	while (i < conn->db->MAX_ROWS) {
		while (i < conn->db->MAX_ROWS) {
			if(conn->db->rows[i].set == 1) {
				if (strstr(conn->db->rows[i].name, keyword) != NULL || strstr(conn->db->rows[i].email, keyword) != NULL) {
					break;
				}
			}
			i++;
		}

		if (i>=conn->db->MAX_ROWS) break;
		Address_print(&(conn->db->rows[i]));
		count++;
		i++;
	}

	if (count == 0) {
		printf("No matches found, try some other words.\n");
	}
}

int main(int argc, char *argv[]) {
	if (argc < 3) diec("USAGE: ./dynamic-db <dbfile> <action> [action params]");
	int id = 0;
	if (argc > 3) id = atoi(argv[3]);

	char *filename = argv[1];
	char action = argv[2][0];
	struct Connection *conn = Database_open(filename,action);

	switch (action) {
		case 'c':
			Database_create(conn);
			Database_write(conn);
			printf("\nDatabase created.\n");
			break;
		case 'g':
			if(argc != 4) die("Need an id to get", conn);
			Database_get(conn, id);
			break;
		case 's':
			if(argc != 6) die("Need an id, name, and email to set", conn);
			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;
		case 'd':
			if(argc != 4) die("Need an id to delete", conn);
			Database_delete(conn, id);
			Database_write(conn);
			break;
		case 'l':
			Database_list(conn);
			break;
		case 'f':
			if(argc != 4) die("Need keyword to search", conn);
			Database_find(conn, argv[3]);
			break;
		default:
			die("Invalid action, only: c=create, g=get, s=set, d=del, l=list, f=find", conn);
	}
}
