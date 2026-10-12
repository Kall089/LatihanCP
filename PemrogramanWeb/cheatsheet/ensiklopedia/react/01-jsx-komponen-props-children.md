# 01 — JSX, komponen, props, dan children

[← Daftar ensiklopedia](README.md) · [Lanjut: state, event, form →](02-state-event-form.md)

React membangun antarmuka dari **komponen**: fungsi yang mengembalikan deskripsi tampilan. JSX adalah cara menulis deskripsi itu menyerupai HTML. Props mengirim data ke komponen anak. `children` adalah isi yang ditulis di antara tag pembuka dan penutup.

## Daftar isi

- [Function component](#function-component)
- [JSX dasar](#jsx-dasar)
- [Ekspresi di dalam kurung kurawal](#ekspresi-di-dalam-kurung-kurawal)
- [Atribut yang berbeda dari HTML](#atribut-yang-berbeda-dari-html)
- [Fragment](#fragment)
- [Props](#props)
- [Default pada props](#default-pada-props)
- [Children](#children)
- [Props callback](#props-callback)
- [Spread props](#spread-props)
- [Komposisi layout](#komposisi-layout)
- [Komponen murni](#komponen-murni)
- [createElement di balik JSX](#createelement-di-balik-jsx)
- [Komentar dan beberapa akar](#komentar-dan-beberapa-akar)
- [Props boolean dan object](#props-boolean-dan-object)
- [Slot sederhana dengan children](#slot-sederhana-dengan-children)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)
- [children sebagai fungsi (render props)](#children-sebagai-fungsi-render-props)
- [dangerouslySetInnerHTML](#dangerouslysetinnerhtml)
- [Syarat komponen bisa dipecah](#syarat-komponen-bisa-dipecah)

## Function component

**Untuk apa:** memecah halaman menjadi potongan yang punya nama, bisa diuji, dan bisa dipakai ulang.

```jsx
function Sapaan() {
  return <h1>Halo, Haikal</h1>;
}

export default function App() {
  return (
    <main>
      <Sapaan />
      <p>Selamat belajar React.</p>
    </main>
  );
}
```

Nama komponen harus diawali huruf besar. `<sapaan />` akan dianggap sebagai tag HTML yang tidak dikenal, bukan komponenmu. Satu file biasanya mengekspor satu komponen utama dengan `export default`; komponen kecil di file yang sama boleh tanpa export.

Komponen adalah fungsi JavaScript biasa. Ia menerima satu argument bernama `props` (object), lalu **harus mengembalikan** sesuatu yang React bisa render: elemen JSX, `null`, `false`, string, angka, atau array elemen. Jika fungsi tidak `return`, layar kosong.

**Biasanya digabungkan dengan:** props, `children`, CSS/CSS Modules, dan state jika tampilan berubah karena interaksi. [Komponen](https://react.dev/learn/your-first-component).

## JSX dasar

**Untuk apa:** menulis pohon UI tanpa merangkai string HTML.

```jsx
export default function App() {
  return (
    <article className="kartu">
      <h2>Buku JavaScript</h2>
      <p>Harga: Rp45.000</p>
      <img src="/buku.jpg" alt="Sampul buku JavaScript" />
      <input type="search" name="q" />
    </article>
  );
}
```

Aturan yang sering terlupakan:

- Semua tag harus ditutup. Tag kosong memakai bentuk mandiri: `<img />`, `<input />`, `<br />`.
- JSX harus punya **satu akar** per `return`, atau dibungkus Fragment.
- `class` menjadi `className`. `for` pada label menjadi `htmlFor`.
- Atribut boolean ditulis `<input required />` atau `<input required={true} />`.
- Gaya sebaris memakai object: `style={{ color: "navy" }}`, bukan string CSS.

JSX bukan HTML yang disisipkan ke JavaScript. Tool proyek (Vite, Next.js) mengubahnya menjadi panggilan `React.createElement` atau `jsx()`. File `.jsx` tidak dibuka langsung di browser tanpa proses itu.

**Biasanya digabungkan dengan:** CSS untuk tampilan, dan ekspresi `{...}` untuk data dinamis.

## Ekspresi di dalam kurung kurawal

**Untuk apa:** menyisipkan nilai JavaScript ke JSX: variabel, hitungan, pemanggilan fungsi, atau hasil kondisi.

```jsx
function formatRupiah(angka) {
  return `Rp${angka.toLocaleString("id-ID")}`;
}

export default function App() {
  const nama = "Buku CSS";
  const harga = 40000;
  const diskon = true;

  return (
    <section>
      <h1>{nama}</h1>
      <p>{formatRupiah(harga)}</p>
      <p>{diskon ? "Sedang diskon" : "Harga normal"}</p>
      <p>{harga > 0 && "Bisa dibeli"}</p>
    </section>
  );
}
```

Isi `{...}` harus berupa **ekspresi** (menghasilkan nilai), bukan pernyataan. Jangan tulis `if` atau `for` langsung di dalam JSX. Hitung dulu di tubuh fungsi, atau pakai ternary / `&&` / `map`.

Yang boleh di dalam `{...}`:

- literal: `{42}`, `{"teks"}`, `{true}` (boolean `true`/`false` tidak tampil)
- variabel dan properti: `{produk.nama}`
- panggilan fungsi: `{formatRupiah(harga)}`
- object untuk `style`: `style={{ marginTop: 8 }}`
- elemen lain: `{<strong>Penting</strong>}`

Yang tidak tampil: `true`, `false`, `null`, `undefined`. Hati-hati dengan angka `0`: `{stok && <p>Ada stok</p>}` akan menampilkan `0` jika stok nol. Tulis `{stok > 0 && <p>Ada stok</p>}`.

**Biasanya digabungkan dengan:** `map` untuk daftar, ternary untuk cabang tampilan, dan fungsi pembantu format.

## Atribut yang berbeda dari HTML

**Untuk apa:** menghindari bentrok nama dengan kata kunci JavaScript dan memakai konvensi DOM.

```jsx
export default function App() {
  return (
    <form>
      <label htmlFor="email">Email</label>
      <input
        id="email"
        className="isian"
        autoComplete="email"
        tabIndex={0}
        spellCheck={false}
      />
      <button type="submit" disabled={false}>
        Kirim
      </button>
    </form>
  );
}
```

Beberapa nama yang sering dipakai:

| HTML | JSX |
| --- | --- |
| `class` | `className` |
| `for` | `htmlFor` |
| `tabindex` | `tabIndex` |
| `colspan` | `colSpan` |
| `readonly` | `readOnly` |
| `maxlength` | `maxLength` |
| `cellpadding` | `cellPadding` |

Event memakai camelCase: `onClick`, `onChange`, `onSubmit`, `onInput`. Nilainya harus **fungsi**, bukan string: `onClick={handleKlik}`, bukan `onClick="handleKlik()"`.

Atribut `style` menerima object dengan nama properti camelCase:

```jsx
const kotak = {
  backgroundColor: "#f4f4f4",
  padding: 16,
  borderRadius: 8,
};

export default function App() {
  return <div style={kotak}>Kartu</div>;
}
```

Nilai angka untuk banyak properti CSS dianggap piksel. Untuk `opacity`, `zIndex`, `fontWeight`, dan beberapa properti lain, angka punya arti sendiri. Untuk `em`/`rem`/`%`, tulis string: `width: "50%"`.

**Biasanya digabungkan dengan:** form, aksesibilitas (`htmlFor`, `id`, `aria-*`), dan CSS eksternal agar `style` tidak menumpuk.

## Fragment

**Untuk apa:** mengelompokkan beberapa elemen tanpa menambah `<div>` di DOM.

```jsx
export default function App() {
  return (
    <>
      <h1>Toko Buku</h1>
      <p>Belanja catatan kuliah.</p>
    </>
  );
}
```

Bentuk singkat `<>...</>` tidak menerima `key`. Jika Fragment ada di dalam `map`, pakai bentuk bernama:

```jsx
import { Fragment } from "react";

const bagian = [
  { id: "a", judul: "Buku", isi: "JavaScript" },
  { id: "b", judul: "Alat", isi: "Pensil" },
];

export default function App() {
  return (
    <dl>
      {bagian.map((item) => (
        <Fragment key={item.id}>
          <dt>{item.judul}</dt>
          <dd>{item.isi}</dd>
        </Fragment>
      ))}
    </dl>
  );
}
```

Jangan membungkus semuanya dengan `<div>` hanya karena `return` membutuhkan satu akar. Pembungkus ekstra merusak CSS grid/flex dan semantik (`<p>` di dalam `<p>`, `<li>` di luar `<ul>`).

**Biasanya digabungkan dengan:** `map` yang mengembalikan beberapa saudara, dan layout yang sensitif terhadap jumlah anak DOM. Lihat juga katalog [Fragment](13-katalog-api-react.md#fragment).

## Props

**Untuk apa:** mengirim data dari induk ke anak. Anak **membaca** props; induk yang punya data.

```jsx
function KartuProduk({ nama, harga, stok }) {
  return (
    <article>
      <h2>{nama}</h2>
      <p>Rp{harga.toLocaleString("id-ID")}</p>
      <p>{stok > 0 ? `Stok ${stok}` : "Habis"}</p>
    </article>
  );
}

export default function App() {
  return (
    <KartuProduk
      nama="Buku JavaScript"
      harga={45000}
      stok={3}
    />
  );
}
```

Props adalah object. Dua cara membacanya sama saja:

```jsx
function KartuProduk(props) {
  return <h2>{props.nama}</h2>;
}

function KartuProduk({ nama }) {
  return <h2>{nama}</h2>;
}
```

Destructuring lebih ringkas jika kamu memakai beberapa field. Simpan `props` utuh jika hendak meneruskan sisa atribut ke elemen DOM.

Props **hanya dibaca**. Jangan menulis `props.harga = 0` di anak. Jika harga harus berubah, induk menyimpan state lalu mengirim nilai baru, atau mengirim callback.

String boleh ditulis tanpa kurung: `nama="Buku"`. Angka, boolean, object, array, dan fungsi memakai `{...}`: `harga={45000}`, `aktif={true}`, `onPilih={handlePilih}`.

**Biasanya digabungkan dengan:** `children`, callback untuk meminta induk mengubah data, dan daftar `map` yang mengirim satu item per kartu. [Passing props](https://react.dev/learn/passing-props-to-a-component).

## Default pada props

**Untuk apa:** memberi nilai cadangan jika pemanggil tidak mengirim prop.

```jsx
function Lencana({ teks = "Baru", warna = "hijau" }) {
  return <span className={`lencana lencana-${warna}`}>{teks}</span>;
}

export default function App() {
  return (
    <>
      <Lencana />
      <Lencana teks="Habis" warna="merah" />
    </>
  );
}
```

Default parameter pada destructuring adalah cara yang paling jelas di function component. Nilai default dipakai jika prop `undefined`, tetapi **tidak** dipakai jika pemanggil mengirim `null` atau string kosong.

Untuk object opsi:

```jsx
function Tabel({ kolom = [], baris = [] }) {
  return (
    <p>
      {kolom.length} kolom, {baris.length} baris
    </p>
  );
}
```

Jangan mengandalkan mutasi default. Jika default berupa array/object, dan kamu mengubahnya di dalam komponen, buat salinan terlebih dahulu atau hitung nilai turunan tanpa mengubah argument.

**Biasanya digabungkan dengan:** komponen UI yang punya banyak opsi opsional, seperti tombol, badge, dan kartu.

## Children

**Untuk apa:** mengisi “lubang” di tengah komponen. Induk yang memutuskan isi dalamnya.

```jsx
function Kartu({ judul, children }) {
  return (
    <section className="kartu">
      <h2>{judul}</h2>
      <div className="kartu-isi">{children}</div>
    </section>
  );
}

export default function App() {
  return (
    <Kartu judul="Pengumuman">
      <p>Praktikum diganti hari Jumat.</p>
      <button type="button">Saya mengerti</button>
    </Kartu>
  );
}
```

`children` adalah prop khusus: semua yang ditulis di antara `<Kartu>` dan `</Kartu>`. Bisa berupa teks, elemen, array elemen, atau `null`.

Pola ini membuat komponen pembungkus (kartu, modal, layout, tab) tetap umum. Jangan membuat puluhan props seperti `isi1`, `isi2`, `tombolTeks` jika isi dalamnya bebas.

`children` boleh tidak ada. Cek sebelum merender bagian opsional:

```jsx
function Panel({ children }) {
  return (
    <aside>
      {children ?? <p>Tidak ada isi.</p>}
    </aside>
  );
}
```

**Biasanya digabungkan dengan:** layout, modal, `createPortal`, dan Context Provider yang membungkus pohon anak.

## Props callback

**Untuk apa:** membiarkan anak **memberitahu** induk bahwa sesuatu terjadi, tanpa anak mengubah data induk secara langsung.

```jsx
function TombolTambah({ onTambah, label = "Tambah" }) {
  return (
    <button type="button" onClick={onTambah}>
      {label}
    </button>
  );
}

export default function App() {
  return (
    <TombolTambah
      label="Tambah ke keranjang"
      onTambah={() => {
        console.log("Induk menerima permintaan tambah");
      }}
    />
  );
}
```

Konvensi nama: `on` + kejadian (`onTambah`, `onHapus`, `onGanti`). Anak memanggil `onTambah()` atau `onHapus(id)`. Induk yang menjalankan `setState`.

Jika anak perlu mengirim data:

```jsx
function BarisProduk({ produk, onPilih }) {
  return (
    <button type="button" onClick={() => onPilih(produk.id)}>
      {produk.nama}
    </button>
  );
}
```

Jangan menulis `onClick={onPilih(produk.id)}` — itu memanggil fungsi saat render. Tulis fungsi yang menunggu klik: `() => onPilih(produk.id)`.

**Biasanya digabungkan dengan:** `useState` di induk, lifting state up, dan daftar item yang punya tombol aksi. Lihat [state dan event](02-state-event-form.md).

## Spread props

**Untuk apa:** meneruskan sisa atribut ke elemen DOM atau komponen lain tanpa menuliskan satu per satu.

```jsx
function InputTeks({ label, id, ...isian }) {
  return (
    <div>
      <label htmlFor={id}>{label}</label>
      <input id={id} type="text" {...isian} />
    </div>
  );
}

export default function App() {
  return (
    <InputTeks
      id="nama"
      label="Nama"
      name="nama"
      placeholder="Nama lengkap"
      required
    />
  );
}
```

`...isian` meneruskan `name`, `placeholder`, `required`, dan atribut lain ke `<input>`. Urutan penting: atribut yang ditulis **sesudah** spread menimpa nilai yang sama dari spread.

Hati-hati meneruskan seluruh `props` ke `<div>`. Prop milik komponenmu (`judul`, `onSimpan`) bukan atribut DOM yang valid dan bisa memicu peringatan. Ambil yang kamu butuhkan, lalu sebar sisanya.

**Biasanya digabungkan dengan:** komponen form terbungkus, library UI, dan `forwardRef` jika ref juga perlu diteruskan. Lihat [file 05](05-useRef-useImperativeHandle-forwardRef.md).

## Komposisi layout

**Untuk apa:** menyusun halaman dari bagian yang masing-masing kecil, bukan satu komponen raksasa.

```jsx
function Kepala({ judul }) {
  return (
    <header>
      <h1>{judul}</h1>
    </header>
  );
}

function Menu({ items }) {
  return (
    <nav>
      <ul>
        {items.map((item) => (
          <li key={item}>{item}</li>
        ))}
      </ul>
    </nav>
  );
}

function Layout({ children }) {
  return (
    <div className="layout">
      <Kepala judul="Toko Belajar" />
      <Menu items={["Beranda", "Produk", "Tentang"]} />
      <main>{children}</main>
    </div>
  );
}

export default function App() {
  return (
    <Layout>
      <p>Isi halaman beranda.</p>
    </Layout>
  );
}
```

Komposisi lebih fleksibel daripada pewarisan class. Jika dua halaman mirip, buat `Layout` yang menerima `children`. Jika hanya sebagian yang berbeda, kirim props atau children bernama (slot):

```jsx
function Laman({ samping, children }) {
  return (
    <div className="dua-kolom">
      <aside>{samping}</aside>
      <section>{children}</section>
    </div>
  );
}
```

**Biasanya digabungkan dengan:** `children`, Context untuk tema/user, dan routing di Next.js untuk `layout.js`.

## Komponen murni

**Untuk apa:** membuat hasil render dapat ditebak: input (props + state) yang sama menghasilkan JSX yang sama.

```jsx
function Pajak({ harga }) {
  const pajak = Math.round(harga * 0.11);
  return <p>Pajak: Rp{pajak.toLocaleString("id-ID")}</p>;
}
```

Selama render, jangan:

- mengubah variabel di luar komponen
- menulis ke localStorage
- memanggil `fetch`
- memanggil `setState` tanpa syarat

Pekerjaan samping diletakkan di event handler atau Effect. React boleh merender komponen dua kali di development (Strict Mode) untuk menemukan ketidakmurnian.

Perhitungan turunan **boleh** dilakukan saat render:

```jsx
function RingkasanKeranjang({ item }) {
  const total = item.reduce((jumlah, baris) => jumlah + baris.harga, 0);
  return <p>Total: Rp{total.toLocaleString("id-ID")}</p>;
}
```

Tidak perlu `useEffect` hanya untuk menghitung `total` dari `item`.

**Biasanya digabungkan dengan:** `useMemo` jika hitungannya berat dan inputnya sering sama, serta Strict Mode saat development. Lihat [file 12](12-aturan-hooks-kesalahan.md).

## createElement di balik JSX

**Untuk apa:** memahami bahwa JSX adalah gula sintaksis, berguna saat debug atau menulis tanpa JSX.

```jsx
import { createElement } from "react";

export default function App() {
  return createElement(
    "h1",
    { className: "judul" },
    "Halo, ",
    createElement("span", null, "Haikal")
  );
}
```

Setara dengan:

```jsx
export default function App() {
  return (
    <h1 className="judul">
      Halo, <span>Haikal</span>
    </h1>
  );
}
```

Argument: tipe (`"h1"` atau komponen), props (`null` jika tidak ada), lalu children. Kamu hampir selalu menulis JSX. `createElement` muncul di stack trace dan di katalog API.

**Biasanya digabungkan dengan:** tooling, tes yang membandingkan elemen, dan pemahaman Fragment/`cloneElement`. Lihat [katalog createElement](13-katalog-api-react.md#createelement).

## Komentar dan beberapa akar

**Untuk apa:** menulis catatan di JSX dan mengembalikan lebih dari satu elemen.

Komentar di dalam JSX memakai kurung kurawal:

```jsx
export default function App() {
  return (
    <main>
      {/* Judul toko, jangan diubah jadi h2 */}
      <h1>Toko Belajar</h1>
    </main>
  );
}
```

`// komentar` di antara tag akan error. Di tubuh fungsi (di luar JSX) komentar biasa tetap valid.

Jika `return` berisi lebih dari satu elemen, bungkus Fragment atau induk semantik (`<main>`, `<section>`). Early return diperbolehkan sebelum JSX:

```jsx
function Profil({ user }) {
  if (!user) {
    return <p>Silakan masuk.</p>;
  }
  return <p>Halo, {user.nama}</p>;
}
```

**Biasanya digabungkan dengan:** render bersyarat di [file 03](03-list-key-conditional.md).

## Props boolean dan object

**Untuk apa:** mengirim tanda hidup/mati dan data terstruktur tanpa merancang puluhan prop datar.

```jsx
function Tombol({ primer, kecil, children }) {
  const kelas = [
    "tombol",
    primer ? "tombol-primer" : "tombol-biasa",
    kecil ? "tombol-kecil" : "",
  ]
    .filter(Boolean)
    .join(" ");

  return (
    <button type="button" className={kelas}>
      {children}
    </button>
  );
}

export default function App() {
  return (
    <>
      <Tombol primer>Simpan</Tombol>
      <Tombol kecil>Batal</Tombol>
    </>
  );
}
```

Menulis `<Tombol primer>` sama dengan `primer={true}`. Tidak menulis prop itu membuat nilainya `undefined` (dianggap palsu di kondisi).

Object sebagai props cocok untuk data yang sudah berbentuk record:

```jsx
function KartuProduk({ produk }) {
  return (
    <article>
      <h2>{produk.nama}</h2>
      <p>{produk.harga}</p>
    </article>
  );
}

<KartuProduk produk={{ id: 1, nama: "Pensil", harga: 3000 }} />
```

Membuat object baru di JSX setiap render (`produk={{ ... }}`) menghasilkan referensi baru. Itu tidak salah, tetapi komponen yang di-`memo` akan menganggap props berubah. Untuk data statis, simpan object di luar komponen atau di state induk.

**Biasanya digabungkan dengan:** CSS class dinamis, `React.memo`, dan daftar produk.

## Slot sederhana dengan children

**Untuk apa:** meniru “slot” (kepala, isi, kaki) tanpa library.

```jsx
function Dialog({ judul, kaki, children }) {
  return (
    <div className="dialog" role="dialog" aria-labelledby="judul-dialog">
      <h2 id="judul-dialog">{judul}</h2>
      <div className="dialog-isi">{children}</div>
      {kaki && <footer>{kaki}</footer>}
    </div>
  );
}

export default function App() {
  return (
    <Dialog
      judul="Hapus item?"
      kaki={
        <>
          <button type="button">Batal</button>
          <button type="button">Hapus</button>
        </>
      }
    >
      <p>Item tidak bisa dikembalikan.</p>
    </Dialog>
  );
}
```

`judul` string, `children` isi utama, `kaki` elemen aksi. Pola ini lebih fleksibel daripada `teksTombol1` / `teksTombol2`.

Jangan menaruh JSX besar sebagai default parameter. Jika slot kosong, render `null` atau jangan render footer.

**Biasanya digabungkan dengan:** `createPortal` untuk modal, dan state `terbuka` di induk. Lihat [file 11](11-portal-suspense-error-boundary.md).

## Kesalahan umum bab ini

- **Komponen diawali huruf kecil.** React mengiriminya ke DOM sebagai tag HTML.
- **Lupa `return`.** Fungsi berjalan tetapi tidak ada yang dirender.
- **Dua akar tanpa Fragment.** Compiler JSX menolaknya.
- **Memakai `class` dan `for`.** Harus `className` dan `htmlFor`.
- **Mengubah props di anak.** Data mengalir ke bawah; perubahan diminta lewat callback ke atas.
- **`onClick={fungsi()}`.** Fungsi jalan saat render. Pakai `onClick={fungsi}` atau `onClick={() => fungsi(arg)}`.
- **Menyimpan JSX di variabel lalu lupa merendernya.** Variabel elemen harus masuk ke `return`.
- **`{0 && <p>Kosong</p>}` menampilkan 0.** Bandingkan secara eksplisit.

Latihan: pecah halaman toko menjadi `Kepala`, `KartuProduk`, dan `Layout`. Kirim nama serta harga lewat props, dan taruh tombol di `children` kartu.

## children sebagai fungsi (render props)

**Untuk apa:** membiarkan induk menentukan tampilan, sementara anak menyediakan data.

```jsx
function DaftarNama({ item, children }) {
  return (
    <ul>
      {item.map((x) => (
        <li key={x.id}>{children(x)}</li>
      ))}
    </ul>
  );
}

export default function App() {
  const item = [{ id: 1, nama: "Buku" }];
  return (
    <DaftarNama item={item}>
      {(produk) => <strong>{produk.nama}</strong>}
    </DaftarNama>
  );
}
```

`children` di sini adalah fungsi. Pola ini jarang wajib; props `renderItem` lebih eksplisit. Tetap berguna dikenali saat membaca library.

**Biasanya digabungkan dengan:** daftar fleksibel, dan lebih sering: komponen `Kartu` biasa + `map` di induk.

## dangerouslySetInnerHTML

**Untuk apa:** menyisipkan HTML string — hampir selalu dihindari.

```jsx
function HtmlDariCms({ html }) {
  return <div dangerouslySetInnerHTML={{ __html: html }} />;
}
```

Nama sengaja menakutkan: XSS jika string berasal dari pengguna. Jangan pakai untuk markdown mentah tanpa sanitasi. Untuk tugas, tampilkan teks biasa `{html}` agar ter-escape.

**Biasanya digabungkan dengan:** sanitizer di server, bukan sebagai jalan pintas JSX.

## Syarat komponen bisa dipecah

**Untuk apa:** memutuskan kapan file baru layak.

Pecah jika:

- JSX mengulang (kartu, baris tabel)
- ada nama yang jelas (`MenuPengguna`)
- state lokal mandiri (input pencarian di header)

Jangan pecah hanya agar “terlihat rapi” menjadi 15 file berisi 5 baris. Satu file beberapa fungsi kecil di atas `App` sah untuk latihan.

**Biasanya digabungkan dengan:** props yang tidak lebih dari ~7 field; jika lebih, kirim object `produk` atau pecah lagi.
