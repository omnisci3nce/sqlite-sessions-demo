# sqlite-sessions-demo

1. run `make` in terminal to compile sqlite and the two demo executables
1. run `./create_changeset` to create two db files and a SQLite changeset file
1. inspect the following files
    1. `slave.db` : run `sqlite3 slave.db` to enter the CLI. Inspect the animals table with `select * from animals;`
    1. `master.db` : same as above for master.db
    1. you'll notice that master.db has two additional rows. These are the rows that have been run while a SQLite session was open -> and then saved into `changes.session`
1. run `./apply_changeset` to apply the changes from `changes.session` to `.slave.db`.
1. inspect the contents of `slave.db` from the CLI again. the two additional animal rows have been applied to the other database via the changeset file.