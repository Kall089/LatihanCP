/*
============================================================
🏋️ Exercise 2: Panjang Kode Huffman
============================================================
Day: 75 | Difficulty: Easy
Topic: Membangun pohon Huffman
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N simbol dengan frekuensi f[i]. Rancang kode biner bebas awalan
(tidak ada kode yang menjadi awalan kode lain) yang meminimalkan total
panjang pesan terkode, yaitu jumlah dari f[i] dikali panjang kode simbol
ke-i.
Cetak PANJANG KODE untuk setiap simbol, sesuai urutan masukan.

📥 INPUT FORMAT:
- Baris pertama: N
- Baris kedua: N frekuensi f[i]

📤 OUTPUT FORMAT:
- Satu baris berisi N bilangan: panjang kode tiap simbol

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 1 <= f[i] <= 10^9

📎 SAMPLE INPUT 1:
6
5 9 12 13 16 45

📎 SAMPLE OUTPUT 1:
4 4 3 3 3 1

📎 SAMPLE INPUT 2:
1
7

📎 SAMPLE OUTPUT 2:
1

💡 HINT: Exercise 1 hanya meminta total biaya, sehingga kamu tidak perlu
         membangun pohonnya. Kali ini kamu butuh strukturnya.
         Berapa banyak simpul yang dimiliki pohon biner penuh dengan N
         daun? Hitung dulu, lalu alokasikan sekaligus.
         Simpan pasangan (nilai, indeks simpul) di dalam heap, bukan nilai
         saja — kamu perlu tahu simpul mana yang digabungkan.
         Setelah pohonnya jadi, telusuri untuk mencatat kedalaman tiap
         daun. Lakukan secara ITERATIF, bukan rekursif: dengan frekuensi
         yang tepat (coba Fibonacci) pohon Huffman bisa sangat miring dan
         rekursimu akan kehabisan stack.
         Sampel 2 adalah kasus tepi. Tidak ada penggabungan sama sekali,
         tetapi kamu tetap butuh satu bit untuk mengirim simbol itu.
         Terakhir, periksa hasilmu sendiri: jumlah f[i] dikali panjang[i]
         harus sama persis dengan jawaban Exercise 1 pada data yang sama.

🎯 Learning Goals:
- [ ] Membangun pohon Huffman secara eksplisit
- [ ] Menelusuri pohon secara iteratif
- [ ] Memverifikasi dengan identitas dua rumus
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: alokasi simpul; heap berisi (nilai, indeks)

    // TODO: bangun pohon

    // TODO: telusuri ITERATIF untuk mencatat kedalaman

    return 0;
}
