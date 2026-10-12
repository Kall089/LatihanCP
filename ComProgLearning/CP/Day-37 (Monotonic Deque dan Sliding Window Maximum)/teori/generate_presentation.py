#!/usr/bin/env python3
"""Day 38 — Queue & Deque Applications: BFS, sliding window max/min, stream.
Rich visuals untuk setiap subtopik."""
import sys, os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..")))
from pptx_lib import *


def main():
    prs = make_presentation()

    # ── Cover ────────────────────────────────────────────────────
    def cov_deco(slide):
        labels = ["FIFO", "Deque", "BFS", "Window"]
        cols = [PRIMARY, EMERALD, AMBER, VIOLET]
        for i, (lbl, col) in enumerate(zip(labels, cols)):
            cx = 6.4 + i * 1.55
            rounded_rect(slide, cx, 5.6, 1.45, 0.5, col)
            tb(slide, lbl, cx, 5.7, 1.45, 0.4,
               size=11, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)

    cover_slide(prs, 38, "Queue & Deque Applications",
                ["FIFO · Double-Ended · Sliding Window",
                 "Pola O(n) elegan dengan deque monotonic"],
                decoration=cov_deco)

    # ── Agenda ───────────────────────────────────────────────────
    agenda_slide(prs, "Agenda — Day 38", [
        ("01", "Queue\nReview", PRIMARY,
         ["FIFO ops", "push/pop O(1)", "Visualisasi", "Kapan pakai?"]),
        ("02", "Deque —\nDouble Ended", EMERALD,
         ["push/pop_front", "push/pop_back", "Stack alternatif", "Queue alternatif"]),
        ("03", "Sliding\nWindow Max", AMBER,
         ["Monotonic deque", "Step-by-step trace", "O(n) total", "Window invariant"]),
        ("04", "Stream &\nBFS Level", VIOLET,
         ["First non-repeat", "Queue + freq", "BFS level order", "Tips & pitfall"]),
    ])

    # ── Section 01 ───────────────────────────────────────────────
    section_divider(prs, "01", "Queue Review",
                    "FIFO sederhana — fondasi BFS dan simulasi")

    slide = new_slide(prs)
    slide_header(slide, "Queue STL — FIFO Visualisasi",
                 "Yang masuk pertama, keluar pertama")

    # Left: code
    code = """#include <queue>

queue<int> q;
q.push(x);    // O(1) — tambah ke belakang
q.pop();      // O(1) — hapus dari depan
q.front();    // O(1) — peek depan
q.back();     // O(1) — peek belakang
q.empty();    // bool kosong
q.size();     // jumlah

while (!q.empty()) {
    int x = q.front(); q.pop();
    process(x);
}"""
    code_box(slide, code, 0.5, 1.1, 5.5, 4.5, font_size=11, accent=PRIMARY)

    info_card(slide, "Kapan pakai Queue?",
              ["• BFS / Level-order traversal",
               "• Simulasi antrian / proses",
               "• Stream processing",
               "• Topological sort (Kahn's)"],
              0.5, 5.75, 5.5, 1.5, accent=EMERALD)

    # Right: visual queue
    tb(slide, "🎬 Visualisasi: enqueue & dequeue",
       6.3, 1.1, 6.7, 0.4, size=13, bold=True, color=AMBER)

    # 4 steps showing queue state
    queue_stages = [
        ("push 1",   [1],          {0: PRIMARY}),
        ("push 2",   [1, 2],       {0: SLATE, 1: PRIMARY}),
        ("push 3",   [1, 2, 3],    {0: SLATE, 1: SLATE, 2: PRIMARY}),
        ("pop → 1",  [2, 3],       {0: AMBER, 1: SLATE}),
    ]
    for i, (lbl, items, hl) in enumerate(queue_stages):
        sx = 6.4 + (i % 2) * 3.4
        sy_top = 1.7 + (i // 2) * 2.55
        # Container
        cn_w = 3.0
        cn_h = 1.0
        rounded_rect(slide, sx, sy_top, cn_w, cn_h + 0.6, BG_CARD,
                     line_color=BORDER, line_w=0.5)
        tb(slide, lbl, sx, sy_top + 0.05, cn_w, 0.3,
           size=10, bold=True, color=AMBER, align=PP_ALIGN.CENTER)
        # Queue cells horizontal
        cell_w = 0.55
        cell_x = sx + (cn_w - len(items) * (cell_w + 0.06)) / 2
        cell_y = sy_top + 0.55
        for k, val in enumerate(items):
            col = hl.get(k, BG_CARD_2)
            cx = cell_x + k * (cell_w + 0.06)
            rounded_rect(slide, cx, cell_y, cell_w, 0.5, col,
                         line_color=BORDER, line_w=0.5)
            tc = BG_DEEP if k in hl else WHITE
            tb(slide, str(val), cx, cell_y + 0.08, cell_w, 0.35,
               size=12, bold=True, color=tc, align=PP_ALIGN.CENTER,
               font_name="Menlo")
        # Front and back arrows
        if items:
            tb(slide, "front↑", cell_x, cell_y + 0.55, cell_w, 0.3,
               size=8, color=ROSE, align=PP_ALIGN.CENTER, bold=True)
            last_x = cell_x + (len(items) - 1) * (cell_w + 0.06)
            tb(slide, "↑back", last_x, cell_y + 0.55, cell_w, 0.3,
               size=8, color=EMERALD, align=PP_ALIGN.CENTER, bold=True)

    callout(slide, "FIFO: First In, First Out — semua O(1)",
            6.3, 6.85, 6.7, 0.5, color=EMERALD, icon="⚡")

    # ── Section 02 ───────────────────────────────────────────────
    section_divider(prs, "02", "Deque — Double Ended",
                    "push/pop di kedua ujung — O(1) all the way",
                    color=EMERALD)

    slide = new_slide(prs)
    slide_header(slide, "Deque STL — 4 Operasi di 2 Ujung")

    code = """#include <deque>

deque<int> dq;

// === KEDUA UJUNG ===
dq.push_front(x);  // O(1)
dq.push_back(x);   // O(1)
dq.pop_front();    // O(1)
dq.pop_back();     // O(1)
dq.front();        // peek depan
dq.back();         // peek belakang

// === SEBAGAI STACK ===
dq.push_back(x); dq.pop_back(); dq.back();

// === SEBAGAI QUEUE ===
dq.push_back(x); dq.pop_front(); dq.front();"""
    code_box(slide, code, 0.5, 1.1, 6.2, 5.5, font_size=11, accent=EMERALD)

    # Right: comparison + visual
    tb(slide, "📊 Queue vs Deque",
       6.9, 1.1, 6.0, 0.4, size=13, bold=True, color=AMBER)
    rows = [
        ["push_back",  ("✓", EMERALD), ("✓", EMERALD)],
        [("push_front", PRIMARY), ("✗", ROSE), ("✓", EMERALD)],
        [("pop_back",   PRIMARY), ("✗", ROSE), ("✓", EMERALD)],
        ["pop_front",  ("✓", EMERALD), ("✓", EMERALD)],
        [("operator[]", PRIMARY), ("✗", ROSE), ("✓ O(1)", EMERALD)],
    ]
    styled_table(slide, ["Operasi", "queue", "deque"], rows,
                 6.9, 1.7, [2.0, 1.7, 2.3], row_h=0.5,
                 header_colors=[PRIMARY, EMERALD, AMBER],
                 body_size=10, header_size=10)

    # Visual: deque double-headed
    tb(slide, "🎯 Deque visual (2 ujung)",
       6.9, 4.9, 6.0, 0.3, size=11, bold=True, color=PRIMARY)

    # Show deque with arrows on both sides
    deq_items = [4, 7, 2, 9, 1]
    deq_x = 7.4
    deq_y = 5.4
    cell_w = 0.6
    for i, val in enumerate(deq_items):
        bx = deq_x + i * (cell_w + 0.05)
        rounded_rect(slide, bx, deq_y, cell_w, 0.5, BG_CARD_2,
                     line_color=BORDER, line_w=0.5)
        tb(slide, str(val), bx, deq_y + 0.08, cell_w, 0.35,
           size=12, bold=True, color=WHITE, align=PP_ALIGN.CENTER,
           font_name="Menlo")

    # Left arrow (front)
    arrow(slide, deq_x - 0.5, deq_y + 0.25, deq_x - 0.05, deq_y + 0.25,
          color=ROSE, thickness=2.0)
    tb(slide, "front", deq_x - 0.65, deq_y + 0.55, 0.7, 0.3,
       size=9, bold=True, color=ROSE, align=PP_ALIGN.CENTER)
    # Right arrow (back)
    last_x = deq_x + (len(deq_items)) * (cell_w + 0.05)
    arrow(slide, last_x + 0.05, deq_y + 0.25, last_x + 0.5, deq_y + 0.25,
          color=EMERALD, thickness=2.0)
    tb(slide, "back", last_x + 0.0, deq_y + 0.55, 0.7, 0.3,
       size=9, bold=True, color=EMERALD, align=PP_ALIGN.CENTER)

    callout(slide, "Deque > Queue di fleksibilitas (semua O(1))",
            6.9, 6.4, 6.0, 0.55, color=EMERALD, icon="✨")

    # ── Section 03: Sliding Window Max ────────────────────────
    section_divider(prs, "03", "Sliding Window Maximum",
                    "Monotonic decreasing deque — O(n) elegan",
                    color=AMBER)

    slide = new_slide(prs)
    slide_header(slide, "Sliding Window Maximum — Konsep & Invariant",
                 "Deque menyimpan INDEX, monoton menurun berdasar nilai")

    info_card(slide, "🎯 Invariant Deque",
              [("• Front = index nilai MAX di window", AMBER),
               ("• Nilai dq.front → dq.back menurun", SILVER),
               ("• Index out-of-window di pop_front", SILVER),
               ("• Index nilai ≤ baru di pop_back", SILVER)],
              0.5, 1.1, 6.0, 2.7, accent=AMBER)

    code = """vector<int> swMax(vector<int>& A, int k) {
    deque<int> dq;
    vector<int> res;
    for (int i = 0; i < (int)A.size(); i++) {
        // 1. Buang index out-of-window
        while (!dq.empty() && dq.front() <= i-k)
            dq.pop_front();
        // 2. Buang yang ≤ A[i] dari belakang
        while (!dq.empty() && A[dq.back()] <= A[i])
            dq.pop_back();
        dq.push_back(i);
        if (i >= k - 1)
            res.push_back(A[dq.front()]);
    }
    return res;
}"""
    code_box(slide, code, 0.5, 3.95, 6.0, 3.3, font_size=10.5, accent=AMBER)

    # Right: visualization of monotonic deque growth
    tb(slide, "🎬 Monotonic Decreasing Deque",
       6.7, 1.1, 6.3, 0.4, size=13, bold=True, color=PRIMARY)

    # Show 4 stages visually
    deq_stages = [
        ("Push 5",   [5],         {0: PRIMARY}),
        ("Push 3",   [5, 3],      {0: SLATE, 1: PRIMARY}),
        ("Push 7→pop 3,5", [7],   {0: EMERALD}),
        ("Push 2",   [7, 2],      {0: SLATE, 1: PRIMARY}),
    ]
    for i, (lbl, items, hl) in enumerate(deq_stages):
        sx = 6.7 + (i % 2) * 3.25
        sy_top = 1.7 + (i // 2) * 2.7
        rounded_rect(slide, sx, sy_top, 3.0, 2.4, BG_CARD,
                     line_color=BORDER, line_w=0.5)
        tb(slide, lbl, sx, sy_top + 0.05, 3.0, 0.3,
           size=10, bold=True, color=AMBER, align=PP_ALIGN.CENTER)
        # Items horizontal
        cell_w = 0.55
        cell_x = sx + (3.0 - len(items) * (cell_w + 0.06)) / 2
        cell_y = sy_top + 0.55
        for k, val in enumerate(items):
            col = hl.get(k, BG_CARD_2)
            cx = cell_x + k * (cell_w + 0.06)
            rounded_rect(slide, cx, cell_y, cell_w, 0.5, col,
                         line_color=BORDER, line_w=0.5)
            tc = BG_DEEP if k in hl else WHITE
            tb(slide, str(val), cx, cell_y + 0.08, cell_w, 0.35,
               size=12, bold=True, color=tc, align=PP_ALIGN.CENTER,
               font_name="Menlo")
        # Labels below
        if items:
            tb(slide, "front", cell_x, cell_y + 0.6, cell_w, 0.25,
               size=9, color=ROSE, align=PP_ALIGN.CENTER, bold=True)
            last_x = cell_x + (len(items) - 1) * (cell_w + 0.06)
            tb(slide, "back", last_x, cell_y + 0.6, cell_w, 0.25,
               size=9, color=EMERALD, align=PP_ALIGN.CENTER, bold=True)
        # Property note
        if len(items) > 1:
            tb(slide, "→ monoton turun", sx, sy_top + 1.6, 3.0, 0.3,
               size=10, color=PRIMARY, italic=True, align=PP_ALIGN.CENTER)

    # Slide: Full trace
    slide = new_slide(prs)
    slide_header(slide, "Sliding Window Max — Full Trace",
                 "A = [1, 3, -1, -3, 5, 3, 6, 7], k = 3")

    A = [1, 3, -1, -3, 5, 3, 6, 7]
    cell_w = 1.05
    array_x = 0.6
    array_y = 1.4
    array_cells(slide, A, array_x, array_y,
                cell_w=cell_w, cell_h=0.6,
                highlights={i: BG_CARD_2 for i in range(len(A))},
                value_size=14)

    # Trace table for each i
    rows = [
        ["0", "1",  "[0]",         "—"],
        ["1", "3",  "[1]",         "—"],
        [("2", AMBER), ("-1", AMBER), ("[1, 2]", AMBER), ("3", EMERALD)],
        [("3", AMBER), ("-3", AMBER), ("[1, 2, 3]", AMBER), ("3", EMERALD)],
        [("4", AMBER), ("5", AMBER), ("[4]", AMBER), ("5", EMERALD)],
        [("5", AMBER), ("3", AMBER), ("[4, 5]", AMBER), ("5", EMERALD)],
        [("6", AMBER), ("6", AMBER), ("[6]", AMBER), ("6", EMERALD)],
        [("7", AMBER), ("7", AMBER), ("[7]", AMBER), ("7", EMERALD)],
    ]
    styled_table(slide, ["i", "A[i]", "Deque (idx)", "Output"], rows,
                 0.5, 2.4, [0.7, 1.2, 4.0, 1.5], row_h=0.42,
                 header_colors=[PRIMARY, EMERALD, AMBER, ROSE],
                 body_size=10, header_size=10)

    # Right: result
    tb(slide, "📊 Output: [3, 3, 5, 5, 6, 7]",
       8.3, 1.4, 4.6, 0.4, size=13, bold=True, color=EMERALD,
       font_name="Menlo")
    array_cells(slide, [3, 3, 5, 5, 6, 7], 8.3, 1.95,
                cell_w=0.7, cell_h=0.55,
                highlights={i: EMERALD for i in range(6)},
                colors_map={i: BG_DEEP for i in range(6)})

    insight_card(slide, "💡 Mengapa O(n)?",
                 ["Setiap index push 1× ke deque",
                  "Setiap index pop 1× dari deque",
                  "→ Total operasi 2n = O(n)",
                  "Bukan O(nk) walau ada while!"],
                 8.3, 2.85, 4.6, 1.95)

    callout(slide, "Min: ubah '<=' jadi '>=' di pop_back",
            8.3, 4.95, 4.6, 0.55, color=PRIMARY, icon="🔄")

    insight_card(slide, "🎯 Tips Penting",
                 ["dq menyimpan INDEX (bukan value)",
                  "Cek out-of-window pakai i-k",
                  "Output mulai i ≥ k-1",
                  "Buat function monotonic = reusable"],
                 8.3, 5.65, 4.6, 1.6)

    # ── Section 04: Stream & BFS ───────────────────────────────
    section_divider(prs, "04", "First Non-Repeating & BFS Level",
                    "Aplikasi queue di stream processing & graph",
                    color=VIOLET)

    slide = new_slide(prs)
    slide_header(slide, "First Non-Repeating Character in Stream")

    code = """string firstNonRepeating(string stream) {
    queue<char> q;
    int freq[26] = {};
    string ans;

    for (char c : stream) {
        freq[c - 'a']++;
        q.push(c);
        // Buang dari depan kalau sudah duplikat
        while (!q.empty() && freq[q.front()-'a'] > 1)
            q.pop();
        ans += q.empty() ? '#' : q.front();
    }
    return ans;
}"""
    code_box(slide, code, 0.5, 1.1, 6.5, 4.5, font_size=11, accent=VIOLET)

    insight_card(slide, "🧠 Logic",
                 ["Queue tracks urutan masuk char",
                  "freq[] hitung kemunculan",
                  "Front yang freq>1 → buang",
                  "Front sekarang = first non-repeat"],
                 0.5, 5.75, 6.5, 1.5)

    # Right: full trace
    tb(slide, "🎬 Trace: stream = 'aabcc'",
       7.2, 1.1, 5.7, 0.4, size=13, bold=True, color=AMBER,
       font_name="Menlo")

    rows = [
        [("'a'", PRIMARY), "[a]",   "a=1",      "a"],
        [("'a'", AMBER), "[ ]",   "a=2 (pop)", "#"],
        [("'b'", PRIMARY), "[b]",   "b=1",      "b"],
        [("'c'", PRIMARY), "[b,c]", "c=1",      "b"],
        [("'c'", AMBER), "[b]",   "c=2 (pop)", "b"],
    ]
    styled_table(slide, ["c", "Queue", "freq update", "Output"], rows,
                 7.2, 1.7, [1.0, 1.5, 1.7, 1.5], row_h=0.5,
                 header_colors=[PRIMARY, EMERALD, AMBER, VIOLET],
                 body_size=10, header_size=10)

    callout(slide, "Result: 'a#bbb' (concat semua output)",
            7.2, 5.0, 5.7, 0.55, color=EMERALD, icon="🎯")

    insight_card(slide, "Variasi",
                 ["Cek char di interval (last 60 chars)",
                  "→ Pop juga saat keluar window",
                  "Pakai timestamp + map"],
                 7.2, 5.75, 5.7, 1.5)

    # Slide: BFS level order with visualization
    slide = new_slide(prs)
    slide_header(slide, "BFS Level-Order Traversal — Queue di Tree/Graph")

    code = """vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> res;
    if (!root) return res;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int sz = q.size();   // SIZE level saat ini
        vector<int> level;
        for (int i = 0; i < sz; i++) {
            auto* node = q.front(); q.pop();
            level.push_back(node->val);
            if (node->left)  q.push(node->left);
            if (node->right) q.push(node->right);
        }
        res.push_back(level);
    }
    return res;
}"""
    code_box(slide, code, 0.5, 1.1, 6.5, 5.0, font_size=10.5, accent=VIOLET)

    # Right: tree visualization with proper edges + level coloring
    tb(slide, "🌳 Tree dengan level coloring",
       7.2, 1.1, 5.7, 0.4, size=13, bold=True, color=AMBER)

    # Tree nodes by level
    tree_nodes = [
        ("3", 10.0, 1.85, PRIMARY),     # 0: root level 0
        ("9", 8.6,  3.1,  EMERALD),     # 1: level 1
        ("20", 11.4, 3.1, EMERALD),     # 2: level 1
        ("15", 10.5, 4.35, AMBER),      # 3: level 2
        ("7",  12.3, 4.35, AMBER),      # 4: level 2
    ]
    tree_edges = [(0, 1), (0, 2), (2, 3), (2, 4)]
    draw_tree(slide, tree_nodes, tree_edges,
              radius=0.32, value_size=13)

    # Level labels on left
    tb(slide, "L0", 7.6, 1.7, 0.6, 0.3, size=11, bold=True,
       color=PRIMARY, align=PP_ALIGN.CENTER)
    tb(slide, "L1", 7.6, 2.95, 0.6, 0.3, size=11, bold=True,
       color=EMERALD, align=PP_ALIGN.CENTER)
    tb(slide, "L2", 7.6, 4.2, 0.6, 0.3, size=11, bold=True,
       color=AMBER, align=PP_ALIGN.CENTER)

    # Output
    rounded_rect(slide, 7.2, 5.0, 5.7, 1.5, BG_CARD,
                 line_color=PRIMARY, line_w=1.2)
    rect(slide, 7.2, 5.0, 5.7, 0.06, PRIMARY)
    tb(slide, "📋 Output", 7.35, 5.1, 5.5, 0.32,
       size=12, bold=True, color=PRIMARY)
    tb(slide, "[ [3], [9, 20], [15, 7] ]",
       7.35, 5.45, 5.5, 0.4, size=14, bold=True, color=EMERALD,
       font_name="Menlo", align=PP_ALIGN.CENTER)
    tb(slide, "Level 0, Level 1, Level 2",
       7.35, 5.95, 5.5, 0.3, size=10, color=SLATE, italic=True,
       align=PP_ALIGN.CENTER)

    callout(slide, "Trick: simpan q.size() di awal level untuk pisah level",
            7.2, 6.6, 5.7, 0.5, color=AMBER, icon="💡")

    # ── Common Mistakes ────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Common Mistakes — Queue/Deque Pitfalls")
    mistakes = [
        ("1. Sliding window: pakai value bukan index",
         "deque<int> dq simpan INDEX!\nPakai A[dq.front()] untuk value.",
         ROSE),
        ("2. Lupa cek out-of-window",
         "while (dq.front() <= i-k) pop_front\nHarus di paling awal loop.",
         ROSE),
        ("3. Output mulai i=0",
         "Pertama kali window penuh: i=k-1.\nOutput hanya saat i ≥ k-1.",
         AMBER),
        ("4. Ambiguity '<' vs '<='",
         "Max: pop saat A[back] <= A[i]\nMin: pop saat A[back] >= A[i]",
         AMBER),
        ("5. BFS lupa simpan q.size()",
         "Tanpa fix size, infinite loop.\nSimpan sz = q.size() per level.",
         AMBER),
        ("6. Stream: lupa pop sampai habis",
         "while loop, bukan if!\nBisa banyak char yang sudah duplikat.",
         AMBER),
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

    # ── Cheatsheet ─────────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Cheatsheet — Queue/Deque Templates")

    cheat_left = """// === SLIDING WINDOW MAX ===
deque<int> dq;
vector<int> res;
for (int i = 0; i < n; i++) {
    while (!dq.empty() && dq.front() <= i-k)
        dq.pop_front();
    while (!dq.empty() && A[dq.back()] <= A[i])
        dq.pop_back();
    dq.push_back(i);
    if (i >= k-1)
        res.push_back(A[dq.front()]);
}

// === SLIDING WINDOW MIN ===
// Sama tapi: A[dq.back()] >= A[i]"""
    code_box(slide, cheat_left, 0.5, 1.1, 6.2, 5.7, font_size=10, accent=AMBER)

    cheat_right = """// === BFS LEVEL ORDER ===
queue<TreeNode*> q; q.push(root);
while (!q.empty()) {
    int sz = q.size();
    for (int i = 0; i < sz; i++) {
        auto* x = q.front(); q.pop();
        // process x
        if (x->l) q.push(x->l);
        if (x->r) q.push(x->r);
    }
    // level selesai
}

// === STREAM FIRST NON-REPEAT ===
queue<char> q; int freq[26] = {};
for (char c : stream) {
    freq[c-'a']++;  q.push(c);
    while (!q.empty() && freq[q.front()-'a']>1)
        q.pop();
    out += q.empty() ? '#' : q.front();
}"""
    code_box(slide, cheat_right, 6.8, 1.1, 6.0, 5.7, font_size=10, accent=PRIMARY)

    # ── Closing ─────────────────────────────────────────────────
    closing_slide(prs, 38, "Queue & Deque — fondasi BFS dan sliding window O(n)", [
        (PRIMARY, "Queue", "FIFO. push_back, pop_front. Pakai untuk BFS, simulasi, stream."),
        (EMERALD, "Deque", "2 ujung O(1). Bisa jadi stack atau queue. operator[] random access."),
        (AMBER, "Sliding Window", "Monotonic deque simpan INDEX. Setiap idx push/pop 1× → O(n)."),
        (VIOLET, "BFS Level", "Simpan q.size() per iterasi untuk pisah level. Stream + freq array."),
        (ROSE, "Pitfall", "Out-of-window check di awal. Output mulai i≥k-1. Stream pakai while."),
    ])

    save_presentation(prs, os.path.join(
        os.path.dirname(os.path.abspath(__file__)),
        "Day_38_Presentation.pptx"))


if __name__ == "__main__":
    main()
