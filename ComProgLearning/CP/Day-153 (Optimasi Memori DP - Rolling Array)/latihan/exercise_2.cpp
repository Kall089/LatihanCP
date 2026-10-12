/*
============================================================
🏋️ Exercise 2: Menyunting Nama Arsip (Edit Distance O(min(N, M)) Space)
============================================================
Day: 153 | Difficulty: Medium | Topic: 2-Row Rolling Array DP
Source: LeetCode 72 / Classic Edit Distance
Time Limit: 2.0 detik | Memory Limit: 64 MB

📋 PROBLEM STATEMENT:
Kamu diminta menghitung jarak penyuntingan (Edit Distance / Levenshtein Distance)
antara dua nama string A dan B.
Operasi yang diizinkan:
1. Menyisipkan (Insert) satu karakter baru (biaya 1).
2. Menghapus (Delete) satu karakter (biaya 1).
3. Mengganti (Replace) satu karakter dengan karakter lain (biaya 1).
Jika dua karakter sudah sama, karakter tersebut dapat dipertahankan tanpa biaya (biaya 0).

Khusus jika string kosong, pada input direpresentasikan dengan tanda strip tunggal `-`.
(Tanda `-` bukan bagian dari karakter alfabet).

Karena panjang string dapat mencapai 4.000 karakter, tabel 2D penuh berukuran
4001 x 4001 int akan memakan sekitar ~64 MB (mendekati atau melampaui batas).
Gunakan teknik Rolling Array 2 Baris untuk menekan memori menjadi O(min(|A|, |B|))!

📥 INPUT FORMAT:
- Satu baris berisi dua token A dan B dipisahkan oleh spasi.
- Masing-masing token berupa string huruf kecil 'a'..'z' atau tanda `-` (menandakan string kosong).

📤 OUTPUT FORMAT:
- Satu baris berisi satu bilangan bulat: jumlah operasi penyuntingan minimum.

📏 CONSTRAINTS:
- 0 <= |A|, |B| <= 4.000
- A dan B hanya terdiri dari huruf kecil 'a'..'z' atau `-`
- Memori DP harus O(min(|A|, |B|))

📎 SAMPLE INPUT 1:
kitten sitting

📎 SAMPLE OUTPUT 1:
3

[Penjelasan Sample 1:
kitten -> sitten (replace k -> s)
sitten -> sittin (replace e -> i)
sittin -> sitting (insert g)
Total operasi = 3.]

📎 SAMPLE INPUT 2:
- abc

📎 SAMPLE OUTPUT 2:
3

[Penjelasan Sample 2:
String A kosong. Menyisipkan 'a', 'b', 'c' membutuhkan 3 operasi.]

📎 SAMPLE INPUT 3:
- -

📎 SAMPLE OUTPUT 3:
0

[Penjelasan Sample 3:
Kedua string kosong, biaya 0.]

💡 HINT:
- Jika panjang B > panjang A, tukar (swap) A dan B agar dimensi kolom selalu bernilai minimum: M = min(|A|, |B|).
- Gunakan dua baris array: `vector<int> prev(M + 1)` dan `vector<int> cur(M + 1)`.
- Inisialisasi baris pertama: `prev[j] = j` untuk semua 0 <= j <= M.
- Untuk setiap baris i dari 1 sampai N:
  - `cur[0] = i`
  - Untuk setiap j dari 1 sampai M:
    - `cost = (A[i-1] == B[j-1] ? 0 : 1)`
    - `cur[j] = min({prev[j] + 1, cur[j-1] + 1, prev[j-1] + cost})`
  - Tukar pointer: `prev.swap(cur)`.
- Jawaban akhir berada di `prev[M]`.

🎯 Learning Goals:
- [ ] Mengimplementasikan pola 2-Row Rolling Array dengan `prev.swap(cur)`.
- [ ] Mengoptimalkan dimensi kolom ke ukuran yang lebih kecil: O(min(N, M)).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string a, b;
    if (!(cin >> a >> b)) return 0;

    // TODO: Selesaikan Edit Distance dengan 2-Row Rolling Array
    // 1. Tangani tanda '-' sebagai string kosong
    // 2. Pastikan |b| <= |a| (swap jika perlu)
    // 3. Gunakan prev dan cur untuk iterasi baris demi baris

    return 0;
}
