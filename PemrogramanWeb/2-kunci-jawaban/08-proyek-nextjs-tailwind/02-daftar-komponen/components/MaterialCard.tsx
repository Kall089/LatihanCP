import Link from "next/link";
import type { Material } from "../data/materials";

export default function MaterialCard({ material }: { material: Material }) {
  return (
    <article className="rounded-2xl border border-slate-200 bg-white p-5 shadow-sm">
      <p className="text-sm font-semibold uppercase text-blue-600">{material.level}</p>
      <h2 className="mt-2 text-xl font-bold">{material.title}</h2>
      <p className="mt-2 text-slate-600">{material.description}</p>
      <Link className="mt-4 inline-block font-semibold text-blue-700" href={`/materi/${material.slug}`}>Pelajari</Link>
    </article>
  );
}
