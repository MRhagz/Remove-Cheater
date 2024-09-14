#include "Course.h"

int main() {
    Course* csit = new Course("CSIT221");
    char op;
    Student* s;
    // if (s == nullptr)
    //     return 1;

    do {
        cout << "op: ";
        cin >> op;
        switch (op) {
            case 'a':
                s = new Student();
                cout << "Enter student name: ";
                cin >> s->name;
                cout << "Program and Year: ";
                cin >> s->program >> s->year;
                if (csit->add(s) == -1) {
                    cout << s->program << " " << s->year << " is blocklisted" << endl;
                }
                break;
            case 'c':
                cout << "Who cheated? ";
                cin >> s->name;
                cout << csit->removeCheater(s) << " student/s removed." << endl;;
                break;
            case 'p':
                csit->print();
                break;
            case 'x':
                break;
            default:
                cout << "Invalid op" << endl;
                break;
        }
    } while (op != 'x');

    delete(s);
    delete csit;
    return 0;
}
