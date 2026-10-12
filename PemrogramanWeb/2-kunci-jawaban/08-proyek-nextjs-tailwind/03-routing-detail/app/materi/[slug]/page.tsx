import Link from "next/link";
import { notFound } from "next/navigation";

const materials = [
  { slug: "html", title: "HTML", level: "Pemula", description: "Pelajari struktur halaman web." },
  { slug: "css", title: "CSS", level: "Pemula", description: "Pelajari cara menata halaman web." },
];

export default async function MaterialPage({ params }: { params: Promise<{ slug: string }> }) {
  const { slug } = await params;
  const material = materials.find((item) => item.slug === slug);
  if (!material) notFound();
  return <main className="mx-auto max-w-3xl p-6"><p>{material.level}</p><h1 className="text-3xl font-bold">{material.title}</h1><p className="mt-3">{material.description}</p><Link className="mt-6 inline-block text-blue-700" href="/">Kembali</Link></main>;
}
