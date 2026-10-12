# Contoh Penyelesaian Tahap Akhir

Pisahkan data awal (Server Component) dari filter interaktif (Client Component).
Nilai progres merupakan derived state:

```tsx
const completedCount = materials.filter((item) => item.completed).length;
const visibleMaterials = materials.filter((item) =>
  filter === "all" ? true : filter === "done" ? item.completed : !item.completed,
);
```

Gunakan satu state array sebagai sumber kebenaran. Perubahan status dibuat tanpa
memutasi item lama:

```tsx
setMaterials((current) => current.map((item) =>
  item.slug === slug ? { ...item, completed: !item.completed } : item,
));
```

Urutan komponen yang disarankan: `app/page.tsx` mengirim data awal ke
`LearningTracker`, kemudian `LearningTracker` merender `Progress`, `FilterBar`,
dan kumpulan `MaterialCard`. Detail materi tetap berada pada route `[slug]`.
