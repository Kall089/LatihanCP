/*
============================================================
✅ Solution 2: Semua Jumlah Koin
============================================================
Approach: Reachable sums dengan subset sum DP
Complexity: Time O(N*T) | Space O(T), T = total semua koin
Key Insight: Untuk mencetak semua jumlah yang mungkin, target DP bukan satu
             angka S, melainkan seluruh rentang 0..total.

📖 PENJELASAN PENDEKATAN:
1. Hitung total semua koin sebagai batas sum terbesar.
2. Jalankan subset sum 0/1 sampai total.
3. Scan s dari 1 sampai total dan simpan semua yang reachable.
4. Cetak banyaknya dan daftar sum terurut.

🔄 ALTERNATIVE APPROACHES:
- bitset: `bs |= bs << x`, biasanya lebih cepat.
- set<int>: lebih sederhana secara ide, tetapi overhead besar.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> a(n);
    int total = 0;
    for (int &x : a)
    {
        cin >> x;
        total += x;
    }

    vector<char> bisa(total + 1, 0);
    bisa[0] = 1;

    for (int x : a)
    {
        for (int s = total; s >= x; s--)
        {
            bisa[s] |= bisa[s - x];
        }
    }

    vector<int> hasil;
    for (int s = 1; s <= total; s++)
    {
        if (bisa[s])
            hasil.push_back(s);
    }

    cout << hasil.size() << '\n';
    for (int i = 0; i < (int)hasil.size(); i++)
    {
        if (i)
            cout << ' ';
        cout << hasil[i];
    }
    cout << '\n';

    return 0;
}
