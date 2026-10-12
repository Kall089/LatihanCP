/*
============================================================
✅ Solution 6: Kapan Jalur Aman Terbentuk
============================================================
Approach: Parallel binary search + DSU pada grid
Complexity: Time O(log T * (T * 4 + q) * alpha) | Space O(R*C + T + q)
Key Insight: Gabungan Exercise 4 (DSU) dengan penanganan grid. Satu detail
             tambahan yang mudah terlewat: sebuah sel hanya boleh
             digabungkan dengan tetangga yang SUDAH menjadi daratan.
             Menggabungkan dengan sel yang belum muncul akan membuat
             komponen terbentuk terlalu awal, dan jawabannya terlalu kecil.

📖 PENJELASAN PENDEKATAN:
1. Catat hariMuncul[sel] untuk setiap sel yang pernah muncul.
2. Kerangka parallel binary search seperti biasa.
3. Saat menerapkan hari ke-t: tandai selnya sebagai daratan, lalu untuk
   masing-masing dari empat tetangganya, gabungkan HANYA kalau tetangga itu
   sudah menjadi daratan (yaitu hariMuncul[tetangga] <= t).
4. Menjawab query = cek apakah kedua sel berada di komponen yang sama.

⚠️ SYARAT TAMBAHAN: KEDUA SEL HARUS SUDAH MUNCUL.
   Jawabannya tidak mungkin lebih awal dari
   max(hariMuncul[sel1], hariMuncul[sel2]).
   Kita bisa memakai itu sebagai batas bawah awal lo[i], yang menghemat
   beberapa iterasi -- tetapi bahkan tanpa optimasi itu jawabannya tetap
   benar, karena dua sel yang belum menjadi daratan tidak akan pernah
   berada di komponen yang sama.
   Solusi ini memasang batas bawah tersebut karena gratis dan membuat
   maksud kodenya lebih jelas.

⚠️ MENGGABUNGKAN DENGAN TETANGGA YANG BELUM MUNCUL adalah bug klasik.
   Periksa `sudahDaratan[tetangga]` sebelum unite, bukan hanya batas grid.

⚠️ PEMETAAN KOORDINAT: sel (r, c) dengan r dan c 1-based menjadi indeks
   (r-1)*C + (c-1). Selalu periksa batas grid sebelum menghitung indeks
   tetangga, kalau tidak kamu bisa "membungkus" dari kolom terakhir baris i
   ke kolom pertama baris i+1 -- bug yang menghasilkan jawaban yang tampak
   masuk akal tetapi salah.

⚠️ RESET DSU DAN ARRAY sudahDaratan di setiap putaran.

VERIFIKASI SAMPEL (grid 2x2, urutan muncul: (1,1), (1,2), (2,2), (2,1)):
   query (1,1)-(1,2): keduanya daratan pada hari 2, dan bersebelahan
       secara horizontal -> terhubung hari 2   ✓
   query (1,1)-(2,1): (2,1) baru muncul hari 4. Pada hari 4 seluruh grid
       sudah menjadi daratan dan terhubung -> hari 4   ✓

🔄 ALTERNATIVE APPROACHES:
- Memproses MUNDUR (dari seluruh daratan lalu menghapus satu per satu):
  DSU tidak mendukung pemisahan, tetapi dengan membalik urutan waktu,
  penghapusan menjadi penambahan. Ini trik yang sangat berguna dan sering
  menyederhanakan soal konektivitas "seiring waktu".
- Kruskal reconstruction tree + LCA: O(log n) per query setelah
  preprocessing, tetapi butuh materi Day 201.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> par, sz;

void dsuReset(int n) {
    par.resize(n);
    sz.assign(n, 1);
    for (int i = 0; i < n; i++) par[i] = i;
}
int find(int x) {
    while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
    return x;
}
void unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a;
    sz[a] += sz[b];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C, T, q;
    cin >> R >> C >> T >> q;

    int total = R * C;
    auto idx = [&](int r, int c) { return (r - 1) * C + (c - 1); };

    vector<int> hariMuncul(total, INT_MAX);
    vector<int> selHari(T + 1);
    for (int t = 1; t <= T; t++) {
        int r, c;
        cin >> r >> c;
        int id = idx(r, c);
        selHari[t] = id;
        hariMuncul[id] = t;
    }

    vector<int> qa(q), qb(q), lo(q), hi(q, T + 1);
    for (int i = 0; i < q; i++) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        qa[i] = idx(r1, c1);
        qb[i] = idx(r2, c2);
        // jawabannya tidak mungkin lebih awal dari saat KEDUANYA sudah daratan
        lo[i] = max(hariMuncul[qa[i]], hariMuncul[qb[i]]);
        if (lo[i] > T) lo[i] = T + 1;
    }

    vector<vector<int>> bucket(T + 2);
    vector<char> sudahDaratan(total);
    const int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};

    while (true) {
        for (auto& b : bucket) b.clear();
        bool jalan = false;

        for (int i = 0; i < q; i++)
            if (lo[i] < hi[i]) {
                bucket[lo[i] + (hi[i] - lo[i]) / 2].push_back(i);
                jalan = true;
            }
        if (!jalan) break;

        dsuReset(total);                                   // RESET
        fill(sudahDaratan.begin(), sudahDaratan.end(), 0); // RESET

        for (int t = 1; t <= T; t++) {
            int id = selHari[t];
            sudahDaratan[id] = 1;

            int r = id / C + 1, c = id % C + 1;
            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 1 || nr > R || nc < 1 || nc > C) continue;  // batas grid
                int nid = idx(nr, nc);
                if (sudahDaratan[nid]) unite(id, nid);     // HANYA yang sudah daratan
            }

            for (int i : bucket[t]) {
                if (find(qa[i]) == find(qb[i])) hi[i] = t;
                else                            lo[i] = t + 1;
            }
        }
    }

    string out;
    for (int i = 0; i < q; i++) {
        out += to_string(lo[i] > T ? -1 : lo[i]);
        out += '\n';
    }
    cout << out;

    return 0;
}
