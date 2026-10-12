/*
============================================================
✅ Solution 6: K Terbesar dari Aliran Data
============================================================
Approach: Min-heap berukuran tetap K
Complexity: Time O(n log K) | Space O(K)
Key Insight: Batas memori 16 MB dengan N sampai 10^7 membuat nth_element
             MUSTAHIL -- ia membutuhkan seluruh array di memori (40 MB).
             Ini contoh penting bahwa algoritma "tercepat" tidak selalu
             yang benar; batasan sumber daya ikut menentukan.

📖 PENJELASAN PENDEKATAN:
1. Jaga min-heap yang berisi paling banyak K elemen.
2. Untuk setiap bilangan yang masuk: push, lalu kalau ukurannya melebihi K,
   pop. Yang di-pop selalu yang TERKECIL di antara kandidat.
3. Setelah seluruh data diproses, isi heap tepat K elemen TERBESAR.
4. Keluarkan seluruhnya (menghasilkan urutan menaik), lalu balik untuk
   mendapatkan urutan menurun.

⚠️ MENCARI YANG TERBESAR MEMAKAI MIN-HEAP -- ini terdengar terbalik dan
   memang sering membingungkan. Alasannya: kita perlu tahu siapa kandidat
   TERLEMAH agar bisa membuangnya saat kandidat baru datang. Min-heap
   memberi elemen terkecil di puncak, tepat yang kita butuhkan.
   (Sebaliknya, untuk mencari K TERKECIL kamu memakai MAX-heap.)

⚠️ priority_queue di C++ secara default adalah MAX-heap. Untuk min-heap
   kamu harus menuliskan ketiga parameter templatnya:
       priority_queue<int, vector<int>, greater<int>> pq;
   Melupakan greater<int> menghasilkan jawaban yang salah total dan ini
   kesalahan yang sangat umum.

⚠️ JANGAN MENYIMPAN SELURUH DATA. Baca satu per satu langsung ke dalam
   variabel sementara. Menulis `vector<int> a(n)` lalu membacanya sudah
   melanggar batas memori sebelum satu operasi pun dilakukan.

ANALISIS MEMORI:
   vector<int> berisi 10^7 elemen : 40 MB   -> MLE
   heap berisi 1000 elemen        : 4 KB    -> aman
   Selisihnya empat orde besaran.

ANALISIS WAKTU:
   O(n log K) = 10^7 * log2(1000) ~ 10^7 * 10 = 10^8 operasi heap.
   Ini di ambang batas, sehingga I/O cepat menjadi penting. Perhatikan
   bahwa kebanyakan elemen akan langsung ditolak (push lalu pop) sehingga
   konstanta praktisnya lebih kecil dari perkiraan terburuk.

OPTIMASI YANG BERGUNA: kalau heap sudah penuh dan bilangan baru lebih kecil
dari puncak heap, kita bisa MELEWATINYA tanpa push sama sekali:
    if ((int)pq.size() == K && x <= pq.top()) continue;
Ini menghindari sepasang operasi heap untuk sebagian besar data.

🔄 ALTERNATIVE APPROACHES:
- nth_element: O(n) waktu, tetapi O(n) ruang -> MLE di sini.
- sort: O(n log n) waktu dan O(n) ruang -> MLE.
- Quickselect dengan pembacaan bertahap: rumit dan tidak lebih baik.
- Kalau K sangat besar (mendekati n), heap kehilangan keunggulannya dan
  pendekatan lain perlu dipertimbangkan.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, K;
    cin >> n >> K;

    // MIN-heap: puncaknya adalah kandidat TERLEMAH yang siap dibuang
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;                              // JANGAN simpan seluruh data

        if ((int)pq.size() == K && x <= pq.top()) continue;   // tolak cepat
        pq.push(x);
        if ((int)pq.size() > K) pq.pop();
    }

    vector<int> hasil;
    hasil.reserve(pq.size());
    while (!pq.empty()) { hasil.push_back(pq.top()); pq.pop(); }
    reverse(hasil.begin(), hasil.end());        // menaik -> MENURUN

    string out;
    for (size_t i = 0; i < hasil.size(); i++) {
        out += to_string(hasil[i]);
        out += (i + 1 == hasil.size()) ? '\n' : ' ';
    }
    cout << out;

    return 0;
}
