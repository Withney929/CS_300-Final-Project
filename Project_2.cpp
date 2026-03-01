//============================================================================
// Name        : Project 2.cpp
// Author      : Withney Villarreal
// Description : 7-1 Project 2 
//============================================================================


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// ===============================
// Course Structure
// ===============================
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// ===============================
// BST Node Structure
// ===============================
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) {
        course = c;
        left = nullptr;
        right = nullptr;
    }
};

// ===============================
// Binary Search Tree Class
// ===============================
class BinarySearchTree {
private:
    Node* root;

    // Insert helper
    Node* addNode(Node* node, Course course) {
        if (node == nullptr) {
            return new Node(course);
        }

        if (course.courseNumber < node->course.courseNumber) {
            node->left = addNode(node->left, course);
        }
        else {
            node->right = addNode(node->right, course);
        }

        return node;
    }

    // Search helper
    Node* search(Node* node, string courseNumber) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->course.courseNumber == courseNumber) {
            return node;
        }

        if (courseNumber < node->course.courseNumber) {
            return search(node->left, courseNumber);
        }

        return search(node->right, courseNumber);
    }

    // In-order traversal helper
    void inOrder(Node* node) {
        if (node == nullptr) return;

        inOrder(node->left);
        cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;
        inOrder(node->right);
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    void Insert(Course course) {
        root = addNode(root, course);
    }

    Node* Search(string courseNumber) {
        return search(root, courseNumber);
    }

    void PrintInOrder() {
        inOrder(root);
    }

    bool IsEmpty() {
        return root == nullptr;
    }
};

// ===============================
// Helper: Convert to uppercase
// ===============================
string ToUpper(string s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

// ===============================
// Load Courses From File
// ===============================
void LoadCourses(string filename, BinarySearchTree& bst) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;

    while (getline(file, line)) {
        if (line.empty()) continue; // Skip empty lines
        stringstream ss(line);
        string number, title, prereq;
        vector<string> prereqs;

        getline(ss, number, ',');
        getline(ss, title, ',');

        while (getline(ss, prereq, ',')) {
            if (!prereq.empty()) {
                prereqs.push_back(prereq);
            }
        }

        Course course;
        course.courseNumber = number;
        course.courseTitle = title;
        course.prerequisites = prereqs;

        bst.Insert(course);
    }

    file.close();
}

// ===============================
// Print Course Information
// ===============================
void PrintCourseInfo(BinarySearchTree& bst, string courseNumber) {
    courseNumber = ToUpper(courseNumber);
    Node* result = bst.Search(courseNumber);

    if (result == nullptr) {
        cout << "Course not found." << endl;
        return;
    }

    cout << result->course.courseNumber << ", " << result->course.courseTitle << endl;

    if (result->course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
    }
    else {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < result->course.prerequisites.size(); i++) {
            cout << result->course.prerequisites[i];
            if (i < result->course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

// ===============================
// Main Program
// ===============================
int main() {
    BinarySearchTree bst;
    int choice = 0;
    string filename;
    string courseNumber;

    cout << "Welcome to the course planner." << endl << endl;

    while (choice != 9) {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl << endl;

        cout << "What would you like to do? ";
        cin >> choice;

        cout << endl;

        if (choice == 1) {
            cout << "Enter the file name: ";
            cin >> filename;
            LoadCourses(filename, bst);
            cout << endl;
        }
        else if (choice == 2) {
            if (bst.IsEmpty()) {
                cout << "No data loaded." << endl << endl;
            }
            else {
                cout << "Here is a sample schedule:" << endl << endl;
                bst.PrintInOrder();
                cout << endl;
            }
        }
        else if (choice == 3) {
            if (bst.IsEmpty()) {
                cout << "No data loaded." << endl << endl;
            }
            else {
                cout << "What course do you want to know about? ";
                cin >> courseNumber;
                cout << endl;
                PrintCourseInfo(bst, courseNumber);
                cout << endl;
            }
        }
        else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
        }
        else {
            cout << choice << " is not a valid option." << endl << endl;
        }
    }

    return 0;
}