//g++  7.4.0

#include <iostream>
#include <bits/stdc++.h>

using namespace std;
// query by student id , student name


class Elective  {
    public:
    string name;
    int numberOfStudent = 0;

    bool operator <  (const Elective &other) const {
        return numberOfStudent > other.numberOfStudent;
    }
    list<int> students;
};

class Student {
    public:
    string name; // ordering of Student will be based on name
    int rollNo;
    list <Elective*> electivesTaken;
};

int main()
{
    // pq stores as electives
    // top will contain the most taken elective
    // pq.top() reference to Elective, numberOfStudents and List of students
    priority_queue <Elective, vector <Elective>> pq;

    /// int here is roll no, rollNo -> Student Object ptr
    unordered_map <int, Student*> umRollToStudent;

    // balance search tree on, string (name) -> Studenet Object ptr
    map <string, Student*> mpNameToStudent; // O(|s|) * O(logN)

    // O(N) * (O(|maxS|))

}
