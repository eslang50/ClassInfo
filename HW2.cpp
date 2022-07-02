#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
using namespace std;

class Person
{

private:
    string fullname; // variables for Person
    string address;
    int age;

public:
    void readPersonInfo(ifstream *pf)
    {
        string temp; // reads person's info from file
        getline(*pf, fullname);
        getline(*pf, address);
        getline(*pf, temp);
        age = stoi(temp);
    }

    void printPersonInfo()
    {

        // prints specific info on Person
        cout.width(20);
        cout << left << fullname;
        cout.width(20);
        cout << left << address;
        cout.width(10);
        cout << left << age;
    }

    int personAge()
    { // returns the age of the Person
        return age;
    }

    string personName()
    { // returns the full name of the Person
        return fullname;
    }
};

class Student : public Person
{

private:
    string ID; // variables for Student
    string major;
    float gpa;

public:
    void readStudentInfo(ifstream *sf)
    {
        string temp;
        readPersonInfo(sf); // reads info from file given
        getline(*sf, ID);
        getline(*sf, major);
        getline(*sf, temp);
        gpa = stof(temp);
    }

    void printStudentInfo()
    {
        cout.width(20); // prints a specific Student's info
        cout << left << ID;
        cout.width(10);
        cout << left << major;
        cout.width(10);
        cout << left << gpa << endl;
    }

    float studentGPA()
    { // returns the gpa of the Student
        return gpa;
    }
};

// to represent a course with its ID, title, and credits
class Course
{
private:
    string ID;
    string title;
    int credits;

public:
    Course(std::string ID, std::string title, int credits) // class constructor with appropriate parameters
    {
        this->ID = ID;
        this->title = title;
        this->credits = credits;
    }

    void printCourseInfo() // prints info on Course
    {
        cout << "Course ID: " << ID << "\nCourse Title: " << title << "\nCourse Credits: " << credits << endl;
        cout << "\n";
        cout.width(8);
        cout << left << "Seq";
        cout.width(20);
        cout << left << "Full Name:";
        cout.width(20);
        cout << left << "Address:";
        cout.width(10);
        cout << left << "Age:";
        cout.width(20);
        cout << left << "ID:";
        cout.width(10);
        cout << left << "Major:";
        cout.width(10);
        cout << left << "GPA:" << endl;
    }
};

class CourseSection : public Course
{ // CourseSection class that inherits the Course class
private:
    int sectionSize;
    Student *roster; // pointer object for class Student
    Student **sortedNames;
    Student **sortedAges;
    Student **sortedGPAs;

    void sortNames();
    void sortAges();
    void sortGPAs();

public:
    CourseSection(string ID, string title, int credits, int sectionSize) : Course(ID, title, credits) // constructor with appropriate paramters
    {
        this->sectionSize = sectionSize;
        roster = new Student[sectionSize];
        sortedNames = new Student *[sectionSize];
        sortedAges = new Student *[sectionSize];
        sortedGPAs = new Student *[sectionSize];
    }

    void fillRosterInfo(ifstream *rf)
    { // reads info of all Students in the section one at a time and then fills the roster

        for (int i = 0; i < sectionSize; i++)
        {
            roster[i].readStudentInfo(rf);
            sortedNames[i] = &roster[i];
            sortedAges[i] = &roster[i];
            sortedGPAs[i] = &roster[i];
        }
    }

    void printSectionInfo()
    { // prints course info, followed by specific students iZ
        Course::printCourseInfo();
        for (int i = 0; i < sectionSize; i++)
        {
            cout.width(8);
            cout << i + 1;
            roster[i].printPersonInfo();
            roster[i].printStudentInfo();
        }
    }

    void printSectionInfoByName()
    { // sorts by names and prints info accordingly
        int i, j;
        Student key;
        for (i = 1; i < sectionSize; i++)
        {
            key = *sortedNames[i];
            j = i - 1;

            while (j >= 0 && sortedNames[j][0].personName() > key.personName())
            {
                sortedNames[j + 1][0] = sortedNames[j][0];
                j = j - 1;
            }
            sortedNames[j + 1][0] = key;
        }

        printSectionInfo();
        cout << "\n";
    }

    void printSectionInfoByAge()
    { // sorts by ages and prints info accordingly
        int i, j;
        Student key;
        for (i = 1; i < sectionSize; i++)
        {
            key = roster[i];
            j = i - 1;

            while (j >= 0 && roster[j].personAge() > key.personAge())
            {
                sortedNames[j + 1][0] = sortedNames[j][0];
                j = j - 1;
            }
            sortedNames[j + 1][0] = key;
        }

        printSectionInfo();
        cout << "\n";
    }

    void printSectionInfoByGPA()
    { // sorts by GPAs and prints info accordingly
        int i, j;
        Student key;
        for (i = 1; i < sectionSize; i++)
        {
            key = roster[i];
            j = i - 1;

            while (j >= 0 && roster[j].studentGPA() < key.studentGPA())
            {
                sortedNames[j + 1][0] = sortedNames[j][0];
                j = j - 1;
            }
            sortedNames[j + 1][0] = key;
        }

        printSectionInfo();
        cout << "\n";
    }

    ~CourseSection()
    {
        delete[] roster;
    }
};

int main()
{
    int num, cr;
    string id, tl;
    ifstream inf;
    inf.open("C:\\Users\\18572\\Downloads\\section01.txt"); // replace with the exact location where your file is stored
    if (inf.fail())
    { // to avoid terminating your program without displaying a message
        cerr << "Error: Could not open input file\n";
        exit(1);
    }
    // activate the exception handling of inf stream
    inf.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    cout << "Course ID? ";
    cin >> id;
    cin.get(); // remove the leftover "new line" character from cin
    cout << "Course Title? ";
    getline(cin, tl);
    cout << "Course Credits? ";
    cin >> cr;
    cin.get(); // remove the leftover "new line" character from cin
    cout << "How many students in the course section? ";
    cin >> num;
    cin.get();                          // remove the leftover "new line" character from cin
    CourseSection sec(id, tl, cr, num); // define sec for CourseSection
    sec.fillRosterInfo(&inf);           // ifstream cannot be passed by value
    inf.close();

    cout << "Section info (course and students info) sorted by students' names:\n";
    sec.printSectionInfoByName();

    cout << "\nSection info (course and students info) sorted by students' ages:\n";
    sec.printSectionInfoByAge();

    cout << "\nSection info (course and students info) sorted by students' GPAs:\n";
    sec.printSectionInfoByGPA();

    return 0;
}