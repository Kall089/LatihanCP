export type MaterialLevel = "pemula" | "menengah" | "lanjut";

export type Material = {
  slug: string;
  title: string;
  description: string;
  level: MaterialLevel;
  completed: boolean;
};

export const materials: Material[] = [
  { slug: "html-semantik", title: "HTML Semantik", description: "Struktur halaman yang bermakna.", level: "pemula", completed: true },
  { slug: "css-dasar", title: "CSS Dasar", description: "Warna, tipografi, dan box model.", level: "pemula", completed: true },
  { slug: "flexbox", title: "Flexbox", description: "Layout dalam satu dimensi.", level: "pemula", completed: false },
  { slug: "css-grid", title: "CSS Grid", description: "Layout dalam dua dimensi.", level: "menengah", completed: false },
  { slug: "react-state", title: "React State", description: "Data interaktif di dalam komponen.", level: "menengah", completed: false },
  { slug: "nextjs-routing", title: "Next.js Routing", description: "Routing berbasis struktur folder.", level: "lanjut", completed: false },
];
