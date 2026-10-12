export default function HomePage() {
  return (
    <main className="mx-auto flex min-h-screen max-w-3xl items-center px-6 py-16">
      <section className="w-full rounded-3xl border border-slate-800 bg-slate-900 p-8 shadow-2xl sm:p-12">
        <p className="mb-3 text-sm font-bold uppercase tracking-[0.25em] text-sky-400">
          Starter project
        </p>
        <h1 className="text-3xl font-bold tracking-tight sm:text-5xl">
          11-worldwise
        </h1>
        <p className="mt-5 max-w-2xl text-lg leading-8 text-slate-300">
          Template sudah siap dengan Next.js, TypeScript, dan Tailwind CSS.
          Mulai latihan dengan mengubah file app/page.tsx.
        </p>
        <div className="mt-8 rounded-2xl bg-slate-950 p-5 font-mono text-sm text-emerald-300">
          npm run dev
        </div>
      </section>
    </main>
  );
}
