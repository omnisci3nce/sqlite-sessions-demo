#include "sqlite/sqlite3.h"

#define SQL_CALL_AND_CHECK(db, result) do { \
  int rc = (result); \
  if (rc != SQLITE_OK) { \
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db)); \
    sqlite3_close(db); \
    return 1; \
  } \
} while (0)
