/*
============================================================
🏋️ Exercise 5: K Titik Terdekat
============================================================
Day: 45 | Difficulty: Hard
Topic: nth_element dengan komparator kustom
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N titik pada bidang dua dimensi dengan koordinat bilangan bulat,
cari K titik yang PALING DEKAT ke titik asal (0, 0). Jarak yang dipakai
adalah jarak Euclidean biasa.
Cetak K titik itu, masing-masing pada satu baris. Urutan pencetakannya
bebas. Jika ada beberapa titik yang jaraknya sama dan berada tepat di
batas, titik mana pun boleh dipilih.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- N baris berikutnya: masing-masing x dan y

📤 OUTPUT FORMAT:
- K baris, masing-masing dua bilangan

📏 CONSTRAINTS:
- 1 <= K <= N <= 10^5
- -10^4 <= x, y <= 10^4

📎 SAMPLE INPUT 1:
3 2
1 3
-2 2
2 -2

📎 SAMPLE OUTPUT 1:
-2 2
2 -2

💡 HINT: Kamu tidak perlu K titik itu TERURUT, hanya perlu tahu titik
         mana saja. Fungsi apa yang memberi itu dalam waktu linier?
         Untuk membandingkan jarak, JANGAN memakai akar kuadrat: selain
         lambat, ia memperkenalkan kesalahan pembulatan. Membandingkan
         kuadrat jaraknya memberi urutan yang sama persis.
         Perhatikan juga tipe data untuk kuadrat jarak.

🎯 Learning Goals:
- [ ] Memakai nth_element dengan komparator kustom
- [ ] Membandingkan kuadrat jarak alih-alih jarak
- [ ] Menyadari kapan "terurut" tidak diperlukan
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: baca titik

    // TODO: nth_element dengan komparator berdasarkan kuadrat jarak

    // TODO: cetak K pertama

    return 0;
}
