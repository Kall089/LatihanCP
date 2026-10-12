# Studi Kasus 02 — Dashboard Interaktif

Dashboard sederhana **pesanan kedai** (atau inventori tugas kuliah — pilih
satu tema, konsisten). Bekal: Tailwind CDN (Modul 04) + JavaScript DOM
(Modul 05).

Kunci: [`../../5-kunci-jawaban-latihan/studi-kasus/02-dashboard-interaktif/`](../../5-kunci-jawaban-latihan/studi-kasus/02-dashboard-interaktif/).

## Fitur wajib (JavaScript)

1. **Sumber data = array** di `script.js` (minimal 6 objek: id, nama, kategori,
   status/harga — sesuaikan tema).
2. **Render list** dari array ke DOM (`createElement` + `textContent`, atau
   rakit HTML hanya dari field yang sudah kamu kendalikan — **jangan**
   `innerHTML` dari input pengguna).
3. **Filter** — tombol/select kategori atau status; ubah state filter, lalu
   `render()`.
4. **Form tambah item** — `submit` + `preventDefault`, validasi (nama tidak
   kosong, dll.), push ke array, `render()`, reset form. Tampilkan pesan
   error di halaman, bukan `alert`.
5. **Hapus item** — tombol per baris, `splice` / filter array, `render()`.

Pola: **state → render**. Jangan mengedit DOM di luar `render()` kecuali
pesan validasi form.

## Tampilan (Tailwind CDN)

- Header judul dashboard.
- Kartu ringkasan (jumlah item, boleh derived dari array).
- Toolbar filter.
- Daftar (kartu atau tabel) responsif: `grid-cols-1 md:grid-cols-2`.
- Form di aside atau section bawah.

Jangan pakai file CSS sendiri kecuali benar-benar perlu; utamakan utility.

## Cara uji

Buka `index.html`. Console tanpa error. Tambah item, filter, hapus. Cek:

```bash
node --check script.js
```

(Perintah itu hanya cek sintaks; `document` tidak dijalankan.)
