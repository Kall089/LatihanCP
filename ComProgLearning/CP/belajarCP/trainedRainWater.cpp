#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    stack<int> st;

    int total = 0;

    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && arr[st.top()] < arr[i])
        {
            int dasar = st.top();
            st.pop();

            if (st.empty())
            {
                break;
            }

            int kiri = st.top();
            int lebar = i - kiri - 1;
            int tinggi = min(arr[kiri], arr[i]) - arr[dasar];
            total += lebar * tinggi;
        }
        st.push(i);
    }

    cout << total;
}