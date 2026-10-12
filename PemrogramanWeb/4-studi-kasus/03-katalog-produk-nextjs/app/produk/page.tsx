import KatalogClient from "@/components/KatalogClient";
import { daftarProduk } from "@/lib/data";

export default function ProdukPage() {
  // TODO: halaman ini SERVER component — kirim daftarProduk ke island client
  return (
    <main className="mx-auto max-w-6xl px-4 py-10">
      <h1 className="text-3xl font-bold">Menu</h1>
      <KatalogClient items={daftarProduk} />
    </main>
  );
}
