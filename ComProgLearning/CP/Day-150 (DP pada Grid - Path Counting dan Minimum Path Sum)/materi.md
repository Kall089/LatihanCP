# Day 150 - DP pada Grid

## Deskripsi
Grid dengan gerakan hanya ke kanan dan ke bawah adalah DAG: setiap langkah menambah nilai (i + j) tepat satu, sehingga mustahil kembali ke sel yang sama. Karena itu urutan topologisnya sudah tersedia secara gratis — cukup proses baris demi baris dari kiri ke kanan.

## Dua Pertanyaan Utama
- Menghitung jalur: `dp[i][j] = dp[i-1][j] + dp[i][j-1]`, dengan `dp[0][0] = 1`.
- Jumlah minimum: `dp[i][j] = a[i][j] + min(dp[i-1][j], dp[i][j-1])`.

## Halangan
Untuk penghitungan jalur, sel yang terhalang diisi 0 — nol adalah elemen netral penjumlahan, sehingga seluruh jalur yang melewatinya otomatis mati. Untuk minimum, sel terhalang diisi INF, dan sel bersentinel harus dilewati saat merelaksasi agar nilainya tidak menular.

## Batas Penerapan
Begitu gerakannya menjadi 4 arah, grafnya bersiklus dan DP tidak lagi terdefinisi. Gunakan BFS untuk biaya seragam atau Dijkstra untuk biaya non-negatif.

## Kompleksitas
O(R*C) waktu; memori bisa ditekan menjadi O(C) dengan rolling array, dengan konsekuensi rekonstruksi jalur menjadi mustahil.
