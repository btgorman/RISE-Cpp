#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <string>
#include <libpq-fe.h>

#include "Classes.cpp"

int db_read_bus(PGconn *conn);

void do_exit(PGconn *conn) {

	PQfinish(conn);
	exit(1);
}

int main() {

	std::string DBHOST = "8.26.94.3";
	std::string DBPORT = "3304";
	std::string DBNAME = "calc";
	std::string DBUSER = "rise";
	std::string DBPASSWORD = "capstone";

	std::string connectstr = "host=" + DBHOST + " port=" + DBPORT + " dbname=" + DBNAME + " user=" + DBUSER + " password=" + DBPASSWORD;
	PGconn *conn = PQconnectdb(connectstr.c_str());
	if (PQstatus(conn) == CONNECTION_BAD) {

		fprintf(stderr, "Connection to database failed: %s\n",
			PQerrorMessage(conn));
		do_exit(conn);
	}

	db_read_bus(conn);

	PQfinish(conn);

	return 0;
}

int db_read_bus(PGconn *conn) {
	enum {
		ID = 0,
		NAME = 1,
		OPERATIONAL_STATUS = 2,
		VOLTAGE_1_MAGNITUDE = 4,
		VOLTAGE_1_ANGLE = 5,
		VOLTAGE_1_PU = 6,
		TYPE = 7,
		LATITUDE = 8,
		LONGITUDE = 9,
		LL_VOLTAGE = 11,
		NOMINAL_VOLTAGE = 12
	};

	PGresult *res = PQexec(conn, "SELECT * FROM public.client_node, public.client_bus WHERE client_node.id = client_bus.node_ptr_id");

	if (PQresultStatus(res) != PGRES_TUPLES_OK) {

		printf("No data retrieved\n");
		PQclear(res);
		do_exit(conn);
	}

	int rows = PQntuples(res);

	for (int i = 0; i<rows; i++) {

		printf("%s %s %s\n", PQgetvalue(res, i, 0),
			PQgetvalue(res, i, 1), PQgetvalue(res, i, 2));
	}

	PQclear(res);

	return 0;
}