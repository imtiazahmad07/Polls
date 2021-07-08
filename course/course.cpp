#include <iostream>
#include <iomanip> // for setw and setprecision
#include <fstream> // for file input/output
using namespace std;

// print() function to print details of averages both groups for the same course
void print(string courseName, double courseAvgGrp1, double courseAvgGrp2)
{
    cout << fixed << setprecision(2);
    cout << left << setw(13) << courseName << setw(13) << "1" << courseAvgGrp1 << "\n";
    cout << left << setw(13) << " " << setw(13) << "2" << courseAvgGrp2 << "\n\n";
}
// function to calculate the average of each course and then average of each group.
// This function also calls the print() function for each group
void calculateAverage(ifstream &f1, ifstream &f2)
{
    // variables to hold the data for each course of each grp
    string courseGrp1, courseGrp2;
    int scoreGrp1, scoreGrp2, courseCount = 0;
    double courseAvg1, courseAvg2, avgGrp1 = 0, avgGrp2 = 0;
    // reading data while both files have a course data in them
    while (f1 >> courseGrp1 && f2 >> courseGrp2)
    {
        double totalScoreGrp1 = 0, totalScoreGrp2 = 0;
        int scoreCountGrp1 = 0, scoreCountGrp2 = 0;
        // reading from file f1
        while (f1 >> scoreGrp1)
        {
            if (scoreGrp1 == -999)
                break;
            // calculating total score of a course for group 1
            totalScoreGrp1 += scoreGrp1;
            // updating the score count for group 1
            scoreCountGrp1++;
        }
        // reading from file f2
        while (f2 >> scoreGrp2)
        {
            if (scoreGrp2 == -999)
                break;
            // calculating total score of a course for group 2
            totalScoreGrp2 += scoreGrp2;
            // updating the score count for group 2
            scoreCountGrp2++;
        }
        // if both the course names are same, do the following
        if (courseGrp2 == courseGrp1)
        {
            // increment the courseCount
            courseCount++;
            // calculate avg for the current course
            courseAvg1 = totalScoreGrp1 / scoreCountGrp1;
            courseAvg2 = totalScoreGrp2 / scoreCountGrp2;
            // adding the current course's average to the group avg
            avgGrp1 += courseAvg1;
            avgGrp2 += courseAvg2;
            print(courseGrp1, courseAvg1, courseAvg2);
        }
        // else print an error message
        else
        {
            cout << "\nTHE COURSE IDs WERE NOT SAME\nEXITING....";
            exit(1);
        }
    }
    cout << fixed << setprecision(2);
    cout << "\nAvg for group 1: " << avgGrp1 / courseCount;
    cout << "\nAvg for group 2: " << avgGrp2 / courseCount;
}
// driver function
int main()
{
    // opening file group1.txt
    ifstream f1("group1.txt", ios::in);
    ifstream f2("group2.txt", ios::in);
    // checking if the first file opened
    if (!f1.is_open())
    {
        cout << "Error: Could not open the input file 1!\nExiting....\n";
        exit(1);
    }
    // checking if the second file opened
    if (!f2.is_open())
    {
        cout << "Error: Could not open the input file 2!\nExiting....\n";
        exit(1);
    }
    // Printing the header  to the console
    cout << left << setw(13) << "CourseId" << setw(13) << "Group No" << "Course Average\n";
    // calling calculateAverage function to calculate and print the averages
    calculateAverage(f1, f2);
    // closing input file f1
    f1.close();
    // closing input file f2
    f2.close();
    return 0;
}