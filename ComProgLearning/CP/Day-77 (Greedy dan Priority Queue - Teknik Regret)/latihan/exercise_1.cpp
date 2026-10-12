/*
============================================================
🏋️ Exercise 1: Mengambil Kursus
============================================================
Day: 77 | Difficulty: Easy
Topic: Regret dasar (deadline + durasi)
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N kursus. Kursus ke-i memerlukan t[i] hari untuk diselesaikan dan harus
SELESAI paling lambat pada hari d[i], dihitung dari hari ke-0.
Kamu hanya bisa mengambil satu kursus pada satu waktu, dan sekali dimulai
sebuah kursus harus diselesaikan tanpa jeda.
Cari JUMLAH KURSUS MAKSIMUM yang bisa kamu selesaikan.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: t[i] dan d[i]

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah kursus maksimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= t[i] <= 10^4
- 1 <= d[i] <= 10^9

📎 SAMPLE INPUT 1:
4
100 200
200 1300
1000 1250
2000 3200

📎 SAMPLE OUTPUT 1:
3

📎 SAMPLE INPUT 2:
2
5 5
4 6

📎 SAMPLE OUTPUT 2:
1

📎 SAMPLE INPUT 3:
5
2 5
2 6
1 7
3 9
100 100

📎 SAMPLE OUTPUT 3:
4

💡 HINT: Naluri pertama: urutkan menurut durasi, ambil yang terpendek dulu.
         Uji itu pada sampel 1. Kamu mungkin mendapat jawaban yang benar
         secara kebetulan — jadi ujilah juga pada sampel 3.
         Pendekatan yang benar memproses kursus dalam urutan tertentu, lalu
         mengambil SEMUANYA secara serakah. Ketika total waktu melewati
         tenggat kursus yang sedang diproses, kamu membatalkan satu kursus
         yang sudah diambil.
         Urutan pemrosesan mana yang membuat argumen ini sah? Petunjuk:
         kamu ingin batasannya makin KETAT seiring berjalan, bukan makin
         longgar.
         Kursus mana yang dibatalkan? Kamu ingin membebaskan waktu
         sebanyak-banyaknya dengan mengorbankan sesedikit mungkin kursus.
         Perhatikan bahwa kursus yang dibatalkan BISA JADI kursus yang baru
         saja kamu masukkan. Itu bukan kesalahan — itu justru berarti
         menolak kursus itu memang pilihan terbaik.
         Sampel 3 dibuat khusus untuk menguji hal ini.

🎯 Learning Goals:
- [ ] Memahami pola ambil-dulu-batalkan-kemudian
- [ ] Menentukan urutan pemrosesan yang membuat regret sah
- [ ] Menyadari bahwa elemen yang baru masuk boleh dibatalkan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: urutkan agar batasan makin ketat

    // TODO: ambil semua; saat melanggar, batalkan yang terburuk

    return 0;
}
