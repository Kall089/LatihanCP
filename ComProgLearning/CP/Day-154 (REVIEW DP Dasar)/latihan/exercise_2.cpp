/*
============================================================
🏋️ Exercise 2: Rangkaian Pameran Bertumbuh (Maximum Sum Increasing Subsequence)
============================================================
Day: 154 | Difficulty: Medium | Topic: LIS Variation / Weighted LIS
Source: Classic DP / Review Synthesis
Time Limit: 2.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Terdapat N karya seni yang dipamerkan dalam urutan kedatangan tertentu.
Karya ke-i memiliki tingkat keahlian a[i] dan nilai kurasi v[i] (nilai kurasi bisa bernilai negatif).
Kurator ingin memilih sebuah SUBSEKUENS KARYA YANG TIDAK KOSONG sedemikian rupa sehingga:
1. Tingkat keahlian dari karya-karya yang dipilih meningkat secara ketat:
   Jika indeks yang dipilih adalah i_1 < i_2 < ... < i_k, maka harus berlaku:
   a[i_1] < a[i_2] < ... < a[i_k].
2. TOTAL NILAI KURASI (jumlah v[i]) dari subsekuens tersebut bernilai SEBESAR MUNGKIN.

Perhatikan: Yang dimaksimalkan adalah JUMLAH NILAI KURASI, bukan panjang subsekuens!
Subsekuens harus memiliki setidaknya satu karya.

Tentukan total nilai kurasi maksimum yang bisa didapatkan.

📥 INPUT FORMAT:
- Baris pertama berisi satu bilangan bulat N.
- N baris berikutnya masing-masing berisi dua bilangan bulat a[i] dan v[i].

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: jumlah nilai kurasi maksimum.

📏 CONSTRAINTS:
- 1 <= N <= 2.000
- -1.000.000.000 <= a[i], v[i] <= 1.000.000.000

📎 SAMPLE INPUT 1:
4
1 5
3 100
2 6
4 7

📎 SAMPLE OUTPUT 1:
112

[Penjelasan Sample 1:
Pilih karya 0 (a=1, v=5), karya 1 (a=3, v=100), dan karya 3 (a=4, v=7).
Tingkat keahlian: 1 < 3 < 4 (meningkat ketat).
Total nilai kurasi: 5 + 100 + 7 = 112.]

📎 SAMPLE INPUT 2:
1
9 -5

📎 SAMPLE OUTPUT 2:
-5

[Penjelasan Sample 2:
Hanya ada 1 karya bernilai -5. Karena subsekuens tidak boleh kosong, jawabannya -5.]

📎 SAMPLE INPUT 3:
3
1 -8
2 -3
3 -9

📎 SAMPLE OUTPUT 3:
-3

[Penjelasan Sample 3:
Pilih karya ke-2 saja (a=2, v=-3), nilai maksimum adalah -3.]

💡 HINT:
- Definisikan state:
  `dp[i]` = jumlah nilai kurasi maksimum dari subsekuens meningkat ketat yang BERAKHIR di elemen i.
- Base case: `dp[i] = v[i]` (subsekuens hanya terdiri dari karya i itu sendiri).
- Transisi:
  Untuk setiap j < i:
  Jika `a[j] < a[i]`:
    `dp[i] = max(dp[i], dp[j] + v[i])`.
- Jawaban akhir: nilai maksimum dari `dp[i]` untuk seluruh 0 <= i < N.
- Hati-hati: Inisialisasi jawaban akhir dengan nilai terkecil (misal `-INF`), BUKAN `0`,
  karena semua nilai kurasi bisa negatif dan subsekuens tidak boleh kosong.

🎯 Learning Goals:
- [ ] Menyesuaikan pola DP LIS standar untuk memaksimalkan bobot/jumlah nilai (*weighted* LIS).
- [ ] Menangani kasus di mana seluruh bobot bernilai negatif dan subsekuens non-kosong.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // TODO: Selesaikan Maximum Sum Increasing Subsequence

    return 0;
}
