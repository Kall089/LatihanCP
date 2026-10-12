/*
 * Day 59 — DFS
 * File  : tugas_11.cpp
 * Topik : Rekonstruksi Cycle pada Graph BERARAH
 * Tingkat: Hard ★★★★☆
 * -----------------------------------------------
 * Diberikan graph BERARAH dengan N node dan M edge.
 * Jika ada cycle, cetak SATU cycle sebagai urutan node, dimulai dan diakhiri
 * dengan node yang sama. Jika tidak ada cycle, cetak "IMPOSSIBLE".
 *
 * Ini adalah tingkat lanjut dari exercise_4 — bukan hanya mendeteksi
 * ADA/TIDAKNYA cycle, tapi menunjukkan cycle-nya.
 *
 * Idea:
 *   Jalankan DFS 3-color sambil mencatat par[v] = u setiap kali masuk dari
 *   u ke v. Saat menemukan tetangga v yang GRAY dari node u:
 *     - v adalah titik awal cycle
 *     - telusuri mundur dari u lewat par[] sampai bertemu v
 *     - balik urutannya, lalu tambahkan v di akhir untuk menutup cycle
 *
 *   Contoh: 1→2→3→4, lalu 4→2. Saat di node 4 kita lihat 2 masih GRAY.
 *   Telusuri mundur: 4 → par[4]=3 → par[3]=2 = v, berhenti.
 *   Terkumpul [4,3,2], dibalik → [2,3,4], tutup → 2 3 4 2
 *
 * ⚠️ Berhenti SEGERA setelah cycle pertama ditemukan (pakai flag global),
 *    jangan lanjutkan DFS — nanti par[] tertimpa dan rekonstruksinya rusak.
 *
 * Input format  : Baris 1: N dan M
 *                 M baris berikutnya: u dan v (edge berarah u → v)
 * Output format : urutan node cycle (node pertama = node terakhir),
 *                 atau "IMPOSSIBLE"
 * Constraints   : 1 ≤ N ≤ 200.000
 *                 0 ≤ M ≤ 200.000
 *
 * Sample Input 1:        Sample Output 1:
 * 4 4                    2 3 4 2
 * 1 2
 * 2 3
 * 3 4
 * 4 2
 *
 * Sample Input 2:        Sample Output 2:
 * 3 2                    IMPOSSIBLE
 * 1 2
 * 2 3
 *
 * Sample Input 3:        Sample Output 3:
 * 2 2                    1 2 1
 * 1 2
 * 2 1
 *
 * NOTE: Kalau ada beberapa cycle, cetak yang mana saja — asal valid
 *       (setiap pasangan berurutan benar-benar punya edge berarah,
 *        dan node pertama sama dengan node terakhir).
 *
 * HINT: Soal ini setara dengan CSES 1678 "Round Trip II". Setelah selesai,
 *       submit ke sana untuk validasi.
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int color[MAXN];
int par[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: DFS 3-color + catat parent, rekonstruksi cycle saat ketemu GRAY

    return 0;
}
