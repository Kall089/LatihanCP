# 02 — State, event, dan form

[← JSX dan props](01-jsx-komponen-props-children.md) · [Daftar](README.md) · [Lanjut: list dan key →](03-list-key-conditional.md)

State adalah data yang **milik komponen** dan bisa berubah karena interaksi. Event handler merespons klik, ketikan, dan pengiriman form. Form controlled membuat nilai input mengikuti state React.

## Daftar isi

- [useState](#usestate)
- [Setter bentuk nilai dan bentuk fungsi](#setter-bentuk-nilai-dan-bentuk-fungsi)
- [Beberapa state vs satu object](#beberapa-state-vs-satu-object)
- [Event dasar](#event-dasar)
- [Argumen ke handler](#argumen-ke-handler)
- [Form controlled: teks](#form-controlled-teks)
- [Checkbox, radio, select, textarea](#checkbox-radio-select-textarea)
- [Mencegah submit bawaan](#mencegah-submit-bawaan)
- [Update object](#update-object)
- [Update array](#update-array)
- [Object bersarang](#object-bersarang)
- [Batching setter](#batching-setter)
- [State sebagai snapshot](#state-sebagai-snapshot)
- [Lifting state](#lifting-state)
- [Input tidak terkontrol secara singkat](#input-tidak-terkontrol-secara-singkat)
- [Validasi sederhana](#validasi-sederhana)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)
- [Menyimpan fungsi di state (jarang)](#menyimpan-fungsi-di-state-jarang)
- [onSubmit vs tombol terpisah](#onsubmit-vs-tombol-terpisah)
- [Checkbox “pilih semua”](#checkbox-pilih-semua)

## useState

**Untuk apa:** menyimpan nilai yang memengaruhi tampilan dan berubah selama komponen hidup.

```jsx
import { useState } from "react";

export default function App() {
  const [jumlah, setJumlah] = useState(0);

  return (
    <div>
      <p aria-live="polite">Jumlah: {jumlah}</p>
      <button type="button" onClick={() => setJumlah(jumlah + 1)}>
        Tambah
      </button>
      <button type="button" onClick={() => setJumlah(0)}>
        Reset
      </button>
    </div>
  );
}
```

`useState(0)` mengembalikan pasangan: nilai saat ini dan fungsi setter. Saat `setJumlah` dipanggil dengan nilai berbeda, React merencanakan render ulang. Nama bebas, konvensi `const [x, setX]`.

Argument `useState` adalah nilai awal, hanya dipakai pada render pertama. `useState([])`, `useState("")`, `useState(false)`, `useState(null)` semuanya valid.

Jika nilai awal mahal dihitung, kirim fungsi:

```jsx
const [data, setData] = useState(() => JSON.parse(localStorage.getItem("draft") || "[]"));
```

Fungsi inisialisasi jalan sekali, bukan setiap render.

Jangan memanggil `useState` di dalam `if`, loop, atau fungsi bersarang. Lihat [aturan Hooks](12-aturan-hooks-kesalahan.md).

**Biasanya digabungkan dengan:** event handler, form, `map` untuk daftar, dan Effect jika state harus disinkronkan ke luar React. [useState](https://react.dev/reference/react/useState).

## Setter bentuk nilai dan bentuk fungsi

**Untuk apa:** memilih cara memperbarui state agar tidak memakai nilai yang kedaluwarsa.

```jsx
import { useState } from "react";

export default function App() {
  const [jumlah, setJumlah] = useState(0);

  function tambahTigaSalah() {
    setJumlah(jumlah + 1);
    setJumlah(jumlah + 1);
    setJumlah(jumlah + 1);
  }

  function tambahTigaBenar() {
    setJumlah((lama) => lama + 1);
    setJumlah((lama) => lama + 1);
    setJumlah((lama) => lama + 1);
  }

  return (
    <>
      <p>{jumlah}</p>
      <button type="button" onClick={tambahTigaSalah}>+1 tiga kali (salah)</button>
      <button type="button" onClick={tambahTigaBenar}>+1 tiga kali (benar)</button>
    </>
  );
}
```

`setJumlah(jumlah + 1)` tiga kali dalam satu handler memakai snapshot `jumlah` yang sama, jadi hasilnya +1, bukan +3. `setJumlah((lama) => lama + 1)` membaca nilai antrian terbaru.

Pakai bentuk fungsi jika:

- nilai baru bergantung pada nilai lama
- setter dipanggil dari timer, Effect, atau callback yang mungkin menutup nilai lama
- beberapa update terjadi berurutan

Pakai bentuk nilai jika mengganti seluruh nilai tanpa melihat yang lama: `setNama("")`, `setTerbuka(true)`.

Setter mengabaikan update jika nilai baru adalah `Object.is` sama dengan nilai lama. `setJumlah(0)` saat sudah `0` tidak merender ulang.

**Biasanya digabungkan dengan:** counter, antrian update, dan setter di dalam `setInterval`.

## Beberapa state vs satu object

**Untuk apa:** memutuskan apakah tiap field punya `useState` sendiri atau digabung.

```jsx
import { useState } from "react";

export default function App() {
  const [nama, setNama] = useState("");
  const [kota, setKota] = useState("");
  const [setuju, setSetuju] = useState(false);

  return (
    <form>
      <input value={nama} onChange={(e) => setNama(e.target.value)} />
      <input value={kota} onChange={(e) => setKota(e.target.value)} />
      <input
        type="checkbox"
        checked={setuju}
        onChange={(e) => setSetuju(e.target.checked)}
      />
    </form>
  );
}
```

Beberapa `useState` lebih mudah jika field berubah sendiri-sendiri. Gabungkan ke object jika field selalu di-update bersama, atau jika bentuknya meniru record server:

```jsx
const [profil, setProfil] = useState({ nama: "", kota: "" });

function ubahField(event) {
  const { name, value } = event.target;
  setProfil((lama) => ({ ...lama, [name]: value }));
}
```

Jangan meniru “satu class state besar” tanpa alasan. Jangan juga memecah object server menjadi puluhan state jika kamu hanya menampilkannya lalu mengirim kembali.

**Biasanya digabungkan dengan:** form banyak field, `useReducer` jika aksi mulai rumit. Lihat [file 07](07-useReducer-useSyncExternalStore.md).

## Event dasar

**Untuk apa:** menjalankan kode saat pengguna berinteraksi.

```jsx
export default function App() {
  function handleKlik() {
    console.log("Diklik");
  }

  return (
    <button type="button" onClick={handleKlik}>
      Simpan
    </button>
  );
}
```

React mengirim **SyntheticEvent**: pembungkus event browser agar nama dan perilaku seragam. Kamu tetap memakai `event.preventDefault()`, `event.target`, `event.currentTarget`.

Event yang sering dipakai:

| Event | Dipakai pada |
| --- | --- |
| `onClick` | tombol, kartu yang bisa diklik |
| `onChange` | input, select, textarea |
| `onSubmit` | form |
| `onInput` | ketikan per karakter (jarang diperlukan jika sudah `onChange`) |
| `onFocus` / `onBlur` | fokus field |
| `onKeyDown` | pintasan papan tombol |
| `onMouseEnter` / `onMouseLeave` | hover |
| `onPointerDown` | pointer umum (mouse/touch) |

Handler adalah fungsi. Jangan menaruh side effect berat langsung di tubuh render.

**Biasanya digabungkan dengan:** `useState`, `preventDefault` pada form, dan props callback ke induk.

## Argumen ke handler

**Untuk apa:** mengirim id item atau data tambahan saat event terjadi.

```jsx
const produk = [
  { id: 1, nama: "Buku" },
  { id: 2, nama: "Pensil" },
];

export default function App() {
  function pilih(id) {
    console.log("Memilih", id);
  }

  return (
    <ul>
      {produk.map((item) => (
        <li key={item.id}>
          <button type="button" onClick={() => pilih(item.id)}>
            {item.nama}
          </button>
        </li>
      ))}
    </ul>
  );
}
```

Tiga pola:

```jsx
onClick={handleKlik}
onClick={() => pilih(item.id)}
onClick={(event) => pilih(event, item.id)}
```

Pola yang salah:

```jsx
onClick={pilih(item.id)}
```

Itu menjalankan `pilih` saat render, lalu `onClick` menerima **hasil kembalian** (sering `undefined`).

Jika handler tidak butuh event, jangan buat pembungkus kosong yang tidak perlu: `onClick={handleKlik}` lebih jelas daripada `onClick={() => handleKlik()}`.

**Biasanya digabungkan dengan:** daftar, hapus item, dan form dinamis.

## Form controlled: teks

**Untuk apa:** membuat React menjadi sumber kebenaran nilai input.

```jsx
import { useState } from "react";

export default function App() {
  const [nama, setNama] = useState("");
  const [pesan, setPesan] = useState("");

  function kirim(event) {
    event.preventDefault();
    const bersih = nama.trim();
    setPesan(bersih ? `Halo, ${bersih}!` : "Nama perlu diisi.");
  }

  return (
    <form onSubmit={kirim}>
      <label htmlFor="nama">Nama</label>
      <input
        id="nama"
        value={nama}
        onChange={(event) => setNama(event.target.value)}
        autoComplete="name"
        required
      />
      <button type="submit">Sapa</button>
      <p role="status">{pesan}</p>
    </form>
  );
}
```

Pasangan wajib: `value` + `onChange`. Tanpa `onChange`, input tampak macet karena React terus menulis nilai lama.

`event.target.value` selalu **string**, termasuk pada `type="number"`. Konversi saat menghitung:

```jsx
const [umur, setUmur] = useState("");

function handleUmur(event) {
  setUmur(event.target.value);
}

const umurAngka = Number(umur);
```

Menyimpan string kosong memudahkan input tetap bisa dikosongkan. Menyimpan `0` sebagai awal `type="number"` sering membingungkan.

**Biasanya digabungkan dengan:** filter daftar, validasi, dan `fetch` POST ke backend.

## Checkbox, radio, select, textarea

**Untuk apa:** mengontrol jenis input lain dengan state yang sesuai.

Checkbox memakai `checked` dan `event.target.checked`:

```jsx
const [setuju, setSetuju] = useState(false);

<input
  type="checkbox"
  checked={setuju}
  onChange={(event) => setSetuju(event.target.checked)}
/>
```

Beberapa checkbox (set pilihan):

```jsx
const [minat, setMinat] = useState([]);

function toggleMinat(nilai) {
  setMinat((lama) =>
    lama.includes(nilai)
      ? lama.filter((item) => item !== nilai)
      : [...lama, nilai]
  );
}
```

Radio memakai satu string:

```jsx
const [kurir, setKurir] = useState("reguler");

<label>
  <input
    type="radio"
    name="kurir"
    value="reguler"
    checked={kurir === "reguler"}
    onChange={(event) => setKurir(event.target.value)}
  />
  Reguler
</label>
```

Select:

```jsx
const [kota, setKota] = useState("bdg");

<select value={kota} onChange={(event) => setKota(event.target.value)}>
  <option value="bdg">Bandung</option>
  <option value="jkt">Jakarta</option>
</select>
```

Textarea di JSX memakai `value`, bukan isi di antara tag:

```jsx
<textarea
  value={catatan}
  onChange={(event) => setCatatan(event.target.value)}
  rows={4}
/>
```

**Biasanya digabungkan dengan:** object form, `name` pada input, dan pengiriman JSON ke API.

## Mencegah submit bawaan

**Untuk apa:** menahan reload halaman saat form dikirim, lalu memproses data di JavaScript.

```jsx
function handleSubmit(event) {
  event.preventDefault();
  // baca state, validasi, fetch
}
```

Tanpa `preventDefault`, browser mengirim form secara klasik dan mereload. Di aplikasi React, itu biasanya menghapus state.

Tombol di dalam form default-nya `type="submit"`. Tombol aksi lain harus `type="button"` agar tidak mengirim form.

```jsx
<form onSubmit={kirim}>
  <button type="submit">Simpan</button>
  <button type="button" onClick={batal}>Batal</button>
</form>
```

**Biasanya digabungkan dengan:** `fetch`, pesan error, dan menonaktifkan tombol saat `sedangKirim`.

## Update object

**Untuk apa:** mengubah sebagian field tanpa memutasi object yang sedang dipakai React.

```jsx
import { useState } from "react";

export default function App() {
  const [profil, setProfil] = useState({
    nama: "Haikal",
    kota: "Bandung",
  });

  function pindahKota() {
    setProfil((lama) => ({ ...lama, kota: "Jakarta" }));
  }

  return (
    <>
      <p>{profil.nama} — {profil.kota}</p>
      <button type="button" onClick={pindahKota}>Pindah kota</button>
    </>
  );
}
```

Salah:

```jsx
profil.kota = "Jakarta";
setProfil(profil);
```

Object yang sama (referensi sama) bisa membuat React mengira tidak ada perubahan. Selalu buat object baru: `{ ...lama, kota: "Jakarta" }`.

Spread hanya menyalin tingkat pertama. Field yang tidak disebut tetap sama. Field yang disebut menimpa.

**Biasanya digabungkan dengan:** form profil, pengaturan, dan payload API.

## Update array

**Untuk apa:** menambah, menghapus, mengganti, dan mengurutkan item di state daftar.

```jsx
import { useState } from "react";

export default function App() {
  const [produk, setProduk] = useState([
    { id: 1, nama: "Buku", stok: 3 },
  ]);

  function tambah(itemBaru) {
    setProduk((lama) => [...lama, itemBaru]);
  }

  function hapus(id) {
    setProduk((lama) => lama.filter((item) => item.id !== id));
  }

  function ubahStok(id, stok) {
    setProduk((lama) =>
      lama.map((item) => (item.id === id ? { ...item, stok } : item))
    );
  }

  function urutNama() {
    setProduk((lama) =>
      [...lama].sort((a, b) => a.nama.localeCompare(b.nama, "id"))
    );
  }

  return (
    <div>
      <button type="button" onClick={() => tambah({ id: Date.now(), nama: "Pensil", stok: 5 })}>
        Tambah
      </button>
      <button type="button" onClick={urutNama}>Urutkan</button>
      <ul>
        {produk.map((item) => (
          <li key={item.id}>
            {item.nama} ({item.stok})
            <button type="button" onClick={() => ubahStok(item.id, item.stok + 1)}>+</button>
            <button type="button" onClick={() => hapus(item.id)}>Hapus</button>
          </li>
        ))}
      </ul>
    </div>
  );
}
```

Hindari `push`, `splice`, `sort` langsung pada array state. `sort` mengubah array asal; salin dulu `[...lama].sort(...)`.

`Date.now()` sebagai id hanya untuk latihan. Di data sungguhan pakai id dari server atau `crypto.randomUUID()`.

**Biasanya digabungkan dengan:** `key` yang stabil, form tambah item, dan CRUD antarmuka. Lihat [file 03](03-list-key-conditional.md).

## Object bersarang

**Untuk apa:** mengubah field dalam yang bersarang tanpa merusak sisa object.

```jsx
const [alamat, setAlamat] = useState({
  pengirim: { kota: "Bandung", kode: "40123" },
  penerima: { kota: "Jakarta", kode: "10110" },
});

function ubahKotaPenerima(kota) {
  setAlamat((lama) => ({
    ...lama,
    penerima: { ...lama.penerima, kota },
  }));
}
```

Setiap tingkat yang berubah perlu disalin. `...lama` saja tidak menyalin `penerima` secara dalam; tanpa salinan `penerima`, kamu masih memutasi object dalam yang sama.

Jika bersarangnya dalam sekali, pertimbangkan meratakan state atau memakai `useReducer`. Library seperti Immer (`useImmer`) membantu, tetapi tidak wajib untuk tugas kecil.

**Biasanya digabungkan dengan:** form alamat, pengaturan bertingkat, dan reducer.

## Batching setter

**Untuk apa:** memahami bahwa beberapa `setState` dalam satu event digabung menjadi satu render.

```jsx
function handleKlik() {
  setNama("Haikal");
  setKota("Bandung");
  setLangkah(2);
}
```

React 18+ menggabungkan update di event, timeout, dan Promise. Tiga setter di atas biasanya menghasilkan **satu** render, bukan tiga. Itu bagus: tampilan tidak berkedip di tengah jalan.

Jangan mengandalkan membaca state baru di baris berikutnya:

```jsx
setJumlah(jumlah + 1);
console.log(jumlah); // masih nilai lama
```

Pakai variabel lokal jika kamu butuh nilai berikutnya sekarang:

```jsx
const berikutnya = jumlah + 1;
setJumlah(berikutnya);
console.log(berikutnya);
```

Atau bentuk fungsi jika hanya setter yang harus berurutan.

**Biasanya digabungkan dengan:** form multi-field dan transisi langkah wizard.

## State sebagai snapshot

**Untuk apa:** menghindari bug “nilai belum berubah” di dalam handler yang sama.

```jsx
import { useState } from "react";

export default function App() {
  const [n, setN] = useState(0);

  function handleKlik() {
    setN(n + 1);
    alert(n); // masih angka sebelum klik
  }

  return <button type="button" onClick={handleKlik}>{n}</button>;
}
```

Saat render, `n` adalah foto. Handler menutup foto itu. `setN` tidak mengubah variabel `n` di handler yang sedang berjalan; ia meminta render berikutnya dengan foto baru.

Akibatnya: timer yang dibuat dengan `n` lama tetap melihat `n` lama, kecuali memakai bentuk fungsi atau ref. Lihat [useRef](05-useRef-useImperativeHandle-forwardRef.md) untuk nilai yang selalu mutakhir tanpa render.

**Biasanya digabungkan dengan:** `useEffect` berdependensi, `useRef` untuk nilai terkini, dan bentuk fungsi setter.

## Lifting state

**Untuk apa:** menaikkan state ke induk terdekat yang menjadi nenek moyang bersama, agar dua anak membaca data yang sama.

```jsx
import { useState } from "react";

function KotakPencarian({ kata, onGanti }) {
  return (
    <input
      value={kata}
      onChange={(event) => onGanti(event.target.value)}
      placeholder="Cari"
    />
  );
}

function Hasil({ kata }) {
  return <p>Mencari: {kata || "(kosong)"}</p>;
}

export default function App() {
  const [kata, setKata] = useState("");
  return (
    <>
      <KotakPencarian kata={kata} onGanti={setKata} />
      <Hasil kata={kata} />
    </>
  );
}
```

Jika `kata` disimpan di `KotakPencarian`, `Hasil` tidak bisa membacanya. Naikkan ke `App`. Jangan langsung meloncat ke Context jika hanya dua komponen berdekatan.

**Biasanya digabungkan dengan:** pencarian + daftar, wizard, dan kelak Context jika jaraknya jauh. Lihat [file 08](08-context-useContext-useId.md).

## Input tidak terkontrol secara singkat

**Untuk apa:** membaca nilai input dari DOM hanya saat perlu, tanpa state per ketikan.

```jsx
import { useRef } from "react";

export default function App() {
  const namaRef = useRef(null);
  const [pesan, setPesan] = useState("");

  function kirim(event) {
    event.preventDefault();
    setPesan(`Halo, ${namaRef.current.value}`);
  }

  return (
    <form onSubmit={kirim}>
      <label htmlFor="nama">Nama</label>
      <input id="nama" ref={namaRef} defaultValue="" />
      <button type="submit">Kirim</button>
      <p>{pesan}</p>
    </form>
  );
}
```

`defaultValue` (atau `defaultChecked`) mengatur nilai awal DOM. Setelah itu React tidak mengendalikan ketikan. Cocok untuk form sederhana yang hanya dibaca saat submit, atau integrasi library non-React.

Untuk filter live, validasi per ketikan, atau menonaktifkan tombol berdasarkan isi, pakai controlled. Jangan mencampur `value` dan `defaultValue` pada input yang sama.

**Biasanya digabungkan dengan:** `useRef`, form “kirim lalu selesai”, dan file input (`type="file"` hampir selalu tidak terkontrol).

## Validasi sederhana

**Untuk apa:** menampilkan pesan sebelum data dikirim.

```jsx
import { useState } from "react";

export default function App() {
  const [email, setEmail] = useState("");
  const [error, setError] = useState("");

  function kirim(event) {
    event.preventDefault();
    if (!email.includes("@")) {
      setError("Email tidak valid.");
      return;
    }
    setError("");
    console.log("Kirim", email);
  }

  return (
    <form onSubmit={kirim} noValidate>
      <label htmlFor="email">Email</label>
      <input
        id="email"
        type="email"
        value={email}
        onChange={(event) => setEmail(event.target.value)}
        aria-invalid={Boolean(error)}
        aria-describedby={error ? "email-error" : undefined}
      />
      {error && (
        <p id="email-error" role="alert">
          {error}
        </p>
      )}
      <button type="submit">Daftar</button>
    </form>
  );
}
```

`noValidate` menonaktifkan popup bawaan browser agar kamu memakai pesan sendiri. Untuk tugas kecil, validasi HTML (`required`, `type="email"`, `minLength`) sudah cukup tanpa state error.

Jangan hanya memvalidasi di client jika data masuk ke server. Server tetap harus memeriksa.

**Biasanya digabungkan dengan:** `aria-invalid`, menonaktifkan submit saat `sedangKirim`, dan pesan dari API.

## Kesalahan umum bab ini

- **`onClick={setJumlah(1)}`.** Setter jalan saat render, bisa loop tak hingga. Tulis `onClick={() => setJumlah(1)}`.
- **Mutasi array/object lalu `setState` object yang sama.** React bisa melewati render.
- **Membaca state langsung setelah `setState` dan mengira sudah baru.**
- **Input `value` tanpa `onChange`.**
- **Checkbox memakai `value` + `event.target.value`.** Pakai `checked` + `checked`.
- **Semua tombol di form tanpa `type`.** Klik “Hapus” ikut mensubmit.
- **`push` ke state array.**
- **Menyimpan nilai yang bisa dihitung:** total harga dari daftar tidak perlu state sendiri.

Latihan: buat daftar tugas. Input controlled menambah item, tombol menandai selesai dengan `map`, tombol hapus dengan `filter`.

## Menyimpan fungsi di state (jarang)

**Untuk apa:** mengetahui bahwa `useState(fn)` memanggil `fn` sebagai initializer.

```jsx
const [fn, setFn] = useState(() => () => console.log("awal"));

// salah: useState menganggap ini initializer
// setFn(() => console.log("baru"));

setFn(() => () => console.log("baru"));
```

Hampir tidak kamu butuhkan. Handler simpan di `useRef` atau `useCallback`, bukan state.

**Biasanya digabungkan dengan:** inisialisasi malas `useState(() => hitungMahal())` yang **bukan** menyimpan fungsi sebagai nilai.

## onSubmit vs tombol terpisah

**Untuk apa:** memilih elemen yang memicu pengiriman.

```jsx
<form onSubmit={kirim}>
  <button type="submit">Simpan</button>
</form>
```

Enter di input teks mensubmit form. Itu fitur. Jika kamu hanya `onClick` pada tombol tanpa `onSubmit`, Enter tidak jalan.

Jangan menaruh `onSubmit` dan `onClick` submit yang keduanya `fetch` — dobel. Satu jalur: `onSubmit`.

**Biasanya digabungkan dengan:** `type="submit"`, dan `type="button"` untuk aksi lain.

## Checkbox “pilih semua”

**Untuk apa:** state turunan dari daftar, bukan boolean terpisah yang bisa tidak sinkron.

```jsx
const semua = item.length > 0 && item.every((x) => x.pilih);
const sebagian = item.some((x) => x.pilih) && !semua;

function toggleSemua(event) {
  const nilai = event.target.checked;
  setItem((lama) => lama.map((x) => ({ ...x, pilih: nilai })));
}

<input
  type="checkbox"
  checked={semua}
  ref={(el) => {
    if (el) el.indeterminate = sebagian;
  }}
  onChange={toggleSemua}
/>
```

`indeterminate` adalah properti DOM, bukan atribut React yang andal di semua versi sebagai prop — callback ref mengisinya. `semua` dihitung dari data.

**Biasanya digabungkan dengan:** update array, `key` id, dan aksi massal hapus.
