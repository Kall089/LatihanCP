/*
============================================================
🏋️ Exercise 3: Nominal Donasi yang Mungkin (Bounded Reachability)
============================================================
Day: 147 | Difficulty: Hard | Topic: Bounded Reachability / Subset Sum
Source: POJ 1742 / Classic DP
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah panitia penggalangan dana memiliki N jenis kupon donasi.
Kupon jenis ke-i memiliki nilai nominal w[i] rupiah dan tersedia sebanyak c[i] lembar.
Hitung berapa banyak nominal berbeda dalam rentang 1 sampai S (inklusif)
yang dapat dibentuk dengan menggabungkan sebagian kupon yang ada.
Yang dihitung adalah banyaknya nominal positif yang terjangkau, BUKAN banyaknya cara kombinasi.
Nominal 0 tidak ikut dihitung.

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat N dan S.
- N baris berikutnya, masing-masing berisi dua bilangan bulat w[i] dan c[i].

📤 OUTPUT FORMAT:
- Satu bilangan bulat: banyaknya nominal dalam rentang [1, S] yang dapat dibentuk.

📏 CONSTRAINTS:
- 1 <= N <= 60
- 0 <= S <= 20.000
- 1 <= w[i] <= 20.000
- 0 <= c[i] <= 10^9

📎 SAMPLE INPUT 1:
2 10
2 2
3 1

📎 SAMPLE OUTPUT 1:
5

[Penjelasan Sample 1:
Kupon yang tersedia: dua lembar 2 dan satu lembar 3.
Kombinasi nominal yang bisa dibentuk:
- {2} = 2
- {3} = 3
- {2, 2} = 4
- {2, 3} = 5
- {2, 2, 3} = 7
Total ada 5 nominal berbeda dalam rentang [1, 10] yang terjangkau: {2, 3, 4, 5, 7}.]

📎 SAMPLE INPUT 2:
1 5
1 5

📎 SAMPLE OUTPUT 2:
5

[Penjelasan Sample 2: Kupon 1 ada 5 lembar, bisa membentuk 1, 2, 3, 4, 5. Total = 5.]

📎 SAMPLE INPUT 3:
1 0
1 5

📎 SAMPLE OUTPUT 3:
0

[Penjelasan Sample 3: Rentang [1, 0] kosong, output = 0.]

💡 HINT:
- Gunakan array boolean `can` berukuran (S + 1), dengan can[0] = true.
- Pecah stok c[i] menjadi paket biner q.
- Paket q memiliki bobot q * w[i].
- Untuk setiap paket, update boolean can secara mundur dari S ke q * w[i]:
  can[j] |= can[j - q * w[i]].
- Hitung berapa banyak elemen true pada indeks 1 sampai S.

🎯 Learning Goals:
- [ ] Menggunakan Dekomposisi Biner untuk masalah jangkauan nilai (Reachability / Subset Sum).
- [ ] Memahami sifat idempoten operasi logika OR yang kebal terhadap duplikasi representasi paket.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, s;
    if (!(cin >> n >> s)) return 0;

    vector<int> w(n);
    vector<long long> c(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> c[i];
    }

    // TODO: Selesaikan Bounded Reachability
    // 1. vector<bool> can(s + 1, false), can[0] = true
    // 2. Dekomposisi biner stok kupon
    // 3. Update boolean OR secara mundur
    // 4. Hitung jumlah elemen true pada can[1...s]

    return 0;
}
