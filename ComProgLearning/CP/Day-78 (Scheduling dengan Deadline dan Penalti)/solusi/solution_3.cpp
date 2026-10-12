/*
============================================================
✅ SOLUSI Exercise 3: Penalti Seragam
============================================================
Difficulty: Medium | Kompleksitas: O(n log n)

── KENAPA BOBOT TIDAK MEMATIKAN GREEDY DI SINI ─────────────
Aturan umum: bobot biasanya mematikan greedy, karena
menciptakan DUA besaran yang bersaing (sumber daya yang dimakan
dan nilai yang diberikan).

Yang menyelamatkan soal ini: seluruh durasi SERAGAM (1 satuan).
Setiap tugas memakan sumber daya yang sama persis, sehingga
hanya SATU besaran yang bersaing — bobotnya. Greedy kembali
berlaku.

Bandingkan dengan Exercise 4, di mana durasi bervariasi dan
greedy benar-benar mati.

── MENGUBAH MINIMASI MENJADI MAKSIMASI ─────────────────────
Soal meminta total denda MINIMUM, tetapi kerangka regret secara
alami menghitung sesuatu yang MAKSIMUM.

    total denda minimum = total seluruh denda
                          - denda maksimum yang bisa DIHINDARI

"Denda yang dihindari" adalah bobot tugas-tugas yang berhasil
tepat waktu. Jadi maksimalkan itu, lalu kurangkan.

Trik "hitung komplemennya" ini sangat sering berguna. Kapan pun
soal minimasi terasa canggung, periksa apakah versi maksimasinya
lebih alami.

── ALGORITMA ───────────────────────────────────────────────
Urut tenggat menaik. Ambil setiap tugas. Kalau jumlah tugas
terpilih melebihi tenggat sekarang, buang bobot TERKECIL.

Perhatikan arah heap: MIN-heap, berlawanan dengan Exercise 2.
Alasannya sama dengan Day 77 Pola 2: karena setiap tugas
memakan slot yang sama, "terburuk" berarti bernilai terkecil.

── KENAPA MEMERIKSA pq.size() > d SUDAH CUKUP ──────────────
Klaim: sehimpunan tugas berdurasi 1 dengan tenggat d_i bisa
dijadwalkan tepat waktu semua BILA DAN HANYA BILA, setelah
diurutkan menurut tenggat menaik, berlaku k + 1 <= d_(k) untuk
setiap k.
Arah "bila": jadwalkan tugas ke-k pada slot ke-k.
Ini kasus khusus teorema Hall yang bisa diperiksa dalam satu
sapuan.

── JEBAKAN ─────────────────────────────────────────────────
1. Memakai MAX-heap (menyalin Exercise 2 tanpa berpikir).
2. Lupa mengurangkan dari total. Kamu akan mencetak denda yang
   DIHINDARI, bukan yang dibayar.
3. Lupa long long: 2*10^5 tugas dikali 10^9 = 2*10^14.
4. Membandingkan pq.size() (unsigned) dengan d tanpa cast.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;
    vector<pair<ll, ll>> j(n);                  // (tenggat, denda)
    ll total = 0;
    for (auto& [d, w] : j) { cin >> d >> w; total += w; }

    sort(j.begin(), j.end());                   // tenggat MENAIK

    priority_queue<ll, vector<ll>, greater<ll>> pq;   // MIN-heap denda
    ll dihindari = 0;
    for (auto& [d, w] : j) {
        pq.push(w);
        dihindari += w;
        if ((ll)pq.size() > d) {                // slot tidak cukup
            dihindari -= pq.top();              // buang denda TERKECIL
            pq.pop();
        }
    }

    cout << total - dihindari << '\n';          // komplemennya
    return 0;
}
