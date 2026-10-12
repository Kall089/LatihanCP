/*
 * Day 59 — DFS
 * File  : tugas_15.cpp
 * Topik : Deteksi Cycle di Grid dengan Panjang ≥ 4
 * Tingkat: Hard ★★★★★
 * -----------------------------------------------
 * Diberikan grid R × C berisi huruf. Tentukan apakah ada CYCLE yang seluruh
 * selnya berisi HURUF YANG SAMA, dengan panjang minimal 4 sel.
 * Cetak "YES" atau "NO".
 *
 * Gerakan hanya 4-arah (atas, bawah, kiri, kanan).
 * "Cycle" berarti ada jalur tertutup yang kembali ke sel awal tanpa
 * mengulang sel yang sama di tengah jalan.
 *
 * Idea — DFS DENGAN CEK PARENT (versi grid dari exercise_3):
 *   Perlakukan grid sebagai graph tak berarah di mana dua sel bertetangga
 *   terhubung jika hurufnya sama.
 *
 *   bool dfs(r, c, pr, pc, ch) {
 *       vis[r][c] = true;
 *       for tiap 4 arah (nr, nc):
 *           if (di luar grid || grid[nr][nc] != ch) continue;
 *           if (nr == pr && nc == pc) continue;      ← jangan balik ke parent
 *           if (vis[nr][nc]) return true;            ← CYCLE ditemukan
 *           if (dfs(nr, nc, r, c, ch)) return true;
 *       return false;
 *   }
 *
 * Mengapa panjang ≥ 4 otomatis terpenuhi? Karena pada grid 4-arah,
 * cycle terpendek yang mungkin adalah persegi 2×2 = 4 sel. Tidak ada
 * cycle berukuran 3. Jadi cukup deteksi cycle biasa.
 *
 * ⚠️ Cek parent di sini berupa PASANGAN koordinat (pr, pc), bukan satu
 *    nomor node. Ini kesalahan implementasi yang sering terjadi.
 *
 * ⚠️ Setiap huruf diperlakukan sebagai graph terpisah — cycle harus
 *    seluruhnya berisi huruf yang SAMA.
 *
 * Input format  : Baris 1: R dan C
 *                 R baris berikutnya: string sepanjang C
 * Output format : "YES" atau "NO"
 * Constraints   : 1 ≤ R, C ≤ 1000
 *                 Grid berisi huruf kecil 'a'..'z'
 *
 * Sample Input 1:        Sample Output 1:
 * 3 4                    YES
 * AAAA
 * ABCA
 * AAAA
 *
 * Sample Input 2:        Sample Output 2:
 * 3 4                    NO
 * AAAA
 * ABCA
 * AADA
 *
 * Sample Input 3:        Sample Output 3:
 * 2 2                    YES
 * AA
 * AA
 *
 * NOTE Sample 1: huruf 'A' membentuk cincin mengelilingi B dan C → ada cycle.
 * NOTE Sample 2: cincin 'A' terputus di pojok kanan bawah → tidak ada cycle.
 * NOTE Sample 3: persegi 2×2 penuh 'A' = cycle terpendek yang mungkin.
 *
 * NOTE: Sample memakai huruf besar untuk keterbacaan; sesuaikan solusimu
 *       agar bekerja untuk huruf apa pun (jangan hardcode 'a'..'z').
 *
 * HINT: Soal ini setara dengan Codeforces 510B "Fox And Two Dots".
 *       Grid 1000×1000 → waspadai kedalaman rekursi.
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: DFS grid dengan cek parent berupa pasangan koordinat

    return 0;
}
