#!/usr/bin/env python3
"""Day 16 — Custom Comparator: operator<, functor, lambda, priority_queue."""
import sys, os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..")))
from pptx_lib import *


def main():
    prs = make_presentation()

    # ── Cover ────────────────────────────────────────────────────
    def cov_deco(slide):
        labels = ["operator<", "lambda", "functor"]
        cols = [PRIMARY, EMERALD, AMBER]
        for i, (lbl, col) in enumerate(zip(labels, cols)):
            cx = 6.4 + i * 1.85
            rounded_rect(slide, cx, 5.6, 1.7, 0.5, col)
            tb(slide, lbl, cx, 5.7, 1.7, 0.4,
               size=11, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER,
               font_name="Menlo")

    cover_slide(prs, 16, "Custom Comparator",
                ["Strict weak ordering · Multi-criteria sort",
                 "Sort apa saja, sebebas-bebasnya"],
                decoration=cov_deco)

    # ── Agenda ───────────────────────────────────────────────────
    agenda_slide(prs, "Agenda — Day 16", [
        ("01", "Strict Weak\nOrdering", PRIMARY,
         ["Irreflexivity", "Asymmetry", "Transitivity", "Pakai < bukan <="]),
        ("02", "operator< &\nLambda", EMERALD,
         ["Override operator<", "Lambda inline", "Capture [&]", "Multi-criteria"]),
        ("03", "Functor &\nContainer", AMBER,
         ["struct + operator()", "priority_queue", "set / map", "Reusable"]),
        ("04", "Pola CP\nKlasik", VIOLET,
         ["Index sort + iota", "Negate trick", "Sort by length", "Stable vs unstable"]),
    ])

    # ── Section 01 ───────────────────────────────────────────────
    section_divider(prs, "01", "Strict Weak Ordering",
                    "3 aturan wajib agar comparator C++ tidak crash")

    slide = new_slide(prs)
    slide_header(slide, "3 Aturan Strict Weak Ordering")

    rules_data = [
        ("1. Irreflexivity",
         "comp(a, a) = FALSE",
         "Tidak boleh: a < a",
         "Selalu return false untuk\nelemen yang sama",
         PRIMARY),
        ("2. Asymmetry",
         "comp(a,b)=T → comp(b,a)=F",
         "Jika a<b, maka b≠<a",
         "< adalah satu arah,\ntidak bisa 2 arah",
         EMERALD),
        ("3. Transitivity",
         "a<b ∧ b<c → a<c",
         "Urutan harus konsisten",
         "Kalau melanggar:\nundefined behavior!",
         AMBER),
    ]
    for i, (title, formula, intuition, detail, col) in enumerate(rules_data):
        ty = 1.2 + i * 1.85
        rounded_rect(slide, 0.5, ty, 12.3, 1.7, BG_CARD,
                     line_color=col, line_w=1.0)
        rect(slide, 0.5, ty, 0.12, 1.7, col)
        tb(slide, title, 0.75, ty + 0.15, 4.0, 0.4,
           size=14, bold=True, color=col)
        rounded_rect(slide, 0.75, ty + 0.7, 4.0, 0.4, BG_CARD_2)
        tb(slide, formula, 0.85, ty + 0.78, 3.9, 0.32,
           size=10, color=AMBER, font_name="Menlo")
        tb(slide, intuition, 0.75, ty + 1.2, 4.0, 0.35,
           size=11, italic=True, color=SLATE)
        tb(slide, detail, 5.2, ty + 0.3, 7.4, 1.2,
           size=12, color=SILVER)

    # Bottom warning
    rounded_rect(slide, 0.5, 6.85, 12.3, 0.55, BG_CARD,
                 line_color=ROSE, line_w=1.2)
    rect(slide, 0.5, 6.85, 0.1, 0.55, ROSE)
    tb(slide, "⚠  JANGAN pakai a <= b di comparator → langgar irreflexivity → CRASH",
       0.75, 6.93, 12.0, 0.4, size=12, bold=True, color=ROSE)

    # ── Section 02 ───────────────────────────────────────────────
    section_divider(prs, "02", "operator< & Lambda",
                    "Dua cara paling populer untuk custom sort",
                    color=EMERALD)

    slide = new_slide(prs)
    slide_header(slide, "operator< pada Struct — Cara Cleanest")

    code = """struct Point {
    int x, y;

    bool operator<(const Point& o) const {
        if (x != o.x) return x < o.x;  // primary: x asc
        return y < o.y;                 // tiebreak:  y asc
    }
};

vector<Point> pts = {{3,1},{1,5},{1,2},{3,0}};
sort(pts.begin(), pts.end());
// Output: (1,2)(1,5)(3,0)(3,1)

// Bonus: bekerja juga di
set<Point> s;
priority_queue<Point> pq;
map<Point, int> m;"""
    code_box(slide, code, 0.5, 1.1, 6.5, 5.5, font_size=11, accent=EMERALD)

    # Right: visualization
    tb(slide, "🎯 Sort Result Visualization",
       7.2, 1.1, 5.7, 0.4, size=13, bold=True, color=AMBER)
    points_before = ["(3,1)", "(1,5)", "(1,2)", "(3,0)"]
    points_after = ["(1,2)", "(1,5)", "(3,0)", "(3,1)"]

    tb(slide, "Before sort:", 7.2, 1.65, 5.7, 0.3,
       size=11, color=ROSE)
    for i, p in enumerate(points_before):
        cx = 7.2 + i * 1.45
        rounded_rect(slide, cx, 2.0, 1.35, 0.55, BG_CARD,
                     line_color=ROSE, line_w=0.5)
        tb(slide, p, cx, 2.1, 1.35, 0.4,
           size=12, bold=True, color=ROSE, align=PP_ALIGN.CENTER,
           font_name="Menlo")

    tb(slide, "↓ sort()", 9.5, 2.7, 1.0, 0.3, size=11, color=PRIMARY)

    tb(slide, "After sort:", 7.2, 3.15, 5.7, 0.3,
       size=11, color=EMERALD)
    for i, p in enumerate(points_after):
        cx = 7.2 + i * 1.45
        rounded_rect(slide, cx, 3.5, 1.35, 0.55, BG_CARD,
                     line_color=EMERALD, line_w=0.5)
        tb(slide, p, cx, 3.6, 1.35, 0.4,
           size=12, bold=True, color=EMERALD, align=PP_ALIGN.CENTER,
           font_name="Menlo")

    insight_card(slide, "Kelebihan operator<",
                 ["Otomatis bekerja di set, map, pq",
                  "Tidak perlu lambda di setiap call",
                  "Self-documenting: lihat di struct",
                  "Default sort tanpa argumen ke-3"],
                 7.2, 4.4, 5.7, 2.3)

    # ── Slide: Lambda comparator ──────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Lambda Comparator — Concise & Inline")

    code = """// Sort by length
sort(v.begin(), v.end(),
    [](const string& a, const string& b) {
        return a.size() < b.size();
    });

// Multi-criteria 3-tingkat
sort(students.begin(), students.end(),
    [](const Student& a, const Student& b) {
        if (a.score != b.score)
            return a.score > b.score;  // score desc
        if (a.name != b.name)
            return a.name < b.name;    // name asc
        return a.age < b.age;          // age asc
    });"""
    code_box(slide, code, 0.5, 1.1, 6.6, 4.8, font_size=11, accent=PRIMARY)

    # Right
    code2 = """// Capture variabel luar dengan [&]
int K = 5;
sort(v.begin(), v.end(),
    [K](int a, int b) {
        return abs(a-K) < abs(b-K);
    });
// Sort by jarak ke K"""
    code_box(slide, code2, 7.3, 1.1, 5.6, 2.2, font_size=11, accent=AMBER)

    insight_card(slide, "Lambda Capture",
                 ["[]   tanpa capture",
                  "[&]  capture by reference",
                  "[=]  capture by value",
                  "[&K] hanya K by reference"],
                 7.3, 3.45, 5.6, 2.5)

    rounded_rect(slide, 0.5, 6.05, 12.3, 1.0, BG_CARD,
                 line_color=VIOLET, line_w=1.0)
    rect(slide, 0.5, 6.05, 12.3, 0.06, VIOLET)
    tb(slide, "🎯 Multi-Criteria Pattern: if (a.X != b.X) return a.X CMP b.X; ...",
       0.7, 6.15, 12.0, 0.35, size=12, bold=True, color=VIOLET)
    tb(slide, "Selalu pakai != untuk cek tie, lalu compare. Ini lebih readable & mudah extend.",
       0.7, 6.55, 12.0, 0.4, size=10.5, color=SILVER)

    # ── Section 03 ─────────────────────────────────────────────
    section_divider(prs, "03", "Functor & Container",
                    "struct dengan operator() — wajib untuk priority_queue/set",
                    color=AMBER)

    slide = new_slide(prs)
    slide_header(slide, "Functor — struct + operator()")

    code = """struct Student {
    string name;
    int score, age;
};

// Functor: callable struct
struct CompStudent {
    bool operator()(const Student& a,
                    const Student& b) const {
        if (a.score != b.score)
            return a.score > b.score;  // desc
        return a.name < b.name;
    }
};

sort(v.begin(), v.end(), CompStudent{});

// Bisa dipakai juga di:
priority_queue<Student, vector<Student>,
               CompStudent> pq;
set<Student, CompStudent> s;"""
    code_box(slide, code, 0.5, 1.1, 6.6, 5.7, font_size=10.5, accent=AMBER)

    # Right: comparison
    tb(slide, "Lambda vs Functor", 7.3, 1.1, 5.6, 0.4,
       size=13, bold=True, color=PRIMARY)

    rows = [
        ["Sintaks", "Pendek", "Lebih panjang"],
        ["Reusable", "Tidak", ("Ya", EMERALD)],
        [("Pakai di pq/set", AMBER), ("Tidak (butuh tipe)", ROSE), ("Ya", EMERALD)],
        ["State", "Capture [&]", "Member variabel"],
        ["Inline", ("Ya, ringkas", EMERALD), "Tidak"],
    ]
    styled_table(slide, ["Aspek", "Lambda", "Functor"], rows,
                 7.3, 1.7, [1.7, 1.95, 1.95], row_h=0.5,
                 header_colors=[PRIMARY, EMERALD, AMBER],
                 body_size=10, header_size=10)

    callout(slide,
            "Container (set, pq, map) butuh TIPE → wajib functor",
            7.3, 5.3, 5.6, 0.7, color=AMBER, icon="🔑")

    insight_card(slide, "Tip CP",
                 ["Default: lambda jika sekali pakai",
                  "Pakai functor jika butuh di pq/set",
                  "operator< paling clean kalau struct milik kita"],
                 7.3, 6.15, 5.6, 0.85)

    # ── Slide: priority_queue ─────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "priority_queue — Max vs Min Heap")

    code = """// === DEFAULT: MAX-HEAP ===
priority_queue<int> pq;
pq.push(3); pq.push(1); pq.push(5);
// pq.top() = 5

// === MIN-HEAP (greater) ===
priority_queue<int, vector<int>,
               greater<int>> minPQ;
// minPQ.top() = elemen terkecil

// === CUSTOM: min-heap by deadline ===
struct Task { string name; int deadline; };

struct CompTask {
    bool operator()(const Task& a,
                    const Task& b) const {
        return a.deadline > b.deadline; // ← min
    }
};
priority_queue<Task, vector<Task>,
               CompTask> taskPQ;"""
    code_box(slide, code, 0.5, 1.1, 6.7, 5.7, font_size=10.5, accent=PRIMARY)

    # Right: explain logic
    tb(slide, "🧠 Logika priority_queue",
       7.4, 1.1, 5.5, 0.4, size=13, bold=True, color=AMBER)

    info_card(slide, "Aturan",
              ["• comp(a,b)=true → b di atas a",
               "• Default: comp = less",
               "  → max element di top",
               "• Untuk min-heap:",
               "  comp(a,b) = a > b",
               "  → terkecil di top"],
              7.4, 1.7, 5.5, 2.2, accent=EMERALD)

    insight_card(slide, "Pola Umum CP",
                 ["Min-heap: greater<int>()",
                  "Top-K terbesar → min-heap size K",
                  "Dijkstra → min-heap pair<dist,v>",
                  "Median → 2 heap (max+min)"],
                 7.4, 4.05, 5.5, 2.0)

    callout(slide, "Hati-hati: pq.top() READONLY, jangan modify!",
            7.4, 6.15, 5.5, 0.6, color=ROSE, icon="⚠")

    # ── Section 04 ─────────────────────────────────────────────
    section_divider(prs, "04", "Pola CP Klasik",
                    "Index sort, negate trick, version comparator",
                    color=VIOLET)

    slide = new_slide(prs)
    slide_header(slide, "Index Sort — Sort tapi simpan urutan asli")

    code = """vector<int> A = {30, 10, 50, 20, 40};
vector<int> idx(A.size());
iota(idx.begin(), idx.end(), 0);
// idx = {0, 1, 2, 3, 4}

// Sort indices BY value of A
sort(idx.begin(), idx.end(),
    [&A](int i, int j){
        return A[i] < A[j];
    });

// idx sekarang = {1, 3, 0, 4, 2}
// A[idx[0]] = 10 (terkecil)
// A[idx[1]] = 20
// A[idx[k]] = elemen ke-k terkecil"""
    code_box(slide, code, 0.5, 1.1, 6.5, 5.5, font_size=11, accent=VIOLET)

    # Right: visual
    tb(slide, "🎯 Visual Index Sort",
       7.2, 1.1, 5.7, 0.4, size=13, bold=True, color=PRIMARY)

    tb(slide, "A = ", 7.2, 1.7, 0.6, 0.4, size=12, bold=True, color=PRIMARY,
       font_name="Menlo")
    array_cells(slide, [30, 10, 50, 20, 40], 7.8, 1.7,
                cell_w=0.6, cell_h=0.5,
                highlights={0: BG_CARD_2, 1: BG_CARD_2, 2: BG_CARD_2,
                            3: BG_CARD_2, 4: BG_CARD_2})

    tb(slide, "↓ idx sort", 9.5, 2.4, 1.0, 0.3, size=11, color=AMBER)

    tb(slide, "idx = ", 7.2, 2.85, 0.6, 0.4, size=12, bold=True, color=AMBER,
       font_name="Menlo")
    array_cells(slide, [1, 3, 0, 4, 2], 7.8, 2.85,
                cell_w=0.6, cell_h=0.5,
                highlights={i: AMBER for i in range(5)},
                colors_map={i: BG_DEEP for i in range(5)})

    insight_card(slide, "Mengapa berguna?",
                 ["Tahu rank tiap elemen",
                  "Akses elemen sorted tanpa\n  ubah array asli",
                  "Multi-array sort konsisten",
                  "Output urutan original"],
                 7.2, 3.85, 5.7, 2.3)

    callout(slide,
            "Pola: iota + sort + lambda — 3 baris jadi index sort",
            7.2, 6.3, 5.7, 0.7, color=EMERALD, icon="✨")

    # ── Slide: Negate trick & misc ────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Negate Trick & Stable Sort")

    code_neg = """// Negate trick — sort multi-criteria
// dengan default <
struct Item { int score; string name; int rank; };

// Sort: score DESC, name ASC, rank ASC
vector<tuple<int, string, int>> v;
for (auto& it : items)
    v.push_back({-it.score, it.name, it.rank});

sort(v.begin(), v.end());
// Negate score → DESC otomatis"""
    code_box(slide, code_neg, 0.5, 1.1, 6.4, 4.0, font_size=11, accent=AMBER)

    code_stable = """// stable_sort — pertahankan urutan relatif
// untuk elemen yang equal
stable_sort(v.begin(), v.end(),
    [](auto& a, auto& b){
        return a.score < b.score;
    });
// Kalau dua score sama, urutan input tetap"""
    code_box(slide, code_stable, 0.5, 5.25, 6.4, 1.7, font_size=11, accent=EMERALD)

    # Right: stable vs unstable
    tb(slide, "🔄 stable_sort vs sort",
       7.1, 1.1, 5.8, 0.4, size=13, bold=True, color=PRIMARY)

    rows = [
        ["sort", "O(n log n)", "Tidak"],
        [("stable_sort", EMERALD), ("O(n log² n)", AMBER), ("Ya", EMERALD)],
    ]
    styled_table(slide, ["Algoritma", "Time", "Stable"], rows,
                 7.1, 1.7, [1.9, 1.9, 1.9], row_h=0.55,
                 header_colors=[PRIMARY, AMBER, EMERALD])

    info_card(slide, "Kapan Pakai Stable?",
              ["• Multi-pass sort (sort N kali)",
               "• Hindari stable: 1 sort lambda",
               "  multi-criteria",
               "• Pakai stable saat kriteria",
               "  hierarki tidak bisa di-1-call"],
              7.1, 3.1, 5.8, 2.0, accent=EMERALD)

    callout(slide,
            "Pakai sort + lambda multi-criteria > multiple stable_sort",
            7.1, 5.3, 5.8, 0.7, color=AMBER, icon="💡")

    # ── Common Mistakes ────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Common Mistakes — Comparator Pitfalls")

    mistakes = [
        ("1. Pakai <= bukan <",
         "Langgar irreflexivity → UB.\nGunakan < (strict) saja.",
         ROSE),
        ("2. Tidak transitif",
         "Misal: comp by 'mood'.\nHasil sort tidak konsisten.",
         ROSE),
        ("3. Lambda di set/map/pq",
         "Tidak bisa langsung.\nPakai functor atau decltype.",
         AMBER),
        ("4. Lupa const di operator<",
         "set butuh const → compile error.\noperator<(...) const wajib.",
         AMBER),
        ("5. priority_queue logika balik",
         "comp(a,b)=true → b di atas a.\nUntuk min: a > b (kebalikan).",
         AMBER),
        ("6. Capture lifetime issue",
         "Capture by ref [&] saat objek\nsudah dihancurkan → UB.",
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
    slide_header(slide, "Cheatsheet — Comparator Templates")

    cheat_left = """// === OPERATOR< ===
struct Point {
    int x, y;
    bool operator<(const Point& o) const {
        return tie(x, y) < tie(o.x, o.y);
    }
};

// === LAMBDA ===
sort(v.begin(), v.end(),
    [](auto& a, auto& b){
        return a.score > b.score;
    });

// === MULTI-CRITERIA ===
sort(v.begin(), v.end(), [](auto& a, auto& b){
    if (a.x != b.x) return a.x < b.x;
    if (a.y != b.y) return a.y > b.y;
    return a.z < b.z;
});"""
    code_box(slide, cheat_left, 0.5, 1.1, 6.2, 5.7, font_size=10.5, accent=PRIMARY)

    cheat_right = """// === FUNCTOR (untuk pq, set) ===
struct Cmp {
    bool operator()(const T& a,
                    const T& b) const {
        return a.score > b.score; // min-heap
    }
};

priority_queue<T, vector<T>, Cmp> pq;
set<T, Cmp> s;

// === INDEX SORT ===
vector<int> idx(n);
iota(idx.begin(), idx.end(), 0);
sort(idx.begin(), idx.end(),
    [&](int i, int j){
        return A[i] < A[j];
    });"""
    code_box(slide, cheat_right, 6.8, 1.1, 6.0, 5.7, font_size=10.5, accent=AMBER)

    # ── Closing ─────────────────────────────────────────────────
    closing_slide(prs, 16, "Custom Comparator: sort apapun, sebebas-bebasnya", [
        (PRIMARY, "Strict Weak Ordering", "3 aturan: irreflexive, asymmetric, transitive. Pakai < bukan <=."),
        (EMERALD, "operator< & Lambda", "operator< paling clean. Lambda untuk inline. Multi-criteria pakai if !=."),
        (AMBER, "Functor", "struct + operator(). Wajib untuk priority_queue, set, map. Reusable."),
        (VIOLET, "Pola CP", "Index sort dengan iota+lambda. Negate trick untuk desc multi-criteria."),
        (ROSE, "Pitfall", "<= ke comparator → UB. Lambda tidak bisa langsung di pq/set tanpa decltype."),
    ])

    save_presentation(prs, os.path.join(
        os.path.dirname(os.path.abspath(__file__)),
        "Day_16_Presentation.pptx"))


if __name__ == "__main__":
    main()
