import Link from "next/link";

export default function Navbar() {
  return (
    <header className="border-b border-stone-200 bg-white">
      <nav
        className="mx-auto flex max-w-6xl items-center justify-between gap-4 px-4 py-4"
        aria-label="Navigasi utama"
      >
        <Link href="/" className="font-bold text-stone-900">
          Kopi Senja
        </Link>
        <Link href="/produk" className="font-medium text-orange-700 hover:underline">
          Menu
        </Link>
      </nav>
    </header>
  );
}
