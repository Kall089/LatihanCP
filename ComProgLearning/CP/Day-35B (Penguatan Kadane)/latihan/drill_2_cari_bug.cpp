/*
============================================================
🐛 Drill 2: Enam Kadane yang Rusak
============================================================
Day: 35B | Target: 30 menit
Tujuan: melatih mata, bukan jari.

CARA MAIN
  1. BACA dulu keenam fungsi di bawah. Untuk masing-masing, tulis di kertas:
       - apa bug-nya
       - CONTOH ARRAY yang membuatnya salah
     Jangan compile dulu. Ini bagian yang melatih pemahaman.
  2. Baru compile & jalankan. Stress tester akan mencari counterexample
     terkecil untuk tiap fungsi.
  3. Bandingkan tebakanmu dengan hasilnya, lalu buka solusi/drill_2_kunci.md

  g++ -std=c++17 -O2 -o drill_2 drill_2_cari_bug.cpp && ./drill_2

ATURAN SOAL YANG BENAR
  Subarray TIDAK boleh kosong. Elemen boleh negatif.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ─── REFERENSI BENAR (O(n^2), dipakai sebagai pembanding) ───
ll benar(const vector<ll>& a) {
    ll best = LLONG_MIN;
    for (size_t i = 0; i < a.size(); i++) {
        ll s = 0;
        for (size_t j = i; j < a.size(); j++) {
            s += a[j];
            best = max(best, s);
        }
    }
    return best;
}

// ─── BUG 1 ──────────────────────────────────────────────
ll bug1(const vector<ll>& a) {
    ll best = 0, cur = 0;
    for (ll x : a) {
        cur = max(x, cur + x);
        best = max(best, cur);
    }
    return best;
}

// ─── BUG 2 ──────────────────────────────────────────────
ll bug2(const vector<ll>& a) {
    ll best = LLONG_MIN, cur = 0;
    for (ll x : a) {
        best = max(best, cur);
        cur = max(x, cur + x);
    }
    return best;
}

// ─── BUG 3 ──────────────────────────────────────────────
ll bug3(const vector<ll>& a) {
    ll best = LLONG_MIN, cur = 0;
    for (ll x : a) {
        if (cur < 0) cur = 0;
        cur += x;
        best = max(best, cur);
    }
    if (best < 0) best = 0;   // <- baris ini "mengamankan" kasus negatif
    return best;
}

// ─── BUG 4 ──────────────────────────────────────────────
ll bug4(const vector<ll>& a) {
    ll best = a[0], cur = a[0];
    for (size_t i = 0; i < a.size(); i++) {   // perhatikan batas awalnya
        cur = max(a[i], cur + a[i]);
        best = max(best, cur);
    }
    return best;
}

// ─── BUG 5 ── versi prefix minimum ──────────────────────
ll bug5(const vector<ll>& a) {
    ll best = LLONG_MIN, pre = 0, minPre = 0;
    for (ll x : a) {
        pre += x;
        minPre = min(minPre, pre);       // perhatikan URUTAN dua baris ini
        best = max(best, pre - minPre);
    }
    return best;
}

// ─── BUG 6 ── tipe data ─────────────────────────────────
ll bug6(const vector<ll>& a) {
    int best = INT_MIN, cur = 0;         // perhatikan tipe variabelnya
    for (ll x : a) {
        cur = max((int)x, cur + (int)x);
        best = max(best, cur);
    }
    return best;
}

// ─── STRESS TESTER ──────────────────────────────────────
int main() {
    struct Kandidat { const char* nama; ll (*f)(const vector<ll>&); };
    vector<Kandidat> daftar = {
        {"bug1", bug1}, {"bug2", bug2}, {"bug3", bug3},
        {"bug4", bug4}, {"bug5", bug5}, {"bug6", bug6},
    };

    mt19937 rng(12345);
    // kandidat counterexample terkecil per fungsi
    vector<vector<ll>> ce(daftar.size());

    for (int iter = 0; iter < 200000; iter++) {
        int n = 1 + rng() % 6;
        // rentang kecil supaya counterexample-nya mudah dibaca manusia
        vector<ll> a(n);
        for (int i = 0; i < n; i++) a[i] = (ll)(rng() % 21) - 10;

        ll ref = benar(a);
        for (size_t k = 0; k < daftar.size(); k++) {
            if (daftar[k].f(a) != ref) {
                if (ce[k].empty() || a.size() < ce[k].size()) ce[k] = a;
            }
        }
    }

    cout << "=== Counterexample terkecil (nilai kecil) ===\n\n";
    for (size_t k = 0; k < daftar.size(); k++) {
        cout << daftar[k].nama << " : ";
        if (ce[k].empty()) {
            cout << "tidak ketemu pada rentang kecil "
                 << "(coba pikirkan: butuh angka SEBESAR apa?)\n";
        } else {
            cout << "a = [";
            for (size_t i = 0; i < ce[k].size(); i++)
                cout << ce[k][i] << (i + 1 < ce[k].size() ? ", " : "");
            cout << "]  benar=" << benar(ce[k])
                 << "  dapat=" << daftar[k].f(ce[k]) << "\n";
        }
    }

    cout << "\nCatatan: satu fungsi sengaja TIDAK akan gagal pada rentang ini.\n"
            "Cari tahu kenapa, dan buat sendiri array yang mematahkannya.\n";
    return 0;
}
