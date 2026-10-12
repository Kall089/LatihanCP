import { notFound } from "next/navigation";
import Link from "next/link";
import { daftarProduk, getProdukById } from "@/lib/data";
import { formatRupiah } from "@/lib/format";

type PageProps = { params: Promise<{ id: string }> };

export function generateStaticParams() {
  // TODO: return daftarProduk.map((p) => ({ id: String(p.id) }))
  return [];
}

export default async function DetailProdukPage({ params }: PageProps) {
  // TODO 1: await params, Number(id), getProdukById
  // TODO 2: if (!produk) notFound()
  // TODO 3: tampilkan nama, kategori, harga, deskripsi, Link kembali
  return <main className="mx-auto max-w-3xl px-4 py-10">{/* TODO */}</main>;
}
