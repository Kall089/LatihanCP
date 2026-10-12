/*
 * Day 11 — Recursion Dasar
 * Template C++ dengan pola rekursi umum
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 105;
ll memo[MAXN];

// ── Factorial ──
ll factorial(int n) {
    if (n == 0) return 1LL;
    return (ll)n * factorial(n - 1);
}

// ── Fibonacci dengan memoization ──
ll fib(int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = fib(n-1) + fib(n-2);
}

// ── Fast Power O(log b) ──
ll fastpow(ll base, ll exp, ll mod) {
    if (exp == 0) return 1LL;
    ll half = fastpow(base, exp / 2, mod);
    ll half2 = (half * half) % mod;
    if (exp % 2 == 0) return half2;
    return (base % mod * half2) % mod;
}

// ── GCD & LCM ──
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

// ── Palindrome ──
bool isPalin(const string& s, int l, int r) {
    if (l >= r) return true;
    if (s[l] != s[r]) return false;
    return isPalin(s, l+1, r-1);
}

// ── Tower of Hanoi ──
void hanoi(int n, char src, char dst, char via) {
    if (n == 0) return;
    hanoi(n-1, src, via, dst);
    cout << "Move disk " << n << " from " << src << " to " << dst << "\n";
    hanoi(n-1, via, dst, src);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    memset(memo, -1, sizeof(memo));

    return 0;
}
