/*
============================================================
✅ Solution 5: Berapa Semester Minimum? (Rantai Terpanjang)
============================================================
Approach: Kahn + relaksasi level
Complexity: Time O(N + M) | Space O(N + M)
Key Insight: Semester paling awal untuk mata kuliah v ditentukan oleh
             prasyarat yang PALING LAMBAT selesai. Jadi
                 lvl[v] = max(lvl[u] + 1)  untuk semua u -> v
             Jawaban = max(lvl) + 1 (karena lvl dihitung 0-based).

📖 KENAPA RELAKSASI INI VALID TANPA PERLU DP TERPISAH:
   Saat u dikeluarkan dari antrean, SELURUH pendahulu u sudah dikeluarkan
   (itulah arti indeg[u] mencapai 0). Jadi lvl[u] sudah final saat kita
   memakainya untuk memperbarui tetangga. Kita tidak pernah membaca nilai
   setengah jadi. Ini persis alasan DP di DAG bekerja -- lihat Day 120.

⚠️ JAWABANNYA max(lvl)+1, BUKAN max(lvl).
   lvl = 0 berarti "semester pertama". Sampel 2 (rantai 5 simpul) memberi
   lvl maksimum 4, jawabannya 5.

⚠️ SIKLUS -> -1. Cek keluar != n seperti biasa. Sampel 3 mengujinya.

⚠️ JANGAN GREEDY "hitung panjang rantai terpanjang dengan DFS berulang".
   Itu O(N*M) pada graf padat. Kahn menyelesaikannya sekali jalan.

VERIFIKASI SAMPEL 1 (1->3, 2->4, 2->6, 3->5, 4->5):
   lvl awal semua 0. antre [1,2]
   pop 1: lvl[3]=max(0,0+1)=1
   pop 2: lvl[4]=1, lvl[6]=1
   pop 3: lvl[5]=max(0,1+1)=2
   pop 4: lvl[5]=max(2,1+1)=2
   pop 6: -
   pop 5: -
   max lvl = 2  ->  jawaban 3  ✓  (sem1:{1,2} sem2:{3,4,6} sem3:{5})

🔄 ALTERNATIVE APPROACHES:
- BFS berlapis: proses antrean per "gelombang" (ukuran antrean saat ini),
  hitung berapa gelombang. Setara, dan kadang lebih intuitif.
- Ini juga soal LONGEST PATH pada DAG -- yang pada graf umum NP-hard, tapi
  di DAG mudah. Day 120 memperluas ide ini.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    vector<int> indeg(n + 1, 0), lvl(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        indeg[v]++;
    }

    queue<int> q;
    for (int u = 1; u <= n; u++)
        if (indeg[u] == 0)
            q.push(u);

    int keluar = 0, best = 0;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        keluar++;
        best = max(best, lvl[u]);
        for (int v : g[u])
        {
            lvl[v] = max(lvl[v], lvl[u] + 1);
            if (--indeg[v] == 0)
                q.push(v);
        }
    }

    cout << (keluar != n ? -1 : best + 1) << '\n';
    return 0;
}
