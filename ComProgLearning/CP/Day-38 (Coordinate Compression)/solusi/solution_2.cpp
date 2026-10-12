/*
============================================================
✅ Solution 2: Frekuensi Nilai Besar
============================================================
Approach: Kompresi + array frekuensi + verifikasi keberadaan
Complexity: Time O((n + q) log n) | Space O(n)
Key Insight: Kompresi adalah JEMBATAN yang mengubah "nilai sampai 10^9"
             menjadi "indeks 0..m-1", sehingga array frekuensi yang
             semula mustahil menjadi mungkin.

📖 PENJELASAN PENDEKATAN:
1. Kompres array, bangun kamus v berukuran m.
2. freq[m], lalu freq[idx(a[i])]++ untuk semua i.
3. Untuk query x: cari posisi p = lower_bound(v, x) - v.begin().
   VERIFIKASI: kalau p == m atau v[p] != x, berarti x tidak ada -> jawab 0.

⚠️ VERIFIKASI ITU WAJIB, dan inilah inti soal ini.
   lower_bound tidak mengembalikan "tidak ditemukan". Ia mengembalikan
   posisi TEMPAT x SEHARUSNYA disisipkan agar urutan tetap terjaga.
   Contoh: v = [1, 4, 9], query x = 5 -> lower_bound mengembalikan indeks 2,
   yaitu posisi nilai 9. Kalau kamu langsung membaca freq[2], kamu akan
   menjawab "berapa kali 9 muncul" untuk pertanyaan tentang 5.
   Bug ini tidak pernah crash dan sering lolos sampel. Selalu verifikasi.

PENDEKATAN ALTERNATIF YANG JUGA BENAR:
   Masukkan seluruh nilai query ke dalam kamus SEBELUM bangun(). Dengan
   begitu setiap query dijamin ada, dan verifikasi tidak diperlukan.
   Ini pola "kumpulkan dulu, kompres belakangan" yang wajib dipakai kalau
   query bukan sekadar membaca frekuensi, melainkan memperbarui struktur.

🔄 ALTERNATIVE APPROACHES:
- map<ll,int> freq langsung: jauh lebih pendek, O((n+q) log n) juga.
  Untuk soal SESEDERHANA ini, map memang pilihan yang wajar.
  Kompresi baru benar-benar menang ketika struktur datanya diakses berkali-kali
  setelahnya (BIT, segment tree, DP) -- di situ konstanta map terasa mahal.
- unordered_map: O(1) rata-rata tetapi bisa di-hack di Codeforces.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;
    vector<ll> a(n);
    for (ll& x : a) cin >> x;

    vector<ll> v = a;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int m = v.size();

    vector<int> freq(m, 0);
    for (ll x : a)
        freq[lower_bound(v.begin(), v.end(), x) - v.begin()]++;

    string out;
    while (q--) {
        ll x;
        cin >> x;
        int p = int(lower_bound(v.begin(), v.end(), x) - v.begin());
        int jawab = (p < m && v[p] == x) ? freq[p] : 0;   // VERIFIKASI
        out += to_string(jawab);
        out += '\n';
    }
    cout << out;

    return 0;
}
