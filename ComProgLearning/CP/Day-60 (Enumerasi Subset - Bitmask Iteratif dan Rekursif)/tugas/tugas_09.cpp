/*
============================================================
📋 TUGAS 09: Partisi Dua Subset dengan Sum Sama
============================================================
Source: Original
Difficulty: Medium
Topics: bitmask enumeration, subset sum, partition

PROBLEM:
Diberikan array a[] dengan n elemen bilangan bulat positif.
Tentukan apakah array bisa dibagi menjadi DUA subset tidak kosong
yang total jumlahnya sama.
Jika bisa, cetak "YES" dan tampilkan kedua subset (subset pertama
adalah subset dengan indeks-indeks yang ditemukan pertama kali
saat iterasi mask dari 1 ke atas, subset kedua adalah komplementnya).
Jika tidak bisa, cetak "NO".

INPUT FORMAT:
- Baris 1: integer n
- Baris 2: n buah integer a[0..n-1]

OUTPUT FORMAT:
- Jika memungkinkan: "YES", lalu "Subset 1: { e1 e2 ... }", lalu "Subset 2: { e1 e2 ... }"
- Jika tidak: "NO"

CONSTRAINTS:
- 2 ≤ n ≤ 20
- 1 ≤ a[i] ≤ 10^6

SAMPLE INPUT 1:
4
1 5 3 3

SAMPLE OUTPUT 1:
YES
Subset 1: { 1 5 }
Subset 2: { 3 3 }

SAMPLE INPUT 2:
3
1 2 4

SAMPLE OUTPUT 2:
NO

NOTE: Jika total sum ganjil, jawabannya pasti NO.
      Cari mask (bukan 0 dan bukan full_mask) dengan sum = total/2.
      Komplementnya adalah ~mask & full_mask.
      Untuk n=4, a=[1,5,3,3]: total=12, target=6. mask=0b0011={1,5} sum=6 ✓.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<long long> a(n);
    long long total = 0;
    for (long long& x : a) { cin >> x; total += x; }

    if (total % 2 != 0) {
        cout << "NO\n";
        return 0;
    }

    long long half = total / 2;
    int full = (1 << n) - 1;

    for (int mask = 1; mask < full; mask++) {
        long long sum = 0;
        for (int i = 0; i < n; i++)
            if ((mask >> i) & 1) sum += a[i];
        if (sum == half) {
            cout << "YES\n";
            cout << "Subset 1: { ";
            for (int i = 0; i < n; i++)
                if ((mask >> i) & 1) cout << a[i] << ' ';
            cout << "}\n";
            cout << "Subset 2: { ";
            int comp = (~mask) & full;
            for (int i = 0; i < n; i++)
                if ((comp >> i) & 1) cout << a[i] << ' ';
            cout << "}\n";
            return 0;
        }
    }
    cout << "NO\n";
    return 0;
}
