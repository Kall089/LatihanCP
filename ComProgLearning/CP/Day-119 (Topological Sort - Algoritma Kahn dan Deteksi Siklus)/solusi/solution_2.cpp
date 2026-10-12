/*
============================================================
✅ Solution 2: Deteksi Siklus pada Graf Berarah
============================================================
Approach: Kahn, lalu bandingkan ukuran hasil dengan n
Complexity: Time O(N + M) | Space O(N + M)
Key Insight: Sebuah simpul di dalam siklus punya pendahulu yang juga di dalam
             siklus itu. Untuk bisa keluar, ia harus menunggu pendahulunya
             keluar lebih dulu -- dan pendahulunya menunggu pendahulunya.
             Melingkar, tak ada yang bisa mulai. Jadi indeg mereka TIDAK PERNAH
             mencapai 0 dan mereka hilang dari hasil.

📖 BUKTI DUA ARAH:
   (a) Ada siklus -> ord.size() < n.  Argumen di atas.
   (b) Tidak ada siklus -> ord.size() == n. Setiap DAG tak kosong pasti punya
       simpul ber-indegree 0 (kalau tidak, berjalan mundur terus-menerus pasti
       mengunjungi simpul sama dua kali = siklus). Jadi prosesnya tidak pernah
       berhenti selama masih ada sisa.

⚠️ SELF-LOOP. Edge u -> u membuat indeg[u] naik 1 karena dirinya sendiri.
   Ia tidak akan pernah 0. Sampel 3 menguji ini: jawabannya YA. Perilaku ini
   BENAR -- self-loop memang siklus panjang 1.

⚠️ JANGAN PAKAI SATU BIT "visited" ALA GRAF TAK BERARAH.
   Pada graf berarah, mengunjungi simpul yang sudah selesai bukan siklus; itu
   cuma cross/forward edge. Kalau mau DFS, wajib 3 warna. Kahn menghindari
   seluruh jebakan ini.

⚠️ int untuk indeg cukup (M <= 2*10^5), tapi hati-hati kalau edge ganda banyak.

VERIFIKASI SAMPEL 1 (1->2, 2->3, 3->4, 4->2):
   indeg = [_,0,2,1,1]
   antre [1]; pop 1 -> indeg[2]=1 (belum 0). Antrean kosong.
   ord.size() = 1 != 4  ->  YA  ✓

🔄 ALTERNATIVE APPROACHES:
- DFS 3 warna: sama cepat, berguna kalau kamu juga ingin MENCETAK siklusnya
  (simpan parent, lalu telusuri balik dari back edge).
- Simpul yang TIDAK muncul di ord adalah simpul yang ada di siklus atau bisa
  dicapai dari siklus -- berguna untuk soal "sebutkan yang bermasalah".
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        indeg[v]++;
    }

    queue<int> q;
    for (int u = 1; u <= n; u++) if (indeg[u] == 0) q.push(u);

    int keluar = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        keluar++;
        for (int v : g[u]) if (--indeg[v] == 0) q.push(v);
    }

    cout << (keluar != n ? "YA" : "TIDAK") << '\n';
    return 0;
}
