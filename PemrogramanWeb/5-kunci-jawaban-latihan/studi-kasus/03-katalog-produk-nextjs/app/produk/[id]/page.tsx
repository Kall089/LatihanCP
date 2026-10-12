import Link from "next/link";
import { notFound } from "next/navigation";
import { daftarProduk, getProdukById } from "@/lib/data";
import { formatRupiah } from "@/lib/format";

type PageProps = { params: Promise<{ id: string }> };

export function generateStaticParams() {
  return daftarProduk.map((p) => ({ id: String(p.id) }));
}

export default async function DetailProdukPage({ params }: PageProps) {
  const { id } = await params;
  const produk = getProdukById(Number(id));
  if (!produk) notFound();

  return (
    <main className="mx-auto max-w-3xl px-4 py-10">
      <p className="text-sm font-semibold uppercase text-orange-700">{produk.kategori}</p>
      <h1 className="mt-2 text-4xl font-bold">{produk.nama}</h1>
      <p className="mt-4 text-2xl font-semibold text-stone-800">{formatRupiah(produk.harga)}</p>
      <p className="mt-6 text-lg leading-relaxed text-stone-600">{produk.deskripsi}</p>
      <Link href="/produk" className="mt-8 inline-block font-semibold text-orange-700 hover:underline">
        ← Kembali ke menu
      </Link>
    </main>
  );
}
