#!/usr/bin/env python3
"""Day 39 — Priority Queue & Heap Applications: Kth largest, merge K, median.
Rich visuals untuk setiap subtopik."""
import sys, os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..")))
from pptx_lib import *


def main():
    prs = make_presentation()

    # ── Cover ────────────────────────────────────────────────────
    def cov_deco(slide):
        labels = ["Max-Heap", "Min-Heap", "Dijkstra"]
        cols = [PRIMARY, EMERALD, AMBER]
        for i, (lbl, col) in enumerate(zip(labels, cols)):
            cx = 6.4 + i * 1.95
            rounded_rect(slide, cx, 5.6, 1.85, 0.5, col)
            tb(slide, lbl, cx, 5.7, 1.85, 0.4,
               size=11, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)

    cover_slide(prs, 39, "Priority Queue & Heap",
                ["Max/Min Heap · K-th · Merge K · Dijkstra",
                 "Pola powerful untuk problem optimization"],
                decoration=cov_deco)

    # ── Agenda ───────────────────────────────────────────────────
    agenda_slide(prs, "Agenda — Day 39", [
        ("01", "Heap\nFundamental", PRIMARY,
         ["Complete bin tree", "Max vs Min heap", "Kompleksitas", "STL pq"]),
        ("02", "K-th Largest\n& Merge K", EMERALD,
         ["Min-heap size K", "Top-K pattern", "Merge K sorted", "O(N log K)"]),
        ("03", "Median\nStream", AMBER,
         ["Two heaps trick", "max + min", "Balance invariant", "O(log n) per add"]),
        ("04", "Dijkstra &\nTask Scheduler", VIOLET,
         ["Shortest path", "Stale entry skip", "Greedy w/ heap", "Aplikasi nyata"]),
    ])

    # ── Section 01 ───────────────────────────────────────────────
    section_divider(prs, "01", "Heap Fundamental",
                    "Complete binary tree dengan heap property")

    # Slide: Heap visualisasi (max-heap as binary tree + array)
    slide = new_slide(prs)
    slide_header(slide, "Apa itu Heap? — Tree + Array Representation",
                 "Complete binary tree, parent ≥/≤ children")

    # Left: max-heap as tree
    tb(slide, "🌳 MAX-HEAP — root = max",
       0.5, 1.1, 6.0, 0.4, size=13, bold=True, color=AMBER)

    # Tree of [50, 30, 40, 10, 20, 35, 25]
    tree_nodes = [
        ("50", 3.4, 1.95, AMBER),    # 0: root
        ("30", 1.8, 3.0,  PRIMARY),  # 1
        ("40", 5.0, 3.0,  PRIMARY),  # 2
        ("10", 1.0, 4.05, EMERALD),  # 3
        ("20", 2.6, 4.05, EMERALD),  # 4
        ("35", 4.2, 4.05, EMERALD),  # 5
        ("25", 5.8, 4.05, EMERALD),  # 6
    ]
    tree_edges = [(0, 1), (0, 2), (1, 3), (1, 4), (2, 5), (2, 6)]
    draw_tree(slide, tree_nodes, tree_edges,
              radius=0.32, value_size=13)

    # Array representation below tree
    tb(slide, "Array (level-order):",
       0.5, 4.8, 6.0, 0.3, size=11, bold=True, color=AMBER)
    array_cells(slide, [50, 30, 40, 10, 20, 35, 25], 0.5, 5.2,
                cell_w=0.78, cell_h=0.5,
                highlights={0: AMBER},
                colors_map={0: BG_DEEP},
                value_size=12)

    # Index formula
    rounded_rect(slide, 0.5, 6.0, 6.0, 1.2, BG_CARD,
                 line_color=PRIMARY, line_w=1.0)
    rect(slide, 0.5, 6.0, 6.0, 0.06, PRIMARY)
    tb(slide, "📐 Index Formula",
       0.65, 6.1, 5.7, 0.3, size=11, bold=True, color=PRIMARY)
    tb(slide, "parent(i) = (i-1)/2     left(i) = 2i+1",
       0.65, 6.42, 5.7, 0.32, size=11, color=AMBER, font_name="Menlo")
    tb(slide, "right(i) = 2i+2",
       0.65, 6.78, 5.7, 0.32, size=11, color=AMBER, font_name="Menlo")

    # Right: complexity table + comparison
    tb(slide, "📊 Kompleksitas Heap",
       7.0, 1.1, 6.0, 0.4, size=13, bold=True, color=AMBER)
    rows = [
        [("push", PRIMARY),     "O(log n)", "Sift-up"],
        [("top", EMERALD),      "O(1)",     "Lihat root"],
        [("pop", AMBER),        "O(log n)", "Sift-down"],
        [("build", VIOLET),     "O(n)",     "Heapify"],
        ["Find arbitrary",      "O(n)",     "Bukan BST"],
    ]
    styled_table(slide, ["Operasi", "Time", "Cara"], rows,
                 7.0, 1.7, [2.0, 1.7, 2.3], row_h=0.5,
                 header_colors=[PRIMARY, EMERALD, AMBER],
                 body_size=10, header_size=10)

    insight_card(slide, "💡 Why Heap di CP?",
                 ["Get max/min cepat O(1)",
                  "Insert/remove O(log n)",
                  "Tidak butuh sort dulu",
                  "Cocok untuk Top-K, Dijkstra"],
                 7.0, 4.65, 6.0, 1.7)

    callout(slide, "Heap = root selalu yang 'paling penting'",
            7.0, 6.5, 6.0, 0.6, color=EMERALD, icon="🎯")

    # Slide: priority_queue STL
    slide = new_slide(prs)
    slide_header(slide, "priority_queue STL — Max & Min Heap")

    code = """#include <queue>

// === MAX-HEAP (default) — top = max ===
priority_queue<int> maxPQ;
maxPQ.push(x);    // O(log n)
maxPQ.top();      // O(1)
maxPQ.pop();      // O(log n)
maxPQ.size();
maxPQ.empty();

// === MIN-HEAP — top = min ===
priority_queue<int, vector<int>,
               greater<int>> minPQ;

// === CUSTOM COMPARATOR ===
struct Cmp {
    bool operator()(const T& a, const T& b) const {
        return a.dist > b.dist; // min-heap by dist
    }
};
priority_queue<T, vector<T>, Cmp> pq;"""
    code_box(slide, code, 0.5, 1.1, 6.5, 5.7, font_size=11, accent=PRIMARY)

    # Right: visual showing push/pop sequence
    tb(slide, "🎬 push 5 → push 3 → push 8 → pop",
       7.2, 1.1, 5.7, 0.4, size=12, bold=True, color=AMBER)

    pq_stages = [
        ("push 5",  [5],          {0: PRIMARY},  "top=5"),
        ("push 3",  [5, 3],       {0: AMBER, 1: SLATE}, "top=5"),
        ("push 8",  [8, 3, 5],    {0: EMERALD},  "top=8"),
        ("pop",     [5, 3],       {0: AMBER, 1: SLATE}, "top=5"),
    ]
    for i, (lbl, items, hl, top_str) in enumerate(pq_stages):
        sx = 7.2 + (i % 2) * 3.0
        sy_top = 1.7 + (i // 2) * 2.7
        rounded_rect(slide, sx, sy_top, 2.8, 2.4, BG_CARD,
                     line_color=BORDER, line_w=0.5)
        tb(slide, lbl, sx, sy_top + 0.05, 2.8, 0.3,
           size=10, bold=True, color=AMBER, align=PP_ALIGN.CENTER)
        # Tree-like structure (simple horizontal)
        cell_w = 0.55
        cell_x = sx + (2.8 - len(items) * (cell_w + 0.06)) / 2
        cell_y = sy_top + 0.6
        for k, val in enumerate(items):
            col = hl.get(k, BG_CARD_2)
            cx = cell_x + k * (cell_w + 0.06)
            rounded_rect(slide, cx, cell_y, cell_w, 0.5, col,
                         line_color=BORDER, line_w=0.5)
            tc = BG_DEEP if k in hl else WHITE
            tb(slide, str(val), cx, cell_y + 0.08, cell_w, 0.35,
               size=12, bold=True, color=tc, align=PP_ALIGN.CENTER,
               font_name="Menlo")
        tb(slide, top_str, sx, sy_top + 1.6, 2.8, 0.3,
           size=11, bold=True, color=PRIMARY, italic=True,
           align=PP_ALIGN.CENTER, font_name="Menlo")

    # ── Section 02: K-th Largest ──────────────────────────────
    section_divider(prs, "02", "K-th Largest & Merge K",
                    "Min-heap size K untuk efisiensi memori",
                    color=EMERALD)

    slide = new_slide(prs)
    slide_header(slide, "K-th Largest — Min-Heap Size K",
                 "Counter-intuitive: pakai MIN-heap untuk cari LARGEST")

    code = """int kthLargest(vector<int>& A, int k) {
    priority_queue<int, vector<int>,
                   greater<int>> minPQ;  // ← min-heap!
    for (int x : A) {
        minPQ.push(x);
        if ((int)minPQ.size() > k)
            minPQ.pop();   // buang yang kecil
    }
    return minPQ.top();    // top = K-th largest
}

// K-th SMALLEST: pakai MAX-heap size K
priority_queue<int> maxPQ;
// pop saat size > k (buang yang besar)"""
    code_box(slide, code, 0.5, 1.1, 6.5, 4.5, font_size=11, accent=EMERALD)

    insight_card(slide, "🧠 Mengapa min-heap?",
                 ["Heap berisi K largest sementara",
                  "Top = yang TERKECIL di antara K largest",
                  "Saat ada elemen baru:",
                  "  jika > top → masuk, top dipop",
                  "Akhir: top = K-th largest"],
                 0.5, 5.75, 6.5, 1.5)

    # Right: visual trace
    tb(slide, "🎬 A = [3, 2, 1, 5, 6, 4], k = 2",
       7.2, 1.1, 5.7, 0.4, size=12, bold=True, color=AMBER,
       font_name="Menlo")

    rows = [
        [("3", PRIMARY), "[3]",         "size=1"],
        [("2", PRIMARY), "[2, 3]",      "size=2"],
        [("1", AMBER),   "[1, 3]→[2,3]", "1<min, pop"],
        [("5", PRIMARY), "[2,3,5]→[3,5]","push, pop 2"],
        [("6", PRIMARY), "[3,5,6]→[5,6]","push, pop 3"],
        [("4", AMBER),   "[4,5,6]→[5,6]","4<5, pop 4"],
    ]
    styled_table(slide, ["x", "minPQ", "Aksi"], rows,
                 7.2, 1.7, [0.7, 2.0, 3.0], row_h=0.45,
                 header_colors=[PRIMARY, EMERALD, AMBER],
                 body_size=10, header_size=10)

    callout(slide, "minPQ.top() = 5 → 2nd largest!",
            7.2, 4.6, 5.7, 0.55, color=EMERALD, icon="🎯")

    # Slide: Merge K sorted lists
    slide = new_slide(prs)
    slide_header(slide, "Merge K Sorted Lists — Min-Heap O(N log K)")

    code = """// min-heap of (val, list_idx, elem_idx)
priority_queue<tuple<int,int,int>,
               vector<tuple<int,int,int>>,
               greater<>> pq;

// Init: push first elem of each list
for (int i = 0; i < K; i++)
    if (!lists[i].empty())
        pq.push({lists[i][0], i, 0});

vector<int> result;
while (!pq.empty()) {
    auto [v, li, ei] = pq.top(); pq.pop();
    result.push_back(v);
    // Push next elem from same list
    if (ei + 1 < (int)lists[li].size())
        pq.push({lists[li][ei+1], li, ei+1});
}"""
    code_box(slide, code, 0.5, 1.1, 6.5, 5.5, font_size=10.5, accent=AMBER)

    # Right: visual
    tb(slide, "🎯 3 lists merging",
       7.2, 1.1, 5.7, 0.4, size=13, bold=True, color=PRIMARY)

    # Show 3 lists
    lists_data = [
        ("L0", [1, 4, 7], PRIMARY),
        ("L1", [2, 5, 8], EMERALD),
        ("L2", [3, 6, 9], AMBER),
    ]
    for i, (name, lst, col) in enumerate(lists_data):
        ly = 1.7 + i * 0.7
        tb(slide, name, 7.2, ly, 0.5, 0.4,
           size=12, bold=True, color=col)
        for k, val in enumerate(lst):
            cx = 7.75 + k * 0.65
            rounded_rect(slide, cx, ly, 0.55, 0.4, col,
                         line_color=BORDER, line_w=0.5)
            tb(slide, str(val), cx, ly + 0.06, 0.55, 0.3,
               size=11, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER,
               font_name="Menlo")

    # Arrow down
    arrow(slide, 9.5, 3.85, 9.5, 4.25, color=VIOLET, thickness=2.5)
    tb(slide, "min-heap merge", 8.5, 4.0, 2.5, 0.3,
       size=10, italic=True, color=VIOLET, align=PP_ALIGN.CENTER)

    # Result
    tb(slide, "Result:", 7.2, 4.4, 0.8, 0.3,
       size=12, bold=True, color=EMERALD)
    array_cells(slide, [1, 2, 3, 4, 5, 6, 7, 8, 9], 7.2, 4.7,
                cell_w=0.62, cell_h=0.5,
                highlights={i: EMERALD for i in range(9)},
                colors_map={i: BG_DEEP for i in range(9)},
                value_size=11)

    metric_card(slide, "Time", "O(N log K)", 7.2, 5.6, 2.7, 1.0, accent=PRIMARY)
    metric_card(slide, "Space", "O(K)", 10.1, 5.6, 2.8, 1.0, accent=EMERALD)

    callout(slide, "N=total elemen, K=jumlah list",
            7.2, 6.75, 5.7, 0.4, color=AMBER, icon="📊")

    # ── Section 03: Median Stream ──────────────────────────────
    section_divider(prs, "03", "Median dari Data Stream",
                    "Two heaps trick — divide elements jadi 2 setengah",
                    color=AMBER)

    slide = new_slide(prs)
    slide_header(slide, "MedianFinder — 2 Heap Side by Side",
                 "max-heap (lower half) + min-heap (upper half)")

    # Left: Visual of two heaps
    tb(slide, "🎯 Konsep: Bagi Array Jadi 2",
       0.5, 1.1, 6.5, 0.4, size=13, bold=True, color=AMBER)

    # Visual: number line with median
    line_y = 2.5
    rect(slide, 0.5, line_y - 0.04, 6.5, 0.05, SLATE)
    # Lower half (red side)
    rect(slide, 0.5, line_y - 0.03, 3.0, 0.05, ROSE)
    tb(slide, "Lower (max-heap)", 0.5, line_y + 0.15, 3.0, 0.3,
       size=10, bold=True, color=ROSE, align=PP_ALIGN.CENTER)
    # Upper half (green side)
    rect(slide, 4.0, line_y - 0.03, 3.0, 0.05, EMERALD)
    tb(slide, "Upper (min-heap)", 4.0, line_y + 0.15, 3.0, 0.3,
       size=10, bold=True, color=EMERALD, align=PP_ALIGN.CENTER)
    # Median marker
    circle(slide, 3.5, line_y, 0.18, AMBER)
    tb(slide, "median", 3.0, line_y + 0.5, 1.0, 0.3,
       size=11, bold=True, color=AMBER, align=PP_ALIGN.CENTER)

    # Two heaps visualization
    # Lower heap
    info_card(slide, "maxH (lower)",
              [("Top = MAX of lower", ROSE),
               ("Berisi 1/2 elemen kiri", SILVER),
               ("Sebagai TINGGI:", SILVER),
               ("3 → 2 → 1", SLATE)],
              0.5, 3.2, 3.1, 2.4, accent=ROSE)
    info_card(slide, "minH (upper)",
              [("Top = MIN of upper", EMERALD),
               ("Berisi 1/2 elemen kanan", SILVER),
               ("Sebagai TINGGI:", SILVER),
               ("4 → 5 → 6", SLATE)],
              3.7, 3.2, 3.1, 2.4, accent=EMERALD)

    # Median formula
    rounded_rect(slide, 0.5, 5.85, 6.5, 1.4, BG_CARD,
                 line_color=AMBER, line_w=1.2)
    rect(slide, 0.5, 5.85, 6.5, 0.08, AMBER)
    tb(slide, "📐 Rumus Median",
       0.65, 5.95, 6.2, 0.32, size=12, bold=True, color=AMBER)
    tb(slide, "ganjil: maxH.top()",
       0.65, 6.3, 6.2, 0.32, size=11, color=ROSE, font_name="Menlo")
    tb(slide, "genap: (maxH.top() + minH.top()) / 2.0",
       0.65, 6.62, 6.2, 0.32, size=11, color=EMERALD, font_name="Menlo")

    # Right: code
    code = """class MedianFinder {
    priority_queue<int> maxH;  // lower
    priority_queue<int, vector<int>,
                   greater<int>> minH; // upper

public:
    void addNum(int num) {
        maxH.push(num);
        minH.push(maxH.top()); maxH.pop();
        if (maxH.size() < minH.size()) {
            maxH.push(minH.top()); minH.pop();
        }
    }
    double findMedian() {
        if (maxH.size() > minH.size())
            return maxH.top();
        return (maxH.top()+minH.top()) / 2.0;
    }
};"""
    code_box(slide, code, 7.2, 1.1, 5.7, 5.5, font_size=10, accent=PRIMARY)

    callout(slide, "addNum O(log n) · findMedian O(1)",
            7.2, 6.7, 5.7, 0.5, color=EMERALD, icon="⚡")

    # Slide: Trace median for stream
    slide = new_slide(prs)
    slide_header(slide, "MedianFinder — Step-by-Step Trace",
                 "Stream: 1, 2, 3, 4, 5")

    rows = [
        [("add 1", PRIMARY), "[1]",       "[]",       "1.0"],
        [("add 2", PRIMARY), "[1]",       "[2]",      "1.5"],
        [("add 3", PRIMARY), "[2, 1]",    "[3]",      "2.0"],
        [("add 4", PRIMARY), "[2, 1]",    "[3, 4]",   "2.5"],
        [("add 5", PRIMARY), "[3, 2, 1]", "[4, 5]",   "3.0"],
    ]
    styled_table(slide, ["Aksi", "maxH (lower)", "minH (upper)", "Median"],
                 rows, 0.5, 1.2, [2.0, 3.0, 3.0, 2.0], row_h=0.6,
                 header_colors=[PRIMARY, ROSE, EMERALD, AMBER])

    # Visual after add 5 (rightmost state)
    tb(slide, "📊 Setelah 'add 5':",
       0.5, 5.3, 12.4, 0.3, size=13, bold=True, color=AMBER,
       align=PP_ALIGN.CENTER)

    # max heap on left, min heap on right
    # Lower (max heap) = [3, 2, 1] (3 at top)
    # Upper (min heap) = [4, 5] (4 at top)
    # Visualize as small trees
    # maxH tree
    maxH_nodes = [
        ("3", 3.0, 5.95, ROSE),
        ("2", 2.2, 6.7, ROSE),
        ("1", 3.8, 6.7, ROSE),
    ]
    maxH_edges = [(0, 1), (0, 2)]
    draw_tree(slide, maxH_nodes, maxH_edges,
              radius=0.32, value_size=14)
    tb(slide, "maxH", 2.5, 5.65, 1.0, 0.3,
       size=11, bold=True, color=ROSE)

    # Median in middle
    circle(slide, 6.5, 6.3, 0.35, AMBER)
    tb(slide, "3.0", 6.0, 6.18, 1.0, 0.3,
       size=14, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
    tb(slide, "median", 6.0, 6.65, 1.0, 0.3,
       size=10, bold=True, color=AMBER, align=PP_ALIGN.CENTER)

    # minH tree
    minH_nodes = [
        ("4", 9.5, 5.95, EMERALD),
        ("5", 8.7, 6.7, EMERALD),
    ]
    minH_edges = [(0, 1)]
    draw_tree(slide, minH_nodes, minH_edges,
              radius=0.32, value_size=14)
    tb(slide, "minH", 9.0, 5.65, 1.0, 0.3,
       size=11, bold=True, color=EMERALD)

    callout(slide, "size: 3 vs 2 → ganjil → median = maxH.top() = 3",
            0.5, 7.05, 12.4, 0.4, color=PRIMARY, icon="🎯")

    # ── Section 04: Dijkstra ───────────────────────────────────
    section_divider(prs, "04", "Dijkstra & Task Scheduler",
                    "Aplikasi heap di shortest path & greedy scheduling",
                    color=VIOLET)

    slide = new_slide(prs)
    slide_header(slide, "Dijkstra Shortest Path — Min-heap O((V+E) log V)")

    code = """const ll INF = 1e18;
vector<ll> dijkstra(int s, int n,
        vector<vector<pair<int,int>>>& adj) {
    vector<ll> dist(n+1, INF);
    dist[s] = 0;
    priority_queue<pair<ll,int>, vector<pair<ll,int>>,
                   greater<>> pq;  // min-heap
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;  // STALE!
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}"""
    code_box(slide, code, 0.5, 1.1, 7.0, 5.5, font_size=10, accent=VIOLET)

    # Right: graph visualization
    tb(slide, "🕸️ Contoh graph & shortest path",
       7.7, 1.1, 5.3, 0.4, size=12, bold=True, color=AMBER)

    # Simple weighted graph
    graph_nodes = [
        ("0", 8.4, 2.0,  AMBER),     # 0: start
        ("1", 11.0, 1.85, PRIMARY),
        ("2", 9.4,  3.4,  PRIMARY),
        ("3", 12.0, 3.5,  EMERALD),
        ("4", 10.2, 5.0,  EMERALD),
    ]
    graph_edges = [(0, 1), (0, 2), (1, 3), (2, 3), (2, 4), (3, 4)]
    edge_labels = {
        (0, 1): "4",
        (0, 2): "1",
        (1, 3): "5",
        (2, 3): "3",
        (2, 4): "8",
        (3, 4): "2",
    }
    draw_graph(slide, graph_nodes, graph_edges,
               radius=0.32, value_size=13, edge_labels=edge_labels)

    # Result table
    tb(slide, "Shortest from 0:", 7.7, 5.55, 5.3, 0.3,
       size=11, bold=True, color=EMERALD)
    rows = [
        ["0", "0"],
        ["1", "4"],
        ["2", "1"],
        ["3", "4"],
        ["4", "6"],
    ]
    styled_table(slide, ["node", "dist"], rows,
                 7.7, 5.9, [1.5, 1.5], row_h=0.32,
                 header_colors=[PRIMARY, EMERALD],
                 body_size=9, header_size=9)

    callout(slide, "if (d > dist[u]) continue → skip stale entry",
            0.5, 6.75, 7.0, 0.45, color=ROSE, icon="⚠")

    # Slide: Task Scheduler
    slide = new_slide(prs)
    slide_header(slide, "Task Scheduler — Greedy with Max-Heap")

    code = """// tasks=['A','A','A','B','B','B'], n=2
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
        if (maxPQ.empty()) break;
        time += cycle + 1;  // idle slots
    }
    return time;
}"""
    code_box(slide, code, 0.5, 1.1, 7.0, 5.7, font_size=10, accent=AMBER)

    # Right: Visualize execution
    tb(slide, "🎯 Visualisasi cycle (n=2)",
       7.7, 1.1, 5.3, 0.4, size=12, bold=True, color=PRIMARY)

    # 2 cycles of 3 slots
    cycle_data = [
        ("Cycle 1", [("A", AMBER), ("B", PRIMARY), ("idle", DIM)]),
        ("Cycle 2", [("A", AMBER), ("B", PRIMARY), ("idle", DIM)]),
        ("Cycle 3", [("A", AMBER), ("B", PRIMARY), (None, None)]),
    ]
    cell_w = 1.5
    cell_h = 0.55
    for ci, (label, slots) in enumerate(cycle_data):
        cy = 1.7 + ci * 1.0
        tb(slide, label, 7.7, cy, 1.4, 0.3,
           size=11, bold=True, color=AMBER)
        for si, slot in enumerate(slots):
            if slot[0] is None:
                continue
            cx = 9.2 + si * 1.2
            col = slot[1]
            rounded_rect(slide, cx, cy, cell_w * 0.7, cell_h, col,
                         line_color=BORDER, line_w=0.5)
            tc = WHITE if col == DIM else BG_DEEP
            tb(slide, slot[0], cx, cy + 0.15, cell_w * 0.7, 0.3,
               size=11, bold=True, color=tc, align=PP_ALIGN.CENTER,
               font_name="Menlo")

    callout(slide, "Total = 8 slots (6 task + 2 idle)",
            7.7, 5.0, 5.3, 0.55, color=EMERALD, icon="🎯")

    insight_card(slide, "🧠 Greedy Insight",
                 ["Pilih task terbanyak dulu",
                  "Tunggu cooldown n",
                  "→ idle saat tidak ada task ready",
                  "Heap = ambil top freq tiap cycle"],
                 7.7, 5.7, 5.3, 1.5)

    # ── Common Mistakes ────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Common Mistakes — Heap Pitfalls")
    mistakes = [
        ("1. Default = max-heap",
         "priority_queue<int> = MAX!\nUntuk min: greater<int>().",
         ROSE),
        ("2. Comparator logika balik",
         "comp(a,b)=true → b di atas a.\nMin-heap: a > b (bukan a < b!).",
         ROSE),
        ("3. Lupa stale entry skip",
         "Dijkstra: cek if (d > dist[u]) continue.\nTanpa ini, salah / lambat.",
         AMBER),
        ("4. Heap bukan untuk find arbitrary",
         "Cari elemen tertentu di heap = O(n).\nPakai BST/set kalau perlu.",
         AMBER),
        ("5. Modify top()",
         "top() readonly! Pop dulu, push baru.\nLangsung modify → invalid heap.",
         AMBER),
        ("6. Custom compare lambda",
         "decltype trick atau struct functor.\nLambda biasa tidak bisa di pq.",
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
    slide_header(slide, "Cheatsheet — Priority Queue Templates")

    cheat_left = """// === MAX-HEAP (default) ===
priority_queue<int> maxPQ;

// === MIN-HEAP ===
priority_queue<int, vector<int>, greater<int>> minPQ;

// === K-th LARGEST ===
priority_queue<int, vector<int>, greater<int>> pq;
for (int x : A) {
    pq.push(x);
    if (pq.size() > k) pq.pop();
}
return pq.top();

// === MERGE K SORTED ===
priority_queue<tuple<int,int,int>, ..., greater<>> pq;
for (int i = 0; i < K; i++)
    if (!lists[i].empty()) pq.push({lists[i][0], i, 0});"""
    code_box(slide, cheat_left, 0.5, 1.1, 6.2, 5.7, font_size=10, accent=PRIMARY)

    cheat_right = """// === DIJKSTRA ===
vector<ll> dist(n, INF); dist[s] = 0;
priority_queue<pii, vector<pii>, greater<>> pq;
pq.push({0, s});
while (!pq.empty()) {
    auto [d, u] = pq.top(); pq.pop();
    if (d > dist[u]) continue;  // STALE!
    for (auto [v, w] : adj[u])
        if (dist[u] + w < dist[v]) {
            dist[v] = dist[u] + w;
            pq.push({dist[v], v});
        }
}

// === MEDIAN STREAM ===
priority_queue<int> maxH;          // lower
priority_queue<int, vector<int>,
               greater<>> minH;    // upper"""
    code_box(slide, cheat_right, 6.8, 1.1, 6.0, 5.7, font_size=10, accent=AMBER)

    # ── Closing ─────────────────────────────────────────────────
    closing_slide(prs, 39, "Priority Queue & Heap — top-K, merge K, Dijkstra", [
        (PRIMARY, "Heap Basics", "Complete bin tree. push/pop O(log n), top O(1). build O(n)."),
        (EMERALD, "K-th Largest", "Min-heap size K. Counter-intuitive! top = K-th largest."),
        (AMBER, "Median Stream", "2 heap trick. addNum O(log n), median O(1)."),
        (VIOLET, "Dijkstra", "Min-heap (dist, node). Cek stale entry: if d > dist[u]."),
        (ROSE, "Pitfall", "Default max-heap. Min butuh greater<>. Cek stale di Dijkstra."),
    ])

    save_presentation(prs, os.path.join(
        os.path.dirname(os.path.abspath(__file__)),
        "Day_39_Presentation.pptx"))


if __name__ == "__main__":
    main()
