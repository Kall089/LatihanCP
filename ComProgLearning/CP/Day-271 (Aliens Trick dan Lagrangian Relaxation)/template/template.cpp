/*
============================================================
📦 TEMPLATE BOILERPLATE: Aliens Trick / Lagrangian Relaxation
============================================================
Day: 271 | Topic: Aliens Trick (WQS Binary Search)
Standard: C++17 Competitive Programming Master Template

Konsep Utama:
Menghilangkan dimensi batas operasi K pada DP dengan memperkenalkan penalti biaya lambda,
lalu menggunakan Binary Search untuk mencari lambda* yang menghasilkan tepat K operasi.

Kapan Menggunakan:
1. Fungsi biaya f(k) dengan k operasi bersifat konveks (atau konkaf untuk maksimasi).
2. Transisi DP tanpa batas k dapat dihitung cepat (misal O(N) dengan CHT atau State Machine).
3. Kompleksitas akhir: O(Kompleksitas_DP_1D * log(Range_Lambda)).

Modul yang tersedia:
1. `AliensMaxProfit`: Maksimasi keuntungan dengan pembatasan operasi K.
2. `AliensMinPartitionCHT`: Minimasi kuadratik partisi K segmen + Monotonic CHT Deque.
3. `AliensIntervals`: Pemilihan K interval tak tumpang tindih berbobot maksimum.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128_t int128;

// ============================================================
// 1. AliensMinPartitionCHT: Minimasi Kuadratik Partisi K Segmen
// ============================================================
namespace AliensCHT {
    struct Line {
        ll m, c;
        int cnt;
        ll eval(ll x) const { return m * x + c; }
    };

    inline bool bad(const Line& l1, const Line& l2, const Line& l3) {
        return (int128)(l2.c - l1.c) * (l2.m - l3.m) >= (int128)(l3.c - l2.c) * (l1.m - l2.m);
    }

    struct DPRes {
        ll val;
        int cnt;
    };

    DPRes run_dp(int n, const vector<ll>& pref, ll lambda) {
        deque<Line> dq;
        dq.push_back({0, 0, 0});

        ll dp_val = 0;
        int dp_cnt = 0;

        for (int i = 1; i <= n; i++) {
            ll x = pref[i];
            while (dq.size() >= 2) {
                ll v1 = dq[0].eval(x);
                ll v2 = dq[1].eval(x);
                if (v2 < v1 || (v2 == v1 && dq[1].cnt < dq[0].cnt)) {
                    dq.pop_front();
                } else {
                    break;
                }
            }

            dp_val = dq[0].eval(x) + x * x + lambda;
            dp_cnt = dq[0].cnt + 1;

            Line new_line = {-2 * pref[i], dp_val + pref[i] * pref[i], dp_cnt};
            while (dq.size() >= 2 && bad(dq[dq.size() - 2], dq.back(), new_line)) {
                dq.pop_back();
            }
            dq.push_back(new_line);
        }

        return {dp_val, dp_cnt};
    }

    ll solve(int n, int k, const vector<ll>& a) {
        vector<ll> pref(n + 1, 0);
        for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + a[i];

        ll low = 0, high = pref[n] * pref[n];
        ll best_lambda = 0;

        while (low <= high) {
            ll mid = low + (high - low) / 2;
            DPRes res = run_dp(n, pref, mid);
            if (res.cnt <= k) {
                best_lambda = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        DPRes res = run_dp(n, pref, best_lambda);
        return res.val - (ll)k * best_lambda;
    }
}

// ============================================================
// 2. AliensStock: Maksimasi dengan K Transaksi (State Machine)
// ============================================================
namespace AliensStock {
    struct State {
        ll val;
        int cnt;
        bool operator<(const State& o) const {
            if (val != o.val) return val < o.val;
            return cnt < o.cnt;
        }
    };

    State run_dp(int n, const vector<ll>& p, ll lambda) {
        State free = {0, 0};
        State hold = {-p[0], 0};

        for (int i = 1; i < n; i++) {
            State next_free = max(free, State{hold.val + p[i] - lambda, hold.cnt + 1});
            State next_hold = max(hold, State{free.val - p[i], free.cnt});
            free = next_free;
            hold = next_hold;
        }
        return free;
    }

    ll solve(int n, int k, const vector<ll>& p) {
        if (n <= 1 || k == 0) return 0;
        ll low = 0, high = 1e9 + 7;
        ll best_lambda = 0;

        while (low <= high) {
            ll mid = low + (high - low) / 2;
            State res = run_dp(n, p, mid);
            if (res.cnt >= k) {
                best_lambda = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        State res = run_dp(n, p, best_lambda);
        return res.val + (ll)k * best_lambda;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "=== MASTER TEMPLATE ALIENS TRICK / LAGRANGIAN RELAXATION ===\n";
    cout << "Modul 1: AliensCHT::solve (Minimasi Kuadratik Partisi K Segmen)\n";
    cout << "Modul 2: AliensStock::solve (Maksimasi Transaksi K Saham)\n";

    return 0;
}
