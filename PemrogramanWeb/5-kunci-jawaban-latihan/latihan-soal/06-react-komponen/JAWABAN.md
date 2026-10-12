# Jawaban 06 — React Komponen

---

## A. Konsep

### A1 — b

Huruf besar membedakan komponen dari tag HTML. State tidak wajib (kartu
statis hanya props).

### A2

Dua masalah: `class` harus `className`; dua elemen tanpa induk. Perbaikan:
fragment `<>...</>` + `className`.

### A3

Props adalah argumen; mengubahnya merusak satu arah data. Induk punya
state; anak memanggil `props.onChange(nilaiBaru)` — events up.

### A4

Tetap **0**. Mutasi `jumlah++` tidak meminta React render ulang; setiap
klik tetap closure nilai 0 dari render pertama. `useState` + `setJumlah`.

### A5 — c

`onClick={hapus(id)}` memanggil saat render. Arrow `() => hapus(id)`
menunda sampai klik.

### A6

Setelah hapus index 0, input yang tersisa bisa **membawa nilai ketikan
lama** karena React mendaur ulang instance menurut key. Pakai `key={item.id}`.

### A7

`value={state}` dan `onChange={(e) => setState(e.target.value)}`.
Keuntungan: satu sumber kebenaran, validasi live, disable tombol saat
kosong.

### A8

Tidak perlu `useState` untuk `tampil`. Itu **derived state** — dihitung
setiap render dari `q` + data.

### A9 — b

Fragment = induk JSX tanpa node extra di DOM.

### A10

1. State `query` di `App`.
2. `SearchBox` terima `value` + `onChange`.
3. Ketikan → callback → `setQuery`.
4. `DaftarItem` terima `query`, filter, render. Data down, events up.

---

## B. Praktik

### B1

```tsx
function CourseCard({ judul, sks }: { judul: string; sks: number }) {
  return (
    <article>
      <h2>{judul}</h2>
      <p>{sks} SKS</p>
    </article>
  );
}

function App() {
  return (
    <>
      <CourseCard judul="Pemrograman Web" sks={3} />
      <CourseCard judul="PBO" sks={3} />
    </>
  );
}
```

### B2

```tsx
function StudyCounter() {
  const [jumlah, setJumlah] = useState(0);
  return (
    <div>
      <p>{jumlah}</p>
      <button type="button" onClick={() => setJumlah(jumlah + 1)}>Tambah</button>
      <button type="button" onClick={() => setJumlah(0)}>Reset</button>
    </div>
  );
}
```

### B3

```tsx
function Filter() {
  const data = [
    { id: 1, nama: "HTML" },
    { id: 2, nama: "CSS" },
  ];
  const [q, setQ] = useState("");
  const tampil = data.filter((d) =>
    d.nama.toLowerCase().includes(q.toLowerCase()),
  );
  return (
    <div>
      <input value={q} onChange={(e) => setQ(e.target.value)} />
      {tampil.length === 0 ? (
        <p>Tidak ada hasil.</p>
      ) : (
        <ul>
          {tampil.map((d) => (
            <li key={d.id}>{d.nama}</li>
          ))}
        </ul>
      )}
    </div>
  );
}
```
