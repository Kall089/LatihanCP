/*
 * Day 16 — Custom Comparator
 * File  : exercise_3.cpp
 * Topik : Multi-Criteria Lambda — 3+ Kriteria
 * -----------------------------------------------
 * Sort tasks: deadline ascending, jika sama priority descending, jika sama name ascending. Gunakan lambda.
 *
 * Input format  : Baris 1: n
Baris 2..n+1: name deadline priority
 * Output format : Tasks setelah sort, satu per baris
 * Constraints   : 1 ≤ n ≤ 10^5
 *
 * Sample Input 1:      Sample Output 1:
 * 4                    D 3 2
 * A 5 2                B 3 1
 * B 3 1                C 5 3
 * C 5 3                A 5 2
 * D 3 2
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Task {
    string name;
    int deadline, priority;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<Task> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i].name >> v[i].deadline >> v[i].priority;

    // TODO: Sort dengan lambda, 3 kriteria:
    // 1. deadline ascending
    // 2. priority descending (jika deadline sama)
    // 3. name ascending (jika deadline & priority sama)
    //
    // sort(v.begin(), v.end(), [](const Task& a, const Task& b) {
    //     if (a.deadline != b.deadline) return a.deadline < b.deadline;
    //     if (a.priority != b.priority) return a.priority > b.priority;
    //     return a.name < b.name;
    // });

    for (auto& t : v)
        cout << t.name << " " << t.deadline << " " << t.priority << "\n";

    return 0;
}
