/*
============================================================
🏋️ Exercise 4: Denda Berbobot
============================================================
Day: 78 | Difficulty: Medium
Topic: Kapan greedy mati, dan apa penggantinya
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N tugas yang semuanya harus dikerjakan pada satu mesin, satu per satu
tanpa jeda, mulai dari waktu 0.
Tugas ke-i memerlukan t[i] satuan waktu, punya tenggat d[i], dan denda w[i]
yang harus dibayar kalau tugas itu selesai setelah tenggatnya.
Cari TOTAL DENDA MINIMUM.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: t[i], d[i], dan w[i]

📤 OUTPUT FORMAT:
- Satu bilangan: total denda minimum

📏 CONSTRAINTS:
- 1 <= N <= 2000
- 1 <= t[i] <= 100
- 1 <= d[i] <= 2 * 10^5
- 1 <= w[i] <= 10^9

📎 SAMPLE INPUT 1:
3
3 3 5
3 4 10
3 5 1

📎 SAMPLE OUTPUT 1:
6

📎 SAMPLE INPUT 2:
2
1 1 5
1 1 7

📎 SAMPLE OUTPUT 2:
5

💡 HINT: Coba dulu dua pendekatan yang paling wajar, dan uji keduanya
         dengan brute force atas seluruh permutasi pada n kecil:
           (a) kerangka Exercise 2 (batalkan durasi terbesar)
           (b) kerangka Exercise 3 (batalkan denda terkecil)
         Keduanya akan gagal. Menemukan kegagalan itu sendiri adalah
         bagian dari latihan ini.
         Kenapa gagal? Karena sekarang ada DUA besaran yang bersaing:
         waktu yang dimakan sebuah tugas, dan denda yang dihindarinya.
         Dua keadaan dengan denda terselamatkan sama bisa memakai waktu
         berbeda, dan tidak ada yang mendominasi.
         Itu tandanya kamu butuh pendekatan yang menyimpan lebih banyak
         informasi daripada satu angka.
         Perhatikan batasannya: N sampai 2000 dan t sampai 100. Kalikan
         keduanya — angka itu memberitahumu ukuran tabel yang dimaksud.
         Setelah memilih pendekatan, satu pertanyaan tersisa: apakah urutan
         pemrosesan masih penting? Jawabannya ya. Pikirkan klaim ini: kalau
         sehimpunan tugas bisa diselesaikan tepat waktu semua, maka
         mengerjakannya menurut tenggat menaik juga berhasil.
         Terakhir, perhatikan di mana tenggat harus muncul di dalam
         kodemu. Ia bukan sekadar syarat tambahan — ia adalah BATAS pada
         salah satu loopmu.

🎯 Learning Goals:
- [ ] Mengenali "dua besaran bersaing" sebagai tanda greedy mati
- [ ] Membaca batasan untuk menentukan ukuran tabel
- [ ] Menegakkan tenggat lewat batas loop, bukan pemeriksaan terpisah
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: buktikan dulu bahwa greedy gagal

    // TODO: urutkan menurut tenggat; rumuskan tabel

    // TODO: tenggat menjadi BATAS loop

    return 0;
}
