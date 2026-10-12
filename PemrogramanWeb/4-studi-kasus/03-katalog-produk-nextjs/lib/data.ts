export type Produk = {
  id: number;
  nama: string;
  kategori: "kopi" | "nonkopi" | "snack";
  harga: number;
  deskripsi: string;
};

// TODO: isi minimal 6 produk nyata (nama + deskripsi berbahasa Indonesia)
export const daftarProduk: Produk[] = [];

export function getProdukById(id: number) {
  return daftarProduk.find((p) => p.id === id);
}

export function getProdukByKategori(kategori: Produk["kategori"] | "semua") {
  if (kategori === "semua") return daftarProduk;
  return daftarProduk.filter((p) => p.kategori === kategori);
}
