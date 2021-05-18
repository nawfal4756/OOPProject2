#include <iostream>
using namespace std;

#include "GlobalFunctions.cpp"

int main() {
    int res, userOption;
    char userCharOption;

    while (1) {
        cout << "Enter 1 to go to customer console" << endl;
        cout << "Enter 2 to go to employee console" << endl;
        cout << "Enter 3 to exit" << endl;
        cout << "Enter desired option: ";
        cin >> userOption;
        fflush(stdin);

        if (userOption == 1) {
            res = customerInterface();
        }
        else if (userOption == 2) {

        }
        else if (userOption == 3) {
            cout << "Do you want to exit? (Yes or No)" << endl;
            cout << "Enter desired option: ";
            cin >> userCharOption;
            fflush(stdin);

            if (userCharOption == 'Y' || userCharOption == 'y') {
                return 1;
            }
            else if (userCharOption == 'N' || userCharOption == 'n') {

            }
            else {
                cout << "Incorrect option entered!" << endl;
                cout << "Press enter to continue...";
                getchar();
            }
        }
        system("cls");
    }
    
}