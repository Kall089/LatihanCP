# Day 143 - DP Linear 1D

## Deskripsi
DP linear satu dimensi adalah bentuk DP paling sederhana: state-nya hanya satu indeks, dan `dp[i]` dihitung dari sejumlah kecil nilai sebelumnya. Empat soal klasik yang mewakilinya adalah climbing stairs, house robber, frog jump, dan maximum subarray (Kadane).

## Empat Rekurens
- Tangga: `dp[i] = dp[i-1] + dp[i-2]` — menghitung banyak cara.
- House robber: `dp[i] = max(dp[i-1], dp[i-2] + a[i])` — dilarang mengambil dua yang bersebelahan.
- Frog jump: `dp[i] = min(dp[i-j] + |h[i]-h[i-j]|)` untuk j = 1..k.
- Kadane: `cur = max(a[i], cur + a[i])`, `best = max(best, cur)`.

## Kunci Pemahaman
Perbedaan terpenting adalah antara definisi "dp[i] = jawaban terbaik SAMPAI indeks i" dan "dp[i] = jawaban terbaik yang BERAKHIR TEPAT di i". Kadane memakai yang kedua, sehingga jawabannya adalah maksimum atas seluruh dp — bukan dp terakhir.

## Kompleksitas
O(n) waktu dan O(1) memori setelah dioptimasi dengan rolling variable. Frog jump dengan lompatan sampai k adalah O(nk), yang bisa diturunkan menjadi O(n) dengan monotonic deque.
