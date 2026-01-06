#include <iostream>

using namespace std;

int main()
{
    int arr[5] = {1, 2, 3, 4, 5}; // init list
    int n = sizeof(arr) / sizeof(int);

    for (int i = 0; i < n; i++)
    {
        cout << arr[i];
    }

    return 0;
}