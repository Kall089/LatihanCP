/*
============================================================
🏋️ Exercise 5: Tenggat dengan Prasyarat
============================================================
Day: 78 | Difficulty: Hard
Topic: Modifikasi tenggat lalu EDF
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N pekerjaan pada satu mesin, dikerjakan satu per satu tanpa jeda mulai
dari waktu 0. Pekerjaan ke-i memerlukan t[i] satuan waktu dan punya tenggat
d[i].
Selain itu ada M aturan prasyarat berupa pasangan (a, b) yang berarti
pekerjaan a harus selesai SEBELUM pekerjaan b dimulai.
Dijamin aturan-aturan itu tidak membentuk siklus.
Susun urutan pengerjaan yang memenuhi seluruh prasyarat sehingga
KETERLAMBATAN TERBESAR menjadi sekecil mungkin, lalu cetak nilai itu.

📥 INPUT FORMAT:
- Baris pertama: N dan M
- N baris berikutnya: t[i] dan d[i]
- M baris berikutnya: a dan b (1-based)

📤 OUTPUT FORMAT:
- Satu bilangan: keterlambatan terbesar minimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 0 <= M <= 2 * 10^5
- 1 <= t[i] <= 10^9
- 1 <= d[i] <= 10^18

📎 SAMPLE INPUT 1:
3 1
3 6
2 8
1 9
2 1

📎 SAMPLE OUTPUT 1:
-1

📎 SAMPLE INPUT 2:
2 0
5 1
5 100

📎 SAMPLE OUTPUT 2:
4

💡 HINT: Naluri pertama: lakukan pengurutan topologis, lalu di antara
         pekerjaan yang siap pilih yang tenggatnya paling awal. Ide itu
         masuk akal tetapi ada cara yang jauh lebih rapi.
         Pikirkan begini: kalau pekerjaan a harus selesai sebelum b, maka
         a sebenarnya punya tenggat yang lebih ketat daripada yang
         tertulis. Seberapa ketat?
         Petunjuk: kalau b harus selesai pada waktu d[b], dan b memerlukan
         t[b] waktu, maka b harus MULAI paling lambat pada d[b] - t[b].
         Apa artinya bagi tenggat a?
         Setelah kamu menurunkan rumusnya, terapkan pada seluruh graf.
         Ke arah mana kamu harus memprosesnya — dari pekerjaan awal ke
         akhir, atau sebaliknya? Pikirkan urutan mana yang menjamin
         informasi sudah lengkap saat kamu memakainya.
         Setelah semua tenggat dimodifikasi, apakah kamu masih perlu
         memikirkan prasyarat sama sekali? Jawabannya mungkin
         mengejutkanmu.
         Teknik "modifikasi masukan lalu jalankan algoritma sederhana"
         ini muncul di banyak soal. Kenali bentuknya.

🎯 Learning Goals:
- [ ] Menurunkan tenggat efektif dari prasyarat
- [ ] Menentukan arah pemrosesan pada graf berarah
- [ ] Mengenali pola "modifikasi lalu pakai algoritma yang sudah ada"
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: turunkan tenggat efektif dari prasyarat

    // TODO: proses graf ke arah yang benar

    // TODO: setelah itu, algoritma apa yang cukup?

    return 0;
}
