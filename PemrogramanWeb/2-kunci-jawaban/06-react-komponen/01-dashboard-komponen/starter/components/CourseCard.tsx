type CourseCardProps = {
  title: string;
  description: string;
  completed: boolean;
};

export default function CourseCard(props: CourseCardProps) {
  const { title, description, completed } = props;
  return <article className="rounded-xl border border-slate-200 p-5"><span className={completed ? "text-emerald-700" : "text-amber-700"}>{completed ? "Selesai" : "Belum selesai"}</span><h2 className="mt-2 text-xl font-bold">{title}</h2><p className="mt-1 text-slate-600">{description}</p></article>;
}
