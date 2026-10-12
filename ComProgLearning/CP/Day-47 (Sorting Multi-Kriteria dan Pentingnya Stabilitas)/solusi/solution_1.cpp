// Day 16 — Custom Comparator
// File  : solution_1.cpp

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point {
    int x, y;
    bool operator<(const Point& o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<Point> pts(n);
    for (int i = 0; i < n; i++) cin >> pts[i].x >> pts[i].y;

    sort(pts.begin(), pts.end());

    for (auto& p : pts)
        cout << p.x << " " << p.y << "\n";

    return 0;
}
