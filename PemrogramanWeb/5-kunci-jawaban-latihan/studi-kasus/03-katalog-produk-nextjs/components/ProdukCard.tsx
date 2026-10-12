import Link from "next/link";
import type { Produk } from "@/lib/data";
import { formatRupiah } from "@/lib/format";

export default function ProdukCard({ produk }: { produk: Produk }) {
  return (
    <article className="flex h-full flex-col rounded-2xl border border-stone-200 bg-white p-5 shadow-sm">
      <p className="text-sm font-semibold uppercase text-orange-700">{produk.kategori}</p>
      <h2 className="mt-2 text-xl font-bold">{produk.nama}</h2>
      <p className="mt-2 flex-1 text-stone-600">{produk.deskripsi}</p>
      <p className="mt-4 font-semibold">{formatRupiah(produk.harga)}</p>
      <Link
        href={`/produk/${produk.id}`}
        className="mt-4 inline-block font-semibold text-orange-700 hover:underline focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-orange-400"
      >
        Lihat detail
      </Link>
    </article>
  );
}
