#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// Definition of the Course structure
struct Course {
    string courseCode;          
    string courseName;           
    vector<string> prerequisites;
};

// Function to split a string into a vector of strings using a given delimiter
vector<string> splitString(string input, string delimiter = " ") {
    vector<string> result;
    size_t start = 0;
    size_t end = input.find(delimiter);

    while (end != string::npos) {
        result.push_back(input.substr(start, end - start));
        start = end + delimiter.size();
        end = input.find(delimiter, start);
    }

    result.push_back(input.substr(start, end - start));
    return result;
}

// Function to load course data from a file and store it in a vector of Course structures
vector<Course> loadDataStructure() {
    ifstream file("courses.txt", ios::in); 
    vector<Course> courseList;             
    string line;

    // Read course data line by line until reaching the end marker
    while (true) {
        getline(file, line);
        if (line == "-1")
            break;

        Course course;
        vector<string> tokens = splitString(line, ",");

        course.courseCode = tokens[0];
        course.courseName = tokens[1];

        // Store prerequisites for the course
        for (int i = 2; i < tokens.size(); i++) {
            course.prerequisites.push_back(tokens[i]);
        }

        courseList.push_back(course); // Add the course to the vector
    }

    file.close(); // Close the file
    return courseList;
}

// Function to print information about a single course
void printCourseInfo(Course course) {
    string code = course.courseCode;
    string name = course.courseName;
    vector<string> prerequisites = course.prerequisites;

    cout << "Course Code: " << code << endl;
    cout << "Course Name: " << name << endl;
    cout << "Prerequisites: ";
    for (int i = 0; i < prerequisites.size(); i++) {
        cout << prerequisites[i] << " ";
    }
    cout << "\n\n";
}

// Function to print information about all courses in the vector
void printCourseListInfo(vector<Course> courseList) {
    int numCourses = courseList.size();

    // Bubble sort to sort the course list by course code
    for (int i = 0; i < numCourses - 1; i++) {
        for (int j = 0; j < numCourses - i - 1; j++) {
            if (courseList[j].courseCode > courseList[j + 1].courseCode) {
                swap(courseList[j], courseList[j + 1]);
            }
        }
    }

    // Print information about each course in the sorted list
    for (int i = 0; i < numCourses; i++) {
        printCourseInfo(courseList[i]);
    }
}

// Function to search for a course by its course code
void searchForCourse(vector<Course> courseList) {
    int numCourses = courseList.size();
    string courseCode;
    int found = 0;

    cout << "Enter Course Code: ";
    cin >> courseCode;

   
    for (int i = 0; i < numCourses; i++) {
        if (courseList[i].courseCode == courseCode) {
            found = 1;
            printCourseInfo(courseList[i]);
            break;
        }
    }

    // If course not found, display an error message
    if (found == 0) {
        cout << "Course with the given course code not found\n";
    }
}

// Main function
int main(int argc, char **argv) {
    vector<Course> courseList; // Vector to store course data

    // Display the menu options
    cout << "1. Load Data Structure\n";
    cout << "2. Print Course List\n";
    cout << "3. Print Course\n";
    cout << "4. Exit\n";

    int choice;

    // Main loop for processing user's choices
    do {
        cout << "\nEnter your choice: ";
        cin >> choice;

        // Switch statement to perform actions based on user's choice
        switch (choice) {
            case 1:
                courseList = loadDataStructure(); 
                break;
            case 2:
                printCourseListInfo(courseList); 
                break;
            case 3:
                searchForCourse(courseList);    
                break;
            case 4:
                cout << "Exit\n";               
                break;
            default:
                cout << "Invalid Choice\n";      
        }
    } while (choice != 4); 

    return 0;
}
