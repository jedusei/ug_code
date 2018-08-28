#include <iostream>
using namespace std;

bool isPrime(int number) {
    if (number < 2) return false;
    if (number == 2 || number == 3 || number == 5 || number == 7 || number == 13)
        return true;
        
    if (number % 2 != 0) {
        if (number % 3 != 0) {
            if (number % 5 != 0) {
                if (number % 7 != 0) {
                    if (number % 13 != 0)
                        return true;
              }
          }
      }
  }
  return false;
}

int main () {
    int num;
    cout << "Please enter an integer: ";
    cin >> num;
    if (isPrime(num))
        cout << num << " is a prime number." << endl;
    else 
         cout << num << " is not a prime number." << endl;
         
    return 0;
}
