/*
============================================================
📋 TUGAS 14: Rekonstruksi Penumpukan Balok Tertinggi (Box Stacking)
============================================================
Source: Classic DP / Box Stacking LIS
Difficulty: Hard
Topics: 3D Box Rotations, DAG LIS, Reconstruction

PROBLEM:
Terdapat N balok dengan dimensi (panjang L_i, lebar W_i, tinggi H_i).
Kamu dapat memutar setiap balok sehingga sembarang sisi dapat dijadikan alas (ada 3 rotasi unik per balok:
asumsikan alas berupa (p, l) dengan p > l, dan t adalah tingginya).
Sebuah balok B hanya boleh ditumpuk di atas balok A jika:
panjang alas B < panjang alas A DAN lebar alas B < lebar alas A (lebih kecil secara ketat).
Tentukan tinggi maksimum tumpukan balok yang dapat dicapai di baris pertama,
serta banyak balok dalam tumpukan tersebut (K) di baris kedua.

INPUT FORMAT:
Baris pertama berisi satu bilangan bulat N.
N baris berikutnya berisi tiga bilangan bulat L_i, W_i, H_i.

OUTPUT FORMAT:
Baris pertama: tinggi tumpukan maksimum.
Baris kedua: banyak balok terpilih K.

CONSTRAINTS:
1 <= N <= 100
1 <= L_i, W_i, H_i <= 10.000

SAMPLE INPUT 1:
4
4 6 7
1 2 3
4 5 6
10 12 32

SAMPLE OUTPUT 1:
60
(Penjelasan: Tinggi maksimum 60)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Box {
    ll l, w, h;
    bool operator<(const Box& o) const {
        if (l != o.l) return l > o.l;
        return w > o.w;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Box> boxes;
    for (int i = 0; i < n; i++) {
        ll l, w, h;
        cin >> l >> w >> h;
        // 3 rotasi
        vector<ll> d = {l, w, h};
        sort(d.begin(), d.end());
        boxes.push_back({d[2], d[1], d[0]});
        boxes.push_back({d[2], d[0], d[1]});
        boxes.push_back({d[1], d[0], d[2]});
    }

    sort(boxes.begin(), boxes.end());

    // TODO: Selesaikan LIS Box Stacking dengan rekonstruksi tinggi dan banyak balok

    return 0;
}
