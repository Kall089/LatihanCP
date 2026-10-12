/*
============================================================
🏋️ Exercise 5: Kapasitas Bus Wisata
============================================================
Day: 29 | Difficulty: Medium-Hard
Topic: Difference Array + pengecekan batas (capacity check)
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Sebuah bus wisata berkapasitas C orang berjalan satu arah melewati
halte bernomor 1, 2, 3, dan seterusnya, tanpa pernah kembali.
Ada N rombongan yang ingin ikut. Rombongan ke-i berjumlah p orang,
naik di halte s, dan turun di halte t. Artinya rombongan itu berada
di dalam bus pada rentang halte [s, t) — mereka sudah turun tepat di halte t,
sehingga kursinya bisa langsung dipakai rombongan lain yang naik di halte t.

Tentukan apakah bus sanggup mengangkut SEMUA rombongan tanpa pernah
melebihi kapasitas C pada titik mana pun.

📥 INPUT FORMAT:
- Baris pertama: dua integer N dan C
- N baris berikutnya: tiga integer p, s, t

📤 OUTPUT FORMAT:
- Satu baris: "BISA" jika semua rombongan bisa diangkut,
  atau "TIDAK" jika kapasitas pernah terlampaui.

📏 CONSTRAINTS:
- 1 ≤ N ≤ 2 × 10^5
- 1 ≤ C ≤ 10^9
- 1 ≤ p ≤ 10^6
- 1 ≤ s < t ≤ 1000

📎 SAMPLE INPUT 1:
2 4
2 1 5
3 3 7

📎 SAMPLE OUTPUT 1:
TIDAK

📎 SAMPLE INPUT 2:
2 5
2 1 5
3 3 7

📎 SAMPLE OUTPUT 2:
BISA

📎 SAMPLE INPUT 3:
2 3
2 1 5
3 5 8

📎 SAMPLE OUTPUT 3:
BISA

💡 HINT:
- Rombongan hadir pada [s, t), jadi tandai diff[s] += p dan diff[t] -= p.
- Perhatikan Sample 3: rombongan kedua naik tepat di halte 5, saat
  rombongan pertama sudah turun. Keduanya tidak pernah bersamaan.
- Setelah prefix sum, cek apakah ADA titik yang nilainya melebihi C.

🎯 Learning Goals:
- [ ] Menerapkan difference array untuk pengecekan batas, bukan sekadar hasil
- [ ] Memahami arti interval setengah terbuka [s, t)
- [ ] Berhenti lebih awal (early exit) saat syarat sudah dilanggar
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca N dan C

    // TODO: Bangun difference array untuk interval [s, t)

    // TODO: Prefix sum sambil mengecek apakah pernah melebihi C

    return 0;
}
