/*
============================================================
🏋️ Exercise 3: Mengisi Bahan Bakar
============================================================
Day: 77 | Difficulty: Medium
Topic: Menunda keputusan
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Kamu berkendara sejauh D satuan jarak, dari posisi 0 ke posisi D.
Mobilmu menghabiskan tepat 1 liter per satuan jarak, dan tangkinya berisi
S liter saat berangkat. Kapasitas tangki tidak terbatas.
Ada N pom bensin; pom ke-i berada di posisi p[i] dan menyediakan b[i] liter
(kamu harus mengambil SELURUH b[i] liter kalau berhenti di situ).
Cari JUMLAH PEMBERHENTIAN MINIMUM agar bisa mencapai posisi D, atau -1
kalau tidak mungkin.

📥 INPUT FORMAT:
- Baris pertama: N, D, dan S
- N baris berikutnya: p[i] dan b[i]

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah pemberhentian minimum, atau -1

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= D <= 10^9
- 0 <= S <= 10^9
- 0 < p[i] < D
- 1 <= b[i] <= 10^9

📎 SAMPLE INPUT 1:
4 100 10
10 60
20 30
30 30
60 40

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
1 100 1
10 100

📎 SAMPLE OUTPUT 2:
-1

📎 SAMPLE INPUT 3:
1 10 10
5 5

📎 SAMPLE OUTPUT 3:
0

💡 HINT: Naluri pertama: "isi kalau bahan bakar sudah tipis". Coba tuliskan
         aturannya dengan tepat, dan kamu akan sadar bahwa kamu tidak tahu
         berapa "tipis" itu — karena kamu belum tahu apa yang ada di depan.
         Itu tandanya keputusannya harus DITUNDA.
         Pikirkan begini: kamu tidak wajib memutuskan saat melewati pom.
         Kamu bisa mencatat pom itu sebagai "kupon" yang bisa dipakai
         KAPAN SAJA nanti.
         Kalau nanti bahan bakarmu habis di suatu titik, kupon mana yang
         kamu tebus? Dan kenapa menebus kupon dari pom yang sudah lama
         terlewat tetap sah?
         Petunjuk untuk pertanyaan kedua: secara matematis, kapan bahan
         bakar ditambahkan ke tangki tidak mengubah apakah kamu bisa
         mencapai pom itu. Yang berubah hanya seberapa banyak informasi
         yang kamu punya saat memutuskan.
         Sampel 3 adalah kasus tepi: kamu sudah bisa sampai tanpa berhenti
         sama sekali.

🎯 Learning Goals:
- [ ] Mengenali kapan keputusan sebaiknya ditunda
- [ ] Memakai heap sebagai kumpulan "kupon" yang belum ditebus
- [ ] Menangani kasus tidak mungkin dan kasus tanpa pemberhentian
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: urutkan pom menurut posisi

    // TODO: kumpulkan kupon dari pom yang bisa dicapai

    // TODO: tebus kupon terbaik hanya saat benar-benar butuh

    return 0;
}
