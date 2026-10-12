/*
============================================================
🏋️ Exercise 2: Memotong Pita Panggung (Cutting Stick DP)
============================================================
Day: 270 | Difficulty: Medium | Topic: Knuth Optimization (Cutting Problems)
Source: UVa 10003 Cutting Sticks Variant
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah pita panggung yang membentang lurus memiliki panjang awal L meter (dari koordinat 0 hingga L).
Pita tersebut harus dipotong pada M titik tertentu yang diberikan dalam urutan menaik ketat:
`0 < p[1] < p[2] < ... < p[M] < L`.

Setiap kali kamu memotong sebuah potongan pita, biaya yang harus dibayar adalah
PANJANG DARI POTONGAN PITA TERSEBUT SESAAT SEBELUM DIPOTONG.
Setiap titik potong p[i] harus dipotong tepat satu kali. Urutan pemotongan bebas dipilih.
Jika M = 0 (tidak ada titik potong), biayanya adalah 0.

Tentukan TOTAL BIAYA PEMOTONGAN MINIMUM untuk menyelesaikan seluruh M pemotongan!

Selesaikan dengan KNUTH OPTIMIZATION dalam waktu O(M^2)!

📥 INPUT FORMAT:
- Baris pertama berisi dua bilangan bulat L dan M.
- Baris kedua berisi M bilangan bulat p[1], p[2], ..., p[M] (terurut menaik).
  (Jika M = 0, baris kedua dapat kosong).

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: total biaya pemotongan minimum.

📏 CONSTRAINTS:
- 1 <= L <= 1.000.000.000
- 0 <= M <= 1999
- 0 < p[1] < p[2] < ... < p[M] < L

📎 SAMPLE INPUT 1:
10 3
2 4 7

📎 SAMPLE OUTPUT 1:
20

[Penjelasan Sample 1:
Titik potong pada koordinat 2, 4, 7.
- Tambahkan batas: p = [0, 2, 4, 7, 10]. Panjang bagian-bagian pita: [2, 2, 3, 3].
- Potong pertama di koordinat 4 (panjang 10, biaya = 10). Menghasilkan dua pita: [0..4] dan [4..10].
- Potong kedua di koordinat 2 pada pita kiri (panjang 4, biaya = 4).
- Potong ketiga di koordinat 7 pada pita kanan (panjang 6, biaya = 6).
Total biaya = 10 + 4 + 6 = 20.]

📎 SAMPLE INPUT 2:
100 0

📎 SAMPLE OUTPUT 2:
0

📎 SAMPLE INPUT 3:
9 1
4

📎 SAMPLE OUTPUT 3:
9

💡 HINT:
- Masalah pemotongan stick dari luar ke dalam adalah EKIVALEN DENGAN penggabungan segmen dari dalam ke luar!
- Tambahkan `p[0] = 0` dan `p[M+1] = L`.
- Terdapat M+1 potongan segmen dasar dengan panjang `a[i] = p[i+1] - p[i]`.
- Total biaya pemotongan sama persis dengan biaya menggabungkan M+1 segmen ini secara berurutan!
- Selesaikan dengan Knuth Optimization untuk M+1 elemen.

🎯 Learning Goals:
- [ ] Memahami reduksi masalah pemotongan (*cutting stick*) menjadi penggabungan berurutan (*sequential merging*).
- [ ] Mengimplementasikan Knuth Optimization pada array selisih koordinat.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll l;
    int m;
    if (!(cin >> l >> m)) return 0;

    // TODO: Selesaikan dengan Knuth Optimization O(M^2)

    return 0;
}
