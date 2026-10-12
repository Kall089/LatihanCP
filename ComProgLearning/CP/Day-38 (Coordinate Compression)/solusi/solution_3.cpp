/*
============================================================
✅ Solution 3: Peringkat Penuh
============================================================
Approach: Urutkan INDEKS dengan komparator (nilai, indeks)
Complexity: Time O(n log n) | Space O(n)
Key Insight: Ada dua jenis kompresi yang sering tertukar.
             Jenis A membuang duplikat: nilai sama -> peringkat sama.
             Jenis B memberi peringkat penuh: setiap posisi mendapat
             peringkat unik, seri dipecah oleh indeks.
             Pertanyaan pemandunya: "apakah dua nilai yang sama harus
             diperlakukan sebagai hal yang sama?"

📖 PENJELASAN PENDEKATAN:
1. Buat vektor indeks 0..n-1.
2. Urutkan indeks itu, membandingkan a[i] dulu, lalu i sebagai pemecah seri.
3. rank[urut[k]] = k.

   Langkah 3 sering membingungkan. Bacanya: "elemen yang menempati posisi
   ke-k dalam urutan adalah indeks urut[k], maka indeks itulah yang
   berperingkat k."

HASILNYA SELALU PERMUTASI 0..n-1, yang berguna sebagai masukan untuk
algoritma yang mengasumsikan permutasi (misalnya sebagian solusi inversion
count, atau soal yang menanyakan urutan relatif tanpa peduli nilai).

CATATAN TENTANG STABILITAS: karena kita memakai indeks sebagai pemecah seri
secara eksplisit, hasilnya deterministik meskipun sort() tidak stabil.
Alternatifnya adalah memakai stable_sort tanpa pemecah seri -- keduanya
benar, tetapi menuliskan pemecah seri secara eksplisit lebih jelas dan
tidak bergantung pada properti pustaka.

VERIFIKASI SAMPEL 1 (a = [10, 50, 10, 30]):
   pasangan terurut: (10,0) (10,2) (30,3) (50,1)
   rank[0]=0, rank[2]=1, rank[3]=2, rank[1]=3
   hasil = [0, 3, 1, 2]  ✓

🔄 ALTERNATIVE APPROACHES:
- Kompres jenis A dulu, lalu bedakan seri dengan penghitung per nilai:
  bisa, tetapi lebih panjang dan lebih rawan.
- sort pasangan (nilai, indeks) secara langsung: setara, hanya berbeda gaya.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<ll> a(n);
    for (ll& x : a) cin >> x;

    vector<int> urut(n);
    iota(urut.begin(), urut.end(), 0);
    sort(urut.begin(), urut.end(), [&](int i, int j) {
        if (a[i] != a[j]) return a[i] < a[j];
        return i < j;                          // pemecah seri eksplisit
    });

    vector<int> rk(n);
    for (int k = 0; k < n; k++) rk[urut[k]] = k;

    string out;
    for (int i = 0; i < n; i++) {
        out += to_string(rk[i]);
        out += (i + 1 == n) ? '\n' : ' ';
    }
    cout << out;

    return 0;
}
