// ============================================================
// 📦 TEMPLATE — Day 50: Binary Search on Answer
// ============================================================
#include <bits/stdc++.h>
using namespace std;

#define ll long long

// 1. Template Minimalkan Jawaban X (Predikat: 0 0 0 1 1 1)
bool checkMin(ll mid) {
    // TODO: Kembalikan true jika mid VALID (memenuhi syarat)
    return true;
}

ll solveMin(ll min_possible, ll max_possible) {
    ll low = min_possible, high = max_possible;
    ll ans = high;
    while (low <= high) {
        ll mid = low + (high - low) / 2;
        if (checkMin(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}

// 2. Template Maksimalkan Jawaban X (Predikat: 1 1 1 0 0 0)
bool checkMax(ll mid) {
    // TODO: Kembalikan true jika mid VALID
    return true;
}

ll solveMax(ll min_possible, ll max_possible) {
    ll low = min_possible, high = max_possible;
    ll ans = low;
    while (low <= high) {
        ll mid = low + (high - low) / 2;
        if (checkMax(mid)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}
