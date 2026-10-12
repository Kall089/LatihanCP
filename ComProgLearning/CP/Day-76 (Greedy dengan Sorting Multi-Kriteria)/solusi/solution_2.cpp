/*
============================================================
✅ SOLUSI Exercise 2: Titik Pareto
============================================================
Difficulty: Easy | Kompleksitas: O(n log n)

── DEFINISI YANG HARUS TEPAT ───────────────────────────────
Titik i didominasi oleh j bila
      x_j >= x_i  DAN  y_j >= y_i  DAN  minimal satu STRICT.
Konsekuensi penting: dua titik yang IDENTIK tidak saling
mendominasi (tidak ada yang strict), sehingga KEDUANYA
Pareto-optimal. Sampel 2 menguji tepat ini.

── ATURANNYA ───────────────────────────────────────────────
    titik i Pareto-optimal
    <=> y_i maksimum di dalam kelompok ber-x SAMA
        DAN y_i > maksimum y di antara titik ber-x LEBIH BESAR

Perhatikan DUA tanda pembanding yang BERBEDA:
  - di dalam kelompok x sama : seri boleh (y == maksimum kelompok)
  - terhadap x yang lebih besar : STRICT (y > maksimum)

Kenapa berbeda? Terhadap titik ber-x lebih besar, ketidaksamaan
pada x sudah strict, sehingga y yang seri saja sudah cukup
untuk mendominasi. Di dalam kelompok ber-x sama, dibutuhkan y
yang benar-benar lebih besar.

Menyamakan kedua pembanding ini adalah bug klasik, dan ia
HANYA muncul kalau ada koordinat berulang.

── KENAPA MEMPROSES PER KELOMPOK ───────────────────────────
Sapuan naif elemen-per-elemen tidak bisa membedakan "maksimum
dari titik ber-x lebih besar" dan "maksimum termasuk titik
ber-x sama". Dengan memproses kelompok sekaligus, kedua besaran
itu terpisah secara alami: maxBdiKiri hanya diperbarui SETELAH
seluruh kelompok selesai diperiksa.

── GENERATOR STRESS TEST ───────────────────────────────────
Batasi koordinat ke 0..3. Dengan koordinat sampai 10^9, dua
titik tidak akan pernah punya x yang sama, dan seluruh
kesulitan soal ini menghilang — kodemu akan lolos meski salah.

Ini pelajaran umum: generator yang bagus dirancang untuk
MEMECAHKAN kodemu, bukan sekadar "acak saja".

── JEBAKAN ─────────────────────────────────────────────────
1. Menyamakan pembanding dalam-kelompok dan antar-kelompok.
2. Memperbarui maksimum di tengah kelompok.
3. Menganggap titik identik saling mendominasi.
4. Generator berentang besar sehingga bug tak pernah muncul.
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
    vector<pair<ll, ll>> p(n);
    for (auto& [x, y] : p) cin >> x >> y;

    // x MENURUN; saat x seri, y MENURUN
    sort(p.begin(), p.end(), [](const pair<ll, ll>& a, const pair<ll, ll>& b) {
        if (a.first != b.first) return a.first > b.first;
        return a.second > b.second;
    });

    int hasil = 0;
    ll maxYdiKiri = LLONG_MIN;          // maks y dari titik ber-x LEBIH BESAR
    int i = 0;
    while (i < n) {
        int j = i;
        while (j < n && p[j].first == p[i].first) j++;   // kelompok [i, j)
        ll maxYkelompok = p[i].second;                    // sudah terurut menurun
        for (int k = i; k < j; k++)
            if (p[k].second == maxYkelompok && p[k].second > maxYdiKiri) hasil++;
        maxYdiKiri = max(maxYdiKiri, maxYkelompok);       // perbarui SETELAH kelompok
        i = j;
    }

    cout << hasil << '\n';
    return 0;
}
