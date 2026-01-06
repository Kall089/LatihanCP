#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < b; i++)

using namespace std;

int main()
{
    int arr[] = {10, 6, 20, 30, 6, 70};
    int n = sizeof(arr) / sizeof(int);

    priority_queue<int> heap;

    for (int x : arr)
    {
        heap.push(x);
    }

    while (!heap.empty())
    {
        cout << heap.top() << endl;
        heap.pop();
    }
}