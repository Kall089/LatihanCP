# Day 127 - Dijkstra dengan Priority Queue

## Deskripsi
Dijkstra mencari jarak terpendek dari satu sumber ke semua simpul pada graf berbobot NON-NEGATIF. Dengan priority queue (min-heap), kompleksitasnya O(E log V).

## Ide
Simpan jarak sementara ke setiap simpul. Berulang kali ambil simpul dengan jarak sementara TERKECIL yang belum final; jaraknya dijamin sudah final. Lalu relaksasi semua tetangganya.

## Kenapa Gagal pada Bobot Negatif
Jaminan "yang keluar dari heap sudah final" bersandar pada satu fakta: menambah edge tidak pernah memperpendek jalur. Dengan bobot negatif, sebuah jalur yang awalnya tampak panjang bisa berubah menjadi yang terpendek setelah melewati edge negatif — padahal simpul tujuannya sudah terlanjur dikunci. Contoh minimal ada di teori bagian 5. Untuk bobot negatif gunakan Bellman-Ford (Day 129), atau DP topologis kalau grafnya DAG (Day 120).

## Kompleksitas
O(E log V) waktu dengan heap biner, O(V + E) memori.
