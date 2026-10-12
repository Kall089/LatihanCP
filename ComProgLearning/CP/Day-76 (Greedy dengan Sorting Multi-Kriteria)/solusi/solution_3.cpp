/*
============================================================
✅ SOLUSI Exercise 3: Rentang Bersarang
============================================================
Difficulty: Medium | Kompleksitas: O(n log n)

── MENYERAGAMKAN ARAH PERBANDINGAN ─────────────────────────
Rentang j memuat rentang i bila l_j <= l_i DAN r_i <= r_j.
Arahnya BERLAWANAN pada kedua koordinat, sehingga ini bukan
dominasi biasa.
Pandang rentang sebagai titik (-l, r): syaratnya menjadi
(-l_j) >= (-l_i) dan r_j >= r_i — dominasi biasa.
(Kode di bawah tidak benar-benar menegasikan; ia langsung
mengurutkan dengan arah yang sesuai. Menegasikan berbahaya
kalau nilainya bisa mencapai batas tipe data.)

── SATU PENGURUTAN, DUA SAPUAN ─────────────────────────────
Urutkan l MENAIK, dan saat l seri urutkan r MENURUN.
Dengan urutan itu, untuk elemen pada posisi k:

  semua j SESUDAH k  : l_j >= l_i, dan bila l sama maka r_j <= r_i
                       -> kandidat yang DIMUAT oleh i
  semua j SEBELUM k  : l_j <= l_i, dan bila l sama maka r_j >= r_i
                       -> kandidat yang MEMUAT i

Jadi:
  memuat[i]  = (minimum r di antara elemen SESUDAH k) <= r_i
  termuat[i] = (maksimum r di antara elemen SEBELUM k) >= r_i

Satu sapuan mundur dan satu sapuan maju, dengan pengurutan yang
sama. Rapi.

── LUBANG YANG HARUS DITAMBAL: RENTANG IDENTIK ─────────────
Analisis di atas melewatkan satu kasus. Kalau ada dua rentang
IDENTIK, keduanya saling memuat DAN saling termuat. Tetapi
salah satunya pasti berada sebelum yang lain, sehingga hanya
satu arah yang tertangkap oleh sapuan.

Contoh sampel 2: [5,5] dan [5,5].
  sapuan mundur : elemen pertama melihat r = 5 <= 5  -> memuat = 1
                  elemen kedua tidak punya elemen sesudahnya -> 0
  padahal jawabannya keduanya harus 1.

Solusinya sederhana: hitung berapa kali tiap pasangan (l, r)
muncul. Kalau muncul dua kali atau lebih, kedua penanda
langsung bernilai 1.

Bug ini adalah contoh sempurna tema hari ini: ia HANYA muncul
ketika ada nilai berulang, dan tidak akan pernah tertangkap
oleh generator dengan koordinat sampai 10^9.

── JEBAKAN ─────────────────────────────────────────────────
1. Lupa kasus rentang identik.
2. Memakai tie-break r MENAIK — sapuannya menjadi salah untuk
   salah satu dari kedua pertanyaan.
3. Memperbarui min/maks SEBELUM memeriksa, bukan sesudah.
   Urutannya menentukan apakah elemen membandingkan dirinya
   sendiri.
4. Generator berentang besar. Pakai koordinat 1..4.
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
    vector<ll> L(n), R(n);
    for (int i = 0; i < n; i++) cin >> L[i] >> R[i];

    // hitung rentang yang muncul lebih dari sekali
    map<pair<ll, ll>, int> cnt;
    for (int i = 0; i < n; i++) cnt[{L[i], R[i]}]++;

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    // l MENAIK; saat l seri, r MENURUN
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        if (L[a] != L[b]) return L[a] < L[b];
        return R[a] > R[b];
    });

    vector<int> memuat(n, 0), termuat(n, 0);

    // sapuan MUNDUR: minimum r di antara elemen sesudahnya
    {
        ll minR = LLONG_MAX;
        for (int k = n - 1; k >= 0; k--) {
            int i = ord[k];
            if (minR <= R[i]) memuat[i] = 1;
            minR = min(minR, R[i]);            // perbarui SESUDAH memeriksa
        }
    }

    // sapuan MAJU: maksimum r di antara elemen sebelumnya
    {
        ll maxR = LLONG_MIN;
        for (int k = 0; k < n; k++) {
            int i = ord[k];
            if (maxR >= R[i]) termuat[i] = 1;
            maxR = max(maxR, R[i]);            // perbarui SESUDAH memeriksa
        }
    }

    // tambalan: rentang identik saling memuat dan saling termuat
    for (int i = 0; i < n; i++)
        if (cnt[{L[i], R[i]}] >= 2) { memuat[i] = 1; termuat[i] = 1; }

    for (int i = 0; i < n; i++) cout << memuat[i]  << " \n"[i == n - 1];
    for (int i = 0; i < n; i++) cout << termuat[i] << " \n"[i == n - 1];
    return 0;
}
