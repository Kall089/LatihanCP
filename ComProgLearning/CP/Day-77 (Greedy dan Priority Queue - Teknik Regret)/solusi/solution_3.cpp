/*
============================================================
✅ SOLUSI Exercise 3: Mengisi Bahan Bakar
============================================================
Difficulty: Medium | Kompleksitas: O(n log n)

── IDE UTAMA: MENUNDA KEPUTUSAN ────────────────────────────
Jangan pernah mengisi saat melewati pom. Catat saja pom itu
sebagai "kupon" yang bisa ditebus kapan saja nanti.
Saat bahan bakar habis, tebus kupon TERBESAR yang sudah
terkumpul.

── KENAPA MENEBUS KUPON LAMA ITU SAH ───────────────────────
Pertanyaan yang wajar: "bukankah pom itu sudah terlewat?"

Secara matematis, KAPAN bahan bakar ditambahkan ke tangki
tidak mengubah apakah kita bisa mencapai pom tersebut — kita
sudah membuktikannya dengan benar-benar sampai di sana.
Menambahkannya "secara retroaktif" hanya menggeser catatan
pembukuan, bukan kelayakan fisiknya.

Yang berubah adalah INFORMASI: saat berada di pom, kita belum
tahu apakah kita akan membutuhkannya. Menunda keputusan sampai
saat kritis membuat kita memilih dengan informasi lengkap.

── KENAPA MENEBUS YANG TERBESAR ────────────────────────────
Exchange argument. Andaikan solusi optimal, pada saat kritis
pertama, menebus kupon x padahal ada kupon y > x yang tersedia.
Tukar: pakai y alih-alih x. Bahan bakar di setiap titik
sesudahnya menjadi lebih besar atau sama, sehingga setiap
pemberhentian berikutnya yang sah tetap sah. Jumlah
pemberhentian tidak bertambah. ∎

── STRUKTUR LOOP ───────────────────────────────────────────
  1. kumpulkan kupon dari semua pom dengan posisi <= jangkauan
  2. majukan posisi sejauh bahan bakar mengizinkan
  3. kalau sudah sampai, selesai
  4. kalau tidak ada kupon, mustahil
  5. tebus kupon terbesar, ulangi

Penunjuk pengumpul kupon hanya MAJU karena jangkauan hanya
membesar. Total O(n log n).

── JEBAKAN ─────────────────────────────────────────────────
1. Mengisi bahan bakar saat melewati pom (tidak menunda).
2. Lupa kasus -1. Tanpa itu, loopnya berputar selamanya.
3. Lupa kasus 0 pemberhentian (sampel 3): tangki awal sudah
   cukup. Loop di bawah menanganinya karena syarat
   'posisi >= D' diperiksa sebelum menebus kupon.
4. Mengumpulkan kupon SETELAH memajukan posisi. Harus sebelum,
   agar pom tepat di batas jangkauan ikut terkumpul.
5. Lupa long long: D dan b sampai 10^9.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; ll D, S;
    if (!(cin >> n >> D >> S)) return 0;
    vector<pair<ll, ll>> pom(n);                // (posisi, liter)
    for (auto& [p, b] : pom) cin >> p >> b;

    sort(pom.begin(), pom.end());               // posisi MENAIK

    priority_queue<ll> pq;                      // MAX-heap kupon
    ll bahan = S, posisi = 0;
    int hit = 0, i = 0;

    while (posisi < D) {
        // kumpulkan kupon dari pom yang bisa dicapai — SEBELUM maju
        while (i < n && pom[i].first <= posisi + bahan) {
            pq.push(pom[i].second);
            i++;
        }
        posisi += bahan;                        // maju sejauh mungkin
        bahan = 0;
        if (posisi >= D) break;                 // sudah sampai
        if (pq.empty()) { cout << -1 << '\n'; return 0; }
        bahan = pq.top(); pq.pop();             // tebus kupon TERBESAR
        hit++;
    }

    cout << hit << '\n';
    return 0;
}
