# ✅ Kunci Drill 1 — Pengenalan Pola

Skor: **10+/12 = lanjut ke Day 36.** Di bawah itu, baca ulang Bagian B lalu ulangi besok.

| # | Teknik | Sinyal penentu |
|---|---|---|
| 1 | **Kadane** | berurutan · max sum · ada negatif · panjang bebas |
| 2 | **Two pointers / sliding window variabel** | semua **positif** → sum monoton saat window melebar |
| 3 | **Prefix sum + hash map** | kata "**ada berapa banyak**" → menghitung, bukan optimasi |
| 4 | **Prefix + monotonic deque** (Day 37) | ada **batas panjang ≤ 30** |
| 5 | **Kadane pada array selisih** | `d[i] = p[i]−p[i−1]`; untung = jumlah selisih berurutan |
| 6 | **Bukan Kadane** — jumlahkan semua elemen positif | "boleh loncat" = subsequence, tidak berurutan |
| 7 | **Kadane + 1 state** | "boleh ... **paling banyak satu**" → tambah dimensi kecil ke dp |
| 8 | **Kadane melingkar** | `max(kadaneMax, total − kadaneMin)` + penjaga semua-negatif |
| 9 | **Sliding window ukuran tetap** (Day 33) | panjang **tepat** `k` → rata-rata dan jumlah setara |
| 10 | **Binary search on answer + prefix panjang ≥ k** | rata-rata + batas panjang; tebak `x`, kurangi semua elemen dengan `x`, cari subarray panjang ≥ k dengan sum ≥ 0 |
| 11 | **Kunci pasangan baris + Kadane 1D**, O(R²C) | persegi panjang di grid dengan negatif |
| 12 | **Kadane prefix + suffix, kunci titik potong** | dua segmen terpisah (= Drill 3 soal E) |

## Bonus

**13.** Karena `best = 0` diam-diam menyatakan "aku sudah punya kandidat bernilai 0",
dan satu-satunya subarray bernilai 0 yang selalu tersedia adalah **subarray kosong**.
Jadi `best = 0` menjawab pertanyaan "boleh kosong". Kalau soal melarang kosong dan
semua elemen negatif, jawaban benarnya elemen terbesar (yang negatif), tapi kode itu
akan mencetak 0.

**14.** Bukti optimal substructure Kadane berbunyi: *subarray terbaik yang berakhir
di `i` = (subarray terbaik yang berakhir di `i−1`) + `a[i]`*. Langkah pertukarannya
mengasumsikan **subarray terbaik yang berakhir di `i−1` selalu boleh diperpanjang
dengan `a[i]`**. Begitu ada batas panjang, asumsi itu runtuh: subarray terbaik di
`i−1` mungkin sudah mentok 30 elemen, sehingga memperpanjangnya **ilegal**, dan
kandidat yang lebih pendek-tapi-lebih-kecil justru yang harus dipakai.

Diagnosis umumnya: **state-nya kurang.** `dp[i]` tidak lagi cukup — butuh
`dp[i][panjang]`, yang terlalu besar, sehingga kita pindah ke formulasi prefix sum
di mana batas panjang menjadi sekadar batas jendela pada prefix minimum → deque.
