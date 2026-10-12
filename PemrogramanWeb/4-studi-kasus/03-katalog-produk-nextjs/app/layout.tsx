import type { Metadata } from "next";
import "./globals.css";
import Navbar from "@/components/Navbar";

// TODO: isi title dan description toko
export const metadata: Metadata = {
  title: "",
  description: "",
};

export default function RootLayout({
  children,
}: Readonly<{ children: React.ReactNode }>) {
  return (
    <html lang="id">
      <body className="min-h-screen bg-stone-50 text-stone-900">
        {/* TODO: Navbar global, lalu <main>{children}</main>, footer sederhana */}
        <Navbar />
        {children}
      </body>
    </html>
  );
}
