/*
============================================================
📋 TUGAS 09: Dua Subarray Tidak Tumpang Tindih
============================================================
Source: Original
Difficulty: Medium
Topics: kadane prefiks + sufiks, mengunci titik potong

PROBLEM:
Cari DUA subarray yang keduanya TIDAK KOSONG dan TIDAK saling tumpang
tindih, sehingga total jumlah keduanya maksimum. Kedua subarray boleh
bersebelahan. Dijamin N >= 2.

Ide kuncinya: ada tepat satu titik potong i sehingga subarray pertama
seluruhnya berada di a[1..i] dan subarray kedua di a[i+1..N]. Kunci
titik potong itu, lalu kedua sisi menjadi masalah Kadane biasa yang
saling bebas.

INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N bilangan

OUTPUT FORMAT:
- Satu bilangan

CONSTRAINTS:
- 2 <= N <= 2*10^5
- -10^9 <= a[i] <= 10^9

------------------------------------------------------------
SAMPLE 1 - kasus normal
input:
5
1 -2 3 -2 4
output:
7
penjelasan: ambil [3] dan [4] -> 3+4 = 7. Perhatikan bahwa Kadane
tunggal pada array ini menghasilkan 5 ([3,-2,4]), dan menggabungkan
begitu saja justru KALAH karena ikut menelan -2.

SAMPLE 2 - N = 2, keduanya terpaksa diambil
input:
2
-5 -3
output:
-8
penjelasan: kedua subarray wajib tidak kosong, jadi tidak ada pilihan
lain selain mengambil masing-masing satu elemen. Jawaban negatif itu
sah.

SAMPLE 3 - dipisahkan jurang dalam
input:
6
4 -1 4 -100 5 -1
output:
12
penjelasan: [4,-1,4] = 7 dan [5] = 5. Nilai -100 memaksa pemisahan.

SAMPLE 4 - semua negatif
input:
4
-1 -2 -3 -4
output:
-3
penjelasan: ambil dua elemen terbesar yang posisinya memungkinkan,
yaitu -1 dan -2.
------------------------------------------------------------

💡 CEK SEBELUM SUBMIT:
- kiri[i] adalah maksimum BERJALAN di a[1..i], bukan "harus berakhir
  di i". Salah membedakan keduanya adalah bug utama soal ini
- titik potong i berjalan dari 1 sampai N-1
- sentinel awal harus negatif besar, bukan 0 (lihat sample 2 dan 4)
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Kerjakan di sini
    // Hitung best kadane pada prefiks dan pada sufiks, lalu coba semua titik pembatas.

    return 0;
}
