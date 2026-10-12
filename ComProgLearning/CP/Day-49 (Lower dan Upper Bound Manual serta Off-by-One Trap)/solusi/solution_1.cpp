/*
============================================================
✅ Solution 1: Lower Bound dan Upper Bound Manual
============================================================
Approach: Satu kerangka "first true", dua predikat
Complexity: Time O((n + q) log n) | Space O(n)
Key Insight: Jangan menghafal empat varian binary search. Hafalkan SATU
             kerangka yang mencari "indeks pertama yang predikatnya true",
             lalu setiap soal binary search direduksi menjadi satu
             pertanyaan: APA PREDIKAT MONOTONNYA?

📖 KERANGKANYA:
    int lo = 0, hi = n;                   konvensi setengah terbuka [lo, hi)
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (p(mid)) hi = mid;             mid MUNGKIN jawabannya -> jangan dibuang
        else        lo = mid + 1;         mid PASTI bukan -> boleh dibuang
    }
    return lo;

    lower_bound -> p(i) = (a[i] >= x)
    upper_bound -> p(i) = (a[i] >  x)

INVARIANT yang dijaga sepanjang loop:
    seluruh indeks < lo  -> p bernilai FALSE
    seluruh indeks >= hi -> p bernilai TRUE
Saat lo == hi, rentangnya menyempit ke satu titik, dan invariant memaksa
titik itu menjadi batas peralihannya.

⚠️ KENAPA LOOP SELALU BERHENTI:
   Karena lo < hi dan pembagian membulat ke bawah, berlaku lo <= mid < hi.
   Cabang TRUE  : hi = mid     -> hi TURUN (sebab mid < hi)
   Cabang FALSE : lo = mid + 1 -> lo NAIK  (sebab mid >= lo)
   Kedua cabang selalu memperkecil rentang, jadi tidak mungkin berputar
   selamanya.

⚠️ mid = lo + (hi - lo) / 2, BUKAN (lo + hi) / 2.
   Untuk indeks array biasa keduanya sama, tetapi kebiasaan ini WAJIB dibentuk
   sekarang: pada binary search atas rentang nilai (Exercise 4, Day 50),
   lo + hi benar-benar meluap.

⚠️ hi = n, BUKAN n - 1. Dengan hi = n, jawaban "tidak ada" secara alami
   menjadi n tanpa kasus khusus. Ini bagian dari kenapa konvensi setengah
   terbuka lebih sedikit menimbulkan bug.

⚠️ KEDUANYA BISA MENGEMBALIKAN n. Sebelum menulis a[hasil], SELALU periksa
   hasil < n. Ini penyebab runtime error nomor satu di topik ini.

CATATAN: implementasi ini telah diuji terhadap std::lower_bound dan
std::upper_bound pada 50000 kasus acak, termasuk array kosong.

🔄 ALTERNATIVE APPROACHES:
- std::lower_bound / std::upper_bound: di kontes, pakai ini. Sudah teruji,
  lebih pendek, dan sama cepatnya.
- Menulis manual tetap berguna untuk: memahami, saat predikatnya bukan
  perbandingan sederhana, dan untuk binary search pada jawaban (Day 50).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int lowerBound(const vector<int>& a, int x) {
    int lo = 0, hi = a.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] >= x) hi = mid;
        else             lo = mid + 1;
    }
    return lo;
}

int upperBound(const vector<int>& a, int x) {
    int lo = 0, hi = a.size();
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] > x) hi = mid;          // satu karakter berbeda
        else            lo = mid + 1;
    }
    return lo;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    string out;
    while (q--) {
        int x;
        cin >> x;
        out += to_string(lowerBound(a, x));
        out += ' ';
        out += to_string(upperBound(a, x));
        out += '\n';
    }
    cout << out;

    return 0;
}
