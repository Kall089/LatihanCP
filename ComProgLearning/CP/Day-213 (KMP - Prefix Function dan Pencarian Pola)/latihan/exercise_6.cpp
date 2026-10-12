/*
============================================================
🏋️ Exercise 6: Hitung Kemunculan Tiap Prefiks
============================================================
Day: 213 | Difficulty: Hard
Topic: Akumulasi mundur pada pi
Time Limit: 1.0 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Diberikan string S sepanjang n. Untuk setiap i dari 1 sampai n, hitung berapa
kali prefiks S[0..i-1] (yaitu awalan sepanjang i) muncul sebagai substring
di dalam S. Kemunculan boleh saling tumpang tindih.

Contoh untuk "aabaa":
  prefiks "a"     muncul 4 kali (posisi 1, 2, 4, 5)
  prefiks "aa"    muncul 2 kali (posisi 1, 4)
  prefiks "aab"   muncul 1 kali
  prefiks "aaba"  muncul 1 kali
  prefiks "aabaa" muncul 1 kali
Sehingga keluarannya: 4 2 1 1 1

📥 INPUT FORMAT:
- Satu baris berisi string S

📤 OUTPUT FORMAT:
- Satu baris berisi n bilangan: jumlah kemunculan tiap prefiks, dipisah spasi.

📏 CONSTRAINTS:
- 1 <= |S| <= 10^6
- Jawaban bisa besar, gunakan long long

📎 SAMPLE INPUT 1:
aabaa

📎 SAMPLE OUTPUT 1:
4 2 1 1 1

📎 SAMPLE INPUT 2:
aaa

📎 SAMPLE OUTPUT 2:
3 2 1

📎 SAMPLE INPUT 3:
abcab

📎 SAMPLE OUTPUT 3:
2 2 1 1 1

💡 HINT:
- Mulai dengan cnt[i] = 1 untuk semua i (tiap prefiks minimal muncul sekali,
  yaitu di posisi awal string).
- Kuncinya: setiap kemunculan prefiks sepanjang (i+1) OTOMATIS juga merupakan
  kemunculan border-nya, yaitu prefiks sepanjang pi[i].
- Jadi kontribusi harus dialirkan: cnt[pi[i]-1] += cnt[i].
- WAJIB ditelusuri MUNDUR (dari i = n-1 ke 1). Kalau maju, nilai cnt[i]
  belum lengkap saat dialirkan sehingga hasilnya salah.

🎯 Learning Goals:
- [ ] Memahami aliran kontribusi antar prefiks
- [ ] Menyadari kenapa harus ditelusuri mundur
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca S, bangun pi

    // TODO: cnt[i] = 1 untuk semua i

    // TODO: Telusuri MUNDUR, alirkan cnt[i] ke cnt[pi[i]-1]

    return 0;
}
