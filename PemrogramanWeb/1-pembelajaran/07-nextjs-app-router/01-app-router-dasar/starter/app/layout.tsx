import type { Metadata } from "next";
import Link from "next/link";
import "./globals.css";

// TODO 1: Isi title dan description yang sesuai.
export const metadata: Metadata = {
  title: "",
  description: "",
};

export default function RootLayout({ children }: Readonly<{ children: React.ReactNode }>) {
  return (
    <html lang="id">
      <body>
        <header className="border-b border-slate-200 px-6 py-4">
          <nav className="mx-auto flex max-w-5xl gap-6" aria-label="Navigasi utama">
            {/* TODO 2: Tambahkan Link menuju beranda dan halaman tentang. */}
          </nav>
        </header>
        {children}
      </body>
    </html>
  );
}
