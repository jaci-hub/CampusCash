#include <iostream>
#include <iomanip>
#include <string>
#include "criar_sender.h"
#include "criarStaff.h"
#include "criar_receiver.h"
#include "send_cash.h"
#include "loggedInAsStudentMenu.h"
#include "loggedInAsSchoolMenu.h"
#include "generalLogIn.h"
#include "criar_orderFood.h"
#include "delivery.h"
#include "orderFood_payment.h"
#include "show_orders_byFoodBuilding.h"
#include "cashTransactionRecord.h"
#include "management.h"

using namespace std;

int main() {
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
            show_orders_byFoodBuilding();

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

        //Go to Cash Transaction Record
        else if (menuChoice == 2) { //asks for password/PIN
            string cashTransRecoPin;
            cout << "PIN: ";
            cin >> cashTransRecoPin;
            if (cashTransRecoPin == "0123") {
                cout << "*** Campus Cash (CC) ***" << "\n";
                cout << "* Recent Transactions *" << "\n";
                cashTransactionRecord();

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
        }

        //Go to management
        else if (menuChoice == 3) {
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
        else if (menuChoice == 4)
            goto staffLogin;

    }

    //******log in as student******
    else if (selection == 2) {
        studentLogin:
        //criar o sender/fazer log in as a student
        criar_sender();
        //system("clear");

        backToMenu:
        cout << "*** Campus Cash (CC) ***" << "\n";
        cout << "** Welcome " << student1.get_name() << " **" << "\n";
        cout << "\n";
        cout << "* Meals Balance: " << student1.get_mealPlanBalance() << "\n";
        cout << "* Coyote Cash : $" << fixed << setprecision(2) << student1.get_balance() << "\n\n";
        
        //Show Menu
        menu();

        //OPTION 1- Order Food
        if (option == 1) {
            order_food();
            delivery();
            orderFood_payment();
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

        //OPTION 2- Send cash
        else if (option == 2) {
            //criar o receptor
            criar_receiver();
            //fazer envio
            send_cash();
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

        //OPTION 3- Log out
        else if (option == 3)
            goto studentLogin;
    }

    //EXIT
    else if (selection == 3)
        cout << "\n" << "Thank you!" << "\n";

    return 0;
}