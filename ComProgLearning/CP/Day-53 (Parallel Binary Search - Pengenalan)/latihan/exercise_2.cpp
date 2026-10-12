/*
============================================================
🏋️ Exercise 2: Kapan Posisi Mencapai Target
============================================================
Day: 53 | Difficulty: Medium
Topic: Parallel binary search dasar
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada M ember yang berjajar, semuanya mula-mula kosong.
Terjadi N kejadian secara berurutan. Kejadian ke-t menuangkan v[t] liter air
ke SETIAP ember pada rentang posisi [l[t], r[t]].
Ada Q pertanyaan. Pertanyaan ke-i berisi posisi p[i] dan target T[i], dan
kamu harus menjawab pada KEJADIAN KEBERAPA isi ember ke-p[i] pertama kali
mencapai setidaknya T[i]. Cetak -1 kalau tidak pernah tercapai.
Berbeda dari Exercise 1, di sini setiap pertanyaan memeriksa POSISI YANG
BERBEDA, sehingga tidak ada satu besaran global yang bisa diurutkan.

📥 INPUT FORMAT:
- Baris pertama: M, N, dan Q
- N baris berikutnya: l[t], r[t], v[t]
- Q baris berikutnya: p[i] dan T[i]

📤 OUTPUT FORMAT:
- Q baris, masing-masing satu bilangan

📏 CONSTRAINTS:
- 1 <= M, N, Q <= 2 * 10^5
- 1 <= l[t] <= r[t] <= M
- 1 <= v[t] <= 10^9
- 1 <= T[i] <= 10^18

📎 SAMPLE INPUT 1:
5 4 3
1 3 2
2 5 3
1 5 1
4 5 10
2 5
5 12
1 100

📎 SAMPLE OUTPUT 1:
2
4
-1

💡 HINT: Setiap pertanyaan sendirian adalah binary search biasa: kalau isi
         ember sudah mencapai target pada kejadian ke-t, ia juga sudah
         mencapainya pada t+1 (karena air hanya bertambah).
         Masalahnya, untuk MENGUJI satu tebakan kamu harus menerapkan
         seluruh kejadian sampai tebakan itu — dan mengulanginya untuk
         setiap pertanyaan terlalu lambat.
         Idenya: jalankan seluruh binary search BERBARENGAN. Pada setiap
         putaran, kelompokkan pertanyaan berdasarkan tebakan tengahnya, lalu
         lakukan SATU sapuan yang melayani semuanya.
         Peringatan besar: struktur datamu harus dikembalikan ke keadaan
         kosong di AWAL SETIAP PUTARAN. Melupakannya menghasilkan bug yang
         sangat membingungkan karena putaran pertama tetap benar.
         Untuk struktur datanya, kamu butuh yang mendukung penambahan pada
         RENTANG dan pembacaan pada SATU TITIK, keduanya cepat.

🎯 Learning Goals:
- [ ] Menulis kerangka parallel binary search
- [ ] Memilih struktur data yang tepat (update rentang, baca titik)
- [ ] Tidak lupa me-reset struktur data
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: lo[i] = 1, hi[i] = n+1 (n+1 berarti "tidak pernah")

    // TODO: ulangi: isi bucket, RESET struktur, sapu t = 1..n

    // TODO: untuk tiap i di bucket[t], perbarui lo[i] atau hi[i]

    return 0;
}
