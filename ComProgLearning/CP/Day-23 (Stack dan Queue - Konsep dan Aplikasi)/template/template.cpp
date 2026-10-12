// ============================================================
// 📦 TEMPLATE — Day 5: STL Containers 3 (Stack, Queue, Deque, PQ)
// ============================================================
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>
#define pii pair<int,int>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define F first
#define S second

const int MOD = 1e9 + 7;
const ll INF = 1e18;
const int MAXN = 2e5 + 5;

void solve() {
    // === STACK ===
    // stack<int> st;
    // st.push(x); st.pop(); st.top(); st.empty();

    // === QUEUE ===
    // queue<int> q;
    // q.push(x); q.pop(); q.front(); q.back();

    // === DEQUE ===
    // deque<int> dq;
    // dq.push_front(x); dq.push_back(x);
    // dq.pop_front(); dq.pop_back();
    // dq.front(); dq.back(); dq[i];

    // === PRIORITY QUEUE ===
    // priority_queue<int> pq;                          // MAX heap
    // priority_queue<int,vector<int>,greater<int>> pq; // MIN heap
    // pq.push(x); pq.pop(); pq.top();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}
