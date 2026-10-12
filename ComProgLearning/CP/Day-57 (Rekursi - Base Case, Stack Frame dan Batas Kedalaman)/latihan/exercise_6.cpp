/*
 * Day 11 — Recursion Dasar
 * File  : exercise_6.cpp
 * Topik : Palindrome Check Rekursif
 * -----------------------------------------------
 * Untuk setiap string yang diberikan, tentukan apakah palindrome.
 * Gunakan rekursi dua pointer (l dari kiri, r dari kanan).
 *
 * Definisi palindrome: dibaca sama dari kiri maupun kanan.
 *
 * Strategi rekursif:
 *   - BASE CASE: l >= r → semua karakter cocok → TRUE
 *   - Jika s[l] != s[r] → bukan palindrome → FALSE
 *   - Rekursi: cek isPalin(s, l+1, r-1)
 *
 * Input format  : Baris 1: q (jumlah string)
 *                 Baris 2..q+1: satu string per baris
 * Output format : "YES" atau "NO" per baris
 * Constraints   : 1 ≤ q ≤ 10^4, 1 ≤ |s| ≤ 10^3 (hanya huruf kecil)
 *
 * Sample Input 1:      Sample Output 1:
 * 4                    YES
 * racecar              NO
 * hello                YES
 * madam                YES
 * a
 */

#include <bits/stdc++.h>
using namespace std;

// TODO: Implementasikan isPalin rekursif
// Parameter: s = string, l = pointer kiri, r = pointer kanan
// BASE CASE: l >= r → return true
// Jika s[l] != s[r] → return false
// Rekursi: return isPalin(s, l+1, r-1)
bool isPalin(const string& s, int l, int r) {
    // TODO: isi implementasi di sini
    return false; // ganti ini
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;

    while (q--) {
        string s;
        cin >> s;
        bool result = isPalin(s, 0, (int)s.size() - 1);
        cout << (result ? "YES" : "NO") << "\n";
    }

    return 0;
}
