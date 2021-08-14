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
string mealType, menuTableInUse, optionFinalmente;

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
        cout << "1- MeatEater\n";
        cout << "2- Vegetarian\n";
        cout << "3- Vegan\n";
        cout << "Please, enter an option: ";
        cin >> mealTypeID;

        if (mealTypeID == 1)
            mealType = "meatEater";
        else if (mealTypeID == 2)
            mealType = "vegetarian";
        else if (mealTypeID == 3)
            mealType = "vegan";

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
        cout << "Please, enter an option: ";
        cin >> mes;
        cout << "* Year: ";
        cin >> ano;

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
        menuTableInUse = mealType + allinOne_class.get_buildingName() + "MenuPlanTable" + mes + ano;
        
        //CRIACAO DA MENU PLAN TABLE FOR THE MONTH if it doesnt already exists
        if (tableExists(menuTableInUse) == false) {
            string queryCriarTable = "CREATE TABLE " + menuTableInUse + "(mealID VARCHAR(255) NOT NULL, meal VARCHAR(255) NOT NULL, mealPrice DOUBLE(5, 2), mealStartTime VARCHAR(255), mealEndTime VARCHAR(255)) ";
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

            //INSERT DAYS OF MONTH
            for (int i = 1; i <= stoi(getLastDay(mes, ano)); i++) {
                string queryInserirDays = "ALTER TABLE " + menuTableInUse + " ADD Day" + to_string(i) + " VARCHAR(255)";
                const char* qInserirDays = queryInserirDays.c_str();
                qstateMenuPlanManagement = mysql_query(conn, qInserirDays);
                if (qstateMenuPlanManagement)
                    cout << "Query failed: " << mysql_error(conn) << "\n";

                //SET 'none' as default value for DAY(i)
                string querySetNone = "UPDATE " + menuTableInUse + " SET Day" + to_string(i) + " = 'none'";
                const char* qSetNone = querySetNone.c_str();
                qstateMenuPlanManagement = mysql_query(conn, qSetNone);
                if (qstateMenuPlanManagement)
                    cout << "Query failed: " << mysql_error(conn) << "\n";
            }
        }

        listaDosDias:
        //display the days
        string dayChosen;
        cout << "* Select day\n";
        for (int i = 1; i <= stoi(getLastDay(mes, ano)); i++)
            cout << i << "- " << i << "\n";
        cout << "Please, enter an option: ";
        cin >> dayChosen;

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

        cout << "*" << dayName << "* " << monthName << " " << dayChosen << ", " << ano << "\n";

        listaDosMeals:
        //listing the meals from the menuTableInUse
        listarCoisas("mealID", "meal", menuTableInUse);

        //other option
        cout << "5- Other\n";

        string mealChosen;
        cout << "Please, enter an option: ";
        cin >> mealChosen;

        if (mealChosen == "1" || mealChosen == "2" || mealChosen == "3" || mealChosen == "4") {
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
                cout << "* Name of dish: ";
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

                if (optionFinalmente == "1")
                    goto listaDosMeals;
                else if(optionFinalmente == "2")
                    goto listaDosDias;
                else if (optionFinalmente == "3")
                    goto listaDosMealType;
                //else if (optionFinalmente == "4") THIS IS IN management()
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

                if (optionFinalmente == "0") //IMPORTANT: e a DateTime ainda nao passou
                    goto updateMeal;
                else if (optionFinalmente == "1")
                    goto listaDosMeals;
                else if (optionFinalmente == "2")
                    goto listaDosDias;
                else if (optionFinalmente == "3")
                    goto listaDosMealType;
                //else if (optionFinalmente == "4") THIS IS IN management()
            }
        }
        else if(mealChosen == "5") {
            otherMenuPlanManagement(); //from otherMenuPlanManagement.h

            cout << "\n";
            cout << "1- Back to meals\n";
            cout << "2- Back to days\n";
            cout << "3- Back to type of meal\n";
            cout << "4- EXIT Dining\n";
            cout << "Please, enter an option: ";
            cin >> optionFinalmente;

            if (optionFinalmente == "1")
                goto listaDosMeals;
            else if (optionFinalmente == "2")
                goto listaDosDias;
            else if (optionFinalmente == "3")
                goto listaDosMealType;
            //else if (optionFinalmente == "4") THIS IS IN management()
        }
    }
    else puts("Connection to DataBase has failed");
}