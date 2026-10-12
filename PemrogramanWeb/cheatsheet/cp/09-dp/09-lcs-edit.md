# 09 — LCS, edit distance, SCS

[← 08-lis](08-lis.md) · [README](README.md) · [10-grid →](10-grid.md)

Day **149**. Dua string, satu tabel `(n+1) × (m+1)`. String **0-indexed**, tabel **1-indexed**: huruf terakhir prefiks `i` adalah `a[i-1]`. Baris 0 dan kolom 0 adalah string kosong.

> **Satu kalimat:** LCS mencocokkan huruf yang sama tanpa wajib berdekatan; edit distance membayar sisip, hapus, atau ganti; SCS adalah string terpendek yang memuat keduanya sebagai subsekuens.

Tiga pertanyaan tetap wajib sebelum mengetik loop:

```
1. STATE     : dp[i][j] artinya apa? (kalimat lengkap)
2. TRANSISI  : dari sel mana, operator apa (+ / max / min)
3. BASIS     : baris 0 dan kolom 0 nilainya berapa, kenapa?
```

Kalau STATE tertukar antara "prefiks i dan j" dengan "berakhir tepat di i dan j", rekonstruksi dan turunan (substring, palindrom) ikut rusak.

## Daftar isi

- [Konvensi indeks](#konvensi-indeks)
- [LCS](#lcs)
- [Tabel wajib ABCD / ACBD](#tabel-wajib-abcd--acbd)
- [Rekonstruksi LCS](#rekonstruksi-lcs)
- [Edit distance](#edit-distance)
- [Tabel kitten / sitting](#tabel-kitten--sitting)
- [Edit kata pendek](#edit-kata-pendek)
- [SCS](#scs)
- [Turunan: hapus saja, substring, LPS](#turunan-hapus-saja-substring-lps)
- [Satu baris vs tabel penuh](#satu-baris-vs-tabel-penuh)
- [Template gabungan](#template-gabungan)
- [Peta jebakan](#peta-jebakan)
- [Tabel uji](#tabel-uji)

---

## Konvensi indeks

**Teori:** Campuran 0/1 adalah sumber off-by-one nomor satu pada DP string. Analoginya dua penggaris: penggaris string dimulai di 0 (karakter pertama), penggaris tabel dimulai di 1 karena kolom 0 disiapkan untuk prefiks kosong. Sel `dp[i][j]` "sudah memutuskan" `i` huruf pertama `a` dan `j` huruf pertama `b`. Huruf yang sedang dibandingkan selalu `a[i-1]` dan `b[j-1]`.

**Kapan:** semua pola dua string di file ini. **Tidak:** jika kedua array sudah 1-indexed dari input — sesuaikan, jangan campur dua kebiasaan dalam satu fungsi.

**STATE:** `dp[i][j]` adalah jawaban untuk prefiks `a[0..i-1]` dan `b[0..j-1]`.

**TRANSISI:** belum ada rumus khusus di sini; yang penting arah baca: kiri = buang huruf `b`, atas = buang huruf `a`, diagonal = pasangkan kedua huruf.

**BASIS:** `dp[0][*]` dan `dp[*][0]` diisi menurut soal (0 untuk LCS, `i`/`j` untuk edit).

**Proses (table):** peta sel untuk `a = "AB"`, `b = "A"`.

| sel | artinya | huruf yang dibanding |
|---|---|---|
| `dp[0][0]` | `""` vs `""` | tidak ada |
| `dp[1][0]` | `"A"` vs `""` | tidak ada |
| `dp[1][1]` | `"A"` vs `"A"` | `a[0]` vs `b[0]` |
| `dp[2][1]` | `"AB"` vs `"A"` | `a[1]` vs `b[0]` |

**Kode modular:** tidak ada fungsi algoritma di bagian ini; pakai potongan uji indeks.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void jelaskanSel(const string& a, const string& b, int i, int j) {
    string prefA = a.substr(0, i);
    string prefB = b.substr(0, j);
    cout << "dp[" << i << "][" << j << "] = \"" << prefA << "\" vs \"" << prefB << "\"";
    if (i > 0 && j > 0) cout << " banding " << a[i - 1] << " " << b[j - 1];
    cout << '\n';
}

int main() {
    FASTIO;
    jelaskanSel("AB", "A", 2, 1);
    return 0;
}
```

**Jebakan:**

1. Menulis `if (a[i] == b[j])` di loop `i = 1..n` — itu huruf berikutnya, bukan huruf prefiks.
2. Membuat tabel `n × m` tanpa baris/kolom kosong, lalu basis jadi kacau.
3. `substr(0, i)` lupa bahwa `i` adalah panjang, bukan indeks terakhir.

**Kompleksitas:** penjelasan O(1). Kesalahan indeks merusak seluruh `O(nm)`.

---

## LCS

**Teori:** Longest Common Subsequence adalah subsekuens terpanjang yang muncul di kedua string, tidak wajib berdekatan. Analoginya dua antrean tiket: kamu mencocokkan orang dengan nama sama, atau melewatkan satu antrean. Keputusan terakhir hanya tiga: pakai pasangan huruf jika sama, buang ekor `a`, atau buang ekor `b`.

Kenapa saat huruf sama kita **wajib** boleh memakai pasangan itu? Argumen tukar: jika LCS optimal tidak memakai `a[i-1]` yang sama dengan `b[j-1]`, pasangan itu bisa disisipkan atau menggantikan huruf yang lebih kiri tanpa memperpendek. Jadi cabang diagonal `+ 1` sudah mencakup yang optimal. Saat beda, salah satu ekor harus dibuang.

Bukan substring. `"ABC"` dan `"ACB"` punya LCS `"AC"` atau `"AB"` (panjang 2), bukan `"ABC"`.

**Kapan:** "common subsequence", kemiripan dua teks, batu bata untuk SCS / penghapusan / LPS. **Tidak:** harus kontigu (itu longest common **substring**). `n, m ≥ 5000` tabel penuh sering TLE/MLE — panjang saja bisa digulung.

**STATE:** `dp[i][j]` adalah panjang LCS dari prefiks `a[0..i-1]` dan prefiks `b[0..j-1]`.

**TRANSISI:**

```
jika a[i-1] == b[j-1]:  dp[i][j] = dp[i-1][j-1] + 1
jika tidak:             dp[i][j] = max(dp[i-1][j], dp[i][j-1])
```

Tidak ada `max` dengan diagonal saat huruf beda: memasangkan huruf berbeda tidak sah.

**BASIS:** `dp[0][j] = 0` dan `dp[i][0] = 0` karena LCS dengan string kosong adalah 0.

**Proses (table):** contoh kedua, lebih panjang, `a = "AXYT"`, `b = "AYZX"` — dipakai sebagai latihan setelah tabel wajib.

|  | `""` | A | Y | Z | X |
|---|---|---|---|---|---|
| `""` | 0 | 0 | 0 | 0 | 0 |
| A | 0 | 1 | 1 | 1 | 1 |
| X | 0 | 1 | 1 | 1 | 2 |
| Y | 0 | 1 | 2 | 2 | 2 |
| T | 0 | 1 | 2 | 2 | 2 |

Panjang 2. Salah satu LCS: `AY` atau `AX`.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int lcs(const string& a, const string& b) {
    int n = (int)a.size(), m = (int)b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[n][m];
}

int main() {
    FASTIO;
    cout << lcs("ABCD", "ACBD") << '\n'; // 3
    cout << lcs("AXYT", "AYZX") << '\n'; // 2
    return 0;
}
```

**Jebakan:**

1. Off-by-one `a[i] == b[j]`.
2. Saat cocok tetap menulis `max(atas, kiri, diagonal+1)` — panjang biasanya masih benar, rekonstruksi berantakan.
3. Mengambil `max` seluruh tabel (itu definisi "berakhir di i,j", bukan "prefiks").
4. Mengira LCS unik: panjang unik, barisannya tidak.

**Kompleksitas:** `O(nm)` waktu, `O(nm)` memori. Panjang saja: `O(min(n,m))` memori (lihat [13-memori](13-memori.md)).

---

## Tabel wajib ABCD / ACBD

Ini tabel yang harus bisa digambar tanpa melihat kunci. `a = "ABCD"`, `b = "ACBD"`.

**Teori:** Kedua string adalah permutasi hampir sama: `B` dan `C` ditukar. LCS tidak bisa menyimpan `BC` dan `CB` sekaligus, jadi satu huruf dari pasangan itu harus dibuang. Sisa `A` dan `D` selalu masuk. Panjang 3, bukan 4.

**Kapan:** latihan tangan sebelum kontes. **Tidak:** menghafal angka tanpa mengisi sel per sel.

**STATE / TRANSISI / BASIS:** sama dengan bagian LCS.

**Proses (table):**

|  | `""` | A | C | B | D |
|---|---|---|---|---|---|
| `""` | 0 | 0 | 0 | 0 | 0 |
| A | 0 | **1** | 1 | 1 | 1 |
| B | 0 | 1 | 1 | **2** | 2 |
| C | 0 | 1 | **2** | 2 | 2 |
| D | 0 | 1 | 2 | 2 | **3** |

Isi sel penting:

| sel | huruf | rumus | nilai |
|---|---|---|---|
| `(1,1)` | A=A | diagonal + 1 | 1 |
| `(2,2)` | B≠C | max(1, 1) | 1 |
| `(2,3)` | B=B | `dp[1][2]+1 = 2` | 2 |
| `(3,2)` | C=C | `dp[2][1]+1 = 2` | 2 |
| `(3,3)` | C≠B | max(2, 2) | 2 |
| `(4,4)` | D=D | `dp[3][3]+1 = 3` | 3 |

Dua LCS sah: `ABD` (turun lewat `B` di kolom 3) dan `ACD` (lewat `C` di kolom 2). `ABCD` bukan subsekuens `ACBD` karena `B` muncul sebelum `C` di `a` tetapi setelah `C` di `b`.

**Kode modular:** pakai `lcs` di atas; cetak tabel untuk belajar.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

vector<vector<int>> lcsTable(const string& a, const string& b) {
    int n = (int)a.size(), m = (int)b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    return dp;
}

void cetakTabel(const string& a, const string& b, const vector<vector<int>>& dp) {
    cout << "   ";
    cout << ". ";
    for (char c : b) cout << c << ' ';
    cout << '\n';
    for (int i = 0; i <= (int)a.size(); i++) {
        cout << (i == 0 ? '.' : a[i - 1]) << ' ';
        for (int j = 0; j <= (int)b.size(); j++) cout << dp[i][j] << ' ';
        cout << '\n';
    }
}

int main() {
    FASTIO;
    string a = "ABCD", b = "ACBD";
    auto dp = lcsTable(a, b);
    cetakTabel(a, b, dp);
    cout << "panjang " << dp[4][4] << '\n';
    return 0;
}
```

**Jebakan:** mengisi `(3,3)` dengan 3 karena "sudah ada A,B,C" — `C` dan `B` tidak bisa berurutan di kedua string. Mengira hanya ada satu LCS.

**Kompleksitas:** `O(nm)` mengisi, `O(nm)` mencetak.

---

## Rekonstruksi LCS

**Teori:** Nilai `dp[n][m]` adalah panjang, bukan barisan. Jejak mundur dari pojok kanan-bawah: jika huruf sama, huruf itu masuk LCS lalu diagonal; jika beda, pilih tetangga yang nilainya sama dengan sel sekarang (atas atau kiri). Analoginya menelusuri jejak kaki di salju dari tujuan ke awal, lalu membalik urutan.

Saat seri `atas == kiri`, pilih satu kebijakan dan **tetap**: atas dulu menghasilkan salah satu LCS, kiri dulu LCS lain. Keduanya sah selama panjangnya `dp[n][m]`.

**Kapan:** soal minta string LCS, bukan hanya angka. **Tidak:** jika hanya panjang — jangan bangun string.

**STATE:** sama `dp[i][j]`. Pointer implisit: induk adalah `(i-1,j-1)`, `(i-1,j)`, atau `(i,j-1)`.

**TRANSISI mundur:**

```
jika a[i-1] == b[j-1]:  ambil huruf, (i,j) -> (i-1,j-1)
else jika dp[i-1][j] >= dp[i][j-1]: naik
else: geser kiri
```

**BASIS mundur:** berhenti saat `i == 0` atau `j == 0`.

**Proses (table):** dari `(4,4)` pada ABCD / ACBD.

| langkah | `(i,j)` | banding | keputusan | huruf terkumpul (terbalik) |
|---|---|---|---|---|
| 1 | 4,4 | D=D | ambil, diagonal | D |
| 2 | 3,3 | C≠B | atas=2, kiri=2, pilih atas | D |
| 3 | 2,3 | B=B | ambil | BD |
| 4 | 1,2 | A≠C | atas=0 < kiri=1, kiri | BD |
| 5 | 1,1 | A=A | ambil | BDA |
| 6 | 0,0 | selesai | `reverse` | ABD |

Jika di `(3,3)` pilih kiri ke `(3,2)` (`C=C`), hasil `ACD`.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

string lcsString(const string& a, const string& b) {
    int n = (int)a.size(), m = (int)b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    string res;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            res += a[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) i--;
        else j--;
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    FASTIO;
    cout << lcsString("ABCD", "ACBD") << '\n'; // ABD (kebijakan atas dulu)
    return 0;
}
```

**Jebakan:** lupa `reverse`. Membandingkan huruf saat beda lalu tetap mengambil huruf. Rolling array: tabel sudah hilang, rekonstruksi mustahil (simpan parent atau tabel penuh — [12-rekonstruksi](12-rekonstruksi.md)).

**Kompleksitas:** isi `O(nm)`, jejak `O(n+m)`.

---

## Edit distance

**Teori:** Levenshtein distance adalah jumlah operasi minimum mengubah `a` menjadi `b`. Tiga operasi, masing-masing biaya 1: **sisip** satu huruf, **hapus** satu huruf, **ganti** satu huruf. Analoginya menyunting naskah: kamu boleh coret, sisip, atau ganti kata.

Di tabel, tiga tetangga punya arti tetap:

| tetangga | operasi | arti |
|---|---|---|
| diagonal `dp[i-1][j-1]` | ganti (atau 0 jika sama) | pasangkan kedua huruf |
| atas `dp[i-1][j]` | hapus `a[i-1]` | `a` lebih panjang |
| kiri `dp[i][j-1]` | sisip `b[j-1]` | `b` lebih panjang |

Jika huruf sama, ganti gratis: `dp[i][j] = dp[i-1][j-1]`. Jika biaya ganti `> 1` (lebih mahal dari sisip+hapus), `min` otomatis menghindari ganti — tidak perlu cabang khusus.

Beda dengan LCS: basis **bukan nol**. Mengubah `"abc"` jadi `""` butuh 3 hapus.

**Kapan:** spell-check, beda DNA, "minimum operations to convert". **Tidak:** hanya sisip/hapus tanpa ganti — itu `n + m - 2 * LCS`. Hanya ganti tanpa sisip/hapus — panjang harus sama, Hamming.

**STATE:** `dp[i][j]` adalah jumlah operasi minimum untuk mengubah prefiks `a[0..i-1]` menjadi prefiks `b[0..j-1]`.

**TRANSISI:**

```
cost = (a[i-1] == b[j-1] ? 0 : 1)
dp[i][j] = min(
    dp[i-1][j-1] + cost,  // ganti atau cocok
    dp[i-1][j] + 1,       // hapus
    dp[i][j-1] + 1        // sisip
)
```

**BASIS:** `dp[i][0] = i` (hapus semua), `dp[0][j] = j` (sisip semua).

**Proses (table):** lihat bagian kitten/sitting dan kata pendek di bawah.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int editDistance(const string& a, const string& b) {
    int n = (int)a.size(), m = (int)b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
        }
    }
    return dp[n][m];
}

int main() {
    FASTIO;
    cout << editDistance("kitten", "sitting") << '\n'; // 3
    cout << editDistance("cat", "cut") << '\n';       // 1
    return 0;
}
```

**Jebakan:**

1. Basis 0 seperti LCS — seluruh tabel terlalu kecil, WA "terlihat masuk akal".
2. Lupa cabang ganti: hanya sisip/hapus, jawaban `n+m-2*LCS` (beda soal).
3. Rekonstruksi `while (i && j)` — sisa prefiks tidak terproses. Pakai `i > 0 || j > 0`.
4. `int` cukup untuk jarak (maks `n+m`), tapi versi berbobot besar wajib `ll`.

**Kompleksitas:** `O(nm)` waktu, `O(nm)` atau `O(min(n,m))` memori.

---

## Tabel kitten / sitting

`a = "kitten"`, `b = "sitting"`. Jawaban klasik 3: `k→s`, `e→i`, sisip `g`.

**Teori:** Prefiks `"ittn"` hampir sama dengan `"ittin"`. Bagian yang sudah cocok (`itt` … `n`) menekan biaya. Sisip `g` di akhir dan dua ganti di ujung-ujung.

**Kapan:** hafalan tangan yang paling sering diminta. **Tidak:** menyalin tabel tanpa menghitung satu sel diagonal.

**STATE / TRANSISI / BASIS:** sama edit distance.

**Proses (table):**

|  | `""` | s | i | t | t | i | n | g |
|---|---|---|---|---|---|---|---|---|
| `""` | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| k | 1 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| i | 2 | 2 | 1 | 2 | 3 | 4 | 5 | 6 |
| t | 3 | 3 | 2 | 1 | 2 | 3 | 4 | 5 |
| t | 4 | 4 | 3 | 2 | 1 | 2 | 3 | 4 |
| e | 5 | 5 | 4 | 3 | 2 | 2 | 3 | 4 |
| n | 6 | 6 | 5 | 4 | 3 | 3 | 2 | **3** |

Sel yang meragukan:

| sel | kenapa |
|---|---|
| `(1,1)` k≠s | `1 + min(0,1,1) = 1` (ganti) |
| `(2,2)` i=i | diagonal 1, gratis |
| `(4,4)` t=t | rantai `itt` vs `itt` sudah 1 (sisa ganti k→s) |
| `(5,5)` e≠i | ganti, 2 |
| `(6,6)` n=n | 2 |
| `(6,7)` n≠g | sisip g, 3 |

Satu urutan operasi (bukan satu-satunya):

```
kitten
sitten   (ganti k → s)
sittin   (ganti e → i)
sitting  (sisip g)
```

**Kode modular:** `editDistance` di atas. Jejak operasi:

```cpp
vector<string> editOps(const string& a, const string& b) {
    int n = (int)a.size(), m = (int)b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1];
            else dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
    vector<string> ops;
    int i = n, j = m;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && a[i - 1] == b[j - 1]) {
            i--;
            j--;
        } else if (i > 0 && j > 0 && dp[i][j] == dp[i - 1][j - 1] + 1) {
            ops.push_back(string("GANTI ") + a[i - 1] + "->" + b[j - 1]);
            i--;
            j--;
        } else if (i > 0 && dp[i][j] == dp[i - 1][j] + 1) {
            ops.push_back(string("HAPUS ") + a[i - 1]);
            i--;
        } else {
            ops.push_back(string("SISIP ") + b[j - 1]);
            j--;
        }
    }
    reverse(ops.begin(), ops.end());
    return ops;
}
```

**Jebakan:** mengutamakan ganti sebelum mengecek "huruf sama" — operasi palsu `GANTI x->x`. Basis baris 0 diisi 0.

**Kompleksitas:** sama `O(nm)`.

---

## Edit kata pendek

Kalau tabel 6×7 terasa panjang, kuasai dulu kata 3 huruf. Pola yang sama, sel lebih sedikit.

**Teori:** `"cat"` → `"cut"` hanya ganti `a→u`. `"dog"` → `"cat"` tiga ganti. `""` → `"hi"` dua sisip.

**Kapan:** cek basis dan satu sel diagonal sebelum soal panjang. **Tidak:** mengganti latihan kitten jika soal ujian meminta tabel itu.

**STATE / TRANSISI / BASIS:** sama.

**Proses (table):** `a = "cat"`, `b = "cut"`.

|  | `""` | c | u | t |
|---|---|---|---|---|
| `""` | 0 | 1 | 2 | 3 |
| c | 1 | 0 | 1 | 2 |
| a | 2 | 1 | 1 | 2 |
| t | 3 | 2 | 2 | **1** |

Sel `(2,2)`: `a≠u`, `1 + min(0,1,1) = 1`. Jawaban 1.

`"dog"` vs `"cat"`:

|  | `""` | c | a | t |
|---|---|---|---|---|
| `""` | 0 | 1 | 2 | 3 |
| d | 1 | 1 | 2 | 3 |
| o | 2 | 2 | 2 | 3 |
| g | 3 | 3 | 3 | **3** |

Semua huruf beda, panjang sama: 3 ganti. Sisip+hapus juga 2 per huruf, lebih mahal.

**Kode modular:**

```cpp
int main() {
    FASTIO;
    cout << editDistance("cat", "cut") << '\n'; // 1
    cout << editDistance("dog", "cat") << '\n'; // 3
    cout << editDistance("", "hi") << '\n';     // 2
    cout << editDistance("abc", "") << '\n';    // 3
    return 0;
}
```

**Jebakan:** `"dog"`/`"cat"` diisi 0 di `(1,1)` karena "sama-sama 3 huruf". Jarak bukan selisih panjang.

**Kompleksitas:** `O(9)` untuk n=m=3 — dipakai untuk debug, bukan alasan mengubah rumus.

---

## SCS

**Teori:** Shortest Common Supersequence adalah string terpendek yang memuat `a` dan `b` sebagai subsekuens. Setiap huruf LCS cukup ditulis **sekali**. Huruf yang bukan LCS harus ditulis dari string asalnya. Rumus panjang:

```
|SCS| = n + m - |LCS|
```

Analoginya dua daftar belanja: barang yang sama dibeli sekali, sisanya digabung.

Rekonstruksi hampir seperti LCS, tetapi saat huruf **beda** huruf yang dibuang tetap dimasukkan ke hasil (karena SCS harus memuat semua huruf). Sisa prefiks setelah loop wajib ditambahkan.

**Kapan:** "shortest supersequence", gabung dua urutan dengan urutan relatif dipertahankan. **Tidak:** shortest common **substring** (itu beda kata). Merge tanpa menghormati urutan — itu union multiset, bukan SCS.

**STATE:** tabel LCS yang sama, atau `scs[i][j] = i+j-lcs[i][j]`.

**TRANSISI panjang:** `scs[i][j] = n+m-lcs(a,b)` pada ujung, atau langsung:

```
jika sama: scs[i][j] = scs[i-1][j-1] + 1
jika beda: scs[i][j] = 1 + min(scs[i-1][j], scs[i][j-1])
```

**BASIS:** `scs[i][0] = i`, `scs[0][j] = j` (seluruh sisa harus ditulis).

**Proses (table):** `a = "ABCD"`, `b = "ACBD"`, LCS = 3, `|SCS| = 4+4-3 = 5`.

Dua SCS sah: `ABCBD` dan `ACBCD`.

| string | ABCD sebagai subsekuens? | ACBD sebagai subsekuens? |
|---|---|---|
| `ABCBD` | A,B,C,D | A,C,B,D |
| `ACBCD` | A,B,C,D | A,C,B,D |
| `ABCD` | ya | tidak (`B` sebelum `C`) |
| `ACBD` | tidak | ya |

Contoh kedua: `"abac"` dan `"cab"`. LCS panjang 2 (`ab` atau `ac`). SCS panjang 5, misalnya `cabac`.

**Kode modular:**

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int lcs(const string& a, const string& b); // sama bagian LCS

int scsLength(const string& a, const string& b) {
    return (int)a.size() + (int)b.size() - lcs(a, b);
}

string scsString(const string& a, const string& b) {
    int n = (int)a.size(), m = (int)b.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    string res;
    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            res += a[i - 1];
            i--;
            j--;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            res += a[i - 1];
            i--;
        } else {
            res += b[j - 1];
            j--;
        }
    }
    while (i > 0) res += a[--i];
    while (j > 0) res += b[--j];
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    FASTIO;
    cout << scsLength("ABCD", "ACBD") << ' ' << scsString("ABCD", "ACBD") << '\n';
    cout << scsLength("abac", "cab") << ' ' << scsString("abac", "cab") << '\n';
    return 0;
}
```

Salin `lcs` ke file yang sama sebelum compile.

**Jebakan:** rumus `n+m-2*LCS` (itu **hapus** sampai sama, bukan SCS). Lupa sisa prefiks setelah `while`. Mencetak tanpa `reverse`.

**Kompleksitas:** `O(nm)` waktu dan memori.

---

## Turunan: hapus saja, substring, LPS

**Teori:** Banyak soal string 2D adalah LCS dengan **operator diganti**. Hapus saja sampai kedua string sama: tiap huruf di luar LCS dihapus, jadi `n+m-2*LCS`. Longest common **substring** mereset ke 0 saat huruf beda — jawaban adalah **maksimum seluruh tabel**, bukan `dp[n][m]`. Longest palindromic subsequence = `lcs(s, reverse(s))`.

**Kapan:** soal menyebut substring, supersequence, only deletions, palindromic subsequence. **Tidak:** edit dengan ganti (Levenshtein). Palindromic **substring** (kontigu) — expand pusat atau range boolean, bukan LCS.

**STATE substring:** `dp[i][j]` adalah panjang common substring yang **berakhir tepat** di `a[i-1]` dan `b[j-1]`.

**TRANSISI substring:** sama → `dp[i-1][j-1]+1`; beda → `0`.

**BASIS:** baris 0 dan kolom 0 = 0.

**Proses (table):** `a = "ABABC"`, `b = "BABCA"`.

|  | `""` | B | A | B | C | A |
|---|---|---|---|---|---|---|
| `""` | 0 | 0 | 0 | 0 | 0 | 0 |
| A | 0 | 0 | 1 | 0 | 0 | 1 |
| B | 0 | 1 | 0 | 2 | 0 | 0 |
| A | 0 | 0 | 2 | 0 | 0 | 1 |
| B | 0 | 1 | 0 | 3 | 0 | 0 |
| C | 0 | 0 | 0 | 0 | 4 | 0 |

Jawaban 4 (`BABC`), diambil dari `max` tabel, bukan `dp[5][5] = 0`.

`"aa"` vs `"a a"` (dengan spasi): LCS 2, substring 1.

LPS `"bbbab"`: LCS dengan `"babbb"` = 4 (`bbbb`).

**Kode modular:**

```cpp
int lcSubstring(const string& a, const string& b) {
    int n = (int)a.size(), m = (int)b.size(), best = 0;
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else dp[i][j] = 0;
            best = max(best, dp[i][j]);
        }
    return best;
}

int minDeletionsToEqual(const string& a, const string& b) {
    return (int)a.size() + (int)b.size() - 2 * lcs(a, b);
}

int longestPalindromicSubseq(string s) {
    string t = s;
    reverse(t.begin(), t.end());
    return lcs(s, t);
}
```

**Jebakan:** substring memakai `max(atas, kiri)`. Mengembalikan `dp[n][m]` untuk substring. LPS dikira harus kontigu.

**Kompleksitas:** semua `O(nm)`.

---

## Satu baris vs tabel penuh

**Teori:** Transisi LCS/edit hanya melihat baris sebelumnya dan sel kiri. Dua baris cukup untuk **nilai**. Satu baris juga bisa jika diagonal disimpan dulu (`prevDiag`). Rekonstruksi butuh tabel penuh atau pointer — bahas di [13-memori](13-memori.md) dan [12-rekonstruksi](12-rekonstruksi.md).

**Kapan:** MLE pada `n = m = 4000` (`16 juta int` ≈ 64 MB, sering masih lolos; `8000` sudah bahaya). **Tidak:** soal minta string hasil.

**STATE:** `cur[j]` = `dp[i][j]`, `prev[j]` = `dp[i-1][j]`.

**TRANSISI:** sama, ganti indeks baris.

**BASIS:** `prev[j] = 0` (LCS) atau `prev[j] = j` (edit).

**Proses (table):** LCS `"AB"` vs `"B"`.

| i (huruf) | prev | cur setelah j |
|---|---|---|
| awal | `[0, 0]` | — |
| A vs B (beda) | | `[0, 0]` |
| B vs B (sama) | | `[0, 1]` |

**Kode modular:**

```cpp
int lcsRolling(string a, string b) {
    if (a.size() < b.size()) swap(a, b);
    int n = (int)a.size(), m = (int)b.size();
    vector<int> prev(m + 1, 0), cur(m + 1, 0);
    for (int i = 1; i <= n; i++) {
        cur[0] = 0;
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) cur[j] = prev[j - 1] + 1;
            else cur[j] = max(prev[j], cur[j - 1]);
        }
        prev.swap(cur);
    }
    return prev[m];
}
```

**Jebakan:** `swap` lalu `cur` kotor tanpa reset `cur[0]`. Satu array menimpa `dp[j-1]` yang masih dibutuhkan sebagai diagonal.

**Kompleksitas:** waktu `O(nm)`, memori `O(min(n,m))`.

---

## Template gabungan

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int lcs(const string& a, const string& b);
int editDistance(const string& a, const string& b);
int scsLength(const string& a, const string& b);
string lcsString(const string& a, const string& b);
string scsString(const string& a, const string& b);
int lcSubstring(const string& a, const string& b);
int longestPalindromicSubseq(string s);

int main() {
    FASTIO;
    cout << lcs("ABCD", "ACBD") << '\n';
    cout << editDistance("kitten", "sitting") << '\n';
    cout << scsLength("ABCD", "ACBD") << '\n';
    return 0;
}
```

Peta rumus cepat:

| soal | rumus / operator |
|---|---|
| LCS panjang | sama: diagonal+1; beda: max(atas,kiri) |
| edit | 1+min(tiga) atau diagonal jika sama |
| SCS panjang | `n+m-LCS` |
| hapus sampai sama | `n+m-2*LCS` |
| LCSubstring | sama: diagonal+1; beda: 0; jawab `max` |
| LPS | `lcs(s, reverse(s))` |

---

## Peta jebakan

| gejala | penyebab | perbaikan |
|---|---|---|
| LCS off-by-one | `a[i]` vs `a[i-1]` | tabel n+1, banding `i-1` |
| LCS 4 untuk ABCD/ACBD | mengira BC dan CB kompatibel | isi sel `(3,3)` = 2 |
| edit terlalu kecil | basis 0 | `dp[i][0]=i`, `dp[0][j]=j` |
| edit = selisih panjang | hanya hitung sisip | tiga operasi |
| SCS = `n+m-2*LCS` | tertukar dengan hapus | `n+m-LCS` |
| substring 0 padahal ada "BABC" | ambil `dp[n][m]` | `max` seluruh tabel |
| rekonstruksi terbalik | lupa `reverse` | balik di akhir |
| rekonstruksi putus | `while (i && j)` pada edit/SCS | `\|\|` plus sisa prefiks |
| MLE 8000×8000 | tabel `int` penuh | rolling, hanya panjang |

---

## Tabel uji

| fungsi | input | keluaran |
|---|---|---|
| `lcs` | `ABCD` / `ACBD` | 3 |
| `lcsString` | sama, atas dulu | `ABD` |
| `lcs` | `AXYT` / `AYZX` | 2 |
| `editDistance` | `kitten` / `sitting` | 3 |
| `editDistance` | `cat` / `cut` | 1 |
| `editDistance` | `dog` / `cat` | 3 |
| `editDistance` | `""` / `hi` | 2 |
| `scsLength` | `ABCD` / `ACBD` | 5 |
| `scsString` | sama | `ABCBD` (kebijakan atas) |
| `scsLength` | `abac` / `cab` | 5 |
| `lcSubstring` | `ABABC` / `BABCA` | 4 |
| `minDeletionsToEqual` | `ABCD` / `ACBD` | 2 |
| `longestPalindromicSubseq` | `bbbab` | 4 |

Latihan setelah file ini: gambar tabel ABCD/ACBD dan kitten/sitting di kertas, baru buka soal CSES Edit Distance / AtCoder DP-F. Jangan menyalin `latihan/` ComprogLearning.

Lanjut ke [10-grid](10-grid.md) untuk DAG dua dimensi yang hurufnya diganti sel grid.
