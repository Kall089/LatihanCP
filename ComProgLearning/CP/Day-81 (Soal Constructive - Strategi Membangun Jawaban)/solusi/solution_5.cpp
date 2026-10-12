/*
============================================================
✅ SOLUSI Exercise 5: Matriks Baris dan Kolom Seimbang
============================================================
Difficulty: Hard | Kompleksitas: O(n^2)

── TARGET ──────────────────────────────────────────────────
Total seluruh bilangan = n^2 (n^2 + 1) / 2.
Ada n baris, jadi tiap baris (dan tiap kolom) harus berjumlah
    n (n^2 + 1) / 2
Untuk n = 3 itu 15, untuk n = 5 itu 65.
Menghitung target lebih dulu memberi patokan yang jelas untuk
pemeriksamu.

── IDE: PECAH SETIAP BILANGAN MENJADI DUA DIGIT BASIS n ─────
Setiap bilangan dari 1 sampai n^2 bisa ditulis unik sebagai
    a * n + b + 1,     dengan a, b dari 0 sampai n-1.
Jadi mengisi matriks sama dengan menentukan sepasang (a, b)
untuk tiap sel, dengan syarat setiap pasangan muncul TEPAT
SEKALI.

── SYARAT AGAR JUMLAHNYA SERAGAM ───────────────────────────
Jumlah sebuah baris adalah
    n * (jumlah a di baris itu) + (jumlah b di baris itu) + n

Kalau pada SETIAP baris nilai a mengambil seluruh 0..n-1 tepat
sekali, maka jumlah a di tiap baris sama, yaitu n(n-1)/2. Hal
yang sama untuk b. Maka seluruh jumlah baris otomatis sama.
Syarat yang sama untuk kolom.

Artinya: a dan b masing-masing harus membentuk PERSEGI LATIN
(tiap nilai muncul sekali per baris dan sekali per kolom), dan
pasangan (a, b) tidak boleh berulang — yaitu keduanya harus
ORTOGONAL.

── KONSTRUKSI ──────────────────────────────────────────────
    a[i][j] = (i + j) mod n
    b[i][j] = (j - i) mod n
    M[i][j] = a * n + b + 1

Kedua-duanya jelas persegi Latin: untuk baris i tetap, (i+j)
mod n menjelajahi seluruh nilai saat j berjalan, begitu pula
(j-i) mod n.

Ortogonalitasnya: kalau (i1+j1, j1-i1) kongruen dengan
(i2+j2, j2-i2) modulo n, maka menjumlahkan kedua persamaan
memberi 2*j1 kongruen 2*j2, dan mengurangkannya memberi
2*i1 kongruen 2*i2.
Karena n GANJIL, angka 2 punya invers modulo n, sehingga
j1 = j2 dan i1 = i2. Jadi pasangannya unik. ∎

── KENAPA n HARUS GANJIL ───────────────────────────────────
Untuk n genap, angka 2 tidak punya invers modulo n dan
argumen di atas runtuh — konstruksinya menghasilkan duplikat.
Coba n = 2: seluruh sel memberi pasangan yang berulang.

Lebih dari itu, untuk n = 2 soalnya memang MUSTAHIL. Bilangan
1..4 berjumlah 10, jadi tiap baris harus berjumlah 5, yang
memaksa baris berisi {1,4} dan {2,3}. Cobalah keempat cara
menyusunnya: tidak ada yang membuat kedua kolom berjumlah 5.
(Untuk n genap >= 4 sebenarnya mungkin, tetapi konstruksinya
jauh lebih rumit. Soal ini menjamin n ganjil.)

── PEMERIKSA ───────────────────────────────────────────────
Harus memvalidasi TIGA hal:
  1. seluruh bilangan 1..n^2 muncul tepat sekali
  2. semua jumlah baris sama
  3. semua jumlah kolom sama, dan sama dengan jumlah baris
Jalankan untuk seluruh n ganjil dari 1 sampai 59.
Diverifikasi: lolos seluruhnya.

── JEBAKAN ─────────────────────────────────────────────────
1. Memakai a[i][j] = i (yaitu mengisi baris demi baris). Itu
   membuat jumlah tiap baris BERBEDA.
2. Lupa bahwa (j - i) bisa negatif di C++. Tulis
   ((j - i) % n + n) % n.
3. Lupa "+1" sehingga nilainya mulai dari 0.
4. Menguji hanya n = 3.
============================================================
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int a = (i + j) % n;
            int b = ((j - i) % n + n) % n;        // hindari sisa negatif
            cout << (ll)a * n + b + 1 << " \n"[j == n - 1];
        }
    }
    return 0;
}
