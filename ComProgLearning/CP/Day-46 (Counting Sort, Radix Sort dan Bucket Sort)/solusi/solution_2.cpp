/*
============================================================
✅ Solution 2: Counting Sort yang Stabil
============================================================
Approach: Frekuensi -> prefix sum -> penempatan MUNDUR
Complexity: Time O(n + V) | Space O(n + V)
Key Insight: Versi "cetak berulang" (Solution 1) tidak bisa dipakai kalau
             elemen membawa data terkait, karena ia menulis ULANG nilai
             alih-alih MEMINDAHKAN objek. Versi tiga langkah ini memindahkan
             objek utuh ke posisi finalnya, dan penyapuan MUNDUR membuatnya
             stabil.

📖 TIGA LANGKAH:
1. cnt[kode]++ untuk seluruh barang.
2. cnt[v] += cnt[v-1] -- sekarang cnt[v] berarti "berapa barang berkode <= v",
   yang sama dengan "posisi terakhir + 1 untuk kode v".
3. Sapu MUNDUR dari i = n-1: hasil[--cnt[kode]] = barang.

⚠️ KENAPA MUNDUR MENGHASILKAN STABIL:
   cnt[v] menunjuk ke slot TERAKHIR yang tersedia untuk kode v. Dengan
   menyapu dari belakang, barang yang posisinya paling belakang pada input
   mendapat slot paling belakang. Barang berikutnya (yang lebih depan pada
   input) mendapat slot sebelumnya. Urutan asli terjaga.

   Kalau kamu menyapu MAJU dengan cnt yang sama, barang pertama pada input
   akan mendapat slot TERAKHIR -- urutan di antara kode yang sama menjadi
   TERBALIK. Array tetap terurut berdasarkan kode, sehingga bugnya tidak
   terlihat kalau kamu hanya melihat kodenya. Sampel 1 memang dirancang agar
   perbedaannya terlihat: dengan maju, hasilnya menjadi "ebcad".

⚠️ `--cnt[...]` DENGAN PRE-DECREMENT: pengurangan harus terjadi SEBELUM
   dipakai sebagai indeks, karena cnt menyimpan "posisi terakhir + 1".
   Menulis `cnt[...]--` (post-decrement) memberi indeks yang meleset satu
   dan akan menulis di luar batas pada elemen pertama.

MENGAPA STABILITAS PENTING DI LUAR SOAL INI: radix sort (Exercise 4)
sepenuhnya bergantung padanya. Tanpa counting sort yang stabil, radix sort
menghasilkan sampah.

🔄 ALTERNATIVE APPROACHES:
- std::stable_sort: O(n log n), satu baris. Di kontes ini pilihan wajar.
- std::sort dengan pemecah seri indeks asli: O(n log n), eksplisit.
- Counting sort menang kalau V kecil DAN n besar, seperti di sini.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Barang { int kode; char nama; };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<Barang> a(n);
    for (int i = 0; i < n; i++) cin >> a[i].kode >> a[i].nama;

    const int MAKS = 1000;
    vector<int> cnt(MAKS + 1, 0);

    for (auto& b : a) cnt[b.kode]++;                       // 1. frekuensi
    for (int v = 1; v <= MAKS; v++) cnt[v] += cnt[v - 1];  // 2. prefix sum

    vector<Barang> hasil(n);
    for (int i = n - 1; i >= 0; i--)                       // 3. MUNDUR
        hasil[--cnt[a[i].kode]] = a[i];                    //    pre-decrement

    string out;
    for (auto& b : hasil) out += b.nama;
    out += '\n';
    cout << out;

    return 0;
}
