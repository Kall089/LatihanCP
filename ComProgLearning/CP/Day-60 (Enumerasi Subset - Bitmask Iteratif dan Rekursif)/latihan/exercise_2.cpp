/*
============================================================
  Exercise 2: Cek Subset, Superset, dan Interseksi
============================================================
Diberikan dua himpunan A dan B, masing-masing direpresentasikan
sebagai bitmask dari elemen {0..n-1}. Jawab beberapa query
tentang hubungan antara A dan B.

Tiap query adalah salah satu dari:
  IS_SUBSET     -> apakah A ⊆ B? (cetak "YES"/"NO")
  IS_SUPERSET   -> apakah A ⊇ B? (cetak "YES"/"NO")
  DISJOINT      -> apakah A ∩ B = {}? (cetak "YES"/"NO")
  UNION         -> cetak bitmask dari A ∪ B
  INTERSECT     -> cetak bitmask dari A ∩ B
  DIFF          -> cetak bitmask dari A - B

Himpunan diberikan sebagai daftar elemen:
- Baris pertama: n (jumlah elemen universe), q (jumlah query)
- Baris kedua: ka, lalu ka elemen A
- Baris ketiga: kb, lalu kb elemen B

📏 CONSTRAINTS:
  - 1 ≤ n ≤ 20
  - 0 ≤ elemen < n
  - 1 ≤ q ≤ 50

📎 SAMPLE INPUT:
  5 6
  3 0 2 4
  2 2 3
  IS_SUBSET
  IS_SUPERSET
  DISJOINT
  UNION
  INTERSECT
  DIFF

📎 SAMPLE OUTPUT:
  NO
  NO
  NO
  31
  4
  17

  (A = {0,2,4} = 10101 = 21, B = {2,3} = 01100 = 12)
  (Union = 11101 = 29... cek lagi: 21|12 = 10101|01100 = 11101 = 29)
  (Intersect = 10101&01100 = 00100 = 4)
  (Diff A-B = 10101 & ~01100 = 10101 & 10011 = 10001 = 17)

💡 HINT:
  - IS_SUBSET: (A & B) == A
  - IS_SUPERSET: (A & B) == B
  - DISJOINT: (A & B) == 0
  - UNION: A | B
  - INTERSECT: A & B
  - DIFF: A & ~B

🎯 Learning Goals:
  Memahami operasi himpunan menggunakan bitmask.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    // Baca himpunan A
    int ka;
    cin >> ka;
    int A = 0;
    for (int i = 0; i < ka; i++) {
        int x; cin >> x;
        // TODO: encode elemen x ke dalam bitmask A
    }

    // Baca himpunan B
    int kb;
    cin >> kb;
    int B = 0;
    for (int i = 0; i < kb; i++) {
        int x; cin >> x;
        // TODO: encode elemen x ke dalam bitmask B
    }

    while (q--) {
        string op;
        cin >> op;

        if (op == "IS_SUBSET") {
            // TODO: cetak YES jika A ⊆ B, NO jika tidak
        } else if (op == "IS_SUPERSET") {
            // TODO: cetak YES jika A ⊇ B, NO jika tidak
        } else if (op == "DISJOINT") {
            // TODO: cetak YES jika A ∩ B = {}, NO jika tidak
        } else if (op == "UNION") {
            // TODO: cetak bitmask A ∪ B
        } else if (op == "INTERSECT") {
            // TODO: cetak bitmask A ∩ B
        } else if (op == "DIFF") {
            // TODO: cetak bitmask A - B
        }
    }

    return 0;
}
