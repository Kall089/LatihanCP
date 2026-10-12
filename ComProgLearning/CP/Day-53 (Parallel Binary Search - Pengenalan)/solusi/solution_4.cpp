/*
============================================================
✅ Solution 4: Kapan Dua Kota Terhubung
============================================================
Approach: Parallel binary search + DSU
Complexity: Time O(log m * (m + q) * alpha) | Space O(n + m + q)
Key Insight: Keterhubungan bersifat MONOTON -- sekali dua kota terhubung,
             mereka terhubung selamanya (jalan tidak pernah dihancurkan).
             Itu satu-satunya syarat yang dibutuhkan agar binary search
             berlaku, dan DSU adalah struktur data yang tepat untuk
             mengujinya.

📖 KENAPA TIDAK BUTUH DSU DENGAN ROLLBACK:
   Ini pertanyaan yang sering muncul. Rollback diperlukan kalau kamu harus
   MEMBATALKAN operasi penggabungan di tengah jalan -- misalnya pada
   divide and conquer yang menelusuri pohon rekursi.
   Pada parallel binary search, setiap putaran memulai dari NOL dan
   menerapkan kejadian secara berurutan maju. Tidak pernah ada pembatalan.
   Jadi DSU biasa dengan path compression dan union by size sudah cukup,
   dan itu lebih cepat serta lebih pendek daripada versi rollback.
   (Rollback baru diperlukan di Day 191, offline dynamic connectivity.)

📖 BIAYA MENJAWAB SANGAT MURAH:
   Menjawab satu query hanya dua pemanggilan find -- praktis O(alpha),
   konstanta. Jadi bagian yang mendominasi adalah sapuan penggabungan:
   log(m) putaran x m penggabungan = O(m log m * alpha).
   Untuk m = 2*10^5, itu sekitar 3.5*10^6 operasi -- sangat cepat.

⚠️ RESET DSU DI AWAL SETIAP PUTARAN.
   Cara termudah: isi ulang parent[i] = i dan size[i] = 1.
   Biayanya O(n) per putaran, total O(n log m) -- dapat diabaikan.
   Melupakannya berarti putaran kedua dimulai dengan seluruh kota sudah
   tergabung, sehingga setiap query akan menjawab 1.

⚠️ PATH COMPRESSION MENGUBAH STRUKTUR SAAT find DIPANGGIL, tetapi itu
   tidak masalah di sini -- ia hanya mempercepat, tidak mengubah partisi.
   (Ini justru alasan kenapa path compression TIDAK BOLEH dipakai bersama
   rollback: ia merusak kemampuan membatalkan.)

VERIFIKASI SAMPEL (4 kota, jalan: 1-2, 3-4, 2-3):
   query (1,2): jalan hari 1 langsung menghubungkan -> 1   ✓
   query (1,4): butuh 1-2, 3-4, DAN 2-3 -> baru terhubung hari 3   ✓
   query (1,3): butuh 1-2 dan 2-3 -> hari 3   ✓

🔄 ALTERNATIVE APPROACHES:
- Small-to-large merging dengan menyimpan waktu penggabungan: O(m log n),
  menjawab query dalam O(log n) tanpa binary search sama sekali. Lebih
  cepat, tetapi idenya lebih rumit.
- Membangun "Kruskal reconstruction tree": jawabannya menjadi LCA dari dua
  simpul, O(log n) per query setelah preprocessing. Elegan, tetapi butuh
  materi Day 201.
- Untuk soal ini, parallel binary search adalah yang paling mudah ditulis.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> par, sz;

void dsuReset(int n) {
    par.resize(n + 1);
    sz.assign(n + 1, 1);
    for (int i = 0; i <= n; i++) par[i] = i;
}

int find(int x) {
    while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }   // path halving
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

    int n, m, q;
    cin >> n >> m >> q;

    vector<int> U(m + 1), V(m + 1);
    for (int t = 1; t <= m; t++) cin >> U[t] >> V[t];

    vector<int> qu(q), qv(q);
    for (int i = 0; i < q; i++) cin >> qu[i] >> qv[i];

    vector<int> lo(q, 1), hi(q, m + 1);        // m+1 = "tidak pernah"
    vector<vector<int>> bucket(m + 2);

    while (true) {
        for (auto& b : bucket) b.clear();
        bool jalan = false;

        for (int i = 0; i < q; i++)
            if (lo[i] < hi[i]) {
                bucket[lo[i] + (hi[i] - lo[i]) / 2].push_back(i);
                jalan = true;
            }
        if (!jalan) break;

        dsuReset(n);                            // RESET -- WAJIB

        for (int t = 1; t <= m; t++) {
            unite(U[t], V[t]);

            for (int i : bucket[t]) {
                if (find(qu[i]) == find(qv[i])) hi[i] = t;
                else                            lo[i] = t + 1;
            }
        }
    }

    string out;
    for (int i = 0; i < q; i++) {
        out += to_string(lo[i] > m ? -1 : lo[i]);
        out += '\n';
    }
    cout << out;

    return 0;
}
