# Backtracking

[← README](README.md) · [Indeks CP](../README.md)

Backtracking adalah rekursi plus **undo**. Kamu memasang satu pilihan, memanggil rekursi, lalu mengembalikan state persis seperti semula. Analoginya maze: maju, kalau buntu mundur satu langkah, coba lorong lain.

Day terkait: **062**. Kalau cabang yang sama dihitung berulang tanpa undo yang bermakna, itu bukan backtracking: itu overlap, buka [memoization.md](memoization.md).

## Daftar isi

- [Pola coba, lanjut, mundur](#pola-coba-lanjut-mundur)
- [Kurung sah](#kurung-sah)
- [Enumerasi permutasi](#enumerasi-permutasi)
- [N-Queens](#n-queens)
- [Combination Sum dan pruning](#combination-sum-dan-pruning)
- [Subset Sum plus rekonstruksi](#subset-sum-plus-rekonstruksi)
- [Peta keputusan](#peta-keputusan)

---

## Pola coba, lanjut, mundur

**Teori:** Tiga baris mental: **pilih → rekursi → batal**. Pruning memotong cabang yang sudah mustahil sebelum daun. Alasan benar: setiap jalur di pohon keputusan adalah satu kandidat; undo menjamin jalur berikutnya tidak membawa sampah jalur lama. Tanpa undo, state global bocor.

**Kapan:** bangun objek dengan syarat: kurung sah, papan catur, sudoku, IP address, subset berconstraint. Ruang pencarian terbatas atau bisa dipangkas. Jangan jika submasalah overlap berat tanpa memo. Jangan jika `n` besar tanpa pruning kuat.

**Proses:** kerangka generik pada dua pilihan `A` lalu `B`.

```text
void dfs(state):
    if selesai: catat; return
    if mustahil: return
    for pilihan p:
        pasang(p)
        dfs(state')
        cabut(p)
```

Contoh mini: susun string panjang 2 dari `{X, Y}` tanpa huruf sama.

1. Pilih `X`, sisa `{Y}` → `XY`.
2. Undo `X`, pilih `Y`, sisa `{X}` → `YX`.
3. Tanpa undo, setelah `XY` huruf `X` tetap terpakai, `YX` hilang.
4. Pruning: jika sisa huruf kosong sebelum panjang 2, potong.
5. Daun sah: dua string.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void dfs_huruf(string& cur, vector<int>& used, const string& isi,
               vector<string>& semua) {
    if ((int)cur.size() == (int)isi.size()) {
        semua.push_back(cur);
        return;
    }
    for (int i = 0; i < (int)isi.size(); i++) {
        if (used[i]) continue;
        used[i] = 1;
        cur.push_back(isi[i]);
        dfs_huruf(cur, used, isi, semua);
        cur.pop_back();
        used[i] = 0;
    }
}

int main() {
    FASTIO;
    string isi = "XY", cur;
    vector<int> used(2, 0);
    vector<string> semua;
    dfs_huruf(cur, used, isi, semua);
    for (auto& s : semua) cout << s << '\n'; // XY YX
    return 0;
}
```

**Jebakan:**
1. Undo tidak simetris: mengeset `board[i] = 1` lalu lupa `= 0`.
2. Memangkas terlalu agresif sampai jawaban hilang.
3. Memangkas terlalu longgar sampai TLE.
4. Mengubah variabel global tanpa restore.

**Kompleksitas:** ukuran pohon setelah pruning. Sulit rumus tertutup. Ukur `n` kecil lalu extrapolasi.

---

## Kurung sah

**Teori:** Bangun string `n` pasang kurung. Syarat: di setiap awalan, jumlah tutup tidak melebihi buka; total masing-masing `n`. Analoginya antrian: tidak boleh ada orang keluar sebelum cukup orang masuk. Pruning: jangan menambah `(` jika `buka == n`; jangan menambah `)` jika `tutup == buka`.

**Kapan:** generate parentheses, pola Catalan. Kalau soal hanya minta **jumlah** string, rumus Catalan atau DP lebih tepat (folder 09). Jangan enumerasi jika `n >= 15` dan keluaran tidak diminta.

**Proses:** `n = 2`.

```text
""
  "("  buka=1 tutup=0
    "((" buka=2
      "(()"
        "(())" selesai
    "()" buka=1 tutup=1
      "()("
        "()()" selesai
```

Dua hasil: `(())` dan `()()`. Cabang `")..."` dipotong karena `tutup > buka`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void kurung(int buka, int tutup, int n, string& cur, vector<string>& semua) {
    if ((int)cur.size() == 2 * n) {
        semua.push_back(cur);
        return;
    }
    if (buka < n) {
        cur.push_back('(');
        kurung(buka + 1, tutup, n, cur, semua);
        cur.pop_back();
    }
    if (tutup < buka) {
        cur.push_back(')');
        kurung(buka, tutup + 1, n, cur, semua);
        cur.pop_back();
    }
}

int main() {
    FASTIO;
    string cur;
    vector<string> semua;
    kurung(0, 0, 2, cur, semua);
    for (auto& s : semua) cout << s << '\n';
    cout << semua.size() << '\n'; // 2
    return 0;
}
```

**Jebakan:**
1. Syarat `tutup <= buka` tertukar menjadi `tutup < n` saja: string `())(` lolos.
2. Lupa `pop_back`.
3. Menghitung Catalan di kepala lalu enumerasi tetap `n = 20`.

**Kompleksitas:** jumlah daun adalah Catalan `C_n`. Waktu `O(C_n · n)`.

---

## Enumerasi permutasi

**Teori:** Permutasi adalah urutan semua elemen tepat sekali. Rekursi: pilih siapa di posisi `pos`, tandai `used`, lanjut `pos+1`, lalu lepas tanda. Analoginya mengisi kursi satu per satu dari sisa orang. `n!` daun. Iteratif: `next_permutation` pada array terurut.

**Kapan:** `n <= 8` kalau kerja per permutasi `O(n)` (`8! = 40320`, `9! = 362880`, `10! = 3.6e6`, `11!` sudah berat). Jadwal, assignment kecil, cek semua urutan. Untuk `n = 12` jangan brute. Ada duplikat? Sort dulu, skip nilai sama yang sudah dipakai.

**Proses:** `{1, 2, 3}`.

```text
pos0 pilih 1 → 1 2 3 , 1 3 2
pos0 pilih 2 → 2 1 3 , 2 3 1
pos0 pilih 3 → 3 1 2 , 3 2 1
```

Enam permutasi. `next_permutation` dari `1 2 3` menghasilkan urutan leksikografis yang sama.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void permute(int pos, vector<int>& a, vector<int>& used, vector<int>& cur,
             vector<vector<int>>& semua) {
    int n = (int)a.size();
    if (pos == n) {
        semua.push_back(cur);
        return;
    }
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        used[i] = 1;
        cur[pos] = a[i];
        permute(pos + 1, a, used, cur, semua);
        used[i] = 0;
    }
}

vector<vector<int>> permute_stl(vector<int> a) {
    sort(a.begin(), a.end());
    vector<vector<int>> semua;
    do {
        semua.push_back(a);
    } while (next_permutation(a.begin(), a.end()));
    return semua;
}

int main() {
    FASTIO;
    vector<int> a = {1, 2, 3};
    vector<int> used(3, 0), cur(3);
    vector<vector<int>> semua;
    permute(0, a, used, cur, semua);
    cout << semua.size() << '\n'; // 6
    auto b = permute_stl(a);
    cout << b.size() << ' ' << b.back()[0] << b.back()[1] << b.back()[2] << '\n';
    return 0;
}
```

**Jebakan:**
1. Lupa `used[i] = 0`.
2. `next_permutation` tanpa `sort` awal hanya jalan dari urutan sekarang.
3. Duplikat `1,1,2` tanpa skip menghasilkan twin.
4. `n = 11` TLE.

**Kompleksitas:** waktu `O(n! · n)` jika menyalin. Stack `O(n)`.

---

## N-Queens

**Teori:** Taruh `n` ratu di papan `n×n` supaya tidak ada dua yang sebaris, sekolom, atau sediagonal. Backtracking baris demi baris: di baris `r` coba kolom `c` yang aman, lalu baris `r+1`. Kolom dipakai di `col[c]`. Diagonal `/` punya `r+c` konstan. Diagonal `\` punya `r-c` konstan (geser `+ n-1` agar indeks `>= 0`). Kenapa lengkap: setiap solusi punya tepat satu ratu per baris.

**Kapan:** `n <= 14` hitung solusi (`n=14` sekitar 365 ribu, `n=15` sekitar 2 juta). Jangan simulasi papan `O(n^2)` per cek jika `n` besar: bitmask `O(1)`.

**Proses:** `n = 4`. Dua solusi.

Satu solusi (0-index, kolom per baris): `1 3 0 2`

```text
. Q . .
. . . Q
Q . . .
. . Q .
```

Cek: kolom `{1,3,0,2}` unik. `r+c = {1,4,2,5}` unik. `r-c = {-1,-2,2,1}` unik. Aman.

Solusi kedua: `2 0 3 1`. `n = 2` dan `n = 3` nol solusi. `n = 1` satu. `n = 8` sembilan puluh dua.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int nqueens_hitung(int n) {
    int ans = 0;
    int col = 0, d1 = 0, d2 = 0;
    function<void(int)> dfs = [&](int r) {
        if (r == n) {
            ans++;
            return;
        }
        for (int c = 0; c < n; c++) {
            int a = 1 << c;
            int b = 1 << (r + c);
            int d = 1 << (r - c + n - 1);
            if ((col & a) || (d1 & b) || (d2 & d)) continue;
            col ^= a; d1 ^= b; d2 ^= d;
            dfs(r + 1);
            col ^= a; d1 ^= b; d2 ^= d;
        }
    };
    dfs(0);
    return ans;
}

int main() {
    FASTIO;
    cout << nqueens_hitung(1) << '\n'; // 1
    cout << nqueens_hitung(2) << '\n'; // 0
    cout << nqueens_hitung(3) << '\n'; // 0
    cout << nqueens_hitung(4) << '\n'; // 2
    cout << nqueens_hitung(8) << '\n'; // 92
    return 0;
}
```

Undo lewat XOR: bit yang baru dinyalakan dimatikan lagi. Itu simetris dan pendek.

**Jebakan:**
1. Lupa geser `r-c` agar tidak negatif.
2. Undo tidak lengkap.
3. `1 << (2n-2)` untuk `n = 16` melewati 31.
4. Menghitung rotasi sebagai unik atau tidak: ikuti soal.

**Kompleksitas:** kasar `O(n!)` dengan pruning jauh lebih kecil. `n=8` instan, `n=14` masih lolos. Memori `O(n)` stack plus beberapa `int`.

---

## Combination Sum dan pruning

**Teori:** Cari semua kombinasi yang jumlahnya `target`. Boleh ulang atau tidak, tergantung soal. Urutkan array, selalu maju `start` supaya `1,2` dan `2,1` tidak muncul sebagai dua jawaban. Pruning: jika `a[i] > sisa`, `break` karena array sudah terurut. Kenapa benar: setiap kombinasi non-menurun dihasilkan tepat sekali.

**Kapan:** `target` dan `n` kecil, atau nilai membesar cepat sehingga pruning kuat. Coin change yang minta **semua** kombinasi. Kalau hanya jumlah cara atau minimum koin, DP folder 09 jauh lebih tepat. Greedy “koin terbesar dulu” gagal untuk koin `{1, 3, 4}`, target `6`: greedy `4+1+1` tiga koin, optimal `3+3` dua koin.

**Proses:** `a = {2, 3, 6, 7}`, `target = 7`, boleh ulang.

```text
start=0 sisa=7
  ambil 2 → sisa 5
    ambil 2 → sisa 3
      2>1 stop setelah [2,2,2]
      ambil 3 → [2,2,3] sisa 0
    ambil 3 → [2,3] sisa 2, 3>2 stop
  ambil 3 → [3] sisa 4 → [3,3] sisa 1 stop
  ambil 6 → sisa 1 stop
  ambil 7 → [7]
```

Jawaban: `{2,2,3}` dan `{7}`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void comb_sum(int start, ll sisa, vector<int>& a, vector<int>& cur,
              vector<vector<int>>& semua) {
    if (sisa == 0) {
        semua.push_back(cur);
        return;
    }
    for (int i = start; i < (int)a.size(); i++) {
        if (a[i] > sisa) break;
        cur.push_back(a[i]);
        comb_sum(i, sisa - a[i], a, cur, semua); // i = boleh ulang
        cur.pop_back();
    }
}

ll greedy_koin_salah(vector<int> a, ll sisa) {
    sort(a.rbegin(), a.rend());
    ll hit = 0;
    for (int x : a) {
        hit += sisa / x;
        sisa %= x;
    }
    return sisa == 0 ? hit : -1;
}

int main() {
    FASTIO;
    vector<int> a = {2, 3, 6, 7};
    sort(a.begin(), a.end());
    vector<int> cur;
    vector<vector<int>> semua;
    comb_sum(0, 7, a, cur, semua);
    cout << semua.size() << '\n'; // 2
    for (auto& s : semua) {
        for (int x : s) cout << x << ' ';
        cout << '\n';
    }
    cout << greedy_koin_salah({1, 3, 4}, 6) << '\n'; // 3, padahal optimal 2
    return 0;
}
```

**Jebakan:**
1. `comb_sum(i+1)` padahal soal boleh ulang, kehilangan `{2,2,3}`.
2. Sebaliknya `i` padahal soal sekali pakai.
3. Lupa sort sebelum `break`.
4. Duplikat input `{2,2,3}` menghasilkan `{2,3}` dua kali tanpa skip.

**Kompleksitas:** terburuk eksponensial. Pruning plus sort memangkas banyak jika `a[i]` besar.

---

## Subset Sum plus rekonstruksi

**Teori:** “Apakah ada subset berjumlah `S`?” plus “berikan satu subsetnya”. Rekursi `pos, sisa`: lewat elemen atau ambil jika muat. Rekonstruksi: simpan pilihan yang sukses. Untuk `n <= 20` bitmask lebih pendek. Untuk `n = 40`, `S <= 1e6` memo/DP. Angka negatif membatalkan pruning `sisa < 0`.

**Kapan:** n kecil, atau sebagai oracle. Jangan `n = 40` tanpa memo. Jangan greedy terbesar.

**Proses:** `a = {3, 1, 7, 4}`, `S = 8`.

```text
pos0 ambil 3 → sisa 5
  pos1 ambil 1 → sisa 4
    7>4 skip
    ambil 4 → sisa 0  YA {3,1,4}
```

Jalur lain `{1,7}` juga 8. `S = 2` semua jalur gagal.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool subset_sum(int pos, ll sisa, const vector<ll>& a, vector<ll>& pilih) {
    if (sisa == 0) return true;
    if (pos == (int)a.size() || sisa < 0) return false;
    pilih.push_back(a[pos]);
    if (subset_sum(pos + 1, sisa - a[pos], a, pilih)) return true;
    pilih.pop_back();
    return subset_sum(pos + 1, sisa, a, pilih);
}

int main() {
    FASTIO;
    vector<ll> a = {3, 1, 7, 4};
    vector<ll> pilih;
    bool ok = subset_sum(0, 8, a, pilih);
    cout << ok << '\n';
    ll s = 0;
    for (ll x : pilih) {
        cout << x << ' ';
        s += x;
    }
    cout << "\njumlah=" << s << '\n';
    pilih.clear();
    cout << subset_sum(0, 2, a, pilih) << '\n'; // 0
    return 0;
}
```

Kalau `n` membesar dan `S` kecil, fungsi yang sama plus memo `(pos, sisa)` menjadi `O(nS)`. Itu jembatan ke [memoization.md](memoization.md).

**Jebakan:**
1. `sisa < 0` tidak dicek.
2. Rekonstruksi dari indeks yang salah.
3. `n = 40` tanpa memo TLE.
4. Angka negatif: kasus dasar `sisa < 0` tidak lagi sah.

**Kompleksitas:** `O(2^n)` waktu, stack `O(n)`. Dengan memo `O(n · S)`.

---

## Peta keputusan

```text
Bangun objek + syarat + undo
  → backtracking

Hanya himpunan, tanpa syarat rumit
  → subset-bitmask.md

Hitung cara / nilai optimal, state berulang
  → memoization.md lalu 09-dp

Koin / knapsack "ambil terbesar"
  → sering salah, bandingkan DP
```

| n | permutasi | N-Queens hitung | kurung Catalan |
| ---: | --- | --- | --- |
| 4 | 24 | 2 | 14 |
| 8 | 4e4 | 92 | 1430 |
| 10 | 3.6e6 | 724 | 16796 |
| 12 | 4.8e8 | 14200 | 208012 |

Ringkasan: pasang, rekursi, cabut. Pruning memotong yang mustahil. Greedy bukan pengganti pencarian jika syarat global.

Lanjut ke [memoization.md](memoization.md) jika pohonnya menghitung state yang sama berkali-kali.
