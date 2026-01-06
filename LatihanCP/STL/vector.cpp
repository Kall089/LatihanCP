#include <bits/stdc++.h>
#define rep(i, a, b) for (int i = a; i < b; i++)

using namespace std;

int main()
{
    int n = 5;
    vector<int> v;

    cin >> n;

    rep(i, 0, n)
    {
        int no;
        cin >> no;
        v.push_back(no);
        cout << "Capacity " << v.capacity() << " Size " << v.size() << endl;
    }
}