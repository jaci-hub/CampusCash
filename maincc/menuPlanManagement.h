#pragma once
#include <iostream>
#include <string>
#include "file_com_pragmaonce_mysql.h"
#include "getCurrentDay.h"
#include "getCurrentMonth.h"
#include "getCurrentYear.h"
#include "allinOne_class.h"
#include "tableExists.h"
#include "getLastDay.h"
#include "diningManagement.h"
#include "otherMenuPlanManagement.h"
#include "columnExists.h"
using namespace std;

int qstateMenuPlanManagement;
string menuTableInUse;

void menuPlanManagement() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        if (tableExists(allinOne_class.get_buildingName() + "DietTable") == false) {
            string queryDietTable = "CREATE TABLE " + allinOne_class.get_buildingName() + "DietTable(dietID INT KEY AUTO_INCREMENT, dietName VARCHAR(300) UNIQUE) ";
            const char* qDietTable = queryDietTable.c_str();
            qstateMenuPlanManagement = mysql_query(conn, qDietTable);
            if (qstateMenuPlanManagement)
                cout << "Query failed: " << mysql_error(conn) << "\n";

            //Add diet table to the MCIDrecordTable
            addCoisaToTable(allinOne_class.get_buildingName() + "DietTable", "DietTables", "MCIDrecordTable"); //ADDED
        }
    listaDasDiets:
        string dietOption;
        cout << "* Select a diet\n";
        //listar as diets from allinOne_class.get_buildingName() + "DietTable"
        if (tableExists(allinOne_class.get_buildingName() + "DietTable") == true)
            listarCoisas("dietID", "dietName", allinOne_class.get_buildingName() + "DietTable");
        else cout << "* No diet!\n";

        cout << "a- Add\n";
        cout << "r- Remove\n";
        cout << "b- Back\n";
        cout << "Please, enter an option: ";
        cin >> dietOption;
        if (isdigit(dietOption[0]) != 0) {
            allinOne_class.diet = getName_fromTable(allinOne_class.get_buildingName() + "DietTable", "dietName", "dietID", dietOption);
            allinOne_class.diet = formatName(allinOne_class.diet);
        }
        
        else if (dietOption == "a") {
            //add diet to allinOne_class.get_buildingName() + "DietTable")
            cout << "* Name: ";
            string newDietName;
            cin.ignore();
            getline(cin, newDietName);

            addCoisaToTable(newDietName, "dietName", allinOne_class.get_buildingName() + "DietTable"); //ADDED

            goto listaDasDiets;
        }
        else if (dietOption == "r") {
            //remove diet from allinOne_class.get_buildingName() + "DietTable")
            cout << "* Select diet to be removed\n";
            //listing diets from DietTable
            listarCoisas("dietID", "dietName", allinOne_class.get_buildingName() + "DietTable");

            cout << "Please, enter an option: ";
            int IDtobeRem;
            cin >> IDtobeRem;
            string ItemTobeRem, IDtobeRemString = to_string(IDtobeRem);

            //Getting the diet name first
            ItemTobeRem = getName_fromTable(allinOne_class.get_buildingName() + "DietTable", "dietName", "dietID", IDtobeRemString);

            //Now removing the item
            removeCoisaFromTable(ItemTobeRem, "dietName", allinOne_class.get_buildingName() + "DietTable"); //REMOVED

            ItemTobeRem = formatName(ItemTobeRem);

            //drop that diet menu plan table
            string queryDropMenuPlanTable = "SELECT * FROM MCIDrecordTable WHERE MenuPlanTables LIKE '%" + ItemTobeRem + allinOne_class.get_buildingName() + "MenuPlanTable" + "%'";
            const char* qDropMenuPlanTable = queryDropMenuPlanTable.c_str();
            qstateMenuPlanManagement = mysql_query(conn, qDropMenuPlanTable);
            if (!qstateMenuPlanManagement) {
                res = mysql_store_result(conn);
                while (row = mysql_fetch_row(res)) {
                    if (tableExists(row[0])) {
                        dropTable(row[0]);
                        //remove that diet menu plan table from MCIDrecordTable
                        removeCoisaFromTable(row[0], "MenuPlanTables", "MCIDrecordTable"); //REMOVED
                    }
                }
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

            //drop that diet category table
            if (tableExists(ItemTobeRem + allinOne_class.get_buildingName() + "CategoryTable") == true)
                dropTable(ItemTobeRem + allinOne_class.get_buildingName() + "CategoryTable");

            //drop that diet items table
            string queryDropItemsTable = "SELECT * FROM MCIDrecordTable WHERE ItemsTables LIKE '%" + ItemTobeRem + allinOne_class.get_buildingName() + "ItemsTable" + "%'";
            const char* qDropItemsTable = queryDropItemsTable.c_str();
            qstateMenuPlanManagement = mysql_query(conn, qDropItemsTable);
            if (!qstateMenuPlanManagement) {
                res = mysql_store_result(conn);
                while (row = mysql_fetch_row(res)) {
                    if (tableExists(row[2]))
                        dropTable(row[2]);
                }
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

            //remove that diet category table from MCIDrecordTable
            removeCoisaFromTable(ItemTobeRem + allinOne_class.get_buildingName() + "CategoryTable", "CategoryTables", "MCIDrecordTable"); //REMOVED

            //remove that diet item table from MCIDrecordTable
            string queryRemItemsTables = "DELETE FROM MCIDrecordTable WHERE ItemsTables LIKE '%" + ItemTobeRem + allinOne_class.get_buildingName() + "ItemsTable" + "%'";
            const char* qRemItemsTables = queryRemItemsTables.c_str();
            qstateRem = mysql_query(conn, qRemItemsTables);
            if (qstateRem)
                cout << "Query failed: " << mysql_error(conn) << "\n";

            goto listaDasDiets;
        }
        else if (dietOption == "b") {
            goto menuPlanManagementEnd;
        }

        cout << "* Select an option\n";
        cout << "1- Plan Menu\n";
        cout << "2- Other\n";
        cout << "3- Back\n";
        cout << "Please, enter an option: ";
        int menuOtherOption;
        cin >> menuOtherOption;

        //plan menu
        if (menuOtherOption == 1) {
        mesAndAno:
            //Display current month and year
            string mes, ano;
            cout << "* Select a month\n";
            cout << "1- January\n";
            cout << "2- February\n";
            cout << "3- March\n";
            cout << "4- April\n";
            cout << "5- May\n";
            cout << "6- June\n";
            cout << "7- July\n";
            cout << "8- August\n";
            cout << "9- September\n";
            cout << "10- October\n";
            cout << "11- November\n";
            cout << "12- December\n";
            cout << "13- Back\n";
            cout << "Please, enter an option: ";
            cin >> mes;
            if (mes == "13")
                goto listaDasDiets;
            selectYear:
            cout << "* Select a year\n";
            int currentYear = stoi(getCurrentYear()), yearChoice;
            cout << "0- " << currentYear << "\n";
            cout << "1- " << currentYear + 1 << "\n";
            cout << "Please, enter an option: ";
            cin >> yearChoice;
            if (yearChoice == 0)
                ano = to_string(currentYear);
            else if (yearChoice == 1)
                ano = to_string(currentYear + 1);
            else { 
                cout << "Invalid!\n";
                goto selectYear; 
            }

            //Cant select dates before today
            if (stoi(mes) < stoi(getCurrentMonth()) && stoi(ano) <= stoi(getCurrentYear())) {
                cout << "**Cant select past dates!\n";
                goto mesAndAno;
            }
            string monthName;
            string queryMonthName = "SELECT MONTHNAME('" + ano + "-" + mes + "-" + getCurrentDay() + "')";
            const char* qMonthName = queryMonthName.c_str();
            qstateMenuPlanManagement = mysql_query(conn, qMonthName);
            if (!qstateMenuPlanManagement) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                monthName = row[0];
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

            cout << "**Menu Plan**\n";
            cout << monthName << ", " << ano << "\n";

            //set o nome da new menuTableInUse
            menuTableInUse = allinOne_class.diet + allinOne_class.get_buildingName() + "MenuPlanTable" + mes + ano;

            //CRIACAO DA MENU PLAN TABLE FOR THE MONTH if it doesnt already exists
            if (tableExists(menuTableInUse) == false) {
                string queryCriarTable = "CREATE TABLE " + menuTableInUse + "(mealID VARCHAR(255) NOT NULL, meal VARCHAR(255) NOT NULL)";
                const char* qCriarTable = queryCriarTable.c_str();
                qstateMenuPlanManagement = mysql_query(conn, qCriarTable);
                if (qstateMenuPlanManagement)
                    cout << "Query failed: " << mysql_error(conn) << "\n";

                //INSERTING VALUES
                string queryInserirValues = "INSERT INTO " + menuTableInUse + "(mealID, meal) VALUES ('1', 'Breakfast'), ('2', 'Brunch'), ('3', 'Lunch'), ('4', 'Dinner')";
                const char* qInserirValues = queryInserirValues.c_str();
                qstateMenuPlanManagement = mysql_query(conn, qInserirValues);
                if (qstateMenuPlanManagement)
                    cout << "Query failed: " << mysql_error(conn) << "\n";

                //Add menuTableInUse to the MCIDrecordTable
                addCoisaToTable(menuTableInUse, "MenuPlanTables", "MCIDrecordTable"); //ADDED
            }

        listaDosDias:
            //display the days
            string dayChosen;
            cout << "* Select day\n";
            int i, lastDay = stoi(getLastDay(mes, ano));
            for (i = 1; i <= lastDay; i++)
                cout << i << "- " << i << "\n";
            cout << to_string(i) << "- Back\n";
            cout << "Please, enter an option: ";
            cin >> dayChosen;
            if (dayChosen == to_string(i))
                goto mesAndAno;
            else if (stoi(dayChosen) < stoi(getCurrentDay()) && stoi(mes) == stoi(getCurrentMonth())) {
                cout << "**Cant select past days!\n";
                goto listaDosDias;
            }
            //INSERT CHOSEN DAY into menuTableInUse IF IT DOESNT EXIST YET
            else if(columnExists("Day" + dayChosen, menuTableInUse) == false) {
                string queryInserirDays = "ALTER TABLE " + menuTableInUse + " ADD Day" + dayChosen + " VARCHAR(255)";
                const char* qInserirDays = queryInserirDays.c_str();
                qstateMenuPlanManagement = mysql_query(conn, qInserirDays);
                if (qstateMenuPlanManagement)
                    cout << "Query failed: " << mysql_error(conn) << "\n";

                //SET 'none' as default value for DAY(dayChosen)
                string querySetNone = "UPDATE " + menuTableInUse + " SET Day" + dayChosen + " = 'none'";
                const char* qSetNone = querySetNone.c_str();
                qstateMenuPlanManagement = mysql_query(conn, qSetNone);
                if (qstateMenuPlanManagement)
                    cout << "Query failed: " << mysql_error(conn) << "\n";
            }

            //display day, date chosen
            string dayName;
            string queryDayName = "SELECT DAYNAME('" + ano + "-" + mes + "-" + dayChosen + "')";
            const char* qDayName = queryDayName.c_str();
            qstateMenuPlanManagement = mysql_query(conn, qDayName);
            if (!qstateMenuPlanManagement) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                dayName = row[0];
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

        listaDosMeals:
            cout << "*" << dayName << "* " << monthName << " " << dayChosen << ", " << ano << "\n";

            //listing the meals from the menuTableInUse
            //listarCoisas("mealID", "meal", menuTableInUse);
            if (dayName == "Saturday" || dayName == "Sunday")
                cout << "2- Brunch\n";
            else {
                cout << "1- Breakfast\n";
                cout << "3- Lunch\n";
            }
            cout << "4- Diner\n";
            cout << "5- Back\n";

            string mealChosen;
            int optionFinalmente;
            cout << "Please, enter an option: ";
            cin >> mealChosen;

            if (stoi(mealChosen) >=1 && stoi(mealChosen) <=4) {
                //***criar mealsTimeAndPrice table***// IF IT DOESNT EXIST YET
                if (tableExists(allinOne_class.get_buildingName() + "MealsTimeAndPrice") == false) {
                    string querymealsTimeAndPrice = "CREATE TABLE " + allinOne_class.get_buildingName() + "MealsTimeAndPrice(mealID VARCHAR(255), meal VARCHAR(255), startTime VARCHAR(255), endTime VARCHAR(255), price DOUBLE(5,2))";
                    const char* qmealsTimeAndPrice = querymealsTimeAndPrice.c_str();
                    qstateMenuPlanManagement = mysql_query(conn, qmealsTimeAndPrice);
                    if (qstateMenuPlanManagement)
                        cout << "Query failed: " << mysql_error(conn) << "\n";

                    //INSERTING VALUES into mealsTimeAndPrice
                    string queryInserirValues = "INSERT INTO " + allinOne_class.get_buildingName() + "MealsTimeAndPrice(mealID, meal, startTime, endTime, price) VALUES ('1', 'Breakfast', 'none', 'none', 0), ('2', 'Brunch', 'none', 'none', 0), ('3', 'Lunch', 'none', 'none', 0), ('4', 'Dinner', 'none', 'none', 0)";
                    const char* qInserirValues = queryInserirValues.c_str();
                    qstateMenuPlanManagement = mysql_query(conn, qInserirValues);
                    if (qstateMenuPlanManagement)
                        cout << "Query failed: " << mysql_error(conn) << "\n";
                }

                //Select the dayChosen and mealChosen spot
                string spotValue;
                string querymealID = "SELECT Day" + dayChosen + " FROM " + menuTableInUse + " WHERE mealID = '" + mealChosen + "'";
                const char* qmealID = querymealID.c_str();
                qstateMenuPlanManagement = mysql_query(conn, qmealID);
                if (!qstateMenuPlanManagement) {
                    res = mysql_store_result(conn);
                    while (row = mysql_fetch_row(res)) {
                        spotValue = row[0];
                    }
                }
                else cout << "Query failed: " << mysql_error(conn) << "\n";

                string nameofDish, ingredients;
                //if it is NULL, update to Name of meal and ingredients
                if (spotValue == "none") {
                updateMeal:
                    cout << "* Name of the dish: ";
                    cin.ignore();
                    getline(cin, nameofDish);
                    cout << "* Ingredients: ";
                    getline(cin, ingredients);
                    cout << "\n";

                    //UPDATE nameofDish and ingredients in the menuTableInUse
                    string querymealUpdate = "UPDATE " + menuTableInUse + " SET Day" + dayChosen + " = '*Dish: " + nameofDish + " *Ingredients: " + ingredients + "' WHERE mealID = '" + mealChosen + "'";
                    const char* qmealUpdate = querymealUpdate.c_str();
                    qstateMenuPlanManagement = mysql_query(conn, qmealUpdate);
                    if (qstateMenuPlanManagement)
                        cout << "Query failed: " << mysql_error(conn) << "\n";

                    cout << "*Dish added!\n";

                    //back to select meal or back to menu
                    cout << "\n";
                    cout << "1- Back to meals\n";
                    cout << "2- Back to days\n";
                    cout << "3- Back to diets\n";
                    cout << "4- EXIT Dining\n";
                    cout << "Please, enter an option: ";
                    cin >> optionFinalmente;

                    if (optionFinalmente == 1)
                        goto listaDosMeals;
                    else if (optionFinalmente == 2)
                        goto listaDosDias;
                    else if (optionFinalmente == 3)
                        goto listaDasDiets;
                    else if (optionFinalmente == 4)
                        goto menuPlanManagementEnd;
                }
                //else display it
                else {
                    //Display nameofDish and ingredients in the menuTableInUse
                    string querymealDisplay = "SELECT Day" + dayChosen + " FROM " + menuTableInUse + " WHERE mealID = '" + mealChosen + "'";
                    const char* qmealDisplay = querymealDisplay.c_str();
                    qstateMenuPlanManagement = mysql_query(conn, qmealDisplay);
                    if (!qstateMenuPlanManagement) {
                        res = mysql_store_result(conn);
                        row = mysql_fetch_row(res);
                        cout << "\n";
                        cout << row[0] << "\n";
                    }
                    else cout << "Query failed: " << mysql_error(conn) << "\n";

                    //update or back to select meal
                    cout << "\n";
                    cout << "0- Update\n";
                    cout << "1- Back to meals\n";
                    cout << "2- Back to days\n";
                    cout << "3- Back to diets\n";
                    cout << "4- EXIT Dining\n";
                    cout << "Please, enter an option: ";
                    cin >> optionFinalmente;

                    if (optionFinalmente == 0) //IMPORTANT: it has to be before the start time of the selected meal
                        goto updateMeal;
                    else if (optionFinalmente == 1)
                        goto listaDosMeals;
                    else if (optionFinalmente == 2)
                        goto listaDosDias;
                    else if (optionFinalmente == 3)
                        goto listaDasDiets;
                    else if (optionFinalmente == 4)
                        goto menuPlanManagementEnd;
                }
            }
            else if (mealChosen == "5")
                goto listaDosDias;
        }
        //other
        else if (menuOtherOption == 2) {
            otherMenuPlanManagement(); //from otherMenuPlanManagement.h

            //back to...
            int lastChoice;
            cout << "\n";
            cout << "1- Back to diets\n";
            cout << "2- EXIT Dining\n";
            cout << "Please, enter an option: ";
            cin >> lastChoice;

            if (lastChoice == 1)
                goto listaDasDiets;
            else if (lastChoice == 2)
                goto menuPlanManagementEnd;
        }
        else if (menuOtherOption == 3)
            goto listaDasDiets;
    }
    else puts("Connection to DataBase has failed");

menuPlanManagementEnd:
    cout << "";
}