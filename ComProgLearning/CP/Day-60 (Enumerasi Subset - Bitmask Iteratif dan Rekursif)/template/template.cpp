/*
============================================================
  Day 13 — Bitmask Enumeration | CP Template
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

// Fast I/O
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)

// Types
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;

// Constants
const int INF = 1e9;
const ll LLINF = 1e18;
const int MOD = 1e9 + 7;

// Bitmask macros
#define BIT(mask, i)     (((mask) >> (i)) & 1)        // cek bit ke-i
#define SETBIT(mask, i)  ((mask) | (1 << (i)))        // set bit ke-i
#define CLRBIT(mask, i)  ((mask) & ~(1 << (i)))       // clear bit ke-i
#define TOGBIT(mask, i)  ((mask) ^ (1 << (i)))        // toggle bit ke-i
#define LOWBIT(mask)     ((mask) & -(mask))            // lowest set bit
#define POPCOUNT(x)      __builtin_popcount(x)         // hitung bit aktif
#define POPCOUNTLL(x)    __builtin_popcountll(x)       // untuk long long

// Iterate all subsets of n elements: O(2^n)
// for (int mask = 0; mask < (1<<n); mask++) { ... }

// Iterate all subsets of a given mask: O(3^n) total across all masks
// for (int sub = mask; sub > 0; sub = (sub-1) & mask) { ... }

// Shorthand
#define all(x)   (x).begin(), (x).end()
#define sz(x)    (int)(x).size()
#define pb       push_back
#define mp       make_pair

// Debug
#ifdef LOCAL
#define dbg(x) cerr << #x << " = " << (x) << "\n"
#else
#define dbg(x)
#endif

int main() {
    FASTIO;

    // TODO: write solution here

    return 0;
}
