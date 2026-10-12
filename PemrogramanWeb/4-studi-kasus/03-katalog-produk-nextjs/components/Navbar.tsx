import Link from "next/link";

export default function Navbar() {
  return (
    <header className="border-b border-stone-200 bg-white">
      <nav
        className="mx-auto flex max-w-6xl items-center justify-between gap-4 px-4 py-4"
        aria-label="Navigasi utama"
      >
        {/* TODO: Link merek ke /, Link Menu ke /produk */}
        <span className="font-semibold">TODO Navbar</span>
      </nav>
    </header>
  );
}
