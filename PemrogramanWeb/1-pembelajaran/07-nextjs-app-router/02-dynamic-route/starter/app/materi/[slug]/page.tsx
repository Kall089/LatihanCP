import { notFound } from "next/navigation";

const materials = [
  { slug: "html", title: "HTML", description: "Struktur halaman web." },
  { slug: "css", title: "CSS", description: "Tampilan halaman web." },
];

type PageProps = { params: Promise<{ slug: string }> };

export default async function MaterialPage({ params }: PageProps) {
  // TODO 1: Await params dan cari material berdasarkan slug.
  // TODO 2: Panggil notFound jika material tidak ditemukan.
  return <main>{/* TODO 3: Tampilkan title dan description. */}</main>;
}

// TODO 4: Export generateStaticParams berdasarkan materials.
