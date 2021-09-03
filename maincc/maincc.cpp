#include <iostream>
#include <iomanip>
#include <string>
#include "criar_sender.h"
#include "criarStaff.h"
#include "criar_receiver.h"
#include "send_meal.h"
#include "send_cash.h"
#include "loggedInAsStudentMenu.h"
#include "loggedInAsSchoolMenu.h"
#include "generalLogIn.h"
#include "orderFood.h"
#include "delivery.h"
#include "orderFood_payment.h"
#include "show_orders.h"
#include "management.h"
#include "cancelOrder.h"
#include "receivedOrder.h"

using namespace std;

int qstateMain;

int main() {
    //Stablishing the connection to mysql database
    MYSQL* conn;
    MYSQL_ROW row;
    MYSQL_RES* res;
    conn = mysql_init(0);

    conn = mysql_real_connect(conn, "localhost", "root", "ReinoDaMatamba3", "allstudentdata", 3306, NULL, 0);

    if (conn) {
        cout << "*** Campus Cash (CC) ***" << "\n";

        //log in as school or student menu
        generalLogIn();

        //*****log in as school*****
        if (selection == 1) {
        staffLogin:
            //criar o staff/fazer log in as a staff
            criarStaff();

        backToStaffMenu:
            cout << "*** Campus Cash (CC) ***" << "\n";
            //show menu
            schoolOptionMenu(); //from SchoolStudentOptionLoginMenu.h

            //Go to Show orders
            if (menuChoice == 1) {
                show_orders();

                cout << "\n";
                //ask if staff would like to go to menu or log out
                cout << "1- Back to main Menu\n";
                cout << "Any key- Log out\n";
                cout << "Please, enter an option: ";
                string reoption;
                cin >> reoption;
                if (reoption != "1")
                    goto staffLogin;
                else goto backToStaffMenu;
            }

            //Go to management
            else if (menuChoice == 2) {
                management(); //asks for password/PIN
                if (managementOption == 5)
                    goto backToStaffMenu;

                cout << "\n";
                //ask if staff would like to go to menu or log out
                cout << "1- Back to main Menu\n";
                cout << "Any key- Log out\n";
                cout << "Please, enter an option: ";
                string reoption;
                cin >> reoption;
                if (reoption != "1")
                    goto staffLogin;
                else goto backToStaffMenu;
            }

            //Log Out
            else if (menuChoice == 3)
                goto staffLogin;

        }

        //******log in as student******
        else if (selection == 2) {
        studentLogin:
            //criar o sender/fazer log in as a student
            criar_sender();
            //system("clear");

        backToMenu:
            //SETTING THE OTHER VARIABLES FOR SENDER/STUDENT1

            //setting name
            string theName;
            for (int i = 0; i < student1.email.size(); i++) {
                if (student1.email[i] == '.') //specific to CofI email structure (firstname.lastname@...)
                    break;
                theName += student1.email[i];
            }
            student1.name = theName;
            student1.name[0] = toupper(student1.name[0]);

            //setting ID
            string queryID = "SELECT studentID FROM studentdatatable WHERE studentEmail = '" + student1.email + "'";
            const char* qID = queryID.c_str();
            qstateSender = mysql_query(conn, qID);
            if (!qstateSender) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                student1.id = stoi(row[0]);
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

            //setting balance
            string queryBalance = "SELECT studentBalance FROM studentdatatable WHERE studentEmail = '" + student1.email + "'";
            const char* qBalance = queryBalance.c_str();
            qstateSender = mysql_query(conn, qBalance);
            if (!qstateSender) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                student1.balance = stod(row[0]);
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

            //setting mealPlanBalance
            string queryMeal = "SELECT studentMeals FROM studentdatatable WHERE studentEmail = '" + student1.email + "'";
            const char* qMeal = queryMeal.c_str();
            qstateSender = mysql_query(conn, qMeal);
            if (!qstateSender) {
                res = mysql_store_result(conn);
                row = mysql_fetch_row(res);
                student1.mealPlanBalance = stoi(row[0]);
            }
            else cout << "Query failed: " << mysql_error(conn) << "\n";

            cout << "*** Campus Cash (CC) ***" << "\n";
            cout << "** Welcome " << student1.get_name() << " **" << "\n\n";
            cout << "* Meals: " << student1.get_mealPlanBalance() << "\n";
            cout << "* Cash: $" << fixed << setprecision(2) << student1.get_balance() << "\n\n";

            //Show Menu
            menu();

            //OPTION 1- Order Food
            if (option == "1") {
                if(tableExists("feesTable")==true)
                    order_food();
                else cout << "** Fee not set yet!\n";

                cout << "\n";
                //ask if student would like to go to menu or log out
                cout << "1- Back to main Menu\n";
                cout << "Any key- Log out\n";
                cout << "Please, enter an option: ";
                string reoption;
                cin >> reoption;
                if (reoption != "1")
                    goto studentLogin;
                else goto backToMenu;
            }

            //OPTION m- Send meal
            else if (option == "m") {
                if (tableExists("feesTable") == true) {
                    //criar o receptor
                    criar_receiver();
                    //fazer envio
                    send_meal();
                    cout << "\n";
                }
                else cout << "** Fee not set yet!\n";

                //ask if student would like to go to menu or log out
                cout << "1- Back to main Menu\n";
                cout << "Any key- Log out\n";
                cout << "Please, enter an option: ";
                string reoption;
                cin >> reoption;
                if (reoption != "1")
                    goto studentLogin;
                else goto backToMenu;
            }

            //OPTION 2- Send cash
            else if (option == "2") {
                if (tableExists("feesTable") == true) {
                    //criar o receptor
                    criar_receiver();
                    //fazer envio
                    send_cash();
                    cout << "\n";
                }
                else cout << "** Fee not set yet!\n";

                //ask if student would like to go to menu or log out
                cout << "1- Back to main Menu\n";
                cout << "Any key- Log out\n";
                cout << "Please, enter an option: ";
                string reoption;
                cin >> reoption;
                if (reoption != "1")
                    goto studentLogin;
                else goto backToMenu;
            }

            //OPTION 3- Log out
            else if (option == "3")
                goto studentLogin;

            //OPTION c - cancel Order
            else if (option == "c") {
                cancelOrder();
                
                goto backToMenu;
            }

            //OPTION r - received Order
            else if (option == "r") {
                receivedOrder();
                goto backToMenu;
            }

            //OPTION o - Ok (Student understands that order was canceled)
            else if (option == "o") {
                //set canceledOrderMessage = '0'
                string querycanceledOrderMessage = "UPDATE studentdatatable SET canceledOrderMessage = '0' WHERE studentEmail = '" + student1.get_email() + "'";
                const char* qcanceledOrderMessage = querycanceledOrderMessage.c_str();
                qstateMain = mysql_query(conn, qcanceledOrderMessage);
                if (qstateMain)
                    cout << "Query failed: " << mysql_error(conn) << "\n";

                goto backToMenu;
            }
        }

        //EXIT
        else if (selection == 3)
            cout << "\n" << "Thank you!" << "\n";
    }
    else puts("Connection to DataBase has failed");

    return 0;
}