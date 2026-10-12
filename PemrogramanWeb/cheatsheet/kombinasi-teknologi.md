# Cara menggabungkan teknologi

[← Daftar panduan](README.md)

Tidak semua proyek butuh React, Next.js, dan Laravel sekaligus. Pilih tumpukan yang sesuai pekerjaan, lalu gabungkan hanya bagian yang saling butuh.

## Daftar isi

- [Peta tanggung jawab](#peta-tanggung-jawab)
- [HTML + CSS](#html--css)
- [HTML + CSS + JavaScript](#html--css--javascript)
- [CSS / Tailwind + React](#css--tailwind--react)
- [React + Next.js](#react--nextjs)
- [Next.js + Laravel](#nextjs--laravel)
- [Laravel + Blade + CSS](#laravel--blade--css)
- [Yang tidak perlu digabung](#yang-tidak-perlu-digabung)
- [Checklist memilih tumpukan](#checklist-memilih-tumpukan)
- [Alur error yang sama di semua tumpukan](#alur-error-yang-sama-di-semua-tumpukan)

## Peta tanggung jawab

| Lapisan | Tugas | Contoh di folder ini |
|---|---|---|
| HTML | kerangka dan makna | judul, form, tombol |
| CSS / Tailwind | tampilan dan layout | [css.md](css.md) |
| JavaScript | perilaku di browser | [javascript.md](javascript.md) |
| React | UI dari komponen + state | [react-js.md](react-js.md) |
| Next.js | halaman, server, API milik frontend | [next-js.md](next-js.md) |
| Laravel | validasi, database, HTML/JSON server | [laravel.md](laravel.md) |

Alur data yang paling sering:

**Pengguna → halaman (HTML/React/Next) → permintaan HTTP → Laravel/Next Route Handler → database → JSON/HTML kembali → tampilan berubah.**

## HTML + CSS

**Untuk apa:** halaman statis: profil, landasan tugas pertemuan 3, poster informasi.

```html
<link rel="stylesheet" href="style.css">
<h1 class="judul">Raja Ampat</h1>
```

Tidak ada klik yang mengubah data. Cukup jika isinya jarang berubah dan tidak perlu login.

**Biasanya digabungkan dengan:** Tailwind untuk class utilitas, atau CSS biasa di `style.css`.

## HTML + CSS + JavaScript

**Untuk apa:** interaksi di satu halaman tanpa build tool.

Contoh hidup: [contoh-praktik/index.html](contoh-praktik/index.html) — CSS merapikan kartu, JavaScript memfilter nama dan menandai favorit.

Pakai pola ini untuk kuis, dashboard sederhana, atau tugas DOM.

**Biasanya digabungkan dengan:** `querySelector`, `addEventListener`, Flexbox/Grid. Belum perlu React jika state-nya satu-dua variabel.

## CSS / Tailwind + React

**Untuk apa:** komponen yang diulang, state yang sering berubah.

```jsx
<button className="rounded bg-slate-800 px-4 py-2 text-white" onClick={tambah}>
  Tambah
</button>
```

CSS menjawab “kelihatan seperti apa”. React menjawab “nilainya berapa sekarang”. Jangan menyimpan warna di `useState` kalau cukup class.

**Biasanya digabungkan dengan:** `className`, CSS Module, atau Tailwind. Ingat: di React tulis `className`, bukan `class`.

## React + Next.js

**Untuk apa:** banyak URL, data diambil di server, atau butuh `loading.js` / `not-found`.

Next.js **sudah memakai React**. Bukan dua aplikasi terpisah. File `app/page.js` adalah komponen React. Tambah `"use client"` hanya jika perlu `useState`, event, atau API browser.

**Biasanya digabungkan dengan:** `Link`, dynamic route `[id]`, dan Server Component untuk fetch.

## Next.js + Laravel

**Untuk apa:** etalase di Next, gudang di Laravel.

1. Laravel sediakan `GET /api/produk` (lihat [laravel.md](laravel.md#endpoint-api-untuk-frontend)).
2. Next.js baca `API_BASE_URL` di `.env.local`.
3. Server Component melakukan `fetch`, lalu me-render daftar.
4. Tombol “suka” tetap Client Component; tidak perlu ke database jika hanya tampilan lokal.

Jangan menduplikasi aturan bisnis: stok dan harga sahih ada di Laravel. Next menampilkan dan, jika perlu, mengirim form/JSON ke endpoint yang sama.

**Biasanya digabungkan dengan:** CORS, environment variable, dan state loading/error/empty.

## Laravel + Blade + CSS

**Untuk apa:** website klasik: form, daftar, admin, tanpa SPA.

Controller mengirim data → Blade mencetak HTML → CSS/Tailwind merapikan. CSRF wajib di form.

Pilih ini jika tidak butuh navigasi gaya aplikasi React. Pilih Next + API jika tim frontend ingin komponen dan routing di Node.

**Biasanya digabungkan dengan:** `@csrf`, validasi, Eloquent, dan file CSS di `public/` atau Vite Laravel.

## Yang tidak perlu digabung

- **React + `document.querySelector` untuk teks yang sudah di-state:** biarkan React yang merender.
- **Next Route Handler + Laravel untuk logika yang sama:** pilih satu sumber kebenaran.
- **localStorage sebagai database toko:** data hilang per browser; pakai Laravel/database.
- **Semua prefix Tailwind di halaman yang cukup CSS 20 baris:** boleh CSS biasa.

Latihan: buka [contoh praktik](contoh-praktik/index.html), jelaskan baris mana yang CSS dan mana yang JavaScript. Lalu bayangkan daftar produknya datang dari `/api/produk` Laravel — file HTML mana yang harus berubah, dan mana yang tidak.

## Checklist memilih tumpukan

| Kebutuhan | Cukup pakai |
|---|---|
| Halaman info, landasan, tugas CSS | HTML + CSS / Tailwind |
| Filter, hitung, toggle di satu file | + JavaScript |
| Banyak komponen, state saling terkait | React |
| Banyak URL, SEO, fetch di server | Next.js |
| Form + database + login | Laravel + Blade |
| Etalase modern + gudang data | Next.js + API Laravel |

Jika dosen hanya minta “landing page tanpa JS”, berhenti di HTML+CSS. Jangan memaksa Next.

## Alur error yang sama di semua tumpukan

Empat tampilan data, di mana pun kamu coding:

1. **Memuat** — “sebentar…”
2. **Sukses ada data** — daftar/kartu
3. **Sukses kosong** — “belum ada produk”
4. **Gagal** — “tidak bisa dimuat, coba lagi”

Di JS murni: `status` string + `textContent`. Di React: `useState`. Di Next: `loading.js` + `error.js` + `notFound()`. Di Laravel: `@forelse` / validasi 422 / 404 model.

**Biasanya digabungkan dengan:** `fetch` dan pesan yang bisa dibaca manusia, bukan dump error PHP di layar pengguna.
