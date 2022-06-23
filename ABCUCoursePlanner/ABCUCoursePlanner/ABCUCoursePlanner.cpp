//============================================================================
// Name        : ABCUCoursePlanner.cpp
// Author      : Zachary Wright
// Version     : 1.0
// Description : Project Two
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

// structure to hold course information
struct Courses {
    string courseNumber;
    string courseName;
    string prerequisites;
};

// print the course information of given courses
void printCourse(Courses course) {

    cout << course.courseNumber << ", " << course.courseName << endl;
    cout << "Prerequisites: " << course.prerequisites << endl;
}

// print course information of all the courses
void printCourseList(vector<Courses> course) {

    for (int i = 0; i < course.size() - 1; i++) {
        for (int j = 0; j < course.size() - i - j; j++) {
            if (course[j].courseNumber > course[j + 1].courseNumber) {
                swap(course[j + 1], course[j]);
            }
        }
    }
    for (int i = 0; i < course.size(); i++) {
        printCourse(course[i]);
    }
}
// search courses for the user input
void searchCourse(vector<Courses> course) {

    // user input variable
    string courseNumber;
    
    cout << "What course do you want to know about?";
    cin >> courseNumber;

    // if a course is found from user input 
    // then it will print the information for that course
    for (int i = 0; i < course.size(); i++) {
        if (course[i].courseNumber == courseNumber) {
            printCourse(course[i]);
            break;
        }
    }
}

// load CSV file contining courses to a container
vector<Courses> loadCourses(string csvPath) {
    cout << "Loading CSV File " << csvPath << endl;

    // define vector data structure to hold collection of courses
    vector<Courses> courses;

    // initialize CSV parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of courses
            Courses courseData;
            courseData.courseNumber = file[i][0];
            courseData.courseName = file[i][1];
            courseData.prerequisites = file[i][2];

            // push this course to the end
            courses.push_back(courseData);
        }
    }
    // error catch
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
    return courses;
}


//main method
int main(int argc, char** argv) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "ABCUCourses.csv";
    }

    Courses course;

    // define vector to hold all courses
    vector<Courses> courses(7);

    // define choice variable for user choise in menu
    int choice = 0;

    //define courseChoice variable to see about specific courses
    string courseChoice = "";

    // welcome message
    cout << "Welcome to the course planner!" << endl;

    // Printing menu
    while (choice != 9) {

        cout << "1. Load Data Structure" << endl;
        cout << "2. Print Course List" << endl;
        cout << "3. Print Course" << endl;
        cout << "9. Exit" << endl;
        cout << "" << endl;
        cout << "What would you like to do? ";

        // user puts their choice
        cin >> choice;

        //switch case for menu options
        switch (choice) {

        // menu option 1
        case 1:

            // load courses into data structure from csv file
            courses = loadCourses(csvPath);
            cout << courses.size() << " courses read" << endl;

            break;

        // menu option 2
        case 2:

            cout << "Here is a sample schedule: " << endl;
            cout << "" << endl;

            printCourseList(courses);
            cout << endl;

            break;

        // menu option 3
        case 3:
            
            searchCourse(courses);
            break;

        // default for menu prevents the user from inputing wrong option numbers
        default:

            if ((choice != 1) && (choice != 2) && (choice != 3) && (choice != 9)) {
                cout << choice << " is not a valid option" << endl;
            }
            
            break;
        }
    }

    // goodbye message
     cout << "Thank you for using the course planner!" << endl;;
}