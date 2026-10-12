import Link from "next/link";
import ProdukCard from "@/components/ProdukCard";
import { daftarProduk } from "@/lib/data";

export default function BerandaPage() {
  const unggulan = daftarProduk.slice(0, 3);

  return (
    <main className="mx-auto max-w-6xl px-4 py-10">
      <section className="rounded-3xl bg-stone-900 px-6 py-16 text-stone-50">
        <p className="text-sm uppercase tracking-wide text-orange-300">UMKM kopi kampus</p>
        <h1 className="mt-2 max-w-2xl text-4xl font-bold">Menu Senja, siap diantar ke laboratorium.</h1>
        <p className="mt-4 max-w-xl text-stone-300">
          Enam item contoh di <code className="text-orange-200">lib/data.ts</code> — satu sumber
          untuk beranda, daftar, dan detail.
        </p>
        <Link
          href="/produk"
          className="mt-8 inline-block rounded-lg bg-orange-500 px-5 py-2 font-semibold text-white hover:bg-orange-600 focus-visible:outline-none focus-visible:ring-2 focus-visible:ring-orange-300"
        >
          Lihat semua menu
        </Link>
      </section>

      <section className="mt-12" aria-labelledby="unggulan">
        <h2 id="unggulan" className="text-2xl font-bold">Unggulan minggu ini</h2>
        <ul className="mt-6 grid grid-cols-1 gap-6 sm:grid-cols-2 lg:grid-cols-3">
          {unggulan.map((produk) => (
            <li key={produk.id}>
              <ProdukCard produk={produk} />
            </li>
          ))}
        </ul>
      </section>
    </main>
  );
}
