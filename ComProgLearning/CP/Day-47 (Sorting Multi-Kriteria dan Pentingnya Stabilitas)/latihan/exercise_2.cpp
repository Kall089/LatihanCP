/*
 * Day 16 — Custom Comparator
 * File  : exercise_2.cpp
 * Topik : Comparator Functor Struct
 * -----------------------------------------------
 * Sort daftar siswa: score descending, jika sama name ascending, jika sama age ascending. Gunakan functor struct.
 *
 * Input format  : Baris 1: n
Baris 2..n+1: name score age
 * Output format : Nama dan score setelah sort, satu per baris
 * Constraints   : 1 ≤ n ≤ 10^5
 *
 * Sample Input 1:      Sample Output 1:
 * 4                    Alice 90
 * Alice 90 20          Charlie 90
 * Bob 85 22            Bob 85
 * Charlie 90 21        Dave 85
 * Dave 85 21
 */

#include <bits/stdc++.h>
using namespace std;

struct Siswa
{
    string nama;
};
int main()
{
}