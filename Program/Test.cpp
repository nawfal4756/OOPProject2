#include <iostream>
using namespace std;

#include "GlobalFunctions.cpp"

int main() {
    CreditCard obj;
    int res;

    obj.inputInfo();
    res = obj.add();
    if (res == 404) {
        cout << "File Error!";
    }
    else if (res == 1) {
        cout << "Credit Card Added!";
    }

    // if(dateVerification(0, 5, 2021, 'I')) {
    //     cout << "True!";
    // }
    // else {
    //     cout << "False!";
    // }
}