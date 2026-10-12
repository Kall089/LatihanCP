// Day 16 — Custom Comparator
// File  : solution_2.cpp

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Student {
    string name;
    int score, age;
};

struct CompStudent {
    bool operator()(const Student& a, const Student& b) const {
        if (a.score != b.score) return a.score > b.score;
        if (a.name != b.name) return a.name < b.name;
        return a.age < b.age;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<Student> v(n);
    for (int i = 0; i < n; i++)
        cin >> v[i].name >> v[i].score >> v[i].age;

    sort(v.begin(), v.end(), CompStudent{});

    for (auto& s : v)
        cout << s.name << " " << s.score << "\n";

    return 0;
}
