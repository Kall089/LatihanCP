# Day 38 — Queue & Deque Applications

## Tujuan Pembelajaran
- [ ] Memahami Queue FIFO dan operasi dasar di C++
- [ ] Memahami Deque (Double-Ended Queue) dan kegunaannya
- [ ] Mengimplementasikan Sliding Window Maximum dalam O(n)
- [ ] Mengimplementasikan Sliding Window Minimum dalam O(n)
- [ ] Memecahkan First Non-Repeating Character in Stream
- [ ] Menggunakan Queue untuk BFS Level Order Traversal

---

## 1. Queue — Review

Queue adalah struktur data FIFO (First In, First Out).

```cpp
queue<int> q;
q.push(x);    // O(1) — tambah ke belakang
q.pop();      // O(1) — hapus dari depan
q.front();    // O(1) — lihat elemen paling depan
q.back();     // O(1) — lihat elemen paling belakang
q.empty();    // O(1) — cek kosong
q.size();     // O(1) — jumlah elemen
```

### Kapan Pakai Queue?
| Pola Soal | Teknik |
|-----------|--------|
| BFS / Level-order traversal | Queue standar |
| Simulasi antrian proses | Queue standar |
| Character stream processing | Queue + freq array |
| Sliding window dengan ordered structure | Deque |

---

## 2. Deque — Double-Ended Queue

Deque mendukung push/pop di **kedua ujung** dalam O(1).

```cpp
deque<int> dq;
dq.push_front(x);  // O(1) — tambah ke depan
dq.push_back(x);   // O(1) — tambah ke belakang
dq.pop_front();    // O(1) — hapus dari depan
dq.pop_back();     // O(1) — hapus dari belakang
dq.front();        // O(1) — lihat elemen depan
dq.back();         // O(1) — lihat elemen belakang
dq.empty();        // O(1) — cek kosong
```

### Deque sebagai Stack
```cpp
dq.push_back(x);   // push
dq.pop_back();     // pop
dq.back();         // top
```

### Deque sebagai Queue
```cpp
dq.push_back(x);   // enqueue
dq.pop_front();    // dequeue
dq.front();        // peek
```

---

## 3. Sliding Window Maximum

### Masalah
Diberikan array dan window size k, temukan maksimum di setiap window.

### Ide: Monotonic Decreasing Deque
Pertahankan deque yang menyimpan **index** dalam urutan **menurun** berdasarkan nilai.

**Invariant**: `dq.front()` selalu merupakan index maksimum di window saat ini.

```cpp
vector<int> slidingWindowMax(vector<int>& A, int k) {
    int n = A.size();
    deque<int> dq; // menyimpan index, nilai turun dari depan ke belakang
    vector<int> res;

    for (int i = 0; i < n; i++) {
        // Hapus index yang sudah keluar dari window
        while (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();

        // Hapus index dari belakang yang nilainya ≤ A[i]
        while (!dq.empty() && A[dq.back()] <= A[i])
            dq.pop_back();

        dq.push_back(i);

        // Window sudah penuh
        if (i >= k - 1)
            res.push_back(A[dq.front()]);
    }
    return res;
}
```

### Trace: `A = [1,3,-1,-3,5,3,6,7]`, `k = 3`

| i | A[i] | Deque (index) | Max |
|---|------|---------------|-----|
| 0 | 1    | [0]           | -   |
| 1 | 3    | [1]           | -   |
| 2 | -1   | [1,2]         | 3   |
| 3 | -3   | [1,2,3]       | 3   |
| 4 | 5    | [4]           | 5   |
| 5 | 3    | [4,5]         | 5   |
| 6 | 6    | [6]           | 6   |
| 7 | 7    | [7]           | 7   |

Output: `[3, 3, 5, 5, 6, 7]`

**Kompleksitas**: O(n) — setiap elemen push dan pop tepat sekali.

---

## 4. Sliding Window Minimum

Sama dengan maximum, tapi pertahankan deque **increasing** (nilai naik dari depan ke belakang).

```cpp
vector<int> slidingWindowMin(vector<int>& A, int k) {
    int n = A.size();
    deque<int> dq;
    vector<int> res;

    for (int i = 0; i < n; i++) {
        while (!dq.empty() && dq.front() <= i - k)
            dq.pop_front();

        // Hapus dari belakang yang nilainya >= A[i] (berbeda dari max!)
        while (!dq.empty() && A[dq.back()] >= A[i])
            dq.pop_back();

        dq.push_back(i);

        if (i >= k - 1)
            res.push_back(A[dq.front()]);
    }
    return res;
}
```

---

## 5. First Non-Repeating Character in Stream

### Masalah
Diberikan stream karakter, setiap kali karakter baru masuk, cetak karakter pertama yang belum berulang (atau `#` jika tidak ada).

### Algoritma
- Gunakan Queue untuk melacak urutan masuk karakter
- Gunakan `freq[26]` untuk menghitung frekuensi
- Pop dari depan queue jika frekuensi karakter sudah > 1

```cpp
string firstNonRepeating(string stream) {
    queue<char> q;
    int freq[26] = {};
    string ans;

    for (char c : stream) {
        freq[c - 'a']++;
        q.push(c);

        // Hapus karakter yang sudah duplikat dari depan
        while (!q.empty() && freq[q.front() - 'a'] > 1)
            q.pop();

        ans += q.empty() ? '#' : q.front();
    }
    return ans;
}
```

### Trace: `stream = "aabcc"`

| i | c   | Queue       | freq         | Ans  |
|---|-----|-------------|--------------|------|
| 0 | 'a' | [a]         | a=1          | a    |
| 1 | 'a' | []          | a=2 (pop a)  | #    |
| 2 | 'b' | [b]         | b=1          | b    |
| 3 | 'c' | [b,c]       | c=1          | b    |
| 4 | 'c' | [b]         | c=2 (pop c)  | b    |

Output: `"a#bbb"` → `"a#bb"` wait... output: `"a#bbb"`

---

## 6. BFS Level Order Traversal

Queue adalah struktur alami untuk BFS. Level order traversal:

```cpp
vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if (!root) return res;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int sz = q.size(); // ukuran level saat ini
        vector<int> level;
        for (int i = 0; i < sz; i++) {
            TreeNode* node = q.front(); q.pop();
            level.push_back(node->val);
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
        res.push_back(level);
    }
    return res;
}
```

### Diagram BFS Level Order

```
        1          ← Level 0: [1]
       / \
      2   3        ← Level 1: [2, 3]
     / \   \
    4   5   6      ← Level 2: [4, 5, 6]
```

Queue state:
- Awal: [1]
- Setelah level 0: [2, 3]
- Setelah level 1: [4, 5, 6]

---

## 7. Kompleksitas

| Algoritma | Waktu | Ruang | Catatan |
|-----------|-------|-------|---------|
| Sliding Window Max | O(n) | O(k) | Deque monotonic decreasing |
| Sliding Window Min | O(n) | O(k) | Deque monotonic increasing |
| First Non-Repeating | O(n) | O(n) | Queue + freq array |
| BFS Level Order | O(n) | O(n) | Queue standar |
| Round-Robin Sim | O(n×t) | O(n) | Queue simulasi |

---

## 8. Common Mistakes

1. **Sliding Window: lupa hapus index di luar window**
   - `dq.front() <= i - k` → hapus dari depan
   - Ini HARUS dilakukan SEBELUM compare nilai

2. **Min vs Max: arah perbandingan terbalik**
   - Max: pop belakang jika `A[dq.back()] <= A[i]`
   - Min: pop belakang jika `A[dq.back()] >= A[i]`

3. **BFS: proses semua node di level yang sama**
   - Simpan `sz = q.size()` di awal level, loop `sz` kali
   - Jangan cek `!q.empty()` sebagai kondisi inner loop

4. **First Non-Repeating: pop sampai bersih**
   - `while (!q.empty() && freq[q.front()] > 1) q.pop()`
   - Loop while (bukan if) karena bisa ada beberapa duplikat berturut-turut

5. **Deque index: jangan simpan nilai saat butuh index**
   - Sliding window selalu simpan **index**, bukan nilai langsung

---

## 9. Soal Online Judge

| Platform | Problem | Topik |
|----------|---------|-------|
| LC 239 | Sliding Window Maximum | Deque monotonic |
| CSES | Sliding Median | Sliding window |
| LC 933 | Number of Recent Calls | Queue |
| GFG | First non-repeating character | Queue + freq |
| LC 102 | Binary Tree Level Order | BFS Queue |
| LC 862 | Shortest Subarray with Sum ≥ K | Deque monotonic |
| LC 1438 | Longest Subarray with Abs Diff ≤ K | Deque min & max |
