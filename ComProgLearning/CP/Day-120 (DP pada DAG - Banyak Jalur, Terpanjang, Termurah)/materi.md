# Day 120 - DP pada DAG

## Deskripsi
Pada DAG (graf berarah tanpa siklus), urutan topologis memberi urutan evaluasi yang menjamin setiap subproblem selesai sebelum dipakai. Akibatnya, banyak pertanyaan jalur dapat dijawab dengan satu sapuan linear O(V+E).

## Tiga Pertanyaan, Satu Kerangka
Kerangkanya selalu:
```
for u dalam urutan topologis:
    for setiap edge u -> v berbobot w:
        dp[v] = gabung(dp[v], f(dp[u], w))
```
Yang berubah hanya nilai awal dan operator penggabung:
- Banyak jalur: awal dp[s]=1, gabung dengan penjumlahan (modulo).
- Jalur terpanjang: awal dp[s]=0 dan -INF di tempat lain, gabung dengan max.
- Jalur termurah: awal dp[s]=0 dan +INF di tempat lain, gabung dengan min.

## Catatan Penting
Jalur terpanjang pada graf umum adalah masalah NP-hard, tetapi pada DAG selesai dalam waktu linear. Sebaliknya, jalur termurah di DAG boleh memiliki bobot negatif — sesuatu yang tidak boleh dilakukan Dijkstra.

## Kompleksitas
O(V + E) waktu, O(V) memori.
