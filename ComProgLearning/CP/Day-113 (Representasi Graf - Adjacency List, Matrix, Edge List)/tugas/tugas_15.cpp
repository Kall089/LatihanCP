/*
============================================================
📋 TUGAS 15 (Final Boss): Graph dari String — Dependency Graph
============================================================
Source: Original
Difficulty: Hard
Topics: directed graph, adjacency list, topological sort, cycle detection

PROBLEM:
Diberikan n task dengan nama dan dependensinya.
Format: "task_name: dep1 dep2 ..." (jika tak punya dependensi: "task_name:")
Bangun directed graph (dependency → task, artinya dep harus selesai dulu).
Cetak:
1. Adjacency list (directed, tetangga sorted alphabetically)
2. Tasks yang tidak punya dependensi (indegree 0, bisa dikerjakan pertama)
3. Tasks yang tidak diperlukan siapapun (outdegree 0, bisa dikerjakan terakhir)
4. Apakah ada cycle (dependensi melingkar)?
   Gunakan in-degree: setelah simulasi topological sort, jika ada node yang
   tidak bisa di-resolve (in-degree > 0 tersisa) → ada cycle.

INPUT FORMAT:
- Baris 1: integer n
- n baris berikutnya: "task_name: dep1 dep2 ..." (atau "task_name:")

OUTPUT FORMAT:
- "Dependency graph:" lalu adjacency list
- "Tasks tanpa dependensi: [name1 name2 ...]" (sorted)
- "Tasks tidak diperlukan: [name1 name2 ...]" (sorted)
- "Cycle: ADA" atau "Cycle: TIDAK ADA"

CONSTRAINTS:
- 1 ≤ n ≤ 10^3
- Nama task mengandung huruf kecil dan angka, panjang ≤ 20

SAMPLE INPUT 1:
5
build: compile link
compile: preprocess
link: compile
preprocess:
test: build

SAMPLE OUTPUT 1:
Dependency graph:
preprocess → [compile]
compile → [build, link]
link → [build]
build → [test]

Tasks tanpa dependensi: preprocess
Tasks tidak diperlukan: test
Cycle: TIDAK ADA

SAMPLE INPUT 2:
3
a: b
b: c
c: a

SAMPLE OUTPUT 2:
Dependency graph:
b → [a]
c → [b]
a → [c]

Tasks tanpa dependensi: (tidak ada)
Tasks tidak diperlukan: (tidak ada)
Cycle: ADA

NOTE: Gunakan map<string,int> untuk assign ID ke tiap task name.
      In-degree = jumlah dependensi task tersebut.
      Out-degree dari dep d = berapa task yang bergantung pada d.
      Untuk cycle detection: Kahn's algorithm (topological sort via BFS).
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // TODO
    return 0;
}
