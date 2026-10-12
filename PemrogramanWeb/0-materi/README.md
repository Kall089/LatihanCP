# Peta Materi Pemrograman Web

Dokumen ini membantu memilih apa yang harus dipelajari, apa bukti bahwa sebuah
modul sudah dikuasai, dan kapan boleh melanjutkan. Baca `teori.md` pada folder
modul, kerjakan praktikum yang ditautkan, lalu gunakan checkpoint di bawah
tanpa membuka kunci.

## Cara memakai setiap modul

```text
diagnostik → teori → ketik ulang contoh → ubah contoh → praktikum TODO
           → uji kasus batas → latihan soal → refleksi → kunci jawaban
```

Mengetik ulang saja belum cukup. Setelah contoh berjalan, ubah minimal satu
input, satu aturan, dan satu bagian UI. Perubahan kecil membuktikan bahwa kamu
memahami hubungan antarbagiannya.

## Peta kompetensi dan checkpoint

| Modul | Kompetensi inti | Produk minimum | Checkpoint sebelum lanjut |
|---|---|---|---|
| 01 HTML | struktur & makna konten | halaman profil semantik | outline heading runtut; form punya label; HTML masuk akal tanpa CSS |
| 02 CSS | cascade, box model, selector | kartu profil rapi | mampu menjelaskan style yang menang dan menghitung ukuran kotak |
| 03 Layout | Flexbox, Grid, mobile-first | landing page responsif | tidak overflow pada 360/768/1280 px; bisa memilih Flex atau Grid dengan alasan |
| 04 Tailwind | utility, breakpoint, state | komponen kartu Tailwind | bisa menerjemahkan utility penting kembali ke CSS biasa |
| 05 JavaScript | data, DOM, event, state → render | daftar dinamis | Console bersih; input divalidasi; output pengguna tidak masuk `innerHTML` |
| 06 React | component, props, state, key | dashboard komponen | state tidak diduplikasi; data turun dan event naik |
| 07 Next.js | App Router, server/client, dynamic route | situs multi-halaman | `params` di-await; 404 bekerja; client component hanya bila perlu |
| 08 Proyek | arsitektur, kualitas, deployment | Learning Tracker | lint dan build lolos; responsif; aksesibel; punya empty/error state |

## Diagnostik awal

Jawab tanpa mencari. Jika belum bisa, gunakan kolom “mulai dari”.

1. Mengapa `<button>` lebih tepat daripada `<div onclick>` untuk aksi?
2. Apa bedanya margin, border, padding, dan content?
3. Kapan memakai Flexbox dan kapan memakai Grid?
4. Mengapa Tailwind tidak menghapus kebutuhan memahami CSS?
5. Apa beda data di variabel JavaScript dan tampilan di DOM?
6. Mengapa state React tidak boleh diubah langsung?
7. Apa yang membuat sebuah file perlu `"use client"`?
8. Apa perbedaan “berhasil di `npm run dev`” dan “siap dikumpulkan”?

| Nomor yang sulit | Mulai dari |
|---|---|
| 1 | Modul 01: semantik dan formulir |
| 2 | Modul 02: box model |
| 3 | Modul 03: dua sumbu dan layout 1D/2D |
| 4 | Modul 04: peta CSS → utility |
| 5 | Modul 05: DOM dan state → render |
| 6 | Modul 06: state dan aliran data |
| 7 | Modul 07: Server vs Client Component |
| 8 | Modul 08: checklist kualitas |

## Empat lapisan kualitas

Setiap tugas dinilai dari empat lapisan. Kerjakan berurutan:

1. **Benar:** fitur menghasilkan nilai dan navigasi yang tepat.
2. **Tahan:** input kosong/salah, data kosong, URL tidak valid, dan jaringan
   gagal tidak membuat halaman blank.
3. **Dapat dipakai:** responsif, bisa dinavigasi dengan keyboard, fokus
   terlihat, label/alt/heading bermakna.
4. **Dapat dirawat:** nama jelas, komponen tidak terlalu besar, data tidak
   diduplikasi, dan pemeriksaan otomatis lolos.

Animasi dan dekorasi berada setelah empat lapisan ini, bukan menggantikannya.

## Cara menguji tanpa alat khusus

- **HTML/CSS:** buka DevTools, cek Elements, Console, dan mode responsif.
- **Keyboard:** lepas mouse, tekan `Tab`, `Shift+Tab`, `Enter`, dan `Space`.
- **JavaScript:** coba input kosong, spasi, angka negatif, klik cepat berulang,
  dan daftar kosong.
- **React/Next.js:** cek warning key/hydration di Console, lalu jalankan
  `npm run lint` (jika tersedia) dan `npm run build`.
- **URL:** buka rute valid, rute detail tidak valid, refresh langsung pada
  rute detail, dan kembali melalui navigasi internal.

## Setelah modul inti

Baca [`PENGAYAAN-HTTP-API-KUALITAS-WEB.md`](PENGAYAAN-HTTP-API-KUALITAS-WEB.md).
Materi pengayaan ini mengenalkan HTTP, `fetch`, `async/await`, state
loading/error/empty/success, CORS, keamanan output, aksesibilitas, dan strategi
tes. Konsep tersebut adalah jembatan menuju aplikasi yang memakai data nyata.

Kembali ke [README utama](../README.md).
