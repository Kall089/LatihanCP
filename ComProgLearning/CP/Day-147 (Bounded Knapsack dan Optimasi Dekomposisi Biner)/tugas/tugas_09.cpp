/*
============================================================
📋 TUGAS 09: Pembagian Beban Kargo Seimbang (Bounded Partition)
============================================================
Source: Classic DP / Partition Problem
Difficulty: Medium
Topics: Bounded Partition Equal Subset Sum, Reachability

PROBLEM:
Sebuah pesawat kargo memiliki dua kompartemen bagasi identik di sisi kiri dan kanan.
Terdapat N jenis peti kemas yang harus dimuat. Peti kemas jenis ke-i memiliki berat w[i] kg
dan terdapat c[i] buah peti kemas jenis tersebut.
Tentukan apakah seluruh peti kemas tersebut dapat dibagi menjadi dua kelompok
yang memiliki TOTAL BERAT TEPAT SAMA PERSIS (sehingga keseimbangan pesawat terjaga).
Keluarkan "YES" jika mungkin, atau "NO" jika tidak mungkin.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
N baris berikutnya, masing-masing berisi dua bilangan bulat w[i] dan c[i].

OUTPUT FORMAT:
Cetak "YES" (tanpa tanda kutip) jika dapat dibagi dua sama besar, atau "NO" jika tidak.

CONSTRAINTS:
1 <= N <= 100
1 <= w[i] <= 1.000
1 <= c[i] <= 100
Total berat seluruh peti kemas <= 50.000

SAMPLE INPUT 1:
2
4 3
6 2

SAMPLE OUTPUT 1:
YES
(Penjelasan: Total peti 0 berbobot 4*3 = 12. Total peti 1 berbobot 6*2 = 12. Total keseluruhan = 24.
Target per sisi = 12. Sisi kiri bisa memuat 3 peti jenis 0 (bobot 12), sisi kanan memuat 2 peti jenis 1 (bobot 12). Seimbang!)

SAMPLE INPUT 2:
2
3 3
5 1

SAMPLE OUTPUT 2:
YES
(Penjelasan: Total berat = 3*3 + 5 = 14. Target per sisi = 7. Satu sisi memuat satu peti 5 + satu peti 2?
Tunggu: peti hanya jenis 3 (tiga buah) dan jenis 5 (satu buah).
Kombinasi membentuk 7 dari {3, 3, 3, 5}:
Subset yang mungkin: 3, 5, 6, 8, 9, 11, 14. Nilai 7 tidak ada! Jadi output: NO)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> w(n);
    vector<int> c(n);
    long long total_weight = 0;
    for (int i = 0; i < n; i++) {
        cin >> w[i] >> c[i];
        total_weight += (long long)w[i] * c[i];
    }

    // TODO: Selesaikan Bounded Partition Equal Subset Sum
    // 1. Jika total_weight % 2 != 0 -> cetak NO
    // 2. target = total_weight / 2
    // 3. vector<bool> can(target + 1, false); can[0] = true;
    // 4. Dekomposisi biner stok peti, update mundur
    // 5. Cetak YES jika can[target] == true, else NO

    return 0;
}
