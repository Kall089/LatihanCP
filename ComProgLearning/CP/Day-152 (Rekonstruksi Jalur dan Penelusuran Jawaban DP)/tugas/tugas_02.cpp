/*
============================================================
📋 TUGAS 02: Potongan Palindrom Terawal
============================================================
Source: Classic DP / Palindrome Partition Tracking
Difficulty: Medium
Topics: Two-Stage DP, Suffix 1D DP, Cut Reconstruction

PROBLEM:
Partisikan string S menjadi JUMLAH BAGIAN PALINDROM MINIMUM.
Cetak banyak bagian palindrom tersebut pada baris pertama.
Pada baris kedua, cetak daftar posisi karakter akhir dari setiap bagian (1-indexed, berakhir di |S|).
Jika ada beberapa kemungkinan partisi dengan jumlah bagian minimum yang sama,
pilih daftar posisi akhir yang TERKECIL SECARA LEKSIKOGRAFIS (artinya kita memprioritaskan potongan
pertama sependek mungkin).

INPUT FORMAT:
Satu baris berisi string S tanpa spasi.

OUTPUT FORMAT:
Baris pertama: banyak bagian palindrom minimum.
Baris kedua: daftar indeks akhir setiap bagian dipisahkan spasi.

CONSTRAINTS:
1 <= |S| <= 500
S hanya berisi huruf kecil 'a'..'z'.

SAMPLE INPUT 1:
aab

SAMPLE OUTPUT 1:
2
2 3
(Penjelasan: "aa" [akhir di pos 2] dan "b" [akhir di pos 3]. Daftar [2, 3])

SAMPLE INPUT 2:
abab

SAMPLE OUTPUT 2:
2
1 4
(Penjelasan: "a" [pos 1] dan "bab" [pos 4] menghasilkan daftar [1, 4].
Alternatif "aba" [pos 3] dan "b" [pos 4] menghasilkan [3, 4].
Karena 1 < 3, maka [1, 4] menang secara leksikografis)
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    if (!(cin >> s)) return 0;

    int n = s.size();

    // TODO: Selesaikan Palindrome Partitioning Terawal
    // 1. is_pal[l][r]
    // 2. Suffix dp[i]: minimum bagian palindrom dari indeks i s.d. n-1
    // 3. Rekonstruksi maju: cari j terkecil yang optimal

    return 0;
}
