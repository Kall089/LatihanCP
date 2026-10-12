#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, S, T;

    cin >> n >> S >> T;

    vector<int> pom(n);

    int posisi = 0;
    int i = 0;
    int isi_bensin = 0;

    while (S > posisi + T)
    {
        int terjauh = -1;

        while (i < n && pom[i] <= terjauh + T)
        {
            terjauh = pom[i];
        }

        if (terjauh <= posisi)
        {
        }
    }
}