#pragma once
#include <iostream>
#include <string>
#include "dropTable.h"
#include "formatName.h"
using namespace std;

string onOffCampusDormsTableName, roomNumsTableName;

int qstateDeliveryManagement;

void deliveryManagement() {
	//Stablishing the connection to mysql database
	MYSQL* conn;
	//MYSQL_ROW row;
	//MYSQL_RES* res;
	conn = mysql_init(0);

	conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

	if (conn) {
		//***criar DormsAndRoomsRecordTable***//
		if (tableExists("DormsAndRoomsRecordTable") == false) {
			string queryDormsAndRoomsRecordTable = "CREATE TABLE DormsAndRoomsRecordTable(DormTables VARCHAR(255), RoomNumsTables VARCHAR(255))";
			const char* qDormsAndRoomsRecordTable = queryDormsAndRoomsRecordTable.c_str();
			qstateDeliveryManagement = mysql_query(conn, qDormsAndRoomsRecordTable);
			if (qstateDeliveryManagement)
				cout << "Query failed: " << mysql_error(conn) << "\n";
		}
	listaDosDorms:
		string onOffCampus, escolha;
		cout << "* Select an option\n";
		cout << "1- ON campus\n";
		cout << "2- OFF campus\n";
		cout << "e- EXIT\n";
		cout << "Please, enter an option: ";
		cin >> escolha;

		if (escolha == "1")
			onOffCampus = "ON campus";
		else if (escolha == "2")
			onOffCampus = "OFF campus";
		else if (escolha == "e")
			goto DeliveryManagementEnd;

		//criar onOffCampusDormsTableName if it doesnt exist yet
		//take out all spaces and lower-case all letters first
		onOffCampus = formatName(onOffCampus);
		onOffCampusDormsTableName = onOffCampus + "DormsTable";

		if (tableExists(onOffCampusDormsTableName) == false) {
			string queryCreateTable = "CREATE TABLE " + onOffCampusDormsTableName + "(dormID INT KEY AUTO_INCREMENT, dormName VARCHAR(255) UNIQUE) ";
			const char* qCreateTable = queryCreateTable.c_str();
			qstateDeliveryManagement = mysql_query(conn, qCreateTable);
			if (qstateDeliveryManagement)
				cout << "Query failed: " << mysql_error(conn) << "\n";
		}

		cout << "* Select a dorm \n";
		//listing the dorms in the onOffCampusDormsTableName
		listarCoisas("dormID", "dormName", onOffCampusDormsTableName);

		//adding/removing dorms options
		cout << "a- Add\n";
		cout << "r- Remove\n";
		cout << "b- Back\n";
		cout << "Please, enter an option: ";
		string dormOption;
		cin >> dormOption;

		//heading to roomNums table
		if (isdigit(dormOption[0]) != 0) {
		listaDosRoomNums:
			string dormName;
			//Setting dormName
			dormName = getName_fromTable(onOffCampusDormsTableName, "dormName", "dormID", dormOption);

			//take out all spaces and lower-case all letters
			dormName = formatName(dormName);

			cout << "* Rooms in " + getName_fromTable(onOffCampusDormsTableName, "dormName", "dormID", dormOption) + "\n";
			//listing dormName table selected
			listarCoisas("roomNumID", "roomNumName", onOffCampus + dormName + "RoomNumsTable");

			//adding/removing a room options
			cout << "a- Add\n";
			cout << "r- Remove\n";
			cout << "b- Back to dorms\n";
			cout << "Please, enter an option: "; //CANT SELECT ROOMS!!! THEY ARE ONLY TO BE DISPLAYED!!!
			string roomNumOption;
			cin >> roomNumOption;

			//add roomNum
			if (roomNumOption == "a") {
				cout << "* Room Number: ";
				string newRoomNumName;
				cin.ignore();
				getline(cin, newRoomNumName);
				addCoisaToTable(newRoomNumName, "roomNumName", onOffCampus + dormName + "RoomNumsTable"); //ADDED
				goto listaDosRoomNums;
			}

			//remove roomNum
			else if (roomNumOption == "r") {
				cout << "* Select room  to be removed\n";
				//listing roomNum from RoomNumsTable
				listarCoisas("roomNumID", "roomNumName", onOffCampus + dormName + "RoomNumsTable");

				cout << "Please, enter an option: ";
				int IDtobeRem;
				cin >> IDtobeRem;
				string ItemTobeRem, IDtobeRemString = to_string(IDtobeRem);

				//Getting the roomNum name first
				ItemTobeRem = getName_fromTable(onOffCampus + dormName + "RoomNumsTable", "roomNumName", "roomNumID", IDtobeRemString);

				//Now removing the roomNum
				removeCoisaFromTable(ItemTobeRem, "roomNumName", onOffCampus + dormName + "RoomNumsTable"); //REMOVED

				goto listaDosRoomNums;
			}

			else if (roomNumOption == "b")
				goto listaDosDorms;
		}

		//add dorm
		else if (dormOption == "a") {
			cout << "* Name: ";
			string newDormName;
			cin.ignore();
			getline(cin, newDormName);
			addCoisaToTable(newDormName, "dormName", onOffCampusDormsTableName); //ADDED

			//Add dormName to the DormsAndRoomsRecordTable
			addCoisaToTable(newDormName, "DormTables", "DormsAndRoomsRecordTable"); //ADDED

				//***create RoomNumstable for newDormName
			//take out all spaces and lower-case all letters
			newDormName = formatName(newDormName);

			roomNumsTableName = onOffCampus + newDormName + "RoomNumsTable";

			string queryroomNumsTableName = "CREATE TABLE " + roomNumsTableName + "(roomNumID INT KEY AUTO_INCREMENT, roomNumName VARCHAR(255) UNIQUE)";
			const char* qroomNumsTableName = queryroomNumsTableName.c_str();
			qstateDeliveryManagement = mysql_query(conn, qroomNumsTableName);
			if (qstateDeliveryManagement)
				cout << "Query failed: " << mysql_error(conn) << "\n";

			//Add roomNumsTableName to the DormsAndRoomsRecordTable
			addCoisaToTable(roomNumsTableName, "RoomNumsTables", "DormsAndRoomsRecordTable"); //ADDED

			goto listaDosDorms;
		}

		//remove dorm
		else if (dormOption == "r") {
			cout << "* Select dorm to be removed\n";
			//listing the dorms in the onOffCampusDormsTableName
			listarCoisas("dormID", "dormName", onOffCampusDormsTableName);

			cout << "Please, enter an option: ";
			int IDtobeRem;
			cin >> IDtobeRem;
			string dormTobeRem, IDtobeRemString = to_string(IDtobeRem);

			//Getting the dormName name first
			dormTobeRem = getName_fromTable(onOffCampusDormsTableName, "dormName", "dormID", IDtobeRemString);

			//Now removing the dorm
			removeCoisaFromTable(dormTobeRem, "dormName", onOffCampusDormsTableName); //REMOVED

			//Rem roomNumsTableName to the DormsAndRoomsRecordTable
			removeCoisaFromTable(dormTobeRem, "DormTables", "DormsAndRoomsRecordTable"); //REMOVED

				//***dropping the dorm roomNumsTable***//
			//take out all spaces and lower-case all letters
			dormTobeRem = formatName(dormTobeRem);

			dropTable(onOffCampus + dormTobeRem + "RoomNumsTable"); //TABLE DROPPED

			//Remove RoomNumsTable from the DormsAndRoomsRecordTable
			removeCoisaFromTable(onOffCampus + dormTobeRem + "RoomNumsTable", "RoomNumsTables", "DormsAndRoomsRecordTable"); //REMOVED

			goto listaDosDorms;
		}

		//back to the beggining of the funcao
		else if (dormOption == "b")
			goto listaDosDorms;
	}
	else puts("Connection to DataBase has failed");

DeliveryManagementEnd:
	cout << "";
}

