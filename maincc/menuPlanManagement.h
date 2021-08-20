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
    listaDosMealType:
        int mealTypeID;
        cout << "* Select an option\n";
        cout << "1- Meat eater\n";
        cout << "2- Vegetarian\n";
        cout << "3- Vegan\n";
        cout << "4- Back\n";
        cout << "Please, enter an option: ";
        cin >> mealTypeID;

        if (mealTypeID == 1)
            allinOne_class.mealType = "Meat eater";
        else if (mealTypeID == 2)
            allinOne_class.mealType = "vegetarian";
        else if (mealTypeID == 3)
            allinOne_class.mealType = "vegan";
        else if (mealTypeID == 4)
            goto menuPlanManagementEnd;

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
                goto listaDosMealType;
            cout << "* Year: ";
            cin >> ano;

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
            cout << monthName << ", " << ano << "\n\n";

            cout << "* Just a moment...\n\n";

            //set o nome da new menuTableInUse
            menuTableInUse = allinOne_class.mealType + allinOne_class.get_buildingName() + "MenuPlanTable" + mes + ano;

            //CRIACAO DA MENU PLAN TABLE FOR THE MONTH if it doesnt already exists
            if (tableExists(menuTableInUse) == false) {
                string queryCriarTable = "CREATE TABLE " + menuTableInUse + "(mealID VARCHAR(255) NOT NULL, meal VARCHAR(255) NOT NULL) ";
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

                //Add menuTableInUse to the MCIrecordTable
                addCoisaToTable(menuTableInUse, "MenuPlanTables", "MCIrecordTable"); //ADDED
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
            else if (stoi(dayChosen) <= stoi(getCurrentDay()) && stoi(mes) == stoi(getCurrentMonth())) {
                cout << "**Cant select today or past days!\n";
                goto listaDosDias;
            }
            else {//INSERT CHOSEN DAY into menuTableInUse IF IT DOESNT EXIST YET
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
            listarCoisas("mealID", "meal", menuTableInUse);

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

                    cout << "** Success!\n";

                    //back to select meal or back to menu
                    cout << "\n";
                    cout << "1- Back to meals\n";
                    cout << "2- Back to days\n";
                    cout << "3- Back to type of meal\n";
                    cout << "4- EXIT Dining\n";
                    cout << "Please, enter an option: ";
                    cin >> optionFinalmente;

                    if (optionFinalmente == 1)
                        goto listaDosMeals;
                    else if (optionFinalmente == 2)
                        goto listaDosDias;
                    else if (optionFinalmente == 3)
                        goto listaDosMealType;
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
                    cout << "3- Back to type of meal\n";
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
                        goto listaDosMealType;
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
            cout << "1- Back to type of meal\n";
            cout << "2- EXIT Dining\n";
            cout << "Please, enter an option: ";
            cin >> lastChoice;

            if (lastChoice == 1)
                goto listaDosMealType;
            else if (lastChoice == 2)
                goto menuPlanManagementEnd;
        }
        else if (menuOtherOption == 3)
            goto listaDosMealType;
    }
    else puts("Connection to DataBase has failed");

menuPlanManagementEnd:
    cout << "";
}