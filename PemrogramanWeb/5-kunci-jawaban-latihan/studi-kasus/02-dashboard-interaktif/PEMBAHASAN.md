# Pembahasan — Dashboard Interaktif

## Pola yang sama dengan Modul 05

```text
array pesanan  = STATE
filterKategori = STATE
render()       = satu-satunya yang menulis daftar + total
event          = ubah state, lalu render()
```

Tidak ada `innerHTML +=` dari input pengguna. Setiap kartu dibangun dengan
`createElement` + `textContent` sehingga karakter `<` di nama item tampil
sebagai teks, bukan tag.

## Keputusan desain

- **Enam item awal** agar filter langsung terasa (kopi/nonkopi/snack).
- **Total** menghitung item *yang tampil* (setelah filter), bukan seluruh
  array — sesuai label "Item yang tampil". Boleh juga total semua; yang
  penting konsisten dengan label.
- **ID autonumber** `idBerikutnya` — jangan pakai `pesanan.length + 1`
  setelah hapus (id bisa bentrok).
- **Delegasi event** di `#daftar` dan `#filter`: tombol dibuat ulang tiap
  render, listener di induk tetap hidup.
- **Validasi**: `trim`, panjang nama, `Number` + `Number.isFinite` karena
  `.value` selalu string (`""` → `0`).
- **Empty state** saat filter tidak ketemu — jangan biarkan `<ul>` kosong
  tanpa penjelasan.

## Tailwind CDN

Sah untuk studi kasus ini (Modul 04). Jangan dipakai sebagai bukti
produksi Next.js. Prefix `md:grid-cols-2` = breakpoint 768px.

## Cek

```bash
node --check script.js
```

Perintah itu hanya parser; `document` tidak dijalankan. Uji perilaku di
browser: tambah, filter, hapus, Enter di form (harus tertahan
`preventDefault`).
