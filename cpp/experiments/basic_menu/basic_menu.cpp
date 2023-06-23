#include <iostream>

using namespace std;

int main() {
    char choice[10];

    while (1)
    {
        cout << "Select:\n(a)dd\n(d)elete\n(q)uit\n: ";
        cin >> choice;

        switch (choice[0])
        {
        case 'a':
            cout << "Adding...\n";
            break;
        case 'd':
            cout << "Deleting...\n";
            break;
        case 'q':
            cout << "Quitting...\n";
            exit(0);
        default:
            cout << "Wot?!\n";
            break;
        }
    }

    return 0;
}