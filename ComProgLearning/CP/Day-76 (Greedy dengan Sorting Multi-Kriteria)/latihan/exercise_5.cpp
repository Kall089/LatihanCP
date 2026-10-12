/*
============================================================
🏋️ Exercise 5: Antrean Bermodal
============================================================
Day: 76 | Difficulty: Hard
Topic: Tie-break yang menentukan kelayakan, bukan sekadar urutan
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N tugas. Tugas ke-i membutuhkan modal minimal m[i] agar boleh dimulai,
dan setelah dikerjakan modalmu BERKURANG sebanyak c[i].
Kamu mulai dengan modal M dan harus mengerjakan SELURUH tugas dalam urutan
apa pun yang kamu pilih. Modal tidak boleh menjadi negatif kapan pun.
Tentukan apakah ada urutan yang memungkinkan seluruh tugas dikerjakan.
Cetak YES atau NO.

📥 INPUT FORMAT:
- Baris pertama: N dan M
- N baris berikutnya: m[i] dan c[i]

📤 OUTPUT FORMAT:
- YES atau NO

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 0 <= M <= 10^18
- 0 <= c[i] <= m[i] <= 10^9

📎 SAMPLE INPUT 1:
2 20
10 5
8 6

📎 SAMPLE OUTPUT 1:
YES

📎 SAMPLE INPUT 2:
2 10
10 5
9 6

📎 SAMPLE OUTPUT 2:
NO

📎 SAMPLE INPUT 3:
2 5
5 0
5 0

📎 SAMPLE OUTPUT 3:
YES

💡 HINT: Perhatikan bahwa m[i] selalu lebih besar atau sama dengan c[i].
         Artinya sebuah tugas membutuhkan modal m[i] tetapi hanya
         menghabiskan c[i]; selisih m[i] - c[i] adalah "cadangan" yang
         harus tersedia tetapi tidak terpakai.
         Karena SELURUH tugas harus dikerjakan, total pengeluarannya tetap
         berapa pun urutannya. Yang berubah hanya apakah kamu pernah
         kehabisan modal di tengah jalan.
         Pikirkan dua tugas berdampingan dan tanyakan: urutan mana yang
         lebih mudah dipenuhi? Tuliskan syarat kelayakan untuk kedua
         urutan, lalu bandingkan.
         Untuk sampel 1, hitung dengan tangan KEDUA urutan yang mungkin dan
         lihat bahwa hanya satu di antaranya yang berhasil. Lalu untuk
         sampel 2, periksa bahwa TIDAK ADA urutan yang berhasil — bedanya
         hanya satu angka pada m.
         Sampel 3 menguji apa yang terjadi ketika dua tugas identik dan
         c bernilai nol.
         Waspadai tipe data: M sampai 10^18.

🎯 Learning Goals:
- [ ] Menurunkan kriteria untuk soal KELAYAKAN, bukan optimasi
- [ ] Menyadari bahwa total tidak berubah, hanya lintasannya
- [ ] Menangani modal besar tanpa overflow
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: turunkan kriteria pengurutan dari dua tugas berdampingan

    // TODO: simulasikan dan periksa kelayakan

    return 0;
}
