
#include <stdio.h>
#include <sqlite3.h>
#include <string>

using namespace std;


int main(int argc, char **argv) {
	sqlite3 * db;
	char * sql;
	sqlite3_stmt * stmt;
	int nrecs;
	char * errmsg;
	int i;
	int row = 0;
	int arg;
	int rc;

	rc = sqlite3_open_v2("app/native/first.db", &db, SQLITE_OPEN_CREATE | SQLITE_OPEN_READWRITE, NULL);
	if( rc ){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}

	string cmd = "CREATE TABLE IF NOT EXISTS t (xyz TEXT)";
	rc = sqlite3_prepare_v2(db, cmd.c_str(), strlen(cmd.c_str()) + 1, &stmt, NULL);
	if( rc ) {
		fprintf(stderr, "Can't prepare create statement: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}

	if (sqlite3_step(stmt) != SQLITE_DONE) {
	    printf("\nCould not step (execute) stmt.\n");
	    return 1;
	 }

	cmd = "INSERT INTO t (xyz) VALUES ('Arthur')";
	rc = sqlite3_prepare_v2(db, cmd.c_str(), strlen(cmd.c_str()) + 1, &stmt, NULL);
	if( rc ) {
		fprintf(stderr, "Can't prepare insert statement: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}

	if (sqlite3_step(stmt) != SQLITE_DONE) {
		printf("\nCould not step (execute) stmt.\n");
		return 1;
	}

	cmd = "SELECT * FROM t WHERE xyz = ?";
	rc = sqlite3_prepare_v2(db, cmd.c_str(), strlen(cmd.c_str()) + 1, &stmt, NULL);
	if( rc ) {
		fprintf(stderr, "Can't prepare select statement: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}

	//for (arg = 1; arg < argc; arg++) {
		sqlite3_bind_text(stmt,
							1, /* The number of the argument in value. */
							"Arthur",
							strlen("Arthur"),
							0 /* The callback. */
							);

		while (1) {
			int s;

			s = sqlite3_step (stmt);
			if (s == SQLITE_ROW) {
				int bytes;
				const unsigned char * text;
				bytes = sqlite3_column_bytes(stmt, 0);
				text  = sqlite3_column_text (stmt, 0);
				printf ("%d: %s\n", row, text);
				row++;
			}
			else if (s == SQLITE_DONE) {
				break;
			}
			else {
				fprintf (stderr, "Failed.\n");
				exit (1);
			}
		}

		sqlite3_reset(stmt);
		sqlite3_clear_bindings(stmt);
	//}
	return 0;

}

