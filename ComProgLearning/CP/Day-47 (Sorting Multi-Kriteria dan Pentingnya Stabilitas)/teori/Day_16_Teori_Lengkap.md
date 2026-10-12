# Day 16 — Custom Comparator

## Tujuan Pembelajaran
- [ ] Memahami strict weak ordering yang dibutuhkan comparator C++
- [ ] Mengimplementasikan operator< pada struct
- [ ] Membuat comparator functor dan lambda
- [ ] Menggunakan custom comparator di priority_queue, set, map
- [ ] Menerapkan multi-criteria sort
- [ ] Membedakan stable_sort vs sort

---

## 1. Strict Weak Ordering — Aturan Dasar

Semua comparator di C++ harus memenuhi **strict weak ordering**:

| Properti | Artinya |
|----------|---------|
| **Irreflexivity** | `comp(a, a)` = `false` (tidak bisa `a < a`) |
| **Asymmetry** | Jika `comp(a,b)=true`, maka `comp(b,a)=false` |
| **Transitivity** | Jika `a<b` dan `b<c`, maka `a<c` |

**JANGAN pakai `<=` atau `>=`** → Melanggar irreflexivity → Undefined Behavior!

```cpp
// SALAH — menggunakan <=
sort(v.begin(), v.end(), [](int a, int b){ return a <= b; }); // UB!

// BENAR — menggunakan <
sort(v.begin(), v.end(), [](int a, int b){ return a < b; });   // OK
```

---

## 2. `operator<` Overloading

Cara paling clean: definisikan `operator<` langsung di struct → sort bekerja otomatis.

```cpp
struct Point {
    int x, y;

    bool operator<(const Point& other) const {
        if (x != other.x) return x < other.x; // x lebih kecil dulu
        return y < other.y;                    // tiebreak: y
    }
};

vector<Point> pts = {{3,1},{1,5},{1,2},{3,0}};
sort(pts.begin(), pts.end());
// Hasil: (1,2),(1,5),(3,0),(3,1)

// Juga bekerja untuk: set, map, priority_queue<T>
set<Point> s;
s.insert({1,2});
```

Untuk descending, gunakan:
```cpp
sort(pts.begin(), pts.end(), [](const Point& a, const Point& b){
    return b < a; // balik urutan
});
// atau: sort(pts.rbegin(), pts.rend());
```

---

## 3. Comparator Functor Struct

Berguna saat comparator perlu di-reuse di beberapa tempat, atau dipakai di container.

```cpp
struct Student {
    string name;
    int score, age;
};

// Functor: sort by score desc, name asc
struct CompStudent {
    bool operator()(const Student& a, const Student& b) const {
        if (a.score != b.score) return a.score > b.score; // desc
        return a.name < b.name;                           // asc tiebreak
    }
};

vector<Student> v = {{"Alice",90,20}, {"Bob",85,22}, {"Charlie",90,21}};
sort(v.begin(), v.end(), CompStudent{});

// Keuntungan functor vs lambda:
// → Bisa dipakai di priority_queue, set, map (butuh tipe, bukan value)
priority_queue<Student, vector<Student>, CompStudent> pq;
set<Student, CompStudent> s;
```

---

## 4. Lambda Comparator

Paling concise untuk inline sorting.

```cpp
// Sort satu kriteria
sort(v.begin(), v.end(), [](const string& a, const string& b){
    return a.size() < b.size(); // by length
});

// Multi-criteria (3 tingkat)
sort(v.begin(), v.end(), [](const Student& a, const Student& b){
    if (a.score != b.score) return a.score > b.score; // score desc
    if (a.name != b.name)   return a.name < b.name;   // name asc
    return a.age < b.age;                              // age asc tiebreak
});

// Capture variabel luar
int K = 5;
sort(v.begin(), v.end(), [K](int a, int b){
    return abs(a-K) < abs(b-K); // sort by distance to K
});
```

---

## 5. `priority_queue` dengan Custom Comparator

`priority_queue` default adalah **max-heap**. Untuk custom:

```cpp
// Min-heap untuk int
priority_queue<int, vector<int>, greater<int>> minPQ;

// Min-heap untuk struct Task (by deadline ascending)
struct Task { string name; int deadline, priority; };

struct CompTask {
    bool operator()(const Task& a, const Task& b) const {
        return a.deadline > b.deadline; // min-heap: deadline terkecil di atas
    }
};

priority_queue<Task, vector<Task>, CompTask> taskPQ;
taskPQ.push({"A", 5, 2}); taskPQ.push({"B", 3, 1});
// taskPQ.top() = {"B", 3, 1}  (deadline=3 adalah terkecil)

// KUNCI: priority_queue dengan Comp pops elemen yang comp(other,top)=false
// Artinya: comp(a,b)=true berarti a LEBIH RENDAH PRIORITASNYA dari b
// Untuk min-heap: comp(a,b) = a.val > b.val
```

---

## 6. `set` dan `map` dengan Custom Comparator

```cpp
// set dengan custom comparator
struct CmpByLength {
    bool operator()(const string& a, const string& b) const {
        if (a.size() != b.size()) return a.size() < b.size();
        return a < b; // tiebreak by lex
    }
};

set<string, CmpByLength> wordSet;
wordSet.insert("hello");
wordSet.insert("hi");
wordSet.insert("hey");
// Iterasi: hi, hey, hello (by length, then lex)

// map dengan custom key comparator
map<pair<int,int>, int, [](...)> m; // lambda tidak bisa di sini!
// Gunakan functor atau override operator< pada key
```

---

## 7. Index Sort — Pola Umum CP

Sort array berdasarkan nilai, tapi simpan urutan index aslinya.

```cpp
vector<int> A = {30, 10, 50, 20, 40};
vector<int> idx(A.size());
iota(idx.begin(), idx.end(), 0); // {0,1,2,3,4}

// Sort indices by A[i]
sort(idx.begin(), idx.end(),
    [&A](int i, int j){ return A[i] < A[j]; });
// idx = {1,3,0,4,2}  (index dari terkecil ke terbesar)
// A[idx[0]]=10, A[idx[1]]=20, dst.

// Kegunaan: saat kita perlu tahu "urutan ke-k" tapi juga butuh index aslinya
```

---

## 8. Version String Comparator

Masalah klasik: sort string "1.10.3" dan "1.9.5" secara semantic.

```cpp
// Lexicographic sort salah: "1.10" < "1.9" → SALAH
// Semantic sort benar: "1.10" > "1.9" (10 > 9)

vector<int> parseVersion(const string& s) {
    vector<int> parts;
    stringstream ss(s);
    string token;
    while (getline(ss, token, '.'))
        parts.push_back(stoi(token));
    return parts;
}

bool versionLess(const string& a, const string& b) {
    vector<int> va = parseVersion(a), vb = parseVersion(b);
    return va < vb; // lexicographic compare pada vector<int>
}

vector<string> versions = {"1.10.3","1.9.5","2.0.0","1.10.1"};
sort(versions.begin(), versions.end(), versionLess);
// Hasil: 1.9.5, 1.10.1, 1.10.3, 2.0.0
```

---

## 9. `stable_sort` vs `sort`

```cpp
// sort: urutan relatif elemen-equal TIDAK dijamin
sort(v.begin(), v.end(), comp);

// stable_sort: urutan relatif elemen-equal DIJAMIN sama dengan input
stable_sort(v.begin(), v.end(), comp);
// Berguna untuk multi-pass sort:

// 1. Sort by name
stable_sort(students.begin(), students.end(),
    [](const Student& a, const Student& b){ return a.name < b.name; });
// 2. Stable-sort by score → siswa dengan score sama tetap urut by name
stable_sort(students.begin(), students.end(),
    [](const Student& a, const Student& b){ return a.score > b.score; });
```

---

## 10. Common Mistakes

1. **Comparator dengan `<=`** → Violates strict weak ordering → UB / infinite loop
2. **Inconsistent comparator** → `comp(a,b)=true` dan `comp(b,a)=true` → UB
3. **Priority_queue arah terbalik** → Default adalah MAX-heap. Untuk min-heap: gunakan `greater<T>` atau invert lambda
4. **Lambda di template argument** → Set/map butuh tipe, bukan nilai. Gunakan functor struct atau `decltype(lambda)`
5. **Tiebreak yang incomplete** → Jika `a.score==b.score && a.name==b.name`, comparator harus return false (tidak boleh UB)

---

## 11. Kompleksitas

| Operasi | Menggunakan Comparator | Kompleksitas |
|---------|----------------------|-------------|
| `sort` | Yes | O(n log n) |
| `stable_sort` | Yes | O(n log² n) |
| `priority_queue push/pop` | Yes | O(log n) |
| `set insert/find` | Yes | O(log n) |
| `map operator[]` | Yes | O(log n) |

---

## 12. Quick Reference

```cpp
// operator< (auto-sort, set, priority_queue<T>)
bool operator<(const T& o) const { return key < o.key; }

// Lambda
sort(v.begin(), v.end(), [](const T& a, const T& b){
    return a.x != b.x ? a.x < b.x : a.y < b.y; });

// Functor struct
struct Cmp { bool operator()(const T& a, const T& b) const {
    return a.val < b.val; }};

// Min-heap priority_queue
priority_queue<T, vector<T>, Cmp> pq; // pops min

// Custom set
set<T, Cmp> s;

// Index sort
iota(idx.begin(), idx.end(), 0);
sort(idx.begin(), idx.end(), [&](int i, int j){ return A[i] < A[j]; });
```
