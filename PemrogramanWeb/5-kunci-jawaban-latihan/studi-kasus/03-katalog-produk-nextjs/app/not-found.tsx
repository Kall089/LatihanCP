import Link from "next/link";

export default function TidakDitemukan() {
  return (
    <main className="mx-auto max-w-3xl px-4 py-20 text-center">
      <h1 className="text-3xl font-bold">Halaman tidak ditemukan</h1>
      <p className="mt-3 text-stone-600">
        URL salah atau produk tidak ada di katalog. Coba kembali ke beranda atau daftar menu.
      </p>
      <p className="mt-8 flex justify-center gap-4">
        <Link href="/" className="font-semibold text-orange-700 hover:underline">Beranda</Link>
        <Link href="/produk" className="font-semibold text-orange-700 hover:underline">Menu</Link>
      </p>
    </main>
  );
}
