/*
 * Day 16 — Custom Comparator
 * Template C++ dengan helper comparator
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

// ── Struct template ──
struct Item {
    int val, idx;
    // operator< untuk auto-sort (ascending by val, then idx)
    bool operator<(const Item& o) const {
        if (val != o.val) return val < o.val;
        return idx < o.idx;
    }
};

// ── Functor template ──
struct CompDesc {
    bool operator()(const Item& a, const Item& b) const {
        return a.val > b.val; // descending
    }
};

// ── Useful macros ──
#define all(v) (v).begin(), (v).end()
#define sz(v)  (int)(v).size()

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Sort dengan lambda
    vector<Item> v;
    sort(all(v), [](const Item& a, const Item& b){
        return a.val < b.val;
    });

    // Min-heap dengan functor
    priority_queue<Item, vector<Item>, CompDesc> pq;

    // Index sort
    int n = sz(v);
    vector<int> idx(n); iota(all(idx), 0);
    sort(all(idx), [&](int i, int j){ return v[i].val < v[j].val; });

    return 0;
}
