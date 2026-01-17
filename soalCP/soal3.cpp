#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < b; i++)

void inputData(vector<int> &data, int N)
{
    rep(i, 0, N)
    {
        cin >> data[i];
    }
}

int twoPointer(vector<int> data, int N, int D)
{
    int left = 0;
    int right = 0;

    int count = 0;

    while (right < N)
    {
        int diff = data[right] - data[left];

        if (diff > D)
        {
            left++;
        }
        else if (diff < D)
        {
            right++;
        }
        else
        {
            right++;
            left++;
            count++;
        }

        if (right == left)
        {
            right++;
        }
    }

    return count;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, D;
    cin >> N >> D;

    vector<int> data(N);
    inputData(data, N);

    cout << twoPointer(data, N, D) << "\n";
}