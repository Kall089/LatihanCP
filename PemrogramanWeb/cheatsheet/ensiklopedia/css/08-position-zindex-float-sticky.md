# 08 — Position, z-index, float, sticky

[← Background](07-background-border-outline-shadow.md) · [Indeks](README.md) · [Transform →](09-transform-filter-transition-animation.md)

`position` memindahkan kotak relatif ke acuan. Flex/Grid tetap pilihan pertama untuk layout halaman. Position untuk: badge, dropdown, header nempel, modal, tooltip.

## Daftar isi

- [position static](#position-static)
- [relative](#relative)
- [absolute](#absolute)
- [fixed](#fixed)
- [sticky](#sticky)
- [inset top right bottom left](#inset-top-right-bottom-left)
- [Containing block](#containing-block)
- [z-index dan stacking context](#z-index-dan-stacking-context)
- [isolation](#isolation)
- [float dan clear](#float-dan-clear)
- [object dan shape](#object-dan-shape)
- [Peta Tailwind](#peta-tailwind)

## position static

**Untuk apa:** alur normal. `top/left/z-index` diabaikan.

```css
.biasa { position: static; }
```

Bawaan semua elemen. Tidak bisa jadi acuan `absolute` (kecuali lewat transform/filter lain — lihat containing block).

**Biasanya digabungkan dengan:** layout flow biasa.

## relative

**Untuk apa:** tetap di alur (masih makan ruang asli), bisa digeser dengan `top/right/...`, dan jadi acuan anak `absolute`.

```css
.kartu { position: relative; }

.kartu .badge {
  position: absolute;
  top: 0.75rem;
  right: 0.75rem;
}
```

Geser relatif:

```css
.geser {
  position: relative;
  top: 0.25rem;
}
```

Ruang semula tetap; elemen tetangga tidak merapat. Geser besar dengan `relative` membingungkan — pakai margin/flex.

**Biasanya digabungkan dengan:** anak `absolute`, `z-index` badge.

## absolute

**Untuk apa:** keluar alur. Posisinya relatif ke containing block terdekat yang bukan `static` (induk `relative`/`absolute`/`fixed`/`sticky`, atau yang punya `transform`/`filter`/`will-change` tertentu).

```css
.dropdown {
  position: absolute;
  top: calc(100% + 0.35rem);
  left: 0;
  z-index: 20;
}

.tutup {
  position: absolute;
  inset: 0.5rem 0.5rem auto auto;
}
```

Tidak mendorong saudara. Induk tanpa `relative` membuat dropdown “loncat” ke leluhur lain — bug paling umum.

**Biasanya digabungkan dengan:** induk `relative`, `z-index`, `inset`.

### Menengahkan absolute

**Untuk apa:** modal atau ikon di tengah induk.

```css
.pusat {
  position: absolute;
  top: 50%;
  left: 50%;
  translate: -50% -50%;
}
```

Bentuk lama: `transform: translate(-50%, -50%)`. Bentuk modern: properti `translate`.

Atau inset + margin:

```css
.pusat {
  position: absolute;
  inset: 0;
  margin: auto;
  width: max-content;
  height: max-content;
}
```

**Biasanya digabungkan dengan:** `width` diketahui atau `max-content`.

## fixed

**Untuk apa:** menempel ke viewport (umumnya), tetap saat halaman di-scroll.

```css
.bantuan {
  position: fixed;
  right: 1rem;
  bottom: 1rem;
  z-index: 40;
}

.header-tetap {
  position: fixed;
  top: 0;
  left: 0;
  right: 0;
  z-index: 30;
}
```

Konten halaman harus punya `padding-top` setinggi header, atau konten tertutup.

`fixed` di dalam induk yang punya `transform`, `filter`, `perspective`, atau `contain` tertentu menempel ke induk itu, bukan viewport. Itu sebab modal di dalam kartu yang di-`transform` “tidak fullscreen”.

**Biasanya digabungkan dengan:** `z-index` tinggi, `padding` pada `body`.

## sticky

**Untuk apa:** ikut alur sampai ambang scroll, lalu menempel.

```css
.header {
  position: sticky;
  top: 0;
  z-index: 10;
  background: white;
}

.th {
  position: sticky;
  top: 3.5rem;
  background: #f8fafc;
}

.kolom-meta {
  position: sticky;
  top: 1rem;
  align-self: start;
}
```

Syarat yang sering gagal:

1. Tidak ada `top`/`left`/… — sticky tidak tahu kapan nempel.
2. Induk `overflow: hidden/auto` memotong sticky (containing scroll box salah).
3. Induk persis setinggi sticky — tidak ada ruang untuk “nempel di dalam induk”.
4. Latar transparan: konten lewat kelihatan tembus.

Sticky hidup di dalam induknya. Habis induk ter-scroll pergi, sticky ikut pergi.

**Biasanya digabungkan dengan:** `top`, `z-index`, `background` solid, `scroll-margin-top` pada target.

## inset top right bottom left

**Untuk apa:** jarak ke tepi containing block.

```css
.overlay {
  position: fixed;
  inset: 0;
}

.sheet {
  position: fixed;
  inset: auto 0 0 0;
}

.logical {
  position: absolute;
  inset-inline-end: 0.75rem;
  inset-block-start: 0.75rem;
}
```

`inset: 0` = `top/right/bottom/left: 0` ( regangkan mengisi acuan). `inset: 1rem` = 1rem dari semua sisi.

`inset-inline` dan `inset-block` mengikuti arah tulisan.

Jika `top` dan `bottom` keduanya set serta `height: auto`, elemen meregang vertikal.

**Biasanya digabungkan dengan:** `position` selain `static`.

## Containing block

**Untuk apa:** tahu “0,0”-nya absolute/fixed.

Acuan `absolute`: leluhur terdekat dengan `position` bukan `static`. Jika tidak ada, awal viewport (initial containing block).

Acuan `fixed`: biasanya viewport, kecuali leluhur membentuk containing block khusus:

```css
.rusak {
  transform: translateZ(0);
}
```

Anak `fixed` di dalam `.rusak` menempel ke `.rusak`. Gejala: modal tidak menutupi navbar.

`filter`, `perspective`, `will-change: transform`, `contain: paint`, `backdrop-filter` bisa efek sama.

**Biasanya digabungkan dengan:** pindahkan modal ke `body` / portal React.

## z-index dan stacking context

**Untuk apa:** urutan cat di sumbu z. Hanya berlaku pada elemen yang **positioned** (`relative/absolute/fixed/sticky`) atau flex/grid item, plus beberapa properti lain.

```css
.header { position: sticky; z-index: 10; }
.dropdown { position: absolute; z-index: 20; }
.modal { position: fixed; z-index: 40; }
.toast { position: fixed; z-index: 50; }
```

Skala yang rapi (contoh): 0 konten, 10 sticky, 20 dropdown, 30 header fixed, 40 overlay, 50 toast. Jangan `99999` kecuali darurat.

`z-index` anak **tidak bisa** menembus stacking context induk. Kalau kartu punya `z-index: 1` atau `opacity: 0.99`, dropdown di dalam kartu kalah dari kartu berikutnya meski dropdown `z-index: 999`.

Yang membuat stacking context baru (pilihan yang sering):

- `position` + `z-index` selain `auto`
- `opacity` < 1
- `transform` selain `none`
- `filter` selain `none`
- `isolation: isolate`
- `will-change` tertentu
- `fixed`/`sticky` di banyak browser

**Biasanya digabungkan dengan:** `isolation: isolate` pada kartu agar badge lokal, portal untuk overlay global.

## isolation

**Untuk apa:** stacking context tanpa angka z-index.

```css
.kartu { isolation: isolate; }
```

`z-index: 1` pada badge hanya bersaing di dalam kartu.

**Biasanya digabungkan dengan:** daftar kartu, overlay gambar.

## float dan clear

### float

**Untuk apa:** mengalirkan kotak ke kiri/kanan, teks mengelilingi. Model layout lama.

```css
.artikel img.kiri {
  float: left;
  margin: 0 1rem 0.5rem 0;
  max-width: 40%;
}
```

Induk yang hanya berisi float **kecipak** (tinggi 0) kecuali ada clearfix / `display: flow-root`.

Jangan pakai float untuk kolom halaman. Itu tugas Grid/Flex.

**Biasanya digabungkan dengan:** `shape-outside` untuk teks mengelilingi, atau hindari sama sekali.

### clear

**Untuk apa:** menolak berdampingan dengan float.

```css
.artikel h2 { clear: both; }

.bersih::after {
  content: "";
  display: block;
  clear: both;
}
```

Clearfix klasik. Modern:

```css
.artikel { display: flow-root; }
```

**Biasanya digabungkan dengan:** konten ber-float, bukan navbar.

## object dan shape

**Untuk apa:** `shape-outside` membuat teks mengikuti bentuk float.

```css
img.bulat {
  float: left;
  width: 8rem;
  shape-outside: circle(50%);
  margin-right: 1rem;
}
```

Hanya bekerja bersama `float`.

**Biasanya digabungkan dengan:** artikel majalah, bukan UI app.

## Peta Tailwind

| CSS | Tailwind |
| --- | --- |
| `position: static` | `static` |
| `relative` | `relative` |
| `absolute` | `absolute` |
| `fixed` | `fixed` |
| `sticky` | `sticky` |
| `top: 0` | `top-0` |
| `right: 0.75rem` | `right-3` |
| `inset: 0` | `inset-0` |
| `inset-x: 0` | `inset-x-0` |
| `inset-y: 0` | `inset-y-0` |
| `top: 50%` | `top-1/2` |
| `z-index: 10` | `z-10` |
| `z-index: auto` | `z-auto` |
| `float: left` | `float-left` |
| `clear: both` | `clear-both` |
| `isolation: isolate` | `isolate` |

Badge:

```html
<article class="relative overflow-hidden rounded-xl">
  <span class="absolute top-3 right-3 z-10 rounded-full bg-amber-300 px-2 py-0.5 text-xs">Baru</span>
</article>
```

Header sticky:

```html
<header class="sticky top-0 z-10 border-b bg-white/90 backdrop-blur">
```

**Biasanya digabungkan dengan:** `scroll-mt-*` pada heading target.
