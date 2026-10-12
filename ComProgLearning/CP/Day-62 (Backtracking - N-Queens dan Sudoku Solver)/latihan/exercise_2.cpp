/*
 * Day 12 — Backtracking
 * File  : exercise_2.cpp
 * Topik : Generate All Subsets (Power Set)
 * -----------------------------------------------
 * Generate semua subset dari bilangan 1..n.
 * Cetak dalam urutan lexicographic (subset kosong juga dicetak).
 *
 * Input format  : Satu bilangan n
 * Output format : Semua subset, satu per baris (subset kosong = baris kosong)
 * Constraints   : 1 ≤ n ≤ 15
 *
 * Sample Input 1:      Sample Output 1:
 * 3                    (baris kosong)
 *                      1
 *                      1 2
 *                      1 2 3
 *                      1 3
 *                      2
 *                      2 3
 *                      3
 *
 * Sample Input 2:      Sample Output 2:
 * 2                    (baris kosong)
 *                      1
 *                      1 2
 *                      2
 */

#include <bits/stdc++.h>
using namespace std;

void subset(int i, int n, vector<int> &pilihan)
{
    // Base case: jika i sudah melewati n (1 sampai n sudah diputuskan)
    if (i > n)
    {
        // Cetak semua elemen yang ada di dalam vector 'pilihan'
        for (int j = 0; j < (int)pilihan.size(); j++)
        {
            cout << pilihan[j] << " ";
        }
        cout << "\n"; // Ganti baris (jika pilihan kosong, otomatis jadi baris kosong)
        return;
    }

    // Cabang 1: AMBIL angka i
    pilihan.push_back(i);
    subset(i + 1, n, pilihan);
    pilihan.pop_back(); // Backtrack

    // Cabang 2: LEWATI angka i
    subset(i + 1, n, pilihan);
}

int main()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> pilihan; // Dibuat di dalam main, bukan global

    // Memulai rekursi dari angka 1 sampai n
    subset(1, n, pilihan);

    return 0;
}