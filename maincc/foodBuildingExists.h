#pragma once

int qstatefoodBuildingExists;

bool foodBuildingExists(string foodBuildingName) {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		string querySelectfoodBuilding = "SELECT foodBuildingID FROM foodBuildingsTable WHERE foodBuildingName = '" + foodBuildingName + "'";
		const char* qSelectfoodBuilding = querySelectfoodBuilding.c_str();
		qstatefoodBuildingExists = mysql_query(conn, qSelectfoodBuilding);
		if (!qstatefoodBuildingExists) {
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
				return true;
			return false;
		}
		else cout << "Query failed: " << mysql_error(conn) << "\n";
	}
	else puts("Connection to DataBase has failed");
}