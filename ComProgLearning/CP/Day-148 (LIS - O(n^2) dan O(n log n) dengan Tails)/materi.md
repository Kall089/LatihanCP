# Day 148 - Longest Increasing Subsequence (LIS)

## Deskripsi
LIS mencari subsekuens terpanjang dari sebuah array yang nilainya naik. Subsekuens tidak harus berdekatan, tetapi urutannya harus dipertahankan.

## Versi O(n^2)
`dp[i]` = panjang LIS yang berakhir TEPAT di indeks i. Rekurensnya `dp[i] = 1 + max(dp[j])` untuk semua j < i dengan `a[j] < a[i]`. Jawabannya adalah maksimum atas seluruh dp, bukan dp terakhir.

## Versi O(n log n) dengan Tails
Simpan array `tails`, di mana `tails[k]` adalah nilai ekor TERKECIL di antara semua subsekuens naik yang panjangnya k+1. Array ini selalu terurut menaik, sehingga posisi penyisipan setiap elemen baru dapat dicari dengan binary search. Panjang LIS sama dengan ukuran `tails`.

## Peringatan Penting
Isi `tails` bukan LIS-nya. Hanya ukurannya yang benar. Untuk mendapatkan barisannya, catat posisi setiap elemen di dalam `tails` dan telusuri balik lewat array parent.

## Kompleksitas
O(n^2) untuk versi dasar, O(n log n) untuk versi tails.
