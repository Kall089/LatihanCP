# Jawaban 04 — Tailwind CSS

---

## A. Konsep

### A1 — b

Class utility satu tugas dirangkai di markup. Bukan inline style (tidak ada
`hover:`/`md:` di atribut `style`). Flexbox tetap harus dipahami.

### A2

Kira-kira:

```css
div {
  display: flex;
  align-items: center;
  justify-content: space-between;
  gap: 1rem;
  padding: 1.5rem;
  background: #fff;
  border-radius: 0.75rem;
  box-shadow: 0 1px 3px rgb(0 0 0 / 0.1);
}
```

(`p-6` = 1.5rem, `gap-4` = 1rem, `rounded-xl` = 0.75rem.)

### A3

Contoh: prefix `hover:` / `focus-visible:`; prefix `md:` (media query);
skala tema (`p-4` bukan 13px acak); specificity yang bisa dioverride.

### A4 — b

1 unit = 0.25rem = 4px (root 16px). `p-4` = 16px = 1rem, bukan 4px.

### A5

360px → 1 kolom (`grid-cols-1`). 800px ≥768 (`md`) → 2. 1300px ≥1024 (`lg`)
→ 3.

### A6

CDN menghasilkan CSS besar di runtime, versi bisa berubah, tidak cocok
produksi. Build memindai class di source dan hanya mengeluarkan yang terpakai
(sering <10 KB), plus tema kustom.

### A7

Scanner tidak melihat string utuh `bg-red-500`, jadi class **tidak masuk**
CSS produksi — latar hilang. Tulis lengkap:

```jsx
className={warna === "merah" ? "bg-red-500" : "bg-sky-500"}
```

### A8 — b

`hover:bg-sky-700`. Bukan pseudo CSS mentah dan bukan `onHover`.

### A9

Dasar (HP): `hidden` = `display: none`. `md:block` mulai 768px =
`display: block`. Mobile-first: sembunyikan dulu, tampilkan saat layar
cukup.

### A10

500px: `w-full` mengisi parent, `max-w-4xl` (56rem/896px) tidak memotong.
1400px: lebar dibatasi 896px, `mx-auto` menengahkan sisa ruang.

---

## B. Praktik

### B1

```html
<article class="rounded-2xl bg-white p-5 shadow-sm">
  <h2 class="text-xl font-bold">Kopi Susu Senja</h2>
  <p class="mt-2 text-slate-600">Susu fresh dan gula aren.</p>
  <button type="button"
    class="mt-4 rounded-lg bg-sky-600 px-4 py-2 text-white transition hover:bg-sky-700">
    Pesan
  </button>
</article>
```

### B2

```html
<div class="grid grid-cols-1 gap-6 sm:grid-cols-2 lg:grid-cols-3">
  <!-- tiga kartu -->
</div>
```

### B3

```html
<button type="button"
  class="rounded-lg bg-sky-600 px-4 py-2 text-white
         focus-visible:outline-none focus-visible:ring-2
         focus-visible:ring-sky-400 focus-visible:ring-offset-2">
  Simpan
</button>
<!-- focus-visible: cincin hanya untuk navigasi keyboard, bukan tiap klik mouse -->
```
