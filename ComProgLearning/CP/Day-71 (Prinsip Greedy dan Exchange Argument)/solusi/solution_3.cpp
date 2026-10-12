/*
============================================================
✅ SOLUSI Exercise 3: Membagi Apartemen
============================================================
Difficulty: Medium | Kompleksitas: O(n log n + m log m)

── IDE UTAMA ────────────────────────────────────────────────
Urutkan pelamar dan apartemen. Proses pelamar dari keinginan
TERKECIL, dan berikan padanya apartemen COCOK yang TERKECIL.

── KENAPA BENAR ────────────────────────────────────────────
Misalkan pada urutan terurut, pelamar i (yang paling kecil di
antara yang belum dilayani) bisa menerima apartemen b1 dan b2
dengan b1 < b2. Anggap solusi optimal memberikan b2 kepadanya.

Kasus A: b1 tidak dipakai siapa pun. Tukar — pelamar i tetap
puas (b1 cocok), dan tidak ada yang dirugikan. Jumlah sama.

Kasus B: b1 dipakai pelamar j. Karena i diproses lebih dulu,
a[i] <= a[j]. Kita punya b1 cocok untuk i dan j, dan b2 cocok
untuk i. Apakah b2 cocok untuk j? Ya:
  b2 <= a[i] + K <= a[j] + K   (batas atas terpenuhi)
  b2 >  b1 >= a[j] - K          (batas bawah terpenuhi)
Jadi kita bisa MENUKAR pasangan i↔b1 dan j↔b2. Jumlah pelamar
yang terlayani tidak berubah.

Dalam kedua kasus, ada solusi optimal yang memberikan apartemen
cocok TERKECIL kepada pelamar terkecil. Induksi ke sisanya. ∎

── KENAPA DUA PENUNJUK CUKUP ───────────────────────────────
Karena kedua daftar terurut:
- Kalau b[j] < a[i] - K, apartemen ini terlalu kecil untuk
  pelamar i. Karena a hanya membesar setelah ini, apartemen j
  tidak akan pernah cocok untuk siapa pun lagi → buang, j++.
- Kalau b[j] > a[i] + K, apartemen ini terlalu besar untuk
  pelamar i. Tetapi mungkin cocok untuk pelamar berikutnya
  (yang lebih besar) → jangan buang apartemennya; buang
  PELAMARNYA, i++.
- Selain itu cocok → pasangkan, i++ dan j++.

Kedua penunjuk hanya maju → O(n + m) setelah pengurutan.

── JEBAKAN ─────────────────────────────────────────────────
1. Menukar arah pembuangan (membuang pelamar saat apartemen
   terlalu kecil) → jawaban salah.
2. Memakai pencarian biner + set untuk tiap pelamar juga benar,
   tetapi dua penunjuk lebih sederhana dan lebih cepat.
3. a[i] - K bisa negatif — tidak masalah kalau tipe datanya
   cukup, tetapi jangan memakai unsigned.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    ll k;
    if (!(cin >> n >> m >> k)) return 0;
    vector<ll> a(n), b(m);
    for (ll &x : a) cin >> x;
    for (ll &x : b) cin >> x;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int i = 0, j = 0, hasil = 0;
    while (i < n && j < m) {
        if (b[j] < a[i] - k) {
            j++;              // apartemen terlalu kecil, tidak akan pernah cocok
        } else if (b[j] > a[i] + k) {
            i++;              // pelamar ini tidak bisa dipuaskan sama sekali
        } else {
            hasil++;          // cocok — pasangkan
            i++; j++;
        }
    }

    cout << hasil << '\n';
    return 0;
}
