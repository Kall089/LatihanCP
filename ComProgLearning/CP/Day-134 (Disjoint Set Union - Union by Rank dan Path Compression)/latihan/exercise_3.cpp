/*
============================================================
🏋️ Exercise 3: Total Kekayaan Kelompok
============================================================
Day: 134 | Difficulty: Medium
Topic: DSU dengan agregat per komponen
Time Limit: 2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
Ada N orang, orang ke-i punya kekayaan w[i]. Mula-mula setiap orang
berdiri sendiri.
Ada Q operasi, masing-masing salah satu dari dua jenis:
- "1 a b" : gabungkan kelompok orang a dan kelompok orang b menjadi satu.
- "2 a"   : cetak TOTAL kekayaan seluruh anggota kelompok orang a.
Perhatikan bahwa operasi jenis 1 pada dua orang yang sudah sekelompok tidak
mengubah apa pun.

📥 INPUT FORMAT:
- Baris pertama: N dan Q
- Baris kedua: N bilangan w[i]
- Q baris berikutnya: operasi sesuai format di atas

📤 OUTPUT FORMAT:
- Satu baris untuk setiap operasi jenis 2

📏 CONSTRAINTS:
- 1 <= N, Q <= 2 * 10^5
- 1 <= w[i] <= 10^9

📎 SAMPLE INPUT 1:
4 5
10 20 30 40
2 1
1 1 2
2 2
1 3 4
2 3

📎 SAMPLE OUTPUT 1:
10
30
70

💡 HINT: Simpan agregat (di sini total kekayaan) di satu tempat per
         kelompok, bukan di setiap anggota. Tempat yang paling masuk akal
         adalah perwakilan kelompok itu.
         Saat dua kelompok bergabung, agregat keduanya dijumlahkan ke
         perwakilan yang BARU.
         Ada satu jebakan yang sangat sering terjadi di sini: saat MEMBACA
         agregat, kamu harus membacanya dari tempat yang benar. Membaca
         langsung dari indeks orang yang ditanyakan akan memberi jawaban
         yang salah begitu orang itu bukan lagi perwakilan kelompoknya.
         Perhatikan juga tipe data: 2*10^5 orang dengan kekayaan 10^9.

🎯 Learning Goals:
- [ ] Menyimpan dan menggabungkan agregat per komponen
- [ ] Menyadari bahwa agregat hanya valid di perwakilan
- [ ] Refleks memakai long long untuk akumulasi
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: array agregat, diinisialisasi dengan nilai masing-masing orang

    // TODO: saat unite, jumlahkan agregat ke perwakilan baru

    // TODO: saat membaca, PASTIKAN membaca dari perwakilan

    return 0;
}
