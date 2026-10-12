#!/usr/bin/env python3
"""Day 58 — BFS (Breadth-First Search): level-order, shortest path, multi-source.
Rich visuals untuk setiap subtopik."""
import sys, os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..")))
from pptx_lib import *


def main():
    prs = make_presentation()

    # ── Cover ────────────────────────────────────────────────────
    def cov_deco(slide):
        labels = ["Level 0", "Level 1", "Level 2"]
        cols = [PRIMARY, AMBER, EMERALD]
        for i, (lbl, col) in enumerate(zip(labels, cols)):
            cx = 6.5 + i * 1.95
            rounded_rect(slide, cx, 5.6, 1.85, 0.5, col)
            tb(slide, lbl, cx, 5.7, 1.85, 0.4,
               size=11, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)

    cover_slide(prs, 58, "BFS — Breadth-First Search",
                ["Level-order · Shortest Path · Multi-source",
                 "Queue-based traversal yang fundamental"],
                decoration=cov_deco)

    # ── Agenda ───────────────────────────────────────────────────
    agenda_slide(prs, "Agenda — Day 58", [
        ("01", "Konsep\nBFS", PRIMARY,
         ["Level-order", "Queue FIFO", "Tinta menyebar", "O(V+E)"]),
        ("02", "Algoritma\n& Trace", EMERALD,
         ["Pseudocode", "Step-by-step trace", "dist[] array", "prev[] untuk path"]),
        ("03", "Shortest\nPath", AMBER,
         ["Unweighted graph", "Path reconstruction", "Why optimal?", "BFS vs Dijkstra"]),
        ("04", "Grid &\nMulti-source", VIOLET,
         ["Grid 4-arah", "8-arah variant", "Multi-source BFS", "Aplikasi & tips"]),
    ])

    # ── Section 01 ───────────────────────────────────────────────
    section_divider(prs, "01", "Konsep BFS",
                    "Level per level dari source — seperti tinta menyebar")

    slide = new_slide(prs)
    slide_header(slide, "BFS — Visualisasi Level-Order",
                 "Mulai dari source, lalu ke jarak 1, jarak 2, ...")

    # Big graph visualization with levels
    tb(slide, "🌊 BFS dari node S — kunjungi level by level",
       0.5, 1.1, 12.4, 0.4, size=14, bold=True, color=AMBER,
       align=PP_ALIGN.CENTER)

    # Big graph: S in center, 3 levels around
    g_nodes = [
        ("S", 6.7, 2.5,  AMBER),    # 0: source - level 0
        ("A", 4.8, 2.5,  PRIMARY),  # 1: level 1
        ("B", 8.6, 2.5,  PRIMARY),  # 2: level 1
        ("C", 6.7, 1.0,  PRIMARY),  # 3: level 1
        ("D", 3.0, 2.5,  EMERALD),  # 4: level 2
        ("E", 4.8, 4.0,  EMERALD),  # 5: level 2
        ("F", 8.6, 4.0,  EMERALD),  # 6: level 2
        ("G", 10.4, 2.5, EMERALD),  # 7: level 2
        ("H", 6.7, 5.5,  VIOLET),   # 8: level 3
    ]
    g_edges = [
        (0, 1), (0, 2), (0, 3),    # S to level 1
        (1, 4), (1, 5),            # A to level 2
        (2, 6), (2, 7),            # B to level 2
        (5, 8), (6, 8),            # level 2 to H (level 3)
    ]
    draw_graph(slide, g_nodes, g_edges, radius=0.4,
               value_size=15)

    # Level labels
    tb(slide, "Level 0", 6.5, 2.0, 0.6, 0.3,
       size=9, bold=True, color=AMBER, align=PP_ALIGN.CENTER)
    tb(slide, "Level 1", 5.7, 1.7, 0.6, 0.3,
       size=9, bold=True, color=PRIMARY, align=PP_ALIGN.CENTER)
    tb(slide, "Level 2", 9.5, 4.0, 0.6, 0.3,
       size=9, bold=True, color=EMERALD, align=PP_ALIGN.CENTER)
    tb(slide, "Level 3", 6.5, 5.95, 0.6, 0.3,
       size=9, bold=True, color=VIOLET, align=PP_ALIGN.CENTER)

    # Bottom info
    rounded_rect(slide, 0.5, 6.4, 12.4, 0.7, BG_CARD,
                 line_color=PRIMARY, line_w=1.0)
    rect(slide, 0.5, 6.4, 12.4, 0.06, PRIMARY)
    tb(slide, "🎯 BFS Order: S → A,B,C → D,E,F,G → H",
       0.5, 6.55, 12.4, 0.45, size=14, bold=True, color=PRIMARY,
       align=PP_ALIGN.CENTER, font_name="Menlo")

    # Slide: properties & complexity
    slide = new_slide(prs)
    slide_header(slide, "Properti BFS — Mengapa Powerful?")

    info_card(slide, "🔑 Properti Inti", [
        "1. Struktur: Queue (FIFO)",
        "2. Traversal: level per level",
        "3. dist[v] = jumlah edge minimum",
        "   dari source ke v",
        "4. Setiap node dikunjungi 1×",
    ], 0.5, 1.1, 6.0, 3.0, accent=PRIMARY)

    info_card(slide, "📊 Kompleksitas",
              [("Time: O(V + E)", EMERALD),
               ("  setiap V & E diproses 1×", SLATE),
               ("Space: O(V) — queue + dist", EMERALD),
               ("Optimal untuk unweighted", AMBER)],
              0.5, 4.25, 6.0, 2.5, accent=EMERALD)

    # Right: BFS vs DFS comparison
    tb(slide, "🆚 BFS vs DFS",
       6.7, 1.1, 6.2, 0.4, size=13, bold=True, color=AMBER)
    rows = [
        [("Struktur", PRIMARY), "Queue", "Stack/recursion"],
        [("Order",    EMERALD), "Level-by-level", "Depth-first"],
        [("SP unweighted", AMBER), ("✓ Optimal", EMERALD), ("✗ Tidak", ROSE)],
        [("Memori",   VIOLET),  "O(V) (level lebar)", "O(V) (depth)"],
        [("Use case", ROSE),    "Shortest path,\nlevel order", "Cycle detect,\ntopo sort"],
    ]
    styled_table(slide, ["Aspek", "BFS", "DFS"], rows,
                 6.7, 1.7, [1.7, 2.2, 2.3], row_h=0.7,
                 header_colors=[PRIMARY, EMERALD, AMBER],
                 body_size=10, header_size=10)

    callout(slide, "BFS pertama kali capai v = jarak terpendek",
            6.7, 6.0, 6.2, 0.55, color=EMERALD, icon="🎯")

    # ── Section 02: Algoritma & Trace ───────────────────────────
    section_divider(prs, "02", "Algoritma & Trace",
                    "Step-by-step dengan queue dan dist array",
                    color=EMERALD)

    slide = new_slide(prs)
    slide_header(slide, "BFS Algoritma — Implementasi C++")

    code = """vector<int> bfs(int s, int n,
                vector<vector<int>>& adj) {
    vector<int> dist(n + 1, -1);  // -1 = unvisited
    queue<int> q;
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int v : adj[u]) {
            if (dist[v] == -1) {       // belum visit
                dist[v] = dist[u] + 1; // jarak +1
                q.push(v);
            }
        }
    }
    return dist;  // -1 jika tidak terjangkau
}"""
    code_box(slide, code, 0.5, 1.1, 6.5, 5.5, font_size=11, accent=EMERALD)

    insight_card(slide, "🧠 3 Bagian Utama",
                 ["1. Init: dist=-1, push source",
                  "2. Loop: pop, expand tetangga",
                  "3. Cek dist=-1 sebelum push",
                  "→ pastikan visit 1×"],
                 0.5, 6.75, 6.5, 0.5)

    # Right: full trace
    tb(slide, "🎬 Trace BFS dari node 1",
       7.2, 1.1, 5.7, 0.4, size=13, bold=True, color=AMBER)

    # Mini graph
    g_nodes = [
        ("1", 8.3, 1.95, AMBER),
        ("2", 10.2, 1.95, PRIMARY),
        ("3", 8.3, 3.5, PRIMARY),
        ("4", 10.2, 3.5, EMERALD),
    ]
    g_edges = [(0, 1), (0, 2), (1, 3), (2, 3)]
    draw_graph(slide, g_nodes, g_edges, radius=0.32, value_size=13)

    # Trace table
    rows = [
        ["init", "[1]",     "1:0"],
        ["pop 1", "[2,3]",  "1:0,2:1,3:1"],
        ["pop 2", "[3,4]",  "1:0,2:1,3:1,4:2"],
        ["pop 3", "[4]",    "(4 visited)"],
        [("pop 4", EMERALD), ("[]", EMERALD), ("DONE", EMERALD)],
    ]
    styled_table(slide, ["Step", "Queue", "dist[]"], rows,
                 7.2, 4.5, [1.3, 1.7, 2.7], row_h=0.42,
                 header_colors=[PRIMARY, EMERALD, AMBER],
                 body_size=9, header_size=9)

    callout(slide, "Hasil: dist=[-,0,1,1,2]",
            7.2, 6.85, 5.7, 0.4, color=AMBER, icon="🎯")

    # Slide: Detailed trace with graph state
    slide = new_slide(prs)
    slide_header(slide, "Visualisasi BFS — Setiap Langkah")

    # 4 stages of BFS visualization
    stages = [
        ("1. Init: push 1", 0,
         {0: AMBER}, "queue=[1]"),
        ("2. Pop 1, push 2,3", 1,
         {0: SLATE, 1: PRIMARY, 2: PRIMARY}, "queue=[2,3]"),
        ("3. Pop 2, push 4", 2,
         {0: SLATE, 1: SLATE, 2: PRIMARY, 3: EMERALD}, "queue=[3,4]"),
        ("4. Pop 3,4: done", 3,
         {0: SLATE, 1: SLATE, 2: SLATE, 3: SLATE}, "queue=[]"),
    ]

    g_layout = [(1.5, 2.3), (3.0, 2.3), (1.5, 3.6), (3.0, 3.6)]
    g_labels = ["1", "2", "3", "4"]
    g_edges = [(0, 1), (0, 2), (1, 3), (2, 3)]

    for stage_i, (title, _, hl_map, qstr) in enumerate(stages):
        cn = stage_i % 2
        rn = stage_i // 2
        ox = cn * 6.4
        oy = rn * 3.0
        # Frame
        rounded_rect(slide, 0.5 + ox, 1.2 + oy, 6.0, 2.8, BG_CARD,
                     line_color=BORDER, line_w=0.5)
        tb(slide, title, 0.6 + ox, 1.25 + oy, 5.8, 0.3,
           size=11, bold=True, color=AMBER)

        # Draw mini graph
        for i, (cx, cy) in enumerate(g_layout):
            col = hl_map.get(i, BG_CARD_2)
            tc = BG_DEEP if i in hl_map else WHITE
            cx_real = cx + ox
            cy_real = cy + oy
            # Note: tree_edge & graph_node don't take ox/oy
            graph_node(slide, cx_real, cy_real, g_labels[i],
                       color=col, radius=0.27, size=12, text_color=tc)
        for i, j in g_edges:
            x1, y1 = g_layout[i][0] + ox, g_layout[i][1] + oy
            x2, y2 = g_layout[j][0] + ox, g_layout[j][1] + oy
            tree_edge(slide, x1, y1, x2, y2, r1=0.27, r2=0.27,
                      color=SLATE, thickness=1.5)

        # Draw mini graph again (nodes on top)
        for i, (cx, cy) in enumerate(g_layout):
            col = hl_map.get(i, BG_CARD_2)
            tc = BG_DEEP if i in hl_map else WHITE
            graph_node(slide, cx + ox, cy + oy, g_labels[i],
                       color=col, radius=0.27, size=12, text_color=tc)

        # Queue string
        tb(slide, qstr, 4.3 + ox, 2.6 + oy, 2.0, 0.3,
           size=11, bold=True, color=PRIMARY, font_name="Menlo")

    # ── Section 03: Shortest Path ──────────────────────────────
    section_divider(prs, "03", "Shortest Path Unweighted",
                    "BFS otomatis menemukan jalur terpendek (jumlah edge)",
                    color=AMBER)

    slide = new_slide(prs)
    slide_header(slide, "Shortest Path + Path Reconstruction")

    code = """vector<int> shortest_path(int src, int dst, int n,
                          vector<vector<int>>& adj) {
    vector<int> dist(n+1, -1), prev(n+1, -1);
    queue<int> q;
    dist[src] = 0;  q.push(src);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == dst) break;
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                prev[v] = u;          // ← simpan parent!
                q.push(v);
            }
        }
    }

    if (dist[dst] == -1) return {};
    // Rekonstruksi path: trace dst→src via prev[]
    vector<int> path;
    for (int v = dst; v != -1; v = prev[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}"""
    code_box(slide, code, 0.5, 1.1, 7.5, 5.7, font_size=10, accent=AMBER)

    # Right: visualization
    tb(slide, "🎯 Shortest Path 1 → 5",
       8.2, 1.1, 4.7, 0.4, size=13, bold=True, color=PRIMARY)

    # Graph with path highlighted
    g_nodes = [
        ("1", 9.0,  2.3, AMBER),
        ("2", 11.0, 2.3, EMERALD),    # in path
        ("3", 9.0,  3.8, PRIMARY),
        ("4", 11.0, 3.8, PRIMARY),
        ("5", 12.5, 3.05, EMERALD),   # in path (dst)
    ]
    g_edges_all = [(0, 1), (0, 2), (1, 3), (1, 4), (2, 3), (3, 4), (1, 4), (4, 4)]
    g_path_edges = [(0, 1, EMERALD), (1, 4, EMERALD)]  # 1→2→5
    # Draw all edges as default first
    other_edges = [(0, 1), (0, 2), (1, 3), (2, 3), (3, 4)]
    for i, j in other_edges:
        tree_edge(slide, g_nodes[i][1], g_nodes[i][2],
                  g_nodes[j][1], g_nodes[j][2],
                  r1=0.32, r2=0.32, color=SLATE, thickness=1.0)
    # Path edge highlighted
    tree_edge(slide, g_nodes[0][1], g_nodes[0][2],
              g_nodes[1][1], g_nodes[1][2],
              r1=0.32, r2=0.32, color=EMERALD, thickness=3.0)
    # Add edge from node 2 (idx 1) to node 5 (idx 4)
    tree_edge(slide, g_nodes[1][1], g_nodes[1][2],
              g_nodes[4][1], g_nodes[4][2],
              r1=0.32, r2=0.32, color=EMERALD, thickness=3.0)

    # Nodes on top
    for n in g_nodes:
        graph_node(slide, n[1], n[2], n[0], color=n[3], radius=0.32, size=13)

    # Path output
    rounded_rect(slide, 8.2, 4.7, 4.7, 1.0, BG_CARD,
                 line_color=EMERALD, line_w=1.2)
    rect(slide, 8.2, 4.7, 4.7, 0.06, EMERALD)
    tb(slide, "🎯 Path: 1 → 2 → 5",
       8.35, 4.8, 4.5, 0.32, size=13, bold=True, color=EMERALD,
       font_name="Menlo")
    tb(slide, "Length = 2 edges",
       8.35, 5.15, 4.5, 0.3, size=11, color=AMBER, font_name="Menlo")
    tb(slide, "Trace prev: 5←2←1",
       8.35, 5.45, 4.5, 0.3, size=10, color=SLATE, italic=True,
       font_name="Menlo")

    insight_card(slide, "🧠 Intuisi prev[]",
                 ["Saat pertama kali capai v,",
                  "  parent paling optimal",
                  "Trace back: dst → src",
                  "Reverse → src → dst"],
                 8.2, 5.8, 4.7, 1.4)

    # ── Section 04: Grid & Multi-source ────────────────────────
    section_divider(prs, "04", "Grid BFS & Multi-source",
                    "Aplikasi BFS pada grid 2D & multiple sources",
                    color=VIOLET)

    slide = new_slide(prs)
    slide_header(slide, "BFS Grid — 4-arah Movement",
                 "Setiap sel = node, edge ke 4 tetangga")

    code = """int dx[] = {-1, 1,  0, 0};
int dy[] = { 0, 0, -1, 1};

int bfs_grid(int sr, int sc, int er, int ec) {
    vector<vector<int>> dist(R, vector<int>(C, -1));
    queue<pair<int,int>> q;
    dist[sr][sc] = 0;
    q.push({sr, sc});

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (r == er && c == ec) return dist[r][c];
        for (int d = 0; d < 4; d++) {
            int nr = r + dx[d], nc = c + dy[d];
            if (nr>=0 && nr<R && nc>=0 && nc<C
                && grid[nr][nc] != '#'
                && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }
    return -1;
}"""
    code_box(slide, code, 0.5, 1.1, 6.5, 5.7, font_size=10, accent=VIOLET)

    # Right: grid visualization
    tb(slide, "🗺️ Grid 5×5 BFS dari S",
       7.2, 1.1, 5.7, 0.4, size=13, bold=True, color=AMBER)

    # 5x5 grid
    grid_data = [
        ["S", "1", "2", "#", "5"],
        ["1", "#", "3", "#", "4"],
        ["2", "3", "4", "#", "3"],
        ["3", "#", "5", "#", "2"],
        ["4", "5", "6", "5", "1"],
    ]
    cell_size = 0.65
    gx, gy = 7.5, 1.7
    for r in range(5):
        for c in range(5):
            cx = gx + c * cell_size
            cy = gy + r * cell_size
            val = grid_data[r][c]
            if val == "#":
                col = BG_DEEP
                tc = ROSE
            elif val == "S":
                col = AMBER
                tc = BG_DEEP
            elif val.isdigit():
                # Color by distance (level)
                dist_int = int(val)
                if dist_int == 0:
                    col = AMBER
                elif dist_int == 1:
                    col = PRIMARY
                elif dist_int == 2:
                    col = EMERALD
                elif dist_int <= 3:
                    col = VIOLET
                elif dist_int <= 5:
                    col = ROSE
                else:
                    col = BG_CARD_2
                tc = BG_DEEP if dist_int <= 5 else WHITE
            else:
                col = BG_CARD_2
                tc = WHITE
            rect(slide, cx, cy, cell_size, cell_size, col,
                 line_color=BORDER, line_w=0.5)
            tb(slide, val, cx, cy + 0.2, cell_size, cell_size - 0.3,
               size=12, bold=True, color=tc, align=PP_ALIGN.CENTER,
               font_name="Menlo")

    # Legend
    tb(slide, "🎨 Color = jarak dari S",
       7.2, 5.2, 5.7, 0.3, size=11, bold=True, color=AMBER)
    legends = [
        ("S", AMBER), ("1-2", PRIMARY), ("3", VIOLET),
        ("4-5", ROSE), ("#", ROSE),
    ]
    for i, (lbl, col) in enumerate(legends):
        cx = 7.2 + i * 1.15
        rounded_rect(slide, cx, 5.55, 1.1, 0.4, col)
        tb(slide, lbl, cx, 5.6, 1.1, 0.3,
           size=10, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)

    callout(slide, "Cek (1) batas, (2) bukan tembok, (3) belum visit",
            7.2, 6.15, 5.7, 0.55, color=EMERALD, icon="🎯")

    # Slide: Multi-source BFS
    slide = new_slide(prs)
    slide_header(slide, "Multi-source BFS — Push Banyak Source Sekaligus")

    code = """vector<int> multi_bfs(vector<int>& sources, int n,
                       vector<vector<int>>& adj) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    // Push SEMUA source dengan dist = 0
    for (int s : sources) {
        dist[s] = 0;
        q.push(s);
    }
    // BFS normal selanjutnya
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}"""
    code_box(slide, code, 0.5, 1.1, 6.5, 5.0, font_size=10.5, accent=VIOLET)

    # Right: visualization of multi-source
    tb(slide, "🔥 Contoh: Sebarkan api dari 2 titik",
       7.2, 1.1, 5.7, 0.4, size=13, bold=True, color=AMBER)

    # Mini grid showing fire spread
    grid_fire = [
        ["F", "1", "2", "2", "1"],
        ["1", "2", "3", "1", "F"],
        ["2", "3", "2", "1", "1"],
        ["3", "2", "1", "2", "2"],
    ]
    gx, gy = 7.5, 1.7
    cell_size = 0.7
    for r in range(4):
        for c in range(5):
            cx = gx + c * cell_size
            cy = gy + r * cell_size
            val = grid_fire[r][c]
            if val == "F":
                col = ROSE
                tc = BG_DEEP
            else:
                d = int(val)
                if d == 1:
                    col = AMBER
                elif d == 2:
                    col = PRIMARY
                else:
                    col = EMERALD
                tc = BG_DEEP
            rect(slide, cx, cy, cell_size, cell_size, col,
                 line_color=BORDER, line_w=0.5)
            tb(slide, val, cx, cy + 0.2, cell_size, cell_size - 0.3,
               size=12, bold=True, color=tc, align=PP_ALIGN.CENTER,
               font_name="Menlo")

    callout(slide, "F = source api, angka = jarak terdekat ke F",
            7.2, 4.7, 5.7, 0.55, color=AMBER, icon="🔥")

    info_card(slide, "🎯 Aplikasi Multi-source",
              ["Jarak ke 'sel berbahaya' terdekat",
               "Sebarkan virus dari banyak titik",
               "Distance to nearest exit",
               "Distance to nearest landmark"],
              7.2, 5.4, 5.7, 1.85, accent=EMERALD)

    callout(slide, "Trick: push semua source ke queue dengan dist=0",
            0.5, 6.3, 6.5, 0.55, color=VIOLET, icon="✨")

    # ── Common Mistakes ────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Common Mistakes — BFS Pitfalls")
    mistakes = [
        ("1. Cek visited di pop, bukan push",
         "Lambat & memori boros!\nCek dist[v]==-1 SEBELUM push.",
         ROSE),
        ("2. Push duplicate ke queue",
         "Tanpa cek visited dulu → loop besar.\nFatal di graph dense.",
         ROSE),
        ("3. Lupa cek batas grid",
         "nr<0 atau nr>=R → segfault!\nSelalu validate sebelum akses.",
         AMBER),
        ("4. Pakai BFS untuk weighted graph",
         "BFS hanya benar untuk unweighted.\nWeighted → Dijkstra (min-heap).",
         AMBER),
        ("5. dx/dy salah arah",
         "dx untuk row, dy untuk col.\nKonsistensi penting!",
         AMBER),
        ("6. Source diset visited di luar loop",
         "dist[src]=0 SEBELUM push.\nKalau salah → infinite loop.",
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
    slide_header(slide, "Cheatsheet — BFS Templates")

    cheat_left = """// === STANDARD BFS ===
vector<int> dist(n+1, -1);
queue<int> q;
dist[s] = 0; q.push(s);

while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
        if (dist[v] == -1) {
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
}

// === BFS GRID ===
int dx[] = {-1,1,0,0};
int dy[] = {0,0,-1,1};
queue<pair<int,int>> q;
q.push({sr, sc}); dist[sr][sc] = 0;"""
    code_box(slide, cheat_left, 0.5, 1.1, 6.2, 5.7, font_size=10, accent=PRIMARY)

    cheat_right = """// === SHORTEST PATH ===
vector<int> prev(n+1, -1);
// di dalam BFS, simpan prev[v] = u
// Rekonstruksi:
vector<int> path;
for (int v = dst; v != -1; v = prev[v])
    path.push_back(v);
reverse(path.begin(), path.end());

// === MULTI-SOURCE BFS ===
for (int s : sources) {
    dist[s] = 0;
    q.push(s);
}
// BFS normal: hasil = jarak ke
//             source TERDEKAT

// === TIPS ===
// • dist[v] = -1 berarti unvisited
// • Cek dist[v] == -1 SEBELUM push
// • Grid: encode (r,c) → r*C + c"""
    code_box(slide, cheat_right, 6.8, 1.1, 6.0, 5.7, font_size=10, accent=AMBER)

    # ── Closing ─────────────────────────────────────────────────
    closing_slide(prs, 58, "BFS — fondasi shortest path & level traversal", [
        (PRIMARY, "Konsep", "Level-order traversal dengan queue. Tinta menyebar dari source."),
        (EMERALD, "Algoritma", "init dist=-1, push source. Loop: pop, expand, cek belum visit."),
        (AMBER, "Shortest Path", "Optimal untuk unweighted. prev[] untuk rekonstruksi path."),
        (VIOLET, "Grid & Multi-source", "Grid 4-arah. Multi-source: push semua source dist=0 di awal."),
        (ROSE, "Pitfall", "Cek visited SEBELUM push. Validate batas grid. Weighted → Dijkstra."),
    ])

    save_presentation(prs, os.path.join(
        os.path.dirname(os.path.abspath(__file__)),
        "Day_58_Presentation.pptx"))


if __name__ == "__main__":
    main()
