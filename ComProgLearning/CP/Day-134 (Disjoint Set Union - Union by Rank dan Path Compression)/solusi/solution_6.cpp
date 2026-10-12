/*
============================================================
✅ Solution 6: Pulau Setelah Setiap Penambahan
============================================================
Approach: DSU pada grid + hitungan komponen inkremental
Complexity: Time O(T α(RC)) | Space O(RC)
Key Insight: Menjalankan flood fill setelah setiap operasi berbiaya
             O(R*C) per operasi -- untuk T = 2*10^5 itu 4*10^10, mustahil.
             DSU memungkinkan menjaga hitungan pulau secara inkremental:
             setiap operasi hanya menyentuh satu sel dan empat tetangganya.

📖 ATURAN PERUBAHAN HITUNGAN:
   1. Sel baru menjadi daratan  -> pulau bertambah satu (ia sendirian dulu).
   2. Untuk setiap tetangga yang SUDAH daratan dan belum sekelompok:
      penggabungan menyatukan dua pulau -> pulau berkurang satu.

   Jadi satu operasi bisa menambah 1 lalu mengurangi sampai 4, sehingga
   hitungan bisa berubah dari +1 sampai -3. Semuanya tertangani otomatis
   oleh dua aturan di atas.

⚠️ TIGA JEBAKAN, SEMUANYA MUDAH TERJADI:
   1. TETANGGA DI LUAR GRID. Periksa 0 <= nr < R dan 0 <= nc < C SEBELUM
      menghitung indeksnya. Tanpa itu, sel di kolom terakhir baris i akan
      "bersebelahan" dengan kolom pertama baris i+1 -- membungkus secara
      diam-diam dan menghasilkan jawaban yang tampak masuk akal tetapi salah.
   2. TETANGGA YANG MASIH LAUT. Menggabungkan dengan sel yang belum menjadi
      daratan membentuk pulau yang belum ada.
   3. SEL YANG SUDAH DARATAN. Operasi berulang pada sel yang sama tidak
      boleh mengubah hitungan sama sekali. Periksa dan langsung lewati.

⚠️ PEMETAAN KOORDINAT: (r, c) -> r * C + c dengan r dan c 0-based.
   Rumus ini menjamin setiap sel mendapat indeks berbeda dalam [0, R*C).
   Kalau soal memberi koordinat 1-based, kurangi satu SEBELUM memetakan --
   kesalahan di sini menghasilkan akses di luar batas pada baris terakhir.

⚠️ MEMORI: R*C sampai 2*10^5, jadi DSU berukuran itu -- sekitar 1.6 MB.
   Aman. Tetapi kalau R dan C masing-masing 500, R*C = 250000 dan batas
   soal R*C <= 2*10^5 justru MELARANG kombinasi itu. Selalu perhatikan
   batas GABUNGAN, bukan hanya batas masing-masing.

VERIFIKASI SAMPEL (grid 3x3):
   (1,1) : daratan baru, pulau 0 -> 1. Tidak ada tetangga daratan.  -> 1  ✓
   (1,2) : daratan baru, pulau 1 -> 2. Tetangga (1,1) daratan,
           gabung -> pulau 2 -> 1.                                   -> 1  ✓
   (2,2) : daratan baru, pulau 1 -> 2. Tetangga (1,2) daratan,
           gabung -> pulau 2 -> 1.                                   -> 1  ✓
   (3,3) : daratan baru, pulau 1 -> 2. Tetangga (2,3) dan (3,2)
           masih laut, tidak ada penggabungan.                       -> 2  ✓

🔄 ALTERNATIVE APPROACHES:
- BFS/DFS ulang setiap operasi: O(T * R * C) -- TLE.
- Kalau seluruh operasi diketahui di awal DAN soal hanya menanyakan
  keadaan AKHIR, satu kali flood fill sudah cukup. DSU diperlukan justru
  karena jawabannya diminta SETELAH SETIAP operasi.
- Soal ini adalah bentuk klasik "Number of Islands II" (LeetCode 305).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int R, C, T;
    cin >> R >> C >> T;

    int total = R * C;
    vector<int> par(total), sz(total, 1);
    vector<char> daratan(total, 0);
    iota(par.begin(), par.end(), 0);

    function<int(int)> find = [&](int x) {
        while (par[x] != x) { par[x] = par[par[x]]; x = par[x]; }
        return x;
    };

    auto idx = [&](int r, int c) { return r * C + c; };
    const int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};

    int pulau = 0;
    string out;

    for (int t = 0; t < T; t++) {
        int r, c;
        cin >> r >> c;
        --r; --c;                                  // 1-based -> 0-based
        int id = idx(r, c);

        if (!daratan[id]) {                        // sel yang SUDAH daratan: lewati
            daratan[id] = 1;
            pulau++;                               // mula-mula pulau sendiri

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d], nc = c + dc[d];
                if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;  // batas grid
                int nid = idx(nr, nc);
                if (!daratan[nid]) continue;       // tetangga masih laut

                int a = find(id), b = find(nid);
                if (a == b) continue;              // sudah satu pulau
                if (sz[a] < sz[b]) swap(a, b);
                par[b] = a;
                sz[a] += sz[b];
                pulau--;                           // dua pulau menyatu
            }
        }

        out += to_string(pulau);
        out += '\n';
    }
    cout << out;

    return 0;
}
