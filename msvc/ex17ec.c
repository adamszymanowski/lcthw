#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
// Extra Credit - Change the code to accept parameters for MAX_DATA and MAX_ROWS, store them in the
// Database struct, and write that to the file, thus creating a database that can be arbitrarily sized

struct Address {
    int id;
    int set;
    char *name;
    char *email;
};

struct Database {
    size_t max_rows;
    size_t max_data;
    struct Address *rows;
};

struct Connection {
    FILE *file;
    struct Database *db;
};

void die(const char* message)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1)
        die("Failed to load Database!");
}

struct Connection *Database_open(const char *filename, char mode)
{
    struct Connection *conn = malloc(sizeof(struct Connection));
    if (!conn)
        die("Memory error");

    conn->db = malloc(sizeof(struct Database));
    if (!conn->db)
        die("Memory error");

    if (mode == 'c') {
        conn->file = fopen(filename, "wb"); // modes must be binary, otherwise it won't work!
    } else {
        conn->file = fopen(filename, "rb+"); // same here, binary!

        if (conn->file) {
            Database_load(conn);
        }
    }

    if (!conn->file)
        die("Failed to open the file");

    return conn;
}

void Database_close(struct Connection *conn, size_t max_rows)
{
    if (conn) {
        if (conn->file)
            fclose(conn->file);

        int i = 0;
        for (i = 0; i < max_rows; i++) {
            if (conn->db->rows[i]->name)
                free(conn->db->rows[i]->name);
            if(conn->db->rows[i]->email)
                free(conn->db->rows[i]->email);
        }    

        if (conn->db)
            free(conn->db);
        free(conn);
    }
}

void Database_write(struct Connection *conn)
{
    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
    if (rc != 1)
        die("Failed to write database.");

    rc = fflush(conn->file);
    if (rc == -1)
        die("Cannot flush database.");
}

void Database_create(struct Connection *conn, size_t max_rows, size_t max_data)
{
    conn->db->max_rows = max_rows;
    conn->db->max_data = max_data;
    int i = 0;
    for (i = 0; i < max_rows; i++) {
        // make a prototype to initialize it
        struct Address addr = {.id = i,.set = 0 };
        // then just assign it
        conn->db->rows[i] = addr;

        char *name = malloc(max_data);
        memset(name, 0, max_data);
        conn->db->name = name;

        char *email = malloc(max_data);
        memset(email, 0, max_data);
        conn->db->email = email;
    }
}

void Database_set(struct Connection *conn, int id, const char *name,
        const char *email)
{
    struct Address *addr = &conn->db->rows[id];
    if (addr->set)
        die("Alredy set, delete it first");

    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, conn->db->max_data);
    // demonstrate strncpy bug
    if (!res)
        die("Name copy failed");

    res = strncpy(addr->email, email, MAX_DATA);
    if (!res)
        die("Email copy failed");
}

void Database_get(struct Connection *conn, int id)
{
    struct Address *addr = &conn->db->rows[id];

    if (addr->set) {
        Address_print(addr);
    } else {
        die("ID is not set");
    }
}

void Database_delete(struct Connection *conn, int id)
{
    struct Address addr = {.id = id,.set = 0};
    conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    for (i = 0; i < conn->db->max_rows; i++)
    {
        struct Address *cur = &db->rows[i];

        if (cur->set) {
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
        die("usage: ex17 <dbfile> <action> [action params]");

    char *filename = argv[1];
    char action = argv[2][0];
    struct Connection *conn = Database_open(filename, action);
    int id = 0;
    size_t max_data;
    size_t max_rows;

    if (action == 'c') {
        if (argc == 6) {
            max_rows = atoi(argv[4]);
            max_data = atoi(argv[5]);
        } else {
            die("usage: ex17 <dbfile> c <max_rows> <max_data>");
        }
    } else {
        if (argc > 3) id = atoi(argv[3]);
        max_data = conn->db->max_data;
        max_rows = conn->db->max_rows;
    }


    if (id >= MAX_ROWS) die("There's not that many records.");

    switch (action) {
        case 'c':
            Database_create(conn);
            Database_write(conn);
            break;

        case 'g':
            if (argc != 4)
                die("Need an id to get");

            Database_get(conn, id); 
            break;

        case 's':
            if (argc != 6)
                die("Need id, name, email to set");

            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if (argc != 4)
                die("Need id to delete");

            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            Database_list(conn);
            break;

        default:
            die("Invalid action: c=create, g=get, d=del, l=list");
    }

    Database_close(conn);

    return 0;
}