/*
============================================================
✅ Solution 6: Gabungkan K Barisan
============================================================
Approach: Min-heap berisi K kandidat terdepan
Complexity: Time O(N log K) | Space O(K)
Key Insight: Elemen terkecil yang belum dikeluarkan pasti berada di antara
             K elemen TERDEPAN dari masing-masing barisan. Jadi kita tidak
             perlu melihat seluruh N elemen setiap langkah -- cukup K
             kandidat, dan heap memberi minimum di antaranya dalam O(log K).

📖 PENJELASAN PENDEKATAN:
1. Masukkan elemen pertama dari setiap barisan yang TIDAK KOSONG ke heap,
   beserta informasi barisan mana dan indeks ke berapa.
2. Berulang kali: keluarkan minimum, tulis ke hasil, lalu masukkan
   PENERUS dari barisan yang sama (kalau masih ada).
3. Selesai ketika heap kosong.

KENAPA O(N log K): setiap elemen masuk dan keluar heap tepat sekali,
dan heap tidak pernah berisi lebih dari K elemen.
Bandingkan dengan "gabung satu per satu": barisan hasil tumbuh terus,
sehingga elemen awal disalin berulang kali -> O(N*K). Untuk N = 10^5 dan
K = 10^4 itu 10^9 -- TLE.

⚠️ BARISAN KOSONG harus dilewati saat inisialisasi. Kalau kamu langsung
   memasukkan arr[i][0] tanpa memeriksa, itu akses di luar batas.
   Sampel 2 memang ditaruh untuk menguji ini.

⚠️ SIMPAN INDEKS BARISAN, bukan hanya nilainya. Tanpa itu kamu tidak tahu
   dari barisan mana harus mengambil penerusnya.

⚠️ priority_queue di C++ secara default adalah MAX-heap. Untuk min-heap
   kamu perlu greater<> sebagai komparator ketiga. Lupa ini menghasilkan
   keluaran terurut MENURUN -- kesalahan yang sangat sering terjadi.

ALTERNATIF YANG SAMA BAIKNYA -- DIVIDE AND CONQUER:
   Gabungkan barisan berpasangan (1&2, 3&4, ...), lalu gabungkan hasilnya
   berpasangan lagi, dan seterusnya. Setelah log K putaran hanya tersisa
   satu barisan. Setiap putaran menyentuh N elemen -> O(N log K) juga,
   tanpa heap sama sekali. Untuk sebagian orang ini lebih mudah ditulis,
   dan konstantanya sering lebih kecil karena penggabungan dua array
   berurutan sangat ramah cache.

🔄 ALTERNATIVE APPROACHES:
- Gabung semua lalu std::sort: O(N log N). Untuk K kecil ini sering
  justru LEBIH CEPAT dalam praktik karena std::sort sangat teroptimasi.
  Jangan meremehkan pendekatan sederhana.
- Divide and conquer berpasangan: O(N log K), tanpa heap.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int K;
    cin >> K;
    vector<vector<int>> arr(K);
    for (int i = 0; i < K; i++) {
        int L;
        cin >> L;
        arr[i].resize(L);
        for (int& x : arr[i]) cin >> x;
    }

    // {nilai, indeks barisan, indeks di dalam barisan}
    // greater<> -> MIN-heap (default priority_queue adalah MAX-heap)
    priority_queue<array<int, 3>, vector<array<int, 3>>, greater<>> pq;
    for (int i = 0; i < K; i++)
        if (!arr[i].empty()) pq.push({arr[i][0], i, 0});   // lewati yang KOSONG

    string out;
    bool pertama = true;
    while (!pq.empty()) {
        array<int, 3> t = pq.top();
        pq.pop();

        if (!pertama) out += ' ';
        out += to_string(t[0]);
        pertama = false;

        int ai = t[1], idx = t[2];
        if (idx + 1 < (int)arr[ai].size())
            pq.push({arr[ai][idx + 1], ai, idx + 1});
    }
    out += '\n';
    cout << out;

    return 0;
}
