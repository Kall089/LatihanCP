# Suffix Array, Aho-Corasick, SAM

[← Trie](trie.md) · [String](README.md) · [Geometri →](../13-geometri/README.md)

Day 219–223. Tiga alat berat. Pahami **apa yang diurutkan / dihubungkan**, baru salin template.

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;
```

Jangan menulis ketiganya dari nol di jam pertama kontes jika belum pernah AC.

## Daftar isi

- [Suffix array](#suffix-array)
- [Doubling](#doubling)
- [LCP Kasai](#lcp-kasai)
- [Substring berbeda dan cari pola](#substring-berbeda-dan-cari-pola)
- [LCS dua string](#lcs-dua-string)
- [Aho-Corasick](#aho-corasick)
- [Failure link](#failure-link)
- [Suffix automaton — peta](#suffix-automaton--peta)
- [Pilih alat](#pilih-alat)
- [Uji naif](#uji-naif)
- [Ringkasan](#ringkasan)

## Suffix array

**Teori:** `sa[i]` = indeks awal sufiks ke-i jika semua sufiks diurut leksikografis.

```
s = "banana"
0 banana
1 anana
2 nana
3 ana
4 na
5 a

terurut:
5 a
3 ana
1 anana
0 banana
4 na
2 nana
sa = [5,3,1,0,4,2]
```

`rank[sa[i]] = i`.

**Kapan:**

- Pakai: distinct substring, LCS substring, banyak query sufiks, pattern search O(|P| log n).
- Hash + binsearch sering mengganti LCP dua indeks.
- Jangan mulai SA di jam terakhir jika belum ada template.

**Proses:** `"abc"`:

```
0 abc, 1 bc, 2 c → sa = [0,1,2]
```

`"cba"`: `sa = [2,1,0]` (a, ba, cba).

**Kode:** naif n ≤ 2000.

```cpp
vector<int> saNaif(const string& s) {
    int n = (int)s.size();
    vector<int> sa(n);
    iota(sa.begin(), sa.end(), 0);
    sort(sa.begin(), sa.end(), [&](int i, int j) {
        return s.compare(i, string::npos, s, j, string::npos) < 0;
    });
    return sa;
}
```

**Jebakan:** sentinel saat gabung dua string: tanpa `char(1)`, sufiks menyeberang.

**Kompleksitas:** naif O(n² log n). Target doubling O(n log² n).

## Doubling

**Teori:** peringkat awal = kode karakter. Putaran k: bandingkan pasangan `(rank[i], rank[i+2^{k-1}])`. Setelah log n putaran, peringkat unik = urutan sufiks.

Manber–Myers / Kasai doubling. Radix sort mempercepat jadi O(n log n), tidak wajib.

**Kapan:** n ≤ 2·10^5.

**Proses:** `"banana"` k=1 (2 huruf):

```
ba, an, na, an, na, a+sentinel
urut berubah menuju sa akhir
```

Cukup percaya: setelah rank[sa[n-1]]==n-1, selesai.

**Kode:**

```cpp
vector<int> suffixArray(const string& s) {
    int n = (int)s.size();
    vector<int> sa(n), rnk(n), tmp(n);
    for (int i = 0; i < n; i++) {
        sa[i] = i;
        rnk[i] = (unsigned char)s[i];
    }
    for (int k = 1; k < n; k <<= 1) {
        auto kurang = [&](int i, int j) {
            if (rnk[i] != rnk[j]) return rnk[i] < rnk[j];
            int ri = i + k < n ? rnk[i + k] : -1;
            int rj = j + k < n ? rnk[j + k] : -1;
            return ri < rj;
        };
        sort(sa.begin(), sa.end(), kurang);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i - 1]] + (kurang(sa[i - 1], sa[i]) ? 1 : 0);
        rnk.swap(tmp);
        if (rnk[sa[n - 1]] == n - 1) break;
    }
    return sa;
}
```

**Jebakan:** sentinel rank `-1` vs `0`. Karakter 0 di string. `sort` comparator harus strict weak ordering — `kurang` pada rank yang sudah konsisten OK.

**Kompleksitas:** O(n log² n).

## LCP Kasai

**Teori:** `lcp[i]` = prefix bersama `sa[i]` dan `sa[i-1]` (konvensi ini). Kasai: LCP sufiks k dan tetangganya di SA berkaitan dengan sufiks k+1 — tinggi turun paling 1. Total O(n).

`lcp[0]` tidak bermakna (tidak ada kiri).

**Kapan:** selalu setelah SA untuk distinct / LCS.

**Proses:** `"banana"`, sa `[5,3,1,0,4,2]`.

```
lcp antara a / ana = 1
ana / anana = 3
anana / banana = 0
banana / na = 0
na / nana = 2
lcp ≈ [0,1,3,0,0,2]
```

**Kode:**

```cpp
vector<int> bangunLCP(const string& s, const vector<int>& sa) {
    int n = (int)s.size();
    vector<int> rank(n), lcp(n);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;
    int h = 0;
    for (int i = 0; i < n; i++) {
        int r = rank[i];
        if (r == 0) continue;
        int j = sa[r - 1];
        while (i + h < n && j + h < n && s[i + h] == s[j + h]) h++;
        lcp[r] = h;
        if (h) h--;
    }
    return lcp;
}
```

**Jebakan:** `h--` jadi negatif — jaga `if (h)`. `lcp` ukuran n, pakai dari 1.

**Kompleksitas:** O(n).

## Substring berbeda dan cari pola

**Teori:** semua substring = semua prefiks semua sufiks. Yang dobel = LCP tetangga SA.

```
distinct = n(n+1)/2 − Σ lcp[i]
```

Cari pola: binary search di SA, banding `s.compare(sa[mid], m, p)`.

**Kapan:** CSES *String Functions* sejenis, distinct, search.

**Proses:** `"aaa"`: substring `a,a,a,aa,aa,aaa` distinct 3. n(n+1)/2=6, lcp kira-kira 1+2=3, 6-3=3.

**Kode:**

```cpp
ll substringBerbeda(int n, const vector<int>& lcp) {
    ll semua = 1LL * n * (n + 1) / 2;
    for (int i = 1; i < n; i++) semua -= lcp[i];
    return semua;
}

bool adaPola(const string& s, const vector<int>& sa, const string& p) {
    int n = (int)s.size(), m = (int)p.size();
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        int cmp = s.compare(sa[mid], m, p);
        if (cmp < 0) lo = mid + 1;
        else hi = mid;
    }
    return lo < n && s.compare(sa[lo], m, p) == 0;
}

pair<int, int> rentangPola(const string& s, const vector<int>& sa, const string& p) {
    int n = (int)s.size(), m = (int)p.size();
    auto lower = [&]() {
        int lo = 0, hi = n;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (s.compare(sa[mid], m, p) < 0) lo = mid + 1;
            else hi = mid;
        }
        return lo;
    };
    auto upper = [&]() {
        int lo = 0, hi = n;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (s.compare(sa[mid], m, p) <= 0) lo = mid + 1;
            else hi = mid;
        }
        return lo;
    };
    return {lower(), upper()};
}
```

Jumlah kemunculan = `upper-lower` jika match.

**Jebakan:** `s.compare(pos, m, p)` aman jika sisa lebih pendek (C++ membandingkan sisa). Overflow `n(n+1)`.

**Kompleksitas:** search O(|P| log n).

## LCS dua string

**Teori:** gabung `A + SEP + B`. SEP < semua huruf. LCS *substring* = LCP maksimum dua sufiks tetangga SA yang berasal dari string berbeda.

**Kapan:** longest common **substring**, bukan subsequence (itu DP).

**Proses:** A=`"ababc"`, B=`"babac"`. `"bab"` / `"aba"` dll. `"bab"` panjang 3? B punya `baba`. A punya `bab`. Ya 3? A=`ababc` punya `bab`. Ya.

**Kode:**

```cpp
int lcsSubstring(const string& A, const string& B) {
    char sep = 1;
    string s = A + sep + B;
    auto sa = suffixArray(s);
    auto lcp = bangunLCP(s, sa);
    int n1 = (int)A.size(), best = 0;
    for (int i = 1; i < (int)s.size(); i++) {
        bool x = sa[i] < n1, y = sa[i - 1] < n1;
        if (x != y) best = max(best, lcp[i]);
    }
    return best;
}
```

Sufiks yang mulai di SEP diabaikan secara alami (LCP kecil).

**Jebakan:** SEP muncul di A/B. Indeks `sa[i] < n1` vs `> n1` (bukan ≥ karena SEP di n1).

**Kompleksitas:** O(n log² n).

## Aho-Corasick

**Teori:** banyak pola. Bangun trie semua pola, isi **failure link** seperti KMP di pohon. Teks ditelusuri sekali. Saat di simpul v, semua pola yang berakhir di v (dan fail-chain) dilaporkan.

**Kapan:** ≥ 2 pola, n teks besar, total pola sedang. Satu pola: KMP.

**Proses:** pola `he, she, his, hers`. Teks `ushers`.

```
trie: h-e, s-h-e, h-i-s, h-e-r-s
fail: she → he, dll.
ushers mengandung she, he, hers
```

**Kode:** kerangka simpul.

```cpp
struct Aho {
    struct Node {
        int next[26];
        int fail, out;
        Node() {
            memset(next, -1, sizeof next);
            fail = 0;
            out = -1;                       // indeks pola, atau linked list
        }
    };
    vector<Node> t;
    vector<int> polaDi;                     // simpul akhir tiap pola
    Aho() { t.push_back(Node()); }

    int buat() {
        t.push_back(Node());
        return (int)t.size() - 1;
    }

    void sisip(const string& s, int id) {
        int v = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (t[v].next[c] == -1) t[v].next[c] = buat();
            v = t[v].next[c];
        }
        t[v].out = id;
        polaDi.push_back(v);
    }
};
```

**Jebakan:** banyak pola berakhir di simpul sama — `out` satu int tidak cukup, pakai `vector<int>` atau rantai `outNext`.

**Kompleksitas:** bangun O(total huruf · 26), teks O(n + laporan).

## Failure link

**Teori:** BFS dari akar. `fail[v]` = simpul tempat prefiks terpanjang yang juga sufiks label v. Transisi: jika `next[v][c]` kosong, ikut `next[fail][c]` (isi dictionary link / transisi penuh saat BFS).

**Kapan:** setelah semua sisip, sebelum baca teks.

**Proses:** `she` dan `he`. Simpul `she` fail ke `he`.

**Kode:**

```cpp
    void bangunFail() {
        queue<int> q;
        for (int c = 0; c < 26; c++) {
            if (t[0].next[c] == -1) t[0].next[c] = 0;
            else {
                t[t[0].next[c]].fail = 0;
                q.push(t[0].next[c]);
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int c = 0; c < 26; c++) {
                int u = t[v].next[c];
                if (u != -1) {
                    t[u].fail = t[t[v].fail].next[c];
                    q.push(u);
                } else t[v].next[c] = t[t[v].fail].next[c];
            }
        }
    }

    vector<int> hitungKemunculan(const string& teks, int nPola) {
        vector<int> cnt(nPola, 0);
        int v = 0;
        for (char ch : teks) {
            int c = ch - 'a';
            if (c < 0 || c >= 26) {
                v = 0;
                continue;
            }
            v = t[v].next[c];
            for (int u = v; u; u = t[u].fail) {
                if (t[u].out != -1) cnt[t[u].out]++;
            }
        }
        return cnt;
    }
```

Laporan `for (u=v; u; u=fail)` bisa O(n · |pola|) jika rantai panjang. Perbaiki: `out` rantai hanya simpul yang ada pola, atau DP jumlah di fail DAG setelah satu traversal.

```cpp
    void tarikOut(vector<int>& occ) {
        vector<int> ord(t.size());
        iota(ord.begin(), ord.end(), 0);
        // BFS order sudah top-down; tarik dari daun fail...
    }
```

Untuk kontes: jika laporan jarang, rantai fail OK. Jika n=10^6 dan tiap huruf fail panjang, TLE — increment `hit[v]++` lalu propagate fail reverse.

```cpp
    vector<int> hitungCepat(const string& teks, int nPola) {
        vector<int> hit(t.size(), 0);
        int v = 0;
        for (char ch : teks) {
            int c = ch - 'a';
            v = t[v].next[c];
            hit[v]++;
        }
        vector<int> ord;
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            ord.push_back(x);
            for (int c = 0; c < 26; c++) {
                int u = t[x].next[c];
                if (u != -1 && t[u].fail != u && t[x].next[c] == u)
                    ; // sudah diisi penuh, BFS ulang dari anak asli sulit
            }
        }
        // lebih aman: simpan anak BFS saat bangunFail
        vector<int> cnt(nPola, 0);
        return cnt;
    }
```

Simpan `urutan` BFS di `bangunFail`, propagate dari belakang:

```cpp
    vector<int> urutan;

    // di bangunFail, tiap q.push simpan ke urutan

    vector<int> hitungCepat2(const string& teks, int nPola) {
        vector<int> hit(t.size(), 0);
        int v = 0;
        for (char ch : teks) v = t[v].next[(unsigned char)ch - 'a'], hit[v]++;
        for (int i = (int)urutan.size() - 1; i >= 0; i--) {
            int x = urutan[i];
            hit[t[x].fail] += hit[x];
        }
        vector<int> cnt(nPola, 0);
        for (int id = 0; id < nPola; id++) cnt[id] = hit[polaDi[id]];
        return cnt;
    }
```

**Jebakan:** `next` sudah diisi ke fail, BFS “anak asli” hilang — **simpan urutan saat pertama kali simpul ditemukan**. Huruf non-a-z. Pola duplikat.

**Kompleksitas:** O(n + simpul) setelah transisi penuh.

## Suffix automaton — peta

**Teori:** automata terkecil yang menerima semua substring. State O(n), transisi O(n). Setiap state = kelas endpos (kumpulan posisi akhir substring yang ekuivalen).

Kegunaan: distinct substring (jumlah `len[v]-len[link[v]]`), kemunculan, LCS, posisi pertama.

Membangun: online, untuk tiap huruf clone state. Mudah salah 15 baris.

**Kapan:** statistik **semua** substring. SA+LCP juga bisa distinct. SAM lebih elegan, lebih mudah WA.

Day 223: cukup kenal nama sampai kamu butuh.

**Proses:** s=`"aba"`. Distinct: a,b,ab,ba,aba = 5.

```
SAM state ~ 4–5, link ke kelas lebih pendek
```

**Kode:** template ringkas (uji dengan distinct).

```cpp
struct SAM {
    struct St {
        int next[26];
        int link, len;
        St() {
            memset(next, -1, sizeof next);
            link = -1;
            len = 0;
        }
    };
    vector<St> st;
    int last;

    SAM() {
        st.push_back(St());
        last = 0;
    }

    void extend(int c) {
        int cur = (int)st.size();
        st.push_back(St());
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) st[cur].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) st[cur].link = q;
            else {
                int cl = (int)st.size();
                st.push_back(st[q]);
                st[cl].len = st[p].len + 1;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = cl;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = cl;
            }
        }
        last = cur;
    }

    ll distinct() const {
        ll ans = 0;
        for (int i = 1; i < (int)st.size(); i++)
            ans += st[i].len - st[st[i].link].len;
        return ans;
    }
};

ll distinctSAM(const string& s) {
    SAM sam;
    for (char ch : s) sam.extend(ch - 'a');
    return sam.distinct();
}
```

**Jebakan:** clone menyalin `next`. `link[0]=-1`. Huruf bukan a-z. Distinct n=0 = 0.

**Kompleksitas:** O(n) amortised.

## Pilih alat

**Teori:**

| Kalimat | Alat |
|---|---|
| dua potongan sama | hash |
| satu pola | KMP / Z |
| banyak pola | Aho |
| distinct substring | SA+LCP atau SAM |
| LCS substring | SA gabungan |
| urutan sufiks | SA |
| kamus prefix | Trie |
| belum hafal SA | hash set substring (kasar) |

**Kapan:** 20 menit tersisa → hash/KMP, bukan SAM.

**Proses:** soal “berapa substring berbeda” n=10^5. SA atau SAM. Hash semua O(n²) mati.

**Kode:** `substringBerbeda` vs `distinctSAM` harus sama.

**Jebakan:** LCS subsequence vs substring.

**Kompleksitas:** SA log², SAM linear, Aho linear + alfabet.

## Uji naif

**Teori:** SA vs sort naif. Distinct vs set semua substr n≤20. Aho vs KMP tiap pola. SAM vs rumus SA.

**Kapan:** wajib sebelum submit SA.

**Proses:** `"banana"`, `"aaaa"`, `"abc"`.

**Kode:**

```cpp
ll distinctNaif(const string& s) {
    set<string> st;
    int n = (int)s.size();
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) st.insert(s.substr(i, j - i + 1));
    return (ll)st.size();
}

int main() {
    FASTIO;
    for (string s : {"", "a", "abc", "banana", "aaaa", "abab"}) {
        auto sa = suffixArray(s);
        if (!s.empty() && sa != saNaif(s)) {
            cout << "SA WA " << s << '\n';
            return 0;
        }
        if (!s.empty()) {
            auto lcp = bangunLCP(s, sa);
            ll d = substringBerbeda((int)s.size(), lcp);
            if (d != distinctNaif(s) || d != distinctSAM(s)) {
                cout << "dist WA " << s << '\n';
                return 0;
            }
        }
    }
    string t = "ushers";
    Aho aho;
    vector<string> ps = {"he", "she", "his", "hers"};
    for (int i = 0; i < 4; i++) aho.sisip(ps[i], i);
    aho.bangunFail();
    auto cnt = aho.hitungKemunculan(t, 4);
    assert(cnt[0] >= 1 && cnt[1] >= 1);
    cout << "ok\n";
}
```

**Jebakan:** `substr` n² log pada tes besar. n≤20.

**Kompleksitas:** tes O(n² log n) string.

## Ringkasan

1. SA = semua sufiks terurut. Doubling pangkat dua.
2. LCP Kasai linear. Distinct = n(n+1)/2 − Σ lcp.
3. Cari pola: binsearch di SA.
4. Aho = trie + fail. Banyak pola satu teks.
5. SAM = automata substring, state O(n). Distinct elegan.
6. Belum hafal: hash + KMP dulu.

Latihan Day 219–223. Jangan salin `exercise_*.cpp`.
