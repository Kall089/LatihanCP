/*
============================================================
✅ Solution 6: Nilai yang Paling Sering Muncul
============================================================
Approach: Run-length encoding + sparse table maksimum atas panjang blok
Complexity: Time O(n log n + q) | Space O(n log n)
Key Insight: Karena array TERURUT, nilai yang sama selalu berkelompok dalam
             blok berdampingan. Sebuah rentang query memotong paling banyak
             DUA blok secara sebagian (yang pertama dan terakhir); seluruh
             blok di antaranya termuat UTUH. Jadi jawabannya adalah maksimum
             dari tiga besaran, dan hanya bagian tengah yang butuh struktur.

📖 TIGA BAGIAN SEBUAH QUERY:
       [ blok pertama (sebagian) ][ blok utuh ... blok utuh ][ blok terakhir (sebagian) ]
   1. Potongan blok pertama : dari l sampai akhir blok itu
   2. Blok-blok utuh di tengah : maksimum panjangnya -> SPARSE TABLE
   3. Potongan blok terakhir : dari awal blok itu sampai r

   Jawabannya maksimum dari ketiganya.

⚠️ KASUS KHUSUS YANG WAJIB DITANGANI: seluruh query berada DI DALAM SATU
   blok. Dalam kasus itu tidak ada "blok pertama dan terakhir yang berbeda",
   dan jawabannya cukup panjang rentangnya sendiri (r - l + 1).
   Sampel pertama (query [2,3] pada array yang dimulai dengan dua -1) menguji
   tepat kasus ini: kedua posisi berada di blok berbeda? Mari periksa:
   a = [-1,-1,1,1,1,1,3,10,10,10], posisi 2 dan 3 (1-based) adalah -1 dan 1
   -- blok BERBEDA, masing-masing menyumbang 1. Jawabannya 1.
   Kalau query-nya [1,2], keduanya di blok -1 yang sama, jawabannya 2.
   Tanpa penanganan kasus khusus, perhitungan blok tengah bisa mengakses
   rentang kosong atau terbalik.

⚠️ INDEKS BLOK TENGAH: kalau blok pertama adalah bl dan blok terakhir adalah
   br, maka blok utuh di tengah adalah bl+1 sampai br-1. Rentang itu KOSONG
   kalau br - bl <= 1, sehingga sparse table tidak boleh dipanggil --
   query dengan l > r pada sparse table adalah perilaku tak terdefinisi.

⚠️ MEMETAKAN POSISI KE BLOK: simpan array blokDari[i] = indeks blok yang
   memuat posisi i. Dibangun sekali saat memadatkan, O(n).

📖 KENAPA SPARSE TABLE COCOK DI SINI: kita menanyakan MAKSIMUM panjang blok
   pada rentang blok -- operasi idempoten, array statis, banyak query.
   Persis profil sparse table.

VERIFIKASI SAMPEL (a = [-1,-1,1,1,1,1,3,10,10,10]):
   Blok: (-1, panjang 2, posisi 1-2), (1, panjang 4, posisi 3-6),
         (3, panjang 1, posisi 7), (10, panjang 3, posisi 8-10)
   query [2,3]: posisi 2 di blok 0, posisi 3 di blok 1. Berbeda.
       potongan blok 0: dari 2 sampai 2 -> 1
       blok tengah: dari 1 sampai 0 -> KOSONG
       potongan blok 1: dari 3 sampai 3 -> 1
       jawab 1   ✓
   query [1,10]: blok 0 sampai 3.
       potongan kiri 2, potongan kanan 3, blok tengah maks(4, 1) = 4
       jawab 4   ✓
   query [5,10]: posisi 5 di blok 1, posisi 10 di blok 3.
       potongan kiri: 5..6 -> 2
       blok tengah: blok 2, panjang 1
       potongan kanan: 8..10 -> 3
       jawab 3   ✓

🔄 ALTERNATIVE APPROACHES:
- Segment tree yang menyimpan (prefix run, suffix run, maks run) per simpul:
  bekerja untuk array TIDAK terurut juga, dan mendukung update. Lebih umum
  tetapi jauh lebih panjang.
- Mo's algorithm: O((n+q) sqrt n), berlebihan di sini.
- Soal ini adalah SPOJ FREQUENT / UVa 11235, contoh klasik teknik ini.
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
    vector<int> a(n);
    for (int& x : a) cin >> x;

    // Padatkan menjadi blok (run-length), array sudah TERURUT
    vector<int> blokDari(n), awalBlok, akhirBlok, panjangBlok;
    for (int i = 0; i < n; ) {
        int j = i;
        while (j < n && a[j] == a[i]) j++;
        int id = (int)panjangBlok.size();
        awalBlok.push_back(i);
        akhirBlok.push_back(j - 1);
        panjangBlok.push_back(j - i);
        for (int t = i; t < j; t++) blokDari[t] = id;
        i = j;
    }

    int m = panjangBlok.size();
    vector<int> lg(m + 1, 0);
    for (int i = 2; i <= m; i++) lg[i] = lg[i / 2] + 1;

    int K = lg[m] + 1;
    vector<vector<int>> sp(K, vector<int>(m));
    sp[0] = panjangBlok;
    for (int k = 1; k < K; k++)
        for (int i = 0; i + (1 << k) <= m; i++)
            sp[k][i] = max(sp[k - 1][i], sp[k - 1][i + (1 << (k - 1))]);

    auto maksBlok = [&](int l, int r) {       // rentang INDEKS BLOK
        int k = lg[r - l + 1];
        return max(sp[k][l], sp[k][r - (1 << k) + 1]);
    };

    string out;
    while (q--) {
        int l, r;
        cin >> l >> r;
        --l; --r;

        int bl = blokDari[l], br = blokDari[r];
        int jawab;

        if (bl == br) {
            jawab = r - l + 1;                // KASUS KHUSUS: satu blok saja
        } else {
            jawab = max(akhirBlok[bl] - l + 1,     // potongan blok pertama
                        r - awalBlok[br] + 1);     // potongan blok terakhir
            if (br - bl > 1)                       // blok tengah TIDAK kosong
                jawab = max(jawab, maksBlok(bl + 1, br - 1));
        }

        out += to_string(jawab);
        out += '\n';
    }
    cout << out;

    return 0;
}
