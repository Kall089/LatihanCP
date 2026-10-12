# Day 119 - Topological Sort (Algoritma Kahn)

## Deskripsi
Topological sort menghasilkan urutan linear dari simpul-simpul sebuah graf berarah sehingga untuk setiap edge `u -> v`, simpul `u` selalu muncul sebelum `v`. Urutan ini hanya ada jika graf tidak memiliki siklus (DAG).

## Algoritma Kahn
Berbasis BFS dan derajat masuk (in-degree). Simpul dengan in-degree 0 tidak punya prasyarat, jadi boleh diambil kapan saja. Setelah diambil, ia "membebaskan" tetangganya dengan mengurangi in-degree mereka.

## Deteksi Siklus
Jika jumlah simpul yang berhasil dikeluarkan lebih sedikit dari `n`, artinya ada simpul yang in-degree-nya tidak pernah mencapai nol — itu hanya mungkin terjadi kalau simpul tersebut terkurung dalam siklus. Inilah cara paling ringkas mendeteksi siklus pada graf berarah.

## Kompleksitas
O(V + E) waktu, O(V) memori tambahan.
