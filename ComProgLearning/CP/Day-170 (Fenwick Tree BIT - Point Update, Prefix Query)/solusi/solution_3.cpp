/*
============================================================
✅ Solution 3: Berapa yang Lebih Kecil di Kanan
============================================================
Approach: BIT atas nilai terkompresi, simpan hasil per posisi
Complexity: Time O(N log N) | Space O(N)
Key Insight: Ini Exercise 2 yang "dipecah per posisi". Struktur, urutan
             operasi, dan arah penyapuannya SAMA PERSIS; yang berubah hanya
             apa yang kita lakukan dengan hasil query -- disimpan alih-alih
             diakumulasi.

             Kemampuan memberi jawaban PER POSISI inilah keunggulan BIT
             dibandingkan merge sort untuk masalah ini. Merge sort bisa
             menghitung total inversi dengan mudah, tetapi mengaitkan
             hitungan ke posisi aslinya jauh lebih merepotkan karena
             urutannya berubah selama proses.

📖 ALGORITMANYA:
   for (i = n-1 turun ke 0):
       hasil[i] = query(rank(a[i]) - 1)
       update(rank(a[i]), 1)

   Saat memproses posisi i, BIT tepat memuat seluruh elemen pada posisi
   > i. Jadi query memberi persis "berapa elemen di kanan yang lebih kecil".

⚠️ query(rank - 1) UNTUK "LEBIH KECIL KETAT".
   Sampel 2 ([7,7,7]) sengaja menguji ini: seluruh elemen sama, sehingga
   jawabannya harus nol semua.
   Kalau kamu memakai query(rank), setiap elemen akan menghitung kembarannya
   di kanan dan jawabannya menjadi [2, 1, 0] -- salah.
   Satu angka pada batas query menentukan benar atau salah.

⚠️ VARIAN YANG SERING DIMINTA:
     lebih kecil di kanan : sapu kanan, query(rank - 1)      <- soal ini
     lebih besar di kanan : sapu kanan, total - query(rank)
     lebih kecil di kiri  : sapu KIRI,  query(rank - 1)
     lebih besar di kiri  : sapu KIRI,  total - query(rank)
   Keempatnya memakai struktur yang sama; hanya arah dan batas query yang
   berbeda. Menulis salah satu dengan benar berarti kamu bisa menulis
   keempatnya.

⚠️ TIPE DATA: hasil per posisi paling besar n-1, muat di int. Tetapi kalau
   soal meminta TOTALNYA, itu bisa 2*10^10 dan butuh long long.

VERIFIKASI SAMPEL 1 (a = [5,2,6,1], peringkat = [3,2,4,1]):
   i=3 (1): query(0) = 0        hasil[3]=0   update(1)
   i=2 (6): query(3) = 1        hasil[2]=1   update(4)   [hanya 1]
   i=1 (2): query(1) = 1        hasil[1]=1   update(2)   [hanya 1]
   i=0 (5): query(2) = 2        hasil[0]=2   update(3)   [1 dan 2]
   jawab: 2 1 1 0   ✓

🔄 ALTERNATIVE APPROACHES:
- Merge sort dengan pelacakan indeks: bisa, tetapi jauh lebih rumit karena
  kamu harus membawa indeks asli sepanjang proses penggabungan.
- Policy-based ordered set: order_of_key memberi jawaban langsung, paling
  pendek, tetapi konstanta besar dan hanya tersedia di GCC.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
vector<int> t;

void update(int i, int d) { for (; i <= n; i += i & -i) t[i] += d; }
int query(int i) { int s = 0; for (; i > 0; i -= i & -i) s += t[i]; return s; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int m;
    cin >> m;
    vector<ll> a(m);
    for (ll& x : a) cin >> x;

    vector<ll> v = a;
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    n = v.size();
    t.assign(n + 2, 0);

    vector<int> hasil(m);
    for (int i = m - 1; i >= 0; i--) {
        int p = int(lower_bound(v.begin(), v.end(), a[i]) - v.begin()) + 1;
        hasil[i] = query(p - 1);                  // KETAT lebih kecil
        update(p, 1);
    }

    string out;
    for (int i = 0; i < m; i++) {
        out += to_string(hasil[i]);
        out += (i + 1 == m) ? '\n' : ' ';
    }
    cout << out;

    return 0;
}
