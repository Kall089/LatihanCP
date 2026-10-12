# Cheatsheet Pemrograman

Catatan berbahasa Indonesia: **tipe ini apa, untuk apa, contoh implementasi, dan biasanya digabung dengan apa?**

Ada dua lapisan:

- **Versi cepat** — file di folder ini, cukup untuk tugas harian.
- **Ensiklopedia** — [ensiklopedia/README.md](ensiklopedia/README.md), sekitar **105.000 baris**.
- **CP lengkap** — [cp/README.md](cp/README.md), sekitar **50.000 baris**. DP: [cp/09-dp](cp/09-dp/README.md).

## Versi cepat — web

1. [HTML](html.md)
2. [CSS](css.md)
3. [JavaScript](javascript.md)
4. [React.js](react-js.md)
5. [Next.js](next-js.md)
6. [PHP](php.md)
7. [Laravel](laravel.md)
8. [Cara menggabungkan teknologi web](kombinasi-teknologi.md)

## Versi cepat — bahasa lain

9. [Python](python.md) — dasar, NumPy, pandas → [ensiklopedia](ensiklopedia/python/README.md)
10. [C++ dan Unreal](cpp.md) — tipe, STL, Actor → [ensiklopedia](ensiklopedia/cpp/README.md)
11. [Java](java.md) — primitif, OOP, Collections → [ensiklopedia](ensiklopedia/java/README.md)
12. [Competitive Programming](cp/README.md) — folder lengkap (DP, greedy, graf, …) · [peta cepat](cp.md)

Urutan web: **HTML → CSS → JavaScript → React → Next.js**. Backend: **PHP → Laravel**. Data: **Python → NumPy → pandas**. Game: **C++ dasar → STL → Unreal**. CP: buka [`cp/README.md`](cp/README.md); **DP** ada di [`cp/09-dp`](cp/09-dp/README.md). Latihan harian tetap di `KULIAH/ComprogLearning/CP`.

## Cara memakai catatan ini

- Buka Markdown Preview di editor agar contoh kode dan tautannya nyaman dibaca.
- Gunakan daftar isi setiap file atau cari kata seperti `flex`, `fetch`, `useState`, atau `validate`.
- Contoh pendek adalah potongan terpisah, kecuali dinyatakan sebagai rangkaian. Jangan menempelkan semua contoh ke satu file.
- Nama file di atas blok kode menunjukkan tempat menulisnya **di proyek latihanmu**. Folder ini berisi referensi, bukan instalasi React/Next/Laravel.
- Setelah menyalin, ubah satu nilai dan amati hasilnya. Coba jelaskan kembali fungsi tiap baris dengan bahasamu sendiri.

## Contoh yang langsung bisa dibuka

Buka [contoh-praktik/index.html](contoh-praktik/index.html) di browser. Di sana CSS membentuk kartu produk, sedangkan JavaScript menjalankan pencarian dan tombol favorit. Tidak membutuhkan instalasi paket atau internet.

File pendampingnya: [style.css](contoh-praktik/style.css) dan [script.js](contoh-praktik/script.js).

## Bedakan tugas masing-masing

Bayangkan aplikasi toko:

- **HTML**: kerangka halaman, seperti judul, formulir, dan tombol.
- **CSS**: penampilan kerangka itu, seperti warna tombol dan jumlah kolom.
- **JavaScript**: perilaku, seperti memfilter produk saat pengguna mengetik.
- **React**: mengatur antarmuka JavaScript menjadi komponen yang mengikuti perubahan data.
- **Next.js**: menambahkan kerangka aplikasi di atas React, termasuk halaman berdasarkan URL dan pekerjaan di server.
- **Laravel**: memproses permintaan di server, memvalidasi data, dan berinteraksi dengan database. Laravel juga bisa menghasilkan HTML melalui Blade.
- **Database**: menyimpan data agar tetap ada setelah server/browser dimatikan.

Tidak semuanya harus dipakai sekaligus. Pilih sesuai kebutuhan; contoh kombinasinya ada di [panduan kombinasi](kombinasi-teknologi.md).

## Ruang lingkup dan versi

Contoh menggunakan CSS modern, JavaScript ES modules, React function components dan Hooks, Next.js **App Router**, serta pola Laravel modern. Contoh Next.js ditujukan untuk pola versi 15/16 (`params` di-`await`); Laravel merujuk dokumentasi 13.x. Cocokkan persyaratan runtime dengan versi yang kamu instal.

Dokumentasi framework web diperiksa pada **22 September 2026**. Python merujuk NumPy/pandas modern; C++ ke standar + API publik Unreal Engine; Java ke JDK modern. Cocokkan dengan versi yang kamu instal. Unreal di catatan ini untuk belajar API, bukan cheat game.
