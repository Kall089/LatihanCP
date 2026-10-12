#include <bits/stdc++.h>
using namespace std;

void backtracking(vector<int> &jalan, vector<vector<int>> &hasil, int n, const vector<int> arr, vector<bool> &dipakai)
{
    if (jalan.size() == n)
    {
        for (int c : jalan)
        {
            cout << c;
        }
        cout << endl;
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (dipakai[i])
            continue;
        dipakai[i] = true;
        jalan.push_back(arr[i]);
        backtracking(jalan, hasil, n, arr, dipakai);
        jalan.pop_back();
        dipakai[i] = false;
    }
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    vector<int> jalan;
    vector<vector<int>> hasil;
    vector<bool> dipakai(n);

    backtracking(jalan, hasil, n, arr, dipakai);
}