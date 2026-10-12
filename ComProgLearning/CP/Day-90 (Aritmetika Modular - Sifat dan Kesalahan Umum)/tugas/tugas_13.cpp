/*
 * Day 22 — Aritmatika Modular
 * File  : tugas_13.cpp
 * Topik : Polynomial Hash Prefix (Aplikasi Modular ke String)
 * Tingkat: Hard ★★★☆☆
 * -----------------------------------------------
 * Diberikan string S berisi huruf kecil 'a'..'z'.
 * Hitung POLYNOMIAL HASH untuk setiap prefix S[0..i], didefinisikan:
 *
 *   h(0)  = val(S[0])
 *   h(i)  = (h(i-1) × B + val(S[i])) mod P
 *
 * dengan B = 31 (basis) dan P = 10^9+7, serta val(c) = c - 'a' + 1
 * (jadi 'a'=1, 'b'=2, ..., 'z'=26).
 *
 * Cetak N nilai hash prefix, dipisah spasi.
 *
 * Perhatikan bahwa rumus ini PERSIS Horner's rule dari exercise_4 —
 * hanya basisnya 31 alih-alih 10, dan "digit"-nya adalah huruf.
 * Inilah fondasi String Hashing yang akan dipelajari penuh di Day 33.
 *
 * ⚠️ Overflow: h < P ≈ 10^9, dikalikan B=31 → ~3.1×10^10.
 *    Muat di long long, TIDAK muat di int.
 *
 * ⚠️ Mengapa val('a') = 1 dan bukan 0? Kalau 'a' bernilai 0, maka
 *    "a", "aa", "aaa" semuanya berhash 0 — collision langsung.
 *
 * Input format  : Baris 1: string S
 * Output format : N bilangan dipisah spasi (hash tiap prefix)
 * Constraints   : 1 ≤ panjang(S) ≤ 200.000
 *                 S hanya berisi 'a'..'z'
 *
 * Sample Input 1:        Sample Output 1:
 * abc                    1 33 1026
 *
 * Sample Input 2:        Sample Output 2:
 * z                      26
 *
 * Sample Input 3:        Sample Output 3:
 * aaa                    1 32 993
 *
 * NOTE Sample 1: h(0) = 1 ('a')
 *                h(1) = 1×31 + 2 = 33 ('b' = 2)
 *                h(2) = 33×31 + 3 = 1023 + 3 = 1026 ('c' = 3)
 * NOTE Sample 3: h = 1 → 1×31+1 = 32 → 32×31+1 = 993
 *                Perhatikan hash-nya BERBEDA meski hurufnya sama —
 *                inilah gunanya val('a') = 1.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;
const ll BASE = 31;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: kerjakan dengan Horner's rule basis 31

    return 0;
}
