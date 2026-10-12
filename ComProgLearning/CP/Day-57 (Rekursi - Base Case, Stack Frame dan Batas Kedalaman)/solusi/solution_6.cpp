/*
 * Day 11 — Recursion Dasar
 * File  : solution_6.cpp
 * Topik : Palindrome Check Rekursif
 * Pendekatan: Two-pointer via recursion, O(n) time, O(n) stack
 */

#include <bits/stdc++.h>
using namespace std;

bool isPalin(const string& s, int l, int r) {
    if (l >= r) return true;          // BASE CASE: string kosong/1 karakter
    if (s[l] != s[r]) return false;   // Karakter luar tidak cocok
    return isPalin(s, l + 1, r - 1); // Cek bagian dalam
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;
        cout << (isPalin(s, 0, (int)s.size() - 1) ? "YES" : "NO") << "\n";
    }

    return 0;
}
