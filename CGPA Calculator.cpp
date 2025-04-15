//============================================================================
// Name        : CGPA.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdio>
using namespace std;

void allocateVar(string*& p,float*& point,string*& sub_name,int*& credits,int n) {
	p = new string[n];
	point = new float[n];
	sub_name = new string[n];
	credits = new int[n]; // 3 EXTRA for IN-CASE

}

void inputs(string* subname,int* credit,string* ptr ,int n) {
	                     // COURSES ENTRY
	cout << "~~~Please Enter your Courses Name~~~"<< endl << "Use '-' instead of Space" << endl;
	for(int i=0;i<n;i++) {
		cout << "Course " << i+1 << " : ";
		cin >> subname[i];
		cout << endl;
	}

	                     //CREDIT Hrs. ENTRY

	cout << "~~~Great. Now, enter your Credits Hrs in your respective Courses~~~" << endl;
	for(int i=0;i<n;i++) {
		cout << "Number of Credit Hrs of " << subname[i] << " : ";
		cin >> credit[i];
	}

	                    //GRADES ENTRY

	cout << "~~~Enter your Grade in Course (e.g. A+,A,A-,...,D+,D and F~~~" << endl;

	for(int i=0;i<n;i++) {
		cout << "Enter your Grade in " << subname[i] << " : ";
		cin >> ptr[i];
		if(ptr[i] == "A+" || ptr[i] == "A" || ptr[i] == "A-" || ptr[i] == "B+" || ptr[i] == "B-" || ptr[i] == "B" || ptr[i] == "C+" || ptr[i] == "C-" || ptr[i] == "C" || ptr[i] == "D+" || ptr[i] == "D" || ptr[i] == "F" ){

		}
		else {
			cout << endl << "!!! Grade, you entered, is not True. Enter Again !!!" << endl;
			i--;

		}
	}

}


void assignPoints(string* ptr,float* points ,int n) {
	for(int i=0;i<n;i++) {
		if(ptr[i] == "A" || ptr[i] == "A+")
			points[i] = 4.00;
		else if(ptr[i] == "A-")
			points[i] = 3.67;
		else if(ptr[i] == "B+")
			points[i] = 3.33;
		else if(ptr[i] == "B")
			points[i] = 3.00;
		else if(ptr[i] == "B-")
			points[i] = 2.67;
		else if(ptr[i] == "C+")
			points[i] = 2.33;
		else if(ptr[i] == "C")
			points[i] = 2.00;
		else if(ptr[i] == "C-")
			points[i] = 1.67;
		else if(ptr[i] == "D+")
			points[i] = 1.33;
		else if(ptr[i] == "D")
			points[i] = 1.00;
		else if(ptr[i] == "F")
			points[i] = 0.00;

	}

}


void calculations(float* points,int* credit,float& sum,int& tcredit,int n) {
	for(int i=0;i<n;i++) {
		sum += points[i] * credit[i];
		tcredit += credit[i];
	}
}

void outputs(string* subname,float* points,string* ptr,float sum,int tcredit,long double& gpa,int n)  {
	for(int i=0;i<n;i++) {
		cout << i+1 << ".  " << subname[i] << " \t " << ptr[i];
		printf("\t %.2f",points[i]);
		cout << endl;
	}
	cout << endl << endl << endl << "~~~~~\t\t\t    SEMESTER REPORT   \t\t\t~~~~~" << endl;
	gpa = sum/tcredit;
	printf("\nGPA  :  %.2Lf",gpa);

}

void deallocate( string* ptr,float*	points,string* subname,int* credit) {
	delete[] points;
	delete[] subname;
	delete[] ptr;
	delete[] credit;

}

int main() {

	int n,tcredit,snum;
	float sum=0,count=0;
	long double gpa=0,cgpa=0;
	string* ptr;
    float*	points;
    string* subname;
    int* credit;
    cout << "Enter your Total Semesters : ";
    cin >> snum;

	for(int i=0;i<snum;i++) {

	gpa=0;
	count++;
	cout << "Enter your number of Courses for Semester " << i+1 << " : ";
	cin >> n;
	allocateVar(ptr,points,subname,credit,n);
	inputs(subname,credit,ptr,n);
	assignPoints(ptr,points,n);
	calculations(points,credit,sum,tcredit,n);
	outputs(subname,points,ptr,sum,tcredit,gpa,n);
	cgpa+=gpa;
	deallocate(ptr,points,subname,credit);
	cout << endl;

	}

    cout  << endl << endl << "~~~~~\t\t\tOVERALL SEMESTERS REPORT\t\t\t~~~~~";
    printf("\nCGPA : %.2Lf",cgpa/count);
	return 0;
}
