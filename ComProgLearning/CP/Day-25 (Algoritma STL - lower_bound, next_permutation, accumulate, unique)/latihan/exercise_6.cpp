/*
 * Day 6 — STL Algorithms
 * File  : exercise_6.cpp
 * Topik : Sort Struct & Multi-Criteria — Custom Comparator
 * -----------------------------------------------
 * Sort daftar siswa: pertama by nilai descending, jika sama by nama ascending.
 *
 * Input format  : Baris 1: n
 *                 Baris 2..n+1: nama nilai per siswa
 * Output format : Daftar siswa setelah sort (satu per baris: nama nilai)
 * Constraints   : 1 ≤ n ≤ 10^5, |nama| ≤ 20, 0 ≤ nilai ≤ 100
 *
 * Sample Input 1:      Sample Output 1:
 * 4                    Alice 90
 * Alice 90             Charlie 90
 * Bob 85               Bob 85
 * Charlie 90           Diana 85
 * Diana 85
 *
 * Sample Input 2:      Sample Output 2:
 * 3                    Mike 80
 * Zara 70              Anna 70
 * Anna 70              Zara 70
 * Mike 80
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Student {
    string name;
    int score;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<Student> students(n);
    for (int i = 0; i < n; i++)
        cin >> students[i].name >> students[i].score;

    // TODO: Sort by score descending, jika sama by name ascending
    // sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
    //     if (a.score != b.score) return a.score > b.score; // nilai desc
    //     return a.name < b.name;                           // nama asc
    // });

    for (auto& s : students)
        cout << s.name << " " << s.score << "\n";

    return 0;
}
