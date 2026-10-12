import { notFound } from "next/navigation";

const materials = [
  { slug: "html", title: "HTML", description: "Struktur halaman web." },
  { slug: "css", title: "CSS", description: "Tampilan halaman web." },
];

type PageProps = { params: Promise<{ slug: string }> };

export default async function MaterialPage({ params }: PageProps) {
  const { slug } = await params;
  const material = materials.find((item) => item.slug === slug);
  if (!material) notFound();
  return <main><h1>{material.title}</h1><p>{material.description}</p></main>;
}

export function generateStaticParams() {
  return materials.map(({ slug }) => ({ slug }));
}
