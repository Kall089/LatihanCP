# Pemrograman Web

Paket kuliah lengkap: teori, slide, praktikum, latihan soal, studi kasus, dan
kunci jawaban. Semua materi berbahasa Indonesia. Target akhirnya adalah mampu
membangun antarmuka yang **semantik, responsif, interaktif, aksesibel, aman,
dan siap di-build**, bukan hanya terlihat bagus pada satu ukuran layar.

Untuk belajar **per hari sampai mahir** (± 14 bulan): Tailwind, TypeScript
langsung, Next.js, Laravel, Go, Rust (fokus), pakai
[`../ComProgLearning/ROADMAP_WEB.md`](../ComProgLearning/ROADMAP_WEB.md)
(392 hari, pola `Day-XX` seperti Competitive Programming). Folder kuliah ini
tetap ringkasan semester.

## Peta folder

Untuk referensi kode beserta kegunaan dan pasangan teknologinya, buka
[`cheatsheet/README.md`](cheatsheet/README.md): CSS, JavaScript, React.js,
Next.js, Laravel, dan contoh praktik yang dapat dibuka langsung di browser.

```text
PemrogramanWeb/
├── 0-materi/                  teori.md + slides.pptx per topik
├── 1-pembelajaran/            praktikum ber-TODO (kerjakan dulu)
├── 2-kunci-jawaban/           kunci praktikum lama (buka SETELAH mencoba)
├── 3-latihan-soal/            10 soal konsep + 3 praktik / topik (tanpa jawaban)
├── 4-studi-kasus/             proyek mini tanpa solusi
├── 5-kunci-jawaban-latihan/   kunci latihan soal + studi kasus
├── tools/                     generator slide (jangan diubah sembarangan)
└── Latihan2.html, test.html…  file lepas lama — JANGAN dihapus
```

Panduan isi materi dan checkpoint setiap modul tersedia di
[`0-materi/README.md`](0-materi/README.md). Setelah modul inti, baca
[`0-materi/PENGAYAAN-HTTP-API-KUALITAS-WEB.md`](0-materi/PENGAYAAN-HTTP-API-KUALITAS-WEB.md)
untuk menutup celah penting antara proyek lokal dan aplikasi yang memakai API.

Alur yang dimaksud:

**0-materi** (teori + PPT) → **1-pembelajaran** (praktikum TODO) →
**2-kunci-jawaban** (kunci praktikum) → **3-latihan-soal** → **4-studi-kasus**
→ **5-kunci-jawaban-latihan**.

| Folder | Isi | Kapan dibuka |
|---|---|---|
| [`0-materi/`](0-materi/) | Teori mendalam + `slides.pptx` | Sebelum praktikum, dan saat mengulang ujian |
| [`1-pembelajaran/`](1-pembelajaran/) | Praktikum ber-TODO | Setelah baca teori topik yang sama |
| [`2-kunci-jawaban/`](2-kunci-jawaban/) | Kunci praktikum | Hanya setelah mencoba sendiri |
| [`3-latihan-soal/`](3-latihan-soal/) | Soal konsep + praktik kecil | Setelah praktikum, tanpa melihat kunci |
| [`4-studi-kasus/`](4-studi-kasus/) | Proyek mini (starter TODO) | Menggabungkan beberapa modul |
| [`5-kunci-jawaban-latihan/`](5-kunci-jawaban-latihan/) | Kunci latihan & studi kasus | Setelah mengerjakan 3 dan 4 |

File lepas di root (`Latihan2.html`, `latihan.html`, `test.html`, `style.css`,
dll.) adalah sisa pertemuan awal. **Jangan hapus** — mereka bukan bagian
kurikulum terstruktur, tapi boleh tetap dipakai sebagai catatan pribadi.

## Daftar topik (8 modul)

| # | Topik | Teori | Praktikum | Latihan |
|---|---|---|---|---|
| 01 | HTML Dasar | [`0-materi/01-html-dasar/`](0-materi/01-html-dasar/) | [`1-pembelajaran/01-html-dasar/`](1-pembelajaran/01-html-dasar/) | [`3-latihan-soal/01-html-dasar/`](3-latihan-soal/01-html-dasar/) |
| 02 | CSS Dasar | [`0-materi/02-css-dasar/`](0-materi/02-css-dasar/) | [`1-pembelajaran/02-css-dasar/`](1-pembelajaran/02-css-dasar/) | [`3-latihan-soal/02-css-dasar/`](3-latihan-soal/02-css-dasar/) |
| 03 | Layout Responsif | [`0-materi/03-layout-responsive/`](0-materi/03-layout-responsive/) | [`1-pembelajaran/03-layout-responsive/`](1-pembelajaran/03-layout-responsive/) | [`3-latihan-soal/03-layout-responsive/`](3-latihan-soal/03-layout-responsive/) |
| 04 | Tailwind CSS | [`0-materi/04-tailwind-css/`](0-materi/04-tailwind-css/) | [`1-pembelajaran/04-tailwind-css/`](1-pembelajaran/04-tailwind-css/) | [`3-latihan-soal/04-tailwind-css/`](3-latihan-soal/04-tailwind-css/) |
| 05 | JavaScript & DOM | [`0-materi/05-javascript-dom/`](0-materi/05-javascript-dom/) | [`1-pembelajaran/05-javascript-dom/`](1-pembelajaran/05-javascript-dom/) | [`3-latihan-soal/05-javascript-dom/`](3-latihan-soal/05-javascript-dom/) |
| 06 | React Komponen | [`0-materi/06-react-komponen/`](0-materi/06-react-komponen/) | [`1-pembelajaran/06-react-komponen/`](1-pembelajaran/06-react-komponen/) | [`3-latihan-soal/06-react-komponen/`](3-latihan-soal/06-react-komponen/) |
| 07 | Next.js App Router | [`0-materi/07-nextjs-app-router/`](0-materi/07-nextjs-app-router/) | [`1-pembelajaran/07-nextjs-app-router/`](1-pembelajaran/07-nextjs-app-router/) | [`3-latihan-soal/07-nextjs-app-router/`](3-latihan-soal/07-nextjs-app-router/) |
| 08 | Proyek Next.js + Tailwind | [`0-materi/08-proyek-nextjs-tailwind/`](0-materi/08-proyek-nextjs-tailwind/) | [`1-pembelajaran/08-proyek-nextjs-tailwind/`](1-pembelajaran/08-proyek-nextjs-tailwind/) | [`3-latihan-soal/08-proyek-nextjs-tailwind/`](3-latihan-soal/08-proyek-nextjs-tailwind/) |

Studi kasus lintas-modul ada di [`4-studi-kasus/`](4-studi-kasus/).

## Alur mingguan yang disarankan

Untuk **satu topik** (misalnya minggu HTML):

1. Baca `0-materi/XX-.../teori.md` sampai bagian *cheatsheet*.
2. Skim `slides.pptx` di folder yang sama (14–18 slide ringkasan dosen).
3. Kerjakan bab-bab `1-pembelajaran/XX-.../` berurutan. Isi semua `TODO`.
4. Baru buka `2-kunci-jawaban/XX-.../` untuk membandingkan, bukan menyalin.
5. Kerjakan `3-latihan-soal/XX-.../soal.md` tanpa melihat kunci.
6. Cek pemahaman di `5-kunci-jawaban-latihan/latihan-soal/XX-.../JAWABAN.md`.

Sebuah modul baru dianggap selesai jika kamu bisa:

- menjelaskan konsep utama tanpa membaca cheatsheet;
- membuat ulang contoh kecil dari halaman kosong;
- menyelesaikan semua TODO dan menjelaskan setiap perubahan;
- menguji keyboard, ukuran 360 px, Console, dan kasus data kosong;
- menjalankan pemeriksaan yang relevan (`node --check`, lint, atau build);
- menulis satu bug yang ditemukan beserta akar penyebabnya.

Jangan menilai hasil hanya dari tampilan. UI yang cantik tetapi tidak dapat
dipakai keyboard, error di Console, atau gagal build masih belum selesai.

Setiap **2–3 topik**, kerjakan satu studi kasus di `4-studi-kasus/`:

| Setelah modul | Studi kasus |
|---|---|
| 01–02 | [`00-profil-mahasiswa`](4-studi-kasus/00-profil-mahasiswa/) — HTML semantik, lalu CSS |
| 02–03 | [`01-landing-page-umkm`](4-studi-kasus/01-landing-page-umkm/) — landing page + flexbox |
| 04–05 | [`02-dashboard-interaktif`](4-studi-kasus/02-dashboard-interaktif/) — Tailwind + DOM |
| 06–08 | [`03-katalog-produk-nextjs`](4-studi-kasus/03-katalog-produk-nextjs/) — Next.js + Tailwind |

## Cara membuka HTML di browser

Modul 01–05 (HTML, CSS, Tailwind CDN, JavaScript murni) **tidak butuh server**.

**Finder / Explorer:** klik dua kali `index.html` — terbuka di browser default.

**VS Code / Cursor:** klik kanan file → *Open with Live Server* (jika ekstensi
terpasang). Berguna agar `fetch`/path relatif lebih prediktabel.

**Terminal:**

```bash
# macOS
open 1-pembelajaran/01-html-dasar/01-struktur-dokumen/index.html

# atau server lokal di folder bab (opsional)
cd 1-pembelajaran/01-html-dasar/01-struktur-dokumen
python3 -m http.server 8080
# lalu buka http://localhost:8080
```

DevTools wajib dibuka (`Cmd+Option+I` di macOS, `F12` di Windows): tab
**Elements** untuk HTML/CSS, **Console** untuk error JavaScript.

Gambar memakai path **relatif** terhadap file HTML. Kalau `index.html` di
`halaman/` dan foto di `halaman/img/foto.jpg`, tulis `src="img/foto.jpg"` —
bukan path absolut komputermu.

## Node.js untuk React dan Next.js

Modul 06–08 dan studi kasus katalog **membutuhkan Node.js 20.9 atau lebih baru**.

Cek versi:

```bash
node -v    # contoh: v20.11.0
npm -v
```

Kalau belum terpasang: unduh LTS di [https://nodejs.org](https://nodejs.org)
atau pakai `nvm`.

Perintah yang sering dipakai:

```bash
npx create-next-app@latest nama-proyek --typescript --tailwind --app
cd nama-proyek
npm run dev      # http://localhost:3000  (pengembangan)
npm run build    # wajib lolos sebelum dikumpulkan / di-deploy
npm run lint     # jika script lint tersedia di package.json
npm start        # jalankan hasil build
```

Pada Next.js modern, lint dijalankan sebagai script ESLint/Biome tersendiri;
`npm run build` tidak menggantikan pemeriksaan lint. Lihat `package.json`
proyek karena script yang tersedia dapat berbeda.

Untuk Modul 07–08, jadikan `teori.md` dan dokumentasi resmi sebagai acuan
versi. Framework berubah lebih cepat daripada HTML/CSS, sehingga periksa ulang
syarat Node.js dan perintah proyek ketika memperbarui dependency.

Starter praktikum React/Next ada di subfolder `starter/` tiap bab. Salin ke
proyek Next.js yang sudah kamu buat, lalu isi `TODO`.

Untuk memeriksa sintaks JavaScript murni (Modul 05, studi kasus dashboard):

```bash
node --check script.js
```

## Aturan main untuk mahasiswa

- Jangan menyalin kunci sebelum mencoba. Kunci adalah *pembanding*, bukan
  generator tugas.
- Praktikum lama (`1-pembelajaran/`, `2-kunci-jawaban/`) jangan dihapus atau
  ditimpa — itu jalur resmi pertemuan.
- Slide `0-materi/*/slides.pptx` sudah di-redesain; jangan generate ulang
  kecuali dosen meminta.
- Kumpulkan pekerjaan dari folder kerja sendiri, bukan dengan menimpa kunci.

## Rubrik proyek web

| Aspek | Bobot | Bukti yang dicari |
|---|---:|---|
| Fungsi & data flow | 30% | fitur bekerja, loading/error/empty state masuk akal |
| HTML & aksesibilitas | 20% | semantik, label, alt, fokus keyboard, heading runtut |
| Responsivitas | 15% | tidak overflow pada 360/768/1280 px |
| Struktur kode | 15% | komponen reusable, state minimal, data tidak diduplikasi |
| Ketahanan & keamanan | 10% | input divalidasi, output aman, rahasia tidak ke client |
| Verifikasi | 10% | Console bersih, lint/build lolos, pengujian terdokumentasi |

Skor **80 atau lebih** berarti proyek siap dikumpulkan. Perbaiki fungsi dan
aksesibilitas sebelum menambah animasi atau dekorasi.

## Lanjut

Mulai dari [`0-materi/README.md`](0-materi/README.md), lalu bab pertama
[`1-pembelajaran/01-html-dasar/`](1-pembelajaran/01-html-dasar/).
