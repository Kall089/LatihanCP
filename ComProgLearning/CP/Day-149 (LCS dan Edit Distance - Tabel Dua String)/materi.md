# Day 149 - LCS dan Edit Distance

## Deskripsi
Ketika sebuah masalah melibatkan DUA string, state DP-nya biasanya menjadi dua dimensi: `dp[i][j]` menjawab pertanyaan untuk prefiks pertama sepanjang i dan prefiks kedua sepanjang j.

## LCS (Longest Common Subsequence)
Cari subsekuens terpanjang yang muncul di kedua string. Rekurensnya bertanya satu hal di setiap sel: apakah huruf terakhir kedua prefiks cocok?
- Cocok: `dp[i][j] = dp[i-1][j-1] + 1`
- Tidak: `dp[i][j] = max(dp[i-1][j], dp[i][j-1])`

## Edit Distance (Levenshtein)
Jumlah minimum operasi (sisip, hapus, ganti) untuk mengubah string A menjadi B.
- Cocok: `dp[i][j] = dp[i-1][j-1]` (gratis)
- Tidak: `dp[i][j] = 1 + min(diagonal, atas, kiri)` yang masing-masing berarti ganti, hapus, dan sisip.

Perbedaan penting: base case LCS adalah nol, sedangkan base case edit distance adalah `dp[i][0] = i` dan `dp[0][j] = j`.

## Turunan
- Jumlah penghapusan minimum agar dua string sama: `n + m - 2*LCS`.
- Supersequence bersama terpendek: `n + m - LCS`.
- Longest common SUBSTRING: sama seperti LCS, tetapi saat huruf berbeda nilainya di-RESET ke 0 dan jawabannya adalah maksimum seluruh tabel.

## Kompleksitas
O(n*m) waktu; memori bisa ditekan menjadi O(min(n,m)) dengan rolling array, tetapi rekonstruksi lalu tidak mungkin tanpa teknik Hirschberg.
