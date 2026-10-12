/*
 * Day 16 — Custom Comparator
 * File  : exercise_1.cpp
 * Topik : operator< Overloading pada Struct Point
 * -----------------------------------------------
 * Sort array titik (x, y): utamakan x ascending, jika sama y ascending. Gunakan operator<.
 *
 * Input format  : Baris 1: n
Baris 2..n+1: x y per titik
 * Output format : Titik-titik setelah sort, satu per baris
 * Constraints   : 1 ≤ n ≤ 10^5, -10^9 ≤ x,y ≤ 10^9
 *
 * Sample Input 1:      Sample Output 1:
 * 3                    1 2
 * 3 1                  1 5
 * 1 5                  3 1
 * 1 2
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Point
{
    int x, y;
};

int main()
{
    int n;
    cin >> n;

    vector<Point> p(n);

    for (int i = 0; i < n; i++)
    {
        cin >> p[i].x >> p[i].y;
    }

    auto customCompare = [](const Point &a, const Point &b)
    {
        if (a.x != b.x)
            return a.x < b.x;
        return a.y < b.y;
    };

    sort(p.begin(), p.end(), customCompare);

    for (int i = 0; i < n; i++)
    {
        cout << p[i].x << " " << p[i].y << endl;
    }
}