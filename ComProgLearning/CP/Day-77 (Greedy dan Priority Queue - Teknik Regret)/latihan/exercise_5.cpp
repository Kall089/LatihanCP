/*
============================================================
🏋️ Exercise 5: Kursus dengan Bobot
============================================================
Day: 77 | Difficulty: Hard
Topic: Regret ketika dua besaran berbeda bersaing
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N kursus. Kursus ke-i memerlukan t[i] hari, harus SELESAI paling lambat
hari d[i], dan memberi nilai v[i].
Kamu hanya bisa mengambil satu kursus pada satu waktu.
Cari TOTAL NILAI MAKSIMUM dari kursus-kursus yang bisa kamu selesaikan.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: t[i], d[i], dan v[i]

📤 OUTPUT FORMAT:
- Satu bilangan: total nilai maksimum

📏 CONSTRAINTS:
- 1 <= N <= 2000
- 1 <= t[i] <= 1000
- 1 <= d[i] <= 2 * 10^6
- 1 <= v[i] <= 10^9

📎 SAMPLE INPUT 1:
3
2 5 10
3 6 20
4 7 5

📎 SAMPLE OUTPUT 1:
30

📎 SAMPLE INPUT 2:
2
5 5 1
5 5 100

📎 SAMPLE OUTPUT 2:
100

💡 HINT: Godaan terbesar: pakai regret seperti Exercise 1, tetapi batalkan
         kursus dengan NILAI terkecil. Uji ide itu dengan brute force pada
         masukan kecil sebelum mempercayainya — kamu akan menemukan bahwa
         ia gagal.
         Kenapa gagal? Karena sekarang ada DUA besaran yang bersaing: waktu
         yang dimakan dan nilai yang diberikan. Membatalkan kursus bernilai
         kecil belum tentu membebaskan waktu, dan membatalkan kursus yang
         lama belum tentu mengorbankan sedikit nilai.
         Argumen dominasi keadaan dari teori juga runtuh: dua keadaan
         dengan jumlah kursus sama tidak lagi bisa dibandingkan hanya lewat
         waktu terpakai.
         Perhatikan batasannya: N sampai 2000, t sampai 1000. Kalikan
         keduanya. Angka yang kamu dapat adalah petunjuk kuat tentang
         pendekatan mana yang dimaksud.
         Setelah kamu mengenali pendekatannya, pertanyaan berikutnya adalah
         urutan pemrosesan. Apakah urutan masih penting? Petunjuk: ya,
         sangat. Pikirkan kenapa memproses menurut tenggat menaik membuat
         perumusannya benar.
         Sampel 2 menguji dua kursus yang tidak mungkin diambil bersamaan.

🎯 Learning Goals:
- [ ] Mengenali kapan regret berhenti bekerja
- [ ] Membaca batasan sebagai petunjuk peralihan ke DP
- [ ] Menyadari bahwa urutan pemrosesan tetap penting pada DP
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: uji dulu apakah regret bekerja di sini

    // TODO: kalau tidak, baca batasan dan pilih pendekatan lain

    return 0;
}
