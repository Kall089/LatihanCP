# Day 39 — Priority Queue & Heap Applications

## Tujuan Pembelajaran

- [ ] Memahami max-heap vs min-heap dan kompleksitas operasinya
- [ ] Menggunakan min-heap ukuran K untuk Kth Largest Element
- [ ] Merge K sorted lists dengan min-heap dalam O(N log K)
- [ ] Mengimplementasikan CPU Task Scheduler dengan max-heap greedy
- [ ] Membangun MedianFinder dengan dua heap (lower & upper half)
- [ ] Mengimplementasikan Dijkstra's Algorithm dengan priority queue

---

## Struktur Folder

```
Day-39 (Priority Queue and Heap)/
├── README.md
├── teori/
│   ├── Day_39_Teori_Lengkap.md       ← Baca ini dulu!
│   ├── generate_presentation.py      ← Script generate PPT
│   └── Day_39_Presentation.pptx     ← Presentasi 15 slide
├── latihan/
│   ├── exercise_1.cpp  ← Kth Largest Element
│   ├── exercise_2.cpp  ← Merge K Sorted Lists
│   ├── exercise_3.cpp  ← Task Scheduler
│   ├── exercise_4.cpp  ← Find Median from Stream
│   ├── exercise_5.cpp  ← K Closest Points to Origin
│   └── exercise_6.cpp  ← Dijkstra's Shortest Path
├── solusi/
│   ├── solution_1.cpp through solution_6.cpp
├── tugas/
│   ├── tugas_01.cpp through tugas_15.cpp
└── template/
    └── template.cpp
```

---

## Panduan Belajar

1. **Baca teori** → `teori/Day_39_Teori_Lengkap.md` (atau buka PPT)
2. **Kerjakan latihan** → Isi bagian `// TODO` di folder `latihan/`
3. **Cek solusi** → Lihat `solusi/` jika stuck (coba sendiri dulu!)
4. **Kerjakan tugas** → 15 soal di folder `tugas/` (tanpa solusi)
5. **Online Judge** → Lihat rekomendasi soal di bawah

---

## Exercises

| File | Topik | Difficulty |
|------|-------|------------|
| exercise_1.cpp | Kth Largest Element in Array | Core |
| exercise_2.cpp | Merge K Sorted Lists | Core |
| exercise_3.cpp | Task Scheduler (CPU Cooldown) | Core |
| exercise_4.cpp | Find Median from Data Stream | Challenge |
| exercise_5.cpp | K Closest Points to Origin | Core |
| exercise_6.cpp | Dijkstra's Shortest Path | Challenge |

---

## Tugas (15 soal)

| Soal | Topik | Difficulty |
|------|-------|------------|
| tugas_01 | Kth Smallest in Sorted Matrix | Easy |
| tugas_02 | Last Stone Weight | Easy |
| tugas_03 | Connect Ropes Min Cost | Easy |
| tugas_04 | Reorganize String | Easy |
| tugas_05 | K Most Frequent Elements | Medium |
| tugas_06 | Minimum Cost to Hire K Workers | Medium |
| tugas_07 | Ugly Number II | Medium |
| tugas_08 | IPO — Maximize Capital | Medium |
| tugas_09 | Meeting Rooms II | Medium |
| tugas_10 | Sliding Window Median | Medium |
| tugas_11 | Trapping Rain Water II (3D) | Hard |
| tugas_12 | Find K Pairs Smallest Sums | Hard |
| tugas_13 | Swim in Rising Water | Hard |
| tugas_14 | Design Twitter Feed | Hard |
| tugas_15 | Minimum Deviation in Array | Hard |

---

## Soal Online Judge

| Platform | Problem | Topik |
|----------|---------|-------|
| LC 215   | Kth Largest Element in Array | Min-heap K |
| LC 23    | Merge K Sorted Lists | Min-heap |
| LC 621   | Task Scheduler | Max-heap greedy |
| LC 295   | Find Median from Data Stream | Dua heap |
| LC 973   | K Closest Points to Origin | Max-heap K |
| CSES     | Shortest Routes I | Dijkstra |
| LC 743   | Network Delay Time | Dijkstra |
| LC 347   | Top K Frequent Elements | Min-heap K |

---

## Common Mistakes

1. **Kth Largest vs Smallest terbalik** → Largest → min-heap K, Smallest → max-heap K
2. **Lupa skip stale entry di Dijkstra** → `if (d > dist[u]) continue;` wajib ada
3. **MedianFinder: size invariant** → `maxH.size() >= minH.size()` (bukan sebaliknya)
4. **Merge K: push seluruh list** → hanya push satu elemen berikutnya
5. **Dijkstra untuk bobot negatif** → tidak valid, gunakan Bellman-Ford

---

## Quick Cheatsheet

```cpp
// Min-heap
priority_queue<int, vector<int>, greater<int>> minPQ;

// Kth Largest — min-heap ukuran K
for (int x : A) { minPQ.push(x); if (minPQ.size() > k) minPQ.pop(); }
// → minPQ.top() = Kth Largest

// MedianFinder — dua heap
maxH.push(x); minH.push(maxH.top()); maxH.pop();
if (maxH.size() < minH.size()) { maxH.push(minH.top()); minH.pop(); }
// median = maxH.size() > minH.size() ? maxH.top() : (maxH.top()+minH.top())/2.0

// Dijkstra — stale skip
priority_queue<pair<ll,int>, vector<pair<ll,int>>, greater<>> pq;
pq.push({0, src});
while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue; // skip stale!
    for (auto [v, w] : adj[u])
        if (dist[u]+w < dist[v]) { dist[v]=dist[u]+w; pq.push({dist[v],v}); }
}
```
