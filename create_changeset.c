/**
 * Overall Flow:

  1. Open master.db
  2. Create table
  3. Insert demo data
  4. Copy to new slave.db
  5. Create a **session**
  6. Insert new data
  7. Save session changeset
  8. Close db

*/

#include "sqlite/sqlite3.h"
#include <stdio.h>
#include <stdlib.h>

// All the queries we will perform
char *setup_initial_data = "CREATE TABLE animals(id INTEGER PRIMARY KEY, name TEXT);"
                           "INSERT INTO animals(name) VALUES ('Cat');"
                           "INSERT INTO animals(name) VALUES ('Dog');";
char *insert_additional_data = "INSERT INTO animals(name) VALUES ('Cow');"
                               "INSERT INTO animals(name) VALUES ('Horse');";

int create_master_db();
int duplicate_master_db();

int main(void) {
  create_master_db();
  duplicate_master_db();
}

int create_master_db() {
  sqlite3 *db;
  char *err_msg;

  int rc = sqlite3_open("master.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
  }

  rc = sqlite3_exec(db, setup_initial_data, 0, 0, &err_msg);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
    sqlite3_close(db);
    return 1;
  }

  sqlite3_close(db);
  return 0;
}

int duplicate_master_db() {
  FILE *master = fopen("master.db", "r");
  if (!master) {
    fprintf(stderr, "Could not open master.db");
    return 1;
  }

  FILE *slave = fopen("slave.db", "w");

  char ch;
  while ((ch = fgetc(master)) != EOF)
    fputc(ch, slave);

  printf("File copied successfully.\n");

  fclose(master);
  fclose(slave);

  return 0;
}