"use client";

import { useState } from "react";
import type { Produk } from "@/lib/data";
import ProdukCard from "./ProdukCard";

type KategoriFilter = "semua" | Produk["kategori"];

export default function KatalogClient({ items }: { items: Produk[] }) {
  const [kategori, setKategori] = useState<KategoriFilter>("semua");

  // TODO 1: derived tampil = filter items
  // TODO 2: tombol Semua / kopi / nonkopi / snack
  // TODO 3: jika kosong, pesan empty state; jika ada, grid ProdukCard

  return (
    <div className="mt-8">
      <p className="text-stone-500">TODO filter client island (kategori = {kategori}).</p>
    </div>
  );
}
