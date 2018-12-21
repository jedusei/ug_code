#include <iostream>
#include <iomanip>
#include <string.h>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;

// Buffer to store the string representation of a course, student or staff
char stringBuffer[100];

// Represents a course
struct Course
{
    string code;  // Course code
    string title; // Course title
    int credits;  // Number of credit hours

    // Returns "Code - Title"
    char *ToString()
    {
        int n = sprintf(stringBuffer, "%s - %s", code.c_str(), title.c_str());
        stringBuffer[n] = 0;
        return stringBuffer;
    }
};

// Contains data and methods pertaining to a student
struct Student
{
    int ID;
    string name;
    int age;
    bool isMale;
    int level;

    // The list of courses the student has registered for.
    // This is actually a set of indices of the respective courses
    // in the global list of courses.
    // So if a course is removed from the global list
    // then this list is invalidated and has to be cleared.
    vector<int> courses;
    vector<string> grades;

    // Register a course for this student
    void AddCourse(int courseID)
    {
        if (find(courses.begin(), courses.end(), courseID) == courses.end())
        {
            courses.push_back(courseID);
            grades.push_back("N/A");
        }
    }

    // Unregister a course for this student
    void RemoveCourse(int courseID)
    {
        auto i = find(courses.begin(), courses.end(), courseID);
        if (i != courses.end())
        {
            grades.erase(grades.begin() + (i - courses.begin()));
            courses.erase(i);
        }
    }

    // Returns "ID - Name"
    char *ToString()
    {
        int n = sprintf(stringBuffer, "%i - %s", ID, name.c_str());
        stringBuffer[n] = 0;
        return stringBuffer;
    }
};

// Contains data and methods pertaining to a staff member
struct Staff
{
    int ID;
    string name;
    int age;
    bool isMale;
    string jobTitle;

    // Returns "ID - Name"
    char *ToString()
    {
        int n = sprintf(stringBuffer, "%i - %s", ID, name.c_str());
        stringBuffer[n] = 0;
        return stringBuffer;
    }
};

#define delay Sleep(1500) // Just a little delay between menus so that everything doesn't appear too fast ;)

vector<Student> students; // List of registered students
vector<Staff> staff;      // List of staff
vector<Course> courses;   // List of courses

// Forward declarations...
void MainMenu();
void CourseMenu();
void StudentMenu();
void StaffMenu();

/*
	Prints
		*********
		 HEADING
		*********
*/
void PrintHeading(string heading)
{
    string line(heading.length() + 2, '*');
    cout << line << "\n " << heading << endl;
    cout << line << "\n\n";
}

// Asks the user to enter a number
void askForNum(int &num, string prompt, string errorPrompt = "Invalid entry!")
{
    while (true)
    { // Repeat until a valid number is entered
        string s;
        cout << prompt;
        getline(cin, s);
        try
        {
            num = stoi(s);
            break;
        }
        catch (...)
        {
            cout << errorPrompt << endl;
        }
    }
}

// Asks the user to enter a number between min and max
int GetCommand(int min, int max)
{
    int command;
    while (true)
    {
        askForNum(command, "Enter command: ", "Invalid Command!");
        if (command >= min && command <= max)
            break;
        else
            cout << "Invalid command!\n";
    }
    cout << endl;
    return command;
}

// Asks the user for confirmation
bool ConfirmAction(string prompt)
{
    string s;
    cout << prompt << " (Y/N): ";
    getline(cin, s);
    return (s == "y" || s == "Y");
}

// The Main Menu
int main()
{
    while (true)
    {
        // Display heading and available commands
        PrintHeading("SCHOOL MANAGEMENT SYSTEM");
        cout << "Commands:\n";
        cout << "\t1 - Course Menu\n";
        cout << "\t2 - Student Menu\n";
        cout << "\t3 - Staff Menu\n";
        cout << "\t0 - Exit\n\n";

        int cmd = GetCommand(0, 3);
        delay;
        switch (cmd)
        {
        case 1:
            CourseMenu();
            break;
        case 2:
            StudentMenu();
            break;
        case 3:
            StaffMenu();
            break;
        default: // Exit
            if (ConfirmAction("Are you sure you want to quit?"))
                return 0;
            else
                cout << endl;
        }

        delay;
    }
}

// Find the courseIndex of a course based on its code
int FindCourse(string code)
{
    for (int i = 0; i < (int)courses.size(); i++)
    {
        if (strcmpi(courses[i].code.c_str(), code.c_str()) == 0)
        {
            return i;
        }
    }
    return -1;
}

// Ask the user to enter a course code and returns true if it is valid
bool AskForCourseCode(Course *c, int *index = nullptr)
{
    string code;
    cout << "Course Code: ";
    getline(cin, code);
    int i = FindCourse(code);
    if (index != nullptr)
        *index = i;
    if (i == -1)
    {
        cout << "Course not found.\n";
        return false;
    }
    *c = courses[i];
    return true;
}
void CourseMenu()
{
    while (true)
    {
        PrintHeading("COURSE MENU");
        cout << "Commands:\n";
        cout << "\t1 - Add New Course\n";
        cout << "\t2 - Edit Course\n";
        cout << "\t3 - Delete Course\n";
        cout << "\t0 - Go Back\n\n";

        Course c;
        int index;
        int cmd = GetCommand(0, 3);
        switch (cmd)
        {
        case 1: // Add New Course
            cout << "Course Code: ";
            getline(cin, c.code);
            cout << "Course Title: ";
            getline(cin, c.title);
            askForNum(c.credits, "Number of credit hours: ");

            if (ConfirmAction("Add Course?"))
            { // Ask for confirmation
                courses.push_back(c);
                printf("Course '%s' succesfully added.\n", c.ToString());
            }
            break;

        case 2: // Edit Course
            if (AskForCourseCode(&c, &index)) // If the user entered a valid course code...
            {
                bool changed = false;
                printf("Editing '%s':\n", c.ToString());
                cout << "Press enter to skip editing a field.\n";
                string s;
                cout << "Course Code: ";
                getline(cin, s);
                if (s.length())
                { // That is, if the user entered something before pressing enter...
                    changed = true;
                    c.code = s;
                }
                cout << "Course Title: ";
                getline(cin, s);
                if (s.length())
                {
                    changed = true;
                    c.title = s;
                }
                cout << "Number of credit hours: ";
                getline(cin, s);
                if (s.length())
                {
                    try
                    {
                        c.credits = stoi(s);
                        changed = true;
                    }
                    catch (...)
                    {
                    } // Invalid number entered...do nothing.
                }
                if (changed)
                {
                    if (ConfirmAction("Apply Changes?"))
                    {
                        courses[index] = c;
                        cout << "Course edited successfully.\n";
                    }
                }
                else
                    cout << "No changes have been made.\n";
            }
            break;

        case 3: // Delete course
            if (AskForCourseCode(&c, &index))
            {
                cout << "WARNING: If you delete a course you will have to re-register the courses of all students!\n";
                printf("Are you sure you want to delete '%s'?", c.ToString());
                if (ConfirmAction(""))
                {
                    courses.erase(courses.begin() + index);
                    // Unregister the courses of all students
                    // Go to line 39 for the reason
                    for (int i = 0; i < (int)students.size(); i++)
                    {
                        students[i].courses.clear();
                    }
                    cout << "Course deleted.\n";
                }
            }
            break;

        default: // Go Back
            return;
        }

        cout << endl;
        delay;
    }
}

// Prompts the user to enter a student ID number
// Returns true if the ID is valid
bool AskForStudentID(Student *s, int *index = nullptr)
{
    int id;
    askForNum(id, "Student ID: ");
    for (int i = 0; i < (int)students.size(); i++)
    {
        if (students[i].ID == id)
        {
            *s = students[i];
            if (index != nullptr)
                *index = i;

            return true;
        }
    }
    cout << "Student not found.\n";
    if (index != nullptr)
        *index = -1;

    return false;
}

// Calculates the grade for a score
string getGrade(int score)
{
    if (score >= 80)
        return "A";
    if (score >= 75)
        return "B+";
    if (score >= 70)
        return "B";
    if (score >= 65)
        return "C+";
    if (score >= 60)
        return "C";
    if (score >= 55)
        return "D+";
    if (score >= 50)
        return "D";
    if (score >= 45)
        return "E";

    return "F";
}
void StudentMenu()
{
    while (true)
    { // Keep looping until the user enters 0 to go back
        PrintHeading("STUDENT MENU");
        cout << "Commands:\n";
        cout << "\t1 - Register New Student\n";
        cout << "\t2 - Edit Student Details\n";
        cout << "\t3 - Add Courses\n";
        cout << "\t4 - Remove Courses\n";
        cout << "\t5 - Record Grades\n";
        cout << "\t6 - View Academic Record\n";
        cout << "\t7 - Unregister Student\n";
        cout << "\t0 - Go Back\n\n";

        Student s;
        int index;
        int cmd = GetCommand(0, 7);
        switch (cmd)
        {
        case 1: // Register new student
        {
            askForNum(s.ID, "Student ID: ");
            cout << "Name: ";
            getline(cin, s.name);
            askForNum(s.age, "Age: ");
            cout << "Gender (M/F): ";
            string str;
            getline(cin, str);
            s.isMale = (str == "M" || str == "m");
            askForNum(s.level, "Level: ");

            if (ConfirmAction("Register Student?"))
            {
                students.push_back(s);
                printf("Student '%s' successfully registered.\n", s.ToString());
            }
            break;
        }

        case 2: // Edit Student details
        {
            if (AskForStudentID(&s, &index)) // If the user entered a valid ID...
            {
                bool changed = false;
                printf("Editing Student '%s':\n", s.ToString());
                cout << "Press enter to skip editing a field.\n";
                string str;
                cout << "Student ID: ";
                getline(cin, str);
                if (str.length()) // If the user actually entered something..
                {
                    try
                    {
                        s.ID = stoi(str);
                        changed = true;
                    }
                    catch (...) // Invalid entry...don't do anything
                    {
                    }
                }
                cout << "Name: ";
                getline(cin, str);
                if (str.length())
                {
                    changed = true;
                    s.name = str;
                }
                cout << "Age: ";
                getline(cin, str);
                if (str.length())
                {
                    try
                    {
                        s.age = stoi(str);
                        changed = true;
                    }
                    catch (...)
                    {
                    }
                }
                cout << "Gender: ";
                getline(cin, str);
                if (str.length())
                {
                    changed = true;
                    s.isMale = (str == "M" || str == "m");
                }
                cout << "Level: ";
                getline(cin, str);
                if (str.length())
                {
                    try
                    {
                        s.level = stoi(str);
                        changed = true;
                    }
                    catch (...)
                    {
                    }
                }

                if (changed)
                {
                    if (ConfirmAction("Apply Changes?"))
                    {
                        students[index] = s;
                        cout << "Student details edited successfully.\n";
                    }
                }
                else
                    cout << "No changes have been made.\n";
            }
            break;
        }

        case 3: // Register for courses
        {
            int sIndex;
            if (AskForStudentID(&s, &sIndex))
            {
                printf("Registering courses for '%s':\n", s.ToString());
                cout << "Press enter twice to end registration.\n\n";
                cout << "Enter Courses to add (One Course Code per line):\n\n";
                vector<string> coursesToAdd;
                string str;
                // Let the user enter each of the courses line by line
                // Until the user presses enter twice (a line is found to be empty)
                while (true)
                {
                    getline(cin, str);
                    if (str.length() != 0)
                        coursesToAdd.push_back(str);
                    else
                        break;
                }
                if (coursesToAdd.size() && ConfirmAction("Add Courses?"))
                { // Ask for confirmation
                    // For each course code entered, check if it is valid
                    // If it is valid, then add it to addedCourses
                    vector<string> addedCourses; // List of successfully added courses
                    for (int i = 0; i < (int)coursesToAdd.size(); i++)
                    {
                        int index = FindCourse(coursesToAdd[i]);
                        if (index != -1)
                        {
                            s.AddCourse(index);
                            addedCourses.push_back(courses[index].ToString());
                        }
                    }
                    students[sIndex] = s; // Register the changes in the array
                    int numNotAdded = coursesToAdd.size() - addedCourses.size(); // Number of courses that could not be added
                    if (numNotAdded == 0)
                        cout << "All courses added successfully.\n";
                    else
                    { // Print the courses that were added
                        cout << numNotAdded;
                        cout << (numNotAdded > 1 ? " courses " : " course ");
                        cout << "could not be added because they haven't been registered in the system.\n";
                        cout << "Courses added:\n";
                        for (int i = 0; i < (int)addedCourses.size(); i++)
                        {
                            printf("%i. %s\n", i + 1, addedCourses[i].c_str());
                        }
                    }
                }
            }
            break;
        }

        case 4: // Cancel courses
        {
            int sIndex;
            if (AskForStudentID(&s, &sIndex))
            {
                printf("Cancelling courses for '%s':\n", s.ToString());
                cout << "Press enter twice to end cancellation.\n";
                cout << "Enter Courses to cancel (1 Course Code per line):\n";
                vector<string> coursesToCancel;
                string str;
                while (true)
                { // Enter each course code line by line
                    getline(cin, str);
                    if (str.length() != 0)
                        coursesToCancel.push_back(str);
                    else
                        break;
                }
                if (coursesToCancel.size() && ConfirmAction("Cancel Courses?"))
                {
                    for (int i = 0; i < (int)coursesToCancel.size(); i++)
                    { // Remove each of the specified courses
                        index = FindCourse(coursesToCancel[i]);
                        if (index != -1)
                        {
                            s.RemoveCourse(index);
                        }
                    }
                    students[sIndex] = s; // Apply changes
                    cout << "Courses cancelled successfully.\n";
                }
            }
            break;
        }

        case 5: // Record Grades
        {
            if (AskForStudentID(&s, &index))
            {
                int n = s.courses.size();
                if (n == 0)
                    cout << "This student has not registered for any courses.\n";
                else
                {
                    printf("Recording grades for '%s':\n", s.ToString());
                    cout << "Enter the score for each grade below:\n";
                    cout << "Press enter to skip recording for the current course.\n\n";
                    cout << "Number of courses registered: " << n << endl;
                    bool changed = false;
                    for (int i = 0; i < n; i++) // For each of the registered courses, ask the user to enter a score
                    {
                        Course c = courses[s.courses[i]];
                        printf("%s: ", c.ToString());
                        try
                        {
                            string str;
                            getline(cin, str);
                            if (str.length())
                            { // If the user actually entered something...
                                int score = stoi(str);
                                if (score < 0 || score > 100)
                                    throw 0; // Score must be within the range [0..100]
                                else
                                {
                                    s.grades[i] = getGrade(score); // Calculate grade from score given
                                    changed = true;
                                }
                            }
                        }
                        catch (...)
                        {
                            cout << "Invalid score entered!\n"
                                 << "Skipping...\n";
                        }
                    }
                    if (changed && ConfirmAction("Confirm?"))
                    {
                        students[index].grades = s.grades; // Apply changes
                    }
                }
            }
            break;
        }

        case 6: // View Academic Record
        {
            if (AskForStudentID(&s))
            {
                int n = s.courses.size();
                if (n == 0)
                    cout << "This student has not registered for any courses.\n";
                else
                {
                    cout << "Name: " << s.name << endl;

                    // Calculate the max length among all the course names so that we can
                    // Line up the table well by applying padding
                    string *courseStrs = new string[n];
                    int columnWidth = 0;
                    for (int i = 0; i < n; i++)
                    {
                        string str = courses[s.courses[i]].ToString();
                        courseStrs[i] = str;
                        if ((int)str.length() > columnWidth)
                            columnWidth = str.length();
                    }
                    cout << endl;

                    int numSpacesBefore = (columnWidth - 6) / 2;            // (ColumnWidth - len("COURSE")) / 2
                    int numSpacesAfter = columnWidth - numSpacesBefore - 6; // ColumnWidth - numSpacesBefore - len("COURSE")

                    // Display the table headings

                    // Print some spaces before and after to center the heading
                    cout << string(numSpacesBefore, ' ');
                    cout << "COURSE";
                    cout << string(numSpacesAfter, ' ');

                    // Print the other headings and the underline
                    cout << "     CREDITS    GRADE\n";
                    cout << string(columnWidth, '-') << "    ---------  -------\n";

                    // Display the table
                    for (int j = 0; j < n; j++)
                    {
                        cout << setw(columnWidth) << setiosflags(ios::left) << courseStrs[j]; // Set column width and align the names to the left
                        cout << "        " << courses[s.courses[j]].credits;
                        if (s.grades[j].size() == 3) // N/A
                            cout << "        ";
                        else
                            cout << "         ";

                        cout << s.grades[j] << endl;
                    }

                    cout << endl;
                    system("pause"); // Ask the user to "Press any key to continue..."
                }
            }
            break;
        }
        case 7: // Unregister student
        {
            if (AskForStudentID(&s, &index))
            {
                printf("Are you sure you want to unregister '%s'?", s.ToString());
                if (ConfirmAction(""))
                {
                    students.erase(students.begin() + index);
                    cout << "Student unregistered.\n";
                }
            }
            break;
        }
    
        default: // Go Back
            return;
        }

        cout << endl;
        delay;
    }
}

// Ask the user to enter a Staff ID and
// Returns true if it is valid
bool AskForStaffID(Staff *s, int *index = nullptr)
{
    int id;
    askForNum(id, "Staff ID: ");
    for (int i = 0; i < (int)staff.size(); i++)
    {
        if (staff[i].ID == id)
        {
            *s = staff[i];
            if (index != nullptr)
                *index = i;
            return true;
        }
    }
    cout << "Staff not found.\n";
    if (index != nullptr)
        *index = -1;
    return false;
}
void StaffMenu()
{
    while (true)
    {
        PrintHeading("STAFF MENU");
        cout << "Commands:\n";
        cout << "\t1 - Register New Staff\n";
        cout << "\t2 - Edit Staff Details\n";
        cout << "\t3 - Unregister Staff\n";
        cout << "\t0 - Go Back\n\n";

        Staff s;
        int index;
        int cmd = GetCommand(0, 3);
        switch (cmd)
        {
        case 1: // Register new staff
        {
            askForNum(s.ID, "Staff ID: ");
            cout << "Name: ";
            getline(cin, s.name);
            askForNum(s.age, "Age: ");
            cout << "Gender (M/F): ";
            string str;
            getline(cin, str);
            s.isMale = (str == "M" || str == "m");
            cout << "Job Title: ";
            getline(cin, s.jobTitle);

            if (ConfirmAction("Register Staff?"))
            {
                staff.push_back(s);
                printf("Staff '%s' successfully registered.\n", s.ToString());
            }
            break;
        }

        case 2: // Edit Staff details
        {
            if (AskForStaffID(&s, &index)) // If the user entered a valid ID...
            {
                bool changed = false;
                printf("Editing Staff '%s':\n", s.ToString());
                cout << "Press enter to skip editing a field.\n";
                string str;
                cout << "Staff ID: ";
                getline(cin, str);
                if (str.length() != 0)
                {
                    try
                    {
                        s.ID = stoi(str);
                        changed = true;
                    }
                    catch (...)
                    {
                    }
                }
                cout << "Name: ";
                getline(cin, str);
                if (str.length() != 0)
                {
                    changed = true;
                    s.name = str;
                }
                cout << "Age: ";
                getline(cin, str);
                if (str.length() != 0)
                {
                    changed = true;
                    try
                    {
                        s.age = stoi(str);
                        changed = true;
                    }
                    catch (...)
                    {
                    }
                }
                cout << "Gender: ";
                getline(cin, str);
                if (str.length() != 0)
                {
                    changed = true;
                    s.isMale = (str == "M" || str == "m");
                }
                cout << "Job Title: ";
                getline(cin, str);
                if (str.length() != 0)
                {
                    changed = true;
                    s.jobTitle = str;
                }

                if (changed)
                {
                    if (ConfirmAction("Apply Changes?"))
                    {
                        staff[index] = s;
                        cout << "Staff details edited successfully.\n";
                    }
                }
                else
                    cout << "No changes have been made.\n";
            }
            break;
        }

        case 3: // Unregister staff
        {
            if (AskForStaffID(&s, &index))
            {
                printf("Are you sure you want to unregister '%s'?", s.ToString());
                if (ConfirmAction(""))
                {
                    staff.erase(staff.begin() + index);
                    cout << "Staff unregistered.\n";
                }
            }
            break;
        }

        default: // Go Back
            return;
        }

        cout << endl;
        delay;
    }
}
