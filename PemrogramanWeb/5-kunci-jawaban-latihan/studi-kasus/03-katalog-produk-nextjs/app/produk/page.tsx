import KatalogClient from "@/components/KatalogClient";
import { daftarProduk } from "@/lib/data";

export default function ProdukPage() {
  return (
    <main className="mx-auto max-w-6xl px-4 py-10">
      <h1 className="text-3xl font-bold">Menu lengkap</h1>
      <p className="mt-2 text-stone-600">Saring kategori di bawah. Data tetap dari server.</p>
      <KatalogClient items={daftarProduk} />
    </main>
  );
}
