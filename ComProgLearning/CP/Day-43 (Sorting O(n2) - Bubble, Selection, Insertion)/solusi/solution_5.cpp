/*
============================================================
✅ Solution 5: Data Hampir Terurut
============================================================
Approach: Insertion sort -- O(n + inversi) = O(nK) di sini
Complexity: Time O(nK) | Space O(1)
Key Insight: Kompleksitas insertion sort tidak ditentukan oleh n saja,
             melainkan oleh SEBERAPA JAUH elemen harus digeser. Kalau
             dijamin setiap elemen berjarak paling jauh K dari tempatnya,
             maka setiap penyisipan menggeser paling banyak K langkah,
             sehingga totalnya O(nK) -- bukan O(n^2).

📖 PENJELASAN PENDEKATAN:
1. Insertion sort biasa, tanpa modifikasi apa pun.
2. Analisisnya yang berubah, bukan kodenya.

HITUNGAN BATAS: n = 10^5, K = 100 -> 10^7 operasi. Lolos dengan nyaman.
   Bandingkan kalau tidak ada jaminan K: n^2 = 10^10 -> TLE telak.
   Inilah alasan soal memberi jaminan itu -- jaminan pada constraint adalah
   petunjuk tentang solusi yang diharapkan.

PELAJARAN YANG LEBIH UMUM: biasakan membaca constraint bukan hanya sebagai
"batas", melainkan sebagai PETUNJUK. Angka K <= 100 di soal ini tidak ada
gunanya kecuali kalau solusinya memang memanfaatkan K.

ALTERNATIF O(n log K) DENGAN HEAP:
   Karena setiap elemen berjarak <= K dari tempatnya, elemen terkecil yang
   belum keluar pasti berada di antara K+1 elemen pertama yang belum diproses.
   Jadi: masukkan K+1 elemen pertama ke min-heap, lalu berulang kali
   keluarkan minimumnya dan masukkan elemen berikutnya.

       priority_queue<int, vector<int>, greater<int>> pq;
       for (i = 0; i <= K && i < n; i++) pq.push(a[i]);
       int idx = 0;
       for (i = K+1; i < n; i++) { a[idx++] = pq.top(); pq.pop(); pq.push(a[i]); }
       while (!pq.empty()) { a[idx++] = pq.top(); pq.pop(); }

   O(n log K) mengalahkan O(nK) saat K besar. Untuk K <= 100 keduanya lolos,
   tetapi kalau K bisa mencapai 10^4, hanya versi heap yang selamat.

⚠️ std::sort juga lolos di sini (O(n log n) = 1.7*10^6). Untuk kontes murni,
   memakai std::sort adalah jawaban paling aman. Soal ini ada supaya kamu
   MEMAHAMI bahwa kompleksitas bergantung pada data, bukan supaya kamu
   menghindari sort bawaan.

🔄 ALTERNATIVE APPROACHES:
- std::sort: O(n log n), paling aman dan paling pendek.
- Heap ukuran K+1: O(n log K), optimal saat K jauh lebih kecil dari n.
- Insertion sort: O(nK), menunjukkan poin pedagogis hari ini.
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
    vector<int> a(n);
    for (int& x : a) cin >> x;

    // Insertion sort: pergeseran per elemen dibatasi K, jadi total O(nK)
    for (int i = 1; i < n; i++) {
        int kunci = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > kunci) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = kunci;
    }

    string out;
    for (int i = 0; i < n; i++) {
        out += to_string(a[i]);
        out += (i + 1 == n) ? '\n' : ' ';
    }
    cout << out;

    return 0;
}
