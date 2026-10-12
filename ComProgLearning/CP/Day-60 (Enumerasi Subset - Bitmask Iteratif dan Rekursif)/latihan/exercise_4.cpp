/*
============================================================
  Exercise 4: Subset Sum
============================================================
Diberikan array a[] dengan n elemen bilangan bulat positif dan
sebuah target K. Cari apakah ada subset (tidak kosong) yang
jumlah elemennya sama dengan K.

Jika ada, cetak "YES" lalu cetak SEMUA subset yang memenuhi
(dalam urutan mask dari kecil ke besar), masing-masing dalam
format: { a[i1] a[i2] ... }

Jika tidak ada, cetak "NO".

📏 CONSTRAINTS:
  - 1 ≤ n ≤ 20
  - 1 ≤ a[i] ≤ 10^6
  - 1 ≤ K ≤ 10^9

📎 SAMPLE INPUT 1:
  4 5
  3 1 4 2

📎 SAMPLE OUTPUT 1:
  YES
  { 1 4 }
  { 3 2 }

📎 SAMPLE INPUT 2:
  3 10
  1 2 3

📎 SAMPLE OUTPUT 2:
  NO

💡 HINT:
  - Loop mask dari 1 (bukan 0, karena subset harus tidak kosong) sampai (1<<n)-1
  - Untuk setiap mask, hitung sum semua a[i] di mana bit ke-i aktif
  - Jika sum == K, catat mask ini sebagai jawaban
  - Setelah loop, cek apakah ada jawaban dan cetak

🎯 Learning Goals:
  Aplikasi enumerasi subset untuk problema subset sum klasik.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long K;
    cin >> n >> K;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> answers;  // menyimpan semua mask yang memenuhi

    // TODO: iterasi semua subset tidak kosong
    // untuk setiap subset: hitung sum, jika sum == K simpan mask ke answers

    if (answers.empty()) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (int mask : answers) {
            // TODO: cetak elemen-elemen dari subset ini
            cout << "{ ";
            for (int i = 0; i < n; i++) {
                // TODO: jika bit ke-i aktif, cetak a[i]
            }
            cout << "}\n";
        }
    }

    return 0;
}
