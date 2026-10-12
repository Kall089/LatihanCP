/*
 * Day 11 — Recursion Dasar
 * File  : exercise_3.cpp
 * Topik : Tower of Hanoi
 * -----------------------------------------------
 * Pindahkan semua n disk dari tiang A ke tiang C
 * menggunakan tiang B sebagai perantara.
 * Aturan:
 *   - Hanya 1 disk yang boleh dipindahkan per langkah
 *   - Disk besar tidak boleh di atas disk kecil
 *
 * Output setiap langkah: "Move disk D from X to Y"
 * (D = nomor disk, X = tiang asal, Y = tiang tujuan)
 *
 * Input format  : Satu bilangan n
 * Output format : Urutan langkah pemindahan
 * Constraints   : 1 ≤ n ≤ 15
 *
 * Sample Input 1:      Sample Output 1:
 * 2                    Move disk 1 from A to B
 *                      Move disk 2 from A to C
 *                      Move disk 1 from B to C
 *
 * Sample Input 2:      Sample Output 2:
 * 1                    Move disk 1 from A to C
 */

#include <bits/stdc++.h>
using namespace std;

// TODO: Implementasikan Tower of Hanoi rekursif
// Strategi:
//   1. Pindahkan (n-1) disk dari src ke via (pakai dst sebagai perantara)
//   2. Cetak: "Move disk n from src to dst"
//   3. Pindahkan (n-1) disk dari via ke dst (pakai src sebagai perantara)
// BASE CASE: n == 0, tidak lakukan apa-apa
void hanoi(int n, char src, char dst, char via) {
    // TODO: isi implementasi di sini
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    hanoi(n, 'A', 'C', 'B'); // Pindah dari A ke C, pakai B

    return 0;
}
