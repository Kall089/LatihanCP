/*
============================================================
🏋️ Exercise 3: Barang Mana yang Dipilih
============================================================
Day: 145 | Difficulty: Medium
Topic: Rekonstruksi solusi
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan N barang dengan berat dan nilai, serta kapasitas W.
Selain mencetak nilai maksimum, kamu juga harus mencetak INDEKS barang mana
saja yang dipilih (1-based, terurut menaik).
Jika ada beberapa pilihan yang menghasilkan nilai maksimum yang sama, cetak
yang mana pun — asalkan total beratnya tidak melebihi W dan total nilainya
benar-benar maksimum.

📥 INPUT FORMAT:
- Baris pertama: N dan W
- N baris berikutnya: w[i] dan v[i]

📤 OUTPUT FORMAT:
- Baris pertama: nilai maksimum
- Baris kedua: indeks barang yang dipilih (kosong kalau tidak ada)

📏 CONSTRAINTS:
- 1 <= N <= 500
- 1 <= W <= 2000
- 1 <= w[i] <= W
- 1 <= v[i] <= 10^9

📎 SAMPLE INPUT 1:
3 5
3 3
2 4
4 2

📎 SAMPLE OUTPUT 1:
7
1 2

📎 SAMPLE INPUT 2:
2 1
5 10
6 20

📎 SAMPLE OUTPUT 2:
0


💡 HINT: Versi satu dimensi yang hemat memori punya satu kelemahan: ia
         MENIMPA riwayatnya sendiri, sehingga kamu tidak bisa lagi
         menelusuri keputusan yang diambil.
         Perhatikan batas soal ini — N kali W hanya 10^6, jadi kamu mampu
         menyimpan sesuatu yang lebih lengkap.
         Untuk menelusuri kembali, mulai dari keadaan akhir (seluruh barang
         dipertimbangkan, kapasitas penuh) lalu bergerak MUNDUR. Pada setiap
         langkah, bandingkan nilai di baris sekarang dengan nilai di baris
         tepat di atasnya: kalau berbeda, apa artinya?
         Jangan lupa mengurangi kapasitas saat sebuah barang diputuskan
         terambil.

🎯 Learning Goals:
- [ ] Memahami kenapa versi 1D tidak bisa direkonstruksi
- [ ] Menelusuri tabel mundur untuk memulihkan keputusan
- [ ] Menghitung memori untuk memutuskan 1D atau 2D
============================================================
*/
