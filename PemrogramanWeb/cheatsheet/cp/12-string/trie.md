# Trie dan binary trie

[← Z & Manacher](z-manacher.md) · [String](README.md) · [SA, Aho, SAM →](sa-aho-sam.md)

Day 217. Pohon awalan. Jalur dari akar = prefix. Versi biner: XOR maksimum.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

## Daftar isi

- [Trie huruf](#trie-huruf)
- [Sisip dan cari](#sisip-dan-cari)
- [Hitung prefix](#hitung-prefix)
- [Hapus](#hapus)
- [DP di trie](#dp-di-trie)
- [Binary trie](#binary-trie)
- [Max XOR pasangan](#max-xor-pasangan)
- [Max XOR subarray](#max-xor-subarray)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Trie huruf

**Teori:** tiap sisi satu huruf. Simpul menandai “kata berakhir” dan hitungan sisipan yang lewat. Insert/cari O(panjang).

Analogi: indeks kamus. `app`, `apple`, `ape` berbagi `ap`.

Memori: simpul ≤ 1 + total huruf. Array `next[26]` per simpul. Jangan alokasi 26 anak di daun imajiner n·L jika L besar tanpa hitung.

**Kapan:**

- Pakai: kamus, prefix matching, autocomplete, Aho (lanjutan).
- Jangan: n·26·L meledak. Alfabet besar: `map` atau 256.
- Jangan: XOR — pakai binary trie.

**Proses:** sisip `"ab"`, `"ac"`, `"b"`.

```
    *
   / \
  a   b (akhir)
 / \
b   c
(akhir) (akhir)

"a" ada sebagai prefix, bukan kata
"ab" kata
```

**Kode:** simpul.

```cpp
struct Trie {
    struct Node {
        int next[26];
        int akhir, hitung;
        Node() {
            memset(next, -1, sizeof next);
            akhir = hitung = 0;
        }
    };
    vector<Node> t;
    Trie() { t.push_back(Node()); }

    int buat() {
        t.push_back(Node());
        return (int)t.size() - 1;
    }
};
```

**Jebakan:** `ch-'a'` negatif jika huruf besar. Akar `hitung` tidak otomatis = jumlah kata.

**Kompleksitas:** O(total huruf) waktu dan memori.

## Sisip dan cari

**Teori:** jalan huruf demi huruf, buat simpul jika `-1`. Di setiap simpul (kecuali mungkin akar), `hitung++`. Di akhir, `akhir++`.

Cari kata: sampai ujung dan `akhir>0`. Cari prefix: sampai ujung saja.

**Kapan:** kamus dinamis.

**Proses:** sisip `"ab"` lalu `"abc"`.

```
a hitung=2, b hitung=2 akhir=1, c hitung=1 akhir=1
cari "ab" ya, "abc" ya, "a" tidak (akhir 0), prefix "a" hitung 2
```

**Kode:**

```cpp
    void sisip(const string& s) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) t[v].next[c] = buat();
            v = t[v].next[c];
            t[v].hitung++;
        }
        t[v].akhir++;
    }

    bool cariKata(const string& s) const {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (c < 0 || c >= 26 || t[v].next[c] == -1) return false;
            v = t[v].next[c];
        }
        return t[v].akhir > 0;
    }
```

**Jebakan:** increment `hitung` di akar untuk prefix kosong = jumlah kata — opsional, dokumentasikan. Sisip string kosong menaikkan `akhir` akar.

**Kompleksitas:** O(|s|).

## Hitung prefix

**Teori:** `hitung` di simpul = banyak kata yang melewati (bergantung kapan kamu ++). Di kode atas, `hitung` di simpul huruf terakhir prefix.

**Kapan:** “berapa kata berawalan P”.

**Proses:** kata `app, apple, ape, bat`. Prefix `ap` → 3.

**Kode:**

```cpp
    int hitungPrefix(const string& p) const {
        int v = 0;
        for (char ch : p) {
            int c = ch - 'a';
            if (c < 0 || c >= 26 || t[v].next[c] == -1) return 0;
            v = t[v].next[c];
        }
        return t[v].hitung;
    }

    int banyakKata() const {
        int s = 0;
        for (int c = 0; c < 26; c++)
            if (t[0].next[c] != -1) s += t[t[0].next[c]].hitung;
        s += t[0].akhir;                    // string kosong
        return s;
    }
```

Jika `hitung` juga di akar:

```cpp
    void sisipAkar(const string& s) {
        int v = 0;
        t[0].hitung++;
        for (char ch : s) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) t[v].next[c] = buat();
            v = t[v].next[c];
            t[v].hitung++;
        }
        t[v].akhir++;
    }
```

**Jebakan:** dua gaya `hitung` campur. Pilih satu.

**Kompleksitas:** O(|p|).

## Hapus

**Teori:** turunkan `hitung`/`akhir`. Sisi tidak wajib dihapus. Jangan hapus jika `akhir==0` sudah.

**Kapan:** kamus + hapus. XOR trie juga pakai `d=-1`.

**Proses:** hapus `"ab"` setelah dua sisipan `"ab"`: `akhir` 2→1, masih ada.

**Kode:**

```cpp
    bool hapus(const string& s) {
        if (!cariKata(s)) return false;
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            v = t[v].next[c];
            t[v].hitung--;
        }
        t[v].akhir--;
        return true;
    }
```

**Jebakan:** hapus yang tidak ada merusak `hitung` negatif. Cek dulu. Path harus ada.

**Kompleksitas:** O(|s|).

## DP di trie

**Teori:** Word Combinations: pecah teks jadi kata kamus. DP `ok[i]` = apakah `s[i..]` bisa. Dari i, jalan trie sambil maju j, jika `akhir` maka `ok[i] |= ok[j+1]`.

**Kapan:** kamus + satu teks, n ≤ 5000, total kata sedang.

**Proses:** teks `ababc`, kata `ab, abc, c`. `ok[5]=1`, dari 2 (`abc`? a dari 2 adalah a... ). Dari 0: `ab` → cek ok[2]; `abc` tidak. Dari 2: `c`? s[2]=a. Dari 3? ... gambar sendiri pada tes.

Contoh pendek: teks `abab`, kata `ab`. ok[4]=1, ok[2] dari `ab`, ok[0] dari `ab`.

**Kode:**

```cpp
const int MOD = 1000000007;

int pecahKata(const string& s, Trie& tr) {
    int n = (int)s.size();
    vector<int> dp(n + 1, 0);
    dp[n] = 1;
    for (int i = n - 1; i >= 0; i--) {
        int v = 0;
        for (int j = i; j < n; j++) {
            int c = s[j] - 'a';
            if (c < 0 || c >= 26 || tr.t[v].next[c] == -1) break;
            v = tr.t[v].next[c];
            if (tr.t[v].akhir) dp[i] = (dp[i] + dp[j + 1]) % MOD;
        }
    }
    return dp[0];
}
```

**Jebakan:** overflow `int` jumlah cara. Alfabet. TLE jika n=10^5 dan trie dalam tanpa pruning — biasanya n lebih kecil.

**Kompleksitas:** O(n · L) L kedalaman sampai cabang mati.

## Binary trie

**Teori:** masukkan angka 30–32 bit, **MSB dulu**. XOR terbesar dengan x: di tiap bit usahakan cabang **lawan** bit x jika ada. XOR terkecil: cabang **sama**.

**Kapan:** max XOR pair, max XOR subarray, k-th XOR. n=1e7 × 32 simpul: hitung memori dulu.

**Proses:** masukkan 5=`101`, 7=`111`. Query x=2=`010`.

```
bit2: x=0 lawan 1 ada → ambil 1
bit1: x=1 lawan 0, 5=101 punya 0 → ambil
bit0: x=0 lawan 1, 5 punya 1
XOR 5^2=7. 7^2=5, max=7
```

**Kode:**

```cpp
struct BinTrie {
    static const int B = 30;
    vector<array<int, 2>> next;
    vector<int> cnt;

    BinTrie() { buat(); }

    int buat() {
        next.push_back({-1, -1});
        cnt.push_back(0);
        return (int)next.size() - 1;
    }

    void sisip(int x, int d = 1) {
        int v = 0;
        cnt[v] += d;
        for (int b = B; b >= 0; b--) {
            int bit = (x >> b) & 1;
            if (next[v][bit] == -1) next[v][bit] = buat();
            v = next[v][bit];
            cnt[v] += d;
        }
    }
};
```

**Jebakan:** LSB dulu → salah total. Negatif: pakai unsigned / hanya ≥ 0. Query trie kosong.

**Kompleksitas:** O(B) per operasi, memori O(n B).

## Max XOR pasangan

**Teori:** sisip semua, untuk tiap x query `maxXor(x)`, jawaban max. Atau sisip on-line jika pasangan i<j.

`maxXor` mengembalikan **nilai XOR**, bukan pasangan y. y = ans ^ x.

**Kapan:** n ≤ 2·10^5, B=30.

**Proses:** `{1,2,3}` = 01,10,11. 1^2=3, 1^3=2, 2^3=1. Max 3.

**Kode:**

```cpp
    int maxXor(int x) const {
        if (cnt[0] == 0) return 0;
        int v = 0, ans = 0;
        for (int b = B; b >= 0; b--) {
            int bit = (x >> b) & 1;
            int want = bit ^ 1;
            if (next[v][want] != -1 && cnt[next[v][want]] > 0) {
                ans |= 1 << b;
                v = next[v][want];
            } else {
                v = next[v][bit];
            }
        }
        return ans;
    }

    int minXor(int x) const {
        if (cnt[0] == 0) return 0;
        int v = 0, ans = 0;
        for (int b = B; b >= 0; b--) {
            int bit = (x >> b) & 1;
            if (next[v][bit] != -1 && cnt[next[v][bit]] > 0) v = next[v][bit];
            else {
                ans |= 1 << b;
                v = next[v][bit ^ 1];
            }
        }
        return ans;
    }

int maxXorPair(const vector<int>& a) {
    BinTrie tr;
    int ans = 0;
    for (int x : a) {
        if (tr.cnt[0]) ans = max(ans, tr.maxXor(x));
        tr.sisip(x);
    }
    return ans;
}
```

**Jebakan:** query x terhadap dirinya jika sudah di-sisip: XOR 0, max tetap dari pasangan lain jika n≥2. Sisip dulu semua lalu query: termasuk x^x=0, max tetap OK.

**Kompleksitas:** O(n B).

## Max XOR subarray

**Teori:** prefix XOR `px`. Subarray i..j XOR = `px[j+1] ^ px[i]`. Max = untuk tiap px, max XOR dengan prefix sebelumnya. Sisip 0 di awal (subarray dari 0).

**Kapan:** satu array, XOR subarray max.

**Proses:** a=`[1,2,3]`. px: 0,1,3,0. 1^0=1, 3^0=3, 3^1=2, 0^1=1, 0^3=3. Max 3 (`[1,2]` atau `[2,3]`? 1^2=3, 2^3=1, 1^2^3=0). Ya 3.

**Kode:**

```cpp
int maxXorSubarray(const vector<int>& a) {
    BinTrie tr;
    tr.sisip(0);
    int px = 0, ans = 0;
    for (int x : a) {
        px ^= x;
        ans = max(ans, tr.maxXor(px));
        tr.sisip(px);
    }
    return ans;
}
```

**Jebakan:** lupa sisip 0. `ans` awal 0 salah jika semua XOR negatif — XOR tidak negatif.

**Kompleksitas:** O(n B).

## Uji naif

**Teori:** trie vs `vector<string>`. XOR vs O(n²).

**Kapan:** n ≤ 12 XOR, kamus kecil.

**Proses:** kata di atas, prefix. a=`{1,2,3}` max pair 3.

**Kode:**

```cpp
int maxPairNaif(const vector<int>& a) {
    int ans = 0;
    for (int i = 0; i < (int)a.size(); i++)
        for (int j = i + 1; j < (int)a.size(); j++) ans = max(ans, a[i] ^ a[j]);
    return ans;
}

int main() {
    FASTIO;
    Trie tr;
    tr.sisip("ab");
    tr.sisip("ac");
    tr.sisip("b");
    assert(tr.cariKata("ab"));
    assert(!tr.cariKata("a"));
    assert(tr.hitungPrefix("a") == 2);
    assert(tr.hitungPrefix("b") == 1);
    vector<int> a = {1, 2, 3};
    assert(maxXorPair(a) == maxPairNaif(a));
    assert(maxXorSubarray({1, 2, 3}) == 3);
    cout << "ok\n";
}
```

**Jebakan:** `hitungPrefix("a")` bergantung increment di simpul `a` — dua kata `ab,ac` = 2.

**Kompleksitas:** tes kecil.

## Ringkasan

1. Trie = pohon huruf, `akhir` dan `hitung`.
2. Kompres memori: simpul = total huruf.
3. DP pecah kata: jalan trie dari tiap i.
4. Binary trie MSB dulu. Lawan bit = XOR 1.
5. Subarray XOR = prefix XOR + trie.
6. Banyak pola + teks panjang: Aho, bukan trie naif per posisi tanpa fail.

Latihan Day 217. Jangan salin folder latihan.
