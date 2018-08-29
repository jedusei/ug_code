// Prime Number Checker
// By Joseph Edusei
#include <iostream>
#include <cmath>

using namespace std;

bool isPrime(int number) {
    if (number < 2) // All integers below 2 are non-prime
        return false;

    // Check every number from 2 to the square root of the number and see if any divides the number without a remainder
    int root = (int)sqrt(number);
    for (int i = 2; i <= root; i++) { 
        if (number % i == 0)
            return false;
    }
    
    return true;
}

int main () {
    int num;
    cout << "Please enter an integer: ";
    cin >> num;
    if (isPrime(num)) // Number is prime
        cout << num << " is a prime number." << endl;
    else 
        cout << num << " is not a prime number." << endl;
         
    return 0;
}
