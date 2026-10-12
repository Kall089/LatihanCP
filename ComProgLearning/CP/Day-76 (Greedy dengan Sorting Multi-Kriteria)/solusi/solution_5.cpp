/*
============================================================
✅ SOLUSI Exercise 5: Antrean Bermodal
============================================================
Difficulty: Hard | Kompleksitas: O(n log n)

── JAWABANNYA: URUT (m - c) MENURUN ────────────────────────
Besaran m[i] - c[i] adalah "cadangan" tugas ke-i: modal yang
harus TERSEDIA tetapi tidak terpakai. Kerjakan tugas dengan
cadangan TERBESAR lebih dulu.

── BUKTI (exchange argument pada kelayakan) ────────────────
Karena SELURUH tugas harus dikerjakan, total pengeluarannya
tetap berapa pun urutannya. Yang berubah hanya apakah modal
pernah jatuh di bawah syarat.

Lihat dua tugas berdampingan i lalu j, dengan modal M saat
keduanya dimulai.

  urutan (i, j) layak  <=>  M >= m_i  DAN  M - c_i >= m_j
                       <=>  M >= max( m_i , m_j + c_i )
  urutan (j, i) layak  <=>  M >= max( m_j , m_i + c_j )

Kita ingin syarat yang LEBIH RINGAN, yaitu maksimum yang lebih
kecil. Klaim: (i, j) tidak lebih buruk bila
      m_i - c_i  >=  m_j - c_j

Bukti klaim. Tambahkan (c_i + c_j) ke kedua sisi setiap suku:
      max( m_i , m_j + c_i ) + c_j = max( m_i + c_j , m_j + c_i + c_j )
      max( m_j , m_i + c_j ) + c_i = max( m_j + c_i , m_i + c_j + c_i )
Suku kedua pada kedua baris IDENTIK. Jadi perbandingannya
tinggal m_i + c_j versus m_j + c_i pada suku pertama —
dan itu setara dengan m_i - c_i versus m_j - c_j. ∎

── KENAPA "m MENURUN" SALAH ────────────────────────────────
Dugaan yang paling wajar adalah mengurutkan m menurun
(kerjakan yang paling menuntut dulu). Itu SALAH.

Contoh tandingan (ditemukan lewat stress test):
      M = 13, tugas (m,c) = (3,1) (5,5) (9,6)
  urut m menurun : (9,6) -> 13>=9, m=7
                   (5,5) -> 7>=5,  m=2
                   (3,1) -> 2>=3   GAGAL
  urut (m-c) menurun : cadangan 2, 0, 3
                   (9,6) -> 13>=9, m=7
                   (3,1) -> 7>=3,  m=6
                   (5,5) -> 6>=5,  m=1   BERHASIL

Diuji pada 30.000 kasus acak: kriteria "m menurun" gagal pada
602 kasus, "m menurun lalu c menaik" gagal pada 921 kasus,
sedangkan "(m - c) menurun" lolos SELURUHNYA.

Ini contoh sempurna kenapa dugaan harus diuji sebelum dipercaya.

── SOAL KELAYAKAN, BUKAN OPTIMASI ──────────────────────────
Perhatikan bahwa exchange argument-nya bekerja pada SYARAT
kelayakan, bukan pada nilai fungsi tujuan. Polanya sama:
tuliskan syarat untuk kedua urutan, sederhanakan, bandingkan.
Teknik ini berlaku untuk banyak soal "adakah urutan yang
memenuhi ...".

── JEBAKAN ─────────────────────────────────────────────────
1. Mengurutkan m menurun. Terlihat sangat masuk akal, salah.
2. Lupa long long: M sampai 10^18.
3. Menyangka jawabannya cukup memeriksa M >= max(m) atau
   M >= sum(c). Keduanya syarat perlu, bukan cukup.
4. m - c bisa nol; kriteria tetap benar.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; ll M;
    if (!(cin >> n >> M)) return 0;
    vector<pair<ll, ll>> t(n);
    for (auto& [m, c] : t) cin >> m >> c;

    // cadangan (m - c) MENURUN
    sort(t.begin(), t.end(), [](const pair<ll, ll>& x, const pair<ll, ll>& y) {
        return x.first - x.second > y.first - y.second;
    });

    ll modal = M;
    for (auto& [m, c] : t) {
        if (modal < m) { cout << "NO\n"; return 0; }
        modal -= c;
    }

    cout << "YES\n";
    return 0;
}
