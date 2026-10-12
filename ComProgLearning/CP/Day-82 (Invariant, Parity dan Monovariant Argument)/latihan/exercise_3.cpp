/*
============================================================
🏋️ Exercise 3: Menuang Air
============================================================
Day: 82 | Difficulty: Medium
Topic: FPB sebagai invarian
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N wadah; wadah ke-i saat ini berisi a[i] liter air dan kapasitasnya
tidak terbatas.
Satu operasi memilih dua wadah, lalu memindahkan sejumlah air dari salah
satu ke yang lain, dengan syarat jumlah yang dipindahkan harus membuat SALAH
SATU wadah menjadi kosong atau membuat kedua wadah berisi sama banyak.
Diberikan sebuah target T, tentukan apakah mungkin membuat SALAH SATU wadah
berisi tepat T liter. Cetak "YA" atau "TIDAK".

📥 INPUT FORMAT:
- Baris pertama: N dan T
- Baris kedua: N bilangan a[i]

📤 OUTPUT FORMAT:
- "YA" atau "TIDAK"

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 0 <= T <= 10^18
- 0 <= a[i] <= 10^12

📎 SAMPLE INPUT 1:
2 4
6 10

📎 SAMPLE OUTPUT 1:
YA

📎 SAMPLE INPUT 2:
2 5
6 10

📎 SAMPLE OUTPUT 2:
TIDAK

📎 SAMPLE INPUT 3:
3 7
3 5 9

📎 SAMPLE OUTPUT 3:
YA

💡 HINT: Aturan operasinya terdengar rumit, tetapi jangan terjebak
         mensimulasikannya. Tanyakan dulu: besaran apa yang tidak berubah?
         Perhatikan bahwa memindahkan air antar wadah tidak mengubah total.
         Itu satu invarian, dan ia langsung memberi satu syarat yang jelas.
         Tetapi ada invarian kedua yang jauh lebih tajam. Coba beberapa
         contoh kecil dengan tangan: mulai dari 6 dan 10, nilai apa saja
         yang bisa kamu buat? Tuliskan daftarnya dan cari polanya.
         Kamu akan menemukan bahwa seluruh nilai yang bisa dicapai adalah
         kelipatan dari suatu bilangan tertentu yang bisa dihitung langsung
         dari masukan.
         Bilangan itu adalah sesuatu yang sudah kamu kenal sejak lama, dan
         ia juga merupakan invarian: operasi apa pun tidak mengubahnya.
         Setelah menemukannya, gabungkan dengan syarat pertama tentang
         total.
         Kasus tepi yang wajib diperiksa: T sama dengan 0, dan seluruh
         wadah kosong.
         Waspadai tipe data: a sampai 10^12 dengan 2*10^5 wadah.

🎯 Learning Goals:
- [ ] Menemukan invarian yang lebih tajam daripada yang pertama terlihat
- [ ] Mengenali FPB sebagai invarian pada operasi penjumlahan/pengurangan
- [ ] Menggabungkan beberapa syarat perlu menjadi jawaban
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: invarian pertama yang jelas

    // TODO: invarian kedua yang lebih tajam

    return 0;
}
