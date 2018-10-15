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

void ReceiveInput()
{
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
        cout << "Gender: ";
        cin >> s.gender;
        cout << "Score: ";
        cin >> s.score;
        cout << "Grade: ";
        cin >> s.grade;
        cout << endl;

        students[i] = s;

        avgAge += s.age;
        avgScore += s.score;

        if (s.gender == 'M' || s.gender == 'm')
            maleCount++;
        else
            femaleCount++;
    }

    avgAge /= 5.0;
    avgScore /= 5.0;
}

void StoreData()
{
    ofstream file;
    file.open(fileName, fstream::out);
    file << "ID\t\tName\t\tAge\t\tGender\t\tScore\t\tGrade" << endl;
    file << "*********************************************" << endl;

    for (int i = 0; i < 5; i++)
    {
        Student s = students[i];
        file << setfill('0') << setw(8) << s.id << "  ";
        file << s.name << "  " << s.age << " ";
        file << s.gender << "  " << s.score << " ";
        file << s.grade << endl;
    }

    file << endl;
    file << "Average Age: " << avgAge << endl;
    file << "Average Score: " << avgScore << endl;
    file << "Male Count: " << maleCount << endl;
    file << "Female Count: " << femaleCount << endl;
    file.close();

    cout << "Data saved in: " << fileName << endl;
}
