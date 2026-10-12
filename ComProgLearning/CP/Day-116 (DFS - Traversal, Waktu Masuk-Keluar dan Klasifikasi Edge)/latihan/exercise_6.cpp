/*
 * Day 59 — DFS (Depth-First Search)
 * File  : exercise_6.cpp
 * Topik : DFS Iteratif — Menghindari Stack Overflow
 * -----------------------------------------------
 * Diberikan graph TAK BERARAH dengan N node yang bisa berbentuk RANTAI PANJANG
 * (kedalaman sampai 10^6). DFS rekursif akan menyebabkan STACK OVERFLOW
 * pada kasus terburuk.
 *
 * Implementasikan DFS ITERATIF menggunakan stack EKSPLISIT, lalu cetak
 * jumlah node yang terjangkau dari node 1.
 *
 * Idea:
 *   stack<int> st;
 *   st.push(start);
 *   while (!st.empty()) {
 *       int u = st.top(); st.pop();
 *       if (visited[u]) continue;        ← WAJIB: node bisa masuk stack >1×
 *       visited[u] = true;
 *       count++;
 *       for (int v : adj[u])
 *           if (!visited[v]) st.push(v);
 *   }
 *
 * ⚠️ BEDA PENTING dengan versi rekursif:
 *    Sebuah node bisa di-push ke stack beberapa kali sebelum sempat ditandai.
 *    Karena itu pengecekan visited dilakukan SAAT POP, bukan hanya saat push.
 *    Kalau lupa, node yang sama diproses berulang → hasil salah.
 *
 * ⚠️ Urutan kunjungan versi iteratif KEBALIKAN dari rekursif kalau kamu
 *    push tetangga dari depan. Untuk menyamakan, push dari BELAKANG ke depan.
 *    (Untuk exercise ini urutan tidak dinilai — hanya jumlahnya.)
 *
 * Input format  : Baris 1: N dan M
 *                 M baris berikutnya: u dan v
 * Output format : satu bilangan — jumlah node yang terjangkau dari node 1
 *                 (termasuk node 1 sendiri)
 * Constraints   : 1 ≤ N ≤ 1.000.000
 *                 0 ≤ M ≤ 1.000.000
 *                 Graph bisa berbentuk rantai sepanjang N.
 *
 * Sample Input 1:        Sample Output 1:
 * 5 4                    5
 * 1 2
 * 2 3
 * 3 4
 * 4 5
 *
 * Sample Input 2:        Sample Output 2:
 * 6 3                    3
 * 1 2
 * 2 3
 * 4 5
 *
 * Sample Input 3:        Sample Output 3:
 * 1 0                    1
 *
 * NOTE Sample 2: dari node 1 hanya bisa mencapai {1,2,3} = 3 node.
 *                Node 4, 5, 6 berada di komponen lain.
 *
 * HINT: Uji sendiri dengan membuat rantai 10^6 node — versi rekursif akan
 *       crash (segmentation fault), versi iteratif tetap jalan.
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
vector<int> adj[MAXN];
bool visited[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca input, bangun adjacency list dua arah

    // TODO: DFS ITERATIF dengan stack eksplisit dari node 1

    // TODO: Cetak jumlah node yang terjangkau

    return 0;
}
