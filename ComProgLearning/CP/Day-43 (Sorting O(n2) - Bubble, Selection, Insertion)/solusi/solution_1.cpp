/*
============================================================
✅ Solution 1: Hitung Pertukaran Bubble Sort
============================================================
Approach: Bubble sort baku dengan batas loop yang menyusut
Complexity: Time O(n^2) | Space O(1)
Key Insight: Setelah putaran ke-i, sebanyak i elemen TERBESAR sudah berada
             di posisi akhirnya di ujung kanan. Karena itu batas loop dalam
             menyusut: j+1 < n-i. Ini bukan sekadar optimasi -- menuliskannya
             sebagai j < n-i akan mengakses a[n] di luar array.

📖 PENJELASAN PENDEKATAN:
1. Loop luar i dari 0 sampai n-2.
2. Loop dalam j dari 0 selama j+1 < n-i.
3. Tukar kalau a[j] > a[j+1], hitung swapnya.

IDENTITAS YANG PATUT DIINGAT:
   jumlah swap bubble sort = banyaknya INVERSI
   yaitu banyaknya pasangan (i, j) dengan i < j dan a[i] > a[j].

   Alasannya: setiap swap pada elemen BERDAMPINGAN menghilangkan tepat satu
   inversi (pasangan yang ditukar itu sendiri), dan tidak mengubah status
   pasangan lain mana pun. Array yang terurut punya nol inversi. Jadi jumlah
   swap harus sama persis dengan jumlah inversi awal.

   Verifikasi pada [5,1,4,2]: inversinya (5,1) (5,4) (5,2) (4,2) = 4,
   dan bubble sort memang melakukan 4 swap.  ✓

   Identitas ini penting karena Day 44 akan mengajarkan cara menghitung
   inversi dalam O(n log n) -- artinya kamu bisa menjawab "berapa swap
   bubble sort" untuk n = 10^5 tanpa menjalankan bubble sortnya.

⚠️ '>' BUKAN '>=': memakai >= akan menukar elemen kembar, merusak
   stabilitas sekaligus menambah swap yang tidak seharusnya dihitung.

⚠️ OVERFLOW: untuk n = 2000 jumlah swap maksimal ~2*10^6 (muat di int),
   tetapi untuk n = 10^5 bisa 5*10^9. Biasakan long long.

🔄 ALTERNATIVE APPROACHES:
- Merge sort untuk menghitung inversi: O(n log n) (Day 44).
- BIT + kompresi koordinat: O(n log n) (Day 38 + Day 170).
- Kedua-duanya memberi ANGKA yang sama tanpa menjalankan bubble sort.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    ll swapCount = 0;
    for (int i = 0; i + 1 < n; i++) {
        bool adaTukar = false;
        for (int j = 0; j + 1 < n - i; j++)        // j+1 < n-i
            if (a[j] > a[j + 1]) {                 // '>' menjaga stabilitas
                swap(a[j], a[j + 1]);
                swapCount++;
                adaTukar = true;
            }
        if (!adaTukar) break;
    }

    cout << swapCount << '\n';
    for (int i = 0; i < n; i++) cout << a[i] << " \n"[i + 1 == n];

    return 0;
}
