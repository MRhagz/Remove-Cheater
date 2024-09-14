//
// Created by Moen Malone Rago on 9/12/24.
//

#ifndef COURSE_H
#define COURSE_H
#include "Student.h"
#include <string>

class Course {
    string title;
    int size;
    int capacity;
    Student** students;

    Course* cheaters;
    // dynamically resize the students
    void dynamic_resize() {
        if (size == capacity)
            capacity += ceil(capacity * .5);
        else if (size <= capacity * 2.0/3 && capacity != 5)
            capacity -= floor(capacity * .25);
        else
            return;

        students = (Student**)realloc(students, capacity * sizeof(Student*));
    }

    // to shift the elements to the left to the given position
    void shiftElements (int pos) {
        if (pos < 0 || pos > capacity)
            return;

        for (int i = pos-1; i < size-1; i++)
            students[i] = students[i+1];
    }

    // to remove the element in the given position
    void remove (int pos) {
        free(students[pos-1]);
        shiftElements(pos);
        size--;
    }

    // checks if student is blocklisted


public:
    explicit Course (string title) : size(0), capacity(5) {
        this->title = title;
        students = (Student**)malloc(capacity * sizeof(Student*));
        cheaters = nullptr;
    }

    int add (Student* s) {
        cout << "ADDING " << s->name << endl;
        if (cheaters != nullptr && cheaters->isCheater(s))
            return -1;
        dynamic_resize();
        students[size++] = s;
        for (int i = size-1; i > 0; --i) {
            if (students[i]->name < students[i-1]->name) {
                swap(students[i], students[i-1]);
            }
        }
        return 0;
    }

    bool isCheater (Student* s) const {
        for (int i = 0; i < size; i++) {
            if (students[i]->year == s->year && students[i]->program == s->program) {
                return true;
            }
        }
        return false;
    }

    int removeCheater (Student* s) {
        cout << cheaters << endl;
        cout << students << endl;

        int count = 0;
        int found = false;
        for (int i = 0; i < size; i++) {
            if (s->name == students[i]->name) {
                if (cheaters == nullptr)
                    cheaters = new Course("Cheaters");

                cheaters->add(s);
                remove(i+1);
                found = true;
                count++;
                break;
            }
        }
        if (found) {
            for (int i = 0; i < size; i++) {
                if (cheaters->isCheater(s)) {
                    remove(i+1);
                    count++;
                    --i;
                }
            }
        }

        size -= count;
        dynamic_resize();

        return count;
    }

    void print () const {
        for (int i = 0; i < capacity; i++) {
            cout << i+1 << ". ";
            if (i < size)
                cout << students[i]->name << " - " << students[i]->program << " " << students[i]->year << endl;
            else
                cout << "(none)" << endl;
        }
    }
    ~Course() {
        delete(cheaters);

        for (int i = 0; i < size; i++)
            free(students[i]);

        free(students);

        cout << "Destructed" << endl;
    }
};



#endif //COURSE_H

