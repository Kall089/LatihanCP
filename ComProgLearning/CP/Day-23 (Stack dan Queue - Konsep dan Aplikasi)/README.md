# 📦 Day 5: STL Containers 3 — Stack, Queue, Deque, Priority_Queue

**Hari**: Day 5 dari 150 Hari Competitive Programming  
**Topik**: Container Adaptor & Double-Ended Queue  
**Prerequisites**: Day 3-4 (vector, set, map)  
**Difficulty**: ⭐⭐ (Beginner-Intermediate)

---

## 🎯 Learning Objectives

Setelah menyelesaikan Day 5, kamu harus bisa:
- [ ] Menggunakan `stack` (LIFO) untuk bracket matching, undo, dll.
- [ ] Menggunakan `queue` (FIFO) untuk BFS-like processing
- [ ] Menggunakan `deque` untuk operasi dua ujung
- [ ] Menggunakan `priority_queue` (heap) untuk greedy/scheduling
- [ ] Mengetahui kapan pakai container adaptor mana

---

## 📚 Struktur Folder

```
Day-5 (STL Containers 3 - Stack, Queue, Deque, Priority_Queue)/
├── teori/
│   └── Day_5_Teori_Lengkap.md   ← Baca ini PERTAMA
├── latihan/
│   ├── exercise_1.cpp  (Warm-up: Bracket matching — Stack)
│   ├── exercise_2.cpp  (Warm-up: Queue simulation)
│   ├── exercise_3.cpp  (Core: Reverse with stack)
│   ├── exercise_4.cpp  (Core: Priority queue — top K)
│   ├── exercise_5.cpp  (Challenge: Deque — sliding window max)
│   └── exercise_6.cpp  (Contest-level: Stack — next greater element)
├── solusi/
│   ├── solution_1.cpp ~ solution_6.cpp
├── tugas/
│   ├── tugas_01.cpp ~ tugas_15.cpp (TANPA solusi!)
├── template/
│   └── template.cpp
└── README.md  ← Kamu di sini
```

---

## 📖 Step-by-Step Learning Guide

### Langkah 1: Baca Teori (30-45 menit)
1. Stack: LIFO, kapan digunakan, operasi dasar
2. Queue: FIFO, BFS, task scheduling
3. Deque: double-ended, sliding window
4. Priority Queue: max-heap default, min-heap trick

### Langkah 2: Kerjakan Exercise (60-90 menit)
- Exercise 1-2: warm-up (langsung dari teori)
- Exercise 3-4: perlu pemahaman lebih dalam
- Exercise 5-6: challenge (kombinasi konsep)

### Langkah 3: Kerjakan Tugas (self-practice)
- 15 tugas tanpa solusi, progresif easy → hard

---

## 🔗 Link Soal Online Judge Terkait

| No | Platform | Soal | Topik |
|----|----------|------|-------|
| 1 | CSES | Tower of Hanoi | Stack/Recursion |
| 2 | Codeforces 1279B | Brackets | Stack |
| 3 | CSES | Sliding Window | Deque |
| 4 | Codeforces 1092C | Prefixes and Suffixes | Queue |
| 5 | CSES | Traffic Lights | Priority Queue / Set |

---

## ⚠️ Common Mistakes Hari Ini

1. **Pop/top dari stack/queue kosong** — UB! Selalu cek `empty()` dulu
2. **Priority_queue default = MAX heap** — untuk min heap: `priority_queue<int, vector<int>, greater<int>>`
3. **Deque vs vector** — deque O(1) push_front, tapi random access sedikit lebih lambat
4. **Stack tidak bisa iterasi** — tidak ada begin/end, hanya top/push/pop
5. **Priority_queue tidak support erase** — pakai lazy deletion atau multiset

---

## ✅ Checklist Sebelum Lanjut ke Day 6

- [ ] Bisa solve bracket matching tanpa lihat referensi
- [ ] Paham perbedaan LIFO vs FIFO
- [ ] Bisa buat min-heap dengan priority_queue
- [ ] Paham sliding window maximum dengan deque
- [ ] Sudah selesai minimal 4/6 exercise
- [ ] Sudah coba minimal 5/15 tugas

---

## 👀 Preview Day 6

**Day 6: STL Algorithms — sort, lower/upper_bound, next_permutation, accumulate, max_element**

---

## 📝 Quick Reference Cheatsheet

```cpp
// === STACK (LIFO) ===
stack<int> st;
st.push(x);         // tambah atas
st.pop();           // hapus atas (void!)
st.top();           // lihat atas
st.empty();         // cek kosong
st.size();

// === QUEUE (FIFO) ===
queue<int> q;
q.push(x);          // tambah belakang
q.pop();            // hapus depan (void!)
q.front();          // lihat depan
q.back();           // lihat belakang
q.empty(); q.size();

// === DEQUE (double-ended) ===
deque<int> dq;
dq.push_front(x); dq.push_back(x);
dq.pop_front();    dq.pop_back();
dq.front();        dq.back();
dq[i];             // random access O(1)

// === PRIORITY_QUEUE (max-heap default) ===
priority_queue<int> pq;                    // MAX heap
priority_queue<int, vector<int>, greater<int>> pq_min; // MIN heap
pq.push(x);         // insert O(log n)
pq.pop();           // remove top O(log n)
pq.top();           // peek max/min O(1)
pq.empty(); pq.size();
```
