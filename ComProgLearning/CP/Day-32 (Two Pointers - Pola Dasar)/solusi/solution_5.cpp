/*
 * Day 19 — Two Pointers
 * File  : solution_5.cpp
 * Topik : Valid Palindrome — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: Clean string + Opposite Direction Two Pointers
 *
 * Idea:
 *   1. Bersihkan string: ambil hanya alfanumerik, jadikan lowercase
 *   2. L = 0, R = len-1
 *   3. Bandingkan clean[L] dan clean[R]
 *      - Jika tidak sama → bukan palindrome
 *      - L++, R-- lanjutkan
 *   4. Jika L >= R tanpa mismatch → palindrome
 *
 * Alternatif (tanpa membuat clean string, O(1) space):
 *   Gunakan dua pointer langsung pada string asli,
 *   skip karakter non-alphanumeric dengan while loop.
 *
 * Complexity: O(n) time, O(n) space (clean string)
 *            atau O(n) time, O(1) space (in-place)
 *
 * Verifikasi sample:
 *   "A man a plan a canal Panama"
 *   clean = "amanaplanacanalpanama"
 *   Ini palindrome → YES ✓
 *
 *   "race a car"
 *   clean = "raceacar"
 *   r vs r ✓, a vs a ✓, c vs c ✓, e vs a ✗ → NO ✓
 *
 *   "Was it a car or a cat I saw"
 *   clean = "wasitacaroracatisaw"
 *   Palindrome → YES ✓
 */

#include <bits/stdc++.h>
using namespace std;

bool isPalindrome(const string& s) {
    // Build clean string
    string clean = "";
    for (char c : s) {
        if (isalpha(c)) clean += (char)tolower(c);
        else if (isdigit(c)) clean += c;
    }

    // Two pointers from both ends
    int L = 0, R = (int)clean.size() - 1;
    while (L < R) {
        if (clean[L] != clean[R]) return false;
        L++;
        R--;
    }
    return true;
}

// Alternatif: O(1) space, langsung pada string asli
bool isPalindromeInPlace(const string& s) {
    int L = 0, R = (int)s.size() - 1;
    while (L < R) {
        // Skip non-alphanumeric dari kiri
        while (L < R && !isalnum(s[L])) L++;
        // Skip non-alphanumeric dari kanan
        while (L < R && !isalnum(s[R])) R--;
        // Bandingkan (case-insensitive)
        if (L < R && tolower(s[L]) != tolower(s[R])) return false;
        L++;
        R--;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;
    cin.ignore();  // abaikan newline setelah angka Q

    while (q--) {
        string s;
        getline(cin, s);
        // Menggunakan versi O(1) space
        cout << (isPalindromeInPlace(s) ? "YES" : "NO") << "\n";
    }

    return 0;
}
