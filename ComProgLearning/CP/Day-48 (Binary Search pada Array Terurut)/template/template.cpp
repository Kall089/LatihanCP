// ============================================================
// 📦 TEMPLATE — Day 48: Binary Search pada Array Terurut
// ============================================================
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(x) (x).begin(), (x).end()

// 1. Binary Search Standar (Mengembalikan Indeks / -1)
int binary_search_std(const vector<int>& a, int target) {
    int low = 0, high = (int)a.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (a[mid] == target) return mid;
        if (a[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// 2. Lower Bound Manual (Elemen Pertama >= target)
int lower_bound_manual(const vector<int>& a, int target) {
    int low = 0, high = (int)a.size();
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (a[mid] >= target) high = mid;
        else low = mid + 1;
    }
    return low;
}

// 3. Upper Bound Manual (Elemen Pertama > target)
int upper_bound_manual(const vector<int>& a, int target) {
    int low = 0, high = (int)a.size();
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (a[mid] > target) high = mid;
        else low = mid + 1;
    }
    return low;
}

void solve() {
    int n, target;
    if (!(cin >> n >> target)) return;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(all(a)); // Pastikan terurut

    int idx = binary_search_std(a, target);
    cout << "Index: " << idx << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}
