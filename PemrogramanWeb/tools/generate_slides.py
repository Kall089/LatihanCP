#!/usr/bin/env python3
"""
Generate slides.pptx untuk SEMUA topik 0-materi/ Pemrograman Web.
Tema: "Modern Cobalt" (pptx_lib.py).

Jalankan dari mana saja:
    python3 tools/generate_slides.py
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from pptx_lib import *  # noqa: F401,F403

BASE = os.path.abspath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "0-materi"))


# ═══════════════════════════════════════════════════════════════════
# Helper layout khusus Pemrograman Web
# ═══════════════════════════════════════════════════════════════════

def cover_pills(labels, colors=None):
    """Dekorasi cover ala deck CP: pill topik di kanan bawah."""
    if colors is None:
        colors = [PRIMARY, EMERALD, AMBER, VIOLET]

    def deco(slide):
        for i, (lbl, col) in enumerate(zip(labels, colors)):
            cx = 6.15 + i * 1.72
            rounded_rect(slide, cx, 5.55, 1.6, 0.48, col)
            tb(slide, lbl, cx, 5.64, 1.6, 0.35,
               size=10, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
    return deco


def web_cover(prs, num, title, subtitle_lines, color=PRIMARY, pills=None):
    """Cover identik deck CP (cover_slide) dengan badge MODUL."""
    return cover_slide(
        prs, num, title, subtitle_lines,
        decoration=cover_pills(pills) if pills else None,
        topic_color=color, badge="MODUL",
        course="PEMROGRAMAN WEB",
        series="Teori + Praktikum · 8 Modul",
    )


def web_closing(prs, num, title_main, takeaways):
    """Penutup identik deck CP (closing_slide)."""
    return closing_slide(
        prs, num, title_main, takeaways,
        footer="Pemrograman Web · lanjut ke 1-pembelajaran/",
    )


def _card_h(lines):
    return 0.72 + len(lines) * 0.32


def slide_cards(prs, title, subtitle, cards):
    """Slide berisi 1-4 info_card. cards: (judul, lines, accent)."""
    slide = new_slide(prs)
    slide_header(slide, title, subtitle)
    y0 = 1.35 if subtitle else 1.15
    n = len(cards)
    if n == 1:
        geo = [(0.5, y0, 12.3)]
    elif n == 2:
        geo = [(0.5, y0, 6.0), (6.75, y0, 6.05)]
    elif n == 3:
        geo = [(0.5, y0, 6.0), (6.75, y0, 6.05), (0.5, None, 12.3)]
    else:
        geo = [(0.5, y0, 6.0), (6.75, y0, 6.05),
               (0.5, None, 6.0), (6.75, None, 6.05)]
    row1_h = max(_card_h(c[1]) for c in cards[:2])
    for i, (ct, lines, accent) in enumerate(cards):
        x, y, w = geo[i]
        if y is None:
            y = y0 + row1_h + 0.25
        info_card(slide, ct, lines, x, y, w, _card_h(lines), accent=accent)
    return slide


def slide_code(prs, title, subtitle, code, accent=PRIMARY, right_cards=None,
               font_size=10.5, code_w=6.5, code_h=None):
    """Kode (tanpa highlight C++) di kiri + kartu penjelasan di kanan."""
    slide = new_slide(prs)
    slide_header(slide, title, subtitle)
    y0 = 1.35 if subtitle else 1.15
    nlines = code.count("\n") + 1
    if code_h is None:
        code_h = min(7.2 - y0, 0.55 + nlines * (font_size / 10.0) * 0.21)
    plain_code_box(slide, code, 0.5, y0, code_w, code_h,
                   font_size=font_size, accent=accent)
    if right_cards:
        cy = y0
        rx = 0.5 + code_w + 0.3
        rw = 12.8 - code_w - 0.3
        for (ct, lines, cac) in right_cards:
            h = _card_h(lines)
            info_card(slide, ct, lines, rx, cy, rw, h, accent=cac)
            cy += h + 0.22
    return slide


def slide_ascii(prs, title, subtitle, art, caption=None, accent=PRIMARY,
                font_size=12, side_card=None):
    """Diagram ASCII besar dalam code box."""
    slide = new_slide(prs)
    slide_header(slide, title, subtitle)
    y0 = 1.35 if subtitle else 1.15
    w = 7.6 if side_card else 12.3
    h = 7.15 - y0 - (0.75 if caption else 0.0)
    plain_code_box(slide, art, 0.5, y0, w, h,
                   font_size=font_size, accent=accent, text_color=SILVER)
    if side_card:
        ct, lines, cac = side_card
        info_card(slide, ct, lines, 8.35, y0, 4.45, _card_h(lines), accent=cac)
    if caption:
        callout(slide, caption, 0.5, 7.15 - 0.62, w, 0.6, color=accent)
    return slide


def slide_table(prs, title, subtitle, headers, rows, widths,
                header_colors=None, row_h=0.48, body_size=10):
    slide = new_slide(prs)
    slide_header(slide, title, subtitle)
    y0 = 1.35 if subtitle else 1.2
    styled_table(slide, headers, rows, 0.5, y0, widths, row_h=row_h,
                 header_colors=header_colors, body_size=body_size)
    return slide


def slide_compare(prs, title, subtitle, lt, ll, rt, rl,
                  lc=ROSE, rc=EMERALD, bottom=None):
    slide = new_slide(prs)
    slide_header(slide, title, subtitle)
    y0 = 1.35 if subtitle else 1.15
    h = max(_card_h(ll), _card_h(rl))
    comparison_panel(slide, 0.5, y0, 12.3, h, lt, ll, rt, rl,
                     left_color=lc, right_color=rc)
    if bottom:
        text, col = bottom
        callout(slide, text, 0.5, y0 + h + 0.25, 12.3, 0.65, color=col)
    return slide


def slide_mistakes(prs, title, items):
    """Grid 2x3 kesalahan umum. items: (judul, deskripsi, warna)."""
    slide = new_slide(prs)
    slide_header(slide, title)
    for i, (t, d, col) in enumerate(items[:6]):
        cn = i % 3
        rn = i // 3
        mx = 0.4 + cn * 4.25
        my = 1.1 + rn * 2.95
        rounded_rect(slide, mx, my, 4.1, 2.7, BG_CARD, line_color=col, line_w=1.0)
        rect(slide, mx, my, 4.1, 0.08, col)
        tb(slide, t, mx + 0.2, my + 0.2, 3.85, 0.55, size=12, bold=True, color=col)
        tb(slide, d, mx + 0.2, my + 0.85, 3.85, 1.75, size=10.5, color=SILVER)
    return slide


def slide_twocode(prs, title, subtitle, code_l, code_r,
                  accent_l=PRIMARY, accent_r=VIOLET, caption=None,
                  font_size=10, label_l=None, label_r=None):
    slide = new_slide(prs)
    slide_header(slide, title, subtitle)
    y0 = 1.35 if subtitle else 1.15
    if label_l:
        tb(slide, label_l, 0.5, y0, 6.1, 0.3, size=12, bold=True, color=accent_l)
    if label_r:
        tb(slide, label_r, 6.85, y0, 6.0, 0.3, size=12, bold=True, color=accent_r)
    cy = y0 + (0.38 if (label_l or label_r) else 0.0)
    h = 7.15 - cy - (0.8 if caption else 0.05)
    plain_code_box(slide, code_l, 0.5, cy, 6.1, h, font_size=font_size, accent=accent_l)
    plain_code_box(slide, code_r, 6.85, cy, 5.98, h, font_size=font_size, accent=accent_r)
    if caption:
        text, col = caption
        callout(slide, text, 0.5, 7.15 - 0.65, 12.33, 0.62, color=col)
    return slide


# ═══════════════════════════════════════════════════════════════════
# MODUL 01 — HTML Dasar
# ═══════════════════════════════════════════════════════════════════

def build_01(prs):
    C = PRIMARY
    web_cover(prs, 1, "HTML Dasar",
              ["HyperText Markup Language",
               "Struktur  ·  Teks  ·  Media  ·  Semantik"],
              color=C, pills=["struktur", "teks", "media", "semantik"])

    agenda_slide(prs, "Agenda — Modul 01: HTML Dasar", [
        ("01", "Fondasi\nHTML", PRIMARY,
         ["Apa itu HTML?", "HTML vs CSS vs JS", "Cara browser merender", "Tag · elemen · atribut"]),
        ("02", "Teks &\nMedia", EMERALD,
         ["Heading h1–h6", "Paragraf & format", "Link & gambar", "List ul / ol"]),
        ("03", "Data &\nFormulir", AMBER,
         ["Tabel tr/th/td", "Form label+input", "Semantic HTML", "header/nav/main"]),
        ("04", "Latihan &\nPitfall", VIOLET,
         ["Profil Saya", "10 komponen wajib", "Kesalahan umum", "Cheatsheet"]),
    ])

    section_divider(prs, "01", "Fondasi HTML",
                    "HTML = struktur, CSS = tampilan, JS = perilaku", color=C)

    # Apa itu HTML? — selaras slide dosen
    slide = new_slide(prs)
    slide_header(slide, "Apa itu HTML?",
                 "HyperText Markup Language — bahasa markup, BUKAN bahasa pemrograman")
    info_card(slide, "Definisi & Peran", [
        "• Menyusun STRUKTUR dan KONTEN halaman web",
        "• Menentukan makna: judul, paragraf, gambar, tautan",
        "• File teks berekstensi .html dibaca browser",
        "• Tidak mengatur warna, animasi, atau logika",
    ], 0.5, 1.2, 6.3, 3.15, accent=PRIMARY)
    info_card(slide, "HTML digunakan untuk", [
        "• Judul & paragraf  (headings, paragraphs)",
        "• Media & tautan    (gambar, URL)",
        "• Data terstruktur  (daftar, tabel)",
        "• Input pengguna    (formulir & kontrol)",
        "• Tata letak dasar  (kerangka halaman)",
    ], 7.0, 1.2, 5.8, 3.15, accent=CYAN)
    callout(slide,
            "PENTING: HTML memberi MAKNA. CSS memberi TAMPILAN. Jangan campur keduanya di satu file.",
            0.5, 4.55, 12.3, 0.7, color=AMBER, icon="!")
    metric_card(slide, "Bukan pemrograman", "MARKUP", 0.5, 5.45, 4.0, 1.55, accent=PRIMARY)
    metric_card(slide, "Hasilnya", "STRUKTUR", 4.7, 5.45, 4.0, 1.55, accent=EMERALD)
    metric_card(slide, "Dibaca oleh", "BROWSER", 8.9, 5.45, 3.9, 1.55, accent=VIOLET)

    # Analogi rumah — 3 pilar seperti slide dosen
    slide = new_slide(prs)
    slide_header(slide, "HTML, CSS, dan JavaScript",
                 "Analogi rumah: rangka · cat & dekorasi · instalasi listrik")
    pillars = [
        (0.5, PRIMARY, "HTML", "Struktur & Konten", "Analogi: rangka rumah",
         ["Pondasi halaman", "Heading & paragraf", "Gambar & tautan", "Urutan konten"]),
        (4.78, CYAN, "CSS", "Tampilan & Desain", "Analogi: cat & dekorasi",
         ["Warna & tipografi", "Jarak & border", "Layout visual", "Responsive"]),
        (9.06, AMBER, "JS", "Interaksi & Perilaku", "Analogi: listrik & saklar",
         ["Klik & validasi", "Data dinamis", "Filter & hitung", "API / state"]),
    ]
    for x, col, name, role, analogi, bullets in pillars:
        rounded_rect(slide, x, 1.25, 4.05, 5.0, BG_CARD, line_color=col, line_w=1.2)
        rect(slide, x, 1.25, 4.05, 0.1, col)
        tb(slide, name, x + 0.2, 1.5, 3.65, 0.5, size=26, bold=True, color=col)
        tb(slide, role, x + 0.2, 2.05, 3.65, 0.35, size=13, bold=True, color=WHITE)
        pill(slide, analogi, x + 0.2, 2.5, 3.65, 0.38, color=col)
        for i, b in enumerate(bullets):
            tb(slide, "▸  " + b, x + 0.25, 3.1 + i * 0.55, 3.55, 0.45,
               size=13, color=SILVER)
    tb(slide, "Ketiganya wajib dikuasai terpisah dulu — baru digabung di proyek.",
       0.5, 6.45, 12.3, 0.4, size=12, italic=True, color=MUTED)

    # 01 02 03 proses render — numbered_step_card seperti dosen
    slide = new_slide(prs)
    slide_header(slide, "Bagaimana HTML Ditampilkan?",
                 "Dari kode mentah ke halaman visual — tiga langkah")
    numbered_step_card(slide, 1, "KODE HTML",
                       "File teks .html berisi tag terstruktur. Ini dokumen sumber — belum ada warna atau layout.",
                       0.5, 1.25, 12.3, 1.55, accent=PRIMARY)
    numbered_step_card(slide, 2, "BROWSER",
                       "Chrome / Safari / Firefox mengurai (parse) tag menjadi pohon elemen (DOM), lalu merender.",
                       0.5, 3.0, 12.3, 1.55, accent=CYAN)
    numbered_step_card(slide, 3, "WEBSITE",
                       "Hasil visual di layar: heading, paragraf, gambar, tautan. Yang kamu lihat adalah hasil render, bukan file mentah.",
                       0.5, 4.75, 12.3, 1.55, accent=EMERALD)
    callout(slide, "Kalau tampilan aneh: buka View Source / Inspect — bandingkan tag dengan yang kamu tulis.",
            0.5, 6.5, 12.3, 0.6, color=VIOLET)

    # Struktur dasar — kode kiri, 3 kartu kanan
    slide_code(prs, "Struktur Dasar Dokumen HTML",
               "<!DOCTYPE html> wajib di baris pertama — menandai standar HTML5",
               '<!DOCTYPE html>\n'
               '<html>\n'
               '  <head>\n'
               '    <title>Judul Halaman</title>\n'
               '  </head>\n'
               '  <body>\n'
               '    Isi halaman web\n'
               '  </body>\n'
               '</html>',
               accent=C, font_size=14, code_w=6.4, code_h=5.4,
               right_cards=[
                   ("<!DOCTYPE html>",
                    ["• Deklarasi, BUKAN tag HTML",
                     "• Wajib paling atas",
                     "• Tanpa ini: quirks mode"], ROSE),
                   ("<html>  ROOT",
                    ["• Pembungkus seluruh dokumen",
                     "• Tambah lang=\"id\" (aksesibilitas)"], PRIMARY),
                   ("<head> vs <body>",
                    ["• head = metadata, tak tampil",
                     "• body = semua yang tampil"], EMERALD),
               ])

    # Tag vs Element vs Attribute — visual seperti dosen
    slide = new_slide(prs)
    slide_header(slide, "Tag, Element, dan Attribute",
                 "Tiga istilah yang sering tertukar — hafalkan perbedaannya")
    plain_code_box(slide,
                   '<p id="intro">\n'
                   '  Selamat datang\n'
                   '</p>',
                   0.5, 1.2, 6.3, 2.35, font_size=18, accent=PRIMARY)
    info_card(slide, "Empat bagian baris itu", [
        ("<p>  →  TAG", PRIMARY),
        "Penanda buka / tutup elemen",
        ("<p>...</p>  →  ELEMENT", EMERALD),
        "Keseluruhan dari buka sampai tutup",
        ("id=\"intro\"  →  ATTRIBUTE", AMBER),
        "Info tambahan di tag pembuka",
        ("Selamat datang  →  CONTENT", CYAN),
        "Teks / isi di dalam elemen",
    ], 7.0, 1.2, 5.8, 5.5, accent=AMBER, body_size=11)
    callout(slide, "Tag berpasangan: <h1>...</h1>   ·   Empty tag (self-closing): <br> <hr> <img>",
            0.5, 3.75, 6.3, 1.1, color=CYAN)
    callout(slide, "Atribut SELALU di tag pembuka: nama=\"nilai\". Tanpa spasi di sekitar =.",
            0.5, 5.05, 6.3, 1.1, color=VIOLET)

    section_divider(prs, "02", "Teks, Daftar, Tautan, Gambar",
                    "Konten inti hampir semua halaman web", color=EMERALD)

    # Heading hierarchy visual — seperti slide dosen
    slide = new_slide(prs)
    slide_header(slide, "Heading h1 sampai h6",
                 "Pakai heading berdasarkan STRUKTUR konten, bukan ukuran huruf")
    levels = [
        ("<h1>", "Judul utama halaman", PRIMARY, 0.0),
        ("<h2>", "Bagian besar", CYAN, 0.45),
        ("<h3>", "Sub-bagian", EMERALD, 0.9),
        ("<h4>", "Lebih dalam", AMBER, 1.35),
        ("<h5>", "Detail", VIOLET, 1.8),
        ("<h6>", "Paling dalam", ROSE, 2.25),
    ]
    for i, (tag, desc, col, indent) in enumerate(levels):
        y = 1.2 + i * 0.78
        rounded_rect(slide, 0.5 + indent, y, 6.6 - indent, 0.68, BG_CARD,
                     line_color=col, line_w=1.0)
        rect(slide, 0.5 + indent, y, 0.12, 0.68, col)
        tb(slide, tag, 0.8 + indent, y + 0.12, 1.5, 0.45, size=16, bold=True, color=col)
        tb(slide, desc, 2.4 + indent, y + 0.16, 4.4, 0.4, size=13, color=SILVER)
    info_card(slide, "Best practice", [
        "• Tepat SATU <h1> per halaman",
        "• Jangan loncat: h1 → h3 tanpa h2",
        "• Bukan untuk memperbesar teks",
        "  (itu tugas CSS font-size)",
        "• Screen reader baca urutan ini",
        "  sebagai peta dokumen",
    ], 7.5, 1.2, 5.3, 4.55, accent=AMBER)
    callout(slide, "<p> untuk paragraf. <strong> makna penting · <em> penekanan · <b>/<i> murni visual.",
            0.5, 6.05, 12.3, 0.7, color=EMERALD)

    slide_table(prs, "Tag Teks, Daftar, dan Pemisah", "Hafalkan — ini muncul di ujian dan dipakai setiap hari",
                ["Tag", "Fungsi", "Catatan"],
                [["<h1>–<h6>", "Heading level 1–6", "Satu <h1> per halaman"],
                 ["<p>", "Paragraf", "Blok teks utama"],
                 ["<strong> / <em>", "Penting / penekanan", "Bermakna, bukan sekadar tebal/miring"],
                 ["<ul> + <li>", "Daftar tak berurut", "Bullet points"],
                 ["<ol> + <li>", "Daftar berurut", "Angka otomatis"],
                 ["<blockquote>", "Kutipan panjang", "Sertakan cite bila ada"],
                 ["<code> / <pre>", "Kode inline / blok", "pre mempertahankan spasi"],
                 ["<br> / <hr>", "Ganti baris / garis", "Jangan pakai <br> utk jarak"]],
                [2.4, 4.6, 5.3],
                header_colors=[PRIMARY, EMERALD, AMBER])

    slide_code(prs, "Tautan dan Gambar",
               "href menentukan tujuan; alt wajib untuk aksesibilitas",
               '<!-- Tautan keluar (buka tab baru) -->\n'
               '<a href="https://developer.mozilla.org"\n'
               '   target="_blank" rel="noopener">MDN</a>\n'
               '\n'
               '<!-- Tautan relatif antar-halaman -->\n'
               '<a href="tentang.html">Tentang Kami</a>\n'
               '\n'
               '<!-- Anchor ke bagian halaman -->\n'
               '<a href="#kontak">Lompat ke Kontak</a>\n'
               '\n'
               '<!-- Gambar: alt WAJIB -->\n'
               '<img src="img/logo.png"\n'
               '     alt="Logo Toko Kopi Senja"\n'
               '     width="200" height="80">',
               accent=EMERALD,
               right_cards=[("Jenis URL",
                             ["• Absolut: https://situs.com/x",
                              "• Relatif: img/foto.jpg",
                              "• Anchor: #id-elemen",
                              "• mailto: / tel: juga bisa"], EMERALD),
                            ("Mengapa alt penting?",
                             ["• Dibaca screen reader",
                              "• Tampil saat gambar gagal",
                              "• Dinilai mesin pencari",
                              "• alt=\"\" utk gambar dekoratif"], AMBER)])

    section_divider(prs, "03", "Tabel dan Formulir",
                    "Data terstruktur dan input pengguna", color=AMBER)

    slide_code(prs, "Tabel: Struktur yang Benar",
               "thead + tbody, th untuk sel judul, td untuk data",
               '<table>\n'
               '  <caption>Nilai Praktikum</caption>\n'
               '  <thead>\n'
               '    <tr>\n'
               '      <th>Nama</th>\n'
               '      <th>Modul</th>\n'
               '      <th>Nilai</th>\n'
               '    </tr>\n'
               '  </thead>\n'
               '  <tbody>\n'
               '    <tr>\n'
               '      <td>Sinta</td>\n'
               '      <td>HTML Dasar</td>\n'
               '      <td>92</td>\n'
               '    </tr>\n'
               '  </tbody>\n'
               '</table>',
               accent=AMBER,
               right_cards=[("Aturan tabel",
                             ["• <tr> = baris, <td> = sel data",
                              "• <th> = sel judul (tebal + scope)",
                              "• thead/tbody memisah struktur",
                              "• caption = judul tabel",
                              "• colspan/rowspan gabung sel"], AMBER),
                            ("Kapan pakai tabel?",
                             ["• HANYA untuk data tabular",
                              "• BUKAN untuk layout halaman",
                              "  (itu tugas CSS grid/flexbox)"], ROSE)])

    slide_code(prs, "Formulir: label, input, dan validasi bawaan",
               "Setiap input butuh label; type menentukan keyboard & validasi",
               '<form action="/daftar" method="post">\n'
               '  <label for="nama">Nama lengkap</label>\n'
               '  <input id="nama" name="nama"\n'
               '         type="text" required>\n'
               '\n'
               '  <label for="email">Email</label>\n'
               '  <input id="email" name="email"\n'
               '         type="email" required>\n'
               '\n'
               '  <label for="prodi">Prodi</label>\n'
               '  <select id="prodi" name="prodi">\n'
               '    <option value="ti">Teknik Info</option>\n'
               '    <option value="si">Sistem Info</option>\n'
               '  </select>\n'
               '\n'
               '  <button type="submit">Kirim</button>\n'
               '</form>',
               accent=AMBER, font_size=10,
               right_cards=[("Hubungan label–input",
                             ["• for pada label = id pada input",
                              "• Klik label → fokus ke input",
                              "• name = kunci data saat submit"], AMBER),
                            ("Type input berguna",
                             ["• email, number, date, password",
                              "• checkbox, radio, file, range",
                              "• required, min, max, pattern",
                              "  = validasi tanpa JavaScript"], EMERALD)])

    section_divider(prs, "04", "HTML Semantik",
                    "Tag yang menjelaskan MAKNA konten, bukan hanya tampilan",
                    color=VIOLET)

    slide_ascii(prs, "Peta Halaman Semantik",
                "Struktur umum: header → nav → main (section/article) → footer",
                '┌──────────────────────────────────────────┐\n'
                '│ <header>  logo + judul situs             │\n'
                '│   <nav>   menu navigasi utama            │\n'
                '├──────────────────────────────────────────┤\n'
                '│ <main>    konten utama (1x per halaman)  │\n'
                '│  ┌────────────────────┐ ┌─────────────┐  │\n'
                '│  │ <section>          │ │ <aside>     │  │\n'
                '│  │   <article>        │ │  sidebar,   │  │\n'
                '│  │   konten mandiri   │ │  info       │  │\n'
                '│  │   <article> ...    │ │  tambahan   │  │\n'
                '│  └────────────────────┘ └─────────────┘  │\n'
                '├──────────────────────────────────────────┤\n'
                '│ <footer>  kontak + hak cipta             │\n'
                '└──────────────────────────────────────────┘',
                caption="div = kotak TANPA makna. Pakai tag semantik dulu, div hanya jika perlu wadah netral.",
                accent=VIOLET,
                side_card=("Mengapa semantik?",
                           ["• Screen reader bisa lompat",
                            "  antar-bagian halaman",
                            "• SEO: mesin pencari paham",
                            "  struktur konten",
                            "• Kode mudah dibaca tim",
                            "• Dipakai di praktikum",
                            "  01-html-dasar & studi",
                            "  kasus landing page"], VIOLET))

    # Latihan resmi dosen — Profil Saya
    slide = new_slide(prs)
    slide_header(slide, "Latihan: Profil Saya",
                 "Halaman HTML semantik TANPA CSS — 10 komponen wajib (slide dosen)")
    rounded_rect(slide, 0.5, 1.2, 7.4, 5.5, BG_CARD, line_color=VIOLET, line_w=1.0)
    rect(slide, 0.5, 1.2, 7.4, 0.08, VIOLET)
    tb(slide, "Komponen wajib", 0.75, 1.4, 7.0, 0.4, size=16, bold=True, color=VIOLET)
    items = [
        "01  Judul halaman (<title> + <h1>)",
        "02  Nama lengkap",
        "03  NIM mahasiswa",
        "04  Foto profil  (<img src alt>)",
        "05  Deskripsi diri  (<p>)",
        "06  Daftar hobi  (<ul>)",
        "07  Daftar mata kuliah  (<ol>)",
        "08  Link sosmed / web  (<a>)",
        "09  Tabel data  (<table>)",
        "10  Form kontak sederhana",
    ]
    for i, t in enumerate(items):
        col = [PRIMARY, CYAN, EMERALD, AMBER, VIOLET][i % 5]
        y = 1.9 + i * 0.45
        circle(slide, 1.05, y + 0.18, 0.14, col)
        tb(slide, t, 1.35, y, 6.3, 0.4, size=13, color=SILVER)
    info_card(slide, "Aturan pengerjaan", [
        "• FOKUS pada struktur semantik",
        "• Jangan pakai style / CSS dulu",
        "• Tag yang tepat > terlihat bagus",
        "• header / main / footer wajib",
        "• Kerjakan di 1-pembelajaran/",
        "  01-html-dasar lalu bandingkan",
        "  dengan 2-kunci-jawaban/",
    ], 8.15, 1.2, 4.65, 5.5, accent=AMBER)

    slide_mistakes(prs, "Kesalahan Umum HTML — Hindari Ini!", [
        ("1. Lupa tag penutup",
         "<div> tanpa </div> merusak layout.\nIndentasi rapi membantu melihat pasangan tag.",
         ROSE),
        ("2. Heading loncat level",
         "h1 → h3 tanpa h2 membingungkan\nscreen reader. Heading = outline dokumen.",
         ROSE),
        ("3. <img> tanpa alt",
         "Gambar tak terbaca screen reader\ndan tampak rusak saat gagal dimuat.",
         AMBER),
        ("4. <br> untuk jarak",
         "Jarak antar-elemen itu tugas CSS\n(margin/padding), bukan <br><br>.",
         AMBER),
        ("5. Input tanpa <label>",
         "Placeholder BUKAN pengganti label —\nhilang saat diketik, tak dibaca AT.",
         VIOLET),
        ("6. div untuk segalanya",
         "\"div soup\" sulit dirawat.\nGunakan header/main/section/footer.",
         VIOLET),
    ])

    slide_twocode(prs, "Cheatsheet HTML", None,
                  '<!-- Kerangka -->\n'
                  '<!DOCTYPE html>\n'
                  '<html lang="id">\n'
                  '<head>\n'
                  '  <meta charset="UTF-8">\n'
                  '  <meta name="viewport" content=\n'
                  '   "width=device-width, initial-scale=1.0">\n'
                  '  <title>Judul</title>\n'
                  '</head>\n'
                  '<body> ... </body>\n'
                  '</html>\n'
                  '\n'
                  '<!-- Teks -->\n'
                  '<h1>–<h6>, <p>, <strong>, <em>\n'
                  '<ul>/<ol> + <li>, <blockquote>',
                  '<!-- Tautan & media -->\n'
                  '<a href="url" target="_blank">..</a>\n'
                  '<img src="x.jpg" alt="deskripsi">\n'
                  '\n'
                  '<!-- Tabel -->\n'
                  '<table><thead><tr><th>..\n'
                  '<tbody><tr><td>..\n'
                  '\n'
                  '<!-- Form -->\n'
                  '<label for="x">..</label>\n'
                  '<input id="x" name="x" type="email"\n'
                  '       required>\n'
                  '\n'
                  '<!-- Semantik -->\n'
                  '<header> <nav> <main> <section>\n'
                  '<article> <aside> <footer>',
                  accent_l=PRIMARY, accent_r=EMERALD,
                  caption=("Latihan: 1-pembelajaran/01-html-dasar (5 bab) — kerjakan semua TODO!", EMERALD))

    web_closing(prs, "01", "HTML Dasar — struktur dan makna konten", [
        (PRIMARY, "Struktur",
         "DOCTYPE → html → head (metadata) → body (konten tampil). Viewport wajib untuk responsive."),
        (EMERALD, "Konten",
         "Heading berjenjang, paragraf, list, tautan (href), gambar (alt wajib)."),
        (AMBER, "Tabel & Form",
         "Tabel hanya untuk data. Form: label terhubung id, type + required = validasi gratis."),
        (VIOLET, "Semantik",
         "header/nav/main/section/article/footer memberi makna — aksesibilitas + SEO."),
        (ROSE, "Pitfall",
         "Tag tak ditutup, heading loncat, img tanpa alt, br untuk jarak, input tanpa label."),
    ])


# ═══════════════════════════════════════════════════════════════════
# MODUL 02 — CSS Dasar
# ═══════════════════════════════════════════════════════════════════

def build_02(prs):
    C = CYAN
    web_cover(prs, 2, "CSS Dasar",
              ["Cascading Style Sheets",
               "Selector  ·  Box Model  ·  Flexbox  ·  Responsive"],
              color=C, pills=["selector", "box-model", "flexbox", "responsive"])

    agenda_slide(prs, "Agenda — Modul 02: CSS Dasar", [
        ("01", "Cara Kerja\nCSS", PRIMARY,
         ["Mengapa CSS?", "Syntax rule", "Selector E/C/ID", "Inline/Internal/External"]),
        ("02", "Box\nModel", EMERALD,
         ["content-padding", "border-margin", "width/height", "display & position"]),
        ("03", "Layout &\nResponsive", AMBER,
         ["Flexbox axis", "justify/align", "Media query", "Cascade"]),
        ("04", "Latihan &\nPitfall", VIOLET,
         ["Desain Profil", "Typography", "Kesalahan umum", "Cheatsheet"]),
    ])

    section_divider(prs, "01", "Cara Kerja CSS",
                    "Selector memilih elemen, deklarasi mengubah tampilannya", color=C)

    # Mengapa CSS — comparison seperti dosen
    slide = new_slide(prs)
    slide_header(slide, "Mengapa Kita Membutuhkan CSS?",
                 "HTML murni monoton — CSS membuat halaman layak dibaca dan profesional")
    comparison_panel(slide, 0.5, 1.2, 12.3, 4.35,
                     "HTML Tanpa CSS",
                     ["Tampilan default browser",
                      "Teks hitam di latar putih",
                      "Tidak ada jarak yang rapi",
                      "Gambar ukuran asli",
                      "Sulit dibaca lama-lama"],
                     "HTML + CSS",
                     ["Kartu, warna, tipografi",
                      "Foto lingkaran + bayangan",
                      "Padding & margin terukur",
                      "Layout flex / grid",
                      "Nyaman di HP dan desktop"],
                     left_color=ROSE, right_color=EMERALD)
    callout(slide, "HTML = apa isinya. CSS = bagaimana kelihatannya. Pisahkan file: index.html + css/style.css.",
            0.5, 5.75, 12.3, 0.85, color=CYAN)

    # Syntax visual
    slide = new_slide(prs)
    slide_header(slide, "Syntax CSS",
                 "selector { property: value; } — pilih elemen, ubah aspek visualnya")
    plain_code_box(slide,
                   'h1 {\n'
                   '    color: blue;\n'
                   '    font-size: 32px;\n'
                   '}',
                   0.5, 1.25, 6.4, 2.8, font_size=20, accent=CYAN)
    info_card(slide, "Tiga bagian rule", [
        ("selector  (h1)", PRIMARY),
        "Elemen HTML yang diincar",
        ("property  (color, font-size)", AMBER),
        "Aspek visual yang diubah",
        ("value  (blue, 32px)", EMERALD),
        "Nilai spesifik properti itu",
    ], 7.15, 1.25, 5.65, 4.6, accent=CYAN)
    numbered_step_card(slide, 1, "Inline",
                       '<p style="color:red"> — menempel di HTML, sulit dirawat. Hindari.',
                       0.5, 4.25, 6.4, 1.15, accent=ROSE)
    numbered_step_card(slide, 2, "Internal",
                       "<style> di <head> — hanya berlaku di 1 halaman.",
                       0.5, 5.55, 6.4, 1.15, accent=AMBER)

    # Selector 3 kartu
    slide = new_slide(prs)
    slide_header(slide, "Tiga Selector Dasar",
                 "Element · Class (titik) · ID (pagar) — class adalah pilihan utama")
    selectors = [
        (0.5, PRIMARY, "Element", "p { color: blue; }",
         "Pilih semua tag <p>", "Paling lemah · gaya global"),
        (4.78, EMERALD, "Class", ".judul { color: red; }",
         'HTML: class="judul"', "Reusable · pilihan utama"),
        (9.06, AMBER, "ID", "#header { background: gray; }",
         'HTML: id="header"', "Unik 1× · specificity tinggi"),
    ]
    for x, col, name, code, html, note in selectors:
        rounded_rect(slide, x, 1.25, 4.05, 4.35, BG_CARD, line_color=col, line_w=1.2)
        rect(slide, x, 1.25, 4.05, 0.1, col)
        tb(slide, name, x + 0.2, 1.5, 3.65, 0.45, size=22, bold=True, color=col)
        plain_code_box(slide, code, x + 0.2, 2.1, 3.65, 1.15, font_size=13, accent=col)
        tb(slide, html, x + 0.25, 3.4, 3.55, 0.55, size=13, color=SILVER)
        pill(slide, note, x + 0.25, 4.15, 3.55, 0.45, color=col)
    callout(slide, "Specificity: inline > #id > .class > elemen. Skor sama → rule TERAKHIR yang menang (cascade).",
            0.5, 5.85, 12.3, 0.85, color=AMBER)

    slide_table(prs, "Cascade & Specificity — Siapa yang Menang?",
                "Urutan keputusan browser saat dua rule bertabrakan",
                ["Prioritas", "Sumber", "Contoh", "Catatan"],
                [["1 (tertinggi)", "!important", "color: red !important", "Hindari — sulit di-debug"],
                 ["2", "Inline style", "style=\"color:red\"", "Menempel di HTML"],
                 ["3", "ID selector", "#header", "Specificity (1,0,0)"],
                 ["4", "Class/pseudo", ".btn, :hover", "Specificity (0,1,0)"],
                 ["5", "Elemen", "p, div, a", "Specificity (0,0,1)"],
                 ["6 (terendah)", "Inherited", "warna dari parent", "font/color menurun, box tidak"]],
                [1.7, 2.6, 4.0, 4.0],
                header_colors=[ROSE, AMBER, PRIMARY, EMERALD])

    section_divider(prs, "02", "Box Model",
                    "Setiap elemen adalah kotak: content, padding, border, margin",
                    color=EMERALD)

    # Box model visual — nested rects ala diagram CP, bukan ASCII
    slide = new_slide(prs)
    slide_header(slide, "Box Model — Empat Lapisan Kotak",
                 "Setiap elemen HTML adalah kotak: content → padding → border → margin")
    ox, oy = 0.5, 1.2
    rounded_rect(slide, ox, oy, 7.5, 5.55, RGBColor(0x14, 0x2E, 0x24),
                 line_color=EMERALD, line_w=1.5)
    tb(slide, "MARGIN  ·  jarak antar elemen", ox + 0.2, oy + 0.08, 7.1, 0.32,
       size=11, bold=True, color=EMERALD)
    rounded_rect(slide, ox + 0.55, oy + 0.5, 6.4, 4.5, RGBColor(0x2E, 0x24, 0x14),
                 line_color=AMBER, line_w=1.5)
    tb(slide, "BORDER  ·  garis tepi", ox + 0.75, oy + 0.58, 6.0, 0.32,
       size=11, bold=True, color=AMBER)
    rounded_rect(slide, ox + 1.15, oy + 1.05, 5.2, 3.4, RGBColor(0x14, 0x24, 0x2E),
                 line_color=PRIMARY, line_w=1.5)
    tb(slide, "PADDING  ·  ruang dalam", ox + 1.35, oy + 1.13, 4.8, 0.32,
       size=11, bold=True, color=PRIMARY)
    rounded_rect(slide, ox + 1.9, oy + 1.7, 3.7, 2.1, PRIMARY)
    tb(slide, "CONTENT", ox + 1.9, oy + 2.15, 3.7, 0.45,
       size=18, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
    tb(slide, "teks / gambar", ox + 1.9, oy + 2.6, 3.7, 0.4,
       size=12, color=BG_DEEP, align=PP_ALIGN.CENTER)
    info_card(slide, "box-sizing: border-box", [
        "content-box (default):",
        "  width = isi saja",
        "  padding+border MENAMBAH",
        "  lebar total → pusing!",
        "",
        "border-box:",
        "  width = TOTAL kotak",
        "",
        "Set di awal setiap proyek:",
        "* { box-sizing: border-box; }",
    ], 8.25, 1.2, 4.55, 5.55, accent=EMERALD)

    slide_code(prs, "Box Model dalam Praktik",
               "Shorthand: 1 nilai=semua sisi · 2 nilai=atas-bawah kiri-kanan",
               '* { box-sizing: border-box; }\n'
               '\n'
               '.kartu {\n'
               '  width: 320px;\n'
               '  padding: 24px;          /* semua sisi */\n'
               '  padding: 16px 24px;     /* v | h */\n'
               '  border: 1px solid #d1d5db;\n'
               '  border-radius: 12px;\n'
               '  margin: 0 auto;         /* tengah! */\n'
               '  box-shadow: 0 4px 12px\n'
               '              rgba(0, 0, 0, 0.08);\n'
               '}',
               accent=EMERALD,
               right_cards=[("margin: 0 auto",
                             ["• auto kiri-kanan = elemen blok",
                              "  dengan width berada di tengah",
                              "• Trik klasik menengahkan kartu"], EMERALD),
                            ("Margin collapse",
                             ["• Margin vertikal 2 elemen",
                              "  bertemu → diambil TERBESAR,",
                              "  bukan dijumlah",
                              "• Sering bikin bingung pemula"], AMBER)])

    section_divider(prs, "03", "Warna, Unit, Tipografi",
                    "Nilai yang paling sering ditulis di CSS", color=AMBER)

    slide_table(prs, "Unit dan Warna — Referensi Cepat",
                "px untuk detail kecil, rem untuk ukuran teks, % untuk lebar relatif",
                ["Nilai", "Contoh", "Kapan dipakai"],
                [["px", "border: 1px", "Detail presisi: border, shadow"],
                 ["rem", "font-size: 1.25rem", "Teks & spacing (1rem = 16px), ikut setelan user"],
                 ["%", "width: 50%", "Lebar relatif terhadap parent"],
                 ["vw / vh", "height: 100vh", "Relatif ukuran layar (hero section)"],
                 ["Hex", "#0ea5e9", "Warna paling umum"],
                 ["rgb(a)", "rgba(0,0,0,0.5)", "Perlu transparansi"],
                 ["hsl", "hsl(199 89% 48%)", "Mudah diatur terang/gelapnya"]],
                [2.0, 3.6, 6.7],
                header_colors=[PRIMARY, AMBER, EMERALD])

    slide_code(prs, "Tipografi Dasar",
               "Empat properti ini menentukan 90% kenyamanan baca",
               'body {\n'
               '  font-family: "Inter", system-ui,\n'
               '               sans-serif;\n'
               '  font-size: 1rem;      /* 16px */\n'
               '  line-height: 1.6;     /* tanpa unit */\n'
               '  color: #1f2937;\n'
               '}\n'
               '\n'
               'h1 {\n'
               '  font-size: 2rem;\n'
               '  font-weight: 700;\n'
               '  letter-spacing: -0.02em;\n'
               '}\n'
               '\n'
               '.tercoret { text-decoration: line-through; }\n'
               '.kapital  { text-transform: uppercase; }',
               accent=AMBER, font_size=10,
               right_cards=[("Aturan praktis",
                             ["• line-height 1.5–1.7 utk paragraf",
                              "• Fallback font selalu ada",
                              "  (system-ui, sans-serif)",
                              "• Kontras teks vs latar cukup",
                              "  (WCAG minimal 4.5:1)"], AMBER)])

    section_divider(prs, "04", "Pseudo-class & Interaksi",
                    "Halaman terasa hidup: hover, focus, transisi", color=VIOLET)

    slide_code(prs, "Pseudo-class: State Elemen",
               ":hover mouse di atas · :focus dipilih keyboard · :disabled nonaktif",
               '.tombol {\n'
               '  background: #0ea5e9;\n'
               '  color: white;\n'
               '  transition: background 150ms ease,\n'
               '              transform 150ms ease;\n'
               '}\n'
               '.tombol:hover {\n'
               '  background: #0284c7;\n'
               '  transform: translateY(-1px);\n'
               '}\n'
               '.tombol:focus-visible {\n'
               '  outline: 3px solid #38bdf8;\n'
               '  outline-offset: 2px;\n'
               '}\n'
               'input:invalid { border-color: #ef4444; }\n'
               'li:nth-child(odd) { background: #f8fafc; }',
               accent=VIOLET, font_size=10,
               right_cards=[("Jangan hapus outline!",
                             ["• outline: none tanpa ganti =",
                              "  pengguna keyboard tersesat",
                              "• Pakai :focus-visible + outline",
                              "  custom yang jelas"], ROSE),
                            ("Transisi halus",
                             ["• transition di state NORMAL,",
                              "  bukan di :hover",
                              "• 150–250ms terasa responsif",
                              "• Animasikan transform/opacity"], EMERALD)])

    # Flexbox visual — seperti slide dosen + gaya CP
    slide = new_slide(prs)
    slide_header(slide, "Flexbox — Sumbu Utama vs Sumbu Silang",
                 "display:flex  ·  justify-content = main axis  ·  align-items = cross axis")
    tb(slide, "ROW  →  kiri ke kanan (default)", 0.5, 1.15, 6.3, 0.35,
       size=14, bold=True, color=PRIMARY)
    rounded_rect(slide, 0.5, 1.55, 6.3, 2.15, BG_CARD, line_color=PRIMARY, line_w=1.0)
    for i, (lab, col) in enumerate([("1", PRIMARY), ("2", EMERALD), ("3", AMBER)]):
        rounded_rect(slide, 0.75 + i * 1.95, 1.9, 1.7, 1.4, col)
        tb(slide, "Item " + lab, 0.75 + i * 1.95, 2.35, 1.7, 0.5,
           size=16, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
    tb(slide, "COLUMN  ↓  atas ke bawah", 7.05, 1.15, 5.75, 0.35,
       size=14, bold=True, color=AMBER)
    rounded_rect(slide, 7.05, 1.55, 5.75, 2.15, BG_CARD, line_color=AMBER, line_w=1.0)
    for i, (lab, col) in enumerate([("1", PRIMARY), ("2", EMERALD), ("3", AMBER)]):
        rounded_rect(slide, 7.3 + i * 1.75, 1.9, 1.55, 1.4, col)
        tb(slide, lab, 7.3 + i * 1.75, 2.35, 1.55, 0.5,
           size=18, bold=True, color=BG_DEEP, align=PP_ALIGN.CENTER)
    metric_card(slide, "justify-content", "MAIN AXIS", 0.5, 3.95, 4.05, 1.35, accent=PRIMARY)
    metric_card(slide, "align-items", "CROSS AXIS", 4.7, 3.95, 4.05, 1.35, accent=EMERALD)
    metric_card(slide, "@media max-width 768", "COLUMN", 8.9, 3.95, 3.9, 1.35, accent=AMBER)
    callout(slide, "Desktop: flex-direction:row  ·  HP (≤768px): flex-direction:column  — inti responsive design.",
            0.5, 5.5, 12.3, 0.7, color=VIOLET)
    plain_code_box(slide,
                   '.container { display:flex; gap:20px; }   @media (max-width:768px) { .container { flex-direction:column; } }',
                   0.5, 6.35, 12.3, 0.75, font_size=13, accent=CYAN)

    # Latihan dosen — Desain Profil Mahasiswa
    slide = new_slide(prs)
    slide_header(slide, "Latihan: Desain Profil Mahasiswa",
                 "HTML semantik + CSS terpisah — brief resmi dosen")
    info_card(slide, "Komponen wajib", [
        "• Header & menu navigasi",
        "• Foto profil (lingkaran)",
        "• Nama dan NIM",
        "• Deskripsi diri & hobi",
        "• Daftar mata kuliah",
        "• Contact & footer",
    ], 0.5, 1.2, 6.2, 3.7, accent=VIOLET)
    info_card(slide, "Target implementasi CSS", [
        "• Typography & color (hex/rgb)",
        "• Background & border-radius",
        "• Margin & padding (box model)",
        "• Layout Flexbox (nav + kartu)",
        "• Responsive: column di ≤768px",
        "• File terpisah: css/style.css",
    ], 6.95, 1.2, 5.85, 3.7, accent=EMERALD)
    numbered_step_card(slide, 1, "Struktur dulu",
                       "Selesaikan HTML semantik (latihan Profil Saya) sebelum menambah CSS.",
                       0.5, 5.1, 12.3, 0.95, accent=PRIMARY)
    numbered_step_card(slide, 2, "Gaya kemudian",
                       "External CSS + class. Kerjakan 1-pembelajaran/02-css-dasar/01-kartu-profil.",
                       0.5, 6.2, 12.3, 0.95, accent=CYAN)

    slide_mistakes(prs, "Kesalahan Umum CSS — Hindari Ini!", [
        ("1. Perang !important",
         "Menang sesaat, kacau selamanya.\nPerbaiki specificity, bukan tambah !important.",
         ROSE),
        ("2. Lupa box-sizing",
         "width 300 + padding 24 = 348px!?\nSet * { box-sizing: border-box; } di awal.",
         ROSE),
        ("3. Selector terlalu dalam",
         "div .a ul li a span {...} rapuh.\nBeri class langsung pada target.",
         AMBER),
        ("4. px untuk semua ukuran teks",
         "Abaikan setelan font pengguna.\nGunakan rem untuk font-size.",
         AMBER),
        ("5. Margin untuk layout besar",
         "Menyusun kolom dengan margin manual\nrapuh — itu tugas flexbox/grid (Modul 03).",
         VIOLET),
        ("6. Styling pakai ID",
         "Specificity tinggi, susah dioverride.\nID untuk anchor/JS, class untuk CSS.",
         VIOLET),
    ])

    slide_twocode(prs, "Cheatsheet CSS Dasar", None,
                  '/* Reset minimal */\n'
                  '* { box-sizing: border-box; }\n'
                  'body { margin: 0;\n'
                  '  font-family: system-ui, sans-serif;\n'
                  '  line-height: 1.6; }\n'
                  '\n'
                  '/* Selector */\n'
                  'p        /* elemen  (0,0,1) */\n'
                  '.class   /* class   (0,1,0) */\n'
                  '#id      /* id      (1,0,0) */\n'
                  'nav a    /* turunan */\n'
                  '.a > .b  /* anak langsung */',
                  '/* Box model */\n'
                  'padding: 16px 24px;  /* v h */\n'
                  'margin: 0 auto;      /* tengah */\n'
                  'border: 1px solid #ddd;\n'
                  'border-radius: 12px;\n'
                  '\n'
                  '/* State */\n'
                  '.btn:hover        { ... }\n'
                  '.btn:focus-visible{ outline: ... }\n'
                  'input:invalid     { ... }\n'
                  '\n'
                  '/* Transisi */\n'
                  'transition: all 150ms ease;',
                  accent_l=CYAN, accent_r=VIOLET,
                  caption=("Latihan: 1-pembelajaran/02-css-dasar (4 bab: kartu profil → pseudo-class)", EMERALD))

    web_closing(prs, "02", "CSS Dasar — selector, box model, state", [
        (PRIMARY, "Rule & Selector",
         "selector { properti: nilai; }. Class = pilihan utama. External CSS via <link>."),
        (CYAN, "Cascade",
         "inline > id > class > elemen; skor sama → yang terakhir menang. Hindari !important."),
        (EMERALD, "Box Model",
         "content → padding → border → margin. Selalu box-sizing: border-box."),
        (AMBER, "Nilai",
         "rem untuk teks, px untuk detail, % untuk lebar. Hex/rgba/hsl untuk warna."),
        (VIOLET, "State",
         ":hover, :focus-visible, :invalid + transition = interaksi halus dan aksesibel."),
    ])


# ═══════════════════════════════════════════════════════════════════
# MODUL 03 — Layout Responsive (Flexbox, Grid, Media Query)
# ═══════════════════════════════════════════════════════════════════

def build_03(prs):
    C = EMERALD
    web_cover(prs, 3, "Layout Responsif",
              ["Flexbox · CSS Grid · media query",
               "Mobile-first: satu situs, semua ukuran layar"],
              color=C, pills=["flexbox", "grid", "breakpoint", "mobile-first"])

    agenda_slide(prs, "Agenda — Modul 03: Layout Responsif", [
        ("01", "Flexbox", PRIMARY,
         ["Main vs cross axis", "justify/align", "gap & wrap", "flex: 1"]),
        ("02", "CSS Grid", EMERALD,
         ["Baris + kolom", "fr & repeat()", "minmax()", "grid-area"]),
        ("03", "Media\nQuery", AMBER,
         ["Breakpoint", "Mobile-first", "min-width", "Viewport meta"]),
        ("04", "Strategi\nLayout", VIOLET,
         ["Flex vs Grid", "Pola umum", "auto-fit", "Menghindari overflow"]),
    ])

    section_divider(prs, "01", "Flexbox",
                    "Layout satu dimensi: baris ATAU kolom", color=PRIMARY)

    slide_ascii(prs, "Flexbox — Dua Sumbu",
                "justify-content bekerja di MAIN axis, align-items di CROSS axis",
                'flex-direction: row (default)\n'
                '\n'
                '        main axis ───────────────────▶\n'
                '  ┌────────────────────────────────────┐\n'
                '  │  ┌─────┐  ┌─────┐  ┌─────┐         │  cross\n'
                '  │  │  1  │  │  2  │  │  3  │         │  axis\n'
                '  │  └─────┘  └─────┘  └─────┘         │   │\n'
                '  └────────────────────────────────────┘   ▼\n'
                '     justify-content: flex-start | center |\n'
                '       space-between | space-around\n'
                '     align-items: stretch | center |\n'
                '       flex-start | flex-end\n'
                '\n'
                'flex-direction: column → sumbu BERTUKAR:\n'
                '  justify-content jadi vertikal!',
                caption="Ingat: justify = sumbu utama, align = sumbu silang. direction menukar keduanya.",
                accent=PRIMARY,
                side_card=("Properti container",
                           ["display: flex",
                            "flex-direction: row|column",
                            "justify-content: ...",
                            "align-items: ...",
                            "gap: 16px  ← jarak antar",
                            "flex-wrap: wrap",
                            "",
                            "Properti item:",
                            "flex: 1 (isi sisa ruang)",
                            "align-self, order"], PRIMARY))

    slide_code(prs, "Pola Flexbox Sehari-hari",
               "Navbar, centering sempurna, dan kolom fleksibel",
               '/* 1. Navbar: logo kiri, menu kanan */\n'
               '.navbar {\n'
               '  display: flex;\n'
               '  justify-content: space-between;\n'
               '  align-items: center;\n'
               '  gap: 16px;\n'
               '}\n'
               '\n'
               '/* 2. Centering sempurna */\n'
               '.hero {\n'
               '  display: flex;\n'
               '  justify-content: center; /* horizontal */\n'
               '  align-items: center;     /* vertikal  */\n'
               '  min-height: 100vh;\n'
               '}\n'
               '\n'
               '/* 3. Sidebar tetap + konten mengisi */\n'
               '.layout { display: flex; }\n'
               '.sidebar { flex: 0 0 240px; }\n'
               '.konten  { flex: 1; }',
               accent=PRIMARY, font_size=9.5,
               right_cards=[("flex: 1 artinya",
                             ["flex-grow:1 flex-shrink:1",
                              "flex-basis:0 → item berbagi",
                              "sisa ruang secara merata"], PRIMARY),
                            ("gap > margin",
                             ["• gap memberi jarak antar item",
                              "  tanpa margin di tepi luar",
                              "• Berlaku juga di grid"], EMERALD)])

    section_divider(prs, "02", "CSS Grid",
                    "Layout dua dimensi: baris DAN kolom sekaligus", color=EMERALD)

    slide_code(prs, "Grid: Kolom, fr, dan minmax",
               "fr = pecahan ruang tersisa; repeat + auto-fit = grid responsif tanpa media query",
               '/* 3 kolom sama lebar */\n'
               '.galeri {\n'
               '  display: grid;\n'
               '  grid-template-columns: repeat(3, 1fr);\n'
               '  gap: 20px;\n'
               '}\n'
               '\n'
               '/* Sidebar 240px + konten fleksibel */\n'
               '.app {\n'
               '  display: grid;\n'
               '  grid-template-columns: 240px 1fr;\n'
               '}\n'
               '\n'
               '/* RESPONSIF OTOMATIS: kolom menyesuaikan */\n'
               '.produk {\n'
               '  display: grid;\n'
               '  grid-template-columns:\n'
               '    repeat(auto-fit, minmax(250px, 1fr));\n'
               '  gap: 20px;\n'
               '}',
               accent=EMERALD, font_size=9.5,
               right_cards=[("Membaca minmax",
                             ["minmax(250px, 1fr):",
                              "• minimal 250px per kolom",
                              "• maksimal berbagi rata (1fr)",
                              "auto-fit: jumlah kolom otomatis",
                              "menyesuaikan lebar layar"], EMERALD),
                            ("Span & area",
                             ["grid-column: span 2;",
                              "grid-row: 1 / 3;",
                              "grid-template-areas: peta",
                              "layout bernama (header, main)"], AMBER)])

    slide_ascii(prs, "grid-template-areas — Layout Bernama",
                "Gambar layout langsung di CSS, lalu tempelkan nama ke elemen",
                '.halaman {\n'
                '  display: grid;\n'
                '  grid-template-columns: 240px 1fr;\n'
                '  grid-template-areas:\n'
                '    "header header"      ┌────────────────────┐\n'
                '    "sidebar konten"     │       header       │\n'
                '    "footer footer";     ├────────┬───────────┤\n'
                '}                        │sidebar │  konten   │\n'
                '.header  { grid-area:    │        │           │\n'
                '           header; }     ├────────┴───────────┤\n'
                '.sidebar { grid-area:    │       footer       │\n'
                '           sidebar; }    └────────────────────┘',
                caption="Nama area bebas — yang penting membentuk persegi panjang utuh.",
                accent=EMERALD)

    slide_compare(prs, "Flexbox vs Grid — Kapan Pakai yang Mana?",
                  "Keduanya saling melengkapi, bukan bersaing",
                  "FLEXBOX — 1 dimensi",
                  ["• Konten menentukan ukuran",
                   "• Baris ATAU kolom (satu arah)",
                   "• Navbar, deret tombol, card row",
                   "• Distribusi ruang antar item",
                   "• align-self per item mudah"],
                  "GRID — 2 dimensi",
                  ["• Layout menentukan ukuran",
                   "• Baris DAN kolom bersamaan",
                   "• Kerangka halaman, galeri foto",
                   "• Penempatan presisi (area/span)",
                   "• auto-fit + minmax = responsif"],
                  lc=PRIMARY, rc=EMERALD,
                  bottom=("Praktik umum: GRID untuk kerangka halaman, FLEXBOX untuk isi tiap bagian.", AMBER))

    section_divider(prs, "03", "Media Query & Mobile-First",
                    "Satu HTML, gaya berbeda per ukuran layar", color=AMBER)

    slide_code(prs, "Mobile-First dengan min-width",
               "Gaya dasar = HP. Tambah aturan saat layar MEMBESAR.",
               '/* Dasar (mobile): 1 kolom */\n'
               '.galeri {\n'
               '  display: grid;\n'
               '  grid-template-columns: 1fr;\n'
               '  gap: 16px;\n'
               '}\n'
               '\n'
               '/* Tablet ke atas: 2 kolom */\n'
               '@media (min-width: 640px) {\n'
               '  .galeri {\n'
               '    grid-template-columns: repeat(2, 1fr);\n'
               '  }\n'
               '}\n'
               '\n'
               '/* Desktop: 3 kolom */\n'
               '@media (min-width: 1024px) {\n'
               '  .galeri {\n'
               '    grid-template-columns: repeat(3, 1fr);\n'
               '  }\n'
               '}',
               accent=AMBER, font_size=9.5,
               right_cards=[("Kenapa mobile-first?",
                             ["• Mayoritas pengunjung dari HP",
                              "• Gaya dasar sederhana, override",
                              "  makin sedikit",
                              "• min-width menumpuk rapi",
                              "  ke atas (640 → 1024)"], AMBER),
                            ("Wajib di <head>",
                             ["<meta name=\"viewport\"",
                              " content=\"width=device-width,",
                              " initial-scale=1.0\">",
                              "Tanpa ini media query kacau",
                              "di perangkat mobile!"], ROSE)])

    slide_table(prs, "Breakpoint Umum", "Selaras dengan default Tailwind (Modul 04)",
                ["Breakpoint", "min-width", "Target umum"],
                [["(dasar)", "—", "HP portrait — gaya default tanpa media query"],
                 ["sm", "640px", "HP landscape / phablet"],
                 ["md", "768px", "Tablet portrait"],
                 ["lg", "1024px", "Tablet landscape / laptop"],
                 ["xl", "1280px", "Desktop"],
                 ["2xl", "1536px", "Layar lebar"]],
                [2.4, 2.4, 7.5],
                header_colors=[PRIMARY, AMBER, EMERALD])

    slide_mistakes(prs, "Kesalahan Umum Layout — Hindari Ini!", [
        ("1. Lupa viewport meta",
         "Media query tidak jalan di HP.\nSelalu cek <meta name=\"viewport\"> ada.",
         ROSE),
        ("2. Width tetap (fixed px)",
         "width: 900px meledak di layar kecil.\nGunakan max-width + width: 100%.",
         ROSE),
        ("3. justify vs align tertukar",
         "justify = main axis, align = cross.\nflex-direction: column MENUKAR sumbu!",
         AMBER),
        ("4. Desktop-first campur aduk",
         "max-width dan min-width dicampur\nbikin konflik. Pilih mobile-first konsisten.",
         AMBER),
        ("5. Margin manual antar kolom",
         "margin-right per item rapuh.\nPakai gap pada flex/grid container.",
         VIOLET),
        ("6. Overflow horizontal",
         "Gambar/teks lebar bocor keluar.\nimg { max-width: 100%; } + minmax(0, 1fr).",
         VIOLET),
    ])

    slide_twocode(prs, "Cheatsheet Layout Responsif", None,
                  '/* FLEXBOX */\n'
                  '.row {\n'
                  '  display: flex;\n'
                  '  justify-content: space-between;\n'
                  '  align-items: center;\n'
                  '  gap: 16px;\n'
                  '  flex-wrap: wrap;\n'
                  '}\n'
                  '.item-isi-sisa { flex: 1; }\n'
                  '\n'
                  '/* CENTERING */\n'
                  '.center { display: flex;\n'
                  '  justify-content: center;\n'
                  '  align-items: center; }',
                  '/* GRID */\n'
                  '.grid {\n'
                  '  display: grid;\n'
                  '  grid-template-columns:\n'
                  '    repeat(auto-fit,\n'
                  '           minmax(250px, 1fr));\n'
                  '  gap: 20px;\n'
                  '}\n'
                  '\n'
                  '/* MEDIA QUERY (mobile-first) */\n'
                  '@media (min-width: 640px) { ... }\n'
                  '@media (min-width: 1024px){ ... }\n'
                  '\n'
                  'img { max-width: 100%; }',
                  accent_l=PRIMARY, accent_r=EMERALD,
                  caption=("Latihan: 1-pembelajaran/03-layout-responsive (flexbox, grid, layout responsif)", AMBER))

    web_closing(prs, "03", "Layout Responsif — flexbox, grid, media query", [
        (PRIMARY, "Flexbox",
         "1 dimensi. justify = main axis, align = cross axis. gap untuk jarak, flex:1 mengisi sisa."),
        (EMERALD, "Grid",
         "2 dimensi. fr berbagi ruang, repeat(auto-fit, minmax(250px,1fr)) = responsif otomatis."),
        (AMBER, "Media Query",
         "Mobile-first: gaya dasar untuk HP, @media (min-width: ...) menambah saat layar besar."),
        (VIOLET, "Strategi",
         "Grid untuk kerangka halaman, flexbox untuk isi bagian. max-width mencegah overflow."),
        (ROSE, "Pitfall",
         "Lupa viewport meta, fixed width, sumbu tertukar saat column, campur min/max-width."),
    ])


# ═══════════════════════════════════════════════════════════════════
# MODUL 04 — Tailwind CSS
# ═══════════════════════════════════════════════════════════════════

def build_04(prs):
    C = CYAN
    web_cover(prs, 4, "Tailwind CSS",
              ["Utility-first: styling langsung di HTML",
               "Skala konsisten · responsive prefix · state variant"],
              color=C, pills=["utility", "responsive", "state", "komponen"])

    agenda_slide(prs, "Agenda — Modul 04: Tailwind CSS", [
        ("01", "Utility-\nFirst", PRIMARY,
         ["Filosofi", "vs CSS manual", "Setup CDN", "Skala desain"]),
        ("02", "Utility\nInti", EMERALD,
         ["Spacing p-/m-", "Warna & teks", "Flex & grid", "Border/shadow"]),
        ("03", "Responsive\n& State", AMBER,
         ["sm: md: lg:", "hover: focus:", "Mobile-first", "dark:"]),
        ("04", "Praktik\nBaik", VIOLET,
         ["Urutan class", "Ekstraksi komponen", "Anti-pattern", "CDN vs build"]),
    ])

    section_divider(prs, "01", "Filosofi Utility-First",
                    "Class kecil satu-tugas dirangkai menjadi desain lengkap", color=C)

    slide_twocode(prs, "CSS Manual vs Tailwind",
                  "Hasil visual sama — bedanya di mana gaya ditulis",
                  '<!-- CSS tradisional -->\n'
                  '<div class="kartu">\n'
                  '  <h2 class="kartu-judul">Halo</h2>\n'
                  '</div>\n'
                  '\n'
                  '<style>\n'
                  '.kartu {\n'
                  '  background: white;\n'
                  '  padding: 24px;\n'
                  '  border-radius: 12px;\n'
                  '  box-shadow: 0 1px 3px\n'
                  '    rgba(0,0,0,0.1);\n'
                  '}\n'
                  '.kartu-judul {\n'
                  '  font-size: 1.25rem;\n'
                  '  font-weight: 700;\n'
                  '}\n'
                  '</style>',
                  '<!-- Tailwind: utility di class -->\n'
                  '<div class="bg-white p-6\n'
                  '            rounded-xl shadow">\n'
                  '  <h2 class="text-xl font-bold">\n'
                  '    Halo\n'
                  '  </h2>\n'
                  '</div>\n'
                  '\n'
                  '<!-- Setup CDN (untuk belajar):-->\n'
                  '<script src=\n'
                  ' "https://cdn.tailwindcss.com">\n'
                  '</script>\n'
                  '\n'
                  '<!-- Proyek nyata: build via  -->\n'
                  '<!-- PostCSS/CLI (Modul 07-08)-->',
                  accent_l=ROSE, accent_r=EMERALD, font_size=9.5,
                  label_l="Cara lama: pindah-pindah file", label_r="Tailwind: satu tempat",
                  caption=("Tidak perlu mengarang nama class · skala desain konsisten · tidak ada CSS mati", CYAN))

    slide_cards(prs, "Mengapa Utility-First?",
                "Trade-off yang disengaja: HTML ramai, tetapi cepat dan konsisten",
                [("Keuntungan",
                  ["• Tidak mengarang nama class (.kartu-v2-final)",
                   "• Skala terbatas → desain otomatis konsisten",
                   "• Hapus HTML = hapus stylenya (tak ada CSS mati)",
                   "• Prototyping sangat cepat",
                   "• Responsive & state tinggal prefix"], EMERALD),
                 ("Keberatan umum + jawabannya",
                  ["• \"HTML jadi panjang\" → benar, tapi lokal",
                   "  dan mudah dilacak",
                   "• \"Sama dengan inline style?\" → BUKAN:",
                   "  punya hover:, md:, skala, dan tema",
                   "• Duplikasi class → ekstrak jadi komponen",
                   "  (React, Modul 06)"], AMBER)])

    section_divider(prs, "02", "Utility Inti",
                    "Spacing, tipografi, warna, layout — hafalkan polanya", color=EMERALD)

    slide_table(prs, "Skala Spacing & Ukuran", "Angka = kelipatan 0.25rem (4px): p-4 = 1rem = 16px",
                ["Utility", "CSS yang dihasilkan", "Arti"],
                [["p-4 / px-6 / pt-2", "padding: 1rem; ...", "Padding semua/horizontal/atas"],
                 ["m-4 / mx-auto", "margin: 1rem; auto", "Margin; mx-auto = tengah"],
                 ["gap-4", "gap: 1rem", "Jarak item flex/grid"],
                 ["w-64 / w-full", "width: 16rem / 100%", "Lebar"],
                 ["max-w-md", "max-width: 28rem", "Batas lebar konten"],
                 ["text-sm/base/xl/2xl", "font-size: ...", "Skala ukuran teks"],
                 ["font-bold / font-medium", "font-weight: 700/500", "Ketebalan"],
                 ["rounded-lg / shadow-md", "border-radius/box-shadow", "Sudut & bayangan"]],
                [3.3, 4.3, 4.7],
                header_colors=[PRIMARY, EMERALD, AMBER], body_size=9.5)

    slide_code(prs, "Warna dan Layout",
               "Pola warna: {properti}-{warna}-{intensitas 50–950}",
               '<!-- Warna: bg-, text-, border- -->\n'
               '<div class="bg-sky-600 text-white\n'
               '            border border-sky-700">\n'
               '\n'
               '<!-- Flexbox -->\n'
               '<nav class="flex items-center\n'
               '            justify-between gap-4">\n'
               '\n'
               '<!-- Grid responsif -->\n'
               '<div class="grid grid-cols-1\n'
               '            md:grid-cols-3 gap-6">\n'
               '\n'
               '<!-- Kartu lengkap -->\n'
               '<article class="max-w-sm rounded-xl\n'
               '  bg-white p-6 shadow-md\n'
               '  hover:shadow-lg transition">\n'
               '  <h2 class="text-xl font-bold\n'
               '             text-slate-900">Judul</h2>\n'
               '  <p class="mt-2 text-slate-600">...</p>\n'
               '</article>',
               accent=EMERALD, font_size=9.5,
               right_cards=[("Intensitas warna",
                             ["• 50 = paling terang",
                              "• 500-600 = warna utama",
                              "• 900 = paling gelap",
                              "• slate/gray utk netral",
                              "• sky/blue/emerald dll."], EMERALD),
                            ("Persis seperti CSS-nya",
                             ["flex = display:flex",
                              "items-center = align-items",
                              "justify-between = justify-",
                              "content:space-between",
                              "Modul 03 tetap wajib paham!"], PRIMARY)])

    section_divider(prs, "03", "Responsive & State",
                    "Prefix mengubah SEMUA utility jadi kondisional", color=AMBER)

    slide_code(prs, "Prefix Responsive dan State",
               "Tanpa prefix = mobile. sm:/md:/lg: aktif saat layar ≥ breakpoint.",
               '<!-- 1 kolom di HP, 2 tablet, 3 desktop -->\n'
               '<div class="grid grid-cols-1\n'
               '            sm:grid-cols-2\n'
               '            lg:grid-cols-3 gap-6">\n'
               '\n'
               '<!-- Sembunyikan menu di HP -->\n'
               '<nav class="hidden md:flex gap-6">\n'
               '\n'
               '<!-- Tombol dengan state -->\n'
               '<button class="bg-sky-600 text-white\n'
               '  px-4 py-2 rounded-lg\n'
               '  hover:bg-sky-700\n'
               '  focus-visible:ring-2\n'
               '  focus-visible:ring-sky-400\n'
               '  disabled:opacity-50\n'
               '  transition">\n'
               '  Simpan\n'
               '</button>\n'
               '\n'
               '<!-- Dark mode -->\n'
               '<div class="bg-white dark:bg-slate-900">',
               accent=AMBER, font_size=9.5,
               right_cards=[("Mobile-first!",
                             ["grid-cols-1 = default (HP)",
                              "md:grid-cols-3 = ≥768px",
                              "Prefix = min-width, sama",
                              "persis media query Modul 03"], AMBER),
                            ("State variant",
                             ["hover: focus: active:",
                              "disabled: checked:",
                              "group-hover: (ikuti parent)",
                              "dark: (mode gelap)"], VIOLET)])

    slide_compare(prs, "Tailwind CDN vs Build Process",
                  "CDN untuk belajar & prototipe; build untuk produksi",
                  "CDN (praktikum kita)",
                  ["• 1 baris <script> langsung jalan",
                   "• Tidak perlu Node.js/npm",
                   "• Semua utility tersedia (berat)",
                   "• Konfigurasi terbatas",
                   "• JANGAN untuk produksi"],
                  "Build (Next.js, Modul 07-08)",
                  ["• Instal via npm + PostCSS",
                   "• Hasil CSS berisi HANYA class terpakai",
                   "  (bisa < 10 KB!)",
                   "• Konfigurasi tema penuh",
                   "• Standar industri"],
                  lc=AMBER, rc=EMERALD,
                  bottom=("Di studi kasus dashboard kita pakai CDN; di proyek Next.js pakai build.", CYAN))

    slide_mistakes(prs, "Kesalahan Umum Tailwind — Hindari Ini!", [
        ("1. Class dinamis dirakit",
         "bg-{warna}-500 (template string) tak\nterdeteksi build. Tulis nama class UTUH.",
         ROSE),
        ("2. Lupa prefix = mobile",
         "md:flex tanpa flex dasar = elemen\nhilang di HP. Selalu pikirkan default-nya.",
         ROSE),
        ("3. Nilai arbitrer berlebihan",
         "w-[137px] mt-[13px] di mana-mana =\nkehilangan konsistensi skala. Pakai skala.",
         AMBER),
        ("4. Menyalin class panjang",
         "Kartu sama di 10 tempat? Ekstrak jadi\nkomponen (React) — bukan copy-paste.",
         AMBER),
        ("5. Tak paham CSS-nya",
         "items-center gagal? Kamu harus tetap\npaham flexbox! Tailwind ≠ pengganti CSS.",
         VIOLET),
        ("6. CDN di produksi",
         "Lambat + tak stabil versi. Produksi\nselalu pakai build process.",
         VIOLET),
    ])

    slide_twocode(prs, "Cheatsheet Tailwind", None,
                  '<!-- Layout -->\n'
                  'flex items-center justify-between\n'
                  'grid grid-cols-3 gap-6\n'
                  'hidden md:block\n'
                  'max-w-4xl mx-auto px-4\n'
                  '\n'
                  '<!-- Spacing (x4px) -->\n'
                  'p-4 px-6 py-2 mt-8 mb-4 gap-4\n'
                  '\n'
                  '<!-- Teks -->\n'
                  'text-sm text-xl text-3xl\n'
                  'font-medium font-bold\n'
                  'text-slate-600 text-center',
                  '<!-- Dekorasi -->\n'
                  'bg-white bg-sky-600\n'
                  'rounded-lg rounded-xl\n'
                  'border border-slate-200\n'
                  'shadow-md shadow-lg\n'
                  '\n'
                  '<!-- Responsive -->\n'
                  'sm:640 md:768 lg:1024 xl:1280\n'
                  'grid-cols-1 md:grid-cols-3\n'
                  '\n'
                  '<!-- State -->\n'
                  'hover:bg-sky-700 transition\n'
                  'focus-visible:ring-2\n'
                  'disabled:opacity-50 dark:bg-slate-900',
                  accent_l=CYAN, accent_r=AMBER,
                  caption=("Latihan: 1-pembelajaran/04-tailwind-css (3 bab: utility, kartu, state)", EMERALD))

    web_closing(prs, "04", "Tailwind — utility-first CSS", [
        (CYAN, "Filosofi",
         "Class kecil satu-tugas dirangkai di HTML. Tidak mengarang nama, skala konsisten."),
        (EMERALD, "Utility Inti",
         "p-4/m-4 (x4px), text-xl, font-bold, bg-sky-600, flex/grid, rounded, shadow."),
        (AMBER, "Responsive",
         "Tanpa prefix = mobile. sm:/md:/lg: = min-width. Persis media query Modul 03."),
        (VIOLET, "State",
         "hover:, focus-visible:, disabled:, dark: — interaksi tanpa menulis CSS terpisah."),
        (ROSE, "Pitfall",
         "Jangan rakit nama class dinamis, jangan CDN di produksi, tetap harus paham CSS."),
    ])


# ═══════════════════════════════════════════════════════════════════
# MODUL 05 — JavaScript & DOM
# ═══════════════════════════════════════════════════════════════════

def build_05(prs):
    C = AMBER
    web_cover(prs, 5, "JavaScript & DOM",
              ["Dasar bahasa · seleksi elemen · event",
               "Render list · validasi form — fondasi React"],
              color=C, pills=["syntax", "DOM", "event", "form"])

    agenda_slide(prs, "Agenda — Modul 05: JavaScript & DOM", [
        ("01", "Dasar\nJavaScript", PRIMARY,
         ["let/const", "Fungsi & arrow", "Array method", "Template literal"]),
        ("02", "DOM &\nSeleksi", EMERALD,
         ["DOM tree", "querySelector", "textContent", "classList"]),
        ("03", "Event", AMBER,
         ["addEventListener", "click & submit", "event object", "preventDefault"]),
        ("04", "Pola\nAplikasi", VIOLET,
         ["State → render", "Render list", "Validasi form", "Menuju React"]),
    ])

    section_divider(prs, "01", "Dasar JavaScript",
                    "Sintaks minimum untuk memanipulasi halaman", color=PRIMARY)

    slide_code(prs, "Variabel, Fungsi, Template Literal",
               "const sebagai default; let hanya jika nilainya diganti",
               'const nama = "Sinta";      // tak diganti\n'
               'let jumlahSesi = 0;        // akan berubah\n'
               '\n'
               '// Fungsi biasa vs arrow function\n'
               'function sapa(nama) {\n'
               '  return `Halo, ${nama}!`;\n'
               '}\n'
               'const tambah = (a, b) => a + b;\n'
               '\n'
               '// Template literal: string + variabel\n'
               'const pesan = `${nama} sudah belajar\n'
               '${jumlahSesi} sesi`;\n'
               '\n'
               '// Objek & destructuring\n'
               'const mhs = { nama: "Andi", ipk: 3.7 };\n'
               'const { ipk } = mhs;\n'
               'console.log(mhs.nama, ipk);',
               accent=PRIMARY, font_size=10,
               right_cards=[("var? Lupakan.",
                             ["• var = cara lama, scope aneh",
                              "• const = tidak bisa di-assign",
                              "  ulang (objeknya tetap mutable)",
                              "• let = bisa di-assign ulang"], PRIMARY),
                            ("Template literal",
                             ["• Backtick ` bukan kutip biasa",
                              "• ${ekspresi} disisipkan",
                              "• Bisa multi-baris",
                              "• Nanti mirip JSX di React"], AMBER)])

    slide_table(prs, "Array Method yang Wajib Hafal",
                "Trio map/filter/find adalah 80% pekerjaan data di web (dan inti React)",
                ["Method", "Hasil", "Contoh"],
                [["map(fn)", "Array baru, tiap item diubah", "harga.map(h => h * 1000)"],
                 ["filter(fn)", "Array baru, item lolos tes", "mhs.filter(m => m.ipk >= 3)"],
                 ["find(fn)", "SATU item pertama yang cocok", "produk.find(p => p.id === 2)"],
                 ["forEach(fn)", "Jalankan efek, tanpa hasil", "items.forEach(render)"],
                 ["reduce(fn, awal)", "Satu nilai akumulasi", "angka.reduce((a,b)=>a+b, 0)"],
                 ["some / every", "Boolean ada/semua cocok", "nilai.some(n => n < 60)"],
                 ["join(pemisah)", "String gabungan", "kelas.map(...).join(\"\")"]],
                [2.6, 4.2, 5.5],
                header_colors=[PRIMARY, EMERALD, AMBER], body_size=9.5)

    section_divider(prs, "02", "DOM — Document Object Model",
                    "HTML di-parse browser menjadi pohon objek yang bisa dimanipulasi",
                    color=EMERALD)

    slide_ascii(prs, "DOM Tree — HTML Menjadi Pohon",
                "JS tidak mengubah file .html — ia mengubah POHON di memori browser",
                'HTML:                          DOM tree:\n'
                '<body>                             body\n'
                '  <h1>Judul</h1>                  ╱    ╲\n'
                '  <ul id="daftar">              h1      ul#daftar\n'
                '    <li>Apel</li>              │       ╱      ╲\n'
                '    <li>Jeruk</li>          "Judul"  li        li\n'
                '  </ul>                              │         │\n'
                '</body>                           "Apel"    "Jeruk"\n'
                '\n'
                'document.querySelector("#daftar")  → node ul\n'
                'ul.children                        → [li, li]\n'
                'li.parentElement                   → ul',
                caption="Inspect Element di DevTools menampilkan DOM (hasil), bukan file sumber.",
                accent=EMERALD)

    slide_code(prs, "Seleksi dan Manipulasi Elemen",
               "querySelector menerima selector CSS apa pun",
               '// SELEKSI (pakai selector CSS!)\n'
               'const judul = document.querySelector("h1");\n'
               'const tombol = document.querySelector("#tambah");\n'
               'const items = document.querySelectorAll(".item");\n'
               '\n'
               '// UBAH KONTEN\n'
               'judul.textContent = "Skor: 5";  // teks aman\n'
               'kotak.innerHTML = "<b>HTML</b>"; // hati-hati\n'
               '\n'
               '// UBAH TAMPILAN via class\n'
               'kartu.classList.add("aktif");\n'
               'kartu.classList.remove("hidden");\n'
               'kartu.classList.toggle("terbuka");\n'
               '\n'
               '// BUAT ELEMEN BARU\n'
               'const li = document.createElement("li");\n'
               'li.textContent = "Item baru";\n'
               'daftar.append(li);',
               accent=EMERALD, font_size=9.5,
               right_cards=[("textContent vs innerHTML",
                             ["• textContent: teks murni, AMAN",
                              "• innerHTML: parse HTML —",
                              "  JANGAN isi input user mentah",
                              "  (celah XSS!)"], ROSE),
                            ("Gaya = ganti class",
                             ["• el.style.color = ... bisa,",
                              "  tapi CSS tercecer di JS",
                              "• Lebih rapi: definisikan class",
                              "  di CSS, JS tinggal toggle"], EMERALD)])

    section_divider(prs, "03", "Event — Merespons Aksi Pengguna",
                    "addEventListener: saat X terjadi, jalankan fungsi ini", color=AMBER)

    slide_code(prs, "Event Listener dan Form",
               "preventDefault menahan reload bawaan form — pola wajib validasi",
               'const tombol = document.querySelector("#plus");\n'
               'tombol.addEventListener("click", () => {\n'
               '  jumlah++;\n'
               '  render();\n'
               '});\n'
               '\n'
               '// Event form: submit, BUKAN click\n'
               'form.addEventListener("submit", (event) => {\n'
               '  event.preventDefault(); // tahan reload\n'
               '\n'
               '  const nama = inputNama.value.trim();\n'
               '  if (nama === "") {\n'
               '    pesanError.textContent =\n'
               '      "Nama wajib diisi";\n'
               '    return;\n'
               '  }\n'
               '  // ... proses data valid\n'
               '});\n'
               '\n'
               '// Event input: setiap ketikan\n'
               'inputCari.addEventListener("input", render);',
               accent=AMBER, font_size=9.5,
               right_cards=[("Event object",
                             ["• Parameter pertama callback",
                              "• event.target = elemen sumber",
                              "• event.preventDefault() =",
                              "  batalkan aksi bawaan browser"], AMBER),
                            ("Event umum",
                             ["click, submit, input, change,",
                              "keydown, focus, blur,",
                              "DOMContentLoaded"], PRIMARY)])

    slide_code(prs, "Pola Emas: State → Render",
               "Satu sumber data (state), satu fungsi gambar ulang (render) — ini DNA React!",
               'let daftarTugas = [];        // STATE\n'
               '\n'
               'function render() {          // RENDER\n'
               '  ul.innerHTML = daftarTugas\n'
               '    .map(t => `<li>${t}</li>`)\n'
               '    .join("");\n'
               '  info.textContent =\n'
               '    `${daftarTugas.length} tugas`;\n'
               '}\n'
               '\n'
               'form.addEventListener("submit", (e) => {\n'
               '  e.preventDefault();        // EVENT:\n'
               '  daftarTugas.push(input.value);\n'
               '  input.value = "";          // ubah state\n'
               '  render();                  // gambar ulang\n'
               '});\n'
               '\n'
               'render();  // gambar pertama kali',
               accent=VIOLET, font_size=9.5,
               right_cards=[("Alurnya selalu",
                             ["1. Event terjadi (klik/submit)",
                              "2. Ubah STATE (data)",
                              "3. Panggil render()",
                              "UI = f(state) — di React,",
                              "langkah 3 jadi otomatis!"], VIOLET),
                            ("Kenapa bukan edit DOM\nsatu-satu?",
                             ["• Sinkronisasi manual rawan bug",
                              "• Render ulang dari data =",
                              "  UI selalu konsisten"], EMERALD)])

    slide_mistakes(prs, "Kesalahan Umum JavaScript/DOM — Hindari Ini!", [
        ("1. Script sebelum elemen",
         "querySelector null karena HTML belum\ndi-parse. Taruh <script> di akhir body atau defer.",
         ROSE),
        ("2. innerHTML + input user",
         "Celah XSS! Input pengguna masuk lewat\ntextContent, bukan innerHTML.",
         ROSE),
        ("3. == bukan ===",
         "\"5\" == 5 true (coercion aneh).\nSelalu pakai === dan !==.",
         AMBER),
        ("4. Lupa preventDefault",
         "Form reload halaman, state hilang.\nevent.preventDefault() di handler submit.",
         AMBER),
        ("5. Ubah DOM tanpa state",
         "Data tercecer di DOM sulit dilacak.\nState di variabel, DOM hasil render.",
         VIOLET),
        ("6. .value selalu string",
         "input.value \"5\" + 1 = \"51\"!\nKonversi dengan Number() dulu.",
         VIOLET),
    ])

    slide_twocode(prs, "Cheatsheet JavaScript & DOM", None,
                  '// Data\n'
                  'const x = ...; let y = ...;\n'
                  'const f = (a, b) => a + b;\n'
                  '`Halo ${nama}`  // template literal\n'
                  '\n'
                  '// Array\n'
                  'arr.map(x => ...)     // ubah\n'
                  'arr.filter(x => ...)  // saring\n'
                  'arr.find(x => ...)    // cari 1\n'
                  'arr.reduce((a,b)=>a+b, 0)\n'
                  '\n'
                  '// Seleksi\n'
                  'document.querySelector("#id")\n'
                  'document.querySelectorAll(".cls")',
                  '// Manipulasi\n'
                  'el.textContent = "aman";\n'
                  'el.classList.add/remove/toggle\n'
                  'el.append(childEl)\n'
                  '\n'
                  '// Event\n'
                  'el.addEventListener("click", fn)\n'
                  'form.addEventListener("submit",\n'
                  '  e => { e.preventDefault(); ... })\n'
                  '\n'
                  '// Pola state → render\n'
                  'let state = [...];\n'
                  'function render() { ...dari state }\n'
                  '// event: ubah state; render();',
                  accent_l=PRIMARY, accent_r=AMBER,
                  caption=("Latihan: 1-pembelajaran/05-javascript-dom (counter, validasi, daftar dinamis)", EMERALD))

    web_closing(prs, "05", "JavaScript & DOM — halaman menjadi hidup", [
        (PRIMARY, "Bahasa",
         "const/let, arrow function, template literal, destructuring. Selalu ===, bukan ==."),
        (EMERALD, "DOM",
         "querySelector (selector CSS), textContent, classList, createElement + append."),
        (AMBER, "Event",
         "addEventListener; submit + preventDefault untuk form; input.value selalu string."),
        (VIOLET, "Pola",
         "State di variabel → render() menggambar ulang UI dari state. Ini fondasi React."),
        (ROSE, "Keamanan",
         "Jangan masukkan input user ke innerHTML (XSS). Script di akhir body / defer."),
    ])


# ═══════════════════════════════════════════════════════════════════
# MODUL 06 — React: Komponen, Props, State
# ═══════════════════════════════════════════════════════════════════

def build_06(prs):
    C = CYAN
    web_cover(prs, 6, "React — Komponen",
              ["Komponen · JSX · props · state",
               "UI = f(state): render otomatis dari data"],
              color=C, pills=["JSX", "props", "state", "list"])

    agenda_slide(prs, "Agenda — Modul 06: React", [
        ("01", "Komponen\n& JSX", PRIMARY,
         ["Fungsi → UI", "Aturan JSX", "Component tree", "Komposisi"]),
        ("02", "Props", EMERALD,
         ["Data parent→anak", "Destructuring", "children", "Read-only!"]),
        ("03", "State &\nEvent", AMBER,
         ["useState", "setState → render", "onClick/onChange", "Controlled form"]),
        ("04", "List &\nPola", VIOLET,
         ["map + key", "Lifting state up", "Conditional render", "Menuju Next.js"]),
    ])

    section_divider(prs, "01", "Komponen & JSX",
                    "Komponen = fungsi JavaScript yang mengembalikan UI", color=PRIMARY)

    slide_ascii(prs, "Component Tree — UI Disusun dari Komponen",
                "Setiap kotak = satu fungsi. Data mengalir dari atas ke bawah.",
                '                    <App />\n'
                '                   ╱   │   ╲\n'
                '          <Header/> <Dashboard/> <Footer/>\n'
                '                    ╱         ╲\n'
                '            <StatCard          <StatCard\n'
                '              judul="Sesi"       judul="Nilai"\n'
                '              nilai={12} />      nilai={88} />\n'
                '\n'
                '  • Komponen dipakai ulang dengan PROPS berbeda\n'
                '  • Nama komponen WAJIB huruf besar (<StatCard/>)\n'
                '  • Satu komponen = satu tanggung jawab',
                caption="Bandingkan dengan praktikum: 1-pembelajaran/06-react-komponen/01-dashboard-komponen",
                accent=PRIMARY,
                side_card=("JSX ≠ HTML",
                           ["• class → className",
                            "• for → htmlFor",
                            "• {ekspresi} JS di kurung",
                            "  kurawal",
                            "• Wajib SATU elemen induk",
                            "  (atau fragment <>...</>)",
                            "• Tag selalu ditutup:",
                            "  <img />, <input />"], AMBER))

    slide_code(prs, "Komponen + Props",
               "Props = parameter fungsi. Parent mengirim, anak menerima (read-only).",
               'function StatCard({ judul, nilai, satuan }) {\n'
               '  return (\n'
               '    <article className="kartu">\n'
               '      <h2>{judul}</h2>\n'
               '      <p>\n'
               '        {nilai} <span>{satuan}</span>\n'
               '      </p>\n'
               '    </article>\n'
               '  );\n'
               '}\n'
               '\n'
               'function Dashboard() {\n'
               '  return (\n'
               '    <main>\n'
               '      <StatCard judul="Sesi Belajar"\n'
               '                nilai={12} satuan="sesi" />\n'
               '      <StatCard judul="Rata-rata"\n'
               '                nilai={88} satuan="poin" />\n'
               '    </main>\n'
               '  );\n'
               '}',
               accent=PRIMARY, font_size=9.5,
               right_cards=[("Aturan props",
                             ["• String: judul=\"Sesi\"",
                              "• Angka/ekspresi: nilai={12}",
                              "• props READ-ONLY —",
                              "  anak tak boleh mengubahnya",
                              "• children = isi di antara tag"], EMERALD),
                            ("Mengapa komponen?",
                             ["• Reuse: 1 definisi, N pemakaian",
                              "• Ubah sekali, semua ikut",
                              "• Tree mudah dinalar"], PRIMARY)])

    section_divider(prs, "02", "State — Data yang Berubah",
                    "useState: saat state berubah, React render ulang otomatis", color=AMBER)

    slide_code(prs, "useState: Counter",
               "setJumlah memicu render ulang — jangan ubah variabel langsung!",
               'import { useState } from "react";\n'
               '\n'
               'function Counter() {\n'
               '  const [jumlah, setJumlah] = useState(0);\n'
               '\n'
               '  return (\n'
               '    <div>\n'
               '      <p>Sesi: {jumlah}</p>\n'
               '      <button onClick={() =>\n'
               '        setJumlah(jumlah + 1)}>\n'
               '        Tambah\n'
               '      </button>\n'
               '      <button onClick={() => setJumlah(0)}>\n'
               '        Reset\n'
               '      </button>\n'
               '    </div>\n'
               '  );\n'
               '}',
               accent=AMBER, font_size=10,
               right_cards=[("Anatomi useState",
                             ["const [nilai, setNilai] =",
                              "      useState(nilaiAwal);",
                              "• nilai: state sekarang",
                              "• setNilai: minta ganti +",
                              "  render ulang komponen"], AMBER),
                            ("Aturan penting",
                             ["• jumlah++ ✗ (React tak tahu)",
                              "• setJumlah(jumlah+1) ✓",
                              "• State array/objek: buat",
                              "  SALINAN baru ([...arr, x])",
                              "• Hook dipanggil di level atas"], ROSE)])

    slide_code(prs, "Controlled Form",
               "Nilai input dikendalikan state — satu sumber kebenaran",
               'function FormPendaftaran() {\n'
               '  const [nama, setNama] = useState("");\n'
               '  const [error, setError] = useState("");\n'
               '\n'
               '  function handleSubmit(e) {\n'
               '    e.preventDefault();\n'
               '    if (nama.trim() === "") {\n'
               '      setError("Nama wajib diisi");\n'
               '      return;\n'
               '    }\n'
               '    setError("");\n'
               '    // ... kirim data\n'
               '  }\n'
               '\n'
               '  return (\n'
               '    <form onSubmit={handleSubmit}>\n'
               '      <input value={nama}\n'
               '        onChange={(e) =>\n'
               '          setNama(e.target.value)} />\n'
               '      {error && <p role="alert">{error}</p>}\n'
               '      <button>Daftar</button>\n'
               '    </form>\n'
               '  );\n'
               '}',
               accent=EMERALD, font_size=9,
               right_cards=[("Pola controlled",
                             ["value={state}",
                              "onChange={e =>",
                              "  setState(e.target.value)}",
                              "→ UI dan data selalu sinkron",
                              "→ validasi real-time mudah"], EMERALD),
                            ("Conditional render",
                             ["{error && <p>...</p>}",
                              "{aktif ? <A/> : <B/>}",
                              "Render sesuai state"], VIOLET)])

    section_divider(prs, "03", "List, Key, dan Aliran Data",
                    "map menggambar array; key membantu React melacak item", color=VIOLET)

    slide_code(prs, "Render List dengan map + key",
               "key unik & stabil (id), BUKAN index array",
               'const produk = [\n'
               '  { id: 1, nama: "Kopi", harga: 15000 },\n'
               '  { id: 2, nama: "Teh",  harga: 10000 },\n'
               '];\n'
               '\n'
               'function DaftarProduk({ items }) {\n'
               '  return (\n'
               '    <ul>\n'
               '      {items.map((p) => (\n'
               '        <li key={p.id}>\n'
               '          {p.nama} —\n'
               '          Rp{p.harga.toLocaleString("id")}\n'
               '        </li>\n'
               '      ))}\n'
               '    </ul>\n'
               '  );\n'
               '}\n'
               '\n'
               '// Filter sebelum map:\n'
               '{items\n'
               '  .filter(p => p.harga <= budget)\n'
               '  .map(p => <li key={p.id}>...</li>)}',
               accent=VIOLET, font_size=9.5,
               right_cards=[("Kenapa key?",
                             ["• React mencocokkan item lama",
                              "  vs baru saat re-render",
                              "• index sebagai key bermasalah",
                              "  saat urutan berubah/dihapus"], VIOLET),
                            ("Lifting state up",
                             ["• State filter di PARENT,",
                              "  dikirim sebagai props",
                              "• Dua komponen berbagi data?",
                              "  Naikkan state ke induk terdekat"], AMBER)])

    slide_ascii(prs, "Aliran Data React — Satu Arah",
                "Data turun lewat props; kejadian naik lewat callback",
                '            state: [query, setQuery]\n'
                '                 ┌──────────┐\n'
                '                 │  <App/>  │\n'
                '                 └──────────┘\n'
                '        props ↓ query     ↑ onChange(q)\n'
                '     ┌──────────────┐  ┌───────────────┐\n'
                '     │ <DaftarItem  │  │ <SearchBox    │\n'
                '     │   query={q}/>│  │  onChange={f}/>│\n'
                '     └──────────────┘  └───────────────┘\n'
                '\n'
                '  1. User mengetik di SearchBox\n'
                '  2. SearchBox memanggil props.onChange(teks)\n'
                '  3. App setQuery(teks) → state berubah\n'
                '  4. React render ulang → DaftarItem menerima query baru',
                caption="\"Data down, events up\" — hafalkan kalimat ini untuk ujian.",
                accent=CYAN)

    slide_table(prs, "Hook React Penting", "useState dan useEffect menutupi mayoritas kebutuhan awal",
                ["Hook", "Kegunaan", "Contoh"],
                [["useState", "Data lokal yang berubah", "const [x, setX] = useState(0)"],
                 ["useEffect", "Efek samping (fetch, timer)", "useEffect(() => {...}, [dep])"],
                 ["useRef", "Referensi DOM / nilai persist", "const inputRef = useRef(null)"],
                 ["useContext", "Data global tanpa props drilling", "useContext(TemaContext)"],
                 ["useMemo", "Cache perhitungan berat", "useMemo(() => hitung(), [data])"]],
                [2.4, 4.4, 5.5],
                header_colors=[PRIMARY, EMERALD, AMBER], body_size=9.5)

    slide_mistakes(prs, "Kesalahan Umum React — Hindari Ini!", [
        ("1. Mengubah state langsung",
         "jumlah++ atau arr.push(x) tak memicu\nrender. Selalu lewat setState + salinan baru.",
         ROSE),
        ("2. onClick={fn()} dipanggil",
         "fn() langsung jalan saat render!\nBerikan referensi: onClick={fn} atau () => fn(x).",
         ROSE),
        ("3. key={index}",
         "Urutan berubah → item salah pasang.\nGunakan id unik yang stabil.",
         AMBER),
        ("4. Hook dalam if/loop",
         "Urutan hook harus tetap tiap render.\nPanggil di level atas komponen saja.",
         AMBER),
        ("5. Lupa className",
         "class adalah kata kunci JS.\nJSX memakai className (dan htmlFor).",
         VIOLET),
        ("6. Props diubah anak",
         "Props read-only! Butuh mengubah?\nKirim callback dari parent (events up).",
         VIOLET),
    ])

    slide_twocode(prs, "Cheatsheet React", None,
                  '// Komponen + props\n'
                  'function Kartu({ judul, children }) {\n'
                  '  return (\n'
                  '    <div className="kartu">\n'
                  '      <h2>{judul}</h2>\n'
                  '      {children}\n'
                  '    </div>\n'
                  '  );\n'
                  '}\n'
                  '\n'
                  '// State\n'
                  'const [x, setX] = useState(0);\n'
                  'setX(x + 1);           // re-render\n'
                  'setArr([...arr, baru]); // salinan!',
                  '// Event\n'
                  '<button onClick={handleClick}>\n'
                  '<input value={v} onChange={e =>\n'
                  '  setV(e.target.value)} />\n'
                  '<form onSubmit={e => {\n'
                  '  e.preventDefault(); ... }}>\n'
                  '\n'
                  '// List & kondisi\n'
                  '{items.map(i =>\n'
                  '  <li key={i.id}>{i.nama}</li>)}\n'
                  '{error && <p>{error}</p>}\n'
                  '{on ? <A/> : <B/>}\n'
                  '\n'
                  '// JSX: className, htmlFor, <img />',
                  accent_l=CYAN, accent_r=AMBER,
                  caption=("Latihan: 1-pembelajaran/06-react-komponen (dashboard, form controlled, filter)", EMERALD))

    web_closing(prs, "06", "React — komponen, props, state", [
        (PRIMARY, "Komponen",
         "Fungsi ber-huruf besar yang mengembalikan JSX. Satu tanggung jawab, bisa dipakai ulang."),
        (EMERALD, "Props",
         "Data parent → anak, read-only. children untuk isi di antara tag."),
        (AMBER, "State",
         "useState; setState memicu render ulang. Array/objek selalu buat salinan baru."),
        (VIOLET, "Pola",
         "map + key untuk list, controlled form, lifting state up, data down — events up."),
        (ROSE, "Pitfall",
         "Jangan mutasi state, onClick={fn} bukan fn(), key bukan index, hook di level atas."),
    ])


# ═══════════════════════════════════════════════════════════════════
# MODUL 07 — Next.js App Router
# ═══════════════════════════════════════════════════════════════════

def build_07(prs):
    C = VIOLET
    web_cover(prs, 7, "Next.js App Router",
              ["File-based routing · layout · dynamic route",
               "Server vs Client Component"],
              color=C, pills=["routing", "layout", "server", "client"])

    agenda_slide(prs, "Agenda — Modul 07: Next.js App Router", [
        ("01", "Kenapa\nNext.js?", PRIMARY,
         ["React + rangka", "SSR vs CSR", "SEO & performa", "Struktur proyek"]),
        ("02", "File-based\nRouting", EMERALD,
         ["app/page.tsx", "layout.tsx", "Nested route", "<Link>"]),
        ("03", "Dynamic\nRoute", AMBER,
         ["[slug]", "params", "notFound()", "generateStaticParams"]),
        ("04", "Server vs\nClient", VIOLET,
         ["Default server", "\"use client\"", "Kapan client?", "Komposisi"]),
    ])

    section_divider(prs, "01", "Mengapa Next.js?",
                    "Next.js menambahkan routing, rendering server, dan tooling produksi pada React",
                    color=PRIMARY)

    slide_cards(prs, "React Client-only vs Next.js",
                "Arsitektur dan tooling menentukan HTML awal serta cara navigasi",
                [("React client-only",
                  ["• HTML awal nyaris kosong + bundle JS besar",
                   "• Routing? Pasang library sendiri",
                   "• Metadata dan rendering perlu tooling tambahan",
                   "• Loading awal lambat di koneksi pelan"], ROSE),
                 ("Dengan Next.js",
                  ["• Routing dari struktur folder (app/)",
                   "• Server render → HTML utuh terkirim",
                   "• Optimasi gambar/font bawaan",
                   "• Code splitting otomatis per halaman"], EMERALD),
                 ("Struktur minimum proyek",
                  ["app/layout.tsx  → kerangka semua halaman (wajib)",
                   "app/page.tsx    → halaman / (root)",
                   "app/globals.css → CSS global + Tailwind",
                   "package.json    → dependensi & script (dev/build)"], PRIMARY)])

    section_divider(prs, "02", "File-based Routing",
                    "Struktur folder app/ = peta URL situsmu", color=EMERALD)

    slide_ascii(prs, "Folder → URL",
                "page.tsx = halaman yang bisa diakses; layout.tsx = bungkus yang bertahan",
                'app/\n'
                '├── layout.tsx              (kerangka semua halaman)\n'
                '├── page.tsx                →  /\n'
                '├── tentang/\n'
                '│   └── page.tsx            →  /tentang\n'
                '├── materi/\n'
                '│   ├── page.tsx            →  /materi\n'
                '│   └── [slug]/\n'
                '│       └── page.tsx        →  /materi/html-dasar\n'
                '│                              /materi/css-dasar\n'
                '└── components/             (bukan route — tak ada page.tsx)\n'
                '    └── Navbar.tsx',
                caption="Hanya folder dengan page.tsx yang menjadi URL. [kurung] = segmen dinamis.",
                accent=EMERALD)

    slide_code(prs, "layout.tsx dan page.tsx",
               "Layout membungkus page lewat props children; tidak di-render ulang saat pindah halaman",
               '// app/layout.tsx\n'
               'export default function RootLayout({\n'
               '  children,\n'
               '}: { children: React.ReactNode }) {\n'
               '  return (\n'
               '    <html lang="id">\n'
               '      <body>\n'
               '        <nav>{/* Navbar semua hal. */}</nav>\n'
               '        <main>{children}</main>\n'
               '        <footer>© 2026</footer>\n'
               '      </body>\n'
               '    </html>\n'
               '  );\n'
               '}\n'
               '\n'
               '// app/tentang/page.tsx\n'
               'export default function TentangPage() {\n'
               '  return <h1>Tentang Kami</h1>;\n'
               '}',
               accent=EMERALD, font_size=9.5,
               right_cards=[("Navigasi dengan <Link>",
                             ["import Link from \"next/link\";",
                              "<Link href=\"/tentang\">",
                              "  Tentang</Link>",
                              "• Tanpa reload halaman penuh",
                              "• Prefetch otomatis"], EMERALD),
                            ("Metadata (SEO)",
                             ["export const metadata = {",
                              "  title: \"Tentang | Situsku\",",
                              "  description: \"...\",",
                              "};  // di page/layout"], PRIMARY)])

    section_divider(prs, "03", "Dynamic Route",
                    "[slug] menangkap nilai dari URL — satu file untuk banyak halaman",
                    color=AMBER)

    slide_code(prs, "Dynamic Route: app/materi/[slug]/page.tsx",
               "URL /materi/css-dasar → params.slug = \"css-dasar\"",
               'import { notFound } from "next/navigation";\n'
               'import { daftarMateri } from "@/lib/data";\n'
               '\n'
               'export function generateStaticParams() {\n'
               '  return daftarMateri.map((m) => ({\n'
               '    slug: m.slug,\n'
               '  }));\n'
               '}\n'
               '\n'
               'export default async function DetailPage({\n'
               '  params,\n'
               '}: { params: Promise<{ slug: string }> }) {\n'
               '  const { slug } = await params;\n'
               '  const materi = daftarMateri.find(\n'
               '    (m) => m.slug === slug\n'
               '  );\n'
               '  if (!materi) notFound();\n'
               '\n'
               '  return <h1>{materi.judul}</h1>;\n'
               '}',
               accent=AMBER, font_size=9.5,
               right_cards=[("Alur data",
                             ["1. User buka /materi/x",
                              "2. Next cocokkan folder [slug]",
                              "3. params berisi { slug: \"x\" }",
                              "4. Cari data, render, atau 404"], AMBER),
                            ("generateStaticParams",
                             ["• Daftar slug diketahui saat",
                              "  build → halaman jadi statis",
                              "• Cepat + murah di-hosting"], EMERALD)])

    section_divider(prs, "04", "Server vs Client Component",
                    "Default = server. \"use client\" hanya saat butuh interaksi.",
                    color=VIOLET)

    slide_ascii(prs, "Request Flow — App Router",
                "Server component dirender di server; client component di-hydrate di browser",
                ' Browser                     Server (Next.js)\n'
                '    │  GET /materi/css  ──────────▶│\n'
                '    │                              │ 1. cocokkan route app/\n'
                '    │                              │ 2. render layout + page\n'
                '    │                              │    (server component,\n'
                '    │                              │     boleh await data)\n'
                '    │ ◀───── HTML utuh + CSS ──────│\n'
                '    │  (langsung terlihat!)        │\n'
                '    │ ◀── JS client component ─────│\n'
                '    │  3. hydration: tombol dkk    │\n'
                '    │     jadi interaktif          │\n'
                '    ▼                              ▼',
                caption="Konten tampil dulu (HTML server), interaktivitas menyusul (hydration).",
                accent=VIOLET)

    slide_compare(prs, "Server vs Client Component",
                  "Pertanyaan kunci: butuh useState/onClick? Kalau tidak → biarkan server.",
                  "SERVER (default)",
                  ["• Render di server, JS tak dikirim",
                   "• Boleh async/await data & rahasia",
                   "• Akses DB/file langsung",
                   "• TIDAK bisa useState/onClick",
                   "• Cocok: halaman, daftar, detail"],
                  "CLIENT (\"use client\")",
                  ["• Baris pertama file: \"use client\"",
                   "• Bisa useState, useEffect, event",
                   "• Dikirim sebagai JS ke browser",
                   "• Tak bisa akses rahasia server",
                   "• Cocok: form, tombol, filter"],
                  lc=EMERALD, rc=AMBER,
                  bottom=("Pola terbaik: halaman tetap server; bagian interaktif dipecah jadi client component kecil.", VIOLET))

    slide_code(prs, "Komposisi: Server Membungkus Client",
               "Data diambil di server, interaksi ditangani client component kecil",
               '// app/produk/page.tsx (SERVER)\n'
               'import { getProduk } from "@/lib/data";\n'
               'import TombolSuka from\n'
               '  "@/components/TombolSuka";\n'
               '\n'
               'export default async function Page() {\n'
               '  const produk = await getProduk();\n'
               '  return (\n'
               '    <ul>\n'
               '      {produk.map((p) => (\n'
               '        <li key={p.id}>\n'
               '          {p.nama}\n'
               '          <TombolSuka id={p.id} />\n'
               '        </li>\n'
               '      ))}\n'
               '    </ul>\n'
               '  );\n'
               '}\n'
               '\n'
               '// components/TombolSuka.tsx (CLIENT)\n'
               '"use client";\n'
               'import { useState } from "react";\n'
               'export default function TombolSuka(...)',
               accent=VIOLET, font_size=9,
               right_cards=[("Aturan komposisi",
                             ["• Server boleh me-render client",
                              "• Client TIDAK bisa import",
                              "  server component langsung",
                              "  (tapi bisa terima children)",
                              "• Props harus serializable"], VIOLET),
                            ("Sinyal butuh \"use client\"",
                             ["useState / useEffect,",
                              "onClick / onChange,",
                              "browser API (localStorage)"], AMBER)])

    slide_mistakes(prs, "Kesalahan Umum Next.js — Hindari Ini!", [
        ("1. \"use client\" di mana-mana",
         "Kehilangan keunggulan server rendering.\nDefault server; client hanya bila perlu.",
         ROSE),
        ("2. useState di server comp.",
         "Error! Hook interaktif butuh \"use client\"\ndi baris pertama file.",
         ROSE),
        ("3. <a> untuk pindah internal",
         "Full reload, state hilang.\nPakai <Link href=\"...\"> dari next/link.",
         AMBER),
        ("4. Lupa await params",
         "Di Next 15 params adalah Promise.\nconst { slug } = await params;",
         AMBER),
        ("5. Folder = route semua",
         "components/ ikut jadi URL? Tidak —\nhanya folder ber-page.tsx yang jadi route.",
         VIOLET),
        ("6. Rahasia bocor ke client",
         "API key di client component terkirim\nke browser! Simpan di server/env.",
         VIOLET),
    ])

    slide_twocode(prs, "Cheatsheet Next.js App Router", None,
                  '# Struktur\n'
                  'app/layout.tsx    → kerangka\n'
                  'app/page.tsx      → /\n'
                  'app/x/page.tsx    → /x\n'
                  'app/x/[id]/page.tsx → /x/:id\n'
                  'app/not-found.tsx → 404\n'
                  '\n'
                  '# Perintah\n'
                  'npx create-next-app@latest\n'
                  'npm run dev    # localhost:3000\n'
                  'npm run build  # produksi',
                  '// Navigasi\n'
                  'import Link from "next/link";\n'
                  '<Link href="/materi">Materi</Link>\n'
                  '\n'
                  '// Dynamic + 404\n'
                  'const { slug } = await params;\n'
                  'if (!data) notFound();\n'
                  '\n'
                  '// Client component\n'
                  '"use client";  // baris PERTAMA\n'
                  '\n'
                  '// Metadata\n'
                  'export const metadata = {\n'
                  '  title: "...", description: "..." };',
                  accent_l=VIOLET, accent_r=EMERALD,
                  caption=("Latihan: 1-pembelajaran/07-nextjs-app-router (routing, dynamic route, server/client)", AMBER))

    web_closing(prs, "07", "Next.js App Router — React tingkat produksi", [
        (PRIMARY, "Framework",
         "Next.js = React + routing + server rendering + optimasi. SEO dan performa lebih baik."),
        (EMERALD, "Routing",
         "Folder app/ = URL. page.tsx halaman, layout.tsx kerangka persisten, <Link> navigasi."),
        (AMBER, "Dynamic",
         "[slug] menangkap URL; await params; notFound() untuk 404; generateStaticParams untuk statis."),
        (VIOLET, "Server vs Client",
         "Default server (data, SEO). \"use client\" untuk useState/event. Pecah kecil-kecil."),
        (ROSE, "Pitfall",
         "Jangan use client semua, jangan <a> internal, jangan taruh rahasia di client."),
    ])


# ═══════════════════════════════════════════════════════════════════
# MODUL 08 — Proyek Next.js + Tailwind
# ═══════════════════════════════════════════════════════════════════

def build_08(prs):
    C = ROSE
    web_cover(prs, 8, "Proyek Next.js + Tailwind",
              ["Arsitektur proyek · data flow · deployment",
               "Menggabungkan seluruh modul jadi produk utuh"],
              color=C, pills=["arsitektur", "data-flow", "kualitas", "deploy"])

    agenda_slide(prs, "Agenda — Modul 08: Proyek Akhir", [
        ("01", "Arsitektur\nProyek", PRIMARY,
         ["Struktur folder", "Pemisahan layer", "Konvensi nama", "lib/ vs components/"]),
        ("02", "Data\nFlow", EMERALD,
         ["Data terpusat", "Server → props", "Client islands", "Tipe data"]),
        ("03", "Kualitas", AMBER,
         ["Responsive", "Aksesibilitas", "Loading & 404", "Checklist rilis"]),
        ("04", "Deployment", VIOLET,
         ["Build produksi", "Git → Vercel", "Env variable", "Preview deploy"]),
    ])

    section_divider(prs, "01", "Arsitektur Proyek",
                    "Struktur yang jelas = proyek mudah tumbuh dan dinilai", color=PRIMARY)

    slide_ascii(prs, "Struktur Proyek Katalog",
                "Tiga layer: data (lib), UI reusable (components), halaman (app)",
                'katalog-produk/\n'
                '├── app/                      ← ROUTING + halaman\n'
                '│   ├── layout.tsx               (navbar/footer global)\n'
                '│   ├── page.tsx                 /          beranda\n'
                '│   ├── globals.css              (Tailwind directives)\n'
                '│   ├── produk/\n'
                '│   │   ├── page.tsx             /produk    daftar + filter\n'
                '│   │   └── [id]/page.tsx        /produk/3  detail\n'
                '│   └── not-found.tsx            404 custom\n'
                '├── components/               ← UI dipakai ulang\n'
                '│   ├── Navbar.tsx  ProdukCard.tsx  FilterKategori.tsx\n'
                '├── lib/                      ← DATA & logika murni\n'
                '│   ├── data.ts                  (array produk + helper)\n'
                '│   └── format.ts                (formatRupiah, dll.)\n'
                '└── package.json  tailwind.config  tsconfig',
                caption="Aturan: app/ boleh import components/ dan lib/; lib/ tidak boleh import UI.",
                accent=PRIMARY, font_size=10.5)

    slide_cards(prs, "Prinsip Pemisahan Layer",
                "Setiap file punya satu alasan untuk berubah",
                [("lib/ — data & logika",
                  ["• Array data + fungsi getProduk(), getById()",
                   "• Fungsi murni: formatRupiah(15000)",
                   "• Tidak tahu-menahu soal React/JSX",
                   "• Mudah diganti API sungguhan nanti"], EMERALD),
                 ("components/ — UI reusable",
                  ["• Menerima data via props, tanpa fetch sendiri",
                   "• ProdukCard dipakai beranda DAN halaman produk",
                   "• Client component hanya yang interaktif",
                   "  (FilterKategori)"], AMBER),
                 ("app/ — halaman & routing",
                  ["• Merangkai: ambil data dari lib/,",
                   "  susun components/",
                   "• Menentukan metadata per halaman",
                   "• Tipis — logika berat jangan di sini"], PRIMARY)])

    section_divider(prs, "02", "Data Flow",
                    "Dari array di lib/ sampai piksel di layar", color=EMERALD)

    slide_ascii(prs, "Data Flow Proyek — Server ke Client",
                "Satu sumber data mengalir satu arah; interaksi filter terjadi di client island",
                ' lib/data.ts          app/produk/page.tsx      components/\n'
                ' ┌───────────┐  impor  ┌────────────────┐  props ┌──────────────┐\n'
                ' │ produk[]  │ ──────▶ │ SERVER comp.   │ ─────▶ │ ProdukCard   │\n'
                ' │ getProduk │         │ ambil + susun  │        │ (server)     │\n'
                ' └───────────┘         │                │        ├──────────────┤\n'
                '                       │                │ ─────▶ │ FilterKateg. │\n'
                '                       └────────────────┘        │ "use client" │\n'
                '                                                 │ useState ✓   │\n'
                '                                                 └──────────────┘\n'
                '  Alur filter: klik kategori → state di client → daftar difilter\n'
                '  (client) ATAU navigasi ?kategori=kopi → server render ulang',
                caption="Data down (props), events up (callback) — berlaku juga lintas server/client.",
                accent=EMERALD, font_size=10.5)

    slide_code(prs, "lib/data.ts — Sumber Data Terpusat",
               "Definisikan tipe + data + helper di satu tempat",
               '// lib/data.ts\n'
               'export type Produk = {\n'
               '  id: number;\n'
               '  nama: string;\n'
               '  kategori: "kopi" | "nonkopi" | "snack";\n'
               '  harga: number;\n'
               '  deskripsi: string;\n'
               '};\n'
               '\n'
               'export const daftarProduk: Produk[] = [\n'
               '  { id: 1, nama: "Kopi Susu Senja",\n'
               '    kategori: "kopi", harga: 18000,\n'
               '    deskripsi: "..." },\n'
               '  // ...\n'
               '];\n'
               '\n'
               'export function getProdukById(id: number) {\n'
               '  return daftarProduk.find(\n'
               '    (p) => p.id === id);\n'
               '}',
               accent=EMERALD, font_size=9.5,
               right_cards=[("Kenapa dipusatkan?",
                             ["• Ganti data → 1 file saja",
                              "• Tipe Produk menjaga semua",
                              "  komponen konsisten",
                              "• Besok ganti ke API/DB:",
                              "  cukup ubah isi fungsi"], EMERALD),
                            ("Format Rupiah",
                             ["harga.toLocaleString(\"id-ID\")",
                              "atau Intl.NumberFormat —",
                              "taruh di lib/format.ts"], AMBER)])

    section_divider(prs, "03", "Kualitas: Responsive, A11y, Edge Case",
                    "Yang membedakan tugas asal jadi dan proyek matang", color=AMBER)

    slide_cards(prs, "Checklist Kualitas Proyek",
                "Uji sebelum mengumpulkan / merilis",
                [("Responsive",
                  ["• Uji 360px (HP), 768px (tablet), 1280px",
                   "• Grid: grid-cols-1 sm:grid-cols-2 lg:grid-cols-3",
                   "• Tak ada scroll horizontal",
                   "• Gambar max-w-full / next/image"], PRIMARY),
                 ("Aksesibilitas",
                  ["• Semua img ber-alt, form ber-label",
                   "• Heading berjenjang (h1 → h2 → h3)",
                   "• Fokus keyboard terlihat (focus-visible:ring)",
                   "• Kontras teks cukup (slate-600+ di putih)"], EMERALD),
                 ("Edge case",
                  ["• Data kosong → tampilkan pesan, bukan blank",
                   "• URL id salah → notFound() (404 custom)",
                   "• Loading state (loading.tsx) untuk data lambat",
                   "• Teks panjang tidak merusak layout (truncate)"], AMBER)])

    section_divider(prs, "04", "Deployment",
                    "Dari laptop ke internet: build → push → deploy", color=VIOLET)

    slide_ascii(prs, "Alur Deployment ke Vercel",
                "Vercel (pembuat Next.js) membaca repo dan mendeploy otomatis tiap push",
                ' Laptop                GitHub                 Vercel\n'
                ' ┌──────────┐  push   ┌──────────┐  webhook  ┌──────────────┐\n'
                ' │ kode +   │ ──────▶ │ repo     │ ────────▶ │ npm install  │\n'
                ' │ git      │         │ main     │           │ npm run build│\n'
                ' └──────────┘         └──────────┘           │ deploy CDN   │\n'
                '      │                    │                 └──────┬───────┘\n'
                '      │                    │ branch/PR              │\n'
                '      │                    └──────▶ PREVIEW URL     ▼\n'
                '      │                            (uji dulu!)  https://\n'
                '      └── npm run build (cek lokal              proyekmu\n'
                '          sebelum push!)                        .vercel.app',
                caption="npm run build HARUS sukses lokal dulu — error build = deploy gagal.",
                accent=VIOLET, font_size=10.5)

    slide_table(prs, "Perintah & Konfigurasi Penting",
                "Dari pengembangan sampai produksi",
                ["Perintah / file", "Fungsi", "Catatan"],
                [["npm run dev", "Server pengembangan", "Hot reload di localhost:3000"],
                 ["npm run build", "Build produksi", "Wajib sukses sebelum deploy"],
                 ["npm start", "Jalankan hasil build", "Simulasi produksi lokal"],
                 ["npm run lint", "Cek kualitas kode", "Gunakan script ESLint/Biome proyek"],
                 [".env.local", "Rahasia (API key)", "JANGAN di-commit ke git"],
                 ["NEXT_PUBLIC_*", "Env yang boleh ke browser", "Selain ini, server-only"]],
                [3.0, 4.0, 5.3],
                header_colors=[PRIMARY, EMERALD, AMBER], body_size=9.5)

    slide_mistakes(prs, "Kesalahan Umum Proyek — Hindari Ini!", [
        ("1. Semua kode di page.tsx",
         "File 500 baris tak terbaca. Pecah ke\ncomponents/ dan lib/ sesuai layer.",
         ROSE),
        ("2. Data dicopy per halaman",
         "Beranda & detail beda data!\nSatu sumber di lib/data.ts.",
         ROSE),
        ("3. Tak pernah npm run build",
         "Error type/import baru ketahuan saat\ndeploy. Build lokal sebelum push.",
         AMBER),
        ("4. .env ikut ke-commit",
         "API key bocor permanen di riwayat git.\nPastikan .gitignore memuat .env*.",
         AMBER),
        ("5. Uji hanya di desktop",
         "Dosen/user buka di HP: layout hancur.\nUji 360px sejak awal (DevTools).",
         VIOLET),
        ("6. Tanpa 404/empty state",
         "URL salah → crash/blank. notFound() +\npesan \"belum ada data\" itu wajib.",
         VIOLET),
    ])

    slide_twocode(prs, "Cheatsheet Proyek", None,
                  '# Setup\n'
                  'npx create-next-app@latest katalog \\\n'
                  '  --typescript --tailwind --app\n'
                  'cd katalog && npm run dev\n'
                  '\n'
                  '# Struktur layer\n'
                  'lib/         data + logika murni\n'
                  'components/  UI reusable (props)\n'
                  'app/         halaman (rangkai)\n'
                  '\n'
                  '# Kualitas\n'
                  'alt, label, heading berjenjang,\n'
                  'uji 360/768/1280px, empty state,\n'
                  'notFound() utk id salah',
                  '# Data flow\n'
                  'lib/data.ts → page.tsx (server,\n'
                  '  await) → props → components\n'
                  'interaktif kecil: "use client"\n'
                  '\n'
                  '# Deployment\n'
                  'npm run build   # wajib lolos!\n'
                  'git push        # ke GitHub\n'
                  '→ Vercel deploy otomatis\n'
                  '→ PR = preview URL\n'
                  '\n'
                  '# Rahasia\n'
                  '.env.local (git-ignored)\n'
                  'NEXT_PUBLIC_ = boleh ke browser',
                  accent_l=ROSE, accent_r=VIOLET,
                  caption=("Latihan: 1-pembelajaran/08-proyek-nextjs-tailwind (4 tahap) + studi kasus 03", EMERALD))

    web_closing(prs, "08", "Proyek — arsitektur, data flow, deployment", [
        (PRIMARY, "Arsitektur",
         "Tiga layer: lib/ (data), components/ (UI reusable), app/ (halaman). Aturan impor searah."),
        (EMERALD, "Data Flow",
         "Satu sumber data di lib/, server component mengambil, props mengalir ke bawah."),
        (AMBER, "Kualitas",
         "Responsive 360-1280px, alt/label/fokus, empty state, 404 custom, loading state."),
        (VIOLET, "Deployment",
         "npm run build lokal → push GitHub → Vercel otomatis. Preview URL per branch."),
        (ROSE, "Pitfall",
         "Jangan tumpuk semua di page.tsx, jangan commit .env, jangan lupa uji di HP."),
    ])


# ═══════════════════════════════════════════════════════════════════
# Main
# ═══════════════════════════════════════════════════════════════════

TOPICS = [
    ("01-html-dasar", build_01),
    ("02-css-dasar", build_02),
    ("03-layout-responsive", build_03),
    ("04-tailwind-css", build_04),
    ("05-javascript-dom", build_05),
    ("06-react-komponen", build_06),
    ("07-nextjs-app-router", build_07),
    ("08-proyek-nextjs-tailwind", build_08),
]


def main():
    for folder, builder in TOPICS:
        prs = make_presentation()
        builder(prs)
        out_dir = os.path.join(BASE, folder)
        os.makedirs(out_dir, exist_ok=True)
        out = os.path.join(out_dir, "slides.pptx")
        save_presentation(prs, out)
        n = len(prs.slides.__iter__.__self__._sldIdLst)  # jumlah slide
        print(f"  {folder}: {n} slide")


if __name__ == "__main__":
    main()
