#!/usr/bin/env python3
"""Day 5 — STL Containers 3 (Stack, Queue, Deque, Priority_Queue)."""
import sys, os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..")))
from pptx_lib import *


def main():
    prs = make_presentation()

    # ── Cover ────────────────────────────────────────────────────
    def cov_deco(slide):
        items = [("LIFO", PRIMARY), ("FIFO", EMERALD),
                 ("Two-end", AMBER), ("Heap", VIOLET)]
        for i, (lbl, col) in enumerate(items):
            cx = 6.5 + i * 1.6
            rounded_rect(slide, cx, 5.6, 1.4, 0.5, col)
            tb(slide, lbl, cx, 5.7, 1.4, 0.4,
               size=10, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
    cover_slide(prs, 5, "STL Containers III",
                ["Stack  ·  Queue  ·  Deque  ·  Priority Queue",
                 "Adapter Containers untuk Pattern Khusus"],
                decoration=cov_deco)

    # ── Agenda ───────────────────────────────────────────────────
    agenda_slide(prs, "Agenda — Day 5", [
        ("01", "Stack\n(LIFO)", PRIMARY,
         ["Last In First Out", "push/pop/top", "Bracket matching", "DFS recursion"]),
        ("02", "Queue\n(FIFO)", EMERALD,
         ["First In First Out", "push/pop/front/back", "BFS traversal", "Round robin"]),
        ("03", "Deque\n(Both ends)", AMBER,
         ["Double-ended queue", "push/pop both sides", "Sliding window", "Random access"]),
        ("04", "Priority Queue\n(Heap)", VIOLET,
         ["Max-heap default", "top selalu max", "Min-heap variation", "Dijkstra"]),
    ])

    # ═══════════════════════════════════════════════════════════
    # SECTION 01 — Stack
    # ═══════════════════════════════════════════════════════════
    section_divider(prs, "01", "Stack — LIFO",
                    "Last In First Out — tumpukan piring")

    # ── Stack Concept ────────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Apa itu Stack?",
                 "Last In First Out — yang masuk terakhir keluar duluan")

    info_card(slide, "Properti Stack", [
        "• Hanya bisa akses elemen TERATAS (top)",
        "• push(x) → tambah ke atas tumpukan",
        "• pop() → hapus elemen teratas",
        "• top() → lihat elemen teratas (tidak hapus)",
        "• Semua O(1)",
    ], 0.5, 1.1, 5.8, 3.0, accent=PRIMARY)

    # Right: Stack visualization (vertikal)
    tb(slide, "Visualisasi Stack",
       6.5, 1.1, 6.3, 0.4, size=13, bold=True, color=PRIMARY)
    tb(slide, "Operasi: push(1), push(2), push(3)",
       6.5, 1.5, 6.3, 0.3, size=11, color=AMBER, font_name="Menlo")

    # Stack tower
    stack_x = 8.5
    for i, val in enumerate([1, 2, 3]):
        sy = 4.4 - i * 0.6
        rounded_rect(slide, stack_x, sy, 1.4, 0.55, PRIMARY)
        tb(slide, str(val), stack_x, sy + 0.1, 1.4, 0.4,
           size=14, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
        if i == 2:
            tb(slide, "← top", stack_x + 1.45, sy + 0.1, 1.0, 0.3,
               size=10, bold=True, color=AMBER)
    # Bottom border
    rect(slide, stack_x - 0.05, 5.0, 1.5, 0.05, SLATE)
    tb(slide, "bottom", stack_x, 5.07, 1.4, 0.3,
       size=9, color=MUTED, align=PP_ALIGN.CENTER)

    metric_card(slide, "push", "O(1)", 0.5, 4.5, 3.0, 1.2, accent=EMERALD)
    metric_card(slide, "pop", "O(1)", 3.7, 4.5, 3.0, 1.2, accent=PRIMARY)
    metric_card(slide, "top", "O(1)", 6.9, 4.5, 1.7, 1.2, accent=AMBER)

    # ── Stack Code & Pattern ─────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Stack — Code & Bracket Matching")

    code = """// === STACK BASICS ===
stack<int> st;
st.push(1);                  // O(1)
st.push(2);
st.push(3);
cout << st.top();            // 3
st.pop();                    // hapus 3
cout << st.size();           // 2
if (st.empty()) ...

// HATI-HATI: top() dari empty = UB!
if (!st.empty()) cout << st.top();

// === BRACKET MATCHING ===
bool isValid(string s) {
    stack<char> st;
    for (char c : s) {
        if (c=='('||c=='['||c=='{')
            st.push(c);
        else {
            if (st.empty()) return false;
            char t = st.top(); st.pop();
            if ((c==')'&&t!='(') ||
                (c==']'&&t!='[') ||
                (c=='}'&&t!='{')) return false;
        }
    }
    return st.empty();
}"""
    code_box(slide, code, 0.5, 1.1, 6.5, 5.7, font_size=10, accent=PRIMARY)

    # Right: trace
    tb(slide, "Trace: \"({[]})\"",
       7.2, 1.1, 5.6, 0.4, size=13, bold=True, color=AMBER)

    trace_steps = [
        ("c='('", "push", "['(']"),
        ("c='{'", "push", "['(','{']"),
        ("c='['", "push", "['(','{','[']"),
        ("c=']'", "pop '['", "['(','{']"),
        ("c='}'", "pop '{'", "['(']"),
        ("c=')'", "pop '('", "[]"),
    ]
    for i, (action, op, stk) in enumerate(trace_steps):
        ry = 1.6 + i * 0.55
        bg = BG_CARD if i % 2 == 0 else BG_CARD_2
        rect(slide, 7.2, ry, 5.6, 0.5, bg)
        tb(slide, action, 7.3, ry + 0.1, 1.0, 0.3,
           size=10, color=PRIMARY, font_name="Menlo")
        tb(slide, op, 8.4, ry + 0.1, 1.2, 0.3,
           size=10, color=AMBER)
        tb(slide, stk, 9.7, ry + 0.1, 3.1, 0.3,
           size=10, color=EMERALD, font_name="Menlo")

    tb(slide, "✓ Stack kosong → BALANCED!",
       7.2, 5.05, 5.6, 0.4, size=12, bold=True, color=EMERALD)

    # ── Monotonic Stack — Next Greater Element ──────────────────
    slide = new_slide(prs)
    slide_header(slide, "Monotonic Stack — Next Greater Element",
                 "Untuk tiap elemen, cari yang pertama lebih besar di kanan")

    code = """// Hasil: result[i] = next greater (atau -1)
vector<int> nextGreater(vector<int>& A) {
    int n = A.size();
    vector<int> res(n, -1);
    stack<int> st;        // simpan INDEX

    for (int i = 0; i < n; i++) {
        while (!st.empty() && A[st.top()] < A[i]) {
            res[st.top()] = A[i];
            st.pop();
        }
        st.push(i);
    }
    return res;
}
// Stack invariant: A[indices] DECREASING dari bawah"""
    code_box(slide, code, 0.5, 1.1, 6.5, 4.5, font_size=11, accent=PRIMARY)

    # Right: trace
    tb(slide, "Trace: A = [4, 5, 2, 10, 8]",
       7.2, 1.1, 5.6, 0.4, size=13, bold=True, color=AMBER)

    array_cells(slide, [4, 5, 2, 10, 8], 7.2, 1.6,
                cell_w=0.85, cell_h=0.55,
                highlights={i: PRIMARY for i in range(5)},
                value_size=14)

    ng_trace = [
        ("i=0", "push 0", "[0]", "—"),
        ("i=1: 5>4", "pop 0, res[0]=5, push 1", "[1]", "res[0]=5"),
        ("i=2: 2<5", "push 2", "[1,2]", "—"),
        ("i=3: 10>2,5", "pop 2,1, push 3", "[3]", "res[1]=10, res[2]=10"),
        ("i=4: 8<10", "push 4", "[3,4]", "—"),
    ]
    for ri, (i_step, op, stk, out) in enumerate(ng_trace):
        ry = 2.5 + ri * 0.5
        bg = BG_CARD if ri % 2 == 0 else BG_CARD_2
        rect(slide, 7.2, ry, 5.7, 0.45, bg)
        tb(slide, i_step, 7.25, ry + 0.07, 1.0, 0.32,
           size=9.5, color=PRIMARY, font_name="Menlo")
        tb(slide, op, 8.3, ry + 0.07, 2.4, 0.32,
           size=9, color=AMBER)
        tb(slide, stk, 10.7, ry + 0.07, 1.0, 0.32,
           size=9, color=EMERALD, font_name="Menlo")
        tb(slide, out, 7.25, ry + 0.07, 5.6, 0.32,
           size=9, color=SILVER, align=PP_ALIGN.RIGHT)

    callout(slide, "Result: [5, 10, 10, -1, -1]",
            7.2, 5.1, 5.6, 0.55, color=EMERALD)

    info_card(slide, "Pola Monotonic",
              ["• Tiap index push & pop max 1× → O(n)",
               "• Decreasing stack: next greater",
               "• Increasing stack: next smaller",
               "• Iterate dari kanan → previous greater/smaller"],
              0.5, 5.85, 12.3, 1.4, accent=VIOLET)

    # ═══════════════════════════════════════════════════════════
    # SECTION 02 — Queue
    # ═══════════════════════════════════════════════════════════
    section_divider(prs, "02", "Queue — FIFO",
                    "First In First Out — antrian di kasir")

    # ── Queue Concept ────────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Apa itu Queue?",
                 "First In First Out — yang masuk pertama keluar duluan")

    info_card(slide, "Properti Queue", [
        "• push(x) → tambah ke BELAKANG (back)",
        "• pop() → hapus dari DEPAN (front)",
        "• front() → lihat depan",
        "• back() → lihat belakang",
        "• Semua O(1)",
    ], 0.5, 1.1, 5.8, 3.0, accent=EMERALD)

    # Right: Queue visualization (horizontal)
    tb(slide, "Visualisasi Queue",
       6.5, 1.1, 6.3, 0.4, size=13, bold=True, color=EMERALD)
    tb(slide, "push(1), push(2), push(3), pop()",
       6.5, 1.5, 6.3, 0.3, size=11, color=AMBER, font_name="Menlo")

    # Queue cells
    array_cells(slide, [2, 3], 7.5, 2.3,
                cell_w=0.85, cell_h=0.7,
                highlights={0: EMERALD, 1: EMERALD},
                value_size=18, show_index=False)
    # Front label
    tb(slide, "front\n(keluar)", 6.5, 2.3, 0.9, 0.7,
       size=10, bold=True, color=AMBER, align=PP_ALIGN.CENTER)
    tb(slide, "→", 7.3, 2.5, 0.3, 0.4, size=18, color=AMBER)
    # Back label
    tb(slide, "back\n(masuk)", 9.4, 2.3, 0.9, 0.7,
       size=10, bold=True, color=PRIMARY, align=PP_ALIGN.CENTER)
    tb(slide, "←", 9.15, 2.5, 0.3, 0.4, size=18, color=PRIMARY)

    callout(slide, "1 sudah keluar (pop). Tinggal 2 di depan, 3 di belakang.",
            6.5, 3.5, 6.3, 0.6, color=EMERALD)

    metric_card(slide, "push", "O(1)", 0.5, 4.5, 3.0, 1.2, accent=PRIMARY)
    metric_card(slide, "pop", "O(1)", 3.7, 4.5, 3.0, 1.2, accent=EMERALD)
    metric_card(slide, "front/back", "O(1)", 6.9, 4.5, 3.0, 1.2, accent=AMBER)

    # ── Queue Code + BFS Pattern ─────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Queue — Code & BFS Pattern")

    code = """// === QUEUE BASICS ===
queue<int> q;
q.push(1); q.push(2); q.push(3);
cout << q.front();   // 1
cout << q.back();    // 3
q.pop();             // hapus 1
cout << q.size();    // 2

// === BFS TEMPLATE ===
void bfs(int start, vector<vector<int>>& adj) {
    int n = adj.size();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        cout << u << " ";   // process
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}"""
    code_box(slide, code, 0.5, 1.1, 6.5, 5.7, font_size=10, accent=EMERALD)

    # Right: BFS visualization
    tb(slide, "BFS: Level-by-level traversal",
       7.2, 1.1, 5.6, 0.4, size=13, bold=True, color=EMERALD)
    callout(slide,
            "Queue menjamin urutan: semua node level-1 diproses sebelum level-2.",
            7.2, 1.6, 5.6, 0.8, color=EMERALD)

    info_card(slide, "Use Cases Queue", [
        "🔹 BFS shortest path (unweighted)",
        "🔹 Level-order traversal di tree",
        "🔹 Round-robin scheduling",
        "🔹 Cache replacement (FIFO)",
        "🔹 Producer-consumer queue",
    ], 7.2, 2.5, 5.6, 2.6, accent=PRIMARY)

    insight_card(slide, "Stack vs Queue di Search",
                 ["Stack → DFS (kedalaman)",
                  "Queue → BFS (lebar / shortest)",
                  "Pola sangat mirip, beda struktur saja"],
                 7.2, 5.25, 5.6, 1.5)

    # ═══════════════════════════════════════════════════════════
    # SECTION 03 — Deque
    # ═══════════════════════════════════════════════════════════
    section_divider(prs, "03", "Deque — Double-Ended Queue",
                    "Bisa push/pop dari kedua ujung — fleksibel!")

    # ── Deque Concept ────────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Deque — Double-Ended Queue",
                 "Push/pop dari front & back — semua O(1)")

    code = """// === DEQUE BASICS ===
deque<int> dq;

// PUSH dari kedua sisi
dq.push_front(1);    // [1]
dq.push_back(2);     // [1, 2]
dq.push_front(0);    // [0, 1, 2]
dq.push_back(3);     // [0, 1, 2, 3]

// AKSES
dq.front();          // 0
dq.back();           // 3
dq[1];               // 1 (random access!)

// POP
dq.pop_front();      // [1, 2, 3]
dq.pop_back();       // [1, 2]

// IDIOMATIC iteration
for (int x : dq) cout << x;"""
    code_box(slide, code, 0.5, 1.1, 6.3, 5.5, font_size=10, accent=AMBER)

    # Right: Deque visualization
    tb(slide, "Deque: 2-ended seperti vector",
       7.0, 1.1, 5.8, 0.4, size=13, bold=True, color=AMBER)

    array_cells(slide, [0, 1, 2, 3], 7.4, 1.7,
                cell_w=0.8, cell_h=0.65,
                highlights={i: AMBER for i in range(4)},
                value_size=16)
    # Arrows
    tb(slide, "↑\nfront\npop_front", 7.0, 2.5, 1.0, 0.8,
       size=9, bold=True, color=PRIMARY, align=PP_ALIGN.CENTER)
    tb(slide, "↑\nback\npop_back", 10.85, 2.5, 1.0, 0.8,
       size=9, bold=True, color=EMERALD, align=PP_ALIGN.CENTER)
    tb(slide, "← push_front", 7.0, 3.5, 2.0, 0.3,
       size=10, color=PRIMARY)
    tb(slide, "push_back →", 10.5, 3.5, 2.0, 0.3,
       size=10, color=EMERALD)

    info_card(slide, "Use Cases Deque", [
        "🔹 Sliding window maximum (monotonic)",
        "🔹 Palindrome check (front vs back)",
        "🔹 0-1 BFS (push_front / push_back)",
        "🔹 Undo/redo (recent + oldest)",
    ], 7.0, 4.0, 5.8, 2.5, accent=AMBER)

    # ── Sliding Window Maximum Trace (Monotonic Deque) ──────────
    slide = new_slide(prs)
    slide_header(slide, "Sliding Window Maximum — Monotonic Deque",
                 "Deque simpan INDEX, A[idx] decreasing dari front")

    code_swm = """// Deque maintains DECREASING order of values (stores indices)
deque<int> dq;
for (int i = 0; i < n; i++) {
    // 1. Pop front yang sudah keluar window
    while (!dq.empty() && dq.front() <= i - k)
        dq.pop_front();
    // 2. Pop back yang nilainya ≤ A[i] (tidak akan jadi max)
    while (!dq.empty() && A[dq.back()] <= A[i])
        dq.pop_back();
    // 3. Push index sekarang
    dq.push_back(i);
    // 4. Window penuh → output max
    if (i >= k - 1) cout << A[dq.front()] << ' ';
}"""
    code_box(slide, code_swm, 0.5, 1.1, 7.0, 4.0, font_size=10.5, accent=AMBER)

    # Right: invariant
    insight_card(slide, "Invariant Deque", [
        "Index dalam dq ⊆ [i-k+1, i]",
        "A[front] ≥ A[next] ≥ ... ≥ A[back]",
        "A[front] = MAX di window sekarang",
        "Tiap elemen masuk & keluar ≤ 1× → O(n)",
    ], 7.7, 1.1, 5.3, 2.4)

    metric_card(slide, "Brute Force", "O(n·k)", 7.7, 3.65, 2.5, 1.4,
                accent=ROSE)
    metric_card(slide, "Mono Deque", "O(n)", 10.4, 3.65, 2.5, 1.4,
                accent=EMERALD)

    # Bottom: trace
    rounded_rect(slide, 0.5, 5.25, 12.3, 2.0, BG_CARD,
                 line_color=AMBER, line_w=1.0)
    rect(slide, 0.5, 5.25, 12.3, 0.08, AMBER)
    tb(slide, "Trace: A=[1,3,-1,-3,5,3,6,7], K=3  →  Output: 3 3 5 5 6 7",
       0.7, 5.35, 12.0, 0.4, size=12, bold=True, color=AMBER)

    swm_steps = [
        ("0", "[0]", "—"),
        ("1: 3>1 pop", "[1]", "—"),
        ("2", "[1,2]", "3"),
        ("3", "[1,2,3]", "3"),
        ("4: 5>−3,−1,3", "[4]", "5"),
        ("5", "[4,5]", "5"),
        ("6: 6>3,5", "[6]", "6"),
        ("7: 7>6", "[7]", "7"),
    ]
    for i, (step, dq, out) in enumerate(swm_steps):
        cn = i % 4
        rn = i // 4
        sx = 0.7 + cn * 3.05
        sy = 5.85 + rn * 0.65
        rounded_rect(slide, sx, sy, 2.95, 0.55, BG_CARD_2,
                     line_color=BORDER, line_w=0.5)
        rect(slide, sx, sy, 2.95, 0.05, EMERALD if "—" not in out else AMBER)
        tb(slide, f"i={step}", sx + 0.08, sy + 0.07, 1.2, 0.22,
           size=9, color=PRIMARY, font_name="Menlo")
        tb(slide, dq, sx + 0.08, sy + 0.3, 1.5, 0.22,
           size=9, color=EMERALD, font_name="Menlo")
        tb(slide, "out=" + out, sx + 1.65, sy + 0.18, 1.25, 0.32,
           size=9, color=AMBER if "—" not in out else MUTED,
           bold=True, align=PP_ALIGN.CENTER)

    # ═══════════════════════════════════════════════════════════
    # SECTION 04 — Priority Queue
    # ═══════════════════════════════════════════════════════════
    section_divider(prs, "04", "Priority Queue — Heap",
                    "Max default. Akses elemen terbesar O(1).")

    # ── Priority Queue Concept ───────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Priority Queue — Auto Sorted Heap",
                 "Top selalu MAX (default), atau MIN (variant)")

    code = """// === MAX-HEAP (DEFAULT) ===
priority_queue<int> pq;
pq.push(3); pq.push(1); pq.push(4);
pq.push(1); pq.push(5);

cout << pq.top();    // 5 (max)
pq.pop();            // remove 5
cout << pq.top();    // 4

// === MIN-HEAP ===
priority_queue<int, vector<int>, greater<int>> pq_min;
pq_min.push(3); pq_min.push(1);
pq_min.push(4);
cout << pq_min.top();   // 1 (min)

// === CUSTOM COMPARATOR ===
auto cmp = [](pair<int,int> a, pair<int,int> b) {
    return a.second > b.second;  // min by second
};
priority_queue<pair<int,int>,
               vector<pair<int,int>>,
               decltype(cmp)> pq3(cmp);"""
    code_box(slide, code, 0.5, 1.1, 6.5, 5.7, font_size=10, accent=VIOLET)

    # Right: Heap visualization
    tb(slide, "Max-Heap (binary tree)",
       7.2, 1.1, 5.6, 0.4, size=13, bold=True, color=VIOLET)
    tb(slide, "Setelah push(3,1,4,1,5):",
       7.2, 1.5, 5.6, 0.3, size=10, color=AMBER, italic=True)

    # Heap visualization sederhana
    nodes = [(10.0, 2.2, 5, VIOLET, BG_DEEP),
             (8.5, 3.4, 4, PRIMARY, BG_DEEP),
             (11.5, 3.4, 3, PRIMARY, BG_DEEP),
             (7.5, 4.6, 1, EMERALD, BG_DEEP),
             (9.5, 4.6, 1, EMERALD, BG_DEEP)]
    # Edges
    for parent, *children in [(0, 1, 2), (1, 3, 4)]:
        for c in children:
            px, py = nodes[parent][0], nodes[parent][1]
            cx, cy = nodes[c][0], nodes[c][1]
            # diagonal line as small rect approximation - skip, just labels
    for nx, ny, val, col, tcol in nodes:
        circle(slide, nx, ny, 0.32, col)
        tb(slide, str(val), nx - 0.32, ny - 0.18, 0.64, 0.36,
           size=14, bold=True, color=tcol, align=PP_ALIGN.CENTER)

    tb(slide, "↑ root = MAX",
       9.5, 1.85, 1.5, 0.3, size=10, bold=True, color=AMBER)

    metric_card(slide, "push", "O(log n)", 0.5, 6.9, 3.0, 0.5,
                accent=PRIMARY)
    metric_card(slide, "pop", "O(log n)", 3.7, 6.9, 3.0, 0.5,
                accent=AMBER)
    metric_card(slide, "top", "O(1)", 6.9, 6.9, 3.0, 0.5,
                accent=EMERALD)

    # ── Priority Queue Use Cases ─────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Priority Queue — Pattern & Use Cases")

    info_card(slide, "🎯 Top-K Largest Elements", [
        "Pakai MIN-HEAP ukuran K.",
        "Jika size > K → pop top (yg terkecil).",
        "Sisanya = top-K largest.",
    ], 0.5, 1.1, 6.0, 1.7, accent=PRIMARY)

    info_card(slide, "🛣️ Dijkstra Shortest Path", [
        "Min-heap of (distance, node).",
        "Pop → process node terdekat dulu.",
        "Update distance neighbors → push.",
    ], 6.7, 1.1, 6.1, 1.7, accent=EMERALD)

    info_card(slide, "🔀 Merge K Sorted Arrays", [
        "Min-heap of (val, arr_idx, val_idx).",
        "Pop terkecil → push next dari array yg sama.",
        "Total O(n log K).",
    ], 0.5, 2.95, 6.0, 1.7, accent=AMBER)

    info_card(slide, "📊 Median Finder (2 heaps)", [
        "Max-heap untuk lower half.",
        "Min-heap untuk upper half.",
        "Median = top heap (atau average).",
    ], 6.7, 2.95, 6.1, 1.7, accent=VIOLET)

    code = """// === TOP-K LARGEST ===
priority_queue<int, vector<int>, greater<int>> minH;  // min-heap
for (int x : nums) {
    minH.push(x);
    if (minH.size() > k) minH.pop();
}
// minH sekarang berisi K largest"""
    code_box(slide, code, 0.5, 4.85, 12.3, 1.8, font_size=11, accent=PRIMARY)

    # ── Heap Trace & Merge K Sorted ─────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Trace Heap & Merge K Sorted Arrays",
                 "Visualisasi push/pop dan pola merge K stream")

    # Left: Heap operations trace
    tb(slide, "Max-Heap Trace", 0.5, 1.1, 6.3, 0.4,
       size=13, bold=True, color=VIOLET)

    heap_trace = [
        ("push(3)", "[3]", "3"),
        ("push(1)", "[3, 1]", "3"),
        ("push(5)", "[5, 1, 3]", "5"),
        ("push(2)", "[5, 2, 3, 1]", "5"),
        ("pop()", "[3, 2, 1]", "3"),
        ("push(4)", "[4, 2, 3, 1]", "4"),
        ("pop()", "[3, 2, 1]", "3"),
    ]
    headers = ["Operasi", "Heap (conceptual)", "top()"]
    widths = [1.7, 3.3, 1.2]

    rect(slide, 0.5, 1.55, sum(widths) - 0.04, 0.4, VIOLET)
    cumx = 0.5
    for h, w in zip(headers, widths):
        tb(slide, h, cumx + 0.05, 1.6, w - 0.1, 0.3,
           size=10, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
        cumx += w
    for ri, row in enumerate(heap_trace):
        ry = 1.96 + ri * 0.42
        bg = BG_CARD if ri % 2 == 0 else BG_CARD_2
        rect(slide, 0.5, ry, sum(widths) - 0.04, 0.4, bg)
        cumx = 0.5
        for ci, (cell, w) in enumerate(zip(row, widths)):
            col = AMBER if ci == 2 else WHITE
            tb(slide, cell, cumx + 0.05, ry + 0.07, w - 0.1, 0.3,
               size=10, color=col, font_name="Menlo",
               align=PP_ALIGN.LEFT if ci == 0 else PP_ALIGN.CENTER)
            cumx += w

    callout(slide, "Heap selalu menjaga max di root → top() O(1)",
            0.5, 5.0, 6.3, 0.55, color=EMERALD)

    # Right: Merge K sorted arrays code
    tb(slide, "Merge K Sorted Arrays — Min Heap",
       7.0, 1.1, 5.8, 0.4, size=13, bold=True, color=AMBER)

    code_mk = """// Min-heap of (value, arr_idx, elem_idx)
priority_queue<tuple<int,int,int>,
    vector<tuple<int,int,int>>,
    greater<>> pq;

// Push first elemen tiap array
for (int i = 0; i < k; i++)
    pq.push({arr[i][0], i, 0});

while (!pq.empty()) {
    auto [v, ai, ei] = pq.top();
    pq.pop();
    cout << v << ' ';
    if (ei + 1 < (int)arr[ai].size())
        pq.push({arr[ai][ei+1], ai, ei+1});
}
// Total: O(n log K)"""
    code_box(slide, code_mk, 7.0, 1.55, 5.8, 4.0, font_size=10, accent=AMBER)

    # Bottom: median finder concept
    rounded_rect(slide, 0.5, 5.7, 12.3, 1.55, BG_CARD,
                 line_color=EMERALD, line_w=1.0)
    rect(slide, 0.5, 5.7, 12.3, 0.08, EMERALD)
    tb(slide, "📊 Median Finder — Two Heaps",
       0.7, 5.8, 8.0, 0.4, size=13, bold=True, color=EMERALD)

    median_pts = [
        ("Max-heap", "lower half (≤ median)", PRIMARY),
        ("Min-heap", "upper half (≥ median)", AMBER),
        ("Balance", "diff ≤ 1 antar heap", VIOLET),
        ("Median", "top heap besar / avg", EMERALD),
    ]
    for i, (label, desc, col) in enumerate(median_pts):
        cn = i % 4
        px = 0.7 + cn * 3.0
        tb(slide, label, px, 6.25, 2.9, 0.3,
           size=11, bold=True, color=col)
        tb(slide, desc, px, 6.55, 2.9, 0.6,
           size=9.5, color=SILVER)

    # ── Pattern Recognition ──────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Pattern Recognition — Container Mana?")

    rows = [
        ["Bracket matching, undo", "stack", "LIFO", "DFS recursion"],
        ["BFS shortest path", "queue", "FIFO", "Level-by-level"],
        ["Sliding window max/min", "deque", "Monotonic", "O(n) total"],
        ["Top-K elements", "priority_queue (min-heap)", "Fixed size K", "O(n log K)"],
        ["Dijkstra / Prim", "priority_queue", "Min by weight", "O(E log V)"],
        ["Merge K sorted", "priority_queue", "Min by value", "O(n log K)"],
        ["Median in stream", "2× priority_queue", "Max-half + Min-half", "O(log n) insert"],
        ["DFS iteratif", "stack", "Replace recursion", "Avoid stack overflow"],
    ]
    styled_table(slide, ["Situasi", "Container", "Strategi", "Complexity"],
                 rows, 0.5, 1.1, [3.5, 3.4, 2.8, 2.3], row_h=0.5,
                 header_colors=[PRIMARY, EMERALD, AMBER, VIOLET])

    # ── Common Mistakes ──────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Common Mistakes — Hindari Ini!")

    mistakes = [
        ("1. top()/pop() di empty container",
         "stack.top() saat empty = UB!\n"
         "Selalu cek: if (!st.empty())\n"
         "Sama untuk queue.front(), pq.top().",
         ROSE),
        ("2. priority_queue default = MAX",
         "priority_queue<int> = max-heap!\n"
         "Untuk min-heap: greater<int> sbg\n"
         "template arg ke-3, ATAU negate value.",
         ROSE),
        ("3. pop() return VOID",
         "int x = q.pop();   ✗ COMPILE ERROR\n"
         "int x = q.front(); ✓\n"
         "q.pop();           ✓ baru pop",
         AMBER),
        ("4. stack vs deque vs vector",
         "Vector bisa simulasi stack (push_back/back/pop_back).\n"
         "Deque > queue (random access + 2 ujung).\n"
         "Pakai stack/queue untuk readability saja.",
         AMBER),
        ("5. Custom comparator pq tricky",
         "auto cmp = [](...){...};\n"
         "priority_queue<T, vector<T>,\n"
         "    decltype(cmp)> pq(cmp);  ← wajib!",
         AMBER),
        ("6. Lazy deletion di pq",
         "pq tidak support erase arbitrary.\n"
         "Pakai trick: tandai 'deleted',\n"
         "skip saat pop jika sudah deleted.",
         VIOLET),
    ]
    for i, (title, desc, col) in enumerate(mistakes):
        cn = i % 3
        rn = i // 3
        mx = 0.4 + cn * 4.25
        my = 1.1 + rn * 2.95
        rounded_rect(slide, mx, my, 4.1, 2.7, BG_CARD, line_color=col, line_w=1.0)
        rect(slide, mx, my, 4.1, 0.08, col)
        tb(slide, title, mx + 0.2, my + 0.2, 3.85, 0.5,
           size=12, bold=True, color=col)
        tb(slide, desc, mx + 0.2, my + 0.75, 3.85, 1.85,
           size=10.5, color=SILVER)

    # ── Cheatsheet ───────────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Cheatsheet — Quick Reference")

    left = """// STACK (LIFO)
stack<int> st;
st.push(x); st.pop(); st.top();
if (!st.empty()) ...

// QUEUE (FIFO)
queue<int> q;
q.push(x); q.pop(); q.front(); q.back();

// DEQUE (Both ends)
deque<int> dq;
dq.push_front(x); dq.push_back(x);
dq.pop_front(); dq.pop_back();
dq[i];                          // random access"""

    right = """// MAX-HEAP (default)
priority_queue<int> pq;
pq.push(x); pq.pop(); pq.top();

// MIN-HEAP
priority_queue<int, vector<int>,
               greater<int>> pq_min;

// PAIR HEAP (sort by first DESC)
priority_queue<pair<int,int>> pqp;

// CUSTOM
auto cmp = [](int a, int b){ return a > b; };
priority_queue<int, vector<int>,
               decltype(cmp)> pq3(cmp);"""

    code_box(slide, left, 0.5, 1.1, 6.2, 4.7, font_size=10.5, accent=PRIMARY)
    code_box(slide, right, 6.7, 1.1, 6.1, 4.7, font_size=10.5, accent=VIOLET)

    rounded_rect(slide, 0.5, 6.0, 12.3, 1.3, BG_CARD,
                 line_color=AMBER, line_w=1.0)
    rect(slide, 0.5, 6.0, 12.3, 0.08, AMBER)
    tb(slide, "🌟 Aturan Emas", 0.7, 6.1, 5.0, 0.4,
       size=13, bold=True, color=AMBER)
    rules = [
        ("• stack/queue/pq adalah ADAPTER (bukan container)", SILVER),
        ("• top()/pop()/front() di empty = UB, selalu cek empty()", SILVER),
        ("• Min-heap = greater<int> sebagai 3rd template arg", SILVER),
        ("• Deque mendukung push/pop dua sisi + random access", SILVER),
    ]
    for i, (text, col) in enumerate(rules):
        cn = i % 2; rn = i // 2
        tb(slide, text, 0.7 + cn * 6.0, 6.45 + rn * 0.35,
           5.8, 0.32, size=10, color=col)

    # ── Closing ──────────────────────────────────────────────────
    closing_slide(prs, 5, "Adapter containers — DFS, BFS, sliding window, heap", [
        (PRIMARY, "Stack (LIFO)",
         "push/pop/top all O(1). Bracket match, DFS, undo. Hati-hati top() empty."),
        (EMERALD, "Queue (FIFO)",
         "push/pop dari ujung berbeda. BFS, level-order, scheduling."),
        (AMBER, "Deque (2-ended)",
         "push/pop_front+back. Sliding window monotonic. Random access seperti vector."),
        (VIOLET, "Priority Queue",
         "Max-heap default. Min-heap pakai greater. Dijkstra, top-K, merge sorted."),
        (ROSE, "Pitfall",
         "Akses empty container = UB. Custom comparator priority_queue tricky syntax."),
    ])

    save_presentation(prs, os.path.join(
        os.path.dirname(os.path.abspath(__file__)),
        "Day_5_Presentation.pptx"))


if __name__ == "__main__":
    main()
