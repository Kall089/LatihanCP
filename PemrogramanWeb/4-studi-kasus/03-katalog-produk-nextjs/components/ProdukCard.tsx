import Link from "next/link";
import type { Produk } from "@/lib/data";
import { formatRupiah } from "@/lib/format";

export default function ProdukCard({ produk }: { produk: Produk }) {
  // TODO: article kartu Tailwind — kategori, nama, cuplikan deskripsi, harga, Link /produk/[id]
  // JANGAN import daftarProduk di file ini.
  return (
    <article className="rounded-2xl border border-stone-200 bg-white p-5 shadow-sm">
      <p className="text-sm text-stone-400">TODO Kartu {produk.nama}</p>
    </article>
  );
}
