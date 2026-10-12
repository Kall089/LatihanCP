import type { Metadata } from "next";
import Link from "next/link";
import "./globals.css";

export const metadata: Metadata = {
  title: "WebLab",
  description: "Aplikasi pendamping belajar pemrograman web.",
};

export default function RootLayout({ children }: Readonly<{ children: React.ReactNode }>) {
  return (
    <html lang="id">
      <body>
        <header className="border-b border-slate-200 px-6 py-4">
          <nav className="mx-auto flex max-w-5xl gap-6" aria-label="Navigasi utama">
            <Link href="/">Beranda</Link>
            <Link href="/tentang">Tentang</Link>
          </nav>
        </header>
        {children}
      </body>
    </html>
  );
}
