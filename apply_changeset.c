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

void * load_binary_file(char *file_path, int *psize) {
   FILE *fp;
   void *buffer=0;
   int size;

   fp = fopen(file_path, "rb");
   if (fp) {
      fseek(fp, 0, SEEK_END);
      size = ftell(fp);
      rewind(fp);
      
      buffer = malloc(size);
      if (buffer) {
         fread(buffer, 1, size, fp);
         *psize = size;
      }

      fclose(fp);
   }
   return buffer;

}

int on_conflict (
 void *pCtx,                   /* Copy of sixth arg to _apply() */
 int eConflict,                /* DATA, MISSING, CONFLICT, CONSTRAINT */
 sqlite3_changeset_iter *iter  /* Handle describing change and conflict */
) {
  return SQLITE_CHANGESET_OMIT;
}

int main(void) {
  sqlite3 *db;
  char *err_msg;
  void *buffer;
  int size;

  int rc = sqlite3_open("slave.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
  }

  buffer = load_binary_file("changes.session", &size);
  printf("Applying changeset... (size: %d bytes)\n", size);
  sqlite3changeset_apply(db, size, buffer, 0, on_conflict, db);
  sqlite3_close(db);

  return 0;
}
