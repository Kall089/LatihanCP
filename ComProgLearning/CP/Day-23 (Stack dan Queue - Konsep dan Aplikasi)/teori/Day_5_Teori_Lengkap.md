# 📊 Day 5: STL Containers 3 — Stack, Queue, Deque, Priority_Queue

**Hari**: Day 5 dari 150 Hari Competitive Programming  
**Topik**: Container Adaptor & Deque  
**Prerequisites**: Vector, basic STL (Day 3-4)  
**Difficulty**: ⭐⭐ (Beginner-Intermediate)  
**Learning Objectives**:
- Memahami dan menggunakan Stack (LIFO)
- Memahami dan menggunakan Queue (FIFO)
- Menggunakan Deque untuk operasi dua ujung
- Menggunakan Priority Queue (Heap) untuk greedy problems

---

## 🔍 1. Konsep & Intuisi

### Apa itu Container Adaptor?

Container adaptor = "wrapper" di atas container lain yang membatasi operasi yang bisa dilakukan, sehingga memaksa penggunaan pattern tertentu.

**Analogi Kehidupan Nyata:**

| Container | Analogi | Prinsip |
|-----------|---------|---------|
| **Stack** | Tumpukan piring | LIFO: yang terakhir ditaruh, yang pertama diambil |
| **Queue** | Antrian kasir | FIFO: yang pertama datang, yang pertama dilayani |
| **Deque** | Antrian dua arah | Bisa masuk/keluar dari depan DAN belakang |
| **Priority Queue** | Ruang tunggu IGD | Yang paling urgent dilayani duluan |

### Visualisasi ASCII

```
STACK (LIFO):           QUEUE (FIFO):          PRIORITY QUEUE:
                        
  ┌───┐ ← top          front → ┌───┬───┬───┐ ← back     ┌───┐ ← top (max)
  │ 3 │ ← push/pop              │ 1 │ 2 │ 3 │             │ 9 │ 
  ├───┤                          └───┴───┴───┘             ├───┤
  │ 2 │                         pop ↑         ↑ push       │ 7 │
  ├───┤                                                    ├───┤
  │ 1 │                                                    │ 3 │
  └───┘                                                    └───┘

DEQUE (Double-Ended):
push_front → ┌───┬───┬───┬───┐ ← push_back
pop_front  → │ 1 │ 2 │ 3 │ 4 │ ← pop_back
              └───┴───┴───┴───┘
              front         back
```

### Kapan Digunakan di CP?

| Pattern Soal | Container |
|-------------|-----------|
| Bracket matching, undo operation | **Stack** |
| Next greater/smaller element | **Stack** (monotonic) |
| BFS, level-order traversal | **Queue** |
| Process in order (FIFO) | **Queue** |
| Sliding window min/max | **Deque** (monotonic) |
| Push/pop dari dua sisi | **Deque** |
| Greedy: selalu ambil max/min | **Priority Queue** |
| Merge K sorted, top-K elements | **Priority Queue** |
| Dijkstra shortest path | **Priority Queue** |

---

## 🧮 2. Analisis Kompleksitas

| Operasi | Stack | Queue | Deque | Priority Queue |
|---------|:-----:|:-----:|:-----:|:--------------:|
| push (back/top) | O(1) | O(1) | O(1) | O(log n) |
| pop (top/front) | O(1) | O(1) | O(1) | O(log n) |
| top/front/back | O(1) | O(1) | O(1) | O(1) |
| push_front | ❌ | ❌ | O(1) | ❌ |
| Random access [i] | ❌ | ❌ | O(1) | ❌ |
| Find/search | O(n)* | O(n)* | O(n) | O(n)* |
| Size/empty | O(1) | O(1) | O(1) | O(1) |

*Tidak ada built-in find; harus pop semua untuk search.

### Kapan Pakai Apa?

```
Butuh LIFO? → Stack
Butuh FIFO? → Queue  
Butuh keduanya (front + back)? → Deque
Butuh selalu akses max/min? → Priority Queue
Butuh sorted + insert/delete arbitrary? → Multiset (Day 4)
```

---

## 💻 3. Implementasi C++

### 3.1 Stack — Last In, First Out

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    stack<int> st;

    // === PUSH (tambah ke atas) ===
    st.push(10);  // stack: [10]
    st.push(20);  // stack: [10, 20]
    st.push(30);  // stack: [10, 20, 30] ← top

    // === TOP (lihat elemen paling atas) ===
    cout << st.top() << '\n';  // 30

    // === POP (hapus elemen paling atas) — return void! ===
    st.pop();     // stack: [10, 20] ← top sekarang 20
    cout << st.top() << '\n';  // 20

    // === SIZE & EMPTY ===
    cout << st.size() << '\n';   // 2
    cout << st.empty() << '\n';  // 0 (false)

    // === ITERASI (harus pop satu per satu) ===
    while (!st.empty()) {
        cout << st.top() << ' ';  // 20 10
        st.pop();
    }
    cout << '\n';

    // ================================================
    // USE CASE 1: BRACKET MATCHING
    // ================================================
    string s = "({[]})";
    stack<char> brackets;
    bool valid = true;

    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            brackets.push(c);
        } else {
            if (brackets.empty()) { valid = false; break; }
            char top = brackets.top();
            brackets.pop();
            if (c == ')' && top != '(') { valid = false; break; }
            if (c == '}' && top != '{') { valid = false; break; }
            if (c == ']' && top != '[') { valid = false; break; }
        }
    }
    if (!brackets.empty()) valid = false;
    cout << (valid ? "YES" : "NO") << '\n';  // YES

    return 0;
}
```

### 3.2 Queue — First In, First Out

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    queue<int> q;

    // === PUSH (tambah ke belakang) ===
    q.push(10);  // queue: [10]
    q.push(20);  // queue: [10, 20]
    q.push(30);  // queue: [10, 20, 30]
    //             front↑          ↑back

    // === FRONT & BACK ===
    cout << q.front() << '\n';  // 10 (depan)
    cout << q.back() << '\n';   // 30 (belakang)

    // === POP (hapus dari depan) ===
    q.pop();     // queue: [20, 30]
    cout << q.front() << '\n';  // 20

    // === SIZE & EMPTY ===
    cout << q.size() << '\n';  // 2

    // ================================================
    // USE CASE: SIMULASI ANTRIAN
    // ================================================
    // N orang antri, setiap orang butuh waktu t[i]
    // Cetak waktu selesai masing-masing
    int n = 4;
    int times[] = {3, 2, 5, 1};
    queue<pair<int,int>> antrian;  // (id, waktu_proses)

    for (int i = 0; i < n; i++) {
        antrian.push({i + 1, times[i]});
    }

    int current_time = 0;
    while (!antrian.empty()) {
        auto [id, t] = antrian.front();
        antrian.pop();
        current_time += t;
        cout << "Person " << id << " done at time " << current_time << '\n';
    }

    return 0;
}
```

### 3.3 Deque — Double-Ended Queue

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    deque<int> dq;

    // === PUSH dari kedua sisi ===
    dq.push_back(2);    // dq: [2]
    dq.push_back(3);    // dq: [2, 3]
    dq.push_front(1);   // dq: [1, 2, 3]
    dq.push_front(0);   // dq: [0, 1, 2, 3]

    // === AKSES ===
    cout << dq.front() << '\n';  // 0
    cout << dq.back() << '\n';   // 3
    cout << dq[2] << '\n';       // 2 (random access!)

    // === POP dari kedua sisi ===
    dq.pop_front();  // dq: [1, 2, 3]
    dq.pop_back();   // dq: [1, 2]

    // === SIZE ===
    cout << dq.size() << '\n';  // 2

    // ================================================
    // USE CASE: SLIDING WINDOW MAXIMUM (Monotonic Deque)
    // ================================================
    // Cari maximum di setiap window berukuran K
    vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    deque<int> window;  // simpan INDEX, bukan value
    // Invariant: dq menyimpan index secara decreasing value
    //            dq.front() = index elemen terbesar di window

    for (int i = 0; i < (int)arr.size(); i++) {
        // Hapus elemen yang sudah keluar window
        while (!window.empty() && window.front() <= i - k) {
            window.pop_front();
        }
        // Hapus elemen dari belakang yang lebih kecil dari arr[i]
        // (mereka tidak akan pernah jadi maximum lagi)
        while (!window.empty() && arr[window.back()] <= arr[i]) {
            window.pop_back();
        }
        window.push_back(i);

        // Output maximum window (mulai saat window penuh)
        if (i >= k - 1) {
            cout << arr[window.front()] << ' ';
        }
    }
    // Output: 3 3 5 5 6 7
    cout << '\n';

    return 0;
}
```

### 3.4 Priority Queue — Heap

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // === MAX HEAP (default) ===
    priority_queue<int> max_pq;
    max_pq.push(3);
    max_pq.push(1);
    max_pq.push(4);
    max_pq.push(1);
    max_pq.push(5);

    cout << max_pq.top() << '\n';  // 5 (maximum)
    max_pq.pop();
    cout << max_pq.top() << '\n';  // 4

    // === MIN HEAP ===
    priority_queue<int, vector<int>, greater<int>> min_pq;
    min_pq.push(3);
    min_pq.push(1);
    min_pq.push(4);

    cout << min_pq.top() << '\n';  // 1 (minimum)
    min_pq.pop();
    cout << min_pq.top() << '\n';  // 3

    // === HEAP DENGAN PAIR ===
    // Default: sort by first (max), lalu second (max)
    priority_queue<pair<int,int>> pq;
    pq.push({5, 100});
    pq.push({3, 200});
    pq.push({5, 50});

    cout << pq.top().first << ' ' << pq.top().second << '\n';  // 5 100
    pq.pop();
    cout << pq.top().first << ' ' << pq.top().second << '\n';  // 5 50

    // === MIN HEAP TRICK (negate values) ===
    // Daripada greater<>, bisa juga negate:
    priority_queue<int> pq2;
    pq2.push(-3);  // sebenarnya 3
    pq2.push(-1);  // sebenarnya 1
    pq2.push(-4);  // sebenarnya 4
    cout << -pq2.top() << '\n';  // 1 (min dari {1,3,4})

    // ================================================
    // USE CASE: TOP K SMALLEST ELEMENTS
    // ================================================
    vector<int> arr = {7, 2, 9, 1, 5, 8, 3};
    int K = 3;
    
    priority_queue<int> topK;  // max heap, simpan K terkecil
    for (int x : arr) {
        topK.push(x);
        if ((int)topK.size() > K) {
            topK.pop();  // buang yang terbesar
        }
    }
    // topK berisi: {1, 2, 3} — tiga terkecil
    while (!topK.empty()) {
        cout << topK.top() << ' ';  // 3 2 1
        topK.pop();
    }
    cout << '\n';

    return 0;
}
```

### 3.5 Perbandingan: Stack vs Deque vs Vector

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    // Stack BISA disimulasi dengan vector:
    vector<int> v_stack;
    v_stack.push_back(1);   // push
    v_stack.back();         // top
    v_stack.pop_back();     // pop

    // Keuntungan vector sebagai stack: bisa iterasi & random access
    // Keuntungan stack<>: interface lebih jelas, niat kode lebih readable

    // Queue BISA disimulasi dengan deque:
    deque<int> d_queue;
    d_queue.push_back(1);   // enqueue
    d_queue.front();        // front
    d_queue.pop_front();    // dequeue

    // Di CP, sering pakai deque langsung (lebih fleksibel dari queue)

    return 0;
}
```

---

## 🔄 4. Trace / Simulasi

### Trace: Bracket Matching dengan Stack

```
Input: "({[]})"

Char | Action          | Stack State  | Valid?
-----|-----------------|--------------|-------
'('  | push '('        | ['(']        | ✓
'{'  | push '{'        | ['(', '{']   | ✓
'['  | push '['        | ['(', '{', '['] | ✓
']'  | top='[', match! | ['(', '{']   | ✓
'}'  | top='{', match! | ['(']        | ✓
')'  | top='(', match! | []           | ✓

End: stack empty → VALID ✓
```

```
Input: "({[})"

Char | Action          | Stack State  | Valid?
-----|-----------------|--------------|-------
'('  | push '('        | ['(']        | ✓
'{'  | push '{'        | ['(', '{']   | ✓
'['  | push '['        | ['(', '{', '['] | ✓
'}'  | top='[' ≠ '{'  | —            | ✗ INVALID!
```

### Trace: Sliding Window Maximum (Deque)

```
Array: [1, 3, -1, -3, 5, 3, 6, 7], K=3
Deque stores INDICES. Invariant: arr[dq.front()] >= arr[dq[1]] >= ...

i=0, arr[0]=1:  dq=[0]                         (window belum penuh)
i=1, arr[1]=3:  pop 0 (arr[0]=1 < 3), dq=[1]   (window belum penuh)
i=2, arr[2]=-1: dq=[1, 2]                      → max=arr[1]=3
i=3, arr[3]=-3: dq=[1, 2, 3]                   → max=arr[1]=3
i=4, arr[4]=5:  pop front 1 (out of window)
                pop 3,2 (arr<5), dq=[4]         → max=arr[4]=5
i=5, arr[5]=3:  dq=[4, 5]                      → max=arr[4]=5
i=6, arr[6]=6:  pop 5,4 (arr<6), dq=[6]        → max=arr[6]=6
i=7, arr[7]=7:  pop 6 (arr<7), dq=[7]          → max=arr[7]=7

Output: 3 3 5 5 6 7
```

### Trace: Priority Queue (Max Heap)

```
Operasi              | Heap State (conceptual) | top()
---------------------|-------------------------|------
push(3)              | [3]                     | 3
push(1)              | [3, 1]                  | 3
push(5)              | [5, 1, 3]              | 5
push(2)              | [5, 2, 3, 1]           | 5
pop()                | [3, 2, 1]              | 3
push(4)              | [4, 2, 3, 1]           | 4
pop()                | [3, 2, 1]              | 3
```

---

## 📝 5. Variasi & Pattern

### Pattern 1: Bracket Matching (Stack)

```cpp
bool isValid(string s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else {
            if (st.empty()) return false;
            char t = st.top(); st.pop();
            if (c == ')' && t != '(') return false;
            if (c == '}' && t != '{') return false;
            if (c == ']' && t != '[') return false;
        }
    }
    return st.empty();
}
```

### Pattern 2: Next Greater Element (Monotonic Stack)

```cpp
// Untuk setiap elemen, cari elemen PERTAMA di kanannya yang LEBIH BESAR
vector<int> nextGreater(vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n, -1);
    stack<int> st;  // simpan index

    for (int i = 0; i < n; i++) {
        while (!st.empty() && arr[st.top()] < arr[i]) {
            result[st.top()] = arr[i];
            st.pop();
        }
        st.push(i);
    }
    return result;
}
// Input:  [4, 5, 2, 10, 8]
// Output: [5, 10, 10, -1, -1]
```

### Pattern 3: K Largest Elements (Max Heap + Pop)

```cpp
// Cari K elemen terbesar
priority_queue<int> pq(arr.begin(), arr.end());
for (int i = 0; i < k; i++) {
    cout << pq.top() << ' ';
    pq.pop();
}
```

### Pattern 4: Merge K Sorted Arrays (Min Heap)

```cpp
// Min heap: (value, array_index, element_index)
priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;
// Push first element of each array
for (int i = 0; i < k; i++) {
    pq.push({arrays[i][0], i, 0});
}
while (!pq.empty()) {
    auto [val, arr_i, elem_i] = pq.top(); pq.pop();
    cout << val << ' ';
    if (elem_i + 1 < arrays[arr_i].size()) {
        pq.push({arrays[arr_i][elem_i+1], arr_i, elem_i+1});
    }
}
```

### Pattern 5: Sliding Window Maximum (Monotonic Deque)

```cpp
// Deque maintains decreasing order of values (stores indices)
deque<int> dq;
for (int i = 0; i < n; i++) {
    while (!dq.empty() && dq.front() <= i - k) dq.pop_front();
    while (!dq.empty() && arr[dq.back()] <= arr[i]) dq.pop_back();
    dq.push_back(i);
    if (i >= k - 1) cout << arr[dq.front()] << ' ';
}
```

---

## ⚠️ 6. Common Mistakes & Edge Cases

### Mistake 1: Pop/Top pada Container Kosong

```cpp
stack<int> st;
// ⚠️ BAHAYA: Undefined Behavior!
cout << st.top();  // UB!
st.pop();          // UB!

// ✅ BENAR: selalu cek empty() dulu
if (!st.empty()) {
    cout << st.top();
    st.pop();
}
```

### Mistake 2: Priority Queue Default = MAX

```cpp
priority_queue<int> pq;
pq.push(1); pq.push(5); pq.push(3);
cout << pq.top();  // 5 (BUKAN 1!)

// Untuk MIN heap:
priority_queue<int, vector<int>, greater<int>> min_pq;
// Atau trick negate:
pq.push(-1); pq.push(-5); pq.push(-3);
cout << -pq.top();  // 1 (minimum)
```

### Mistake 3: Queue/Stack pop() Return VOID

```cpp
queue<int> q;
q.push(42);
// ⚠️ SALAH:
// int x = q.pop();  // COMPILE ERROR! pop() return void

// ✅ BENAR:
int x = q.front();  // ambil dulu
q.pop();            // baru pop
```

### Mistake 4: Deque Index Out of Bounds

```cpp
deque<int> dq = {1, 2, 3};
// dq[5] → Undefined Behavior (sama seperti vector)
// Selalu pastikan index valid!
```

### Edge Cases

- **String kosong** → bracket matching = valid (stack tetap kosong)
- **K = 1** → sliding window max = array itu sendiri
- **Semua elemen sama** → monotonic stack/deque langsung kosong per pop
- **N = 1** → hanya satu elemen, tidak ada next greater

---

## 🏆 7. Tips Contest

### Decision Quick Reference

| Mau apa? | Pakai |
|----------|-------|
| Bracket matching | Stack |
| Undo/redo | Stack |
| Next greater/smaller | Monotonic Stack |
| BFS | Queue |
| Proses FIFO | Queue |
| Sliding window min/max | Monotonic Deque |
| Selalu ambil max/min | Priority Queue |
| Top-K elements | Priority Queue (size K) |
| Dijkstra | Priority Queue (min heap) |

### Red Flags di Soal

- "Periksa apakah valid/balanced" → **Stack** (bracket matching)
- "Untuk setiap elemen, cari yang terdekat lebih besar/kecil" → **Monotonic Stack**
- "Maximum/minimum di setiap window ukuran K" → **Monotonic Deque**
- "Proses yang paling urgent/besar/kecil dulu" → **Priority Queue**
- "Antrian, giliran, round-robin" → **Queue**

### Performance Tips

```cpp
// 1. Priority queue dari vector (bulk construct O(n)):
vector<int> v = {3,1,4,1,5};
priority_queue<int> pq(v.begin(), v.end());  // O(n), bukan O(n log n)!

// 2. Lazy deletion di priority queue:
// Jika butuh "delete arbitrary element" tapi pakai PQ:
// Tandai elemen sebagai "deleted", skip saat pop
priority_queue<int> pq;
set<int> deleted;
// Saat pop: while (deleted.count(pq.top())) { pq.pop(); deleted.erase(...); }

// 3. Deque sebagai pengganti queue DAN stack:
// Deque bisa semua yang stack/queue bisa + random access
```

---

## 📌 8. Ringkasan

### Key Points

1. **Stack (LIFO)**: bracket matching, next greater, undo — `push/pop/top`
2. **Queue (FIFO)**: BFS, antrian, scheduling — `push/pop/front/back`
3. **Deque**: sliding window, double-ended ops — `push_front/back, pop_front/back, [i]`
4. **Priority Queue (Heap)**: greedy, top-K, Dijkstra — `push/pop/top`, O(log n) insert/delete
5. **Monotonic Stack/Deque**: teknik kunci untuk range problems O(n)

### Cheatsheet Singkat

```cpp
// STACK: push(x), pop(), top(), empty()
// QUEUE: push(x), pop(), front(), back(), empty()
// DEQUE: push_front/back(x), pop_front/back(), front(), back(), [i]
// PQ MAX: priority_queue<int> pq; push/pop/top
// PQ MIN: priority_queue<int, vector<int>, greater<int>> pq;
```

### Link Soal Latihan Online Judge

| Platform | Problem | Topik |
|----------|---------|-------|
| CSES | Sliding Window (Sliding Cost/Median) | Deque/Multiset |
| CF 1279B | Brackets | Stack |
| CF 1092C | Good String | Stack |
| CSES | Room Allocation | Priority Queue |
| LeetCode 239 | Sliding Window Maximum | Deque |
| LeetCode 20 | Valid Parentheses | Stack |
| LeetCode 232 | Implement Queue using Stacks | Stack+Queue |
