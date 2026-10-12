# Nim dan Sprague-Grundy

[← Teori permainan](README.md) · [Game DP](../09-dp/24-game.md) · [Indeks CP](../README.md)

Day 236. Permainan impartial: aturan sama untuk kedua pemain. Normal play: yang tidak bisa gerak **kalah**.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

Bukan game DP DAG umum saja — lihat juga file DP game. Di sini: XOR, mex, gabungan komponen.

## Daftar isi

- [Menang dan kalah](#menang-dan-kalah)
- [Nim klasik](#nim-klasik)
- [Langkah menuju XOR 0](#langkah-menuju-xor-0)
- [Misère Nim](#misère-nim)
- [Sprague-Grundy](#sprague-grundy)
- [Mex](#mex)
- [Subtraction game](#subtraction-game)
- [Gabungan komponen](#gabungan-komponen)
- [Game DP satu bit](#game-dp-satu-bit)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Menang dan kalah

**Teori:** posisi **kalah** (P-position) jika semua langkah ke posisi menang, atau tidak ada langkah. Posisi **menang** (N-position) jika ada langkah ke posisi kalah.

Normal play: terminal = kalah. Misère: yang mengambil terakhir kalah = terminal (tidak ada objek?) tergantung rumusan — baca soal.

**Kapan:** satu komponen, state kecil. Banyak komponen independen → Grundy + XOR.

**Proses:** n batu, ambil 1 atau 2, yang tidak bisa kalah.

```
n=0 kalah
n=1 ke 0 → menang
n=2 ke 0 → menang
n=3 ke 1 atau 2, keduanya menang → kalah
n=4 ke 3 → menang
pola: n%3==0 kalah
```

**Kode:**

```cpp
vector<char> menangBatu(int n) {
    vector<char> w(n + 1, 0);
    for (int i = 1; i <= n; i++)
        w[i] = (i >= 1 && !w[i - 1]) || (i >= 2 && !w[i - 2]);
    return w;
}
```

`w[0]=0`, `w[1]=1`, `w[2]=1`, `w[3]=0`.

**Jebakan:** mengisi tanpa urutan “s' lebih kecil”. State harus DAG menuju basis.

**Kompleksitas:** O(n · cabang).

## Nim klasik

**Teori:** beberapa tumpukan. Satu giliran: pilih **satu** tumpukan, buang minimal satu batu (boleh semua). Normal play.

Satu tumpukan n: 0 kalah, n≥1 menang. Beberapa tumpukan: **XOR** semua ukuran. XOR=0 kalah, ≠0 menang.

Kenapa XOR: tiap tumpukan permainan terpisah. Nimber tumpukan n adalah n. XOR = jumlah nimber.

**Kapan:**

- Pakai: tumpukan independen, “kurangi dari satu tumpukan”.
- Jangan: satu papan aneh tanpa memecah komponen.
- Jangan: satu giliran boleh sentuh dua tumpukan — XOR rusak.

**Proses:** tumpukan 3, 4, 5.

```
3^4^5 = 011 ^ 100 ^ 101 = 010 = 2 ≠ 0  first win
```

**Kode:**

```cpp
int xorSemua(const vector<int>& a) {
    int x = 0;
    for (int v : a) x ^= v;
    return x;
}

bool nimMenang(const vector<int>& a) { return xorSemua(a) != 0; }
```

**Jebakan:** meng-XOR jumlah total, bukan tiap tumpukan. Tumpukan 0 tetap boleh ada, 0 tidak mengubah XOR.

**Kompleksitas:** O(n).

## Langkah menuju XOR 0

**Teori:** jika `x = XOR semua ≠ 0`, ada tumpukan i dengan `y = a[i] ^ x` dan `y < a[i]`. Ganti a[i] jadi y (buang `a[i]-y`).

Kenapa `y = a[i]^x < a[i]`: bit tertinggi x menyala di suatu a[i], mengurangi bit itu.

**Kapan:** soal konstruktif “cetak langkah”.

**Proses:** 3,4,5, x=2.

```
i=0 a=3: y=3^2=1 < 3  OK  sisa 1,4,5
1^4^5 = 1^4^5 = 0
i=1 a=4: y=4^2=6 >4  ilegal
i=2 a=5: y=5^2=7 >5  ilegal
```

**Kode:**

```cpp
pair<int, int> langkahNim(const vector<int>& a) { // {indeks, sisa}
    int x = xorSemua(a);
    if (x == 0) return {-1, -1};
    for (int i = 0; i < (int)a.size(); i++) {
        int y = a[i] ^ x;
        if (y < a[i]) return {i, y};
    }
    return {-1, -1};
}
```

**Jebakan:** `a[i] ^= x` tanpa `y < a[i]`. Komentar “ingin a[i] jadi y” — rumus `a[i]^x` benar.

**Kompleksitas:** O(n).

## Misère Nim

**Teori:** yang mengambil **terakhir kalah**. Jika ada tumpukan ≥ 2, strategi hampir sama dengan normal (XOR). Jika **semua** tumpukan ≤ 1, kebalikan: XOR biasa salah.

Lebih tepat: jika ada ≥1 tumpukan ≥2, main seperti normal kecuali saat langkah akan meninggalkan semua ≤1 — hati-hati. Aturan praktis yang sering diajarkan:

```
jika max > 1: menang iff XOR ≠ 0     (sama normal)
jika max ≤ 1: menang iff XOR == 0    (kebalikan, ekuivalen jumlah tumpukan genap? 
  semua 0/1, XOR = jumlah mod 2. Normal: ganjil menang. Misère: ganjil kalah
  karena mengambil terakhir kalah. Jadi menang iff jumlah genap, iff XOR==0)
```

**Kapan:** soal “last move loses”. Baca dua kali.

**Proses:** (1,1): normal XOR 0 kalah; misère: ambil satu, lawan terpaksa ambil terakhir, kamu menang. XOR=0 dan max=1 → menang misère. Cocok kebalikan.

(1): max=1, XOR=1, misère kalah (hanya ambil terakhir). Ya.

(2): max>1, XOR=2≠0, misère: jangan ambil 2 (kalah), ambil 1 sisa 1, lawan kalah. Menang. Cocok normal.

**Kode:**

```cpp
bool misereNimMenang(const vector<int>& a) {
    int x = 0, mx = 0;
    for (int v : a) {
        x ^= v;
        mx = max(mx, v);
    }
    if (mx <= 1) return x == 0;
    return x != 0;
}
```

**Jebakan:** memakai rumus ini untuk misère **bukan** Nim (aturan ambil aneh). Hanya Nim klasik.

**Kompleksitas:** O(n).

## Sprague-Grundy

**Teori:** setiap posisi impartial punya **Grundy / nimber**:

```
g(pos) = mex { g(pos') | pos' langkah sah }
```

- `g = 0` → kalah jika giliranmu dan lawan sempurna.
- Gabungan **disjoint** (gerak di tepat satu komponen): `g_total = g1 XOR g2 XOR ...`.

Mex = angka non-negatif terkecil yang tidak muncul. Analogi: tiap komponen diganti tumpukan batu imajiner seukuran g.

**Kapan:**

- Pakai: beberapa permainan kecil, subtraction, Kayles, “ambil 1..k dari satu baris”.
- Jangan: partizan (putih/hitam beda langkah).
- Jangan: satu giliran mengubah **dua** komponen — pecah ulang state.

**Proses:** subtraction {1,3}. `g(0)=mex{}=0`.

```
n=1 → ke 0 (g=0)           mex{0}=1
n=2 → ke 1 (g=1)           mex{1}=0
n=3 → ke 2 atau 0          mex{0,0}=1
n=4 → ke 3 atau 1          mex{1,1}=0
n=5 → ke 4,2  g=0,0        mex=1
```

Dua tumpukan 4 dan 1: 0 XOR 1 = 1 ≠ 0, first win.

**Kode:** lihat mex + `grundySub` di bawah.

**Jebakan:** meng-XOR ukuran tumpukan padahal aturan bukan Nim.

**Kompleksitas:** O(state × cabang × biaya mex).

## Mex

**Teori:** himpunan {0,1,3} → mex 2. Kosong → 0. `{0,1,2}` → 3.

**Kapan:** setiap g(pos).

**Proses:** `{1,1,2}` → 0 (0 tidak muncul).

**Kode:**

```cpp
int mex(vector<int> s) {
    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());
    int m = 0;
    for (int x : s) {
        if (x == m) m++;
        else if (x > m) break;
    }
    return m;
}

int mexBool(const vector<char>& ada) {
    for (int i = 0; i < (int)ada.size(); i++)
        if (!ada[i]) return i;
    return (int)ada.size();
}
```

Array boolean lebih cepat jika g kecil.

**Jebakan:** mex kosong = 0, bukan −1. Nilai negatif di himpunan diabaikan.

**Kompleksitas:** sort O(k log k), boolean O(batas).

## Subtraction game

**Teori:** dari n, kurangi salah satu `steps`. Beberapa tumpukan = XOR g[n].

**Kapan:** “ambil 1, 3, atau 4”.

**Proses:** steps {1,3} di atas. Dua tumpukan 4,1: g=0 dan 1, XOR 1, menang. Gerak di tumpukan 1 ke 0.

**Kode:**

```cpp
vector<int> grundySub(int n, const vector<int>& steps) {
    vector<int> g(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        vector<char> ada(steps.size() + 2, 0);
        for (int s : steps)
            if (i >= s) {
                int v = g[i - s];
                if (v < (int)ada.size()) ada[v] = 1;
            }
        g[i] = mexBool(ada);
    }
    return g;
}

bool menangSub(const vector<int>& tumpukan, const vector<int>& steps) {
    int mx = 0;
    for (int x : tumpukan) mx = max(mx, x);
    auto g = grundySub(mx, steps);
    int x = 0;
    for (int t : tumpukan) x ^= g[t];
    return x != 0;
}
```

**Jebakan:** `ada` terlalu pendek jika g besar. `steps` 0 loop. n=0.

**Kompleksitas:** O(n · |steps|).

## Gabungan komponen

**Teori:** papan = beberapa baris/graf independen. Hitung g tiap komponen, XOR. Contoh: Nimbers pada DAG, “ambil objek di simpul + hapus outgoing”: `g[v]` sesuai aturan, state harus DAG.

Kayles (ide): bowling pins, ambil 1 atau 2 berdempet, putus rantai jadi dua komponen. `g[n] = mex { g[i] XOR g[n-1-i], g[i] XOR g[n-2-i] }`.

**Kapan:** rumus pecah rantai.

**Proses:** dua permainan subtraction terpisah = dua tumpukan.

**Kode:**

```cpp
vector<int> grundyKayles(int n) {
    vector<int> g(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        vector<int> nxt;
        for (int j = 0; j < i; j++) {       // hapus pin j (0-based)
            int L = j, R = i - j - 1;
            nxt.push_back(g[L] ^ g[R]);
        }
        for (int j = 0; j + 1 < i; j++) {   // hapus dua pin j,j+1
            int L = j, R = i - j - 2;
            nxt.push_back(g[L] ^ g[R]);
        }
        g[i] = mex(nxt);
    }
    return g;
}
```

**Jebakan:** indeks pecah rantai off-by-one. Gerak yang menyentuh dua komponen sekaligus di soal lain — jangan XOR.

**Kompleksitas:** O(n²) untuk Kayles naif.

## Game DP satu bit

**Teori:** satu komponen, hanya peduli 0 vs bukan: `win[s] = ada langkah ke !win[s']`. Grundy dikompres 1 bit.

**Kapan:** satu papan, tidak gabung.

**Proses:** sama batu 1–2.

**Kode:** `menangBatu` di atas.

Graf DAG:

```cpp
char winMemo(int s, vector<int>& memo, const vector<vector<int>>& nxt) {
    if (memo[s] != -1) return (char)memo[s];
    char w = 0;
    for (int t : nxt[s])
        if (!winMemo(t, memo, nxt)) w = 1;
    return memo[s] = w;
}
```

**Jebakan:** siklus gerak tanpa memo hati-hati (bukan DAG). Draw mungkin.

**Kompleksitas:** O(state+edge).

## Uji naif

**Teori:** Nim vs minimax kecil. Grundy vs win: g==0 iff kalah.

**Kapan:** n tumpukan kecil, ukuran ≤ 8.

**Proses:** (3,4,5) minimax first win. (0,0) kalah.

**Kode:**

```cpp
bool nimMinimax(vector<int> a) {
    function<bool()> win = [&]() {
        bool ada = false;
        for (int i = 0; i < (int)a.size(); i++)
            for (int k = 1; k <= a[i]; k++) {
                a[i] -= k;
                bool lawan = win();
                a[i] += k;
                ada = true;
                if (!lawan) return true;
            }
        return false;                       // tidak ada gerak
    };
    return win();
}

int main() {
    FASTIO;
    vector<int> a = {3, 4, 5};
    assert(nimMenang(a) == nimMinimax(a));
    auto g = grundySub(10, {1, 3});
    assert(g[0] == 0);
    assert(g[1] == 1);
    assert(misereNimMenang({1, 1}) == true);
    assert(misereNimMenang({1}) == false);
    cout << "ok\n";
}
```

Minimax eksponensial: hanya ukuran kecil.

**Jebakan:** minimax mengubah `a` tanpa restore jika `return` di tengah — kode di atas restore.

**Kompleksitas:** tes kecil.

## Ringkasan

1. Normal play: tidak bisa gerak kalah. Menang = ada langkah ke kalah.
2. Nim = XOR ukuran. 0 kalah.
3. Langkah: `y = a[i]^x` jika `y < a[i]`.
4. Misère Nim: semua ≤1 kebalikan; ada ≥2 seperti normal.
5. Grundy = mex langkah. Gabungan disjoint = XOR.
6. Jangan XOR jika satu gerak menyentuh dua komponen.

Latihan Day 236. Jangan salin `exercise_*.cpp`.
