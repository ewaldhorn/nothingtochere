#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

int main()
{
    // seed the randomizer
    srand((unsigned)time(NULL));

    cout << endl;

    for (int i = 1; i <= 10; i++)
    {
        int random = rand() % 100;
        cout << setw(3) << i << ":" << setw(5) << random << endl;
    }

    cout << endl;
    
    return 0;
}