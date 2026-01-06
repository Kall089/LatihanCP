#include <bits/stdc++.h>

using namespace std;

int main()
{
    array<int, 6> arr = {1, 2, 3, 4, 7, 9};
    arr[0] = 10;

    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }

    arr.size();
}