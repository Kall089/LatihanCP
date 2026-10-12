#!/usr/bin/env python3
"""Day 57 — Graph Representation: adj list, adj matrix, edge list.
Rich visuals untuk setiap representasi."""
import sys, os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..")))
from pptx_lib import *


def main():
    prs = make_presentation()

    # ── Cover ────────────────────────────────────────────────────
    def cov_deco(slide):
        labels = ["Adj List", "Adj Matrix", "Edge List"]
        cols = [PRIMARY, EMERALD, AMBER]
        for i, (lbl, col) in enumerate(zip(labels, cols)):
            cx = 6.4 + i * 1.95
            rounded_rect(slide, cx, 5.6, 1.85, 0.5, col)
            tb(slide, lbl, cx, 5.7, 1.85, 0.4,
               size=11, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)

    cover_slide(prs, 57, "Graph Representation",
                ["3 cara: Adjacency List · Matrix · Edge List",
                 "Pilih sesuai sparsity & operasi yang dibutuhkan"],
                decoration=cov_deco)

    # ── Agenda ───────────────────────────────────────────────────
    agenda_slide(prs, "Agenda — Day 57", [
        ("01", "Konsep\nGraph", PRIMARY,
         ["V & E", "Directed vs Undirected", "Weighted vs Unweighted", "Tree, DAG, dense, sparse"]),
        ("02", "Adjacency\nList", EMERALD,
         ["vector<vector<int>>", "Pair (v, w)", "O(V+E) memori", "Default CP"]),
        ("03", "Adjacency\nMatrix", AMBER,
         ["matrix V×V", "O(1) cek edge", "O(V²) memori", "Untuk dense graph"]),
        ("04", "Edge List &\nProperti", VIOLET,
         ["Sort by weight", "Untuk Kruskal", "Degree, in/out", "Pilih representasi"]),
    ])

    # ── Section 01: Konsep Graph ────────────────────────────────
    section_divider(prs, "01", "Konsep Graph",
                    "G = (V, E) — vertices dan edges, fondasi semua algoritma graph")

    # Slide: Visualisasi konsep graph
    slide = new_slide(prs)
    slide_header(slide, "Apa itu Graph? — Visualisasi V & E",
                 "Kumpulan node (V) yang terhubung oleh edge (E)")

    # Left: 4 examples of graph types
    tb(slide, "🔵 4 Jenis Graph Umum",
       0.5, 1.1, 6.5, 0.4, size=13, bold=True, color=AMBER)

    # 1. Undirected
    tb(slide, "1. Undirected", 0.6, 1.65, 2.8, 0.3,
       size=11, bold=True, color=PRIMARY)
    g1_nodes = [
        ("A", 1.1, 2.4, PRIMARY),
        ("B", 2.4, 2.4, PRIMARY),
        ("C", 1.75, 3.4, PRIMARY),
    ]
    g1_edges = [(0, 1), (0, 2), (1, 2)]
    draw_graph(slide, g1_nodes, g1_edges, radius=0.27, value_size=12)

    # 2. Directed
    tb(slide, "2. Directed", 4.0, 1.65, 2.8, 0.3,
       size=11, bold=True, color=EMERALD)
    g2_pos = [(4.4, 2.4), (5.7, 2.4), (5.05, 3.4)]
    g2_cols = [EMERALD] * 3
    g2_labels = ["A", "B", "C"]
    for (cx, cy), col, lbl in zip(g2_pos, g2_cols, g2_labels):
        graph_node(slide, cx, cy, lbl, color=col, radius=0.27, size=12)
    # Directed edges with arrows
    directed_edge(slide, g2_pos[0][0], g2_pos[0][1],
                  g2_pos[1][0], g2_pos[1][1], r1=0.27, r2=0.27,
                  color=EMERALD, thickness=1.75)
    directed_edge(slide, g2_pos[1][0], g2_pos[1][1],
                  g2_pos[2][0], g2_pos[2][1], r1=0.27, r2=0.27,
                  color=EMERALD, thickness=1.75)

    # 3. Weighted
    tb(slide, "3. Weighted", 0.6, 4.0, 2.8, 0.3,
       size=11, bold=True, color=AMBER)
    g3_nodes = [
        ("A", 1.1, 4.85, AMBER),
        ("B", 2.4, 4.85, AMBER),
        ("C", 1.75, 5.85, AMBER),
    ]
    g3_edges = [(0, 1), (0, 2), (1, 2)]
    g3_labels = {(0, 1): "5", (0, 2): "3", (1, 2): "2"}
    draw_graph(slide, g3_nodes, g3_edges, radius=0.27, value_size=12,
               edge_labels=g3_labels)

    # 4. DAG
    tb(slide, "4. DAG", 4.0, 4.0, 2.8, 0.3,
       size=11, bold=True, color=VIOLET)
    g4_pos = [(4.4, 4.85), (5.7, 4.85), (5.05, 5.85)]
    for (cx, cy), lbl in zip(g4_pos, ["A", "B", "C"]):
        graph_node(slide, cx, cy, lbl, color=VIOLET, radius=0.27, size=12)
    directed_edge(slide, g4_pos[0][0], g4_pos[0][1],
                  g4_pos[1][0], g4_pos[1][1], r1=0.27, r2=0.27,
                  color=VIOLET, thickness=1.75)
    directed_edge(slide, g4_pos[0][0], g4_pos[0][1],
                  g4_pos[2][0], g4_pos[2][1], r1=0.27, r2=0.27,
                  color=VIOLET, thickness=1.75)
    directed_edge(slide, g4_pos[1][0], g4_pos[1][1],
                  g4_pos[2][0], g4_pos[2][1], r1=0.27, r2=0.27,
                  color=VIOLET, thickness=1.75)

    # Right: Terminology table
    tb(slide, "📚 Terminologi Penting",
       7.2, 1.1, 5.7, 0.4, size=13, bold=True, color=AMBER)
    rows = [
        [("V (Vertex)", PRIMARY),    "Node / titik"],
        [("E (Edge)",   EMERALD),    "Sambungan antar V"],
        [("Degree",     AMBER),      "Jumlah tetangga V"],
        [("Path",       VIOLET),     "Jalur antar V"],
        [("Cycle",      ROSE),       "Path balik ke awal"],
        [("Connected",  PRIMARY),    "Bisa dijangkau"],
    ]
    styled_table(slide, ["Istilah", "Makna"], rows,
                 7.2, 1.7, [2.0, 3.7], row_h=0.5,
                 header_colors=[PRIMARY, EMERALD],
                 body_size=10, header_size=10)

    insight_card(slide, "Sparsity",
                 ["Sparse: E ≪ V² (umum di CP)",
                  "Dense: E ≈ V² (jarang di CP)",
                  "Tree: E = V-1 (special)",
                  "Complete: E = V(V-1)/2"],
                 7.2, 5.0, 5.7, 1.95)

    # ── Section 02: Adjacency List ──────────────────────────────
    section_divider(prs, "02", "Adjacency List",
                    "Default representation untuk CP — O(V+E) memori",
                    color=EMERALD)

    slide = new_slide(prs)
    slide_header(slide, "Adjacency List — Konsep & Visualisasi",
                 "Tiap node menyimpan daftar tetangganya")

    # Left: graph + adj list visualization
    tb(slide, "🕸️ Graph (undirected, weighted)",
       0.5, 1.1, 6.0, 0.4, size=13, bold=True, color=AMBER)

    # Visualize a 4-node graph
    g_nodes = [
        ("1", 1.5, 2.8, PRIMARY),
        ("2", 4.5, 2.8, PRIMARY),
        ("3", 1.5, 5.0, PRIMARY),
        ("4", 4.5, 5.0, PRIMARY),
    ]
    g_edges = [(0, 1), (0, 2), (1, 3), (2, 3)]
    g_labels = {(0, 1): "3", (0, 2): "5", (1, 3): "2", (2, 3): "1"}
    draw_graph(slide, g_nodes, g_edges, radius=0.4, value_size=15,
               edge_labels=g_labels)

    # Right: adjacency list visualization
    tb(slide, "📋 Adjacency List Visual",
       7.0, 1.1, 5.9, 0.4, size=13, bold=True, color=PRIMARY)

    adj_data = [
        ("1", [("2", "3"), ("3", "5")], PRIMARY),
        ("2", [("1", "3"), ("4", "2")], PRIMARY),
        ("3", [("1", "5"), ("4", "1")], PRIMARY),
        ("4", [("2", "2"), ("3", "1")], PRIMARY),
    ]
    for i, (node, neighbors, col) in enumerate(adj_data):
        ty = 1.7 + i * 0.78
        # Node label box
        rounded_rect(slide, 7.0, ty, 0.7, 0.55, col)
        tb(slide, node, 7.0, ty + 0.1, 0.7, 0.4,
           size=14, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER,
           font_name="Menlo")
        # Arrow
        arrow(slide, 7.75, ty + 0.275, 8.0, ty + 0.275,
              color=col, thickness=1.5)
        # Neighbor list
        for k, (v, w) in enumerate(neighbors):
            cx = 8.05 + k * 1.7
            rounded_rect(slide, cx, ty, 1.5, 0.55, BG_CARD,
                         line_color=col, line_w=0.75)
            tb(slide, f"({v},{w})", cx, ty + 0.15, 1.5, 0.32,
               size=11, bold=True, color=col, align=PP_ALIGN.CENTER,
               font_name="Menlo")
            if k < len(neighbors) - 1:
                arrow(slide, cx + 1.55, ty + 0.275,
                      cx + 1.7, ty + 0.275,
                      color=col, thickness=1.0)

    # Code at bottom
    code = """vector<vector<pair<int,int>>> adj(n + 1);
adj[u].push_back({v, w});  adj[v].push_back({u, w});
for (auto [v, w] : adj[u])  // iterasi tetangga"""
    plain_code_box(slide, code, 0.5, 5.9, 12.4, 1.3, font_size=11,
                   accent=EMERALD)

    # Slide: Complexity & when to use
    slide = new_slide(prs)
    slide_header(slide, "Adjacency List — Kompleksitas & Kapan Pakai")

    # Complexity table
    rows = [
        [("Tambah edge", PRIMARY), "O(1) amortized"],
        [("Cek edge(u,v)", AMBER), "O(degree(u))"],
        [("Iterasi tetangga u", EMERALD), "O(degree(u))"],
        [("Iterasi semua", VIOLET), "O(V + E)"],
        [("Memori", ROSE),         "O(V + E)"],
    ]
    styled_table(slide, ["Operasi", "Kompleksitas"], rows,
                 0.5, 1.2, [3.5, 3.0], row_h=0.55,
                 header_colors=[PRIMARY, EMERALD])

    # When to use card
    info_card(slide, "✓ Kapan Pakai?",
              [("Graph sparse (E ≪ V²)", EMERALD),
               ("V besar (sampai 10⁵+)", EMERALD),
               ("BFS, DFS, Dijkstra,", EMERALD),
               ("  Bellman-Ford, dll", EMERALD)],
              0.5, 5.0, 6.5, 2.1, accent=EMERALD)

    # Right: Code patterns
    code = """// === UNWEIGHTED, UNDIRECTED ===
vector<vector<int>> adj(n + 1);
for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
}

// === WEIGHTED, UNDIRECTED ===
vector<vector<pair<int,int>>> adj(n + 1);
for (int i = 0; i < m; i++) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

// === ITERASI TETANGGA ===
for (auto [v, w] : adj[u]) {
    // proses edge u→v dengan berat w
}"""
    code_box(slide, code, 7.2, 1.2, 5.7, 6.0, font_size=10, accent=PRIMARY)

    # ── Section 03: Adjacency Matrix ────────────────────────────
    section_divider(prs, "03", "Adjacency Matrix",
                    "Matrix V×V — O(1) cek edge, tapi O(V²) memori",
                    color=AMBER)

    slide = new_slide(prs)
    slide_header(slide, "Adjacency Matrix — Konsep & Visualisasi",
                 "matrix[u][v] = weight (atau 0/INF jika tidak ada)")

    # Left: graph
    tb(slide, "🕸️ Graph (directed)",
       0.5, 1.1, 6.0, 0.4, size=13, bold=True, color=AMBER)

    g_nodes = [
        ("1", 1.5, 2.6, AMBER),
        ("2", 4.5, 2.6, AMBER),
        ("3", 1.5, 4.4, AMBER),
        ("4", 4.5, 4.4, AMBER),
    ]
    # Directed edges 1→2, 1→3, 2→4, 3→4
    g_edges_dir = [(0, 1), (0, 2), (1, 3), (2, 3)]
    # Draw nodes
    for n in g_nodes:
        graph_node(slide, n[1], n[2], n[0], color=n[3], radius=0.4, size=15)
    # Directed edges with arrows
    for i, j in g_edges_dir:
        directed_edge(slide, g_nodes[i][1], g_nodes[i][2],
                      g_nodes[j][1], g_nodes[j][2],
                      r1=0.4, r2=0.4, color=SLATE, thickness=1.75)

    callout(slide, "Edges: 1→2, 1→3, 2→4, 3→4",
            0.5, 5.3, 6.0, 0.55, color=AMBER, icon="🎯")

    # Right: matrix visualization
    tb(slide, "📊 Adjacency Matrix",
       6.8, 1.1, 6.0, 0.4, size=13, bold=True, color=PRIMARY)

    # 5x5 matrix (header row + 4 data rows)
    mat = [
        ["", "1", "2", "3", "4"],
        ["1", "0", "1", "1", "0"],
        ["2", "0", "0", "0", "1"],
        ["3", "0", "0", "0", "1"],
        ["4", "0", "0", "0", "0"],
    ]
    cell_size = 0.8
    mat_x = 7.5
    mat_y = 1.7
    for r in range(5):
        for c in range(5):
            cx = mat_x + c * cell_size
            cy = mat_y + r * cell_size
            val = mat[r][c]
            if r == 0 or c == 0:
                # Header
                col = AMBER
                rect(slide, cx, cy, cell_size, cell_size, BG_CARD,
                     line_color=col, line_w=0.75)
                tb(slide, val, cx, cy + 0.2, cell_size, cell_size - 0.3,
                   size=14, bold=True, color=AMBER, align=PP_ALIGN.CENTER,
                   font_name="Menlo")
            else:
                if val == "1":
                    rect(slide, cx, cy, cell_size, cell_size, EMERALD,
                         line_color=BORDER, line_w=0.5)
                    tc = BG_DEEP
                else:
                    rect(slide, cx, cy, cell_size, cell_size, BG_CARD_2,
                         line_color=BORDER, line_w=0.5)
                    tc = MUTED
                tb(slide, val, cx, cy + 0.2, cell_size, cell_size - 0.3,
                   size=14, bold=True, color=tc, align=PP_ALIGN.CENTER,
                   font_name="Menlo")

    callout(slide, "mat[u][v] = 1 jika ada edge u→v",
            6.8, 6.05, 6.0, 0.5, color=EMERALD, icon="🎯")

    # Code
    code = """vector<vector<int>> mat(n+1, vector<int>(n+1, 0));
mat[u][v] = 1;   // (atau weight jika weighted)
if (mat[u][v]) {/* ada edge */}"""
    plain_code_box(slide, code, 0.5, 6.0, 6.2, 1.2, font_size=11,
                   accent=AMBER)

    # Slide: Complexity & when to use
    slide = new_slide(prs)
    slide_header(slide, "Adjacency Matrix — Pros, Cons, Kapan Pakai")

    # Pros vs Cons
    info_card(slide, "✓ Pros",
              [("Tambah edge: O(1)", EMERALD),
               ("Cek edge(u,v): O(1) ⚡", EMERALD),
               ("Sederhana, tidak tricky", EMERALD),
               ("Cocok untuk Floyd-Warshall", EMERALD)],
              0.5, 1.2, 6.2, 2.5, accent=EMERALD)

    info_card(slide, "✗ Cons",
              [("Memori O(V²) — boros!", ROSE),
               ("Iterasi tetangga: O(V)", ROSE),
               ("V=10⁵ → MLE 10¹⁰ bytes", ROSE),
               ("Tidak efektif untuk sparse", ROSE)],
              6.85, 1.2, 6.0, 2.5, accent=ROSE)

    # When to use
    rounded_rect(slide, 0.5, 3.85, 12.4, 2.5, BG_CARD,
                 line_color=AMBER, line_w=1.2)
    rect(slide, 0.5, 3.85, 12.4, 0.06, AMBER)
    tb(slide, "🎯 Kapan Pakai Adjacency Matrix?",
       0.65, 3.95, 12.0, 0.35, size=14, bold=True, color=AMBER)

    items = [
        "✓ Graph dense — E ≈ V² (graph hampir complete)",
        "✓ V kecil — V ≤ 1000 (memori 4 MB OK)",
        "✓ Algoritma Floyd-Warshall: O(V³) all-pairs SP",
        "✓ Sering query 'apakah ada edge u→v?'",
        "✗ JANGAN jika V > 5000 atau graph sparse — pakai adj list",
    ]
    for i, item in enumerate(items):
        col = EMERALD if item.startswith("✓") else ROSE
        tb(slide, item, 0.7, 4.4 + i * 0.4, 12.0, 0.35,
           size=11, color=col, font_name="Menlo")

    # Bottom: comparison metrics
    metric_card(slide, "V=100",  "40 KB",   0.5, 6.6, 4.0, 0.7, accent=EMERALD)
    metric_card(slide, "V=1000", "4 MB",    4.7, 6.6, 4.0, 0.7, accent=AMBER)
    metric_card(slide, "V=10⁵",  "40 GB ✗", 8.9, 6.6, 4.0, 0.7, accent=ROSE)

    # ── Section 04: Edge List ──────────────────────────────────
    section_divider(prs, "04", "Edge List & Properti",
                    "Edge List untuk Kruskal & Bellman-Ford",
                    color=VIOLET)

    slide = new_slide(prs)
    slide_header(slide, "Edge List — Visualisasi & Sort by Weight",
                 "Simpan semua edge sebagai array tuple")

    # Left: graph with weights
    tb(slide, "🕸️ Graph (undirected, weighted)",
       0.5, 1.1, 6.0, 0.4, size=13, bold=True, color=AMBER)

    g_nodes = [
        ("1", 1.5, 2.6, VIOLET),
        ("2", 4.5, 2.6, VIOLET),
        ("3", 1.5, 4.4, VIOLET),
        ("4", 4.5, 4.4, VIOLET),
    ]
    g_edges = [(0, 1), (0, 2), (1, 3), (2, 3)]
    g_labels = {(0, 1): "3", (0, 2): "5", (1, 3): "2", (2, 3): "1"}
    draw_graph(slide, g_nodes, g_edges, radius=0.4, value_size=15,
               edge_labels=g_labels)

    # Right: edge list before/after sort
    tb(slide, "📋 Edge List Format: (w, u, v)",
       6.8, 1.1, 6.0, 0.4, size=13, bold=True, color=PRIMARY)

    # Before sort
    tb(slide, "Sebelum sort:", 6.8, 1.65, 6.0, 0.3,
       size=11, bold=True, color=ROSE)
    edges_before = [("3", "1", "2"), ("5", "1", "3"), ("2", "2", "4"), ("1", "3", "4")]
    for i, (w, u, v) in enumerate(edges_before):
        cy = 2.05 + i * 0.42
        rounded_rect(slide, 6.8, cy, 6.0, 0.36, BG_CARD,
                     line_color=ROSE, line_w=0.5)
        tb(slide, f"({w}, {u}, {v})", 6.8, cy + 0.04, 6.0, 0.28,
           size=12, bold=True, color=ROSE, align=PP_ALIGN.CENTER,
           font_name="Menlo")

    arrow(slide, 9.8, 3.9, 9.8, 4.25, color=EMERALD, thickness=2.0)
    tb(slide, "sort by weight",
       8.5, 4.0, 2.5, 0.3, size=10, italic=True, color=EMERALD,
       align=PP_ALIGN.CENTER)

    # After sort
    tb(slide, "Setelah sort:", 6.8, 4.4, 6.0, 0.3,
       size=11, bold=True, color=EMERALD)
    edges_after = [("1", "3", "4"), ("2", "2", "4"), ("3", "1", "2"), ("5", "1", "3")]
    for i, (w, u, v) in enumerate(edges_after):
        cy = 4.8 + i * 0.42
        rounded_rect(slide, 6.8, cy, 6.0, 0.36, BG_CARD,
                     line_color=EMERALD, line_w=0.5)
        tb(slide, f"({w}, {u}, {v})", 6.8, cy + 0.04, 6.0, 0.28,
           size=12, bold=True, color=EMERALD, align=PP_ALIGN.CENTER,
           font_name="Menlo")

    callout(slide, "Sort = ready untuk Kruskal MST",
            6.8, 6.6, 6.0, 0.5, color=EMERALD, icon="🎯")

    code = """vector<tuple<int,int,int>> edges;
edges.push_back({w, u, v});
sort(edges.begin(), edges.end());"""
    plain_code_box(slide, code, 0.5, 5.45, 6.0, 1.5, font_size=11,
                   accent=AMBER)

    # Slide: Comparison + Decision Guide
    slide = new_slide(prs)
    slide_header(slide, "🎯 Pilih Representasi: Decision Guide")

    # Big comparison table
    rows = [
        [("Tambah edge",    PRIMARY), "O(1)*",       "O(1)",       "O(1)"],
        [("Cek edge(u,v)",  AMBER),   "O(deg)",      "O(1) ⚡",     "O(E)"],
        [("Iter tetangga",  EMERALD), "O(deg) ⚡",    "O(V)",       "O(E)"],
        [("Iter semua",     VIOLET),  "O(V+E) ⚡",    "O(V²)",      "O(E)"],
        [("Memori",         ROSE),    "O(V+E) ⚡",    "O(V²)",      "O(E)"],
    ]
    styled_table(slide, ["Operasi", "Adj List", "Adj Matrix", "Edge List"],
                 rows, 0.5, 1.2, [3.0, 3.1, 3.1, 3.1], row_h=0.5,
                 header_colors=[PRIMARY, EMERALD, AMBER, VIOLET])

    # Algorithm-specific recommendations
    tb(slide, "🚀 Rekomendasi per Algoritma",
       0.5, 4.45, 12.4, 0.4, size=14, bold=True, color=AMBER,
       align=PP_ALIGN.CENTER)

    algos = [
        ("BFS / DFS",     "Adj List ✓✓",  EMERALD),
        ("Dijkstra",      "Adj List ✓✓",  EMERALD),
        ("Floyd-Warshall","Adj Matrix ✓✓", AMBER),
        ("Kruskal MST",   "Edge List ✓✓", VIOLET),
        ("Bellman-Ford",  "Edge List ✓✓", VIOLET),
        ("Topological",   "Adj List ✓✓",  EMERALD),
    ]
    for i, (algo, rec, col) in enumerate(algos):
        cn = i % 3
        rn = i // 3
        cx = 0.5 + cn * 4.2
        cy = 4.95 + rn * 0.95
        rounded_rect(slide, cx, cy, 4.0, 0.85, BG_CARD,
                     line_color=col, line_w=1.0)
        rect(slide, cx, cy, 4.0, 0.06, col)
        tb(slide, algo, cx + 0.2, cy + 0.13, 3.6, 0.3,
           size=11, bold=True, color=col)
        tb(slide, rec, cx + 0.2, cy + 0.45, 3.6, 0.32,
           size=11, color=SILVER, font_name="Menlo")

    # ── Common Mistakes ────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Common Mistakes — Graph Pitfalls")
    mistakes = [
        ("1. Adj matrix V=10⁵",
         "Memori 10¹⁰ bytes = MLE!\nGraph besar wajib adj list.",
         ROSE),
        ("2. Lupa edge balik undirected",
         "adj[u].push(v); → wajib\nadj[v].push(u); juga.",
         ROSE),
        ("3. 0-indexed vs 1-indexed",
         "Cek input format!\nVector size n+1 untuk 1-indexed.",
         AMBER),
        ("4. Tipe data weight",
         "Weight bisa > 10⁹ → pakai ll.\nDijkstra dist juga ll.",
         AMBER),
        ("5. Self-loop & multi-edge",
         "Beberapa soal allow, beberapa tidak.\nBaca constraint dengan teliti.",
         AMBER),
        ("6. Adj list untuk Floyd-Warshall",
         "Floyd butuh O(V³) iterasi V×V.\nAdj matrix lebih natural.",
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
    slide_header(slide, "Cheatsheet — 3 Representations")

    cheat_left = """// === ADJACENCY LIST ===
// Default untuk CP
vector<vector<pair<int,int>>> adj(n + 1);
adj[u].push_back({v, w});
adj[v].push_back({u, w});

for (auto [v, w] : adj[u]) {
    // proses edge u→v dengan w
}

// Memori: O(V + E)
// Operasi tetangga: O(degree)


// === ADJACENCY MATRIX ===
vector<vector<int>> mat(n+1, vector<int>(n+1, 0));
mat[u][v] = w;     mat[v][u] = w;
if (mat[u][v]) ... // O(1) cek

// Memori: O(V²) — V ≤ 1000"""
    code_box(slide, cheat_left, 0.5, 1.1, 6.2, 5.7, font_size=10, accent=PRIMARY)

    cheat_right = """// === EDGE LIST ===
// Untuk Kruskal MST, Bellman-Ford
vector<tuple<int,int,int>> edges;
for (...) edges.push_back({w, u, v});
sort(edges.begin(), edges.end());

for (auto [w, u, v] : edges) {
    // proses dalam urutan weight
}


// === DECISION GUIDE ===
// Sparse + V besar  → Adj List (default)
// Dense atau V<1k   → Adj Matrix
// Kruskal MST       → Edge List
// Bellman-Ford      → Edge List

// === COMMON STRUCT ===
struct Edge { int u, v, w; };
vector<Edge> edges;"""
    code_box(slide, cheat_right, 6.8, 1.1, 6.0, 5.7, font_size=10, accent=AMBER)

    # ── Closing ─────────────────────────────────────────────────
    closing_slide(prs, 57, "Graph Representation — pilih sesuai sparsity & operasi", [
        (PRIMARY, "Adj List", "Default CP. O(V+E) memori. Cocok untuk BFS/DFS/Dijkstra."),
        (EMERALD, "Adj Matrix", "V×V matrix. O(1) cek edge. Cocok dense graph & Floyd-Warshall."),
        (AMBER, "Edge List", "Sort by weight ready. Untuk Kruskal MST & Bellman-Ford."),
        (VIOLET, "Decision", "Sparse → adj list. Dense+V<1k → matrix. MST → edge list."),
        (ROSE, "Pitfall", "Adj matrix V=10⁵ MLE. Lupa edge balik undirected. Tipe weight ll."),
    ])

    save_presentation(prs, os.path.join(
        os.path.dirname(os.path.abspath(__file__)),
        "Day_57_Presentation.pptx"))


if __name__ == "__main__":
    main()
