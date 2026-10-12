# Latihan Soal 06 — React Komponen

Kerjakan tanpa kunci. Materi:
[`../../0-materi/06-react-komponen/teori.md`](../../0-materi/06-react-komponen/teori.md).

---

## A. Soal konsep (10)

### A1. Pilihan ganda — komponen

- a. Nama fungsi komponen boleh huruf kecil asalkan file `.tsx`.
- b. Komponen adalah fungsi berhuruf besar yang mengembalikan JSX; satu definisi bisa dipakai berkali-kali lewat props berbeda.
- c. Komponen sama dengan class CSS.
- d. Setiap komponen wajib punya `useState`.

### A2. Prediksi JSX

Apa yang salah, dan perbaikannya?

```jsx
function Judul() {
  return (
    <h1 class="judul">Tracker</h1>
    <p>Belajar React</p>
  );
}
```

### A3. Esai — props read-only

Anak ingin mengubah `props.judul`. Mengapa dilarang? Pola apa yang dipakai
agar perubahan terjadi di induk (*events up*)?

### A4. Prediksi `useState`

```jsx
function Counter() {
  let jumlah = 0;
  return <button onClick={() => jumlah++}>{jumlah}</button>;
}
```

Apa yang tampil setelah 10 kali klik? Mengapa harus `useState`?

### A5. Pilihan ganda — event

Mana yang memanggil `hapus` **saat diklik** dengan argumen `id`, bukan saat
render?

- a. `<button onClick={hapus(id)}>`
- b. `<button onClick={hapus}>` saja, dan `id` ajaib terkirim
- c. `<button onClick={() => hapus(id)}>`
- d. `<button click={hapus(id)}>`

### A6. Prediksi list

```jsx
{items.map((item, index) => (
  <input key={index} defaultValue={item.nama} />
))}
```

Item index 0 dihapus. Apa risiko memakai `key={index}` pada input?
`key` yang benar dari mana?

### A7. Esai — controlled input

Tuliskan dua atribut yang membuat `<input>` terkontrol. Apa keuntungannya
untuk validasi dibanding input liar?

### A8. Prediksi filter

```jsx
const [q, setQ] = useState("");
const tampil = mataKuliah.filter((m) =>
  m.nama.toLowerCase().includes(q.toLowerCase()),
);
```

Apakah `tampil` perlu `useState` sendiri? Istilah untuk nilai yang dihitung
dari state lain?

### A9. Pilihan ganda — fragment

`<>...</>` dipakai untuk…

- a. Mengganti `useState`.
- b. Memberi satu induk pada JSX tanpa menambah node DOM.
- c. Menandai Client Component.
- d. Mengimpor CSS.

### A10. Esai — data down, events up

Dengan diagram atau langkah bernomor, jelaskan alur SearchBox + DaftarItem
yang berbagi `query` di `App`.

---

## B. Soal praktik kecil (3)

### B1. Kartu props

Komponen `CourseCard({ judul, sks })` menampilkan artikel dengan kedua
data. Parent merender dua kartu berbeda. Tanpa `useState`.

### B2. Counter state

`StudyCounter` dengan `useState(0)`, tombol Tambah dan Reset. Tampilkan
angka. Jangan `jumlah++`.

### B3. Filter list

Array `const data = [{ id: 1, nama: "HTML" }, { id: 2, nama: "CSS" }]`.
Input terkendali + daftar `ul` hasil `filter` + `map` dengan `key={id}`.
Empty state jika tidak ada yang cocok.
