/*
 * Day 16 — Custom Comparator
 * File  : exercise_6.cpp
 * Topik : Version String Sort
 * -----------------------------------------------
 * Sort version strings secara semantic (1.10.3 > 1.9.5 karena 10 > 9).
 *
 * Input format  : Baris 1: n
Baris 2..n+1: version string
 * Output format : Version strings setelah sort ascending
 * Constraints   : 1 ≤ n ≤ 1000, format: major.minor.patch (semua non-negatif)
 *
 * Sample Input 1:      Sample Output 1:
 * 4                    1.9.5
 * 1.10.3               1.10.1
 * 1.9.5                1.10.3
 * 2.0.0                2.0.0
 * 1.10.1
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> parseVer(const string& s) {
    vector<int> parts;
    stringstream ss(s);
    string tok;
    while (getline(ss, tok, '.'))
        parts.push_back(stoi(tok));
    return parts;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<string> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    // TODO: Sort dengan lambda yang membandingkan parsed version
    // sort(v.begin(), v.end(), [](const string& a, const string& b){
    //     return parseVer(a) < parseVer(b); // vector<int> mendukung operator<
    // });

    for (auto& s : v) cout << s << "\n";

    return 0;
}
