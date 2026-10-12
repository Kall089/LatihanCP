"use client";

import { useState } from "react";
import type { Produk } from "@/lib/data";
import ProdukCard from "./ProdukCard";

type KategoriFilter = "semua" | Produk["kategori"];

const opsi: { nilai: KategoriFilter; label: string }[] = [
  { nilai: "semua", label: "Semua" },
  { nilai: "kopi", label: "Kopi" },
  { nilai: "nonkopi", label: "Nonkopi" },
  { nilai: "snack", label: "Snack" },
];

export default function KatalogClient({ items }: { items: Produk[] }) {
  const [kategori, setKategori] = useState<KategoriFilter>("semua");
  const tampil =
    kategori === "semua" ? items : items.filter((p) => p.kategori === kategori);

  return (
    <div className="mt-8">
      <div className="flex flex-wrap gap-2">
        {opsi.map((o) => (
          <button
            key={o.nilai}
            type="button"
            onClick={() => setKategori(o.nilai)}
            className={
              kategori === o.nilai
                ? "rounded-full bg-stone-900 px-4 py-2 text-sm text-white"
                : "rounded-full bg-white px-4 py-2 text-sm ring-1 ring-stone-200"
            }
          >
            {o.label}
          </button>
        ))}
      </div>

      {tampil.length === 0 ? (
        <p className="mt-8 rounded-2xl border border-dashed border-stone-300 p-8 text-center text-stone-500">
          Tidak ada produk di kategori ini.
        </p>
      ) : (
        <ul className="mt-8 grid grid-cols-1 gap-6 sm:grid-cols-2 lg:grid-cols-3">
          {tampil.map((produk) => (
            <li key={produk.id}>
              <ProdukCard produk={produk} />
            </li>
          ))}
        </ul>
      )}
    </div>
  );
}
