#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

// Map letter grades to grade points
double gradeToPoint(const string &grade) {
    static const unordered_map<string,double> scale{
        {"A+",4.0},{"A",4.0},{"A-",3.67},
        {"B+",3.33},{"B",3.0},{"B-",2.67},
        {"C+",2.33},{"C",2.0},{"C-",1.67},
        {"D+",1.33},{"D",1.0},{"F",0.0}
    };
    auto it = scale.find(grade);
    return it!=scale.end() ? it->second : -1.0;
}

struct Course {
    string name;
    int credit{};
    string grade;
    double points{};
};

double semesterGPA(vector<Course>& courses) {
    double totalPoints = 0.0;
    int totalCredits = 0;
    for (auto &c : courses) {
        totalPoints += c.points * c.credit;
        totalCredits += c.credit;
    }
    return totalCredits ? totalPoints / totalCredits : 0.0;
}

int main() {
    cout << fixed << setprecision(2);
    int totalSemesters;
    cout << "Enter total number of semesters: ";
    cin >> totalSemesters;

    double cumulativeGPA = 0.0;

    for (int s = 1; s <= totalSemesters; ++s) {
        int nCourses;
        cout << "\n--- Semester " << s << " ---\n";
        cout << "Enter number of courses: ";
        cin >> nCourses;

        vector<Course> courses(nCourses);

        // Input courses
        for (int i = 0; i < nCourses; ++i) {
            cout << "\nCourse " << i+1 << " name (use - for spaces): ";
            cin >> courses[i].name;
            cout << "Credit hours: ";
            cin >> courses[i].credit;

            // Validate grade input
            while (true) {
                cout << "Grade (A+,A,A-,B+,...,F): ";
                cin >> courses[i].grade;
                double p = gradeToPoint(courses[i].grade);
                if (p >= 0) {
                    courses[i].points = p;
                    break;
                }
                cout << "Invalid grade. Try again.\n";
            }
        }

        // Semester report
        double gpa = semesterGPA(courses);
        cout << "\nSemester " << s << " Report\n";
        cout << "-------------------------------------------\n";
        cout << left << setw(15) << "Course" 
             << setw(10) << "Grade" 
             << setw(10) << "Points" << '\n';

        for (auto &c : courses) {
            cout << left << setw(15) << c.name 
                 << setw(10) << c.grade 
                 << setw(10) << c.points << '\n';
        }
        cout << "Semester GPA: " << gpa << "\n";
        cumulativeGPA += gpa;
    }

    cout << "\n===========================================\n";
    cout << "Overall CGPA: " << (totalSemesters ? cumulativeGPA/totalSemesters : 0.0) << "\n";
    cout << "===========================================\n";
    return 0;
}
