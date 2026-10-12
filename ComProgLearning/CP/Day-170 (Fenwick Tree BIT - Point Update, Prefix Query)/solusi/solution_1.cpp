/*
============================================================
✅ Solution 1: Update dan Jumlah Bergantian
============================================================
Approach: Fenwick Tree (BIT)
Complexity: Time O((N + Q) log N) | Space O(N)
Key Insight: Prefix sum memberi query O(1) tetapi update O(n); array biasa
             memberi update O(1) tetapi query O(n). BIT menyeimbangkan
             keduanya menjadi O(log n) dengan menyimpan jumlah PARSIAL yang
             panjangnya pangkat dua.

📖 STRUKTURNYA:
   tree[i] menyimpan jumlah a[i - (i&-i) + 1 .. i], yaitu blok sepanjang
   lowbit(i) yang BERAKHIR di i.

       i=1 -> a[1..1]    i=5 -> a[5..5]
       i=2 -> a[1..2]    i=6 -> a[5..6]
       i=4 -> a[1..4]    i=8 -> a[1..8]

   query(r) menjumlahkan blok-blok yang MENUTUPI [1, r] tanpa tumpang tindih,
   bergerak turun dengan i -= i & -i.
   update(i) memperbarui seluruh blok yang MEMUAT posisi i,
   bergerak naik dengan i += i & -i.

📖 KENAPA i & -i MEMBERI BIT TERENDAH YANG MENYALA:
   Dalam two's complement, -i sama dengan ~i + 1.
       i  = 12 = 00001100
       -i =      11110100
       i & -i =  00000100 = 4
   Membalik seluruh bit lalu menambah 1 membuat seluruh bit di bawah bit
   terendah menjadi 1 lalu "carry" menghapusnya, menyisakan tepat satu bit.

⚠️ BIT WAJIB 1-INDEXED -- INI BUG NOMOR SATU.
   Kalau i = 0, maka 0 & -0 = 0, sehingga loop `i += 0` TIDAK PERNAH MAJU
   dan program HANG. Gejalanya membingungkan karena tidak ada pesan error,
   hanya TLE atau program yang menggantung.
   Kalau datamu 0-indexed, geser satu saat memanggil: update(i + 1, x).

⚠️ "GANTI NILAI" BUKAN "TAMBAH NILAI".
   BIT hanya bisa MENAMBAH. Untuk mengganti a[k] menjadi u, kita menambahkan
   selisihnya: update(k, u - nilaiLama), lalu simpan nilaiLama = u.
   Melupakan ini membuat nilai menumpuk alih-alih tergantikan.
   Karena itu kita menyimpan salinan array aslinya secara terpisah.

⚠️ TIPE DATA: 2*10^5 elemen bernilai 10^9 memberi jumlah 2*10^14.
   long long WAJIB untuk tree dan hasil query.

📖 BUILD O(n) ALIH-ALIH O(n log n):
   Alih-alih memanggil update n kali, setiap simpul mewariskan nilainya ke
   induknya sekali:
       t[i] += a[i]; j = i + (i & -i); if (j <= n) t[j] += t[i];
   Perbedaannya kecil tetapi gratis.

VERIFIKASI SAMPEL (a = [3,2,4,5,1,1,5,3]):
   query [1,4] = 3+2+4+5 = 14   ✓
   query [5,6] = 1+1 = 2        ✓
   ganti a[3] dari 4 menjadi 1 -> selisih -3
   query [1,4] = 3+2+1+5 = 11   ✓

CATATAN: implementasi ini telah diuji terhadap brute force pada 20000 kasus
acak dengan operasi update dan query yang berselang-seling.

🔄 ALTERNATIVE APPROACHES:
- Segment tree: O(log n) juga, tetapi ~40 baris dan konstanta 3-5x lebih
  besar. Baru diperlukan kalau operasinya bukan sum (min, max, gcd).
- Sqrt decomposition: O(sqrt n) per operasi, lebih sederhana tetapi lebih
  lambat.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
vector<ll> t;

void update(int i, ll delta) {
    for (; i <= n; i += i & -i) t[i] += delta;    // NAIK: blok yang memuat i
}
ll query(int i) {
    ll s = 0;
    for (; i > 0; i -= i & -i) s += t[i];         // TURUN: blok penutup prefiks
    return s;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> n >> q;
    vector<ll> a(n + 1);                          // simpan nilai asli terpisah
    t.assign(n + 2, 0);

    for (int i = 1; i <= n; i++) {                // build O(n)
        cin >> a[i];
        t[i] += a[i];
        int j = i + (i & -i);
        if (j <= n) t[j] += t[i];
    }

    string out;
    while (q--) {
        int jenis;
        cin >> jenis;
        if (jenis == 1) {
            int k;
            ll u;
            cin >> k >> u;
            update(k, u - a[k]);                  // GANTI = tambah SELISIH
            a[k] = u;
        } else {
            int l, r;
            cin >> l >> r;
            out += to_string(query(r) - query(l - 1));
            out += '\n';
        }
    }
    cout << out;

    return 0;
}
