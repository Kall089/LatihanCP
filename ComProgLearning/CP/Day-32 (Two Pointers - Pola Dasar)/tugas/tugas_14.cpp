/*
 * Day 19 — Two Pointers
 * File  : tugas_14.cpp
 * Topik : Palindrome Pairs
 * Tingkat: Hard
 * -----------------------------------------------
 * Diberikan daftar N kata (string). Temukan semua pasangan indeks (i, j) dengan
 * i != j sehingga penggabungan words[i] + words[j] membentuk palindrome.
 * Output jumlah pasangan, diikuti pasangan-pasangan tersebut.
 *
 * Catatan: (i, j) dan (j, i) dianggap berbeda jika keduanya valid.
 *
 * Pendekatan Brute Force O(n² × |w|):
 *   - Untuk setiap pasangan (i,j), cek apakah words[i]+words[j] adalah palindrome
 *   - Cek palindrome: gunakan two pointers dari ujung string gabungan
 *
 * Pendekatan Optimal O(n × |w|²) dengan HashMap:
 *   - Simpan semua kata dalam hash map (kata → indeks)
 *   - Untuk setiap kata w[i], split menjadi prefix p dan suffix s
 *   - Jika p adalah palindrome dan reverse(s) ada di map → pasangan valid
 *   - Jika s adalah palindrome dan reverse(p) ada di map → pasangan valid
 *
 * Untuk latihan ini, implementasikan brute force O(n²) terlebih dahulu.
 * Constraints cukup kecil (N ≤ 300) untuk solusi O(n² × |w|).
 *
 * Input format  : Baris 1: N
 *                 Baris 2..N+1: Masing-masing satu kata (lowercase letters)
 * Output format : Baris 1: jumlah pasangan
 *                 Baris 2...: pasangan i j (0-indexed, satu per baris)
 *                 (Output pasangan secara lexicographic order: i naik, j naik)
 * Constraints   : 1 ≤ N ≤ 300
 *                 1 ≤ |words[i]| ≤ 300
 *                 Semua kata berisi lowercase letters
 *                 Semua kata unik
 *
 * Sample Input 1:
 * 3
 * abcd
 * dcba
 * lls
 *
 * Sample Output 1:
 * 2
 * 0 1
 * 1 0
 *
 * Sample Input 2:
 * 4
 * abcd
 * dcba
 * lls
 * s
 *
 * Sample Output 2:
 * 4
 * 0 1
 * 1 0
 * 2 3 ← "llss" bukan palindrome. Wait: words[2]="lls", words[3]="s" → "llss"? Bukan palindrome.
 *       words[3]="s", words[2]="lls" → "slls" → palindrome!
 *       words[2]+"s"="llss" bukan palindrome.
 *
 * (Dikoreksi: Sample 2 output:
 *  i=0,j=1: "abcd"+"dcba"="abcddcba" palindrome ✓
 *  i=1,j=0: "dcba"+"abcd"="dcbaabcd" palindrome ✓
 *  i=3,j=2: "s"+"lls"="slls" palindrome ✓
 *  i=2,j=3: "lls"+"s"="llss" bukan palindrome
 *  Total: 3)
 *
 * Sample Output 2 (dikoreksi):
 * 3
 * 0 1
 * 1 0
 * 3 2
 *
 * Fungsi helper yang berguna:
 *   bool isPalin(const string& s, int L, int R) {
 *       while (L < R) { if (s[L] != s[R]) return false; L++; R--; }
 *       return true;
 *   }
 *   // Two pointers untuk cek palindrome substring
 */

#include <bits/stdc++.h>
using namespace std;

bool isPalin(const string& s) {
    int L = 0, R = (int)s.size() - 1;
    while (L < R) {
        if (s[L] != s[R]) return false;
        L++; R--;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Tulis solusimu di sini

    return 0;
}
