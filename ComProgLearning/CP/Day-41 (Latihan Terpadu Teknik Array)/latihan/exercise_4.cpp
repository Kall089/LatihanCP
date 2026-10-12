/*
============================================================
🏋️ Exercise 4: Jendela dengan Rentang Nilai Terbatas
============================================================
Day: 41 | Difficulty: Medium
Topic: sliding window variabel (Day 34) + DUA monotonic deque (Day 37)
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah mesin produksi mencatat N pengukuran berurutan. Mesin dianggap STABIL
pada suatu periode kalau selisih antara pengukuran tertinggi dan terendah
pada periode itu tidak melebihi K.

Cari panjang periode berurutan terpanjang di mana mesin stabil.

Ini soal gabungan klasik. Bagian sliding window-nya mudah, yang sulit adalah
menjawab "berapa maksimum dan minimum pada window saat ini" secara efisien -
karena window-nya melebar DAN menyempit. Menghitung ulang max dan min setiap
kali akan menghasilkan O(N^2).

📥 INPUT FORMAT:
- Baris pertama: N dan K
- Baris kedua: N bilangan bulat

📤 OUTPUT FORMAT:
- Satu bilangan: panjang periode stabil terpanjang

📏 CONSTRAINTS:
- 1 ≤ N ≤ 2·10^5
- 0 ≤ K ≤ 10^9
- 1 ≤ a[i] ≤ 10^9

📎 SAMPLE INPUT 1:
5 4
8 2 4 7 2

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
7 5
10 1 2 4 7 2 5

📎 SAMPLE OUTPUT 2:
5

📎 SAMPLE INPUT 3:
5 0
3 3 3 1 3

📎 SAMPLE OUTPUT 3:
3

📎 SAMPLE INPUT 4:
1 0
42

📎 SAMPLE OUTPUT 4:
1

💡 HINT: Pakai DUA deque - satu menjaga maksimum (nilainya menurun), satu
         menjaga minimum (nilainya menaik). Saat kiri window bergerak,
         buang dari kedua deque semua indeks yang sudah keluar window.

🎯 Learning Goals:
- [ ] Menggabungkan window variabel dengan struktur pembantu
- [ ] Menjalankan dua monotonic deque bersamaan tanpa tertukar
- [ ] Memahami kenapa deque menyimpan indeks, bukan nilai
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N, K, dan array

    // TODO: Siapkan dua deque berisi INDEKS
    //       dqMax: nilainya menurun dari depan ke belakang
    //       dqMin: nilainya menaik dari depan ke belakang

    // TODO: Untuk tiap r, masukkan indeks r ke kedua deque dengan aturan
    //       monotonnya masing-masing

    // TODO: Selama a[dqMax.front()] - a[dqMin.front()] > K, majukan l,
    //       dan buang indeks yang < l dari KEDUA deque

    // TODO: best = max(best, r - l + 1)

    return 0;
}
