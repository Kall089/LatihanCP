/*
============================================================
📋 TUGAS 04: Apakah Graph Bipartit?
============================================================
Source: Original
Difficulty: Easy-Medium
Topics: BFS, 2-coloring, bipartite check

PROBLEM:
Graph tidak berarah disebut BIPARTIT jika node-nodenya bisa
dibagi menjadi 2 kelompok sehingga setiap edge menghubungkan
node dari kelompok berbeda (tidak ada edge dalam kelompok).

Diberikan graph tidak berarah tidak berbobot.
Tentukan apakah graph tersebut bipartit atau tidak.

Gunakan BFS: warnai node dengan 2 warna (0 dan 1).
Saat mengunjungi tetangga v dari u:
  - Jika v belum diwarnai: beri warna berbeda dari u
  - Jika v sudah diwarnai dengan warna SAMA dengan u: BUKAN bipartit

INPUT FORMAT:
- Baris 1: dua integer n, m
- m baris berikutnya: dua integer u v

OUTPUT FORMAT:
- "BIPARTIT" atau "BUKAN BIPARTIT"

CONSTRAINTS:
- 1 ≤ n ≤ 10^5
- 0 ≤ m ≤ 2×10^5
- Graph bisa tidak connected

SAMPLE INPUT 1:
4 4
1 2
2 3
3 4
4 1

SAMPLE OUTPUT 1:
BIPARTIT

SAMPLE INPUT 2:
3 3
1 2
2 3
3 1

SAMPLE OUTPUT 2:
BUKAN BIPARTIT

NOTE: Untuk graph tidak connected, jalankan BFS dari setiap
      komponen yang belum dikunjungi.
      Cycle ganjil → bukan bipartit.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, m;
  cin >> n >> m;

  vector<vector<int>> adj(n + 1);

  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vector<int> color(n + 1, -1);
  bool bipatrit = true;

  for (int s = 1; s <= n; s++)
  {
    if (color[s] != -1)
    {
      continue;
    }

    color[s] = 0;
    queue<int> q;
    q.push(s);

    while (!q.empty())
    {
      int u = q.front();
      q.pop();

      for (int v : adj[u])
      {
        if (color[v] == -1)
        {
          color[v] = 1 - color[u];
          q.push(v);
        }
        else if (color[v] == color[u])
        {
          bipatrit = false;
        }
      }
    }
  }

  if (!bipatrit)
  {
    cout << "BUKAN BIPATRIT" << endl;
  }
  else
  {
    cout << "BIPATRIT" << endl;
  }
}