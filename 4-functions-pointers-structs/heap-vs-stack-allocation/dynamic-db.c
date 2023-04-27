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
		if (fread(&row->set, sizeof(set), 1, conn->file) != 1)
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
	if (conn->db->MAX_ROWS<=0) die("MAX_ROWS must be positive");

	printf("MAX_DATA: ");
	// read user input and store it at memory address of MAX_DATA
	scanf("%d", &conn->db->MAX_DATA);
	if (conn->db->MAX_DATA<=0) die("MAX_DATA must be positive");

	conn->db->rows = (struct Address*)malloc(sizeof(struct Address)*conn->db->MAX_ROWS);

	for (size_t i = 0; i < conn->db->MAX_ROWS; i++) {
		char *a = (char*)malloc(conn->db->MAX_DATA);
		memset(a, 0, conn->db->MAX_DATA)
	}
}
