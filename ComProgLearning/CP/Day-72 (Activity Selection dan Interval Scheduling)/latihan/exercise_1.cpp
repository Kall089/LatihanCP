/*
============================================================
🏋️ Exercise 1: Festival Film
============================================================
Day: 72 | Difficulty: Easy
Topic: Activity selection dasar
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N film di sebuah festival. Film ke-i diputar dari menit a[i] sampai
menit b[i].
Kamu ingin menonton sebanyak mungkin film UTUH. Kamu tidak bisa menonton
dua film yang waktunya beririsan, tetapi kamu BOLEH langsung berpindah ke
film yang mulai tepat saat film sebelumnya selesai.
Cari jumlah film maksimum yang bisa kamu tonton.

📥 INPUT FORMAT:
- Baris pertama: N
- N baris berikutnya: a[i] dan b[i]

📤 OUTPUT FORMAT:
- Satu bilangan: jumlah film maksimum

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= a[i] < b[i] <= 10^9

📎 SAMPLE INPUT 1:
3
3 5
4 9
5 8

📎 SAMPLE OUTPUT 1:
2

📎 SAMPLE INPUT 2:
2
1 10
2 3

📎 SAMPLE OUTPUT 2:
1

💡 HINT: Ada tiga cara mengurutkan yang terasa masuk akal: menurut waktu
         mulai, menurut waktu selesai, dan menurut durasi. Hanya satu yang
         benar.
         Uji ketiganya pada sampel 2 dan pada tiga interval
         [1,10] [9,12] [11,20]. Dua di antaranya akan gugur.
         Untuk yang tersisa, tanyakan pada dirimu: setelah menonton sebuah
         film, apa satu-satunya informasi yang masih kamu butuhkan tentang
         film itu?
         Perhatikan baik-baik kalimat "BOLEH langsung berpindah" — itu
         menentukan apakah syaratmu memakai > atau >=. Sampel 1 ada khusus
         untuk menguji hal ini.

🎯 Learning Goals:
- [ ] Menemukan bahwa kriteria yang benar adalah waktu selesai
- [ ] Membedakan interval tertutup dan setengah terbuka
- [ ] Menyadari bahwa hanya satu variabel keadaan yang perlu disimpan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca interval

    // TODO: urutkan menurut kriteria yang sudah kamu buktikan

    // TODO: sapu sekali sambil menyimpan satu variabel keadaan

    return 0;
}
