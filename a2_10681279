#include <iostream>
#include <string>
using namespace std;

string getGrade(int score) {
    if (score < 0 || score > 100)
        return "Invalid";
        
    if (score >= 80)
        return "A";
    else if (score >= 75)
        return "B+";
    else if (score >= 70)
        return "B";
    else if (score >= 65)
        return "C+";
    else if (score >= 60)
        return "C";
    else if (score >= 55)
        return "D+";
    else if (score >= 50)
        return "D";
    else if (score >= 45)
        return "E";
    else 
        return "F";
}

int main()
{
    float score;
    cout << "Please enter your score: ";
    cin >> score;
    string grade = getGrade(score);
    if (grade != "Invalid")
        cout << "Your grade is " << grade << "." << endl;
    else
        cout << "Invalid Score!" << endl;
        
    return 0;
}
