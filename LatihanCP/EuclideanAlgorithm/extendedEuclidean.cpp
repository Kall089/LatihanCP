#include <bits/stdc++.h>
using namespace std;

vector<int> extendedGCD(int a, int b)
{
    if (b == 0)
    {
        return {1, 0};
    }

    vector<int> result = extendedGCD(b, a % b);

    int smallX = result[0];
    int smallY = result[1];

    int x = smallY;
    int y = smallX - (a / b) * smallY;

    return {x, y};
}

int main()
{
    int a, b;
    cin >> a >> b;

    vector<int> result = extendedGCD(a, b);
    cout << result[0] << " and " << result[1];
}