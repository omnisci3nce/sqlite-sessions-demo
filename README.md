# sqlite-sessions-demo
 
### Compilation

`gcc sqlite/sqlite3.c create_changeset.c -DSQLITE_ENABLE_SESSION -DSQLITE_ENABLE_PREUPDATE_HOOK -lpthread -lm -ldl -o create_changeset`

`gcc sqlite/sqlite3.c apply_changeset.c -DSQLITE_ENABLE_SESSION -DSQLITE_ENABLE_PREUPDATE_HOOK -lpthread -lm -ldl -o apply_changeset`