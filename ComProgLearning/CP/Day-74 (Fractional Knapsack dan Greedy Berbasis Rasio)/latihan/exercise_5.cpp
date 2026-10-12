/*
============================================================
🏋️ Exercise 5: Rasio Terbaik
============================================================
Day: 74 | Difficulty: Hard
Topic: Fractional programming (binary search on answer)
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N mesin. Mesin ke-i menghasilkan a[i] unit produk dan menghabiskan b[i]
unit energi.
Kamu harus memilih TEPAT K mesin. Efisiensi sebuah pilihan didefinisikan
sebagai total produk dibagi total energi dari mesin-mesin terpilih.
Cari EFISIENSI MAKSIMUM. Cetak dengan enam angka di belakang koma.

📥 INPUT FORMAT:
- Baris pertama: N dan K
- N baris berikutnya: a[i] dan b[i]

📤 OUTPUT FORMAT:
- Satu bilangan real dengan enam angka di belakang koma

📏 CONSTRAINTS:
- 1 <= K <= N <= 10^5
- 1 <= a[i] <= 10^4
- 1 <= b[i] <= 10^4

📎 SAMPLE INPUT 1:
3 2
1 1
2 1
3 4

📎 SAMPLE OUTPUT 1:
1.500000

📎 SAMPLE INPUT 2:
2 2
5 1
1 5

📎 SAMPLE OUTPUT 2:
1.000000

💡 HINT: Naluri pertama: urutkan menurut a[i]/b[i] dan ambil K teratas. Uji
         ide itu pada sampel 1 sebelum mempercayainya. Rasio tiap mesin
         berturut-turut adalah 1, 2, dan 0.75; K teratas memberi apa, dan
         apakah itu jawabannya?
         Rasio sebuah GABUNGAN bukan gabungan sederhana dari rasio-rasio
         individual. Itulah kenapa greedy gagal.
         Pendekatan yang benar: alih-alih mencari jawabannya secara
         langsung, TANYAKAN "apakah bisa mencapai rasio sebesar x?".
         Ubah pertanyaan itu menjadi bentuk yang bisa kamu jawab cepat.
         Petunjuk aljabar: rasio total >= x setara dengan sebuah
         pertidaksamaan yang tidak lagi memuat pembagian. Susun ulang, dan
         kamu akan mendapat penjumlahan atas nilai-nilai per mesin.
         Setelah bentuknya sederhana, jawab pertanyaannya dengan
         pengurutan. Lalu perhatikan bahwa jawabannya monoton terhadap x.
         Untuk presisinya, pakai jumlah iterasi TETAP seperti yang kamu
         pelajari di Day 51, bukan perbandingan dengan epsilon.

🎯 Learning Goals:
- [ ] Menyadari bahwa rasio gabungan tidak bisa di-greedy
- [ ] Mengubah pertanyaan optimasi menjadi pertanyaan kelayakan
- [ ] Menerapkan binary search pada bilangan real dengan aman
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: ubah "rasio >= x" menjadi bentuk tanpa pembagian

    // TODO: fungsi kelayakan untuk x tertentu

    // TODO: binary search dengan iterasi tetap

    return 0;
}
