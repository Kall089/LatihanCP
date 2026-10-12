import type { Metadata } from "next";
import "./globals.css";
import Navbar from "@/components/Navbar";

export const metadata: Metadata = {
  title: "Warung Kopi Senja",
  description: "Katalog menu kopi, nonkopi, dan snack UMKM fiktif.",
};

export default function RootLayout({
  children,
}: Readonly<{ children: React.ReactNode }>) {
  return (
    <html lang="id">
      <body className="min-h-screen bg-stone-50 text-stone-900">
        <Navbar />
        {children}
        <footer className="border-t border-stone-200 py-8 text-center text-sm text-stone-500">
          © 2026 Warung Kopi Senja · studi kasus 03
        </footer>
      </body>
    </html>
  );
}
