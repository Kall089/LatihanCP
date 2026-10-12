# 📋 PROMPT TEMPLATE — Web Harian (392 Hari)

Sesuai [`ROADMAP_WEB.md`](ROADMAP_WEB.md). Pola [`PROMPT_TEMPLATE_CP.md`](PROMPT_TEMPLATE_CP.md).

**Cara pakai:** ganti `[N]`, paste ke AI.

---

```
Buatkan materi Web Day [N] di ComProgLearning/Web/ sesuai
ComProgLearning/ROADMAP_WEB.md (392 hari).

Pilar: CSS lengkap (Day 8–23) lalu Tailwind produksi, TypeScript (bukan JS dulu),
Next.js, Laravel, Go, Rust (fokus). Ikuti daftar **Tujuan / Materi / Praktik /
Selesai jika** di ROADMAP_WEB untuk Day [N] — jangan kurangi topik CSS jika hari
itu hari CSS. Hari mudah sudah DIGABUNG — jangan pecah lagi jadi materi tipis.
Isi hari ini harus PADAT sesuai silabus hari itu.

STRUKTUR:
ComProgLearning/Web/Day-[N] ([Nama Topik])/
├── teori/Day_[N]_Teori_Lengkap.md
├── teori/generate_presentation.py  (pptx_lib CP, Modern Cobalt)
├── latihan/exercise_1–5 (TODO)
├── solusi/solution_1–5
├── tugas/tugas_01–10 (tanpa kunci)
├── template/
└── README.md

TEORI: Bahasa Indonesia, analogi, diagram, kode, jebakan, cheatsheet.
SLIDES: cover, agenda, section_divider, kartu, kode, closing — 14–18 slide.
LATIHAN: progresif. Tailwind/Next di browser atau npm. Laravel artisan. Go test. cargo test.
STANDAR:
- Day 8–23: CSS murni lengkap (cascade, selector, box, flex, grid, position, responsive)
- Mulai Day 24: UI produksi Tailwind; tetap boleh menautkan ke CSS yang sudah dipelajari
- TypeScript strict, hindari any
- Next: Server Component default
- Laravel: validasi FormRequest, jaga mass assignment
- Go: gofmt, error nilai, table-driven, -race jika concurrent
- Rust: Result/Option, no unwrap produksi, clippy
```

## Singkat

```
Lanjut Web Day [N] sesuai ROADMAP_WEB.md dan PROMPT_TEMPLATE_WEB.md.
Hari padat, jangan pecah topik mudah. Bahasa Indonesia.
```
