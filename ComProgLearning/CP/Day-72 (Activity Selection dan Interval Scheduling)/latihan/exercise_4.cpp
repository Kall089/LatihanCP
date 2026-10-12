/*
============================================================
🏋️ Exercise 4: Kelas dengan Dua Ruangan
============================================================
Day: 72 | Difficulty: Medium
Topic: Activity selection dengan dua sumber daya
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N kelas, kelas ke-i berlangsung pada [l[i], r[i]) (setengah terbuka:
kelas boleh mulai tepat saat kelas lain selesai).
Kamu punya DUA ruangan. Setiap ruangan hanya bisa menjalankan satu kelas
pada satu waktu, dan sebuah kelas hanya boleh ditempatkan di salah satu
ruangan (tidak boleh dipecah).
Cari JUMLAH KELAS MAKSIMUM yang bisa dijalankan.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: l[i] dan r[i]

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah kelas maksimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= l[i] < r[i] <= 10^9

📎 SAMPLE INPUT 1:
4
1 4
2 5
7 9
3 6

📎 SAMPLE OUTPUT 1:
3

📎 SAMPLE INPUT 2:
3
1 10
1 10
1 10

📎 SAMPLE OUTPUT 2:
2

💡 HINT: Naluri pertama: jalankan algoritma Exercise 1, buang yang terpilih,
         lalu jalankan lagi untuk ruangan kedua. Uji ide itu pada sampel 1
         sebelum mempercayainya — kamu mungkin menemukan bahwa hasilnya
         kurang.
         Pendekatan yang benar tetap mengurutkan menurut waktu selesai,
         tetapi keadaan yang kamu simpan bukan lagi satu angka melainkan
         DUA angka.
         Ketika sebuah kelas muat di kedua ruangan, ruangan mana yang
         sebaiknya kamu pakai? Pikirkan mana yang lebih "berharga" untuk
         disisakan.
         Petunjuk terakhir: pakai ruangan yang waktu bebasnya PALING AKHIR
         di antara yang muat, dan buktikan sendiri kenapa itu tidak pernah
         merugikan.

🎯 Learning Goals:
- [ ] Memperluas greedy interval ke dua sumber daya
- [ ] Menyadari bahwa "jalankan dua kali" tidak selalu benar
- [ ] Memilih sumber daya mana yang dipakai secara sadar
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: urutkan menurut waktu selesai

    // TODO: simpan DUA waktu bebas; pilih yang mana secara sadar

    return 0;
}
