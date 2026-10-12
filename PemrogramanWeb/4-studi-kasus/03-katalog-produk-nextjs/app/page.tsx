import Link from "next/link";
import ProdukCard from "@/components/ProdukCard";
import { daftarProduk } from "@/lib/data";

export default function BerandaPage() {
  // TODO 1: ambil 3 produk pertama sebagai unggulan
  // TODO 2: hero (h1 + paragraf + Link ke /produk)
  // TODO 3: grid ProdukCard
  return (
    <main className="mx-auto max-w-6xl px-4 py-10">
      <p className="text-slate-500">TODO: hero dan daftar unggulan dari daftarProduk.</p>
    </main>
  );
}
