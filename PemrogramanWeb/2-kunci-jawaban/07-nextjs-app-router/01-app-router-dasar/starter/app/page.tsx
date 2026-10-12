export default function HomePage() {
  return (
    <main className="mx-auto max-w-5xl px-6 py-16">
      <h1 className="text-4xl font-bold">Belajar Web Bertahap</h1>
      <p className="mt-3 text-slate-600">Pilih materi dan latih konsepnya melalui proyek kecil.</p>
      <section className="mt-8 grid gap-4 sm:grid-cols-2 lg:grid-cols-3">
        {['HTML Semantik', 'Layout CSS', 'React'].map((title) => <article className="rounded-xl border border-slate-200 p-5" key={title}><h2 className="font-bold">{title}</h2></article>)}
      </section>
    </main>
  );
}
