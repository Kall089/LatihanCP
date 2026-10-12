export type Material = { slug: string; title: string; description: string; level: "pemula" | "menengah" | "lanjut"; completed: boolean };
export const materials: Material[] = [
  { slug: "html", title: "HTML", description: "Struktur halaman.", level: "pemula", completed: true },
  { slug: "css", title: "CSS", description: "Tampilan halaman.", level: "pemula", completed: false },
  { slug: "react", title: "React", description: "UI berbasis komponen.", level: "menengah", completed: false },
];
