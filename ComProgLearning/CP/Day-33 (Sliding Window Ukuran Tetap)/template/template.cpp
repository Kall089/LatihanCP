/*
 * Day 20 — Sliding Window
 * Template C++ dengan pola-pola sliding window
 *
 * Pilih pola yang sesuai dengan problem, hapus yang tidak diperlukan.
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// ──────────────────────────────────────────────────────────────────
// POLA 1: FIXED-SIZE WINDOW (ukuran K tetap)
// Use for: max/min/avg subarray ukuran K, count fitur per window
// Idea  : maintain sum/count, slide dengan add(A[R])-remove(A[L])
// ──────────────────────────────────────────────────────────────────
//
// int n, k; cin >> n >> k;
// vector<ll> A(n);
// for (auto& x : A) cin >> x;
//
// ll sum = 0;
// for (int i = 0; i < k; i++) sum += A[i];   // initial window
// ll ans = sum;
// for (int i = k; i < n; i++) {
//     sum += A[i] - A[i - k];                // slide: + new, - old
//     ans = max(ans, sum);
// }
// cout << ans << "\n";

// ──────────────────────────────────────────────────────────────────
// POLA 2: VARIABLE-SIZE WINDOW (Longest valid)
// Use for: longest subarray/substring dengan constraint
// Idea  : expand R selalu, shrink L sampai window valid
// ──────────────────────────────────────────────────────────────────
//
// int L = 0, ans = 0;
// for (int R = 0; R < n; R++) {
//     // add A[R] ke window
//     while (window_invalid()) {
//         // remove A[L] dari window
//         L++;
//     }
//     ans = max(ans, R - L + 1);
// }

// ──────────────────────────────────────────────────────────────────
// POLA 3: VARIABLE-SIZE WINDOW (Shortest valid)
// Use for: smallest subarray dengan sum ≥ S (atau constraint serupa)
// Idea  : expand R sampai valid, shrink L sambil tetap valid
// Pre-condition: nilai non-negatif (untuk sum-based)
// ──────────────────────────────────────────────────────────────────
//
// int L = 0;
// int ans = INT_MAX;
// ll sum = 0;
// for (int R = 0; R < n; R++) {
//     sum += A[R];
//     while (sum >= S) {                     // valid → coba shrink
//         ans = min(ans, R - L + 1);
//         sum -= A[L];
//         L++;
//     }
// }

// ──────────────────────────────────────────────────────────────────
// POLA 4: VARIABLE-SIZE WINDOW + FREQUENCY MAP
// Use for: longest substring with at most/exactly K distinct chars
// ──────────────────────────────────────────────────────────────────
//
// unordered_map<char, int> freq;
// int L = 0, ans = 0;
// for (int R = 0; R < n; R++) {
//     freq[s[R]]++;
//     while ((int)freq.size() > K) {         // contoh constraint
//         freq[s[L]]--;
//         if (freq[s[L]] == 0) freq.erase(s[L]);
//         L++;
//     }
//     ans = max(ans, R - L + 1);
// }

// ──────────────────────────────────────────────────────────────────
// POLA 5: MONOTONIC DEQUE — Window Max O(n)
// Use for: maximum tiap window ukuran K
// Idea  : deque menyimpan INDEX dengan A[idx] decreasing dari front
//         dq.front() = index elemen terbesar di window saat ini
// ──────────────────────────────────────────────────────────────────
//
// deque<int> dq;   // simpan INDEX (bukan nilai)
// for (int i = 0; i < n; i++) {
//     // 1. Buang index yang sudah keluar window
//     while (!dq.empty() && dq.front() <= i - k)
//         dq.pop_front();
//     // 2. Buang index dengan nilai ≤ A[i] dari belakang
//     //    (mereka tidak akan pernah jadi max selama A[i] ada)
//     while (!dq.empty() && A[dq.back()] <= A[i])
//         dq.pop_back();
//     // 3. Tambah index sekarang
//     dq.push_back(i);
//     // 4. Output ketika window penuh
//     if (i >= k - 1) cout << A[dq.front()] << " ";
// }

// ──────────────────────────────────────────────────────────────────
// POLA 6: MONOTONIC DEQUE — Window Min O(n)
// Sama seperti POLA 5, tapi maintain increasing order
// ──────────────────────────────────────────────────────────────────
//
// deque<int> dq;
// for (int i = 0; i < n; i++) {
//     while (!dq.empty() && dq.front() <= i - k)
//         dq.pop_front();
//     while (!dq.empty() && A[dq.back()] >= A[i])  // ≥ untuk min
//         dq.pop_back();
//     dq.push_back(i);
//     if (i >= k - 1) cout << A[dq.front()] << " ";
// }

// ──────────────────────────────────────────────────────────────────
// POLA 7: "EXACTLY K" → "AT MOST K" - "AT MOST K-1"
// Trick: Subarray dengan EXACTLY K distinct =
//        atMost(K) - atMost(K-1)
// ──────────────────────────────────────────────────────────────────
//
// long long atMostK(vector<int>& A, int K) {
//     unordered_map<int,int> freq;
//     int L = 0;
//     long long ans = 0;
//     for (int R = 0; R < (int)A.size(); R++) {
//         freq[A[R]]++;
//         while ((int)freq.size() > K) {
//             freq[A[L]]--;
//             if (freq[A[L]] == 0) freq.erase(A[L]);
//             L++;
//         }
//         ans += (R - L + 1);  // semua subarray berakhiran R
//     }
//     return ans;
// }
// long long ans = atMostK(A, K) - atMostK(A, K - 1);

// ──────────────────────────────────────────────────────────────────
// MAIN
// ──────────────────────────────────────────────────────────────────

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Baca input
    int n;
    cin >> n;
    vector<int> A(n);
    for (auto& x : A) cin >> x;

    // Pilih dan implementasikan pola yang sesuai di sini

    return 0;
}
