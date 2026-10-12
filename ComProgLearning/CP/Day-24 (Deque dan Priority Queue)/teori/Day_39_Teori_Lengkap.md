# Day 39 — Priority Queue & Heap Applications

## Tujuan Pembelajaran
- [ ] Memahami struktur heap dan kompleksitasnya
- [ ] Menguasai `priority_queue` C++ (max-heap & min-heap)
- [ ] Menggunakan max-heap berukuran K untuk Kth Largest/Smallest
- [ ] Merge K sorted lists dengan min-heap
- [ ] Implementasi MedianFinder dengan dua heap
- [ ] Mengaplikasikan Dijkstra's Algorithm dengan priority queue

---

## 1. Heap — Review Cepat

Heap adalah complete binary tree dengan properti:
- **Max-heap**: setiap node ≥ anaknya → root = maksimum
- **Min-heap**: setiap node ≤ anaknya → root = minimum

### Kompleksitas
| Operasi | Heap | Array | BST |
|---------|------|-------|-----|
| Insert | O(log n) | O(1) amort | O(log n) |
| Get max/min | O(1) | O(n) | O(log n) |
| Delete max/min | O(log n) | O(n) | O(log n) |
| Build | O(n) | - | O(n log n) |

---

## 2. `priority_queue` di C++

```cpp
#include <queue>
using namespace std;

// Max-heap (default) — top() = maksimum
priority_queue<int> maxPQ;
maxPQ.push(x);   // O(log n)
maxPQ.top();     // O(1) — lihat max
maxPQ.pop();     // O(log n) — hapus max
maxPQ.size();    // O(1)
maxPQ.empty();   // O(1)

// Min-heap — top() = minimum
priority_queue<int, vector<int>, greater<int>> minPQ;

// Custom comparator — pair: sort by first ascending
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
```

---

## 3. Pola Umum: K-th Largest (Min-Heap Ukuran K)

**Masalah**: Temukan elemen terbesar ke-K.

**Kunci**: Pertahankan min-heap ukuran K. Elemen terkecil di heap adalah Kth largest.

```cpp
int kthLargest(vector<int>& A, int k) {
    priority_queue<int, vector<int>, greater<int>> minPQ;
    for (int x : A) {
        minPQ.push(x);
        if ((int)minPQ.size() > k) minPQ.pop(); // buang yang terkecil
    }
    return minPQ.top(); // top = Kth largest
}
```

**Kenapa min-heap?** Kita ingin membuang yang lebih kecil → hapus minimum → min-heap.

**K-th Smallest**: gunakan max-heap ukuran K, pop saat > K.

---

## 4. Merge K Sorted Lists

**Strategi**: Gunakan min-heap yang menyimpan `(nilai, list_idx, elemen_idx)`.

```cpp
// min-heap: (nilai, list_idx, elemen_idx)
priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<>> pq;

// Inisialisasi: masukkan elemen pertama tiap list
for (int i = 0; i < K; i++)
    if (!lists[i].empty())
        pq.push({lists[i][0], i, 0});

while (!pq.empty()) {
    auto [val, li, ei] = pq.top(); pq.pop();
    result.push_back(val);
    if (ei + 1 < (int)lists[li].size())
        pq.push({lists[li][ei+1], li, ei+1}); // next dari list yang sama
}
```

**Kompleksitas**: O(N log K), N = total elemen, K = jumlah list.

---

## 5. Median dari Data Stream (Dua Heap)

**Masalah**: Tambah angka kapan saja, query median kapan saja.

**Ide**: Gunakan dua heap untuk membagi array menjadi dua bagian:
- `maxHeap`: lower half (setengah bawah)
- `minHeap`: upper half (setengah atas)

**Invariant**: `|maxH| == |minH|` atau `|maxH| == |minH| + 1`
Maka: median = `maxH.top()` (ganjil) atau `(maxH.top() + minH.top()) / 2.0` (genap)

```cpp
struct MedianFinder {
    priority_queue<int> maxH;                           // lower half
    priority_queue<int, vector<int>, greater<int>> minH; // upper half

    void addNum(int num) {
        maxH.push(num);
        // Selalu kirim top maxH ke minH
        minH.push(maxH.top()); maxH.pop();
        // Balance: maxH.size() >= minH.size()
        if (maxH.size() < minH.size()) {
            maxH.push(minH.top()); minH.pop();
        }
    }

    double findMedian() {
        if (maxH.size() > minH.size()) return maxH.top();
        return (maxH.top() + minH.top()) / 2.0;
    }
};
```

### Trace
Insert 1, 2, 3:
- Insert 1: maxH=[1], minH=[]
- Insert 2: maxH=[1], minH=[2] (balanced)
- Insert 3: maxH=[2,1], minH=[3] → median = 2

---

## 6. Dijkstra dengan Priority Queue

**Masalah**: Shortest path dari source ke semua node (graph berbobot positif).

```cpp
const ll INF = 1e18;
vector<ll> dijkstra(int s, int n, vector<vector<pair<int,int>>>& adj) {
    vector<ll> dist(n+1, INF);
    dist[s] = 0;

    // min-heap: (dist, node)
    priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue; // stale entry — skip!

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
```

**Kenapa `if (d > dist[u]) continue`?**
Priority queue bisa menyimpan entri lama (stale). Saat entri lama di-pop, kita sudah punya jalur lebih pendek → skip.

**Kompleksitas**: O((V + E) log V)

---

## 7. Task Scheduler

**Masalah**: Eksekusi task dengan cooldown n. Temukan waktu minimum.

**Strategi**: Setiap ronde (n+1 slot):
1. Ambil task dengan frekuensi tertinggi (max-heap)
2. Eksekusi n+1 task (atau idle jika heap kosong sebelum n+1)
3. Kembalikan task yang belum selesai ke heap

```cpp
int leastInterval(vector<char>& tasks, int n) {
    int freq[26] = {};
    for (char c : tasks) freq[c-'A']++;
    priority_queue<int> maxPQ;
    for (int f : freq) if (f) maxPQ.push(f);

    int time = 0;
    while (!maxPQ.empty()) {
        vector<int> temp;
        int cycle = n + 1;
        while (cycle-- && !maxPQ.empty()) {
            int f = maxPQ.top(); maxPQ.pop();
            if (f > 1) temp.push_back(f-1);
            time++;
        }
        for (int f : temp) maxPQ.push(f);
        if (!maxPQ.empty()) time += cycle + 1; // idle slots
    }
    return time;
}
```

---

## 8. Common Mistakes

1. **Max-heap vs Min-heap terbalik**
   - Kth Largest → min-heap ukuran K (pop yang lebih kecil)
   - Kth Smallest → max-heap ukuran K (pop yang lebih besar)

2. **Lupa skip stale entry di Dijkstra**
   - `if (d > dist[u]) continue;` sangat penting untuk efisiensi

3. **MedianFinder: invariant size terbalik**
   - maxH harus ≥ minH (bukan sebaliknya)
   - Jika minH > maxH, pindah dari minH ke maxH

4. **Merge K lists: push elemen berikutnya, bukan seluruh list**
   - Hanya push `lists[li][ei+1]`, bukan semua elemen list itu

5. **Custom comparator: greater<> vs less<>**
   - `priority_queue<..., greater<>>` → min-heap
   - `priority_queue<..., less<>>` atau default → max-heap

---

## 9. Kompleksitas

| Algoritma | Waktu | Ruang |
|-----------|-------|-------|
| Kth Largest/Smallest | O(n log k) | O(k) |
| Merge K Sorted Lists | O(N log K) | O(K) |
| MedianFinder (add) | O(log n) | O(n) |
| MedianFinder (median) | O(1) | - |
| Dijkstra | O((V+E) log V) | O(V+E) |
| Task Scheduler | O(n log 26) | O(26) |

---

## 10. Soal Online Judge

| Platform | Problem | Topik |
|----------|---------|-------|
| LC 215 | Kth Largest Element | Min-heap size K |
| LC 23 | Merge K Sorted Lists | Min-heap |
| LC 295 | Find Median from Data Stream | Dua heap |
| CSES | Shortest Routes I | Dijkstra |
| LC 621 | Task Scheduler | Max-heap greedy |
| LC 973 | K Closest Points | Max-heap |
| LC 347 | Top K Frequent Elements | Min-heap |
| LC 1046 | Last Stone Weight | Max-heap |
