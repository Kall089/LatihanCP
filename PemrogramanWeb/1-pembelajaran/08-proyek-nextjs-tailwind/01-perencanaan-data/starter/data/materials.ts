export type MaterialLevel = "pemula" | "menengah" | "lanjut";

export type Material = {
  slug: string;
  title: string;
  description: string;
  level: MaterialLevel;
  completed: boolean;
};

// TODO: Isi minimal 6 materi dengan slug unik.
export const materials: Material[] = [];
