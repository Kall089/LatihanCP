# 📋 PROMPT TEMPLATE — Pembelajaran Competitive Programming dengan C++ (308 Hari)

## 🎯 Cara Menggunakan Template Ini:

1. Copy prompt di bawah
2. Ganti `[DAY_NUMBER]` dengan nomor hari (contoh: 1, 2, 3, dst.)
3. Paste ke chat AI (Cascade, ChatGPT, Claude, dll.)
4. AI akan otomatis membuat struktur lengkap sesuai roadmap CP 308 hari

---

## 📝 PROMPT TEMPLATE LENGKAP (Copy Paste Ini):

```
Buatkan materi pembelajaran Competitive Programming lengkap untuk DAY [DAY_NUMBER] sesuai roadmap 308 hari dengan C++.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
⚠️ CRITICAL CHECKLIST (BEFORE YOU START):
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

1. ✅ TEORI (teori/Day_XX_Teori_Lengkap.md):
   - Penjelasan konsep MENDALAM dalam Bahasa Indonesia
   - Setiap section punya: penjelasan → intuisi → pseudocode → C++ implementation
   - Visualisasi ASCII art / diagram untuk struktur data & alur algoritma
   - Analisis kompleksitas (Time & Space) WAJIB untuk setiap algoritma
   - Code C++ yang COMPILABLE (g++ -std=c++17 -O2)
   - Contoh trace/simulasi step-by-step untuk setiap algoritma

2. ✅ EXERCISE FILES (latihan/exercise_X.cpp):
   - Setiap exercise dalam file .cpp TERPISAH
   - Punya problem statement lengkap di komentar atas
   - Input/Output format yang jelas
   - Sample test cases minimal 2-3 buah
   - // TODO: komentar yang jelas di mana harus coding
   - Constraint yang jelas (N ≤ ?, Time Limit)

3. ✅ SOLUTION FILES (solusi/solution_X.cpp):
   - Implementasi LENGKAP & OPTIMAL (NO TODO di solution)
   - Penjelasan approach di komentar atas
   - Analisis kompleksitas di komentar
   - Bisa langsung compile & run
   - Edge cases di-handle

4. ✅ QUALITY:
   - C++17 compatible (g++ -std=c++17 -O2 -Wall)
   - Fast I/O: ios_base::sync_with_stdio(false); cin.tie(NULL);
   - Gunakan #include <bits/stdc++.h> untuk convenience (atau individual headers)
   - Naming convention: snake_case untuk variabel, camelCase untuk fungsi
   - Penjelasan dalam Bahasa Indonesia
   - Setiap solusi harus AC-ready (bisa langsung submit ke online judge)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

STRUKTUR WAJIB:

1. FOLDER STRUCTURE:
CP/Day-[DAY_NUMBER] ([TOPIC_NAME])/
├── teori/
│   └── Day_[DAY_NUMBER]_Teori_Lengkap.md   (teori + kode + diagram + analisis)
├── latihan/
│   ├── exercise_1.cpp  (5–8 exercise files dengan TODO)
│   ├── exercise_2.cpp
│   ├── ... (hingga exercise_5+.cpp)
├── solusi/
│   ├── solution_1.cpp  (solusi lengkap + penjelasan)
│   ├── solution_2.cpp
│   └── ... (satu per exercise)
├── tugas/
│   ├── tugas_01.cpp  (15 soal tugas — TANPA solusi)
│   ├── tugas_02.cpp
│   ├── ... (hingga tugas_15.cpp)
│   └── FORMAT: problem statement + sample I/O + constraints + TODO
├── template/           (template code yang sering dipakai)
│   └── template.cpp   (starter template untuk topik hari ini)
└── README.md           (panduan belajar hari ini + link online judge)

2. FORMAT TEORI MARKDOWN (WAJIB):

Setiap teori markdown harus punya struktur seperti ini:

# 📊 Day X: [Judul Topik]

**Hari**: Day X dari 308 Hari Competitive Programming
**Topik**: [Topik Utama]
**Prerequisites**: [Apa yang perlu diketahui]
**Difficulty**: ⭐/⭐⭐/⭐⭐⭐
**Learning Objectives**:
- Objective 1
- Objective 2

---

## 🔍 1. Konsep & Intuisi
Penjelasan konsep dalam Bahasa Indonesia yang DETAIL:
- Apa itu (definisi)
- Mengapa penting di CP
- Kapan digunakan (pattern recognition)
- Intuisi visual/analogi kehidupan nyata
- Diagram ASCII atau ilustrasi

## 🧮 2. Analisis Kompleksitas
- Time Complexity: O(?)
- Space Complexity: O(?)
- Perbandingan dengan pendekatan lain
- Kapan approach ini optimal

## 💻 3. Implementasi C++
```cpp
// Step-by-step implementation
// Dengan komentar per-blok
```

## 🔄 4. Trace / Simulasi
- Step-by-step trace dengan contoh input
- Tunjukkan state di setiap iterasi
- Gunakan tabel atau diagram

## 📝 5. Variasi & Pattern
- Variasi soal yang menggunakan teknik ini
- Pattern recognition: kapan pakai teknik ini
- Common modifications

## ⚠️ 6. Common Mistakes & Edge Cases
- Pitfall 1
- Pitfall 2
- Edge case yang sering miss

## 🏆 7. Tips Contest
- Kapan pakai teknik ini di contest
- Red flags yang menandakan pakai teknik ini
- Time management tips

## 📌 8. Ringkasan
- Key points
- Cheatsheet singkat
- Link soal latihan di online judge

---

3. FORMAT EXERCISE FILE (WAJIB):

```cpp
/*
============================================================
🏋️ Exercise X: [Judul Problem]
============================================================
Day: X | Difficulty: Easy/Medium/Hard
Topic: [Topik]
Time Limit: 1-2 detik | Memory Limit: 256 MB

📋 PROBLEM STATEMENT:
[Deskripsi LENGKAP minimal 3-5 kalimat]:
- Konteks/scenario
- Apa yang diminta secara jelas
- Constraint yang jelas

📥 INPUT FORMAT:
- Baris pertama: ...
- Baris kedua: ...

📤 OUTPUT FORMAT:
- ...

📏 CONSTRAINTS:
- 1 ≤ N ≤ ...
- 1 ≤ A[i] ≤ ...

📎 SAMPLE INPUT 1:
5
1 3 2 5 4

📎 SAMPLE OUTPUT 1:
15

📎 SAMPLE INPUT 2:
3
1 1 1

📎 SAMPLE OUTPUT 2:
3

💡 HINT: [Hint ringan tanpa spoil solusi]

🎯 Learning Goals:
- [ ] Goal 1
- [ ] Goal 2
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // TODO: Baca input

    // TODO: Implementasi solusi
    // Hint: [Petunjuk pendekatan]

    // TODO: Cetak output

    return 0;
}
```

4. FORMAT SOLUTION FILE (WAJIB):

```cpp
/*
============================================================
✅ Solution X: [Judul Problem]
============================================================
Approach: [Nama teknik/algoritma yang digunakan]
Complexity: Time O(...) | Space O(...)
Key Insight: [Insight kunci mengapa approach ini optimal]

📖 PENJELASAN PENDEKATAN:
1. [Langkah 1]
2. [Langkah 2]
3. [Langkah 3]

🔄 ALTERNATIVE APPROACHES:
- Brute force: O(...) — TLE untuk N besar
- [Approach lain]: O(...) — [kelebihan/kekurangan]
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Step 1: Baca input
    ...

    // Step 2: Proses dengan [teknik]
    ...

    // Step 3: Output hasil
    ...

    return 0;
}
```

5. ISI MATERI WAJIB:

A. TEORI (.md):
   ✅ Penjelasan konsep MENDALAM dalam Bahasa Indonesia
   ✅ Intuisi VISUAL (diagram ASCII, tabel trace)
   ✅ Analisis kompleksitas (Time & Space) untuk SETIAP pendekatan
   ✅ Perbandingan brute force vs optimal
   ✅ Step-by-step C++ implementation dengan komentar
   ✅ Trace/simulasi dengan contoh input kecil
   ✅ Pattern recognition: "Kapan pakai teknik ini?"
   ✅ Common pitfalls & edge cases
   ✅ Tips contest & trick implementasi
   ✅ Link soal latihan di Codeforces/AtCoder/SPOJ
   ✅ Section struktur:
      - 🔍 Konsep & Intuisi
      - 🧮 Analisis Kompleksitas
      - 💻 Implementasi C++ (step-by-step)
      - 🔄 Trace & Simulasi
      - 📝 Variasi & Pattern
      - ⚠️ Common Mistakes & Edge Cases
      - 🏆 Tips Contest
      - 📌 Ringkasan & Cheatsheet

B. EXERCISE FILES (.cpp):
   ✅ 5–8 exercise per hari (progresif easy → hard)
   ✅ Setiap exercise dalam file TERPISAH (exercise_1.cpp, ...)
   ✅ Problem statement LENGKAP di komentar atas
   ✅ Sample I/O minimal 2 test cases
   ✅ Constraints yang jelas
   ✅ TODO comments yang informatif
   ✅ Hints tersedia (tapi tidak spoil solusi)
   ✅ Tingkat kesulitan:
      - Exercise 1-2: Warm-up (langsung dari teori)
      - Exercise 3-4: Core (butuh pemahaman lebih dalam)
      - Exercise 5-6: Challenge (kombinasi konsep/variasi)
      - Exercise 7-8: Contest-level (opsional, untuk yang mau push)

C. SOLUTION FILES (.cpp):
   ✅ Satu solution per exercise (solution_1.cpp, ...)
   ✅ Kode LENGKAP & bisa langsung compile+run
   ✅ Penjelasan approach di komentar atas
   ✅ Analisis kompleksitas
   ✅ Edge case handling
   ✅ Alternative approaches disebutkan
   ✅ AC-ready (bisa langsung submit ke online judge)

D. TUGAS FILES (.cpp) — TANPA SOLUSI:
   ✅ 15 tugas per hari (tugas_01.cpp sampai tugas_15.cpp)
   ✅ HANYA berisi: problem statement + sample I/O + constraints + TODO
   ✅ TIDAK ADA solusi — harus kerjakan sendiri
   ✅ Format setiap file:
      - Komentar: judul + deskripsi soal lengkap + I/O format + constraints
      - Starter code: main() dengan fast I/O
      - // TODO: Kerjakan di sini
   ✅ Progresif: tugas 1-5 (Easy), tugas 6-10 (Medium), tugas 11-15 (Hard)
   ✅ Soal harus sesuai dengan teori hari itu
   ✅ Bisa diverifikasi dengan sample I/O

E. TEMPLATE (.cpp):
   ✅ Starter template khusus topik hari ini
   ✅ Boilerplate yang sering dipakai
   ✅ Snippet yang berguna (bisa di-copy ke solusi)

F. README.md:
   ✅ Learning objectives hari ini
   ✅ Prerequisites
   ✅ Step-by-step learning guide
   ✅ Breakdown exercise (tingkat kesulitan)
   ✅ Link soal online judge terkait (Codeforces, AtCoder, SPOJ, LeetCode)
   ✅ Checklist sebelum lanjut ke hari berikutnya
   ✅ Common mistakes hari ini
   ✅ Preview hari selanjutnya
   ✅ Quick reference cheatsheet

6. C++ REQUIREMENTS & STYLE:

   ✅ C++17 (g++ -std=c++17 -O2 -Wall)
   ✅ Fast I/O WAJIB:
      ios_base::sync_with_stdio(false);
      cin.tie(NULL);
   ✅ Header: #include <bits/stdc++.h> (atau individual jika prefer)
   ✅ using namespace std; (di CP ini acceptable)
   ✅ Tipe data:
      - int untuk N ≤ 2×10⁹
      - long long untuk N > 2×10⁹ (alias: typedef long long ll;)
      - Hati-hati overflow!
   ✅ Naming:
      - snake_case untuk variabel lokal
      - UPPER_CASE untuk konstanta (const int MOD = 1e9+7;)
      - Deskriptif tapi singkat (n, m, adj, dist, dp)
   ✅ Common defines:
      #define ll long long
      #define vi vector<int>
      #define pii pair<int,int>
      #define pb push_back
      #define all(x) (x).begin(), (x).end()
      const int MOD = 1e9 + 7;
      const int INF = 1e18;
   ✅ Output:
      - Gunakan '\n' bukan endl (endl flush buffer = lambat)
      - Fixed precision: cout << fixed << setprecision(9)
   ✅ Array convention:
      - 0-indexed atau 1-indexed (sebutkan di komentar)
      - Ukuran array: N+5 untuk safety buffer
   ✅ Komentar: Bahasa Indonesia, singkat, informatif
   ✅ Markdown cell: Bahasa Indonesia

7. QUALITY CHECKLIST:

   ✅ Semua .cpp bisa di-compile tanpa error (g++ -std=c++17 -O2)
   ✅ Semua solution menghasilkan output sesuai sample I/O
   ✅ Tidak ada undefined behavior (array out of bounds, uninitialized var)
   ✅ Kompleksitas sesuai constraint (tidak TLE)
   ✅ Edge cases di-handle (N=0, N=1, array kosong, dll.)
   ✅ Memory tidak melebihi limit (biasanya 256 MB)
   ✅ Exercise punya TODO yang jelas
   ✅ Solution COMPLETE (tidak ada TODO yang tersisa)
   ✅ README lengkap dan actionable

8. KONTEN SPESIFIK:

   Lihat roadmap Day [DAY_NUMBER]:
   - Topik utama: [akan auto-detect dari roadmap]
   - Teknik/algoritma: [sesuai topik]
   - Constraint level: [tentukan sesuai kesulitan]
   - Focus: [problem-solving oriented, bukan teori kering]

PENTING:
- Fokus pada PROBLEM-SOLVING mindset
- Emphasis pada pattern recognition & analisis kompleksitas
- Code harus COMPILABLE tanpa modifikasi
- Diagram/trace WAJIB — algoritma tanpa trace itu abstrak
- Penjelasan dalam Bahasa Indonesia
- Selalu tanya: "Bagaimana cara RECOGNIZE kapan pakai teknik ini?"
- Edge cases WAJIB disebutkan
- Materi harus DEEP & PRACTICAL
- Exercise harus memaksa berpikir, bukan sekadar copy-paste template
- Setiap solusi harus bisa di-submit ke online judge

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

---

## 🔥 PROMPT SINGKAT (Untuk Daily Use):

```
Lanjut CP Day [DAY_NUMBER]

Buat struktur lengkap:
- teori/Day_XX_Teori_Lengkap.md (teori + kode + diagram + analisis)
- latihan/exercise_1-5.cpp (exercise dengan TODO)
- solusi/solution_1-5.cpp (solusi lengkap + optimal)
- tugas/tugas_01-15.cpp (15 soal TANPA solusi)
- template/template.cpp (starter template)
- README.md

Ikuti roadmap 308 hari CP (lihat ROADMAP_CP.md). Semua code harus COMPILABLE (C++17).
Penjelasan Bahasa Indonesia. Soal competitive programming style.
```

---

## 📌 QUICK REFERENCE — File Conventions

### 🏷️ Section Headers (Pakai Konsisten di Teori .md):
| Emoji | Arti | Contoh |
|-------|------|--------|
| 🔍 | Konsep/Penjelasan | `## 🔍 1. Apa itu Binary Search?` |
| 🧮 | Complexity/Analysis | `## 🧮 2. Analisis Kompleksitas` |
| 💻 | Implementasi Kode | `## 💻 3. Implementasi C++` |
| 🔄 | Trace/Simulasi | `## 🔄 4. Trace Step-by-Step` |
| 📝 | Variasi/Pattern | `## 📝 5. Variasi Soal` |
| ⚠️ | Warning / Pitfall | `## ⚠️ Common Mistakes` |
| 🏆 | Tips Contest | `## 🏆 Tips Contest` |
| 📌 | Summary / Key Points | `## 📌 Ringkasan` |
| 🏋️ | Exercise / Latihan | `## 🏋️ Exercise` |
| ✅ | Solusi / Done | `## ✅ Solution` |
| 💡 | Hint / Tips | `**💡 Hint**:` |
| 🤔 | Refleksi | `## 🤔 Think About It` |

### 📐 Template Starter Code (Copy-Paste Setiap Hari):
```cpp
// ============================================================
// 📦 TEMPLATE — Day XX: [Topik]
// ============================================================
#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define vi vector<int>
#define pii pair<int,int>
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()

const int MOD = 1e9 + 7;
const int INF = 1e18;
const int MAXN = 2e5 + 5;

void solve() {
    // Solusi untuk satu test case
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cin >> t;  // Uncomment jika multi test case
    while (t--) {
        solve();
    }

    return 0;
}
```

### 📏 Template Problem Statement (di Komentar .cpp):
```cpp
/*
============================================================
📋 [EXERCISE/TUGAS] X: [Judul]
============================================================
Source: [Codeforces/AtCoder/Original]
Difficulty: [Rating jika ada] | [Easy/Medium/Hard]
Topics: [tag1, tag2]

PROBLEM:
[Deskripsi soal lengkap]

INPUT:
[Format input]

OUTPUT:
[Format output]

CONSTRAINTS:
- 1 ≤ T ≤ ...
- 1 ≤ N ≤ ...

SAMPLE INPUT:
[test case]

SAMPLE OUTPUT:
[expected output]

NOTE:
[Penjelasan sample jika perlu]
============================================================
*/
```

---

## 📌 QUICK REFERENCE — Roadmap Competitive Programming (308 Hari)

> **📖 Roadmap lengkap ada di file [`ROADMAP_CP.md`](file:///Users/haikalmuzhoffar/KULIAH/ComProgLearning/ROADMAP_CP.md)**
>
> Roadmap 308 hari mencakup **11 fase** dari fondasi sampai strategi kontes level ICPC/CM+.
> Setiap topik sudah **dipecah per hari** agar lebih fokus dan mudah dipelajari.

### 📊 Ringkasan Struktur Roadmap 308 Hari

| Fase                   | Day     | Fokus                                            |
| ---------------------- | ------- | ------------------------------------------------ |
| Fondasi                | 1–28    | C++, kompleksitas, STL                           |
| Teknik Dasar           | 29–56   | Prefix sum, two pointers, sorting, binary search |
| Pencarian & Greedy     | 57–84   | Brute force, backtracking, greedy, constructive  |
| Matematika             | 85–112  | Teori bilangan, kombinatorika, matriks           |
| Graf                   | 113–140 | BFS/DFS, shortest path, MST, DSU                 |
| DP                     | 141–168 | DP dasar sampai bitmask, digit, tree DP          |
| Struktur Data          | 169–196 | BIT, segment tree, sqrt, persistent, treap       |
| Pohon & String         | 197–224 | LCA, HLD, centroid, hashing, suffix structure    |
| Graf Lanjut & Flow     | 225–252 | SCC, 2-SAT, max flow, matching                   |
| Geometri & Optimasi    | 253–280 | Convex hull, sweep line, CHT, FFT                |
| Teknik Khusus & Kontes | 281–308 | Game theory, randomisasi, strategi kontes        |

---

## 🔗 Online Judge Quick Reference

### 📦 Recommended Platforms
| Platform | URL | Keterangan |
|----------|-----|-----------|
| Codeforces | codeforces.com | Contest rutin, problem archive besar |
| AtCoder | atcoder.jp | Soal berkualitas, editorial bagus |
| SPOJ | spoj.com | Classic problems, good for practice |
| LeetCode | leetcode.com | Interview-style, good explanations |
| CSES | cses.fi/problemset | Problem set terstruktur per topik |
| Kattis | open.kattis.com | University-level problems |
| UVa Online Judge | onlinejudge.org | Classic CP problems |

### 🎯 Recommended Problem Sets per Topic
```
📌 CSES Problem Set (cses.fi) — SANGAT DIREKOMENDASIKAN
   - Introductory: Day 1-7
   - Sorting & Searching: Day 15-21
   - Dynamic Programming: Day 85-112
   - Graph Algorithms: Day 57-84
   - Range Queries: Day 113-126
   - Tree Algorithms: Day 43-49
   - Mathematics: Day 22-28, 134-139
   - String Algorithms: Day 32-34, 127-133
```

---

## 🛠️ Cheatsheet: C++ CP Template

```cpp
#include <bits/stdc++.h>
using namespace std;

// === TYPE ALIASES ===
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pii> vpii;

// === MACROS ===
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define F first
#define S second
#define rep(i,a,b) for(int i=(a);i<(b);i++)
#define per(i,a,b) for(int i=(a)-1;i>=(b);i--)

// === CONSTANTS ===
const int MOD = 1e9 + 7;
const ll INF = 1e18;
const int MAXN = 2e5 + 5;

// === UTILITIES ===
ll power(ll base, ll exp, ll mod = MOD) {
    ll result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

void solve() {
    // Your solution here
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cin >> t;
    while (t--) solve();

    return 0;
}
```

---

## 🛠️ Cheatsheet: Common Algorithms (Quick Ref)

### Binary Search Template
```cpp
// Cari minimum x yang memenuhi kondisi f(x) = true
// Asumsi: f(lo)=false, f(hi)=true
int lo = 0, hi = 1e9;
while (lo < hi) {
    int mid = lo + (hi - lo) / 2;
    if (check(mid)) hi = mid;
    else lo = mid + 1;
}
// lo = answer
```

### DSU Template
```cpp
int parent[MAXN], rnk[MAXN];
void init(int n) { iota(parent, parent+n+1, 0); fill(rnk, rnk+n+1, 0); }
int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
void unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return;
    if (rnk[a] < rnk[b]) swap(a, b);
    parent[b] = a;
    if (rnk[a] == rnk[b]) rnk[a]++;
}
```

### Segment Tree Template
```cpp
int tree[4*MAXN], lazy[4*MAXN];
void build(int node, int l, int r, int arr[]) {
    if (l == r) { tree[node] = arr[l]; return; }
    int mid = (l+r)/2;
    build(2*node, l, mid, arr);
    build(2*node+1, mid+1, r, arr);
    tree[node] = tree[2*node] + tree[2*node+1];
}
void update(int node, int l, int r, int pos, int val) {
    if (l == r) { tree[node] = val; return; }
    int mid = (l+r)/2;
    if (pos <= mid) update(2*node, l, mid, pos, val);
    else update(2*node+1, mid+1, r, pos, val);
    tree[node] = tree[2*node] + tree[2*node+1];
}
int query(int node, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return tree[node];
    int mid = (l+r)/2;
    return query(2*node, l, mid, ql, qr) + query(2*node+1, mid+1, r, ql, qr);
}
```

### Dijkstra Template
```cpp
vector<pii> adj[MAXN]; // {neighbor, weight}
ll dist[MAXN];
void dijkstra(int src, int n) {
    fill(dist, dist+n+1, INF);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}
```

---

## 🔑 Key Mindsets untuk Competitive Programming

### 1. 🤔 Constraint → Complexity → Algorithm
```
N ≤ 10      → O(N!) brute force, permutations
N ≤ 20      → O(2^N) bitmask DP
N ≤ 500     → O(N³) Floyd-Warshall, interval DP
N ≤ 5000    → O(N²) simple DP, brute force with pruning
N ≤ 10⁵     → O(N log N) sorting, binary search, segtree
N ≤ 10⁶     → O(N) linear scan, prefix sum
N ≤ 10⁸     → O(N) with very simple operations
N ≤ 10¹⁸    → O(log N) binary exponentiation, math
```

### 2. 🎯 Problem Recognition Pattern
```
"Minimum/Maximum yang memenuhi..."  → Binary Search on Answer
"Berapa banyak cara..."             → DP / Combinatorics
"Shortest path..."                  → BFS/Dijkstra/Bellman-Ford
"Connected components..."           → DSU / BFS / DFS
"Range query..."                    → Segment Tree / BIT / Sparse Table
"Subsequence..."                    → DP (LIS/LCS variant)
"Prefix/suffix..."                  → Prefix Sum / Z-algo / KMP
"Assign tasks optimally..."         → Greedy / Hungarian / Flow
```

### 3. ⚠️ Common Pitfalls
```cpp
// ❌ Integer overflow
int a = 100000, b = 100000;
int c = a * b;  // OVERFLOW!

// ✅ Cast to long long
ll c = (ll)a * b;  // OK

// ❌ Slow output
cout << x << endl;  // endl = flush = slow

// ✅ Fast output
cout << x << '\n';  // '\n' = fast

// ❌ Array too small
int arr[n];  // n bisa besar!

// ✅ Safety buffer
int arr[MAXN + 5];  // +5 buffer
```

### 4. 🏆 Contest Strategy
```
Jam 0:00 - 0:05  → Baca SEMUA soal, identifikasi yang mudah
Jam 0:05 - 0:30  → Solve A (biasanya implementation/brute force)
Jam 0:30 - 1:00  → Solve B (biasanya greedy/simple DP)
Jam 1:00 - 1:30  → Solve C (biasanya main technique)
Jam 1:30 - 2:00  → Attempt D/E atau debug

RULES:
- Stuck > 15 menit? Pindah soal.
- WA? Cek edge case (N=1, N=0, semua sama, sorted, reverse sorted)
- TLE? Cek complexity, optimize constant factor, ganti algorithm
```

### 5. 📌 Debugging Checklist
```
□ Integer overflow? (pakai long long)
□ Array bounds? (0-indexed vs 1-indexed)
□ Edge cases? (N=0, N=1, empty input)
□ Uninitialized variables?
□ Off-by-one error?
□ Correct I/O format? (extra newline?)
□ Multi test case — reset semua variabel?
□ Graph: 1-indexed atau 0-indexed?
```

---

## ⚙️ Setup Environment (Satu Kali)

```bash
# === COMPILER ===
# Mac (sudah ada clang++, atau install g++ via homebrew)
brew install gcc

# Alias untuk g++ dengan flags CP
alias g++17='g++ -std=c++17 -O2 -Wall -Wextra -DLOCAL'

# === COMPILE & RUN ===
g++17 solution.cpp -o sol
./sol < input.txt

# === STRESS TEST ===
# gen.cpp = random input generator
# brute.cpp = brute force solution (pasti benar tapi lambat)
# sol.cpp = solusi yang mau ditest
g++17 gen.cpp -o gen
g++17 brute.cpp -o brute
g++17 sol.cpp -o sol

# Script stress test
for i in $(seq 1 1000); do
    ./gen > input.txt
    ./brute < input.txt > expected.txt
    ./sol < input.txt > output.txt
    if ! diff -q expected.txt output.txt > /dev/null; then
        echo "MISMATCH on test $i"
        cat input.txt
        break
    fi
done
echo "All tests passed!"

# === IDE RECOMMENDATION ===
# - VS Code + C/C++ extension + Code Runner
# - CLion (JetBrains)
# - Vim/Neovim dengan competitive-companion
```

---

## 📁 Contoh Folder (Referensi Struktur):

> **Catatan:** Nomor Day mengikuti roadmap 308 hari di [`ROADMAP_CP.md`](file:///Users/haikalmuzhoffar/KULIAH/ComProgLearning/ROADMAP_CP.md).
> Setiap folder fokus pada **satu topik** untuk kemudahan belajar.

```
CP/Day-18 (Vector - Operasi, Kapasitas dan Iterator)/
├── teori/
│   └── Day_18_Teori_Lengkap.md
├── latihan/
│   ├── exercise_1.cpp   # Operasi dasar vector
│   ├── exercise_2.cpp   # Iterator & kapasitas
│   ├── exercise_3.cpp   # Resize & reserve
│   ├── exercise_4.cpp   # Vector 2D
│   └── exercise_5.cpp   # Problem solving dengan vector
├── solusi/
│   ├── solution_1.cpp
│   ├── solution_2.cpp
│   ├── solution_3.cpp
│   ├── solution_4.cpp
│   └── solution_5.cpp
├── tugas/                  # 15 SOAL TANPA SOLUSI
│   ├── tugas_01.cpp
│   ├── tugas_02.cpp
│   ├── ...                # (tugas_03 - tugas_14)
│   └── tugas_15.cpp
├── template/
│   └── template.cpp       # Starter template untuk topik ini
└── README.md
```

---

*Template ini mengikuti filosofi: **"Competitive Programming bukan tentang hafal algoritma, tapi tentang problem-solving: mengenali pattern, memilih pendekatan yang tepat, dan implement dengan benar & cepat."*** 🏆
