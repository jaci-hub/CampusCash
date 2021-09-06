#include <iostream>
#include <iomanip>
#include <string>
#include "criar_sender.h"
#include "criarStaff.h"
#include "criar_receiver.h"
#include "send_meal.h"
#include "send_cash.h"
#include "loggedInAsStudentMenu.h"
#include "loggedInAsStaffMenu.h"
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
        cout << "*** Campus Cash (CCash) ***" << "\n";

        //log in as staff or student menu
        comeco:
        generalLogIn();

        //*****log in as staff*****
        if (selection == 1) {
            //criar o staff/fazer log in as a staff
            criarStaff();

        backToStaffMenu:
            cout << "*** Campus Cash (CC) ***" << "\n";
            //show menu
            staffOptionMenu();

            //Go to Show orders
            if (menuChoice == "1") {
                show_orders();

                cout << "\n";
                //ask if staff would like to go to menu or log out
                cout << "1- Back to main Menu\n";
                cout << "Any key- Log out\n";
                cout << "Please, enter an option: ";
                string reoption;
                cin >> reoption;
                if (reoption != "1")
                    goto comeco;
                else goto backToStaffMenu;
            }

            //Go to management
            else if (menuChoice == "2") {
                management();
                if (managementOption == 7)
                    goto backToStaffMenu;

                cout << "\n";
                //ask if staff would like to go to menu or log out
                cout << "1- Back to main Menu\n";
                cout << "Any key- Log out\n";
                cout << "Please, enter an option: ";
                string reoption;
                cin >> reoption;
                if (reoption != "1")
                    goto comeco;
                else goto backToStaffMenu;
            }

            //Log Out
            else if (menuChoice == "e")
                goto comeco;
        }

        //******log in as student******
        else if (selection == 2) {
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
                //checking entregador available first
                bool entregadorAvailable = false;
                string querygetEmail = "SELECT staffEmail FROM staffDataTable WHERE staffType = 'Entregador' AND deliverTo = 'none'";
                const char* qgetEmail = querygetEmail.c_str();
                qstateMain = mysql_query(conn, qgetEmail);
                if (!qstateMain) {
                    res = mysql_store_result(conn);
                    while (row = mysql_fetch_row(res))
                        entregadorAvailable = true;
                }
                else cout << "Query failed: " << mysql_error(conn) << "\n";

                if(tableExists("feesTable")==true && entregadorAvailable == true)
                    order_food();
                else cout << "** Not taking orders currently!\n";

                cout << "\n";
                //ask if student would like to go to menu or log out
                cout << "1- Back to main Menu\n";
                cout << "Any key- Log out\n";
                cout << "Please, enter an option: ";
                string reoption;
                cin >> reoption;
                if (reoption != "1")
                    goto comeco;
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
                    goto comeco;
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
                    goto comeco;
                else goto backToMenu;
            }

            //OPTION 3- Log out
            else if (option == "e")
                goto comeco;

            //OPTION c - cancel Order
            else if (option == "c") {
                //***check if student's order wasnt canceled yet
                //get buildingOrderedFrom first
                string buildingOrderedFrom;
                string querybuildingOrderedFrom = "SELECT buildingOrderedFrom FROM studentDataTable WHERE studentEmail = '" + student1.get_email() + "'";
                const char* qbuildingOrderedFrom = querybuildingOrderedFrom.c_str();
                qstateLoggedInAsStudentMenu = mysql_query(conn, qbuildingOrderedFrom);
                if (!qstateLoggedInAsStudentMenu) {
                    res = mysql_store_result(conn);
                    row = mysql_fetch_row(res);
                    buildingOrderedFrom = row[0];
                }
                else cout << "Query failed: " << mysql_error(conn) << "\n";

                bool encomendeiFood = false;
                if (buildingOrderedFrom != "none") {
                    string queryencomendeiFood = "SELECT orderID FROM " + buildingOrderedFrom + "OrdersTable WHERE studentEmail = '" + student1.get_email() + "'";
                    const char* qencomendeiFood = queryencomendeiFood.c_str();
                    qstateLoggedInAsStudentMenu = mysql_query(conn, qencomendeiFood);
                    if (!qstateLoggedInAsStudentMenu) {
                        res = mysql_store_result(conn);
                        while (row = mysql_fetch_row(res))
                            encomendeiFood = true;
                    }
                    else cout << "Query failed: " << mysql_error(conn) << "\n";
                }

                if (encomendeiFood == true)
                    cancelOrder();
                else cout << "** Your order has already been canceled!\n";
                
                goto backToMenu;
            }

            //OPTION r - received Order
            else if (option == "r") {
                receivedOrder();

                    //***set the entregador deliverTo to 'none'
                //get the entregadorEmail first
                string entregadorEmail;
                string queryentregadorEmail = "SELECT entregadorEmail FROM studentDataTable WHERE studentEmail = '" + student1.get_email() + "'";
                const char* qentregadorEmail = queryentregadorEmail.c_str();
                qstateMain = mysql_query(conn, qentregadorEmail);
                if (!qstateMain) {
                    res = mysql_store_result(conn);
                    row = mysql_fetch_row(res);
                    entregadorEmail = row[0];
                }
                else cout << "Query failed: " << mysql_error(conn) << "\n";

                string queryUpdateentregadorDeliverTo = "UPDATE staffDataTable SET deliverTo = 'none' WHERE staffEmail = '" + entregadorEmail + "'";
                const char* qUpdateentregadorDeliverTo = queryUpdateentregadorDeliverTo.c_str();
                qstateMain = mysql_query(conn, qUpdateentregadorDeliverTo);
                if (qstateMain)
                    cout << "Query failed: " << mysql_error(conn) << "\n";

                //set entregadorEmail to 'none' in student DB
                string queryUpdateentregadorEmail = "UPDATE studentDataTable SET entregadorEmail = 'none' WHERE studentEmail = '" + student1.get_email() + "'";
                const char* qUpdateentregadorEmail = queryUpdateentregadorEmail.c_str();
                qstateMain = mysql_query(conn, qUpdateentregadorEmail);
                if (qstateMain)
                    cout << "Query failed: " << mysql_error(conn) << "\n";

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