export type Produk = {
  id: number;
  nama: string;
  kategori: "kopi" | "nonkopi" | "snack";
  harga: number;
  deskripsi: string;
};

export const daftarProduk: Produk[] = [
  {
    id: 1,
    nama: "Kopi Susu Senja",
    kategori: "kopi",
    harga: 18000,
    deskripsi: "Espresso, susu fresh, dan gula aren cair. Andalan warung.",
  },
  {
    id: 2,
    nama: "Americano",
    kategori: "kopi",
    harga: 14000,
    deskripsi: "Espresso disiram air panas. Pahit bersih untuk begadang.",
  },
  {
    id: 3,
    nama: "Teh Tarik",
    kategori: "nonkopi",
    harga: 12000,
    deskripsi: "Teh susu ditarik sampai berbuih. Favorit yang tidak minum kopi.",
  },
  {
    id: 4,
    nama: "Cokelat Panas",
    kategori: "nonkopi",
    harga: 15000,
    deskripsi: "Cokelat batang dilelehkan, bukan saset. Hangat dan kental.",
  },
  {
    id: 5,
    nama: "Roti Bakar Cokelat Keju",
    kategori: "snack",
    harga: 15000,
    deskripsi: "Roti tawar dipanggang, selai cokelat dan keju parut.",
  },
  {
    id: 6,
    nama: "Pisang Goreng Madu",
    kategori: "snack",
    harga: 10000,
    deskripsi: "Pisang kepok, tepung tipis, madu di atasnya.",
  },
];

export function getProdukById(id: number) {
  return daftarProduk.find((p) => p.id === id);
}

export function getProdukByKategori(kategori: Produk["kategori"] | "semua") {
  if (kategori === "semua") return daftarProduk;
  return daftarProduk.filter((p) => p.kategori === kategori);
}
