/*
============================================================
✅ SOLUSI Exercise 4: Modal Bertumbuh
============================================================
Difficulty: Medium | Kompleksitas: O(n log n)

── DUA STRUKTUR, DUA PERAN ─────────────────────────────────
  array terurut : proyek yang BELUM terjangkau, menunggu modal
                  naik. Diurutkan menurut modal minimum menaik.
  max-heap      : proyek yang SUDAH terjangkau, siap dipilih.
                  Diurutkan menurut keuntungan.

Setiap kali modal naik, penunjuk pada array maju dan
memindahkan proyek-proyek baru ke dalam heap.

── KENAPA AMBIL KEUNTUNGAN TERBESAR ────────────────────────
Karena modal tidak pernah berkurang, mengambil proyek dengan
keuntungan terbesar memberikan dua keuntungan sekaligus:
  (1) menambah modal akhir sebanyak-banyaknya
  (2) membuka proyek terjangkau sebanyak-banyaknya untuk
      langkah berikutnya

Formalnya (exchange argument): andaikan solusi optimal pada
langkah pertama mengambil proyek y padahal ada x terjangkau
dengan p_x > p_y. Tukar. Modal setelah langkah pertama menjadi
lebih besar, sehingga himpunan proyek terjangkau pada langkah
berikutnya MEMUAT himpunan semula. Setiap pilihan yang sah pada
solusi optimal tetap sah, dan modal akhirnya lebih besar atau
sama. ∎

Perhatikan bahwa argumen ini mengandalkan p[i] >= 0. Kalau
keuntungan boleh negatif, greedy ini batal.

── PENUNJUK TIDAK PERNAH MUNDUR ────────────────────────────
Modal C hanya membesar, sehingga proyek yang sudah terjangkau
akan selamanya terjangkau. Penunjuk i hanya maju, total O(n).
Kalau kamu me-reset i di setiap iterasi, kompleksitasnya
menjadi O(n * K) dan TLE.

── KASUS BERHENTI LEBIH AWAL ───────────────────────────────
Kalau heap kosong, tidak ada proyek yang terjangkau dan modal
tidak akan pernah naik lagi. Berhenti — melanjutkan hanya
membuang waktu.
Sampel 2 menguji ini: modal 100, proyek termurah butuh 1000.

── POLA UMUM ───────────────────────────────────────────────
"Penunjuk monoton memindahkan elemen dari struktur A ke
struktur B, lalu ambil ekstrem dari B" adalah pola yang sangat
sering muncul. Sudah kamu temui di Day 73 (covering) dan Day 75
(Exercise 6). Kenali bentuknya.

── JEBAKAN ─────────────────────────────────────────────────
1. Me-reset penunjuk di setiap iterasi.
2. Lupa berhenti saat heap kosong -> loop berjalan K kali
   tanpa guna (masih benar, tetapi lambat kalau K besar).
3. Memakai min-heap.
4. Lupa long long: C + K * p bisa mencapai 10^14.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, K; ll C;
    if (!(cin >> n >> K >> C)) return 0;
    vector<pair<ll, ll>> pr(n);                 // (modal minimum, keuntungan)
    for (auto& [m, p] : pr) cin >> m >> p;

    sort(pr.begin(), pr.end());                 // modal minimum MENAIK

    priority_queue<ll> pq;                      // MAX-heap keuntungan terjangkau
    int i = 0;
    for (int t = 0; t < K; t++) {
        // penunjuk hanya MAJU: modal tak pernah berkurang
        while (i < n && pr[i].first <= C) {
            pq.push(pr[i].second);
            i++;
        }
        if (pq.empty()) break;                  // tidak ada yang terjangkau
        C += pq.top();
        pq.pop();
    }

    cout << C << '\n';
    return 0;
}
