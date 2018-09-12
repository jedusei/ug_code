// Program that finds the Greatest Common Divisor (GCD) of two numbers
#include <iostream>
#include <cmath>
using namespace std;

int gcd(int a, int b) {
    if (a == b) return a; // Function will be called recursively until both numbers are the same
        
    int small = min(a, b);
    int big = max(a, b);
    // The GCD of two numbers is the same as the GCD of the smaller number
    // and the absolute difference between the two
    return gcd(small, big - small); 
}
    
int main()
{
    int a, b;
    
    cout << "Enter first number: ";
    cin >> a;
    cout << "Enter second number: ";
    cin >> b;
    
    cout << "The Greatest Common Divisor (GCD) of " << a << " and " << b;
    cout << " is " << gcd(a, b) << "." << endl;
    
    return 0;
}
