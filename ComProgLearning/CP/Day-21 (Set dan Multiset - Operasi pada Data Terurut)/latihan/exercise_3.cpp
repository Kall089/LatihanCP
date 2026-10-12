/*
============================================================
🏋️ Exercise 3: Concert Tickets (Multiset)
============================================================
Day: 4 | Difficulty: Medium
Topic: Multiset, upper_bound, erase
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N tiket konser dengan harga tertentu. Ada M customer datang
secara berurutan, masing-masing punya budget maksimal.

Untuk setiap customer, cari tiket TERMAHAL yang harganya ≤ budget.
Jika ada, customer beli tiket itu (tiket hilang dari daftar).
Jika tidak ada tiket yang affordable, output -1.

📥 INPUT FORMAT:
- Baris pertama: dua integer N dan M
- Baris kedua: N integer (harga tiket)
- Baris ketiga: M integer (budget masing-masing customer)

📤 OUTPUT FORMAT:
- M baris: harga tiket yang dibeli, atau -1

📏 CONSTRAINTS:
- 1 ≤ N, M ≤ 200,000
- 1 ≤ harga[i], budget[j] ≤ 1,000,000,000

📎 SAMPLE INPUT 1:
5 3
5 3 7 8 5
4 8 3

📎 SAMPLE OUTPUT 1:
3
8
-1

📎 SAMPLE INPUT 2:
3 4
10 20 30
25 10 35 15

📎 SAMPLE OUTPUT 2:
20
10
30
-1

💡 HINT: Masukkan semua tiket ke multiset.
         Untuk setiap budget, pakai upper_bound(budget), lalu mundur 1.
         Jangan lupa erase tiket setelah dibeli!

🎯 Learning Goals:
- [ ] Gunakan multiset untuk koleksi sorted + duplicates
- [ ] Pakai upper_bound + decrement untuk cari largest ≤ x
- [ ] Erase by iterator (bukan by value!)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N dan M
    int n, m;
    cin >> n >> m;

    // TODO: Baca N harga tiket, masukkan ke multiset
    multiset<long long> tiket;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        tiket.insert(x);
    }

    for (int i = 0; i < m; i++)
    {
        int budget;
        cin >> budget;

        auto it = tiket.upper_bound(budget);
        if (it == tiket.begin())
        {
            cout << "-1" << endl;
        }
        else
        {
            it--;
            cout << *it << endl;
            tiket.erase(it);
        }
    }

    return 0;
}
