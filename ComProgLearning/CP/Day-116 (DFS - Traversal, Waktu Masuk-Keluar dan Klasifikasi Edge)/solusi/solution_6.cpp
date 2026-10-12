/*
 * Day 59 — DFS (Depth-First Search)
 * File  : solution_6.cpp
 * Topik : DFS Iteratif dengan Stack Eksplisit — SOLUSI LENGKAP
 * -----------------------------------------------
 * Pendekatan: DFS iteratif menggantikan rekursi
 *
 * MASALAH DENGAN REKURSI:
 *   Graph berbentuk rantai 10^6 node → kedalaman rekursi 10^6.
 *   Tiap frame rekursi memakai puluhan byte (return address, parameter,
 *   iterator lokal) → total puluhan MB, sementara stack default hanya
 *   ~1-8 MB → SEGMENTATION FAULT.
 *
 *   DFS iteratif memindahkan "stack" dari call stack ke HEAP (std::stack),
 *   yang batasnya adalah RAM, bukan stack limit.
 *
 * Idea:
 *   st.push(start)
 *   while !st.empty():
 *       u = st.top(); st.pop()
 *       if visited[u]: continue          ← KUNCI
 *       visited[u] = true
 *       count++
 *       for v in adj[u]: if !visited[v]: st.push(v)
 *
 * ⚠️ KENAPA `if (visited[u]) continue` WAJIB?
 *   Beda mendasar dengan rekursi: sebuah node bisa di-push ke stack oleh
 *   BEBERAPA tetangga sebelum sempat diproses. Contoh segitiga 1-2, 1-3, 2-3:
 *     pop 1 → push 2, push 3
 *     pop 3 → push 2 (lagi!)  → stack = [2, 2]
 *     pop 2 → proses
 *     pop 2 → SUDAH diproses → harus di-skip
 *   Tanpa cek ini, node terhitung dua kali → jawaban salah.
 *
 * Trace sample 2 (N=6, edge 1-2, 2-3, 4-5), start = 1:
 *   push 1 → pop 1, visited{1}, count=1, push 2
 *   pop 2, visited{1,2}, count=2, push 3 (1 sudah visited, tidak di-push)
 *   pop 3, visited{1,2,3}, count=3, tidak ada tetangga baru
 *   stack kosong → count = 3 ✓
 *   Node 4,5,6 tidak terjangkau dari 1 — benar.
 *
 * Complexity: O(V + E) time
 * Space: O(V + E) adjacency list + O(V) stack heap
 *        (stack bisa memuat sampai O(E) entri sementara, tetap aman di heap)
 *
 * Edge cases:
 *   - N=1, M=0 → count = 1 (node itu sendiri)
 *   - Rantai 10^6 node → versi rekursif CRASH, versi ini jalan normal
 *   - Node 1 terisolasi → count = 1
 *   - Graph dengan banyak cycle → cek visited saat pop mencegah pengulangan
 *
 * Alternative approaches:
 *   - BFS iteratif (queue): sama-sama O(V+E) dan bebas stack overflow.
 *     Kalau tidak butuh sifat "mendalam" dari DFS, BFS lebih sederhana.
 *   - Menaikkan stack size via pragma linker: tidak portable, hindari.
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
vector<int> adj[MAXN];
bool visited[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // DFS ITERATIF dari node 1
    int count = 0;
    stack<int> st;
    st.push(1);

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        if (visited[u]) continue;       // WAJIB: node bisa masuk stack >1x
        visited[u] = true;
        count++;

        for (int v : adj[u]) {
            if (!visited[v]) st.push(v);
        }
    }

    cout << count << "\n";
    return 0;
}
