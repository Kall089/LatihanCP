/*
============================================================
✅ Solution 3: Nominal Donasi yang Mungkin (Bounded Reachability)
============================================================
Approach: Bounded Knapsack Dekomposisi Biner + Boolean Reachability
Complexity: Time O(S * sum(log(c_eff + 1))) | Space O(S)
Key Insight:
Kita mendefinisikan array boolean:
can[j] = true jika nominal j dapat dibentuk dari kupon-kupon yang telah diproses.

Base case:
can[0] = true (nominal 0 dibentuk dengan tidak mengambil kupon apa pun).

Ketika stok kupon dipecah menjadi paket biner, sebuah nominal j mungkin bisa
dihasilkan oleh beberapa kombinasi paket berbeda (misal stok 5 dipecah jadi {1, 2, 2},
nominal 2 bisa dari paket 2 pertama atau paket 2 kedua).
Namun, karena operasi yang digunakan adalah logika OR (`can[j] |= can[j - weight]`),
sifat idempoten dari OR memastikan bahwa representasi ganda tidak akan
mempengaruhi kebenaran status ketercapaian nilai.

Setelah seluruh paket diproses:
Hitung banyaknya nilai true pada can[1...S].
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, s;
    if (!(cin >> n >> s)) return 0;

    vector<bool> can(s + 1, false);
    can[0] = true;

    for (int i = 0; i < n; i++) {
        int weight;
        long long count;
        cin >> weight >> count;

        if (weight <= 0 || count <= 0 || s <= 0) continue;

        long long c_eff = min(count, (long long)(s / weight));

        long long p = 1;
        while (c_eff > 0) {
            long long q = min(p, c_eff);
            c_eff -= q;

            int pkg_weight = q * weight;

            for (int j = s; j >= pkg_weight; j--) {
                if (can[j - pkg_weight]) {
                    can[j] = true;
                }
            }

            p *= 2;
        }
    }

    int reachable_count = 0;
    for (int j = 1; j <= s; j++) {
        if (can[j]) reachable_count++;
    }

    cout << reachable_count << "\n";

    return 0;
}
