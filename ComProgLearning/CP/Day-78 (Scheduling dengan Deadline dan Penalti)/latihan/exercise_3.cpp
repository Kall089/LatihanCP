/*
============================================================
🏋️ Exercise 3: Penalti Seragam
============================================================
Day: 78 | Difficulty: Medium
Topic: Regret berbobot dengan durasi seragam
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N tugas yang masing-masing memerlukan TEPAT SATU satuan waktu, semuanya
dikerjakan pada satu mesin mulai dari waktu 0.
Tugas ke-i punya tenggat d[i] dan denda w[i]. Kalau tugas ke-i selesai
setelah waktu d[i], kamu membayar denda sebesar w[i].
Semua tugas harus dikerjakan.
Cari TOTAL DENDA MINIMUM.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: d[i] dan w[i]

📤 OUTPUT FORMAT:
- Satu bilangan: total denda minimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= d[i] <= N
- 1 <= w[i] <= 10^9

📎 SAMPLE INPUT 1:
4
1 10
1 40
1 30
4 20

📎 SAMPLE OUTPUT 1:
40

📎 SAMPLE INPUT 2:
3
1 5
1 5
1 5

📎 SAMPLE OUTPUT 2:
10

💡 HINT: Perhatikan bahwa sekarang ada BOBOT, dan bobot biasanya
         mematikan greedy. Tetapi ada satu hal yang menyelamatkan soal ini:
         seluruh durasi SERAGAM.
         Pikirkan apa artinya. Kalau setiap tugas memakan sumber daya yang
         sama persis, apakah masih ada dua besaran yang bersaing?
         Setelah kamu menjawabnya, kerangka regret dari Exercise 2 bisa
         dipakai dengan satu perubahan: apa yang kamu batalkan saat
         melanggar?
         Perhatikan juga bahwa soal ini menanyakan denda MINIMUM, sedangkan
         algoritmamu secara alami menghitung sesuatu yang MAKSIMUM.
         Bagaimana kamu mengubah satu menjadi yang lain?
         Hati-hati dengan tipe data: 2*10^5 tugas dengan denda 10^9.
         Sampel 2 adalah pemeriksaan paling sederhana: tiga tugas yang
         semuanya bertenggat 1.

🎯 Learning Goals:
- [ ] Mengenali kapan bobot TIDAK mematikan greedy
- [ ] Mengubah masalah minimasi menjadi maksimasi
- [ ] Memilih arah heap berdasarkan besaran yang bersaing
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: hitung total denda seluruhnya lebih dulu

    // TODO: maksimalkan denda yang bisa DIHINDARI

    return 0;
}
