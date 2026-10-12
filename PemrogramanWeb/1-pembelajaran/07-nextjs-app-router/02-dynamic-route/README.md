# 02 — Dynamic Route

Salin starter ke folder `app/materi/[slug]/page.tsx`. Cari data dari `params.slug`,
panggil `notFound()` jika tidak ada, dan buat `generateStaticParams()` dari data.
Pada Next.js modern, `params` bertipe Promise sehingga perlu di-`await`.
