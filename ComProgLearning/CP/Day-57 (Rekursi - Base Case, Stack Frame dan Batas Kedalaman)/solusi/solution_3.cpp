/*
 * Day 11 — Recursion Dasar
 * File  : solution_3.cpp
 * Topik : Tower of Hanoi
 * Pendekatan: Divide & conquer, O(2^n - 1) langkah (optimal)
 */

#include <bits/stdc++.h>
using namespace std;

void hanoi(int n, char src, char dst, char via) {
    if (n == 0) return;                    // BASE CASE: tidak ada disk
    hanoi(n-1, src, via, dst);             // Pindah n-1 disk src→via
    cout << "Move disk " << n << " from " << src << " to " << dst << "\n";
    hanoi(n-1, via, dst, src);             // Pindah n-1 disk via→dst
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    hanoi(n, 'A', 'C', 'B');

    return 0;
}
