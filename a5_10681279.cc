#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

struct Student
{
    int id;
    string name;
    int age, score;
    char gender;
    string grade;
};

Student students[5];
float avgAge, avgScore;
int maleCount = 0;
int femaleCount = 0;

const string fileName = "a5_10681279.txt";

void ReceiveInput();
void StoreData();

int main()
{
    ReceiveInput();
    StoreData();
    system("pause");
    return 0;
}

string GetGrade(int score)
{
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

void ReceiveInput()
{
    cout << "Please enter the student details below:\n"
         << endl;
    for (int i = 0; i < 5; i++)
    {
        Student s;

        cout << "Student " << i + 1 << ":" << endl;
        cout << "ID: ";
        cin >> s.id;
        cout << "Name: ";
        cin >> s.name;
        cout << "Age: ";
        cin >> s.age;
        cout << "Gender (M/F): ";
        cin >> s.gender;
        cout << "Score: ";
        cin >> s.score;
        cout << endl;

        s.grade = GetGrade(s.score);
        students[i] = s;

        avgAge += s.age;
        avgScore += s.score;

        if (s.gender == 'M' || s.gender == 'm')
            maleCount++;
        else if (s.gender == 'F' || s.gender == 'f')
            femaleCount++;
    }

    avgAge /= 5.0;
    avgScore /= 5.0;
}

void StoreData()
{
    ofstream file;
    file.open(fileName, fstream::out);
    file << "ID\t\t\tName\t\tAge\t\tGender\t\tScore\t\tGrade" << endl;
    file << "*************************************************" << endl;

    for (int i = 0; i < 5; i++)
    {
        Student s = students[i];
        file << setfill('0') << setw(8) << s.id << "\t";
        file << s.name << "\t" << s.age << "\t";
        file << s.gender << "\t" << s.score << "\t";
        file << s.grade << endl;
    }

    file << "*************************************************" << endl
         << endl;
    file << "Average Age: " << avgAge << endl;
    file << "Average Score: " << avgScore << endl;
    file << "Male Count: " << maleCount << endl;
    file << "Female Count: " << femaleCount << endl;
    file.close();

    cout << "Data saved in: " << fileName << endl;
}
