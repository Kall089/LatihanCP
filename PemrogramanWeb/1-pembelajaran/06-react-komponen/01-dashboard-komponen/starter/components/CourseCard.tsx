type CourseCardProps = {
  title: string;
  description: string;
  completed: boolean;
};

export default function CourseCard(props: CourseCardProps) {
  // TODO 1: Destructure title, description, dan completed dari props.
  // TODO 2: Tampilkan badge "Selesai" atau "Belum selesai" berdasarkan completed.
  // TODO 3: Gunakan class Tailwind agar kartu memiliki border, padding, dan rounded corner.

  return <article>{/* Tulis isi kartu di sini. */}</article>;
}
