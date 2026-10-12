/*
============================================================
✅ Solution 5: K Titik Terdekat
============================================================
Approach: nth_element dengan komparator kuadrat jarak
Complexity: Time O(n) | Space O(1)
Key Insight: Dua penyederhanaan yang keduanya penting.
             (1) Kita tidak butuh K titik dalam keadaan TERURUT, hanya perlu
                 tahu titik MANA saja -- jadi nth_element (O(n)) cukup,
                 tidak perlu sort (O(n log n)) atau partial_sort.
             (2) Membandingkan jarak sama dengan membandingkan KUADRAT
                 jarak, karena akar kuadrat adalah fungsi monoton naik
                 untuk bilangan non-negatif.

📖 PENJELASAN PENDEKATAN:
1. Simpan setiap titik beserta kuadrat jaraknya: x*x + y*y.
2. nth_element dengan komparator yang membandingkan kuadrat jarak,
   memisahkan K titik terdekat ke bagian depan.
3. Cetak K titik pertama.

⚠️ JANGAN MEMAKAI sqrt(). Tiga alasan:
   1. Akar kuadrat jauh lebih lambat daripada perkalian.
   2. Ia menghasilkan bilangan floating point, yang memperkenalkan
      kesalahan pembulatan -- dua titik yang jaraknya sama persis bisa
      dibandingkan salah.
   3. Ia sama sekali tidak mengubah urutannya.
   Kebiasaan "bandingkan kuadratnya" berlaku untuk hampir semua soal
   geometri yang hanya butuh perbandingan jarak.

⚠️ TIPE DATA UNTUK KUADRAT JARAK: dengan |x|, |y| <= 10^4, kuadrat jaraknya
   paling besar 2 * 10^8 -- masih muat di int. Tetapi kalau koordinatnya
   mencapai 10^9, x*x saja sudah 10^18 dan WAJIB long long.
   Biasakan memakai long long untuk kuadrat jarak; biayanya nol.

⚠️ nth_element MENGUBAH URUTAN. Setelah dipanggil, K titik pertama adalah
   yang terdekat, tetapi urutan di antara mereka tidak terdefinisi. Soal ini
   memang memperbolehkan urutan bebas, sehingga tidak masalah. Kalau soal
   menuntut urutan terurut, pakai partial_sort.

⚠️ TITIK DENGAN JARAK SAMA DI BATAS: kalau titik ke-K dan ke-(K+1)
   jaraknya sama persis, mana yang terpilih bergantung pada implementasi.
   Soal ini secara eksplisit memperbolehkan keduanya. Kalau soal lain
   menuntut aturan tertentu, tambahkan pemecah seri pada komparator.

🔄 ALTERNATIVE APPROACHES:
- sort seluruhnya lalu ambil K pertama: O(n log n). Benar tetapi lebih lambat.
- partial_sort: O(n log K), dipakai kalau butuh K titik TERURUT.
- Max-heap ukuran K: O(n log K) waktu, O(K) ruang. Menang kalau data
  berbentuk aliran atau memori sangat terbatas.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Titik { ll x, y, d2; };

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, K;
    cin >> n >> K;
    vector<Titik> p(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i].x >> p[i].y;
        p[i].d2 = p[i].x * p[i].x + p[i].y * p[i].y;   // KUADRAT, tanpa sqrt
    }

    nth_element(p.begin(), p.begin() + K, p.end(),
                [](const Titik& a, const Titik& b) { return a.d2 < b.d2; });

    string out;
    for (int i = 0; i < K; i++) {
        out += to_string(p[i].x);
        out += ' ';
        out += to_string(p[i].y);
        out += '\n';
    }
    cout << out;

    return 0;
}
