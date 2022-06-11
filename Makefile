sqlite_flags=-DSQLITE_ENABLE_SESSION -DSQLITE_ENABLE_PREUPDATE_HOOK -lpthread -lm -ldl

main: create_changeset apply_changeset

create_changeset: create_changeset.c sqlite3.o
	gcc create_changeset.c sqlite3.o $(sqlite_flags) -o create_changeset

apply_changeset: apply_changeset.c sqlite3.o
	gcc apply_changeset.c sqlite3.o $(sqlite_flags) -o apply_changeset

sqlite3.o: sqlite/sqlite3.c
	gcc -c sqlite/sqlite3.c $(sqlite_flags) -o sqlite3.o

clean:
	rm ./*.o ./*.db ./*.session ./create_changeset ./apply_changeset