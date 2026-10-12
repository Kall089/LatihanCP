/*
============================================================
✅ Solution 5: Gaji Karyawan
============================================================
Approach: Offline + kompresi seluruh nilai + BIT hitungan
Complexity: Time O((N + Q) log(N + Q)) | Space O(N + Q)
Key Insight: BIT diindeks oleh NILAI, sehingga kompresi diperlukan. Tetapi
             ada jebakan yang tidak muncul di Exercise 2: nilai yang perlu
             diindeks TIDAK HANYA berasal dari array awal -- operasi update
             bisa memperkenalkan nilai baru yang belum pernah ada.

📖 KENAPA HARUS OFFLINE:
   Kalau kamu membangun kamus kompresi hanya dari gaji awal, lalu operasi
   "! k x" mengubah gaji menjadi x yang tidak ada di kamus, maka
   lower_bound akan mengembalikan posisi PENYISIPAN -- bukan posisi x --
   dan seluruh hitungan setelahnya menjadi salah, TANPA error apa pun.

   Solusinya: baca SELURUH operasi lebih dulu, kumpulkan setiap nilai yang
   akan pernah dijadikan indeks (gaji awal DAN seluruh x dari operasi "!"),
   lalu bangun kamus sekali. Teknik "kumpulkan dulu, proses belakangan" ini
   sama dengan yang kamu pakai di Day 53.

📖 MEMETAKAN BATAS QUERY a DAN b:
   Batas query TIDAK perlu masuk kamus, tetapi pemetaannya harus hati-hati
   karena a dan b belum tentu ada di sana:
       banyak gaji <= b  ->  pakai upper_bound(b)  (posisi pertama yang > b)
       banyak gaji <  a  ->  pakai lower_bound(a)  (posisi pertama yang >= a)
       jawabannya selisih keduanya.
   Memakai bound yang salah akan melewatkan atau menghitung ganda elemen
   yang nilainya TEPAT SAMA dengan batasnya.

   Alternatif yang lebih sederhana (dipakai di sini): masukkan juga seluruh
   a dan b ke dalam kamus. Dengan begitu keduanya dijamin ada dan pemetaannya
   langsung. Biayanya hanya kamus yang sedikit lebih besar.

⚠️ BIT MENYIMPAN HITUNGAN, BUKAN GAJI.
   Posisi p pada BIT menyimpan "berapa karyawan yang gajinya sama dengan
   nilai ke-p". Menyisipkan berarti update(p, +1), menghapus update(p, -1).
   Query prefiks memberi "berapa karyawan bergaji <= nilai ke-p".

⚠️ OPERASI "!" ADALAH HAPUS LALU SISIP:
       update(posisiGajiLama, -1);
       update(posisiGajiBaru, +1);
   Melupakan penghapusan membuat jumlah karyawan bertambah terus.
   Karena itu kita menyimpan gaji setiap karyawan secara terpisah.

VERIFIKASI SAMPEL (gaji [3,7,2,2,5]):
   "? 2 3" : gaji dalam [2,3] adalah 3, 2, 2 -> 3   ✓
   "! 3 6" : gaji karyawan ke-3 dari 2 menjadi 6
   "? 2 3" : gaji dalam [2,3] tinggal 3 dan 2 -> 2  ✓

🔄 ALTERNATIVE APPROACHES:
- Segment tree dinamis (implicit): tidak butuh offline karena simpul dibuat
  saat diperlukan. Berguna kalau query harus dijawab ONLINE.
- policy-based ordered multiset: order_of_key memberi jawaban langsung,
  tetapi konstanta besar dan sulit menangani duplikat.
- Soal ini adalah CSES 1144 (Salary Queries).
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

    int m, q;
    cin >> m >> q;
    vector<ll> gaji(m + 1);
    vector<ll> semua;                             // SELURUH nilai yang akan diindeks

    for (int i = 1; i <= m; i++) { cin >> gaji[i]; semua.push_back(gaji[i]); }

    // OFFLINE: baca seluruh operasi dulu
    vector<char> jenis(q);
    vector<ll> p1(q), p2(q);
    for (int i = 0; i < q; i++) {
        cin >> jenis[i] >> p1[i] >> p2[i];
        semua.push_back(p1[i]);
        semua.push_back(p2[i]);                   // batas query juga dimasukkan
    }

    sort(semua.begin(), semua.end());
    semua.erase(unique(semua.begin(), semua.end()), semua.end());
    n = semua.size();
    t.assign(n + 2, 0);

    auto idx = [&](ll x) {                        // 1-BASED untuk BIT
        return int(lower_bound(semua.begin(), semua.end(), x) - semua.begin()) + 1;
    };

    for (int i = 1; i <= m; i++) update(idx(gaji[i]), 1);

    string out;
    for (int i = 0; i < q; i++) {
        if (jenis[i] == '!') {
            int k = (int)p1[i];
            ll x = p2[i];
            update(idx(gaji[k]), -1);             // HAPUS gaji lama
            gaji[k] = x;
            update(idx(x), +1);                   // SISIP gaji baru
        } else {
            int lo = idx(p1[i]), hi = idx(p2[i]);
            out += to_string(query(hi) - query(lo - 1));
            out += '\n';
        }
    }
    cout << out;

    return 0;
}
