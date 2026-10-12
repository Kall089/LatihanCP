/*
============================================================
🏋️ Exercise 6: Penjadwalan Tiket
============================================================
Day: 49 | Difficulty: Hard (Contest-level)
Topic: Bound pada multiset dan penghapusan
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah konser menjual N tiket dengan harga masing-masing. Ada M pelanggan
yang datang berurutan, dan pelanggan ke-j punya batas harga b[j].
Setiap pelanggan membeli tiket TERMAHAL yang harganya tidak melebihi
batasnya. Tiket yang sudah dibeli tidak bisa dibeli lagi. Jika tidak ada
tiket yang harganya di bawah atau sama dengan batasnya, pelanggan itu
pulang dengan tangan kosong.
Untuk setiap pelanggan, cetak harga tiket yang ia beli, atau -1 kalau ia
tidak membeli apa pun.

📥 INPUT FORMAT:
- Baris pertama: N dan M
- Baris kedua: N harga tiket
- Baris ketiga: M batas harga pelanggan

📤 OUTPUT FORMAT:
- M baris, masing-masing satu bilangan

📏 CONSTRAINTS:
- 1 <= N, M <= 2 * 10^5
- 1 <= harga, batas <= 10^9

📎 SAMPLE INPUT 1:
5 3
5 3 7 8 5
4 8 3

📎 SAMPLE OUTPUT 1:
3
8
-1

Penjelasan: pelanggan pertama (batas 4) membeli tiket 3. Pelanggan kedua
(batas 8) membeli tiket 8. Pelanggan ketiga (batas 3) tidak menemukan tiket
yang harganya <= 3 karena tiket 3 sudah terjual, sehingga ia pulang.

💡 HINT: Karena tiket dihapus setelah dibeli, array biasa tidak cukup —
         kamu butuh struktur yang mendukung pencarian terurut DAN
         penghapusan, sekaligus mengizinkan harga yang sama muncul
         beberapa kali.
         Untuk mencari "termahal yang <= batas", perhatikan bound mana yang
         memberi posisi tepat SETELAH kandidatmu, lalu mundur satu langkah.
         Satu peringatan besar: pada struktur berbasis pohon, ada cara
         memanggil pencarian yang terlihat benar dan berhasil dikompilasi
         tetapi berjalan LINIER. Pastikan kamu memakai cara yang benar,
         atau kamu akan TLE tanpa tahu sebabnya.
         Peringatan kedua: kalau ada beberapa tiket berharga sama, pastikan
         kamu menghapus TEPAT SATU.

🎯 Learning Goals:
- [ ] Memakai bound pada struktur terurut yang dinamis
- [ ] Mengetahui perbedaan fungsi anggota dan algoritma bebas pada set
- [ ] Menghapus tepat satu salinan dari multiset
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: pilih struktur yang mendukung duplikat dan penghapusan

    // TODO: untuk tiap pelanggan, cari kandidat lalu mundur satu

    // TODO: hapus TEPAT SATU salinan

    return 0;
}
