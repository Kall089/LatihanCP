#!/usr/bin/env python3
"""Day 11 — Recursion: factorial, fibonacci, hanoi, fast power, gcd."""
import sys, os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..")))
from pptx_lib import *


def main():
    prs = make_presentation()

    # ── Cover ────────────────────────────────────────────────────
    def cov_deco(slide):
        # Mini call stack visualization
        labels = ["fact(0)", "fact(1)", "fact(2)", "fact(3)"]
        for i, lbl in enumerate(labels):
            cy = 5.4 + i * (-0.18) + 0.5
            rounded_rect(slide, 6.5, cy, 4.0, 0.32, BG_CARD,
                         line_color=PRIMARY, line_w=0.5)
            tb(slide, lbl, 6.6, cy + 0.02, 4.0, 0.28,
               size=10, color=PRIMARY, font_name="Menlo")

    cover_slide(prs, 11, "Recursion",
                ["Base case  ·  Call stack  ·  Divide & conquer",
                 "Fondasi DP, backtracking, dan tree traversal"],
                decoration=cov_deco)

    # ── Agenda ───────────────────────────────────────────────────
    agenda_slide(prs, "Agenda — Day 11", [
        ("01", "Konsep\nDasar", PRIMARY,
         ["Base case", "Recursive case", "Call stack", "Stack overflow"]),
        ("02", "Klasik:\nFactorial &\nFibonacci", EMERALD,
         ["factorial(n)", "fib naif O(2^n)", "Memoization", "Trace tree"]),
        ("03", "Hanoi &\nFast Power", AMBER,
         ["Tower of Hanoi", "Fast power O(log b)", "GCD Euclidean", "Pola D&C"]),
        ("04", "Pola &\nKonversi", VIOLET,
         ["Linear/binary rec", "Mutual rec", "Iteratif vs rec", "Tips & pitfall"]),
    ])

    # ── Section 01 ───────────────────────────────────────────────
    section_divider(prs, "01", "Konsep Dasar Rekursi",
                    "Base case + recursive case = fondasi rekursi yang aman")

    slide = new_slide(prs)
    slide_header(slide, "Apa itu Rekursi?", "Fungsi yang memanggil dirinya sendiri")
    info_card(slide, "Wajib Ada", [
        "1. BASE CASE — kondisi berhenti",
        "2. RECURSIVE CASE — panggil diri",
        "   dengan input lebih kecil",
        "",
        "Tanpa base case → infinite recursion",
        "→ STACK OVERFLOW (SIGSEGV)",
    ], 0.5, 1.1, 5.5, 3.0, accent=PRIMARY)

    code = """void countdown(int n) {
    if (n == 0) {           // BASE CASE
        cout << "Selesai!\\n";
        return;
    }
    cout << n << "\\n";
    countdown(n - 1);       // RECURSIVE
}
// countdown(3): 3, 2, 1, Selesai!"""
    code_box(slide, code, 0.5, 4.2, 5.5, 2.6, font_size=11, accent=EMERALD)

    # Right: call stack visualization
    tb(slide, "📚 Visualisasi Call Stack: countdown(3)",
       6.3, 1.1, 6.6, 0.4, size=13, bold=True, color=AMBER)

    stack_items = [
        ("countdown(3)", PRIMARY),
        ("  countdown(2)", PRIMARY),
        ("    countdown(1)", PRIMARY),
        ("      countdown(0) → return", EMERALD),
        ("    return", EMERALD),
        ("  return", EMERALD),
        ("return", EMERALD),
    ]
    for i, (txt, col) in enumerate(stack_items):
        ty = 1.7 + i * 0.55
        rounded_rect(slide, 6.5, ty, 6.4, 0.45, BG_CARD,
                     line_color=col, line_w=0.5)
        tb(slide, txt, 6.7, ty + 0.05, 6.2, 0.35,
           size=11, color=col, font_name="Menlo", bold=True)

    # ── Section 02 ───────────────────────────────────────────────
    section_divider(prs, "02", "Factorial & Fibonacci",
                    "Klasik rekursi: linear vs binary, dan kekuatan memoization",
                    color=EMERALD)

    slide = new_slide(prs)
    slide_header(slide, "Factorial — Linear Recursion O(n)")

    code = """ll factorial(int n) {
    if (n == 0) return 1LL;        // BASE CASE
    return (ll)n * factorial(n-1); // RECURSIVE
}

// Trace: factorial(4)
// = 4 * factorial(3)
// = 4 * 3 * factorial(2)
// = 4 * 3 * 2 * factorial(1)
// = 4 * 3 * 2 * 1 * factorial(0)
// = 4 * 3 * 2 * 1 * 1
// = 24"""
    code_box(slide, code, 0.5, 1.1, 6.4, 4.4, font_size=11, accent=EMERALD)

    # Right: complexity table
    tb(slide, "📊 Batasan factorial(n)", 7.1, 1.1, 5.8, 0.4,
       size=13, bold=True, color=AMBER)
    rows = [
        ["5", "120"],
        ["10", "3,628,800"],
        ["15", "1.3 × 10¹²"],
        ["20", "2.4 × 10¹⁸"],
        [("21", ROSE), ("OVERFLOW long long!", ROSE)],
    ]
    styled_table(slide, ["n", "n!"], rows,
                 7.1, 1.7, [1.5, 4.3], row_h=0.5,
                 header_colors=[EMERALD, AMBER])

    callout(slide,
            "Untuk n > 20, gunakan __int128 atau BigInteger",
            7.1, 5.0, 5.8, 0.6, color=AMBER)

    # Bottom: stack frame visualization
    rounded_rect(slide, 0.5, 5.7, 12.3, 1.4, BG_CARD,
                 line_color=PRIMARY, line_w=0.75)
    tb(slide, "🔻 Stack Frame Visualization",
       0.7, 5.78, 6.0, 0.3, size=11, bold=True, color=PRIMARY)
    frames = [
        ("fact(0)=1", EMERALD),
        ("fact(1)=1", PRIMARY),
        ("fact(2)=2", PRIMARY),
        ("fact(3)=6", PRIMARY),
        ("fact(4)=24", AMBER),
    ]
    for i, (txt, col) in enumerate(frames):
        cx = 0.7 + i * 2.45
        rounded_rect(slide, cx, 6.15, 2.3, 0.85, BG_CARD_2,
                     line_color=col, line_w=0.75)
        tb(slide, txt, cx, 6.35, 2.3, 0.4,
           size=12, bold=True, color=col, align=PP_ALIGN.CENTER,
           font_name="Menlo")

    # ── Slide: Fibonacci naif & memo ───────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Fibonacci — Naif O(2ⁿ) vs Memo O(n)")

    code_naif = """// === NAIF — JANGAN PAKAI! ===
ll fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}
// Untuk n=50 → ~1 detik+ (TLE!)"""
    code_box(slide, code_naif, 0.5, 1.1, 6.0, 2.0, font_size=11, accent=ROSE)

    code_memo = """// === MEMOIZATION — RECOMMENDED ===
ll memo[105];

ll fib(int n) {
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];
    return memo[n] = fib(n-1) + fib(n-2);
}
// memset(memo, -1, sizeof memo);"""
    code_box(slide, code_memo, 0.5, 3.25, 6.0, 2.6, font_size=11, accent=EMERALD)

    # Right side: tree visualization with proper edges
    tb(slide, "🌳 Tree fib(5) NAIF — overlapping subproblems",
       6.7, 1.1, 6.2, 0.4, size=12, bold=True, color=ROSE)
    # Use draw_tree helper with proper diagonal edges
    tree_nodes = [
        ("5", 9.7, 1.7, PRIMARY),       # 0: root
        ("4", 8.2, 2.55, PRIMARY),      # 1
        ("3", 11.2, 2.55, AMBER),       # 2
        ("3", 7.2, 3.4, AMBER),         # 3
        ("2", 8.9, 3.4, VIOLET),        # 4 (duplicate dengan #2)
        ("2", 10.4, 3.4, VIOLET),       # 5 (duplicate dengan #4)
        ("1", 11.9, 3.4, EMERALD),      # 6
    ]
    tree_edges = [(0, 1), (0, 2), (1, 3), (1, 4), (2, 5), (2, 6)]
    draw_tree(slide, tree_nodes, tree_edges,
              radius=0.27, value_size=12)

    callout(slide, "fib(3) dihitung 2x, fib(2) 3x — boros!",
            6.7, 4.0, 6.2, 0.7, color=ROSE)

    # Comparison table
    tb(slide, "Naif vs Memo", 6.7, 4.85, 6.2, 0.4,
       size=12, bold=True, color=AMBER)
    rows = [
        ["Naif", "O(2ⁿ)", "O(n)", "TLE n>40"],
        [("Memo", EMERALD), ("O(n)", EMERALD), ("O(n)", EMERALD), ("Aman ≤ 100", EMERALD)],
    ]
    styled_table(slide, ["Versi", "Time", "Space", "Catatan"], rows,
                 6.7, 5.3, [1.4, 1.3, 1.3, 2.2], row_h=0.5,
                 header_colors=[ROSE, AMBER, AMBER, EMERALD])

    # ── Section 03 ───────────────────────────────────────────────
    section_divider(prs, "03", "Hanoi, Fast Power & GCD",
                    "Pola Divide & Conquer — solve big problem dengan small subproblem",
                    color=AMBER)

    slide = new_slide(prs)
    slide_header(slide, "Tower of Hanoi — Klasik D&C")
    code = """void hanoi(int n, char src, char dst, char via) {
    if (n == 0) return;
    hanoi(n-1, src, via, dst);    // n-1 dari src ke via
    cout << "Move " << n << ": " << src
         << " -> " << dst << "\\n";
    hanoi(n-1, via, dst, src);    // n-1 dari via ke dst
}
// hanoi(n, 'A', 'C', 'B');
// Total langkah: 2^n - 1"""
    code_box(slide, code, 0.5, 1.1, 6.4, 4.0, font_size=11, accent=AMBER)

    # Right: steps table
    tb(slide, "📊 Jumlah Langkah", 7.1, 1.1, 5.8, 0.4,
       size=13, bold=True, color=PRIMARY)
    rows = [
        ["1", "1"],
        ["3", "7"],
        ["10", "1,023"],
        ["20", "1,048,575"],
        [("64", ROSE), ("1.8 × 10¹⁹ langkah!", ROSE)],
    ]
    styled_table(slide, ["n disk", "Langkah (2ⁿ-1)"], rows,
                 7.1, 1.7, [1.8, 4.0], row_h=0.5,
                 header_colors=[AMBER, EMERALD])

    callout(slide, "T(n) = 2·T(n-1) + 1",
            7.1, 5.0, 5.8, 0.6, color=PRIMARY,
            icon="🧮")

    # Bottom: hanoi(2) trace
    rounded_rect(slide, 0.5, 5.4, 12.3, 1.7, BG_CARD,
                 line_color=EMERALD, line_w=1.0)
    rect(slide, 0.5, 5.4, 12.3, 0.08, EMERALD)
    tb(slide, "🎬 Trace hanoi(2, A, C, B):",
       0.7, 5.5, 5.0, 0.3, size=11, bold=True, color=EMERALD)
    trace = [
        ("Step 1: Move disk 1 from A → B", PRIMARY),
        ("Step 2: Move disk 2 from A → C", AMBER),
        ("Step 3: Move disk 1 from B → C", PRIMARY),
    ]
    for i, (txt, col) in enumerate(trace):
        cx = 0.7 + i * 4.05
        rounded_rect(slide, cx, 5.85, 3.95, 1.1, BG_CARD_2,
                     line_color=col, line_w=0.5)
        tb(slide, txt, cx + 0.1, 6.15, 3.85, 0.6,
           size=11, color=col, align=PP_ALIGN.CENTER)

    # ── Slide: Fast Power & GCD ───────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Fast Power & GCD — O(log)")

    code_fp = """// === FAST POWER O(log b) ===
ll fastpow(ll a, ll b, ll mod) {
    if (b == 0) return 1LL;
    ll h = fastpow(a, b/2, mod);
    ll h2 = h * h % mod;
    if (b % 2 == 0) return h2;
    return a % mod * h2 % mod;
}
// 2^10 = ~3 level rekursi"""
    code_box(slide, code_fp, 0.5, 1.1, 6.0, 3.5, font_size=11, accent=PRIMARY)

    code_gcd = """// === GCD EUCLIDEAN O(log min) ===
ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}
// Pakai built-in __gcd(a, b)"""
    code_box(slide, code_gcd, 0.5, 4.75, 6.0, 2.2, font_size=11, accent=EMERALD)

    # Right: trace
    tb(slide, "🎬 Trace gcd(48, 18)", 6.7, 1.1, 6.2, 0.4,
       size=13, bold=True, color=AMBER)
    trace_steps = [
        ("gcd(48, 18)", "= gcd(18, 48 % 18) = gcd(18, 12)", PRIMARY),
        ("gcd(18, 12)", "= gcd(12, 18 % 12) = gcd(12, 6)", PRIMARY),
        ("gcd(12, 6)",  "= gcd(6,  12 % 6)  = gcd(6, 0)", AMBER),
        ("gcd(6, 0)",   "= 6  ← BASE CASE!", EMERALD),
    ]
    for i, (lhs, rhs, col) in enumerate(trace_steps):
        ty = 1.7 + i * 0.65
        rounded_rect(slide, 6.7, ty, 6.2, 0.55, BG_CARD,
                     line_color=col, line_w=0.5)
        tb(slide, lhs, 6.85, ty + 0.05, 1.5, 0.45,
           size=11, bold=True, color=col, font_name="Menlo")
        tb(slide, rhs, 8.4, ty + 0.05, 4.4, 0.45,
           size=10.5, color=SILVER, font_name="Menlo")

    callout(slide,
            "GCD: setiap 2 langkah, a berkurang minimal setengah → O(log)",
            6.7, 4.5, 6.2, 0.6, color=EMERALD)

    insight_card(slide, "Kapan Pakai Fast Power?",
                 ["Untuk a^b mod m dengan b besar (10⁹)",
                  "Naif O(b) → TLE",
                  "Modular inverse: a^(p-2) mod p",
                  "Butuh untuk kombinatorika, geometry"],
                 6.7, 5.25, 6.2, 1.7)

    # ── Section 04 ─────────────────────────────────────────────
    section_divider(prs, "04", "Pola & Konversi Iteratif",
                    "Linear, binary, mutual — dan kapan iteratif lebih baik",
                    color=VIOLET)

    slide = new_slide(prs)
    slide_header(slide, "Pola Rekursi — 4 Tipe Utama")

    patterns = [
        ("1. LINEAR", "1 panggilan/langkah", PRIMARY,
         "int sum(int A[], int n) {\n  if (n==0) return 0;\n  return A[0]+sum(A+1,n-1);\n}",
         "Depth O(n), calls O(n)"),
        ("2. BINARY", "2 panggilan/langkah", EMERALD,
         "ll fib(int n) {\n  if (n<=1) return n;\n  return fib(n-1)+fib(n-2);\n}",
         "Depth O(n), calls O(2ⁿ)"),
        ("3. DIVIDE & CONQUER", "Split jadi setengah", AMBER,
         "void mergeSort(int l,int r) {\n  if (l>=r) return;\n  int m=(l+r)/2;\n  mergeSort(l,m);\n  mergeSort(m+1,r);\n}",
         "Depth O(log n), calls O(n)"),
        ("4. MUTUAL", "2 fungsi saling panggil", VIOLET,
         "bool isEven(int n) {\n  return n==0 ? true : isOdd(n-1);\n}\nbool isOdd(int n) {\n  return n==0 ? false : isEven(n-1);\n}",
         "Hati-hati infinite loop"),
    ]
    for i, (title, sub, col, code, complexity) in enumerate(patterns):
        cn = i % 2
        rn = i // 2
        mx = 0.5 + cn * 6.3
        my = 1.1 + rn * 2.95
        rounded_rect(slide, mx, my, 6.1, 2.7, BG_CARD,
                     line_color=col, line_w=1.0)
        rect(slide, mx, my, 6.1, 0.36, col)
        tb(slide, title, mx + 0.15, my + 0.05, 4.0, 0.3,
           size=11, bold=True, color=BG_DEEP)
        tb(slide, sub, mx + 4.2, my + 0.05, 1.85, 0.3,
           size=10, color=BG_DEEP, italic=True)
        plain_code_box(slide, code, mx + 0.15, my + 0.45,
                       5.8, 1.7, font_size=9.5, accent=col,
                       text_color=SILVER)
        tb(slide, complexity, mx + 0.2, my + 2.25, 5.7, 0.35,
           size=10, color=col, bold=True, italic=True)

    # ── Common Mistakes ────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Common Mistakes — Hindari Stack Overflow!")

    mistakes = [
        ("1. Lupa base case",
         "Infinite recursion → SIGSEGV.\nSelalu tulis base case PERTAMA.",
         ROSE),
        ("2. Recursive case salah arah",
         "Input harus mengecil ke base.\nf(n+1) bukannya f(n-1) → infinite!",
         ROSE),
        ("3. Fibonacci naif untuk n besar",
         "n=50 → 1 detik+, TLE!\nWajib pakai memoization.",
         AMBER),
        ("4. Memo tanpa init -1",
         "Default 0 dianggap sudah dihitung.\nmemset(memo, -1, sizeof memo).",
         AMBER),
        ("5. Rekursi terlalu dalam (n>10⁵)",
         "Stack default ~1MB → ~10⁵ frame.\nKonversi iteratif untuk n besar.",
         AMBER),
        ("6. Overflow di factorial(n) untuk n>20",
         "20! = 2.4×10¹⁸ ≈ batas long long.\n21! overflow → pakai __int128.",
         AMBER),
    ]
    for i, (title, desc, col) in enumerate(mistakes):
        cn = i % 3
        rn = i // 3
        mx = 0.4 + cn * 4.25
        my = 1.1 + rn * 2.95
        rounded_rect(slide, mx, my, 4.1, 2.7, BG_CARD,
                     line_color=col, line_w=1.0)
        rect(slide, mx, my, 4.1, 0.08, col)
        tb(slide, title, mx + 0.2, my + 0.2, 3.85, 0.5,
           size=12, bold=True, color=col)
        tb(slide, desc, mx + 0.2, my + 0.75, 3.85, 1.85,
           size=10.5, color=SILVER)

    # ── Cheatsheet ─────────────────────────────────────────────
    slide = new_slide(prs)
    slide_header(slide, "Cheatsheet — Recursion Quick Reference")

    cheat_left = """// === TEMPLATE REKURSI ===
ReturnType solve(args) {
    // 1. BASE CASE
    if (terminating_condition)
        return base_value;

    // 2. RECURSIVE CASE
    return combine(solve(smaller_args));
}

// === MEMOIZATION ===
const int MAXN = 105;
ll memo[MAXN];

ll dp(int n) {
    if (base) return ...;
    if (memo[n] != -1) return memo[n];
    return memo[n] = compute(n);
}
// memset(memo, -1, sizeof memo);"""
    code_box(slide, cheat_left, 0.5, 1.1, 6.2, 5.5, font_size=10.5, accent=PRIMARY)

    cheat_right = """// === FAST POWER ===
ll fpow(ll a, ll b, ll m) {
    if (b == 0) return 1;
    ll h = fpow(a, b/2, m);
    h = h * h % m;
    return b%2 ? a*h%m : h;
}

// === GCD ===
ll gcd(ll a, ll b) {
    return b ? gcd(b, a%b) : a;
}

// === FACTORIAL ===
ll fact(int n) {
    return n ? n * fact(n-1) : 1;
}"""
    code_box(slide, cheat_right, 6.8, 1.1, 6.0, 5.5, font_size=10.5, accent=AMBER)

    rounded_rect(slide, 0.5, 6.7, 12.3, 0.6, BG_CARD,
                 line_color=EMERALD, line_w=1.0)
    rect(slide, 0.5, 6.7, 12.3, 0.04, EMERALD)
    tb(slide, "🌟 Aturan: Base case dulu · Input mengecil · Memo untuk overlapping subproblem · Iteratif untuk n>10⁵",
       0.7, 6.78, 12.0, 0.5, size=10, color=SILVER)

    # ── Closing ─────────────────────────────────────────────────
    closing_slide(prs, 11, "Recursion: solve big with smaller — fondasi DP & backtracking", [
        (PRIMARY, "Base + Recursive", "Setiap rekursi WAJIB punya base case dan input yang mengecil."),
        (EMERALD, "Memoization", "Cache subresult untuk hindari overlapping subproblem. Naif fib O(2ⁿ) → memo O(n)."),
        (AMBER, "Divide & Conquer", "Hanoi 2ⁿ-1, fast power O(log b), gcd O(log min). Split → solve → combine."),
        (VIOLET, "Pola", "Linear, binary, D&C, mutual. Pilih sesuai struktur masalah."),
        (ROSE, "Pitfall", "Stack overflow untuk n>10⁵. Konversi iteratif atau pakai stack STL."),
    ])

    save_presentation(prs, os.path.join(
        os.path.dirname(os.path.abspath(__file__)),
        "Day_11_Presentation.pptx"))


if __name__ == "__main__":
    main()
