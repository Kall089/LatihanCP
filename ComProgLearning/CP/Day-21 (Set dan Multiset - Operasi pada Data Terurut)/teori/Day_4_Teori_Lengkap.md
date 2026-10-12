# 📊 Day 4: STL Containers 2 — Set, Map, Unordered_Set, Unordered_Map, Multiset

**Hari**: Day 4 dari 150 Hari Competitive Programming  
**Topik**: Associative & Unordered Containers  
**Prerequisites**: Vector, Pair, String (Day 3)  
**Difficulty**: ⭐⭐ (Beginner-Intermediate)  
**Learning Objectives**:
- Memahami perbedaan set, multiset, unordered_set
- Menggunakan map dan unordered_map untuk frequency counting & lookup
- Mengetahui tradeoff ordered vs unordered (O(log n) vs O(1))
- Menggunakan lower_bound/upper_bound di set

---

## 🔍 1. Konsep & Intuisi

### Apa itu Associative Containers?

Container yang menyimpan data berdasarkan **KEY**, bukan posisi index.

**Analogi Kehidupan Nyata:**
- **Set** = Daftar hadir (nama unik, otomatis urut A-Z)
- **Multiset** = Rak buku toko (bisa ada buku sama, urut judul)
- **Map** = Buku telepon (nama → nomor, urut nama)
- **Unordered_map** = HashMap / Dictionary (cepat tapi tidak urut)

### Diagram Keputusan: Container Mana yang Dipakai?

```
Butuh simpan data dengan key?
│
├── YA (key → value) ────────────────────────────┐
│   │                                            │
│   ├── Butuh urut by key? ──── YA → map         │
│   │                                            │
│   └── Tidak perlu urut? ──── → unordered_map   │
│                                                │
└── TIDAK (hanya value) ────────────────────────────┐
    │                                                │
    ├── Boleh duplikat?                              │
    │   ├── TIDAK ────────────────────────────┐      │
    │   │   ├── Butuh urut? → set             │      │
    │   │   └── Tidak urut? → unordered_set   │      │
    │   │                                     │      │
    │   └── YA ───────────────────────────────┐      │
    │       └── Butuh urut? → multiset        │      │
    │          (tidak ada unordered_multiset   │      │
    │           yang umum dipakai di CP)       │      │
```

### Kapan Digunakan di CP?

| Pattern Soal | Container |
|-------------|-----------|
| "Hitung elemen distinct" | `set` |
| "Cari elemen ≥ X terdekat" | `set` + `lower_bound` |
| "Frequency count" | `map` atau `unordered_map` |
| "Cek apakah elemen ada" (O(1)) | `unordered_set` |
| "Dynamic sorted collection + delete" | `multiset` |
| "Cari elemen terkecil/terbesar yang tersedia" | `multiset` atau `set` |
| "Registration system (nama + counter)" | `map<string, int>` |

---

## 🧮 2. Analisis Kompleksitas

### Perbandingan Lengkap

| Operasi | `set` / `map` | `unordered_set` / `unordered_map` | `multiset` |
|---------|:-------------:|:---------------------------------:|:----------:|
| Insert | O(log n) | O(1) avg, O(n) worst | O(log n) |
| Erase | O(log n) | O(1) avg | O(log n) |
| Find/Count | O(log n) | O(1) avg | O(log n + k)* |
| Lower/Upper bound | O(log n) | ❌ Tidak ada! | O(log n) |
| Min/Max | O(1)** | ❌ O(n) | O(1)** |
| Iterasi urut | ✅ O(n) | ❌ Random order | ✅ O(n) |

*k = jumlah elemen yang cocok  
**begin() = min, rbegin() = max

### Kapan Pilih Ordered vs Unordered?

| Pilih `set`/`map` (ordered) | Pilih `unordered_set`/`unordered_map` |
|----------------------------|--------------------------------------|
| Butuh lower_bound/upper_bound | Hanya butuh insert/find/erase |
| Butuh min/max cepat | N sangat besar (> 10⁶) |
| Butuh iterasi terurut | Constraint ketat (TLE risk) |
| N ≤ 10⁶ biasanya cukup | Tidak butuh urutan |

**Hati-hati**: `unordered_map` bisa di-hack menjadi O(n) di Codeforces!  
Solusi: custom hash atau pakai `map` saja jika time limit longgar.

---

## 💻 3. Implementasi C++

### 3.1 Set — Koleksi Unik Terurut

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // === DEKLARASI ===
    set<int> s;
    set<int> s2 = {5, 3, 1, 4, 2};  // otomatis urut: {1,2,3,4,5}

    // === INSERT ===
    s.insert(10);   // s = {10}
    s.insert(5);    // s = {5, 10}
    s.insert(10);   // s = {5, 10} — duplikat diabaikan!
    s.insert(3);    // s = {3, 5, 10}

    // === SIZE & CHECK ===
    cout << s.size() << '\n';     // 3
    cout << s.count(5) << '\n';   // 1 (ada)
    cout << s.count(7) << '\n';   // 0 (tidak ada)

    // === FIND ===
    auto it = s.find(5);
    if (it != s.end()) {
        cout << "Found: " << *it << '\n';  // 5
    }

    // === ERASE ===
    s.erase(5);      // s = {3, 10}
    // s.erase(it);  // erase by iterator juga bisa

    // === MIN & MAX ===
    cout << *s.begin() << '\n';   // 3 (minimum)
    cout << *s.rbegin() << '\n';  // 10 (maximum)

    // === LOWER_BOUND & UPPER_BOUND ===
    set<int> nums = {1, 3, 5, 7, 9};
    
    auto lb = nums.lower_bound(4);  // iterator ke >= 4 → menunjuk 5
    auto ub = nums.upper_bound(5);  // iterator ke > 5 → menunjuk 7
    
    cout << *lb << '\n';  // 5
    cout << *ub << '\n';  // 7

    // Cari elemen TERBESAR yang ≤ x:
    int x = 6;
    auto it2 = nums.upper_bound(x);  // > 6 → menunjuk 7
    if (it2 != nums.begin()) {
        --it2;  // mundur 1 → menunjuk 5
        cout << "Largest <= " << x << ": " << *it2 << '\n';  // 5
    }

    // === ITERASI (selalu terurut!) ===
    for (int val : nums) {
        cout << val << ' ';  // 1 3 5 7 9
    }
    cout << '\n';

    return 0;
}
```

### 3.2 Multiset — Koleksi Terurut dengan Duplikat

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    multiset<int> ms;

    // === INSERT (duplikat diizinkan) ===
    ms.insert(5);   // {5}
    ms.insert(3);   // {3, 5}
    ms.insert(5);   // {3, 5, 5}
    ms.insert(1);   // {1, 3, 5, 5}
    ms.insert(5);   // {1, 3, 5, 5, 5}

    // === COUNT (bisa > 1!) ===
    cout << ms.count(5) << '\n';  // 3

    // === ERASE — HATI-HATI! ===
    
    // ⚠️ BAHAYA: ms.erase(5) hapus SEMUA 5!
    // ms.erase(5);  // {1, 3} — semua 5 hilang!

    // ✅ BENAR: Hapus SATU occurrence saja
    ms.erase(ms.find(5));  // {1, 3, 5, 5} — hanya satu 5 dihapus
    cout << ms.count(5) << '\n';  // 2

    // === MIN & MAX ===
    cout << *ms.begin() << '\n';   // 1 (minimum)
    cout << *ms.rbegin() << '\n';  // 5 (maximum)

    // === LOWER/UPPER BOUND ===
    auto lb = ms.lower_bound(5);  // iterator ke 5 pertama
    auto ub = ms.upper_bound(5);  // iterator setelah 5 terakhir
    
    // Hitung jumlah 5: distance(lb, ub) atau ms.count(5)
    
    // === USE CASE CP: Concert Tickets ===
    // "Cari tiket dengan harga ≤ budget, ambil yang termahal"
    multiset<int> tickets = {3, 5, 7, 9, 11};
    int budget = 8;
    
    auto it = tickets.upper_bound(budget);  // > 8 → menunjuk 9
    if (it != tickets.begin()) {
        --it;  // mundur → menunjuk 7
        cout << "Best ticket: " << *it << '\n';  // 7
        tickets.erase(it);  // tiket sudah diambil, hapus
    } else {
        cout << "No ticket available\n";
    }

    return 0;
}
```

### 3.3 Map — Dictionary (Key → Value)

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // === DEKLARASI ===
    map<string, int> m;

    // === INSERT / UPDATE ===
    m["alice"] = 95;
    m["bob"] = 87;
    m["charlie"] = 92;
    m["alice"] = 100;  // UPDATE: alice sekarang 100

    // === AKSES ===
    cout << m["alice"] << '\n';  // 100
    
    // ⚠️ HATI-HATI: m["xyz"] akan INSERT "xyz" dengan value 0!
    // Gunakan count() atau find() untuk cek tanpa insert
    if (m.count("dave")) {
        cout << m["dave"] << '\n';
    } else {
        cout << "dave not found\n";
    }

    // === SIZE & ERASE ===
    cout << m.size() << '\n';  // 3
    m.erase("bob");            // hapus bob
    cout << m.size() << '\n';  // 2

    // === ITERASI (terurut by key!) ===
    for (auto& [key, value] : m) {
        cout << key << ": " << value << '\n';
    }
    // Output (alphabetical by key):
    // alice: 100
    // charlie: 92

    // === FREQUENCY COUNTING (Pattern Paling Umum!) ===
    vector<int> arr = {1, 2, 3, 1, 2, 1, 4, 2};
    map<int, int> freq;
    for (int x : arr) {
        freq[x]++;  // otomatis 0 jika belum ada, lalu +1
    }
    // freq = {1:3, 2:3, 3:1, 4:1}

    // Cari elemen dengan frekuensi tertinggi
    int max_freq = 0, most_common = 0;
    for (auto& [val, cnt] : freq) {
        if (cnt > max_freq) {
            max_freq = cnt;
            most_common = val;
        }
    }
    cout << "Most common: " << most_common << " (" << max_freq << " times)\n";

    // === LOWER_BOUND / UPPER_BOUND di map ===
    map<int, string> scores;
    scores[60] = "C";
    scores[70] = "B";
    scores[80] = "A";
    scores[90] = "A+";

    int student_score = 75;
    auto it = scores.upper_bound(student_score);  // > 75 → menunjuk {80, "A"}
    if (it != scores.begin()) {
        --it;  // mundur → {70, "B"}
        cout << "Grade: " << it->second << '\n';  // B
    }

    return 0;
}
```

### 3.4 Unordered_Map — HashMap (O(1) Average)

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // === DEKLARASI ===
    unordered_map<string, int> um;

    // === INSERT & ACCESS (sama seperti map) ===
    um["alice"] = 95;
    um["bob"] = 87;
    um["bob"]++;  // bob = 88

    // === CEPAT! O(1) average ===
    cout << um["alice"] << '\n';   // 95
    cout << um.count("bob") << '\n'; // 1

    // === FREQUENCY COUNT (lebih cepat dari map untuk N besar) ===
    int n = 7;
    vector<int> arr = {1, 2, 1, 3, 2, 1, 3};
    unordered_map<int, int> freq;
    for (int x : arr) {
        freq[x]++;
    }
    // freq[1]=3, freq[2]=2, freq[3]=2

    // === TWO SUM PATTERN ===
    // "Cari dua elemen yang jumlahnya = target"
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    unordered_map<int, int> seen;  // value → index

    for (int i = 0; i < (int)nums.size(); i++) {
        int complement = target - nums[i];
        if (seen.count(complement)) {
            cout << seen[complement] << " " << i << '\n';  // 0 1
            break;
        }
        seen[nums[i]] = i;
    }

    // === KAPAN PAKAI unordered_map vs map? ===
    // unordered_map: N > 10^5, hanya butuh insert/find/erase
    // map: butuh iterasi terurut, lower/upper_bound, atau N kecil

    // === ANTI-HASH ATTACK (Codeforces) ===
    // Di CF, orang bisa craft input yang membuat unordered_map O(n²)
    // Solusi: custom hash atau pakai map saja
    // Untuk aman di contest: pakai map kecuali benar-benar butuh O(1)

    return 0;
}
```

### 3.5 Unordered_Set — HashSet

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    unordered_set<int> us;

    // === INSERT ===
    us.insert(10);
    us.insert(20);
    us.insert(10);  // duplikat diabaikan
    // us berisi {10, 20} (urutan tidak dijamin)

    // === FIND & COUNT ===
    if (us.count(10)) cout << "10 exists\n";  // O(1) avg

    // === USE CASE: Cek existence cepat ===
    int n = 5;
    vector<int> arr = {3, 1, 4, 1, 5};
    unordered_set<int> exists(arr.begin(), arr.end());

    // Query: apakah x ada?
    int queries[] = {1, 2, 4, 6};
    for (int q : queries) {
        cout << q << ": " << (exists.count(q) ? "YES" : "NO") << '\n';
    }
    // 1: YES, 2: NO, 4: YES, 6: NO

    return 0;
}
```

---

## 🔄 4. Trace / Simulasi

### Trace: Set Insert & Lower_Bound

```
Operasi                    | Set State (sorted)     | Size
---------------------------|------------------------|-----
set<int> s;                | {}                     | 0
s.insert(5);               | {5}                    | 1
s.insert(2);               | {2, 5}                 | 2
s.insert(8);               | {2, 5, 8}             | 3
s.insert(5);               | {2, 5, 8}             | 3  ← duplikat ditolak!
s.insert(1);               | {1, 2, 5, 8}          | 4
s.lower_bound(3);          | → iterator ke 5        |
s.lower_bound(5);          | → iterator ke 5        |
s.upper_bound(5);          | → iterator ke 8        |
s.erase(2);                | {1, 5, 8}             | 3
*s.begin();                | → 1 (minimum)          |
*s.rbegin();               | → 8 (maximum)          |
```

### Trace: Multiset Erase (Trap Umum!)

```
Operasi                        | Multiset State          | Size
-------------------------------|-------------------------|-----
multiset<int> ms;              | {}                      | 0
ms.insert(3);                  | {3}                     | 1
ms.insert(3);                  | {3, 3}                  | 2
ms.insert(3);                  | {3, 3, 3}              | 3
ms.insert(5);                  | {3, 3, 3, 5}           | 4

ms.erase(ms.find(3));         | {3, 3, 5}              | 3  ← hapus SATU 3
ms.erase(3);                   | {5}                     | 1  ← hapus SEMUA 3!
```

**Lesson**: SELALU pakai `ms.erase(ms.find(x))` jika mau hapus satu saja!

### Trace: Map Frequency Count

```
Input: "aababc"

Iterasi | Char | freq state
--------|------|---------------------------
1       | 'a'  | {'a': 1}
2       | 'a'  | {'a': 2}
3       | 'b'  | {'a': 2, 'b': 1}
4       | 'a'  | {'a': 3, 'b': 1}
5       | 'b'  | {'a': 3, 'b': 2}
6       | 'c'  | {'a': 3, 'b': 2, 'c': 1}

Note: map terurut by key (a < b < c)
```

---

## 📝 5. Variasi & Pattern

### Pattern 1: Frequency Count

```cpp
// Hitung frekuensi setiap elemen
map<int, int> freq;
for (int x : arr) freq[x]++;

// Cari elemen paling sering
auto it = max_element(freq.begin(), freq.end(),
    [](auto& a, auto& b) { return a.second < b.second; });
cout << it->first << " appears " << it->second << " times\n";
```

### Pattern 2: Set sebagai "Sliding Sorted Container"

```cpp
// Maintain N elemen terbesar
multiset<int> top_k;
for (int x : stream) {
    top_k.insert(x);
    if (top_k.size() > k) {
        top_k.erase(top_k.begin());  // hapus terkecil
    }
}
// top_k berisi k elemen terbesar
```

### Pattern 3: Two Sum dengan Map

```cpp
// Cari pair (i, j) dimana arr[i] + arr[j] == target
unordered_map<int, int> seen;
for (int i = 0; i < n; i++) {
    int need = target - arr[i];
    if (seen.count(need)) {
        cout << seen[need] << " " << i << '\n';
    }
    seen[arr[i]] = i;
}
```

### Pattern 4: Registration System (Map)

```cpp
// Setiap nama yang sudah ada, tambah suffix "_1", "_2", dst.
map<string, int> names;
for (string& name : registrations) {
    if (names.count(name)) {
        cout << name << "_" << names[name] << '\n';
        names[name]++;
    } else {
        cout << "OK\n";
        names[name] = 1;
    }
}
```

### Pattern 5: Concert Tickets (Multiset + Upper Bound)

```cpp
// Cari tiket termahal yang ≤ budget customer
multiset<int> tickets(all_tickets.begin(), all_tickets.end());
for (int budget : customers) {
    auto it = tickets.upper_bound(budget);
    if (it == tickets.begin()) {
        cout << -1 << '\n';  // tidak ada tiket
    } else {
        --it;
        cout << *it << '\n';
        tickets.erase(it);   // tiket sudah terjual
    }
}
```

---

## ⚠️ 6. Common Mistakes & Edge Cases

### Mistake 1: Map [] Creates Entry!

```cpp
map<string, int> m;
// ⚠️ BAHAYA:
if (m["key"] == 0) { ... }
// "key" sekarang ADA di map dengan value 0!

// ✅ BENAR:
if (m.count("key") == 0) { ... }   // tidak insert
if (m.find("key") == m.end()) { ... }  // tidak insert
```

### Mistake 2: Multiset erase(value) vs erase(iterator)

```cpp
multiset<int> ms = {1, 1, 1, 2, 3};

ms.erase(1);          // HAPUS SEMUA 1! ms = {2, 3}
ms.erase(ms.find(1)); // hapus satu 1.   ms = {1, 1, 2, 3}
```

### Mistake 3: Iterasi + Erase di Set/Map

```cpp
// ⚠️ SALAH:
for (auto it = s.begin(); it != s.end(); it++) {
    if (*it % 2 == 0) s.erase(it);  // iterator invalid setelah erase!
}

// ✅ BENAR:
for (auto it = s.begin(); it != s.end(); ) {
    if (*it % 2 == 0) {
        it = s.erase(it);  // erase return next valid iterator
    } else {
        ++it;
    }
}
```

### Mistake 4: Unordered containers dengan custom types

```cpp
// ⚠️ Tidak compile! pair tidak punya default hash
unordered_set<pair<int,int>> us;  // ERROR!

// ✅ Gunakan set saja, atau define custom hash
set<pair<int,int>> s;  // ini works
```

### Edge Cases

- **Map/Set kosong** → `begin() == end()`, jangan dereference!
- **lower_bound return end()** → tidak ada elemen >= x
- **upper_bound return begin()** → tidak ada elemen < x (jadi jangan `--it`)
- **N = 0** → tidak ada elemen, pastikan tidak akses container kosong

---

## 🏆 7. Tips Contest

### Decision Table Cepat

| Butuh apa? | Pakai |
|------------|-------|
| Count distinct | `set.size()` |
| Cek exists | `set.count()` / `unordered_set.count()` |
| Frequency | `map[x]++` |
| K-th smallest | `set` + advance(it, k) atau `order_of_key` |
| Floor/Ceiling | `set` + `lower_bound`/`upper_bound` |
| Sorted + delete + insert | `multiset` |
| Fast lookup only | `unordered_set/map` |

### Red Flags di Soal

- "Berapa banyak elemen berbeda?" → `set`
- "Untuk setiap query, cari elemen terdekat yang ≥ X" → `set` + `lower_bound`
- "Hitung berapa kali setiap elemen muncul" → `map` frequency
- "Registration: jika sudah ada, beri nama_1, nama_2..." → `map<string,int>`
- "Tiket/resource yang bisa diambil lalu hilang" → `multiset`

### Performance Tips

```cpp
// 1. Untuk string keys yang panjang, unordered_map lebih cepat
//    (map compare string = O(len), unordered hash = O(len) tapi constant smaller)

// 2. Jika hanya butuh min/max + insert/delete, multiset cukup
//    Tidak perlu priority_queue (yang tidak support delete arbitrary)

// 3. Set/map iterasi terurut → bisa binary search dengan lower_bound
//    TAPI jangan pakai std::lower_bound(s.begin(), s.end(), x) 
//    → ini O(n)! Pakai s.lower_bound(x) → O(log n)
```

---

## 📌 8. Ringkasan

### Key Points

1. **Set**: unik + terurut, O(log n) semua operasi
2. **Multiset**: terurut + duplikat, HATI-HATI `erase(value)` hapus semua!
3. **Map**: key→value terurut, `[]` operator auto-insert
4. **Unordered_map/set**: O(1) average tapi no ordering, bisa di-hack
5. **lower_bound(x)**: iterator ke elemen ≥ x
6. **upper_bound(x)**: iterator ke elemen > x

### Cheatsheet Singkat

```cpp
// SET: elemen unik, sorted
set<int> s; s.insert(x); s.erase(x); s.count(x);
*s.begin()=min; *s.rbegin()=max; s.lower_bound(x);

// MULTISET: sorted + duplicates
multiset<int> ms; ms.insert(x);
ms.erase(ms.find(x)); // hapus SATU!

// MAP: key→value, sorted by key
map<K,V> m; m[key]=val; m.count(key); m.erase(key);
for(auto&[k,v]:m)

// UNORDERED: O(1) avg, no ordering
unordered_map<K,V> um; um[key]++;
```

### Link Soal Latihan Online Judge

| Platform | Problem | Topik |
|----------|---------|-------|
| CSES | Distinct Numbers | set |
| CSES | Concert Tickets | multiset + upper_bound |
| CSES | Sum of Two Values | unordered_map (two sum) |
| CF 4C | Registration System | map<string,int> |
| CF 1520D | Same Differences | map frequency |
| AtCoder ABC155D | Pairs | map/multiset |
