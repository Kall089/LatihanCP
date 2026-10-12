/*
============================================================
✅ Solution 3: Hujan Meteor
============================================================
Approach: Parallel binary search + BIT, dengan rentang melingkar
Complexity: Time O((M + N + K) log K log M) | Space O(M + N + K)
Key Insight: Bentuk klasik parallel binary search. Dua tambahan dari
             Exercise 2: rentang bisa MEMBUNGKUS, dan satu query memeriksa
             BEBERAPA sektor. Yang kedua terlihat mahal, tetapi tidak --
             karena total seluruh sektor milik semua negara adalah tepat M.

📖 KENAPA MENJAWAB SELURUH QUERY TETAP MURAH:
   Sekilas, menjawab satu negara berbiaya O(banyak sektornya x log M),
   sehingga menjawab N negara terlihat O(N x M x log M).
   Tetapi dalam SATU putaran, setiap negara dijawab PALING BANYAK SEKALI,
   dan jumlah seluruh sektor di seluruh negara adalah M.
   Jadi total biaya menjawab per putaran adalah O(M log M), bukan O(N M log M).
   Prinsip ini -- biaya dijamin oleh TOTAL ukuran data, bukan per query --
   sering menjadi kunci menganalisis soal offline dengan benar.

📖 RENTANG MELINGKAR:
   Kalau l <= r, itu rentang biasa [l, r].
   Kalau l > r, rentangnya membungkus: pecah menjadi [l, M] dan [1, r].
   Memecah lebih aman daripada mencoba menangani pembungkusan langsung di
   dalam BIT, karena BIT tidak punya konsep melingkar.

⚠️ HENTIKAN PENJUMLAHAN SETELAH TARGET TERCAPAI.
   Total meteor di seluruh sektor sebuah negara bisa mencapai
   M x K x a = 3*10^5 x 3*10^5 x 10^9 -- jauh melampaui long long.
   Karena kita hanya peduli "apakah sudah >= P", berhenti begitu tercapai
   mencegah overflow sekaligus mempercepat. Pola yang sama muncul di
   Day 49, 51, dan 53 -- kenali bentuknya.

⚠️ RESET BIT DI SETIAP PUTARAN. Sama seperti Exercise 2, ini bug nomor satu.

VERIFIKASI SAMPEL:
   Negara 1 memiliki sektor {1, 4}, negara 2 sektor {3}, negara 3 sektor {2, 5}.
   Hujan 1 (l=4, r=2, a=4) MEMBUNGKUS -> sektor 4, 5, 1, 2 masing-masing +4.
       negara 3 = sektor2 + sektor5 = 4 + 4 = 8 >= 7  -> jawab 1   ✓
   Hujan 2 (1..3, +1): s1=5, s2=5, s3=1
       negara 1 = 5 + 4 = 9 < 10 ; negara 2 = 1 < 5
   Hujan 3 (3..5, +2): s3=3, s4=6, s5=6
       negara 1 = 5 + 6 = 11 >= 10 -> jawab 3   ✓
       negara 2 = 3 < 5 -> NIE                  ✓

🔄 ALTERNATIVE APPROACHES:
- Segment tree offline divide and conquer: kompleksitas serupa, kadang
  lebih mudah digeneralisasi ke operasi yang tidak bisa di-BIT.
- Persistent structure: memungkinkan online, tetapi memorinya besar.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int M;
vector<ll> bitArr;

void bitAdd(int i, ll v) { for (; i <= M; i += i & -i) bitArr[i] += v; }
void rangeAdd(int l, int r, ll v) { bitAdd(l, v); bitAdd(r + 1, -v); }
ll bitGet(int i) { ll s = 0; for (; i > 0; i -= i & -i) s += bitArr[i]; return s; }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N >> M;

    vector<vector<int>> sektor(N + 1);
    for (int s = 1; s <= M; s++) {
        int o;
        cin >> o;
        sektor[o].push_back(s);
    }

    vector<ll> P(N + 1);
    for (int i = 1; i <= N; i++) cin >> P[i];

    int K;
    cin >> K;
    vector<int> L(K + 1), R(K + 1);
    vector<ll> A(K + 1);
    for (int t = 1; t <= K; t++) cin >> L[t] >> R[t] >> A[t];

    vector<int> lo(N + 1, 1), hi(N + 1, K + 1);   // K+1 = "NIE"
    vector<vector<int>> bucket(K + 2);

    while (true) {
        for (auto& b : bucket) b.clear();
        bool jalan = false;

        for (int i = 1; i <= N; i++)
            if (lo[i] < hi[i]) {
                bucket[lo[i] + (hi[i] - lo[i]) / 2].push_back(i);
                jalan = true;
            }
        if (!jalan) break;

        bitArr.assign(M + 2, 0);                  // RESET

        for (int t = 1; t <= K; t++) {
            if (L[t] <= R[t]) {
                rangeAdd(L[t], R[t], A[t]);
            } else {                              // MEMBUNGKUS: pecah dua
                rangeAdd(L[t], M, A[t]);
                rangeAdd(1, R[t], A[t]);
            }

            for (int i : bucket[t]) {
                ll total = 0;
                for (int s : sektor[i]) {
                    total += bitGet(s);
                    if (total >= P[i]) break;     // cegah overflow, percepat
                }
                if (total >= P[i]) hi[i] = t;
                else               lo[i] = t + 1;
            }
        }
    }

    string out;
    for (int i = 1; i <= N; i++) {
        if (lo[i] > K) out += "NIE";
        else           out += to_string(lo[i]);
        out += '\n';
    }
    cout << out;

    return 0;
}
