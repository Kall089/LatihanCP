# 08 — LIS

[← Bounded knapsack](07-bounded-knapsack.md) · [← 09-dp](README.md) · [LCS / edit →](09-lcs-edit.md)

Day ComprogLearning: **148**. Subsekuens naik terpanjang. Versi `O(n^2)` mudah diubah. Versi `O(n log n)` menyimpan ekor terkecil, bukan LIS-nya.

> **Ide satu kalimat:** `dp[i]` berakhir tepat di `i`, jawaban `max(dp)`; `tails[k]` adalah ekor terkecil panjang `k+1`, dan mencetak `tails` sebagai barisan hampir selalu salah.

## Daftar isi

- [Masalah dan greedy gagal](#masalah-dan-greedy-gagal)
- [Versi O(n kuadrat)](#versi-on-kuadrat)
- [Array tails](#array-tails)
- [Tails bukan LIS](#tails-bukan-lis)
- [Ketat versus tidak menurun](#ketat-versus-tidak-menurun)
- [Rekonstruksi](#rekonstruksi)
- [Menghitung banyak LIS](#menghitung-banyak-lis)
- [Penyamaran](#penyamaran)

---

## Masalah dan greedy gagal

**Teori:** Diberi `a[0..n-1]`. Cari subsekuens terpanjang yang nilainya naik. Subsekuens boleh loncat, urutan indeks tetap. Substring harus berdekatan. `[2, 7, 18]` adalah subsekuens dari contoh klasik, bukan substring. Panjang LIS unik; barisannya tidak. Greedy "ambil selama naik" gagal pada `[1, 100, 2, 3, 4]`: mengambil 100 menutup 2,3,4. Keputusan lokal merusak masa depan, jadi DP.

**Kapan:** panjang, hitung, atau rekonstruksi subsekuens monoton. `n ≤ 5000` → `O(n^2)`. `n ≤ 2e5` → `O(n log n)`. **Tidak:** substring naik (cukup sapuan `O(n)`).

**STATE:** greedy hanya menyimpan `last` = elemen terakhir yang sudah diambil, dan itu tidak cukup: mengambil 100 menutup semua ekor yang lebih kecil.

**TRANSISI:** transisi sah harus mempertimbangkan semua pendahulu `j < i` dengan `a[j] < a[i]`, bukan hanya ekor greedy.

**BASIS:** satu elemen adalah LIS panjang 1, dan itu berlaku untuk setiap indeks sebagai calon akhir.

**Proses:** `[1, 100, 2, 3, 4]`.

```
Greedy kiri: 1, 100  berhenti     panjang 2
Optimal:     1, 2, 3, 4           panjang 4
```

Contoh klasik `[10, 9, 2, 5, 3, 7, 101, 18]`:

```
LIS contoh: 2,5,7,18    panjang 4
            2,3,7,101   panjang 4
            2,5,7,101   panjang 4
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int greedyNaik(const vector<int>& a) {
    if (a.empty()) return 0;
    int last = a[0], len = 1;
    for (size_t i = 1; i < a.size(); i++)
        if (a[i] > last) {
            last = a[i];
            len++;
        }
    return len;
}

int main() {
    FASTIO;
    cout << greedyNaik({1, 100, 2, 3, 4}) << "\n"; // 2, salah
    return 0;
}
```

**Jebakan:** membaca "substring" sebagai "subsekuens". LC 674 adalah substring, jawabannya bukan LIS.

**Kompleksitas:** greedy `O(n)` dan salah. DP berikut `O(n^2)` atau `O(n log n)`.

---

## Versi O(n kuadrat)

**Teori:** Definisi "sampai i" tidak tahu ekor, jadi tidak bisa memutuskan apakah `a[i]` boleh disambung. Pakai "berakhir tepat di i", pelajaran yang sama dengan Kadane. `dp[i] = 1 + max { dp[j] : j < i, a[j] < a[i] }`, atau 1 jika kosong. Jawaban `max(dp)`, bukan `dp[n-1]`. Versi tidak-menurun mengganti `<` menjadi `<=`. Versi ini paling mudah dimodifikasi: berbobot, parent, penghitungan.

**Kapan:** `n ≤ 5000`, atau butuh banyak LIS / bobot. **Tidak:** `n = 2e5`.

**STATE:** `dp[i]` adalah panjang LIS yang berakhir tepat di indeks `i`.

**TRANSISI:** `dp[i] = 1 + max{ dp[j] : j < i dan a[j] < a[i] }`, atau 1 jika himpunan kosong.

**BASIS:** setiap `dp[i] = 1` (elemen itu sendiri).

**Proses:** `a = [10, 9, 2, 5, 3, 7, 101, 18]`.

```
i   a[i]  j dengan a[j]<a[i]     max dp[j]   dp[i]
0   10    —                      —           1
1    9    —                      —           1
2    2    —                      —           1
3    5    2                      1           2
4    3    2                      1           2
5    7    2,5,3                  2           3
6   101   2,5,3,7                3           4
7    18   2,5,3,7                3           4
```

`max = 4`. Indeks akhir bisa 6 atau 7.

`[5, 100, 1]`:

```
i   a    dp
0   5    1
1   100  2
2   1    1
```

`max = 2`. `dp[n-1] = 1` salah.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int lisLen(const vector<int>& a) {
    int n = (int)a.size();
    if (!n) return 0;
    vector<int> dp(n, 1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < i; j++)
            if (a[j] < a[i]) dp[i] = max(dp[i], dp[j] + 1);
    return *max_element(dp.begin(), dp.end());
}

vector<int> lisRebuildN2(const vector<int>& a) {
    int n = (int)a.size();
    if (!n) return {};
    vector<int> dp(n, 1), par(n, -1);
    int bestI = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++)
            if (a[j] < a[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                par[i] = j;
            }
        if (dp[i] > dp[bestI]) bestI = i;
    }
    vector<int> res;
    for (int v = bestI; v != -1; v = par[v]) res.push_back(a[v]);
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    FASTIO;
    vector<int> a = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << lisLen(a) << "\n";
    for (int x : lisRebuildN2(a)) cout << x << " ";
    cout << "\n";
    return 0;
}
```

**Jebakan:** jawaban `dp[n-1]`. `dp` diisi 0. Membandingkan indeks, bukan nilai.

**Kompleksitas:** `O(n^2)` waktu, `O(n)` memori.

---

## Array tails

**Teori:** `tails[k]` = nilai ekor terkecil di antara semua subsekuens naik berpanjang `k+1` yang memakai elemen yang sudah diproses. Ekor kecil selalu setidaknya sama baiknya untuk masa depan: apa pun yang nyambung ke ekor besar, nyambung juga ke ekor kecil. Exchange argument. `tails` selalu ketat naik, jadi `lower_bound` sah. Bukti: buang elemen terakhir subsekuens berpanjang `k+2` berujung `tails[k+1]`; sisa berujung lebih kecil dari `tails[k+1]`, dan `tails[k]` adalah ekor terkecil panjang `k+1`, maka `tails[k] < tails[k+1]`. Algoritma: untuk setiap `x`, `lower_bound` posisi pertama `>= x`. Jika di ujung, `push_back` (LIS memanjang). Jika di tengah, ganti ekor (panjang tetap, masa depan lebih terbuka).

**Kapan:** `n ≤ 2e5`, hanya panjang. **Tidak:** mencetak `tails` sebagai jawaban barisan.

**STATE:** `tails[k]` adalah ekor terkecil yang pernah dicapai untuk panjang `k+1` sampai elemen berjalan.

**TRANSISI:** `x` mengganti `tails[p]` dengan `p = lower_bound(x)`, atau menambah panjang jika `p == |tails|`.

**BASIS:** `tails` kosong. Elemen pertama selalu `push`.

**Proses:** `a = [10, 9, 2, 5, 3, 7, 101, 18]`.

```
x     lower_bound      aksi          tails
10    end              push          [10]
9     pos 0            ganti         [9]
2     pos 0            ganti         [2]
5     end              push          [2, 5]
3     pos 1            ganti         [2, 3]
7     end              push          [2, 3, 7]
101   end              push          [2, 3, 7, 101]
18    pos 3            ganti         [2, 3, 7, 18]
```

Panjang 4. Di sini `[2,3,7,18]` kebetulan LIS sah.

`a = [3, 1, 4, 1, 5, 9, 2, 6]`:

```
x    tails
3    [3]
1    [1]
4    [1,4]
1    [1,4]
5    [1,4,5]
9    [1,4,5,9]
2    [1,2,5,9]
6    [1,2,5,6]
```

Panjang 4. Contoh LIS sah: `[1,4,5,9]` atau `[1,4,5,6]`. `tails` akhir `[1,2,5,6]` **bukan** subsekuens: 2 muncul setelah 5 di array.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int lisLen(const vector<int>& a) {
    vector<int> tails;
    for (int x : a) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return (int)tails.size();
}

int main() {
    FASTIO;
    cout << lisLen({10, 9, 2, 5, 3, 7, 101, 18}) << "\n"; // 4
    cout << lisLen({1, 6, 7, 2, 3}) << "\n";              // 3
    return 0;
}
```

**Jebakan:** `upper_bound` pada versi ketat. `tails` tidak dikosongkan antar tes. Mengembalikan `tails` ke `cout`.

**Kompleksitas:** `O(n log n)` waktu, `O(n)` memori.

---

## Tails bukan LIS

**Teori:** Kesalahpahaman paling mahal. `tails.size()` dijamin sama dengan panjang LIS. Isi `tails` adalah campuran ekor dari beberapa subsekuens. Di tengah proses, `tails` bahkan bisa bukan subsekuens sama sekali. Patience sorting menumpuk kartu pada tumpukan pertama yang ekornya `>= x`; banyak tumpukan = panjang LIS. Tumpukan kiri ke kanan bukan barisan asli.

**Kapan:** setiap kali tergoda `return tails`. **Tidak:** memakai kebetulan `[2,3,7,18]` sebagai bukti bahwa `tails` selalu sah.

**STATE:** `tails[k]` ekor, bukan elemen ke-`k` dari satu LIS.

**TRANSISI:** mengganti `tails[p]` memutus rantai visual, tidak memutus panjang.

**BASIS:** setelah satu elemen, `tails` kebetulan sama dengan LIS.

**Proses:** `a = [1, 6, 7, 2, 3]`.

```
x=1   [1]           sah
x=6   [1, 6]        sah
x=7   [1, 6, 7]     sah
x=2   [1, 2, 7]     1,2,7 BUKAN subsekuens: 2 setelah 7
x=3   [1, 2, 3]     kebetulan sah lagi
```

Panjang 3 benar (`1,6,7` atau `1,2,3`). Langkah keempat sudah cukup untuk menolak "cetak tails".

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> tailsOnly(const vector<int>& a) {
    vector<int> tails;
    for (int x : a) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return tails; // JANGAN dianggap LIS
}

int main() {
    FASTIO;
    for (int x : tailsOnly({1, 6, 7, 2})) cout << x << " ";
    cout << "\n"; // 1 2 7  -- bukan subsekuens
    return 0;
}
```

**Jebakan:** tes hanya pada array yang `tails` kebetulan rapi. Tambah `[1,6,7,2]`.

**Kompleksitas:** sama `O(n log n)`. Kesalahan ini WA, bukan TLE.

---

## Ketat versus tidak menurun

**Teori:** `lower_bound(x)` mencari pertama `>= x`, lalu mengganti. Nilai sama ikut tergantikan, jadi `x` tidak menyambung dirinya → ketat naik. `upper_bound(x)` mencari pertama `> x`, nilai sama dilewati → tidak menurun. Uji wajib `[1,1,1]`: ketat 1, tidak menurun 3. Tertukar fungsi adalah WA diam pada array ada kembar.

**Kapan:** baca kata "strictly increasing" versus "non-decreasing". **Tidak:** menebak dari satu tes tanpa kembar.

**STATE:** `tails` terurut naik. Untuk non-decreasing, `tails` tidak-menurun, `upper_bound` tetap sah.

**TRANSISI:** pilih bound sesuai relasi.

**BASIS:** uji `[1,1,1]` sebelum submit.

**Proses:**

```
array     ketat lower   nondec upper
[1,1,1]   1             3
[1,2,2]   2             3
[3,2,1]   1             1
```

Jejak `[1,1,1]` ketat:

```
x=1  push [1]
x=1  lower di pos 0, ganti [1]
x=1  ganti [1]
panjang 1
```

Tidak menurun:

```
x=1  push [1]
x=1  upper di end, push [1,1]
x=1  push [1,1,1]
panjang 3
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int lisStrict(const vector<int>& a) {
    vector<int> tails;
    for (int x : a) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return (int)tails.size();
}

int lisNonDec(const vector<int>& a) {
    vector<int> tails;
    for (int x : a) {
        auto it = upper_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return (int)tails.size();
}

int lds(vector<int> a) {
    for (int& x : a) x = -x;
    return lisStrict(a);
}

int main() {
    FASTIO;
    cout << lisStrict({1, 1, 1}) << " " << lisNonDec({1, 1, 1}) << "\n"; // 1 3
    cout << lds({3, 2, 1}) << "\n"; // 3
    return 0;
}
```

**Jebakan:** LDS dengan reverse array tanpa menyesuaikan indeks rekonstruksi. Negasi lebih aman untuk nilai.

**Kompleksitas:** `O(n log n)`.

---

## Rekonstruksi

**Teori:** Saat `a[i]` mendarat di posisi `p`, catat `par[i] = idx[p-1]` yaitu indeks elemen yang saat itu mengakhiri panjang `p`. `idx[k]` adalah indeks elemen yang sedang mengisi `tails[k]`. Setelah selesai, mulai dari `idx.back()`, ikuti `par` sampai `-1`. Rantai ini sah: pendahulu muncul lebih dulu dan nilainya lebih kecil. Panjang rantai = `tails.size()`. Jangan mengembalikan isi `tails`.

**Kapan:** soal minta salah satu LIS. **Tidak:** `return tails`.

**STATE:** `par[i]` adalah indeks elemen sebelum `i` pada sebuah LIS yang berakhir di `i` dengan panjang optimal saat `i` diproses.

**TRANSISI:** `p = lower_bound`; jika `p > 0` maka `par[i] = idx[p-1]`; lalu tulis `tails[p]` dan `idx[p]`.

**BASIS:** `par[i] = -1` jika `p = 0`.

**Proses:** `a = [10, 9, 2, 5, 3, 7, 101, 18]`.

```
i  x    p   par[i]  tails        idx
0  10   0   -1      [10]         [0]
1  9    0   -1      [9]          [1]
2  2    0   -1      [2]          [2]
3  5    1   2       [2,5]        [2,3]
4  3    1   2       [2,3]        [2,4]
5  7    2   4       [2,3,7]      [2,4,5]
6  101  3   5       [2,3,7,101]  [2,4,5,6]
7  18   3   5       [2,3,7,18]   [2,4,5,7]
```

Mulai `idx.back()=7`: 18 ← par 5 (7) ← par 4 (3) ← par 2 (2). Barisan `2,3,7,18`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<int> lisRebuild(const vector<int>& a) {
    int n = (int)a.size();
    if (!n) return {};
    vector<int> tails, idx, par(n, -1);
    for (int i = 0; i < n; i++) {
        int p = (int)(lower_bound(tails.begin(), tails.end(), a[i]) - tails.begin());
        if (p > 0) par[i] = idx[p - 1];
        if (p == (int)tails.size()) {
            tails.push_back(a[i]);
            idx.push_back(i);
        } else {
            tails[p] = a[i];
            idx[p] = i;
        }
    }
    vector<int> res;
    for (int v = idx.back(); v != -1; v = par[v]) res.push_back(a[v]);
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    FASTIO;
    for (int x : lisRebuild({10, 9, 2, 5, 3, 7, 101, 18})) cout << x << " ";
    cout << "\n";
    return 0;
}
```

**Jebakan:** `par[i] = p-1` (posisi tails, bukan indeks array). Mencetak `tails`.

**Kompleksitas:** `O(n log n)` plus `O(panjang)` telusur.

---

## Menghitung banyak LIS

**Teori:** Bawa `len[i]` dan `cnt[i]`. Jika `len[j]+1 > len[i]`, salin `cnt`. Jika sama, jumlahkan. Pola `>` salin, `==` jumlah, sama seperti menghitung jalur terpendek. Jawaban jumlah `cnt[i]` pada `len[i] == max`. Modulo. Versi `O(n log n)` butuh Fenwick pasangan `(panjang, jumlah)` — Day 170, bukan di sini.

**Kapan:** "number of longest increasing subsequences". **Tidak:** menjumlahkan semua `cnt` tanpa filter panjang.

**STATE:** `len[i]` panjang LIS berakhir di `i`; `cnt[i]` banyaknya LIS sepanjang itu yang berakhir di `i`.

**TRANSISI:** untuk `j < i` dan `a[j] < a[i]`, perbarui seperti di atas.

**BASIS:** `len[i] = 1`, `cnt[i] = 1`.

**Proses:** `a = [1, 3, 5, 4, 7]`.

```
i  a  len  cnt  catatan
0  1  1    1
1  3  2    1    lewat 1
2  5  3    1    1,3,5
3  4  3    1    1,3,4
4  7  4    2    1,3,5,7 dan 1,3,4,7
```

`best = 4`, total 2.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

const ll MOD = 1e9 + 7;

ll countLIS(const vector<int>& a) {
    int n = (int)a.size();
    if (!n) return 0;
    vector<int> len(n, 1);
    vector<ll> cnt(n, 1);
    int best = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++)
            if (a[j] < a[i]) {
                if (len[j] + 1 > len[i]) {
                    len[i] = len[j] + 1;
                    cnt[i] = cnt[j];
                } else if (len[j] + 1 == len[i]) {
                    cnt[i] = (cnt[i] + cnt[j]) % MOD;
                }
            }
        best = max(best, len[i]);
    }
    ll total = 0;
    for (int i = 0; i < n; i++)
        if (len[i] == best) total = (total + cnt[i]) % MOD;
    return total;
}

int main() {
    FASTIO;
    cout << countLIS({1, 3, 5, 4, 7}) << "\n"; // 2
    cout << countLIS({10, 9, 2, 5, 3, 7, 101, 18}) << "\n";
    return 0;
}
```

**Jebakan:** `cnt[i] += 1` setiap kali, bukan `cnt[j]`. Menjumlahkan tanpa `len == best`.

**Kompleksitas:** `O(n^2)`.

---

## Penyamaran

**Teori:** LIS sering tidak menyebut "longest increasing". Box stacking / Russian doll: urutkan lebar naik; jika lebar sama, tinggi **menurun**; lalu LIS pada tinggi. Tie-break menurun mencegah dua kotak sama lebar saling menumpuk. Dilworth: jumlah minimum barisan tidak-naik yang menutupi array = panjang LIS. Patience sorting dan "sistem antirudal" adalah Dilworth. LIS berbobot (AtCoder DP-Q) mengganti `+1` dengan `+w[i]`; cepatnya butuh Fenwick. LIS adalah jalur terpanjang di DAG `i -> j` jika `i < j` dan `a[i] < a[j]`.

**Kapan:** dua dimensi "muat di dalam", partisi minimum antimonoton, bunga berbobot. **Tidak:** dua kotak sama lebar diizinkan menumpuk — baca soal.

**STATE:** setelah sort, `h[i]` adalah tinggi kotak ke-`i`; LIS ketat pada `h` adalah rantai sah.

**TRANSISI:** sama `lisStrict(h)`.

**BASIS:** satu kotak.

**Proses:** `[(1,1), (1,2), (2,3)]`.

```
tie-break menurun: (1,2), (1,1), (2,3)
h = [2, 1, 3]
LIS ketat = 2   benar (satu kotak lebar 1 + kotak 2,3)

tie-break menaik: (1,1), (1,2), (2,3)
h = [1, 2, 3]
LIS = 3   salah, dua kotak lebar 1
```

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int lisStrict(const vector<int>& a) {
    vector<int> tails;
    for (int x : a) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) tails.push_back(x);
        else *it = x;
    }
    return (int)tails.size();
}

int russianDoll(vector<pair<int, int>> box) {
    sort(box.begin(), box.end(), [](auto A, auto B) {
        if (A.first != B.first) return A.first < B.first;
        return A.second > B.second;
    });
    vector<int> h;
    for (auto& b : box) h.push_back(b.second);
    return lisStrict(h);
}

int main() {
    FASTIO;
    cout << russianDoll({{1, 1}, {1, 2}, {2, 3}}) << "\n"; // 2
    return 0;
}
```

**Jebakan:** sort tinggi naik saat lebar sama. `a[i] = 0` sebagai netral padahal nilai boleh 0 atau negatif — `dp` diisi 1, bukan 0.

**Kompleksitas:** sort `O(n log n)` plus LIS `O(n log n)`.

---

Uji cepat: `[1,100,2,3,4]` greedy 2, LIS 4; klasik panjang 4, `max(dp)` bukan `dp[n-1]`; `[1,6,7,2,3]` tails tengah `[1,2,7]` bukan subsekuens; `[1,1,1]` ketat 1 / nondec 3; Russian doll contoh 2. Setengah pertama folder 09 selesai. String dan grid mulai di [09-lcs-edit.md](09-lcs-edit.md).
