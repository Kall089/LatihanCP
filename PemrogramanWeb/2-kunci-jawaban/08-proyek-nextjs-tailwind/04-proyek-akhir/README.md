# 08 — Proyek Akhir: Learning Tracker

Buat aplikasi Next.js dengan Tailwind CSS untuk mencatat progres materi kuliah.

## Persiapan

```bash
npx create-next-app@latest learning-tracker
cd learning-tracker
npm run dev
```

## Fitur wajib

- Halaman `/` menampilkan daftar materi.
- Halaman `/materi/[slug]` menampilkan detail materi.
- Pengguna dapat menandai materi sebagai selesai.
- Terdapat filter `Semua`, `Belum selesai`, dan `Selesai`.
- Progress ditampilkan sebagai angka, misalnya `3 dari 8 selesai`.
- Layout nyaman pada ponsel dan desktop.

Untuk tahap awal, data boleh disimpan sebagai array lokal dan progres boleh disimpan dalam state. Setelah fitur dasarnya benar, kamu dapat mempelajari penyimpanan permanen.

## Urutan pengerjaan

### Tahap 1 — Data dan tampilan

- [ ] Buat array data materi berisi `slug`, `title`, `description`, dan `completed`.
- [ ] Buat component `MaterialCard` dengan props bertipe jelas.
- [ ] Render daftar menggunakan `map()` dan `key` yang stabil.

### Tahap 2 — Routing

- [ ] Buat folder route dinamis `app/materi/[slug]`.
- [ ] Cari materi berdasarkan parameter `slug`.
- [ ] Tampilkan keadaan ketika materi tidak ditemukan.

### Tahap 3 — Interaksi

- [ ] Buat Client Component untuk tombol status.
- [ ] Tambahkan filter daftar.
- [ ] Hitung jumlah materi yang selesai dari data, jangan simpan nilai hitungan terpisah.

### Tahap 4 — Tailwind dan responsif

- [ ] Terapkan hierarki visual pada judul, deskripsi, dan metadata.
- [ ] Gunakan grid responsif untuk daftar kartu.
- [ ] Tambahkan state hover dan focus-visible.
- [ ] Uji pada lebar 375 px dan 1280 px.

## Aturan latihan

1. Selesaikan satu tahap sebelum lanjut.
2. Jalankan aplikasi setelah setiap perubahan kecil.
3. Jika error, baca pesan dari baris pertama yang menunjuk ke kode milikmu.
4. Jangan salin solusi penuh; tanyakan satu konsep atau satu error pada satu waktu.

## Tantangan lanjutan

- Simpan progres ke `localStorage`.
- Tambahkan mode gelap.
- Ambil data materi melalui Route Handler.
- Tambahkan loading state dan halaman `not-found`.
