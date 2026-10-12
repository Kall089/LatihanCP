/*
 * Day 19 — Two Pointers
 * File  : exercise_5.cpp
 * Topik : Valid Palindrome (ignore non-alphanumeric, case-insensitive)
 * -----------------------------------------------
 * Sebuah string disebut palindrome jika setelah hanya mempertimbangkan karakter
 * alphanumeric (huruf dan angka) dan mengabaikan huruf kapital, string tersebut
 * terbaca sama dari kiri dan kanan.
 *
 * Diberikan Q query, masing-masing berisi satu baris string. Untuk setiap
 * string, output "YES" jika merupakan palindrome, "NO" jika bukan.
 *
 * Strategi two pointers:
 *   1. Bersihkan string: ambil hanya karakter alphanumeric, jadikan lowercase
 *   2. L = 0, R = len-1
 *   3. Jika clean[L] != clean[R] → bukan palindrome
 *   4. L++, R-- lanjutkan sampai L >= R
 *
 * Input format  : Baris 1: Q (1 ≤ Q ≤ 100)
 *                 Baris 2..Q+1: Masing-masing satu baris string
 * Output format : Untuk setiap query: "YES" atau "NO"
 * Constraints   : 1 ≤ Q ≤ 100
 *                 1 ≤ |string| ≤ 2×10^5
 *                 String hanya berisi karakter ASCII printable
 *
 * Sample Input 1:
 * 3
 * A man a plan a canal Panama
 * race a car
 * Was it a car or a cat I saw
 *
 * Sample Output 1:
 * YES
 * NO
 * YES
 *
 * Sample Input 2:
 * 2
 * racecar
 * hello
 *
 * Sample Output 2:
 * YES
 * NO
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int q;
    cin >> q;
    cin.ignore();  // abaikan newline setelah angka Q

    while (q--) {
        string s;
        getline(cin, s);

        // TODO: implementasikan cek palindrome dengan two pointers
        // Langkah 1: buat string clean hanya alphanumeric lowercase
        // string clean = "";
        // for (char c : s) {
        //     if (isalpha(c)) clean += tolower(c);
        //     else if (isdigit(c)) clean += c;
        // }
        //
        // Langkah 2: two pointers dari ujung
        // int L = 0, R = (int)clean.size() - 1;
        // bool ok = true;
        // while (L < R) {
        //     if (clean[L] != clean[R]) { ok = false; break; }
        //     L++; R--;
        // }
        // cout << (ok ? "YES" : "NO") << "\n";
    }

    return 0;
}
