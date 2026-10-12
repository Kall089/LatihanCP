# 🌐 ROADMAP WEB — DAY 1 s/d DAY 392

**Frontend: TypeScript + Tailwind + Next.js · Backend: Laravel · Go · Rust (fokus)**

**Durasi:** 392 hari (± **14 bulan**)
**Folder:** [`Web/`](Web/) — satu `Day-XX` per hari, pola sama dengan [`CP/`](CP/)

**Urutan UI:** HTML → **CSS lengkap** (selector sampai responsive) → **Tailwind** (produksi) → TypeScript → Next.js

**Yang tidak ada di roadmap ini (sengaja):**
- JavaScript “dulu baru TypeScript” — langsung **TypeScript**
- Vue / Svelte / Astro sebagai jalur utama — fokus **Next.js**
- Node/Express sebagai backend utama — backend = **Laravel, Go, Rust**
- CSS *legacy* sebagai jalur (float layout, vendor prefix drama) — disebut singkat, tidak dilatih berhari-hari

> Kuliah `../PemrogramanWeb/` tetap ringkasan semester. Roadmap ini jalur mahir per hari.

---

## 🎯 CARA PAKAI

**Rutinitas (2–3 jam):** teori 30–45 mnt → ketik ulang 15 mnt → latihan 60–90 mnt → catat 10 mnt.

- Setiap hari punya **tujuan + daftar materi + praktik + kriteria selesai**.
- Topik mudah **digabung** (hari tetap padat).
- **Batas frustrasi 30–45 menit**, lalu solusi → ketik ulang.
- Deploy minimal 1× per bulan mulai Day 28.
- Setelah CSS lengkap, **produksi UI = Tailwind**. CSS murni tetap dipakai untuk mengerti *kenapa* class Tailwind bekerja.
- Urutan backend: Laravel → Go → **Rust (paling dalam)**.

**Target:**

| Selesai | Bisa |
| ------- | ---- |
| Day 7   | Halaman semantik + form valid tanpa CSS |
| Day 23  | Layout halaman dengan **CSS murni** (flex/grid/responsive) |
| Day 28  | Profil + landing **Tailwind**, live |
| Day 56  | Design system kecil (kartu, nav, form, dark) |
| Day 84  | TypeScript: tipe, modul, fetch, DOM tanpa `any` |
| Day 140 | Next.js App Router + Tailwind, data server, Vercel |
| Day 196 | Laravel: Eloquent, auth, API, deploy |
| Day 252 | Go: service HTTP, sqlc, tes, 1 binary |
| Day 336 | Rust: Axum + SQLx, API setara Go, produksi |
| Day 364 | Next + **satu** BE + CI |
| Day 392 | Capstone live yang bisa dibela |

---

## 📁 STRUKTUR FOLDER HARI

```
Web/Day-XX (Nama Topik)/
├── README.md
├── teori/Day_XX_Teori_Lengkap.md + slides.pptx
├── latihan/   exercise + TODO
├── solusi/
├── tugas/     tanpa kunci
└── template/
```

Prompt harian: [`PROMPT_TEMPLATE_WEB.md`](PROMPT_TEMPLATE_WEB.md)

---

# ═══════════════════════════════════════════
# BULAN 1 — HTML + CSS LENGKAP + TAILWIND AWAL (Day 1–28)
# ═══════════════════════════════════════════

> HTML 1 minggu. CSS **kurikulum biasa, lengkap** 2 minggu (bukan 1 hari jembatan). Tailwind mulai setelah kamu bisa layout tanpa utility.

---

### 📅 Day 1 — Cara kerja web, file HTML, struktur dokumen

- **Tujuan:** Paham halaman = file yang dibaca browser, bukan “sihir VS Code”.
- **Materi:**
  - Client vs server (gambaran); URL, folder, `index.html`
  - Browser merender: parse HTML → pohon DOM (intuisi)
  - `<!DOCTYPE html>`, `<html lang="id">`, `<head>`, `<body>`
  - Wajib di `head`: `meta charset`, `title`, `meta viewport`
  - **Tag** vs **elemen** vs **atribut**; elemen void (`meta`, `img`, `br`, `input`) vs berpasangan
  - Nesting valid; komentar `<!-- -->`; indentasi
  - Valid vs rusak: tag tidak ditutup, atribut tanpa kutip
- **Praktik:** 1 halaman “Halo” + inspect di DevTools (Elements). Buat 1 file sengaja rusak, bandingkan.
- **Selesai jika:** Bisa sebutkan isi `head` wajib dan beda tag/elemen/atribut tanpa melihat catatan.

---

### 📅 Day 2 — Konten dasar: teks, daftar, tautan, gambar, path

- **Tujuan:** Semua konten statis yang dipakai 90% halaman.
- **Materi:**
  - Heading `h1`–`h6` (satu `h1` per halaman); `p`; kapan `br` (jangan ganti paragraf)
  - `strong`/`em` (makna) vs tebalkan visual nanti
  - `blockquote`, `pre`/`code`, `hr`
  - `ul`/`ol`/`li` bersarang; `dl`/`dt`/`dd` (definisi)
  - `a`: `href`, path relatif (`./`, `../`), `#id`, `mailto:`, `tel:`; `target="_blank"` + `rel="noopener noreferrer"`
  - `img`: `src`, `alt` bermakna (atau `alt=""` dekoratif), `width`/`height` (hindari layout shift)
  - Path: relatif vs absolut `/`; folder `assets/img/`
- **Praktik:** Halaman “catatan kuliah”: judul, 2 daftar, 3 tautan internal/eksternal, 2 gambar.
- **Selesai jika:** Semua tautan jalan; `alt` bukan nama file; path relatif tidak pecah.

---

### 📅 Day 3 — Semantik, tabel, aksesibilitas dasar

- **Tujuan:** HTML yang dibaca manusia, reader, dan SEO — bukan `div` semua.
- **Materi:**
  - Landmark: `header`, `nav`, `main` (satu), `article`, `section`, `aside`, `footer`
  - Outline heading: jangan loncat `h1` → `h3`
  - `table`: `caption`, `thead`/`tbody`/`tfoot`, `th` + `scope="col|row"`, `td`; kapan tabel (data) vs CSS grid (tata letak)
  - A11y: teks tautan jelas (“Buka silabus” bukan “klik di sini”); `alt`; `lang`; kontras *nanti di CSS*
  - Skip-link (konsep); landmark = navigasi reader
- **Praktik:** Halaman artikel + tabel jadwal kuliah semantik.
- **Selesai jika:** Tanpa CSS, struktur masih masuk akal jika dibaca dari atas ke bawah.

---

### 📅 Day 4 — Formulir lengkap

- **Tujuan:** Form yang bisa dipakai, dikaitkan label, siap di-style.
- **Materi:**
  - `form`: `action`, `method` (`get` vs `post` — kapan mana)
  - `label` + `for`/`id` (wajib); klik label fokus ke input
  - `input type`: `text`, `email`, `password`, `number`, `tel`, `url`, `date`, `search`, `file`, `hidden`, `checkbox`, `radio` (satu `name`)
  - `name` (data terkirim) vs `id` (label/JS nanti)
  - Validasi HTML: `required`, `minlength`/`maxlength`, `min`/`max`, `step`, `pattern`, `autocomplete`
  - `select` + `option` + `optgroup`; `textarea`; `datalist`
  - `button type="submit|button|reset"`; `fieldset` + `legend`
  - Jangan andalkan validasi browser saja (nanti TS/server)
- **Praktik:** Form daftar akun: nama, email, password, tanggal lahir, jurusan (select), setuju (checkbox), submit.
- **Selesai jika:** Setiap kontrol punya label; radio sekelompok; submit tidak `div` palsu.

---

### 📅 Day 5 — Proyek: Profil Saya (HTML murni)

- **Tujuan:** Satu halaman portofolio mini tanpa CSS.
- **Materi (pakai, jangan teori baru):** landmark, heading, daftar skill, tautan sosial, gambar, form kontak, tabel “mata kuliah / nilai dummy”.
- **Praktik:** `profil.html` lengkap: hero teks, tentang, skill, proyek (3 item tautan), kontak.
- **Selesai jika:** Valid secara struktur; 1 `h1`; `main`; form ber-label; gambar ber-`alt`.

---

### 📅 Day 6 — Media, embed, dan kebersihan markup

- **Tujuan:** Konten non-teks + HTML yang rapi.
- **Materi:**
  - `figure` + `figcaption`; `picture`/`source` (gambaran, detail di CSS/Tailwind image)
  - `audio`/`video` + `controls` (aksesibel); jangan autoplay bersuara
  - `iframe` (peta/video): judul, batasan keamanan `sandbox` (kenal saja)
  - `time datetime`; `address`; `small`
  - Karakter khusus: `&amp;` `&lt;` `&nbsp;` (jangan berlebihan)
  - Favicon `link rel="icon"`
- **Praktik:** Tambah ke profil: 1 figure, 1 `time`, favicon, 1 embed opsional.
- **Selesai jika:** Markup bersih; tidak ada tag “asal nutup”.

---

### 📅 Day 7 — REVIEW HTML

- **Tujuan:** HTML terkunci sebelum CSS.
- **Materi:** Kuis: tag vs atribut; semantik vs `div`; kapan tabel; label form; path; a11y.
- **Praktik:** Perbaiki profil (heading, label, `alt`, landmark). Checklist 15 poin.
- **Selesai jika:** Profil lolos checklist; kamu bisa jelaskan setiap landmark.

---

### 📅 Day 8 — CSS: cara kerja, menempelkan style, cascade

- **Tujuan:** CSS = aturan “siapa menang” — bukan kumpulan warna acak.
- **Materi:**
  - CSS apa: properti + nilai; *declaration*, *rule set*, *stylesheet*
  - 3 cara: inline `style=`, `<style>`, file eksternal `<link rel="stylesheet">` — **wajib eksternal**
  - Urutan load; DevTools: Computed vs Styles
  - **Cascade:** origin, importance, urutan sumber
  - **Inheritance:** yang diwarisi (`color`, `font-*`) vs tidak (`margin`, `border`)
  - `* { }` reset kasar vs nanti Preflight Tailwind
- **Praktik:** File `styles.css` terpisah; 5 rule; ubah lewat DevTools.
- **Selesai jika:** Bisa jelaskan kenapa style A mengalahkan B (tanpa hafal angka dulu).

---

### 📅 Day 9 — Selector lengkap

- **Tujuan:** Menarget elemen tanpa `style=` di setiap tag.
- **Materi:**
  - Type, class `.`, id `#` (id jarang untuk style)
  - Grup `h1, h2`; descendant `nav a`; child `ul > li`; adjacent `h2 + p`; sibling `h2 ~ p`
  - Atribut: `[type="email"]`, `[href^="https"]`
  - Pseudo-class: `:hover`, `:focus`, `:focus-visible`, `:first-child`, `:last-child`, `:nth-child()`, `:not()`, `:disabled`, `:checked`, `:invalid`
  - Pseudo-element: `::before`, `::after`, `::placeholder`, `::selection`
  - Modern (kenal + 1 latihan): `:is()`, `:where()`, `:has()`
- **Praktik:** Style daftar, form, dan tautan **hanya** dengan selector — tanpa class berlebihan dulu, lalu bandingkan dengan class.
- **Selesai jika:** Bisa tulis selector untuk “input email yang invalid” dan “tautan di nav saja”.

---

### 📅 Day 10 — Specificity, `!important`, dan urutan class

- **Tujuan:** Tidak panik ketika “CSS-ku tidak jalan”.
- **Materi:**
  - Skor: inline > id > class/atribut/pseudo-class > type/pseudo-element
  - `:where()` = 0; `:is()` = argumen tertinggi
  - `!important` — hampir selalu salah untuk belajar
  - Konflik dua class di satu elemen: **urutan di CSS file**, bukan urutan di `class=""`
  - Ini alasan nanti Tailwind “class terakhir di HTML tidak otomatis menang”
- **Praktik:** 8 teka-teki “siapa menang”; perbaiki stylesheet yang berantakan.
- **Selesai jika:** Bisa debug 1 konflik di DevTools (coret vs aktif) dan jelaskan.

---

### 📅 Day 11 — Nilai, satuan, warna

- **Tujuan:** Ukuran dan warna yang bisa diprediksi.
- **Materi:**
  - `px`, `rem` (akar), `em` (induk), `%`, `vw`/`vh`/`vmin`, `ch`
  - Kapan `rem` (font, spacing) vs `%` (lebar) vs `px` (border tipis)
  - `calc()`, `min()`, `max()`, `clamp()` (tipe fluid singkat)
  - Warna: keyword, `#hex`, `rgb`/`rgba`, `hsl`; `currentColor`; `transparent`
  - Opasitas `opacity` vs alpha pada warna (beda: warisi ke anak)
- **Praktik:** Halaman kartu: `max-width` + `padding` `rem`; judul `clamp`.
- **Selesai jika:** Tahu kenapa `font-size: 10px` di `html` merusak aksesibilitas.

---

### 📅 Day 12 — Tipografi CSS

- **Tujuan:** Teks terbaca, hierarki jelas.
- **Materi:**
  - `font-family` (stack + generic `sans-serif`); web font `link` Google *atau* file lokal (gambaran `@font-face`)
  - `font-size`, `font-weight`, `font-style`, `line-height` (unitless 1.5)
  - `letter-spacing`, `word-spacing`, `text-align`, `text-wrap`/`overflow-wrap`
  - `text-decoration`, `text-transform`, `text-underline-offset`
  - `white-space`; potong teks `overflow: hidden` + `text-overflow: ellipsis` + `white-space: nowrap`
  - Panjang baris ~45–75 karakter (`max-width: 65ch`)
- **Praktik:** Artikel 4–6 paragraf: hierarki heading, body 1rem/1.6, kutipan beda.
- **Selesai jika:** Tanpa “font 12px sesak”; heading tidak menempel body.

---

### 📅 Day 13 — Box model lengkap

- **Tujuan:** Setiap elemen = kotak; kamu mengontrol kotak itu.
- **Materi:**
  - Content + `padding` + `border` + `margin`; margin collapse (vertikal)
  - `box-sizing: content-box` vs `border-box` — **wajib `* { box-sizing: border-box }`**
  - `width`, `min-width`, `max-width`, `height`, `min-height` (`100vh` / `100dvh`)
  - Shorthand `margin`/`padding`/`border`; per-sisi
  - `border-radius`, `outline` vs `border` (fokus a11y: jangan `outline: none` tanpa ganti)
  - `box-shadow`; `overflow`: `visible|hidden|auto|scroll`
- **Praktik:** 3 kotak bersarang; ukur di DevTools; bandingkan content-box vs border-box.
- **Selesai jika:** `width: 100%` + padding tidak pecah layout karena `border-box`.

---

### 📅 Day 14 — Display, flow, dan REVIEW CSS fondasi

- **Tujuan:** Paham alur normal sebelum flex/grid.
- **Materi:**
  - `block`, `inline`, `inline-block`, `none`, `contents` (kenal)
  - `visibility: hidden` vs `display: none` vs `opacity: 0` (aksesibilitas/fokus)
  - Inline: `width`/`height` diabaikan; `vertical-align`
  - Normal flow; kenapa flex/grid “mengambil alih” flow anak
  - **REVIEW** Day 8–13: cascade, selector, satuan, tipe, box
- **Praktik:** Kuis 10 soal + perbaiki halaman yang overflow horizontal.
- **Selesai jika:** Bisa prediksi ukuran kotak dan siapa yang menang di 3 rule konflik.

---

### 📅 Day 15 — Flexbox: container

- **Tujuan:** Baris/kolom modern — fondasi nav dan kartu.
- **Materi:**
  - Sumbu utama vs silang; `flex-direction`: `row|column|*-reverse`
  - `flex-wrap`; `justify-content`; `align-items`; `align-content`
  - `gap` (ganti margin hacks)
  - `flex` shorthand di anak *besok*; hari ini kuasai **induk**
- **Praktik:** Nav horizontal; tumpuk kolom di konsep (belum wajib breakpoint).
- **Selesai jika:** Bisa gambar sumbu saat `flex-direction: column`.

---

### 📅 Day 16 — Flexbox: item + pola layout

- **Tujuan:** Anak flex yang tidak “meledak”.
- **Materi:**
  - `flex-grow`, `flex-shrink`, `flex-basis`; shorthand `flex: 1` / `flex: 0 0 auto`
  - `align-self`; `order` (hati-hati a11y: urutan visual ≠ DOM)
  - `min-width: 0` pada anak yang truncate
  - Pola: sticky footer (`min-height: 100dvh` + `flex-direction: column` + `main { flex: 1 }`)
  - Pola: kartu media (gambar + teks)
- **Praktik:** Header + main tumbuh + footer; kartu 3 kolom pakai wrap.
- **Selesai jika:** Footer di bawah viewport; kartu tidak overflow aneh.

---

### 📅 Day 17 — CSS Grid

- **Tujuan:** Tata letak 2 dimensi.
- **Materi:**
  - `display: grid`; `grid-template-columns` / `rows`; `fr`; `repeat()`
  - `minmax()`, `auto-fit` / `auto-fill` (galeri responsif tanpa media query dulu)
  - `gap`; `grid-column` / `grid-row` / `span`
  - `justify-items`, `align-items`, `place-items`; `justify-content` pada grid
  - Area: `grid-template-areas` + `grid-area` (header/nav/main/footer)
  - Flex vs grid: 1 arah vs 2 arah
- **Praktik:** Dashboard 12-kolom sederhana *atau* areas: header, sidebar, main, footer.
- **Selesai jika:** Bisa buat galeri yang rapih mengecil tanpa JS.

---

### 📅 Day 18 — Position, z-index, stacking

- **Tujuan:** Nav nempel, badge di sudut, overlay — sadar, bukan coba-coba.
- **Materi:**
  - `static` (default), `relative`, `absolute`, `fixed`, `sticky`
  - Containing block: ancestor `position` bukan `static`
  - `top/right/bottom/left` / `inset`; `sticky` + ancestor `overflow`
  - `z-index` hanya pada positioned; stacking context (opacity, filter, transform)
  - Float: **1 paragraf sejarah** — jangan pakai untuk layout baru
- **Praktik:** Header `sticky`; badge `absolute` di kartu; tombol `fixed` “ke atas”.
- **Selesai jika:** Badge mengikuti kartu (bukan viewport) karena parent `relative`.

---

### 📅 Day 19 — Latar, gambar, objek, overflow

- **Tujuan:** Visual blok tanpa merusak layout.
- **Materi:**
  - `background-color`, `background-image`, `url()`, gradient `linear-gradient`
  - `background-size` (`cover`/`contain`), `position`, `repeat`, shorthand `background`
  - Beberapa layer background
  - `object-fit` / `object-position` pada `img`
  - `aspect-ratio`
  - Overlay teks di atas gambar (pseudo atau anak + `position`)
- **Praktik:** Hero: gambar cover + overlay gelap + judul putih terbaca.
- **Selesai jika:** Gambar tidak gepeng; teks kontras.

---

### 📅 Day 20 — Responsive: media query, mobile-first

- **Tujuan:** Satu HTML, banyak lebar — pola yang Tailwind `sm:` tiru.
- **Materi:**
  - Viewport meta (ulangi kenapa wajib)
  - `@media (min-width: …)` mobile-first vs `max-width` desktop-first
  - Breakpoint umum: ~640, 768, 1024, 1280 (nanti sama Tailwind)
  - Ubah: `flex-direction`, jumlah kolom grid, `display: none` menu
  - Unit relatif agar zoom browser tidak rusak
  - Container query (kenal 15 menit — opsional 1 demo)
- **Praktik:** Profil: 1 kolom HP, 2 kolom tablet+; nav stack → baris.
- **Selesai jika:** 360px tidak scroll horizontal; 1280px tidak mega-lebar teks (batasi `max-width`).

---

### 📅 Day 21 — Form, state interaktif, transisi, variabel CSS

- **Tujuan:** Form kelihatan + token yang nanti jadi `tailwind.config`.
- **Materi:**
  - Style `input`/`select`/`textarea`/`button`; `appearance` (kenal)
  - `:hover`, `:focus-visible` (ring/`outline`), `:disabled`, `:invalid`/`:valid`
  - Jangan andalkan warna merah saja (ikon/teks error)
  - `transition`: `color`, `background`, `box-shadow`, `transform` — 150–200ms; jangan `all`
  - Custom property: `:root { --warna-merek; --spasi; }`; `var(--…)`
  - `prefers-reduced-motion`
- **Praktik:** Form Day 4 di-style: fokus terlihat, error jelas, tombol transisi.
- **Selesai jika:** Fokus keyboard terlihat; token dipakai di ≥3 tempat.

---

### 📅 Day 22 — A11y visual + polish CSS

- **Tujuan:** CSS yang tidak merusak aksesibilitas.
- **Materi:**
  - Kontras WCAG ~4.5:1 teks biasa; 3:1 UI besar
  - `:focus-visible` wajib; skip-link terlihat saat fokus
  - `sr-only` / `.visually-hidden` (clip pattern)
  - Target sentuh ~44px
  - `prefers-color-scheme` (pengantar dark) vs class `.dark` nanti
- **Praktik:** Audit profil CSS: kontras, fokus, ukuran sentuh, skip-link.
- **Selesai jika:** Tab ke semua kontrol; tidak ada `outline: none` tanpa pengganti.

---

### 📅 Day 23 — REVIEW CSS + proyek: profil memakai CSS murni

- **Tujuan:** Bukti kamu bisa layout **tanpa** Tailwind.
- **Materi:** Ulangi peta: cascade → box → flex/grid → position → media → token.
- **Praktik:** Style penuh Profil Saya: tipografi, nav, kartu proyek, form, footer, 360/768/1280.
- **Selesai jika:** Responsif; semantik tetap; 0 library. **Ini fondasi sebelum utility.**

---

### 📅 Day 24 — Tailwind: filosofi + setup (setelah CSS)

- **Tujuan:** Utility = CSS yang sudah kamu tahu, dipaket per class.
- **Materi:**
  - Utility-first vs “satu class `.card` berisi 40 properti”
  - Mapping: `p-4` → `padding`; `flex` → `display: flex`; `md:grid-cols-3` → media query
  - Setup **Vite + Tailwind** (bukan cuma CDN Play)
  - `content` paths (purge); `@tailwind base/components/utilities`
  - Preflight = reset — bandingkan dengan CSS Day 8
  - DevTools: class mana yang aktif
- **Praktik:** Halaman kosong → 1 kartu Tailwind; bandingkan dengan CSS Day 23.
- **Selesai jika:** Build jalan; kamu bisa “terjemahkan” 10 class ke CSS.

---

### 📅 Day 25 — Tailwind: spacing, ukuran, container

- **Tujuan:** Skala 4px di kepala.
- **Materi:**
  - `p`/`px`/`py`/`pt`… `m`/`mx`/`space-x`; negatif `-mt`
  - `w`/`h`/`min-h-screen`/`min-h-dvh`/`max-w-prose`/`max-w-6xl`
  - `container` + `mx-auto` + `px-4`
  - `size-*`; `w-full` vs `w-screen` (hati-hati overflow)
- **Praktik:** Layout halaman: container, section berjarak konsisten.
- **Selesai jika:** Tidak campur `p-3` dan `p-[13px]` tanpa alasan.

---

### 📅 Day 26 — Tailwind: tipe, warna, border, bayangan

- **Tujuan:** Palet default + hierarki teks.
- **Materi:**
  - `text-*` size/weight/leading/tracking/align/color
  - `bg-*`, `border`, `rounded`, `shadow`, `ring` (fokus)
  - Palet slate/zinc + satu warna merek
  - `divide-y`; `ring-offset`
- **Praktik:** Artikel + 2 kartu dengan hierarki yang sama seperti Day 12.
- **Selesai jika:** Body terbaca; judul tidak “teriak” tanpa skala.

---

### 📅 Day 27 — Tailwind: flex, grid, responsive, state

- **Tujuan:** Day 15–20 dalam bahasa utility.
- **Materi:**
  - `flex` `flex-col` `items-*` `justify-*` `gap-*` `grow` `shrink-0`
  - `grid` `grid-cols-*` `col-span-*` `md:grid-cols-3`
  - Mobile-first: unprefixed = HP; `sm:` `md:` `lg:`
  - `hover:` `focus:` `focus-visible:` `active:` `disabled:`
  - `group` / `peer` (1 contoh)
- **Praktik:** Nav + galeri 1→3 kolom; tombol hover/fokus.
- **Selesai jika:** 360px stack; 768px+ baris; fokus terlihat.

---

### 📅 Day 28 — REVIEW bulan 1 + deploy

- **Tujuan:** HTML + CSS + Tailwind awal live.
- **Materi:** Cheatsheet mapping CSS ↔ Tailwind; checklist semantik.
- **Praktik:** Profil Tailwind (boleh salin struktur Day 23). Deploy GitHub Pages / Cloudflare Pages.
- **Selesai jika:** URL live; 360px aman; kamu jelaskan 1 layout dalam CSS **dan** Tailwind.

**✅ Checkpoint:** Profil semantik + CSS murni (Day 23) + versi Tailwind live.

---

# ═══════════════════════════════════════════
# BULAN 2 — TAILWIND LANJUT (Day 29–56)
# ═══════════════════════════════════════════

> CSS sudah lengkap. Bulan ini: pola UI, token, dark mode, dua halaman produksi.

---

### 📅 Day 29 — Design token + dark mode

- **Tujuan:** Merek di config, bukan class acak.
- **Materi:** `tailwind.config` `theme.extend`: `colors`, `fontFamily`, `borderRadius`, `boxShadow`; `darkMode: 'class'` vs `media`; class `dark:`; toggle *nanti TS*; jangan 20 warna.
- **Praktik:** Token merek + 1 halaman light/dark (toggle class di `<html>` manual).
- **Selesai jika:** Ganti 1 token di config mengubah banyak tempat.

---

### 📅 Day 30 — Tombol: varian dan ukuran

- **Tujuan:** Satu “komponen” tanpa React — potongan HTML + class konsisten.
- **Materi:** Varian primary/secondary/ghost/danger; size sm/md/lg; `disabled:`; ikon + teks `inline-flex gap-2`; jangan 4 radius campur.
- **Praktik:** Kitchen sink tombol (enabled/hover/focus/disabled × varian).
- **Selesai jika:** Semua tombol memakai token Day 29.

---

### 📅 Day 31 — Form UI lengkap (Tailwind)

- **Tujuan:** Input produksi, memetakan CSS Day 21.
- **Materi:** Label, helper, error text, `aria-invalid`; `ring` fokus; group prefix/suffix; checkbox/radio custom *visual* tetap pakai input asli; `disabled:opacity`.
- **Praktik:** Form daftar + state error palsu (class).
- **Selesai jika:** Error tidak warna-saja; fokus keyboard jelas.

---

### 📅 Day 32 — Kartu, badge, chip

- **Tujuan:** Pola kartu yang bisa diulang.
- **Materi:** 3–4 varian: media, stat, list row, CTA; badge status; `line-clamp`; footer kartu `mt-auto` di flex.
- **Praktik:** Library 4 kartu × light/dark.
- **Selesai jika:** Tinggi kartu dalam satu row terasa konsisten.

---

### 📅 Day 33 — Navigasi + header sticky + menu mobile

- **Tujuan:** Chrome situs.
- **Materi:** `sticky top-0 z-`; backdrop; hamburger (`<button>`, `aria-expanded` konsep); panel `hidden md:flex`; hindari hanya hover untuk buka menu.
- **Praktik:** Header + logo + 4 tautan + CTA; HP menu tertutup default.
- **Selesai jika:** Sticky tidak nutup fokus; menu bisa dibayangkan dikontrol TS nanti.

---

### 📅 Day 34 — Marketing: hero, logo cloud, fitur, FAQ

- **Tujuan:** Section landing standar.
- **Materi:** Hero (judul, sub, 2 CTA, visual); `dl` fitur; logo grayscale; FAQ `<details>`/`<summary>` (tanpa JS).
- **Praktik:** Landing UMKM 1 halaman (lanjut Day 35).
- **Selesai jika:** Hero 360px tidak pecah; CTA 44px.

---

### 📅 Day 35 — Pricing, feature grid, social proof

- **Tujuan:** Grid jual + penekanan 1 paket.
- **Materi:** 3 kolom pricing; skala `md:-translate-y`; daftar cek; testimonial kartu.
- **Praktik:** Lanjut landing: pricing + 1 testimonial row.
- **Selesai jika:** Paket “populer” jelas tanpa mengandalkan warna saja.

---

### 📅 Day 36 — Tabel data + empty state

- **Tujuan:** Data terbaca di HP.
- **Materi:** `overflow-x-auto`; `thead` sticky opsional; badge kolom status; empty: ikon + teks + CTA; jangan tabel untuk layout.
- **Praktik:** Tabel 6 kolom dummy + empty variant.
- **Selesai jika:** HP scroll horizontal *hanya* di tabel, bukan seluruh halaman.

---

### 📅 Day 37 — REVIEW komponen + konsistensi spacing

- **Tujuan:** Rapikan sebelum overlay/dashboard.
- **Materi:** Audit `p-3` vs `p-4`; radius; shadow; dark.
- **Praktik:** Satukan Day 30–36 ke satu `ui.html` scroll.
- **Selesai jika:** 1 skala spasi (mis. kelipatan 4 / 8).

---

### 📅 Day 38 — Overlay: modal & drawer (konsep)

- **Tujuan:** Tahu pola, belum library React.
- **Materi:** `dialog` HTML vs `role="dialog"`; backdrop; `inert`/fokus trap (teori + 1 percobaan); `z-` stacking; drawer kiri/kanan.
- **Praktik:** Modal “konfirmasi hapus” bisa dibuka/ditutup *tanpa* TS dulu (`<dialog>`).
- **Selesai jika:** Esc/backdrop (jika didukung); fokus tidak hilang ke belakang (catat batasan).

---

### 📅 Day 39 — Dashboard shell: sidebar + main

- **Tujuan:** Layout app, bukan marketing.
- **Materi:** `min-h-dvh flex`; sidebar `hidden lg:flex w-64`; main `flex-1 min-w-0`; topbar HP; nav aktif `aria-current`.
- **Praktik:** Shell: 4 item nav + slot konten.
- **Selesai jika:** 360px = topbar + konten; 1024px = sidebar.

---

### 📅 Day 40 — Empty, loading, error **visual**

- **Tujuan:** Tiga keadaan selain “data oke”.
- **Materi:** Skeleton `animate-pulse`; empty; error + retry button (mati dulu); jangan spinner saja tanpa teks.
- **Praktik:** 3 state untuk 1 kartu daftar.
- **Selesai jika:** Ketiga state layout-nya tidak “loncat” parah.

---

### 📅 Day 41 — Image, aspect, overlay teks

- **Tujuan:** Foto produk/hero rapi.
- **Materi:** `aspect-video`/`aspect-square`; `object-cover`; `object-center`; overlay gradient; `sizes` konsep (Next Image nanti).
- **Praktik:** Grid 6 foto + 1 hero overlay.
- **Selesai jika:** Tidak gepeng; teks overlay kontras.

---

### 📅 Day 42 — Tipografi artikel + `@apply` / `@layer`

- **Tujuan:** Prose + tahu kapan utility diekstrak.
- **Materi:** Skala heading artikel; `max-w-prose`; plugin `@tailwindcss/typography` **opsional**; `@layer components` + `@apply`; bahaya `@apply` berantai; lebih baik komponen TSX nanti.
- **Praktik:** 1 artikel + 1 class `@apply` untuk tombol *hanya jika* terulang >3×.
- **Selesai jika:** Bisa jelaskan kapan *jangan* `@apply`.

---

### 📅 Day 43 — A11y + Tailwind (audit)

- **Tujuan:** Utility tidak otomatis aksesibel.
- **Materi:** Kontras palet default; `sr-only`; `focus-visible:ring`; skip-link; `motion-reduce:`.
- **Praktik:** Audit `ui.html` + landing: 10 temuan, perbaiki.
- **Selesai jika:** Tab order masuk akal; 0 `outline-none` tanpa ring.

---

### 📅 Day 44 — REVIEW design system (kitchen sink)

- **Tujuan:** Satu file “semua atom”.
- **Materi:** Inventaris: warna, tipe, tombol, input, kartu, badge, alert, tabel, nav.
- **Praktik:** `kitchen-sink.html` lengkap light/dark.
- **Selesai jika:** Token konsisten; bisa jadi acuan bulan Next.

---

### 📅 Day 45 — Spek proyek 2 halaman

- **Tujuan:** Marketing + dashboard, token sama.
- **Materi:** IA: `/` landing, `/app` dashboard (boleh 2 HTML); daftar section; breakpoint.
- **Praktik:** Wire (boleh grayscale) + daftar komponen yang dipakai ulang.
- **Selesai jika:** Spek 1 halaman tertulis.

---

### 📅 Day 46 — Proyek: header + footer kedua halaman

- **Praktik:** Chrome sama; tautan aktif beda.
- **Selesai jika:** Sticky header; footer tautan; 360px.

---

### 📅 Day 47 — Proyek: hero + social proof landing

- **Praktik:** Hero, logo cloud, 1 testimonial.
- **Selesai jika:** Overlay + CTA.

---

### 📅 Day 48 — Proyek: fitur + pricing

- **Praktik:** Grid fitur + 3 paket.
- **Selesai jika:** 1 paket featured.

---

### 📅 Day 49 — Proyek: form kontak + FAQ

- **Praktik:** Form Day 31 + `<details>`.
- **Selesai jika:** Label + fokus + FAQ keyboard.

---

### 📅 Day 50 — Proyek: dashboard topbar + sidebar

- **Praktik:** Shell Day 39 + 4 menu.
- **Selesai jika:** `lg:` sidebar.

---

### 📅 Day 51 — Proyek: stat cards + tabel

- **Praktik:** 4 stat + tabel + empty.
- **Selesai jika:** Tabel overflow lokal.

---

### 📅 Day 52 — Proyek: dark mode kedua halaman

- **Praktik:** Class `dark` + token; catat yang lolos kontras.
- **Selesai jika:** Tidak ada teks hilang di dark.

---

### 📅 Day 53 — Proyek: mobile pass 360px

- **Praktik:** Perbaiki overflow, tap target, menu.
- **Selesai jika:** Tidak scroll-x halaman.

---

### 📅 Day 54 — Proyek: a11y pass

- **Praktik:** Skip, heading, alt, kontras, fokus.
- **Selesai jika:** Checklist Day 43 hijau.

---

### 📅 Day 55 — Proyek: polish + Lighthouse cepat

- **Materi:** Performa gambar (kompres), heading, meta description.
- **Praktik:** Perbaiki 3 temuan terbesar (bukan kejar 100).
- **Selesai jika:** Live-ready.

---

### 📅 Day 56 — REVIEW + deploy bulan 2

- **Tujuan:** Dua halaman live, token sama.
- **Praktik:** Deploy; tulis catatan “CSS vs Tailwind” 10 baris.
- **Selesai jika:** URL; kitchen sink masih jadi sumber kebenaran.

**✅ Checkpoint:** Landing + dashboard Tailwind, dark, 360px, live.

---

# ═══════════════════════════════════════════
# BULAN 3 — TYPESCRIPT LANGSUNG (Day 57–84)
# ═══════════════════════════════════════════

> Tidak ada bulan JavaScript. Vite + `tsc` dari hari pertama. JS = hasil compile.

---

### 📅 Day 57 — Kenapa TypeScript + setup Vite TS

- **Tujuan:** Toolchain, bukan teori tipe dulu.
- **Materi:** TS = JS + tipe di-hapus saat compile; `tsconfig` `strict`; Vite `npm create vite` template vanilla-ts; `src/main.ts`; bukan file `.js` sumber; `npx tsc --noEmit`.
- **Praktik:** Hello di `#app`; error tipe sengaja, perbaiki.
- **Selesai jika:** Dev server + strict nyala.

---

### 📅 Day 58 — Tipe dasar, variabel, union, literal

- **Materi:** `string` `number` `boolean` `null` `undefined` `bigint`; `let`/`const`; inferensi; anotasi; union `string | number`; literal `'draft' | 'published'`; `as const` pengantar.
- **Praktik:** 15 fungsi kecil typed.
- **Selesai jika:** Tidak memakai `any`.

---

### 📅 Day 59 — Object, `type` vs `interface`, optional, readonly

- **Materi:** Index yang berlebihan dihindari; `type` alias vs `interface` (samakan dulu, pilih `type` untuk union); `?`; `readonly`; nested; excess property check.
- **Praktik:** Tipe `User`, `Project`; objek palsu.
- **Selesai jika:** Optional vs `undefined` eksplisit jelas.

---

### 📅 Day 60 — Fungsi typed

- **Materi:** Param, default, rest; return type; void vs undefined; callback typed; function overload *kenal saja*; jangan `Function`.
- **Praktik:** `formatRupiah`, `clamp`, handler klik bertipe.
- **Selesai jika:** Callback bukan `any`.

---

### 📅 Day 61 — Array + `map` / `filter` / `reduce` typed

- **Materi:** `T[]` vs `Array<T>`; tuple `[string, number]`; `readonly T[]`; predikat filter yang mempersempit; `reduce` dengan generic awal.
- **Praktik:** Olah daftar produk: filter stok, total harga, label.
- **Selesai jika:** `reduce` tidak jadi `any`.

---

### 📅 Day 62 — Narrowing & discriminated union

- **Materi:** `typeof`, `===`, `in`, truthiness; `if`/else; discriminated `kind:`; `never` di switch lengkap; `asserts` *kenal*.
- **Praktik:** `type Hasil = { ok: true; data: T } | { ok: false; error: string }`.
- **Selesai jika:** Switch exhaustive (error jika case baru lupa).

---

### 📅 Day 63 — Generics yang terpakai

- **Materi:** `<T>` pada fungsi; constraint `extends`; `Array<T>`, `Record<K,V>`, `Partial`, `Pick`, `Omit` (yang perlu); jangan generic “pamer”.
- **Praktik:** `wrap(value: T): { value: T }`; helper `pluck`.
- **Selesai jika:** Generic punya alasan, bukan copy StackOverflow.

---

### 📅 Day 64 — `unknown` vs `any`, JSON aman

- **Materi:** `any` mematikan cek; `unknown` wajib narrow; `JSON.parse` → `unknown`; type guard.
- **Praktik:** Parse string JSON user; tolak bentuk salah.
- **Selesai jika:** 0 `any`; parse gagal tidak meledak runtime tanpa pesan.

---

### 📅 Day 65 — Modul: pecah file

- **Materi:** `export`/`import`; default vs named (lebih named); `tsconfig` module; circular *hindari*; barrel `index.ts` hati-hati.
- **Praktik:** `types.ts`, `format.ts`, `main.ts`.
- **Selesai jika:** Satu tanggung jawab per file kecil.

---

### 📅 Day 66 — `async`/`await` + `fetch` typed

- **Materi:** Promise; `async` return `Promise<T>`; `await`; `fetch` + `res.ok`; jangan anggap JSON selalu valid (sambung Day 64/67).
- **Praktik:** GET JSON publik (atau file lokal `/public/data.json`).
- **Selesai jika:** Error jaringan ditangani; tipe data dideklarasikan.

---

### 📅 Day 67 — Zod (runtime + `z.infer`)

- **Tujuan:** Tipe compile ≠ data jaringan.
- **Materi:** `z.object`, array, optional; `.parse` vs `.safeParse`; `z.infer<typeof schema>`; kenapa ini penting sebelum Next/Laravel.
- **Praktik:** Schema `Produk`; parse fetch Day 66.
- **Selesai jika:** Data rusak → error terkontrol, bukan crash diam.

---

### 📅 Day 68 — Error: jangan ditelan

- **Materi:** `try/catch`; `unknown` di catch; type guard `err instanceof Error`; custom `class AppError`; jangan `catch {}` kosong; logging.
- **Praktik:** Bungkus fetch + tampil pesan ke UI (teks).
- **Selesai jika:** Gagal jaringan vs JSON invalid beda pesan.

---

### 📅 Day 69 — DOM dengan TypeScript

- **Materi:** `document.querySelector` → `Element | null`; generic `querySelector<HTMLInputElement>`; `as` terakhir; event `SubmitEvent`; `e.preventDefault`; `classList`; `dataset`.
- **Praktik:** Baca input, tulis ke `<ul>`; null-check.
- **Selesai jika:** Tidak ada `!` non-null sembarangan.

---

### 📅 Day 70 — REVIEW bahasa TypeScript

- **Materi:** Peta Day 57–69; kuis union, narrowing, Zod, DOM.
- **Praktik:** 10 soal + perbaiki kode ber-`any`.
- **Selesai jika:** `tsc --noEmit` hijau di latihan.

---

### 📅 Day 71 — Form typed: value, validasi, error UI

- **Materi:** Baca `FormData` atau `.value`; schema Zod; map error ke field; Tailwind error dari bulan 2.
- **Praktik:** Form kontak jalan di client (belum kirim server).
- **Selesai jika:** Submit invalid tidak “sukses palsu”.

---

### 📅 Day 72 — Render list `T[]` + empty/loading/error

- **Materi:** Satu sumber data; `innerHTML` vs `createElement` (XSS: jangan tempel string tak dipercaya); tiga state UI.
- **Praktik:** Daftar dari JSON + 3 state.
- **Selesai jika:** Loading tidak menimpa error.

---

### 📅 Day 73 — Filter/search: UI = data

- **Materi:** State `query`; `filter` typed; debounce *sederhana* (opsional); highlight *jangan* XSS.
- **Praktik:** Cari nama di daftar.
- **Selesai jika:** Kosong → empty state, bukan tabel hantu.

---

### 📅 Day 74 — `localStorage` + Zod

- **Materi:** `string` only; versioning kunci; parse Zod; kuota; jangan simpan rahasia.
- **Praktik:** Persist filter/favorit.
- **Selesai jika:** Data korup → fallback default.

---

### 📅 Day 75 — Debug TS

- **Materi:** Source map Vite; breakpoint; `tsc` error baca *sebelum* baris; narrowing dengan log.
- **Praktik:** Sengaja 3 bug, perbaiki dengan debugger bukan tebak.
- **Selesai jika:** Tahu beda error compile vs runtime.

---

### 📅 Day 76 — Mini proyek: spek dashboard filter

- **Materi:** Data `Transaksi[]`; kolom; filter status; Tailwind dashboard shell.
- **Praktik:** Spek + `types.ts` + JSON dummy.
- **Selesai jika:** Tipe dan schema Zod siap.

---

### 📅 Day 77 — Dashboard: layout + fetch

- **Praktik:** Shell + load JSON + loading.
- **Selesai jika:** Fetch typed + Zod.

---

### 📅 Day 78 — Dashboard: tabel + empty/error

- **Praktik:** Tabel; error retry; empty.
- **Selesai jika:** 3 state.

---

### 📅 Day 79 — Dashboard: filter + search

- **Praktik:** Status + teks; URL hash opsional.
- **Selesai jika:** Filter tidak mutate sumber mentah (salin array).

---

### 📅 Day 80 — Dashboard: pecah modul + a11y

- **Praktik:** `dom.ts` `api.ts` `filter.ts`; label, fokus.
- **Selesai jika:** 0 `any`; tab oke.

---

### 📅 Day 81 — Dashboard: localStorage + dark toggle

- **Praktik:** Persist preferensi; class `dark`.
- **Selesai jika:** Refresh tetap.

---

### 📅 Day 82 — Dashboard: polish 360/768/1280

- **Praktik:** Overflow tabel; tap.
- **Selesai jika:** Tidak scroll-x.

---

### 📅 Day 83 — Latihan terpadu TS

- **Praktik:** Soal: narrowing, generic kecil, Zod, DOM event.
- **Selesai jika:** Semua compile.

---

### 📅 Day 84 — REVIEW + deploy dashboard TS

- **Praktik:** Deploy Vite; README cara jalan.
- **Selesai jika:** Live; strict; hampir 0 `any`.

**✅ Checkpoint:** Dashboard TS + Tailwind, fetch/Zod, live.

---

# ═══════════════════════════════════════════
# BULAN 4 — NEXT.JS I (Day 85–112)
# ═══════════════════════════════════════════

> React diajarkan **di dalam** Next. App Router. Server Component default.

---

### 📅 Day 85 — Next vs Vite: kapan server

- **Materi:** SSR/RSC vs SPA; routing file; kapan masih Vite; biaya server; Vercel vs static.
- **Praktik:** Tulis 10 baris “kapan Next” / “kapan HTML+TS”.
- **Selesai jika:** Bisa jelaskan kenapa katalog SEO-friendly cocok Next.

---

### 📅 Day 86 — `create-next-app`: TS + Tailwind + App Router

- **Materi:** Opsi CLI; `app/`; `layout.tsx` `page.tsx`; `globals.css` + Tailwind; `next dev` `build`.
- **Praktik:** Proyek baru; hapus boilerplate berlebih; 1 heading.
- **Selesai jika:** `npm run build` hijau kosong-berisi.

---

### 📅 Day 87 — TSX, komponen, props typed

- **Materi:** JSX = `React.createElement` (intuisi); rules of hooks *nanti*; function component; `type Props`; `children: React.ReactNode`; pecah file; jangan class component.
- **Praktik:** `<Button>`, `<Card>` Tailwind dari kitchen sink.
- **Selesai jika:** Props wajib tertangkap compiler.

---

### 📅 Day 88 — State klien: `useState`, event, controlled input

- **Materi:** `"use client"` kapan; `useState`; event `onClick` `onChange`; controlled vs uncontrolled; jangan state untuk data server yang sudah di page.
- **Praktik:** Counter + 1 input terkontrol.
- **Selesai jika:** Input tidak “lawan” state.

---

### 📅 Day 89 — List, `key`, loading/empty/error UI

- **Materi:** `map`; `key` stabil (bukan index jika urutan berubah); conditional render; jangan `&&` jebakan `0`.
- **Praktik:** Daftar dummy 3 state (state lokal dulu).
- **Selesai jika:** Key benar; empty terlihat.

---

### 📅 Day 90 — File routing: `page`, `layout`, folder = URL

- **Materi:** `app/about/page.tsx` → `/about`; `layout` bersarang; `template` kenal; trailing slash; grup `(marketing)` tanpa URL.
- **Praktik:** Home, about, kontak (statis).
- **Selesai jika:** 3 URL + nav `Link` besok — hari ini `<a>` dulu atau `Link` pengantar.

---

### 📅 Day 91 — Layout bersarang + navbar Tailwind

- **Materi:** `app/layout.tsx` font; navbar komponen; `children`; footer.
- **Praktik:** Chrome dari bulan 2.
- **Selesai jika:** Semua halaman punya nav sama.

---

### 📅 Day 92 — Server vs `"use client"` — hemat client

- **Materi:** RSC default tidak ada `useState`; batas: event, browser API; polar: leaf client, page server; bundle.
- **Praktik:** Page server + 1 client widget (toggle).
- **Selesai jika:** Tidak seluruh app `"use client"`.

---

### 📅 Day 93 — Dynamic `[id]` + `not-found`

- **Materi:** `app/produk/[id]/page.tsx`; `params` (async params versi Next baru — ikuti docs yang terpasang); `notFound()`; `generateStaticParams` pengantar.
- **Praktik:** 3 produk dummy; id salah → 404.
- **Selesai jika:** Detail & 404 jalan.

---

### 📅 Day 94 — `loading.tsx` / `error.tsx`

- **Materi:** Suspense boundary file; `error.tsx` client; `reset()`; beda 404 vs 500.
- **Praktik:** Loading skeleton Tailwind; error dummy.
- **Selesai jika:** Refresh error tidak blank putih saja.

---

### 📅 Day 95 — `async` page + `lib/data.ts` typed

- **Materi:** Fetch di server; jangan expose secret; tipe + Zod di batas; delay palsu untuk lihat `loading`.
- **Praktik:** Daftar dari `lib/data.ts` (array dulu, bukan DB).
- **Selesai jika:** Page async; tipe ketat.

---

### 📅 Day 96 — `next/link`, `next/image`, `next/font`

- **Materi:** Prefetch `Link`; `Image` `width/height` `alt` `sizes`; font `localFont` / Google via `next/font` (tanpa FOUT liar).
- **Praktik:** Nav Link; 3 Image; font di layout.
- **Selesai jika:** Tidak `<img>` mentah untuk foto besar.

---

### 📅 Day 97 — Metadata

- **Materi:** `metadata` object / `generateMetadata`; `title.template`; description; jangan duplikat h1 vs title tanpa sadar.
- **Praktik:** Title beda per halaman.
- **Selesai jika:** Tab browser benar.

---

### 📅 Day 98 — REVIEW App Router

- **Praktik:** Kuis RSC vs client; gambar peta folder; perbaiki proyek.
- **Selesai jika:** Bisa jelaskan [id], layout, loading.

---

### 📅 Day 99 — Katalog: model data + `lib/data`

- **Praktik:** Tipe `Produk`; 8–12 item; kategori.
- **Selesai jika:** Zod/schema atau tipe + guard.

---

### 📅 Day 100 — Katalog: halaman daftar + kartu

- **Praktik:** Grid Tailwind; Link ke detail.
- **Selesai jika:** Kartu pakai Image.

---

### 📅 Day 101 — Katalog: filter kategori (server atau searchParams)

- **Materi:** `searchParams` di page; jangan overfetch klien jika bisa server.
- **Praktik:** `?kategori=`
- **Selesai jika:** Filter shareable via URL.

---

### 📅 Day 102 — Katalog: search nama

- **Praktik:** Input + URL `q=`; debounce opsional client kecil.
- **Selesai jika:** Empty hasil.

---

### 📅 Day 103 — Katalog: halaman detail

- **Praktik:** `[id]` lengkap: deskripsi, harga, back link.
- **Selesai jika:** `generateMetadata` judul produk.

---

### 📅 Day 104 — Katalog: `not-found` + empty daftar

- **Praktik:** UI 404 branded; empty filter.
- **Selesai jika:** Tidak stack trace ke user.

---

### 📅 Day 105 — Katalog: loading/error boundaries

- **Praktik:** Skeleton grid; error.tsx.
- **Selesai jika:** Terlihat di soft-nav.

---

### 📅 Day 106 — Katalog: a11y + heading

- **Praktik:** 1 h1; alt; fokus.
- **Selesai jika:** Landmark beres.

---

### 📅 Day 107 — Katalog: 360px pass

- **Praktik:** Grid 1 kolom; tap.
- **Selesai jika:** Tidak overflow.

---

### 📅 Day 108 — Katalog: dark mode

- **Praktik:** Token + `dark:`; toggle client kecil *atau* class statis dulu.
- **Selesai jika:** Detail + daftar konsisten.

---

### 📅 Day 109 — Katalog: polish copy + empty illustrations

- **Praktik:** Microcopy ID.
- **Selesai jika:** Terasa produk, bukan lorem mentah semua.

---

### 📅 Day 110 — Katalog: `next build` perbaiki warning

- **Praktik:** Image, key, metadata.
- **Selesai jika:** Build tanpa error.

---

### 📅 Day 111 — Latihan terpadu katalog

- **Praktik:** Soal: tambah field, pecah komponen, 1 bug routing.
- **Selesai jika:** Build tetap hijau.

---

### 📅 Day 112 — REVIEW Next I

- **Praktik:** Cheatsheet App Router; catat utang API (bulan 5).
- **Selesai jika:** Katalog lokal solid.

**✅ Checkpoint:** Katalog Next, build hijau. Belum wajib API luar.

---

# ═══════════════════════════════════════════
# BULAN 5 — NEXT.JS II (Day 113–140)
# ═══════════════════════════════════════════

---

### 📅 Day 113 — Route Handler `app/api/...`

- **Materi:** `route.ts` `GET`/`POST`; `NextResponse.json`; typed body; status 400/404/500; jangan taruh secret di client.
- **Praktik:** `GET /api/produk` dari data yang sama.
- **Selesai jika:** JSON valid; tipe response.

---

### 📅 Day 114 — Server Actions vs Route Handler

- **Materi:** Action `use server`; form progressive; kapan tetap REST (kontrak Laravel/Go/Rust); **pilih 1 gaya utama** untuk proyek bulan ini (disarankan Route Handler agar mudah di-port).
- **Praktik:** POST item ke memori/file *atau* array module (reset on reload — catat).
- **Selesai jika:** Tahu trade-off 10 baris.

---

### 📅 Day 115 — Validasi Zod di **server**

- **Materi:** Jangan percaya body; `safeParse`; pesan field; 422 vs 400.
- **Praktik:** POST ditolak jika nama kosong.
- **Selesai jika:** Client tidak bisa bypass dengan DevTools tanpa ditolak server.

---

### 📅 Day 116 — Environment variables

- **Materi:** `.env.local`; `NEXT_PUBLIC_*` terekspos; secret hanya server; contoh Vercel; jangan commit `.env`.
- **Praktik:** Baca `API_SECRET` di route; gagal jika hilang.
- **Selesai jika:** Client bundle tidak mengandung secret (cek mental).

---

### 📅 Day 117 — Cache & revalidate (praktis)

- **Materi:** `fetch` cache Next; `revalidate`; `no-store` untuk data user; jangan hafal semua flag — 3 kasus: statis, ISR, dinamis.
- **Praktik:** 1 route statis vs 1 dinamis.
- **Selesai jika:** Bisa jelaskan kenapa data “basi”.

---

### 📅 Day 118 — Middleware

- **Materi:** `middleware.ts` edge; `matcher`; redirect; jangan berat (DB); auth *gambaran*.
- **Praktik:** Redirect `/admin` → `/` jika flag env off.
- **Selesai jika:** Matcher tidak menelan `/_next`.

---

### 📅 Day 119 — Form produksi

- **Materi:** Pending (`useFormStatus` / state); disable double submit; error object per field; sukses toast sederhana.
- **Praktik:** Form tambah produk → API → list refresh (router.refresh).
- **Selesai jika:** Double click tidak dobel data *semampunya*.

---

### 📅 Day 120 — Custom hook tipis

- **Materi:** `use*` hanya client; jangan hook untuk fetch server; extract jika ≥2 komponen.
- **Praktik:** `useMediaQuery` atau `useDebouncedValue` — 1 saja.
- **Selesai jika:** Bukan `useFetch` yang menyembunyikan error.

---

### 📅 Day 121 — REVIEW data & form

- **Praktik:** Kuis env, Zod server, cache, middleware.
- **Selesai jika:** Catatan 1 halaman.

---

### 📅 Day 122 — Spek mini CRUD

- **Materi:** Resource `Catatan` atau `Tugas`: field, validasi, empty.
- **Praktik:** Spek + tipe + schema.
- **Selesai jika:** Kontrak API tertulis (path, status).

---

### 📅 Day 123 — CRUD: GET list + UI

- **Praktik:** Page + fetch server/handler.
- **Selesai jika:** Empty state.

---

### 📅 Day 124 — CRUD: GET detail

- **Praktik:** `[id]` + 404.
- **Selesai jika:** Metadata.

---

### 📅 Day 125 — CRUD: POST create

- **Praktik:** Form + Zod server.
- **Selesai jika:** Validasi field.

---

### 📅 Day 126 — CRUD: PATCH/PUT update

- **Praktik:** Form edit; 404 id.
- **Selesai jika:** Partial vs full sadar.

---

### 📅 Day 127 — CRUD: DELETE

- **Praktik:** Konfirmasi modal `<dialog>` atau halaman.
- **Selesai jika:** 204/200 + list update.

---

### 📅 Day 128 — CRUD: error & a11y form

- **Praktik:** Pesan, fokus error.
- **Selesai jika:** Screen-reader-friendly labels.

---

### 📅 Day 129 — CRUD: env + tidak persist (catat utang DB)

- **Materi:** Data hilang saat restart = wajar; Laravel nanti.
- **Praktik:** README jujur.
- **Selesai jika:** Build hijau.

---

### 📅 Day 130 — CRUD: 360/dark polish

- **Praktik:** UI bulan 2.
- **Selesai jika:** 3 viewport.

---

### 📅 Day 131 — CRUD: pecah komponen + types

- **Praktik:** Folder `components/` `lib/`.
- **Selesai jika:** Page tipis.

---

### 📅 Day 132 — CRUD: tes manual checklist

- **Praktik:** 15 skenario: valid, invalid, 404, empty.
- **Selesai jika:** Checklist tercetak.

---

### 📅 Day 133 — Deploy Vercel

- **Materi:** Git connect; env dashboard; preview vs prod.
- **Praktik:** URL preview + prod.
- **Selesai jika:** Build Vercel hijau.

---

### 📅 Day 134 — Debug production

- **Materi:** Env hilang; log Function; hydration mismatch (class dark).
- **Praktik:** Sengaja salah env di preview, perbaiki.
- **Selesai jika:** Tahu baca log Vercel.

---

### 📅 Day 135 — Auth gambaran

- **Materi:** Session vs JWT vs cookie httpOnly; NextAuth/Auth.js nama saja; **implementasi penuh di Laravel + bulan 13**.
- **Praktik:** Diagram 1 halaman “login nanti”.
- **Selesai jika:** Tidak pasang auth palsu yang tidak aman lalu dikira selesai.

---

### 📅 Day 136 — SEO + Open Graph

- **Materi:** `openGraph` `twitter`; `robots`; sitemap *pengantar*; canonical.
- **Praktik:** OG title/description katalog.
- **Selesai jika:** Preview debugger *atau* meta terpasang.

---

### 📅 Day 137 — Performa

- **Materi:** Waterfall; Image; dynamic import *hati-hati*; bundle analyzer kenal; jangan optimisasi buta.
- **Praktik:** Perbaiki 1 image + 1 client berlebih.
- **Selesai jika:** Catat before/after kasar.

---

### 📅 Day 138 — Latihan terpadu Next II

- **Praktik:** Tambah query + 1 bug cache.
- **Selesai jika:** Build hijau.

---

### 📅 Day 139 — Polish 360/768/1280 + a11y

- **Praktik:** Pass akhir UI.
- **Selesai jika:** Checklist.

---

### 📅 Day 140 — REVIEW Next + URL live

- **Praktik:** Tulis “API kontrak v0” untuk Laravel.
- **Selesai jika:** Produksi Vercel + catatan kontrak.

**✅ Checkpoint:** Next live, CRUD API routes, siap disambung Laravel.

---

# ═══════════════════════════════════════════
# BULAN 6 — LARAVEL I (Day 141–168)
# ═══════════════════════════════════════════

> PHP hanya yang dipakai Laravel. Bukan semester PHP prosedural.

---

### 📅 Day 141 — Kenapa Laravel (vs Go/Rust nanti)

- **Materi:** Batteries: ORM, auth, queue, mail; arti “produktif”; biaya runtime PHP; kapan *jangan* (CLI ketat, memori).
- **Praktik:** Tabel 8 baris banding Laravel/Go/Rust (isi Go/Rust masih hipotesis).
- **Selesai jika:** Alasan bulan Laravel jelas.

---

### 📅 Day 142 — Composer, `laravel new`, struktur, `.env`

- **Materi:** Composer; folder `app` `routes` `database` `resources`; `.env` vs `.env.example`; `APP_KEY`; `php artisan`; Vite + Tailwind di Laravel.
- **Praktik:** Proyek baru jalan di `php artisan serve`.
- **Selesai jika:** Halaman welcome + mengerti `.env`.

---

### 📅 Day 143 — Routing + controller

- **Materi:** `routes/web.php` `api.php`; verb; parameter; `Route::resource`; controller invokable vs resource; thin controller.
- **Praktik:** 3 route + 1 resource controller kosong.
- **Selesai jika:** `route:list` dibaca.

---

### 📅 Day 144 — Blade + komponen + Tailwind

- **Materi:** `{{ }}` escape vs `{!! !!}` (XSS); `@if` `@foreach`; layout `@extends` / komponen `<x-layout>`; slot; Breeze opsional nanti; Vite `@vite`.
- **Praktik:** Layout Tailwind + 1 halaman Blade.
- **Selesai jika:** XSS: data user di-escape.

---

### 📅 Day 145 — Request lifecycle + middleware

- **Materi:** Kernel/bootstrap; middleware global vs group; `VerifyCsrfToken` untuk web; throttle kenal; custom middleware 1 header.
- **Praktik:** Middleware log path (monolog).
- **Selesai jika:** Gambar alur request 6 kotak.

---

### 📅 Day 146 — Eloquent: model, migrasi, relasi

- **Materi:** Migrasi `Schema`; `$fillable` vs `$guarded`; `hasMany`/`belongsTo`; timestamps; soft delete *kenal*; N+1 `with()`.
- **Praktik:** `Category` `Product` + FK.
- **Selesai jika:** Relasi jalan di tinker.

---

### 📅 Day 147 — CRUD web + `FormRequest`

- **Materi:** Resource controller penuh; validasi rules; pesan ID; PRG redirect; `@csrf`; method spoof `PUT/DELETE`.
- **Praktik:** CRUD produk Blade.
- **Selesai jika:** Validasi server; mass assignment aman.

---

### 📅 Day 148 — Seeder & factory

- **Materi:** `factory()`; `fake()`; `DatabaseSeeder`; state factory.
- **Praktik:** 3 kategori, 15 produk.
- **Selesai jika:** `migrate:fresh --seed` berulang aman.

---

### 📅 Day 149 — REVIEW MVC Laravel

- **Praktik:** Kuis lifecycle, fillable, CSRF, N+1.
- **Selesai jika:** CRUD web kamu jelaskan layer.

---

### 📅 Day 150 — API routes + JSON Resource

- **Materi:** `routes/api.php` prefix `/api`; `ApiResource`; wrapping `data`; status; auth *besok bulan*; CORS kenal.
- **Praktik:** GET list/detail JSON typed-ish (Resource).
- **Selesai jika:** Bentuk JSON stabil.

---

### 📅 Day 151 — Pagination + filter query

- **Materi:** `paginate()` vs `simplePaginate`; query string; filter `when()`; indexing *gambaran*.
- **Praktik:** `?q=` `?category=`.
- **Selesai jika:** Meta pagination ada.

---

### 📅 Day 152 — Upload + Storage

- **Materi:** `store()` disk `public`; `storage:link`; validasi `image|max:`; jangan percaya ekstensi; URL `Storage::url`.
- **Praktik:** Foto produk.
- **Selesai jika:** File di luar `public/` mentah tanpa link.

---

### 📅 Day 153 — Error & logging

- **Materi:** `report()`; `APP_DEBUG` prod = berbahaya; page 500; `Log::`; jangan log secret.
- **Praktik:** 1 exception custom + log.
- **Selesai jika:** Debug off mensimulasikan prod lokal.

---

### 📅 Day 154 — Proyek toko: spek + migrasi final

- **Praktik:** Spek kategori/produk; migrasi rapi.
- **Selesai jika:** ERD ASCII.

---

### 📅 Day 155 — Proyek: model + factory lengkap

- **Praktik:** Relasi, seed realistis.
- **Selesai jika:** Tinker query 3 relasi.

---

### 📅 Day 156 — Proyek: CRUD Blade kategori

- **Selesai jika:** Validasi + flash message.

---

### 📅 Day 157 — Proyek: CRUD Blade produk + upload

- **Selesai jika:** Gambar tampil.

---

### 📅 Day 158 — Proyek: index filter + paginate

- **Selesai jika:** Query string tahan.

---

### 📅 Day 159 — Proyek: API Resource list/detail

- **Selesai jika:** Kontrak field tertulis.

---

### 📅 Day 160 — Proyek: API create/update/delete

- **Materi:** 401 belum; validasi JSON.
- **Selesai jika:** Postman/Insomnia koleksi.

---

### 📅 Day 161 — Proyek: Tailwind UI index/show

- **Praktik:** Kartu + tabel dari bulan 2.
- **Selesai jika:** 360px.

---

### 📅 Day 162 — Proyek: form UI + error Blade

- **Selesai jika:** `@error` + old input.

---

### 📅 Day 163 — Proyek: empty/error pages

- **Praktik:** 404 branded.
- **Selesai jika:** Tidak stack ke user (debug off).

---

### 📅 Day 164 — Proyek: N+1 cek + `with()`

- **Praktik:** Debugbar *atau* log query.
- **Selesai jika:** List tidak 1+N query.

---

### 📅 Day 165 — Proyek: polish + kebijakan folder

- **Praktik:** Policy *stub* (isi Day 170).
- **Selesai jika:** README artisan.

---

### 📅 Day 166 — Proyek: tes manual + seed ulang

- **Selesai jika:** Checklist CRUD.

---

### 📅 Day 167 — Latihan terpadu Laravel I

- **Praktik:** Tambah field + migrasi baru.
- **Selesai jika:** `migrate` bersih.

---

### 📅 Day 168 — REVIEW Laravel I

- **Praktik:** Cheatsheet artisan; siapkan auth bulan 7.
- **Selesai jika:** CRUD + API tanpa auth, UI Tailwind.

**✅ Checkpoint:** Toko Laravel + DB + JSON API.

---

# ═══════════════════════════════════════════
# BULAN 7 — LARAVEL II (Day 169–196)
# ═══════════════════════════════════════════

---

### 📅 Day 169 — Auth: Breeze / Fortify

- **Materi:** Session cookie; register/login/logout; hash password; email verifikasi *opsional*; scaffolding Breeze Blade+Tailwind *atau* API saja.
- **Praktik:** Auth jalan lokal.
- **Selesai jika:** Password tidak tersimpan plain.

---

### 📅 Day 170 — Policy & gate (IDOR)

- **Materi:** `authorize`; policy `update`; IDOR: user A ubah milik B; `403`.
- **Praktik:** Produk `user_id`; tes manual dua user.
- **Selesai jika:** IDOR tertutup di web + catat untuk API.

---

### 📅 Day 171 — Sanctum: token / SPA

- **Materi:** SPA cookie vs token personal; CSRF SPA; `HasApiTokens`.
- **Praktik:** Token login API *atau* Sanctum SPA doc.
- **Selesai jika:** `/api/user` butuh auth.

---

### 📅 Day 172 — Next konsumsi Laravel

- **Materi:** CORS `config/cors.php`; `NEXT_PUBLIC_API_URL`; cookie vs `Authorization`; env Vercel + API host.
- **Praktik:** Katalog Next (bulan 5) baca produk Laravel.
- **Selesai jika:** List live dari BE (lokal dulu).

---

### 📅 Day 173 — Job & queue

- **Materi:** `ShouldQueue`; driver `database`; `jobs` table; kapan sync.
- **Praktik:** Job “resize/log produk baru”.
- **Selesai jika:** `queue:work` memproses 1 job.

---

### 📅 Day 174 — Mail / notifikasi

- **Materi:** Mailtrap / log driver; Mailable; jangan kirim asli ke orang random.
- **Praktik:** Email “produk dibuat” ke log.
- **Selesai jika:** Template Blade email.

---

### 📅 Day 175 — Scheduler

- **Materi:** `Kernel` schedule; cron `schedule:run`; timezone.
- **Praktik:** Command tutup “draft lama” *dummy*.
- **Selesai jika:** `schedule:list`.

---

### 📅 Day 176 — Feature test HTTP

- **Materi:** `phpunit`/`pest` (pilih 1); `$this->get/post`; `assertStatus`; actingAs.
- **Praktik:** Tes list, create invalid, IDOR.
- **Selesai jika:** `php artisan test` hijau.

---

### 📅 Day 177 — REVIEW auth + API

- **Praktik:** Diagram Next ↔ Sanctum ↔ Policy.
- **Selesai jika:** 3 tes penting ada.

---

### 📅 Day 178 — Proyek FE+BE: spek tetap

- **Praktik:** Tulis OpenAPI kasar / tabel endpoint (ini kontrak ke Go/Rust).
- **Selesai jika:** Field + status code.

---

### 📅 Day 179 — Proyek: auth Next (login form → API)

- **Praktik:** Simpan token *atau* cookie sesuai pilihan Day 171; jangan `localStorage` jika bisa httpOnly (catat trade-off).
- **Selesai jika:** Login/logout.

---

### 📅 Day 180 — Proyek: list/detail dari Laravel

- **Selesai jika:** Empty/error.

---

### 📅 Day 181 — Proyek: create dari Next

- **Selesai jika:** Zod FE + validasi BE.

---

### 📅 Day 182 — Proyek: update + delete + policy

- **Selesai jika:** 403 ditampilkan.

---

### 📅 Day 183 — Proyek: upload via API (jika perlu) atau skip sadar

- **Selesai jika:** Keputusan tertulis.

---

### 📅 Day 184 — Proyek: pagination UI Next

- **Selesai jika:** `?page=` sinkron.

---

### 📅 Day 185 — Proyek: filter UI = query BE

- **Selesai jika:** Tidak filter hanya di client untuk data besar.

---

### 📅 Day 186 — Proyek: loading/error Next

- **Selesai jika:** 401 → login.

---

### 📅 Day 187 — Proyek: tes feature tambahan

- **Selesai jika:** Cover auth + CRUD.

---

### 📅 Day 188 — Proyek: Tailwind polish kedua sisi

- **Selesai jika:** 360px.

---

### 📅 Day 189 — Proyek: seed demo + README

- **Selesai jika:** Orang lain `migrate --seed` + `npm run dev`.

---

### 📅 Day 190 — Proyek: checklist keamanan

- **Materi:** CSRF web, mass assignment, validasi, secret, debug off.
- **Selesai jika:** Checklist 10 poin.

---

### 📅 Day 191 — Deploy Laravel

- **Materi:** Forge / Pail / Railway / VPS; `APP_ENV=production`; `APP_DEBUG=false`; migrate; `storage` permission; HTTPS.
- **Praktik:** URL API live (pilih platform).
- **Selesai jika:** `/api/health` atau list jalan.

---

### 📅 Day 192 — Queue worker di production

- **Materi:** Supervisor gambaran; restart deploy; failed jobs.
- **Praktik:** 1 job jalan di prod *atau* dokumen kenapa sync.
- **Selesai jika:** Keputusan eksplisit.

---

### 📅 Day 193 — Latihan terpadu

- **Praktik:** Endpoint baru harus FE+BE+tes.
- **Selesai jika:** Kontrak di-update.

---

### 📅 Day 194 — Hardening

- **Materi:** Rate limit API; CORS ketat; `APP_KEY`; headers.
- **Praktik:** Perbaiki 3 temuan.
- **Selesai jika:** Debug off terbukti.

---

### 📅 Day 195 — Tulis kontrak API v1 (kanonik)

- **Materi:** Path, method, body, error shape `{ message, errors? }`, auth header, pagination meta — **ini file suci untuk Go & Rust**.
- **Praktik:** `docs/api-v1.md`.
- **Selesai jika:** Cukup untuk reimplement tanpa baca PHP.

---

### 📅 Day 196 — REVIEW Laravel + URL

- **Selesai jika:** Next + Laravel live + `api-v1.md`.

**✅ Checkpoint:** Pasangan FE/BE pertama selesai; kontrak siap di-port.

---

# ═══════════════════════════════════════════
# BULAN 8 — GOLANG I (Day 197–224)
# ═══════════════════════════════════════════

---

### 📅 Day 197 — Kenapa Go

- **Materi:** 1 binary; `gofmt`; kompilasi cepat; concurrency resmi; kurang “magic” vs Laravel; GC; kapan Rust lebih masuk.
- **Praktik:** Instal `go`; `hello` `go run`.
- **Selesai jika:** Versi Go tercatat.

---

### 📅 Day 198 — Budaya: modules, fmt, test

- **Materi:** `go mod init`; `gofmt`/`go fmt`; `go test`; `go vet`; jangan commit unformatted.
- **Praktik:** Repo `modul` + tes `1+1`.
- **Selesai jika:** `go test ./...` hijau.

---

### 📅 Day 199 — Tipe, slice, map, pointer, struct, method (padat)

- **Materi:** `int` `string` `bool`; slice vs array; `append` backing array; `map` zero value; pointer `&` `*`; nil; struct; method value vs pointer receiver; zero value berguna.
- **Praktik:** 10 latihan kecil (bukan 10 hari).
- **Selesai jika:** Tahu slice sharing bug klasik.

---

### 📅 Day 200 — Interface kecil + error nilai

- **Materi:** Interface implicit; `error`; `fmt.Errorf` `%w`; `errors.Is`/`As`; jangan `panic` untuk request; sentinel.
- **Praktik:** Fungsi `ParseID` return error.
- **Selesai jika:** Bisa wrap + cek.

---

### 📅 Day 201 — Package & ekspor

- **Materi:** Huruf besar publik; `internal/`; hindari package `utils` dewa; cyclic import.
- **Praktik:** `cmd/` vs `internal/app`.
- **Selesai jika:** Layout folder masuk akal.

---

### 📅 Day 202 — Table-driven test

- **Materi:** `t.Run`; slice case; `t.Helper`; golden *opsional*; coverage bukan tujuan.
- **Praktik:** Tes `ParseID` 8 kasus.
- **Selesai jika:** Gagal 1 case pesan jelas.

---

### 📅 Day 203 — Goroutine yang benar

- **Materi:** `go f()`; leak; `WaitGroup`; jangan goroutine tanpa batas per request.
- **Praktik:** Worker tetap 4, bukan 10.000.
- **Selesai jika:** Program selesai, tidak hang.

---

### 📅 Day 204 — Channel + `select` + timeout

- **Materi:** Unbuffered vs buffered; close; range; `select` `default`; timeout via `time.After` / context besok.
- **Praktik:** Fan-in 2 channel.
- **Selesai jika:** Tidak deadlock (sengaja lalu perbaiki).

---

### 📅 Day 205 — `context.Context`

- **Materi:** `WithCancel` `WithTimeout`; value *jarang*; teruskan ctx di API; cancel DB nanti.
- **Praktik:** HTTP *preview* timeout 1s.
- **Selesai jika:** Timeout membatalkan kerja palsu.

---

### 📅 Day 206 — `go test -race`

- **Materi:** Data race; mutex; jangan share map tanpa lock; race detector.
- **Praktik:** Tes yang race, perbaiki.
- **Selesai jika:** `-race` bersih di latihan.

---

### 📅 Day 207 — REVIEW bahasa Go

- **Praktik:** Kuis slice, error, ctx, race.
- **Selesai jika:** Catatan 1 halaman.

---

### 📅 Day 208 — `net/http` + JSON

- **Materi:** `http.Handler`; `ServeMux` Go 1.22+ method+path; `json.Encoder`; status; `Decode` body limit.
- **Praktik:** GET/POST JSON memori.
- **Selesai jika:** 400 body rusak.

---

### 📅 Day 209 — Router chi + middleware

- **Materi:** chi (atau mux standar jika cukup); logger; recover; request ID; middleware chain.
- **Praktik:** `GET /health`; log setiap request.
- **Selesai jika:** Panic → 500, proses hidup.

---

### 📅 Day 210 — Layer handler → service → store

- **Materi:** Deps inject struct; interface store kecil; jangan DB di handler.
- **Praktik:** In-memory store + tes handler.
- **Selesai jika:** 3 layer folder.

---

### 📅 Day 211 — Latihan: health + version + JSON error shape

- **Praktik:** Samakan error `{ "message": }` dengan `api-v1.md`.
- **Selesai jika:** Bentuk error sama Laravel.

---

### 📅 Day 212 — Latihan: list/detail memori

- **Selesai jika:** 404 konsisten.

---

### 📅 Day 213 — Latihan: create + validasi manual

- **Materi:** Validasi field; 422.
- **Selesai jika:** Tes table-driven.

---

### 📅 Day 214 — Latihan: update/delete

- **Selesai jika:** Idempotent delete sadar (404 vs 204).

---

### 📅 Day 215 — Latihan: middleware auth API key dulu

- **Praktik:** Header `X-API-Key`.
- **Selesai jika:** 401 tanpa kunci.

---

### 📅 Day 216 — Latihan: tes `httptest`

- **Selesai jika:** Tanpa listen port.

---

### 📅 Day 217 — Latihan: context timeout di handler

- **Selesai jika:** 504/503 pilihan sadar.

---

### 📅 Day 218 — Latihan: graceful shutdown

- **Materi:** `signal`, `Shutdown`.
- **Selesai jika:** Ctrl+C rapi.

---

### 📅 Day 219 — Latihan: pecah package + gofmt CI mental

- **Selesai jika:** `gofmt -l` kosong.

---

### 📅 Day 220 — Latihan: race tes handler + map store

- **Selesai jika:** Mutex/store aman, `-race` bersih.

---

### 📅 Day 221 — Latihan: README + curl contoh

- **Selesai jika:** Orang lain jalanin.

---

### 📅 Day 222 — Latihan: bandingkan kode Laravel resource vs Go

- **Praktik:** Tabel 10 baris.
- **Selesai jika:** Jujur mana yang lebih cepat ditulis.

---

### 📅 Day 223 — Latihan terpadu HTTP Go

- **Praktik:** 1 endpoint baru + tes.
- **Selesai jika:** Hijau.

---

### 📅 Day 224 — REVIEW Go I

- **Selesai jika:** Handler + tes + race bersih, belum wajib SQL.

**✅ Checkpoint:** API memori idiomatik Go.

---

# ═══════════════════════════════════════════
# BULAN 9 — GOLANG II (Day 225–252)
# ═══════════════════════════════════════════

---

### 📅 Day 225 — `database/sql` + SQLite/Postgres

- **Materi:** Driver; `Open`; pool `SetMaxOpenConns`; `Query`/`Exec`/`QueryRow`; `sql.Null*`; jangan string-concat SQL.
- **Praktik:** Tabel produk SQLite dulu (pindah Postgres mudah).
- **Selesai jika:** CRUD SQL mentah 1 entitas.

---

### 📅 Day 226 — sqlc

- **Materi:** SQL → Go typed; `sqlc.yaml`; query named; no ORM magic.
- **Praktik:** Generate Get/List/Insert.
- **Selesai jika:** Regenerasi setelah ubah SQL.

---

### 📅 Day 227 — Migrasi (goose / golang-migrate)

- **Materi:** Up/down; versi; jangan edit migrasi lama yang sudah deploy.
- **Praktik:** 2 migrasi: create + index.
- **Selesai jika:** Up/down berulang.

---

### 📅 Day 228 — CRUD + `httptest` + DB tes

- **Materi:** Tes vs DB file temp / tx rollback.
- **Praktik:** Tes list/create.
- **Selesai jika:** Tes tidak saling kotor.

---

### 📅 Day 229 — Config/env + structured log

- **Materi:** `os.Getenv`; `log/slog`; level; jangan log body password.
- **Praktik:** `PORT`, `DATABASE_URL`, `API_KEY`.
- **Selesai jika:** Missing env = gagal start (fail fast).

---

### 📅 Day 230 — Port API Laravel → Go

- **Materi:** `docs/api-v1.md` sebagai spek; status & nama field **sama**.
- **Praktik:** List/detail/create produk.
- **Selesai jika:** Kontrak lulus checklist.

---

### 📅 Day 231 — Next ganti `baseURL` ke Go

- **Praktik:** Env; CORS Go; tanpa ubah spek FE.
- **Selesai jika:** UI yang sama hidup.

---

### 📅 Day 232 — REVIEW SQL + port

- **Praktik:** Diff Laravel vs Go: auth, validasi, error, migrasi.
- **Selesai jika:** Daftar gap tertulis (auth user vs API key, dsb.).

---

### 📅 Day 233 — Service toko: spek stok + skema

- **Materi:** Field stok, `updated_at`; aturan tidak negatif.
- **Praktik:** Migrasi `stock`; sqlc query.
- **Selesai jika:** Constraint DB atau cek service.

---

### 📅 Day 234 — Service toko: list/detail + stok

- **Praktik:** JSON sama kontrak + `stock`.
- **Selesai jika:** Tes list.

---

### 📅 Day 235 — Service toko: create/update stok

- **Praktik:** Validasi angka; 422.
- **Selesai jika:** Tes table-driven.

---

### 📅 Day 236 — Service toko: delete + IDOR-lite (API key vs milik)

- **Materi:** Jika belum user: catat utang auth user.
- **Selesai jika:** Delete 404 benar.

---

### 📅 Day 237 — Service toko: pagination meta = Laravel

- **Praktik:** `meta.current_page` dll. sesuai `api-v1.md`.
- **Selesai jika:** Next tidak pecah.

---

### 📅 Day 238 — Service toko: filter `q` + category

- **Selesai jika:** SQL parameterized.

---

### 📅 Day 239 — Service toko: tes integrasi folder `testdata`

- **Selesai jika:** `go test ./... -race`.

---

### 📅 Day 240 — Service toko: logging request-id

- **Praktik:** Middleware + slog attr.
- **Selesai jika:** 1 request = 1 id di log.

---

### 📅 Day 241 — Service toko: CORS + header keamanan dasar

- **Materi:** Allow origin eksplisit; jangan `* ` + credentials.
- **Selesai jika:** Next prod origin saja.

---

### 📅 Day 242 — Service toko: README + makefile

- **Praktik:** `make test` `make run`.
- **Selesai jika:** Tanpa tebak perintah.

---

### 📅 Day 243 — Service toko: seed SQL

- **Praktik:** File seed; idempotent sadar.
- **Selesai jika:** Demo data.

---

### 📅 Day 244 — Service toko: hardening validasi + limit body

- **Materi:** `http.MaxBytesReader`; timeout server.
- **Selesai jika:** Body jumbo ditolak.

---

### 📅 Day 245 — Service toko: Next smoke test

- **Praktik:** FE ke Go: list, create, 401.
- **Selesai jika:** Checklist 8 poin.

---

### 📅 Day 246 — Docker multi-stage Go

- **Materi:** Builder + distroless/scratch; `CGO_ENABLED=0`; non-root.
- **Praktik:** Image jalan `curl /health`.
- **Selesai jika:** Binary kecil, bukan SDK image.

---

### 📅 Day 247 — Deploy Fly / Railway / Cloud Run

- **Materi:** Env prod; healthcheck; volume vs managed Postgres.
- **Praktik:** URL API live.
- **Selesai jika:** Next bisa diarahkan (opsional preview).

---

### 📅 Day 248 — HTMX opsional (form + Go)

- **Materi:** HTML partial vs JSON; kapan skip (jika capek, tulis alasan).
- **Praktik:** 1 form POST → HTML snippet *atau* skip sadar.
- **Selesai jika:** Keputusan + 1 demo atau paragraf skip.

---

### 📅 Day 249 — Latihan terpadu Go II

- **Praktik:** Endpoint `PATCH /produk/{id}/stok` + tes.
- **Selesai jika:** Kontrak di-update.

---

### 📅 Day 250 — Bandingkan Laravel vs Go

- **Materi:** Kecepatan fitur, deploy, antrean, ORM vs sqlc, auth.
- **Praktik:** Tabel jujur 12 baris.
- **Selesai jika:** Tidak mitos “Go selalu lebih cepat”.

---

### 📅 Day 251 — Polish tes + README + OpenAPI cuplikan

- **Selesai jika:** `go test -race` CI-lokal hijau.

---

### 📅 Day 252 — REVIEW Go + API live

- **Selesai jika:** Next jalan ke **Laravel atau Go** tanpa ubah spek.

**✅ Checkpoint:** Port API v1 ke Go + Docker/deploy.

---

# ═══════════════════════════════════════════
# BULAN 10 — RUST I · BAHASA (Day 253–280)
# ═══════════════════════════════════════════

> Tiga bulan Rust. Ownership tidak dipadatkan.

---

### 📅 Day 253 — Kapan Rust (dan kapan jangan)

- **Materi:** Memory safety tanpa GC; biaya compile & belajar; prototipe 1 minggu → Laravel/Go; sistem, CLI, API ketat, WASM kenal.
- **Praktik:** Tulis 8 baris “saya pakai Rust jika…”.
- **Selesai jika:** Tidak memaksa Rust untuk form admin 2 hari.

---

### 📅 Day 254 — Toolchain: rustup, cargo, clippy, rustfmt

- **Materi:** `rustup`; channel stable; `cargo new`; `Cargo.toml`; `cargo clippy` `cargo fmt`; `cargo doc`.
- **Praktik:** Bin hello + clippy bersih.
- **Selesai jika:** Format otomatis.

---

### 📅 Day 255 — Ownership & move

- **Materi:** Setiap nilai 1 owner; move vs copy (`Copy` trait); drop; stack/heap intuisi; `String` move.
- **Praktik:** 10 teka-teki compile; perbaiki tanpa clone buta.
- **Selesai jika:** Bisa jelaskan kenapa `let b = a` mematikan `a` untuk `String`.

---

### 📅 Day 256 — Borrow: `&` / `&mut`

- **Materi:** Aturan: banyak `&` XOR satu `&mut`; lifetime *besok*; dangling dicegah compiler; `*ref`.
- **Praktik:** Fungsi `len(s: &str)`; mutasi lewat `&mut`.
- **Selesai jika:** Tidak lawan borrow checker dengan `clone` di semua tempat.

---

### 📅 Day 257 — Lifetime intuisi

- **Materi:** Anotasi `'a` artinya “hidup setidaknya…”; elision; jangan hafal semua kasus; struct yang menyimpan `&`.
- **Praktik:** 5 contoh elision vs wajib anotasi.
- **Selesai jika:** Paham lifetime = hubungan, bukan “lama waktu CPU”.

---

### 📅 Day 258 — `String`/`&str`, `Vec`, `HashMap`

- **Materi:** Owned vs slice; `to_string`/`into`; indexing UTF-8 jebakan; `Vec` `push`; `HashMap` `entry`; iter.
- **Praktik:** Hitung frekuensi kata CLI kecil.
- **Selesai jika:** Tidak index `str` asal `chars`.

---

### 📅 Day 259 — `Option` — tidak ada `null`

- **Materi:** `Some`/`None`; `unwrap` hanya tes; `map` `and_then` `ok_or`; `if let`; `?` pada Option di fungsi compatible.
- **Praktik:** Cari di map → `Option`.
- **Selesai jika:** 0 `unwrap` di bin non-tes.

---

### 📅 Day 260 — `Result`, `?`, produksi

- **Materi:** `Ok`/`Err`; `?`; `From`; jangan `unwrap`/`expect` di request path; `main` → `Result`.
- **Praktik:** Baca file; error ke stderr.
- **Selesai jika:** Gagal I/O tidak panic.

---

### 📅 Day 261 — `thiserror` vs `anyhow`

- **Materi:** Library: `thiserror` typed; aplikasi: `anyhow` konteks; `#[from]`.
- **Praktik:** Error enum `ParseError` + `anyhow` di `main`.
- **Selesai jika:** Pesan error punya konteks path/field.

---

### 📅 Day 262 — Trait yang terpakai

- **Materi:** `Debug` `Clone` `Default` `From` `Display`; `impl Trait`; trait bound; jangan over-abstract.
- **Praktik:** `Display` untuk ID; `FromStr`.
- **Selesai jika:** Derive yang benar, bukan manual kosong.

---

### 📅 Day 263 — `mod` / crate

- **Materi:** `mod foo;` `foo.rs` / `foo/mod.rs`; `pub use`; bin vs lib; `crates.io` hati-hati.
- **Praktik:** Crate lib `parser` + bin.
- **Selesai jika:** Modul tidak 1 file 2000 baris.

---

### 📅 Day 264 — REVIEW ownership + Result

- **Praktik:** Kuis move/borrow/Option/Result; clippy.
- **Selesai jika:** Cheatsheet 1 halaman.

---

### 📅 Day 265 — Tes `#[test]`

- **Materi:** Unit vs `tests/` integrasi; `assert_eq!`; `#[should_panic]` jarang; `cargo test`; modul `cfg(test)`.
- **Praktik:** Tes parser 8 kasus.
- **Selesai jika:** Gagal jelas.

---

### 📅 Day 266 — CLI 1: args + `clap` (atau std `env::args`)

- **Praktik:** CLI `greet --name`.
- **Selesai jika:** `--help` jalan.

---

### 📅 Day 267 — CLI 2: baca file + Result

- **Praktik:** `cat`-lite dengan error.
- **Selesai jika:** File hilang → kode keluar ≠ 0.

---

### 📅 Day 268 — CLI 3: parse CSV/JSON sederhana

- **Materi:** `serde_json` pengantar (detail HTTP nanti).
- **Praktik:** Hitung baris/field.
- **Selesai jika:** Tes parse.

---

### 📅 Day 269 — CLI 4: tes + clippy pedantic sedang

- **Praktik:** Perbaiki warning.
- **Selesai jika:** `clippy -D warnings` di paket ini (wajar).

---

### 📅 Day 270 — Mini lib: money/id helper typed

- **Praktik:** Newtype `UserId(i64)`; jangan campur id.
- **Selesai jika:** Tes.

---

### 📅 Day 271 — Iterators + `collect`

- **Materi:** `iter` `into_iter`; adapter; jangan mikro-optim.
- **Praktik:** Pipeline filter/map.
- **Selesai jika:** Tanpa index off-by-one.

---

### 📅 Day 272 — Closures + `Fn`/`FnMut` intuisi

- **Praktik:** `sort_by`; counter.
- **Selesai jika:** Tahu kenapa mut borrow di closure.

---

### 📅 Day 273 — Smart pointer: `Box`, `Rc` (kenal), `Arc` (nanti async)

- **Materi:** Kapan heap; `Rc` single thread; cycle; `Arc` multi.
- **Praktik:** 1 `Box` rekursif enum sederhana.
- **Selesai jika:** Tidak `Rc` di API server tanpa alasan.

---

### 📅 Day 274 — Interior mutability: `RefCell` kenal, `Mutex` nanti

- **Materi:** Compile-time vs runtime borrow; jangan `RefCell` di hot path web.
- **Praktik:** 1 demo kecil, lalu **jangan** pakai di Axum state.
- **Selesai jika:** Tahu kenapa `Mutex<T>` + `Arc` pola server.

---

### 📅 Day 275 — Error di CLI utuh

- **Praktik:** Gabung thiserror + clap + file.
- **Selesai jika:** UX error manusiawi.

---

### 📅 Day 276 — Baca docs.rs + std

- **Praktik:** Cari 3 API (`Path`, `BufRead`, `Duration`) dari docs, bukan tutorial acak.
- **Selesai jika:** Catatan cara baca docs.

---

### 📅 Day 277 — Latihan padat: 5 kata compiler

- **Praktik:** Perbaiki 5 program gagal compile (move, lifetime, mut, Option, trait).
- **Selesai jika:** Semua `cargo test` hijau.

---

### 📅 Day 278 — Polish CLI + README

- **Selesai jika:** `cargo test` `fmt` `clippy` bersih.

---

### 📅 Day 279 — Latihan terpadu Rust bahasa

- **Praktik:** Soal campuran ownership/Result/mod.
- **Selesai jika:** Tanpa unwrap produksi.

---

### 📅 Day 280 — REVIEW Rust I

- **Selesai jika:** Clippy bersih; unwrap hanya tes.

**✅ Checkpoint:** Bahasa Rust cukup untuk masuk async/HTTP.

---

# ═══════════════════════════════════════════
# BULAN 11 — RUST II · ASYNC & AXUM (Day 281–308)
# ═══════════════════════════════════════════

---

### 📅 Day 281 — Tokio: runtime, `spawn`, jangan block

- **Materi:** Async runtime; `#[tokio::main]`; `spawn`; `spawn_blocking` untuk CPU/disk sync; jangan `std::thread::sleep` di async.
- **Praktik:** 2 task timeout.
- **Selesai jika:** Tahu block = bahaya.

---

### 📅 Day 282 — `async`/`await` vs Go vs TS

- **Materi:** Future; `.await`; Send bound intuisi; beda goroutine vs green-thread vs event loop.
- **Praktik:** Tabel 10 baris perbandingan.
- **Selesai jika:** Tidak mengira `async` = thread OS.

---

### 📅 Day 283 — Axum: router, `Path`, `Json`, `State`

- **Materi:** `Router`; extractor; `Json<T>`; urutan extractor; 404 default.
- **Praktik:** `GET /health` `GET /produk/{id}` memori.
- **Selesai jika:** JSON typed serde.

---

### 📅 Day 284 — `Arc` + pool + state

- **Materi:** `State(Arc<AppState>)`; share read; `Mutex` hanya jika perlu; DB pool = Arc di dalam.
- **Praktik:** State list produk.
- **Selesai jika:** Tidak clone seluruh Vec tiap request tanpa sadar.

---

### 📅 Day 285 — Validasi + serde

- **Materi:** `Deserialize`; `#[serde(rename)]`; `validator` crate atau cek manual; 422 body.
- **Praktik:** POST produk.
- **Selesai jika:** Field salah → JSON error.

---

### 📅 Day 286 — Map error → HTTP 400/404/500

- **Materi:** `IntoResponse`; enum `AppError`; jangan leak internal; log 500.
- **Praktik:** Samakan shape dengan `api-v1.md`.
- **Selesai jika:** 404/422/500 konsisten.

---

### 📅 Day 287 — REVIEW Axum

- **Praktik:** Kuis extractor, state, error.
- **Selesai jika:** Cheatsheet.

---

### 📅 Day 288 — SQLx (compile-time / offline)

- **Materi:** `query_as!`; offline `SQLX_OFFLINE`; migrasi sqlx; vs Diesel kenal.
- **Praktik:** Postgres atau SQLite; `SELECT`.
- **Selesai jika:** Query typed compile.

---

### 📅 Day 289 — Migrasi + model

- **Praktik:** Tabel produk/kategori sesuai v1.
- **Selesai jika:** `sqlx migrate run`.

---

### 📅 Day 290 — CRUD + tes request

- **Materi:** `tower` test / `oneshot`; atau hit DB tes.
- **Praktik:** List/create tes.
- **Selesai jika:** `cargo test` hijau.

---

### 📅 Day 291 — Port: schema & mapping field JSON

- **Praktik:** Struct = kontrak v1 (nama field).
- **Selesai jika:** Contoh JSON identik Go/Laravel.

---

### 📅 Day 292 — Port: GET list + pagination meta

- **Selesai jika:** Meta sama.

---

### 📅 Day 293 — Port: GET detail + 404

- **Selesai jika:** Body error sama.

---

### 📅 Day 294 — Port: POST create + validasi

- **Selesai jika:** 422 field.

---

### 📅 Day 295 — Port: PATCH/PUT update

- **Selesai jika:** Partial sadar.

---

### 📅 Day 296 — Port: DELETE

- **Selesai jika:** Status sama keputusan Go.

---

### 📅 Day 297 — Port: filter `q` + category

- **Selesai jika:** SQL bind, bukan format string.

---

### 📅 Day 298 — Port: health + version

- **Selesai jika:** Ops.

---

### 📅 Day 299 — Port: error shape + tracing intro

- **Praktik:** Log 5xx.
- **Selesai jika:** Tidak panic ke client.

---

### 📅 Day 300 — Port: tes table-driven handler

- **Selesai jika:** Kasus 400/404/201.

---

### 📅 Day 301 — Port: CORS + Next `baseURL` Rust

- **Selesai jika:** FE list jalan lokal.

---

### 📅 Day 302 — Port: seed

- **Selesai jika:** Data demo.

---

### 📅 Day 303 — Port: clippy pada crate API

- **Selesai jika:** Warning produksi ditutup.

---

### 📅 Day 304 — Port: README run + env

- **Selesai jika:** `DATABASE_URL` didokumentasikan.

---

### 📅 Day 305 — Port: checklist kontrak v1

- **Praktik:** Diff 20 poin vs `api-v1.md`.
- **Selesai jika:** Gap = 0 atau tercatat sadar.

---

### 📅 Day 306 — Latihan terpadu Axum + SQLx

- **Praktik:** Field baru + migrasi + FE tidak wajib hari ini.
- **Selesai jika:** Tes hijau.

---

### 📅 Day 307 — Tracing (`tracing` + `tracing-subscriber`)

- **Materi:** Span; request-id; level; JSON log opsional.
- **Praktik:** Setiap request 1 span.
- **Selesai jika:** Debug 1 gagal dari log.

---

### 📅 Day 308 — REVIEW Rust II

- **Selesai jika:** CRUD Axum, tes hijau, kontrak = Go.

**✅ Checkpoint:** API Rust setara Go untuk v1.

---

# ═══════════════════════════════════════════
# BULAN 12 — RUST III · PRODUKSI (Day 309–336)
# ═══════════════════════════════════════════

---

### 📅 Day 309 — Auth di Rust: session vs JWT — pilih sadar

- **Materi:** JWT stateless vs session store; httpOnly cookie; signing secret; jangan roll crypto sendiri.
- **Praktik:** ADR ½ halaman + mulai 1 jalur.
- **Selesai jika:** Pilihan tertulis.

---

### 📅 Day 310 — Extractor user + layer proteksi

- **Materi:** Extractor `AuthUser`; middleware 401; jangan cek auth di sebagian handler saja.
- **Praktik:** `/api/me`; route terlindungi.
- **Selesai jika:** Tanpa token → 401 seragam.

---

### 📅 Day 311 — Tes IDOR

- **Materi:** User A tidak `GET/PATCH` milik B; tes dua user.
- **Praktik:** Fixture 2 user.
- **Selesai jika:** Tes merah dulu, lalu hijau.

---

### 📅 Day 312 — Upload multipart atau skip sadar

- **Materi:** Limit ukuran; MIME; simpan di luar git; virus *bukan* scope.
- **Praktik:** Foto *atau* paragraf skip + alasan (parity Laravel).
- **Selesai jika:** Keputusan + tes jika ada.

---

### 📅 Day 313 — Config, secret, clap/envy/figment

- **Materi:** Fail fast; jangan default secret; `DATABASE_URL`.
- **Praktik:** Struct `Config::from_env()`.
- **Selesai jika:** Missing secret = tidak bind port.

---

### 📅 Day 314 — Docker Rust (cache deps)

- **Materi:** Chef/cargo-chef atau layer `Cargo.toml` dulu; `RELEASE`; ukuran.
- **Praktik:** Image jalan health.
- **Selesai jika:** Build ulang cepat saat ubah `src`.

---

### 📅 Day 315 — REVIEW keamanan Rust

- **Praktik:** Checklist: unwrap, IDOR, secret, CORS, limit body.
- **Selesai jika:** 0 unwrap di handler.

---

### 📅 Day 316 — Next ↔ Rust (cookie/CORS)

- **Praktik:** Login jika sudah ada; atau API key parity Go dulu + catatan auth.
- **Selesai jika:** FE CRUD ke Rust.

---

### 📅 Day 317 — Timeout & concurrency limit

- **Materi:** `TimeoutLayer`; `ConcurrencyLimitLayer`; slowloris kenal.
- **Praktik:** Timeout 5–10s.
- **Selesai jika:** Handler tidur dipotong.

---

### 📅 Day 318 — Rate limit (sederhana)

- **Materi:** Tower governor / in-memory; di belakang reverse proxy nanti.
- **Praktik:** Limit login/API.
- **Selesai jika:** 429.

---

### 📅 Day 319 — Request-id + access log

- **Praktik:** Header `x-request-id` echo.
- **Selesai jika:** Korelasi FE→BE.

---

### 📅 Day 320 — Graceful shutdown Tokio/Axum

- **Materi:** Signal; drain; DB pool close.
- **Praktik:** Deploy-friendly shutdown.
- **Selesai jika:** Tidak potong request kasar *semampunya*.

---

### 📅 Day 321 — Health/ready vs live

- **Materi:** `/health/live` vs `/ready` (DB ping).
- **Praktik:** Ready gagal jika DB down.
- **Selesai jika:** Orchestrator-friendly.

---

### 📅 Day 322 — Migrasi di CI/prod

- **Materi:** Jalankan migrate sebelum serve; lock.
- **Praktik:** Script `migrate && api`.
- **Selesai jika:** Dokumentasi.

---

### 📅 Day 323 — Tes IDOR + auth regresi

- **Selesai jika:** CI-lokal `cargo test`.

---

### 📅 Day 324 — OpenAPI/skema (utoipa atau tulis manual)

- **Praktik:** Spec mengikuti v1.
- **Selesai jika:** Path utama tercatat.

---

### 📅 Day 325 — Observability: 1 bottleneck query

- **Praktik:** `EXPLAIN` atau log slow.
- **Selesai jika:** 1 indeks atau catat “cukup”.

---

### 📅 Day 326 — Hardening headers

- **Materi:** `Content-Type`; jangan `Server` berlebih; HSTS di proxy.
- **Selesai jika:** CORS ketat.

---

### 📅 Day 327 — Load kasar persiapan

- **Materi:** `hey`/`wrk`; apa yang diukur (p95); warmup.
- **Praktik:** Skrip lokal.
- **Selesai jika:** Angka baseline.

---

### 📅 Day 328 — Perkeras: body limit + timeout ulang

- **Selesai jika:** Checklist prod 12 poin.

---

### 📅 Day 329 — Load: `hey` Go vs Rust (jangan mitos)

- **Praktik:** Sama spek, catat p95, CPU; jujur faktor (DB, JSON, hardware).
- **Selesai jika:** Tabel + 5 kalimat interpretasi.

---

### 📅 Day 330 — Deploy Rust live

- **Praktik:** Fly/Railway/VPS; env; HTTPS.
- **Selesai jika:** URL health.

---

### 📅 Day 331 — Latihan terpadu produksi

- **Praktik:** Bugfix dari deploy (env, migrate).
- **Selesai jika:** Next preview → Rust prod/staging.

---

### 📅 Day 332 — ADR: kapan Laravel / Go / Rust

- **Praktik:** `docs/adr-stack.md` 1–2 halaman.
- **Selesai jika:** Kriteria eksplisit (tim, latency, fitur, memori).

---

### 📅 Day 333 — Polish README arsitektur ASCII

- **Selesai jika:** Orang baru paham 5 menit.

---

### 📅 Day 334 — Polish OpenAPI + contoh curl

- **Selesai jika:** 10 contoh.

---

### 📅 Day 335 — Polish tes + clippy + fmt

- **Selesai jika:** Hijau.

---

### 📅 Day 336 — REVIEW Rust III + URL

- **Selesai jika:** Next + Rust live + ADR.

**✅ Checkpoint:** Backend ketiga produksi; kamu punya pendapat stack.

---

# ═══════════════════════════════════════════
# BULAN 13 — INTEGRASI & KUALITAS (Day 337–364)
# ═══════════════════════════════════════════

---

### 📅 Day 337 — Satu spek, tiga BE: matriks port

- **Materi:** Tabel endpoint × Laravel × Go × Rust (✅/❌/beda).
- **Praktik:** `docs/port-matrix.md`.
- **Selesai jika:** Tidak ada “kira-kira sama”.

---

### 📅 Day 338 — Auth nyata di Next (satu pasangan)

- **Materi:** Auth.js *atau* session Laravel *atau* cookie Rust/Go — **pilih 1**; jangan 3 auth sekaligus.
- **Praktik:** Login/logout FE.
- **Selesai jika:** Refresh tetap login (session) atau alur token sadar.

---

### 📅 Day 339 — Protected route **server**

- **Materi:** Cek di RSC/middleware; jangan hanya hide tombol.
- **Praktik:** `/app` redirect unauth; 401 API.
- **Selesai jika:** URL langsung ditolak.

---

### 📅 Day 340 — CI: `next build` + tes BE terpilih

- **Materi:** GitHub Actions: node + (php|go|cargo); cache; secret.
- **Praktik:** Pipeline hijau di PR dummy.
- **Selesai jika:** Fail jika tes merah.

---

### 📅 Day 341 — E2E Playwright 1 alur

- **Materi:** Install; 1 spec: login → list → create (atau list publik).
- **Praktik:** Jalan di CI *atau* lokal dulu + catatan CI.
- **Selesai jika:** 1 alur deterministik.

---

### 📅 Day 342 — A11y + Lighthouse

- **Praktik:** Axe/Lighthouse 3 halaman; perbaiki 5 temuan nyata.
- **Selesai jika:** Kontras + fokus + heading.

---

### 📅 Day 343 — REVIEW kualitas

- **Praktik:** Daftar utang vs must-fix.
- **Selesai jika:** Prioritas 7 hari ke depan.

---

### 📅 Day 344 — Integrasi: spek fitur baru (kontrak dulu)

- **Praktik:** Endpoint + UI + tes — tulis sebelum kode.
- **Selesai jika:** Spek 1 halaman.

---

### 📅 Day 345 — Integrasi: migrasi/skema BE

- **Selesai jika:** Migrasi di BE terpilih.

---

### 📅 Day 346 — Integrasi: API + tes

- **Selesai jika:** Tes merah→hijau.

---

### 📅 Day 347 — Integrasi: UI Next + Tailwind

- **Selesai jika:** Empty/error/loading.

---

### 📅 Day 348 — Integrasi: authz fitur baru

- **Selesai jika:** IDOR tes.

---

### 📅 Day 349 — Integrasi: filter/pagination jika perlu

- **Selesai jika:** URL shareable.

---

### 📅 Day 350 — Integrasi: Playwright update

- **Selesai jika:** Alur baru atau skip sadar.

---

### 📅 Day 351 — Integrasi: dark/360 polish

- **Selesai jika:** Viewport.

---

### 📅 Day 352 — Integrasi: docs api-v1 patch

- **Selesai jika:** Kontrak tidak basi.

---

### 📅 Day 353 — Integrasi: seed + README

- **Selesai jika:** Demo akun.

---

### 📅 Day 354 — Integrasi: log/error prod-like

- **Selesai jika:** 500 tidak bocor stack ke FE.

---

### 📅 Day 355 — Integrasi: rate limit / CORS review

- **Selesai jika:** Origin prod saja.

---

### 📅 Day 356 — Integrasi: performa 1 query/halaman

- **Selesai jika:** N+1 atau waterfall diperbaiki *atau* diukur cukup.

---

### 📅 Day 357 — Integrasi: a11y pass fitur baru

- **Selesai jika:** Label/fokus.

---

### 📅 Day 358 — Integrasi: CI hijau wajib

- **Selesai jika:** Main tidak merah.

---

### 📅 Day 359 — Latihan terpadu kualitas

- **Praktik:** Bug hunt 5 item.
- **Selesai jika:** 5 tertutup atau triase.

---

### 📅 Day 360 — Hardening: secret, CORS, validasi

- **Praktik:** Audit `.env.example`; rotate dummy secret.
- **Selesai jika:** Tidak ada secret di git (`git grep`).

---

### 📅 Day 361 — Dokumentasi: arsitektur + env

- **Selesai jika:** ASCII + tabel env.

---

### 📅 Day 362 — Dokumentasi: runbook 15 menit

- **Materi:** Down prod: cek health, log, migrate, rollback gagasan.
- **Selesai jika:** Runbook 1 halaman.

---

### 📅 Day 363 — Seed demo + data realistis

- **Selesai jika:** Screenshot README.

---

### 📅 Day 364 — REVIEW integrasi

- **Selesai jika:** CI hijau; login; satu BE produksi.

**✅ Checkpoint:** Kualitas “tim kecil”, bukan demo kuliah.

---

# ═══════════════════════════════════════════
# BULAN 14 — CAPSTONE (Day 365–392)
# ═══════════════════════════════════════════

---

### 📅 Day 365 — Masalah + spek 1 halaman

- **Materi:** Bukan klon Twitter; masalah yang kamu peduli (kampus, UMKM, catatan lab, antrian, stok).
- **Praktik:** Siapa pengguna, 3 pekerjaan utama, non-tujuan.
- **Selesai jika:** Spek 1 halaman tanpa tech dulu.

---

### 📅 Day 366 — Pilih BE + alasan

- **Pilih:** Laravel (fitur cepat) / Go (sederhana) / **Rust default fokus** + ½ halaman alasan merujuk ADR Day 332.
- **Selesai jika:** Tidak “karena keren”.

---

### 📅 Day 367 — Kontrak API + skema DB

- **Praktik:** Entity, migrasi draf, error shape, auth.
- **Selesai jika:** Bisa di-review teman.

---

### 📅 Day 368 — Repo + CI kosong + Tailwind/Next scaffold

- **Selesai jika:** Build hijau.

---

### 📅 Day 369 — DB + migrasi + seed kerangka

- **Selesai jika:** Schema v0.

---

### 📅 Day 370 — Auth end-to-end

- **Praktik:** Register/login (sesuai pilihan) + protected.
- **Selesai jika:** ID belum diuji lengkap — mulai.

---

### 📅 Day 371 — CRUD utama list/detail

- **Selesai jika:** Empty/loading/error.

---

### 📅 Day 372 — CRUD create/update/delete + policy

- **Selesai jika:** IDOR tes awal.

---

### 📅 Day 373 — Fitur domain ke-2 (inti spek)

- **Selesai jika:** Bukan CRUD kosmetik saja.

---

### 📅 Day 374 — UI Tailwind: marketing atau app chrome

- **Selesai jika:** 360px.

---

### 📅 Day 375 — Form produksi + validasi dua sisi

- **Selesai jika:** Zod/BE rules.

---

### 📅 Day 376 — Pagination/filter sesuai spek

- **Selesai jika:** URL.

---

### 📅 Day 377 — Tes BE + 1 E2E

- **Selesai jika:** CI.

---

### 📅 Day 378 — A11y + dark (jika spek)

- **Selesai jika:** Fokus/kontras.

---

### 📅 Day 379 — Hardening awal + log

- **Selesai jika:** Secret/env.

---

### 📅 Day 380 — Freeze fitur: utang vs must

- **Praktik:** Daftar yang *tidak* dikerjakan.
- **Selesai jika:** Scope terkunci.

---

### 📅 Day 381 — Docker Compose: web + api + db

- **Materi:** Jaringan; env; migrate job; volume.
- **Praktik:** `docker compose up` lokal.
- **Selesai jika:** Tanpa “di mesinku saja” semampunya.

---

### 📅 Day 382 — Deploy FE + BE

- **Praktik:** URL publik.
- **Selesai jika:** HTTPS; env prod.

---

### 📅 Day 383 — REVIEW capstone (jalan sendiri)

- **Praktik:** 15 skenario pengguna.
- **Selesai jika:** Bug list.

---

### 📅 Day 384 — Hardening IDOR + validasi + rate limit

- **Selesai jika:** Tes authz hijau.

---

### 📅 Day 385 — Ukur 1 bottleneck, perbaiki

- **Praktik:** Query/N+1/image/bundle — pilih 1.
- **Selesai jika:** Angka atau screenshot.

---

### 📅 Day 386 — README + arsitektur ASCII + `.env.example`

- **Selesai jika:** Clone → jalan (dokumentasi).

---

### 📅 Day 387 — Presentasi 5 menit

- **Praktik:** Masalah, demo, stack, 1 keputusan sulit.
- **Selesai jika:** Naskah + 3 screenshot.

---

### 📅 Day 388 — Launch ke 1 teman, catat bug

- **Selesai jika:** 5 catatan nyata.

---

### 📅 Day 389 — Perbaiki bug launch

- **Selesai jika:** P0/P1 tutup.

---

### 📅 Day 390 — Polish Tailwind

- **Praktik:** Spacing, empty, fokus.
- **Selesai jika:** Terasa satu desain.

---

### 📅 Day 391 — Rencana 90 hari pasca-roadmap

- **Materi:** Job, open source, GEMASTIK web? pendalaman Rust/SQL.
- **Selesai jika:** 6 butir terukur.

---

### 📅 Day 392 — REVIEW AKHIR + checklist mahir

- **Checklist:** Produk live; CI; ADR stack; jelaskan **ownership, goroutine, Eloquent, Server Component, cascade CSS, flex vs grid, kenapa Tailwind**.
- **Selesai jika:** Kamu bisa mengajar Day 1 dan membela capstone.

**✅ Checkpoint akhir:** Bukan koleksi framework — satu produk + tiga backend yang kontraknya kamu pahami.

---

# 📊 RINGKASAN

| Bulan | Day | Isi |
| ----- | --- | --- |
| 1 | 1–28 | HTML → **CSS lengkap** → Tailwind awal |
| 2 | 29–56 | Tailwind produksi (design system, 2 halaman) |
| 3 | 57–84 | **TypeScript langsung** (DOM/fetch/Zod) |
| 4–5 | 85–140 | **Next.js** (2 bulan; React di dalamnya) |
| 6–7 | 141–196 | **Laravel** (2 bulan; API + auth + Next) |
| 8–9 | 197–252 | **Go** (2 bulan; port API Laravel) |
| 10–12 | 253–336 | **Rust** (3 bulan — fokus) |
| 13 | 337–364 | Integrasi, auth, CI, E2E |
| 14 | 365–392 | Capstone |

**CSS di bulan 1 (lengkap, kurikulum biasa):** cascade & file CSS (8) → selector (9) → specificity (10) → satuan & warna (11) → tipografi (12) → box model (13) → display/flow (14) → flex container (15) → flex item (16) → grid (17) → position/z-index (18) → background/gambar (19) → media query (20) → form/transisi/variabel (21) → a11y visual (22) → proyek CSS murni (23) → baru Tailwind (24–28).

---

# 🎯 CHECKPOINT

| Day | Wajib |
| --- | ----- |
| 7 | Profil HTML semantik |
| 23 | Profil **CSS murni** responsif |
| 28 | Versi Tailwind live |
| 56 | Landing + dashboard, token, dark |
| 84 | Dashboard TS strict live |
| 112 | Katalog Next, `build` hijau |
| 140 | Next Vercel live |
| 168 | CRUD Laravel |
| 196 | Next + Laravel live + `api-v1.md` |
| 224 | Go HTTP + tes + race |
| 252 | API Go live, Next ganti URL |
| 280 | Rust: Result/Option lancar |
| 308 | CRUD Axum |
| 336 | Next + Rust live + ADR |
| 364 | CI + login |
| 392 | Capstone live |

---

# 🗺️ PETA

```
HTML ──► CSS lengkap ──► Tailwind ──► TypeScript ──► Next.js
                                                      │
                                    ┌─────────────────┼─────────────────┐
                                    ▼                 ▼                 ▼
                                Laravel              Go               Rust
                                (produktif)      (jelas, cepat)    (ketat, fokus)
                                    └─────────────────┴─────────────────┘
                                                      ▼
                                         Kontrak API sama → ganti BE
                                                      ▼
                                              Integrasi + Capstone
```

---

# ⚠️ YANG DITINGGALKAN DENGAN SENGAJA

1. **JS dulu** — TS dari Day 57.
2. **Float sebagai layout** — 1 paragraf sejarah di hari position; layout = flex/grid lalu Tailwind.
3. **Framework FE lain sebagai jalur** — Next saja.
4. **Hari tipis** — “hanya `br`” tidak dapat 1 hari; CSS tetap **lengkap**, hanya dipaket padat.
5. **Tiga auth sekaligus** — bulan 13 pilih **satu** pasangan Next + BE.

---

*"CSS sampai bisa layout tanpa crutch. Tailwind setelah itu, supaya utility bukan hafalan. TypeScript tanpa tur JavaScript. Next dua bulan. Laravel dua bulan. Go dua bulan. Rust tiga bulan.
Yang mahir: satu produk live, tiga backend, kontrak sama — dan bisa jelaskan kenapa `p-4` itu padding."*
