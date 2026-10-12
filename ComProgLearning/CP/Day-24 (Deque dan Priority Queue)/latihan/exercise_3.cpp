/*
 * Day 39 — Priority Queue & Heap Applications
 * File  : exercise_3.cpp
 * Topik : Task Scheduler (CPU Cooldown)
 * -----------------------------------------------
 * Diberikan task dengan cooldown n, temukan waktu minimum penyelesaian semua task.
 *
 * Input format:
 * Baris 1: n (cooldown)
Baris 2: string task (A-Z)
 *
 * Output format:
 * Satu bilangan: waktu minimum
 *
 * Constraints:
 * 1 ≤ |tasks| ≤ 10^4, 0 ≤ n ≤ 100
 *
 * Sample Input 1:
 * 2
 * AAABBB
 *
 * Sample Output 1:
 * 8
 *
 * Sample Input 2:
 * 0
 * AAABBB
 *
 * Sample Output 2:
 * 6
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    string tasks;
    cin >> n >> tasks;

    // TODO: Hitung waktu minimum dengan greedy + max-heap
    // Hint:
    // 1. Hitung frekuensi tiap task
    // 2. Gunakan max-heap (frekuensi terbesar duluan)
    // 3. Simulasikan siklus n+1 slot per ronde
    //    - Ambil task dari heap, kurangi frek, tambah ke cooldown queue
    //    - Setelah n+1 slot, kembalikan task dari cooldown ke heap

    cout << 0 << "\n"; // ganti dengan jawaban
    return 0;
}
