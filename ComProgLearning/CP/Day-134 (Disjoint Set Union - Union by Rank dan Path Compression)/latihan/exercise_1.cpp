/*
============================================================
🏋️ Exercise 1: Berapa Kelompok Pertemanan
============================================================
Day: 134 | Difficulty: Easy
Topic: DSU dasar
Time Limit: 1 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Di sebuah sekolah ada N siswa yang dinomori 1 sampai N. Mula-mula setiap
siswa berdiri sendiri.
Terjadi M peristiwa perkenalan. Peristiwa ke-i memperkenalkan siswa a dan b,
sehingga mereka (beserta seluruh teman mereka masing-masing) menjadi satu
kelompok pertemanan.
Setelah seluruh peristiwa selesai, cetak BERAPA BANYAK kelompok pertemanan
yang terbentuk, dan berapa ANGGOTA kelompok TERBESAR.
Perhatikan bahwa dua siswa bisa saja diperkenalkan berkali-kali.

📥 INPUT FORMAT:
- Baris pertama: N dan M
- M baris berikutnya: masing-masing a dan b

📤 OUTPUT FORMAT:
- Dua bilangan dipisah spasi: banyaknya kelompok dan ukuran kelompok terbesar

📏 CONSTRAINTS:
- 1 <= N <= 2 * 10^5
- 0 <= M <= 2 * 10^5
- 1 <= a, b <= N

📎 SAMPLE INPUT 1:
6 4
1 2
2 3
4 5
1 3

📎 SAMPLE OUTPUT 1:
3 3

📎 SAMPLE INPUT 2:
3 0

📎 SAMPLE OUTPUT 2:
3 1

💡 HINT: Setiap siswa menunjuk ke satu "perwakilan". Untuk mengetahui
         kelompok seseorang, ikuti penunjuk itu sampai menemukan siswa yang
         menunjuk ke dirinya sendiri.
         Menggabungkan dua kelompok cukup membuat satu perwakilan menunjuk
         ke perwakilan lainnya — satu operasi, bukan mengubah seluruh anggota.
         Dua hal yang bisa kamu lacak secara GRATIS di dalam operasi
         penggabungan: berapa kelompok yang tersisa, dan berapa anggota tiap
         kelompok. Pikirkan kapan tepatnya keduanya berubah.
         Peringatan: siswa dinomori mulai dari 1, jadi perhatikan ukuran
         array yang kamu alokasikan.

🎯 Learning Goals:
- [ ] Menulis find dan unite dari nol
- [ ] Melacak banyaknya kelompok tanpa menyapu ulang
- [ ] Menyadari bahwa penggabungan berulang harus tidak berpengaruh
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

struct DSU
{
    vector<int> par, sz;

    DSU(int n) : par(n), sz(n, 1)
    {
        iota(par.begin(), par.end(), 0);
    }

    int find(int x)
    {
        if (par[x] == x)
            return x;

        return par[x] = find(par[x]);
    }

    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);

        if (a == b)
        {
            return false;
        }

        if (sz[a] < sz[b])
        {
            swap(a, b);
        }

        par[b] = a;
        sz[a] += sz[b];

        return true;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;
    DSU d(n + 1);

    while (m--)
    {
        int a, b;
        cin >> a >> b;

        d.unite(a, b);
    }

    for (int i = 0; i < n; i++)
    {
        cout << d.sz[i] << " ";
    }
}