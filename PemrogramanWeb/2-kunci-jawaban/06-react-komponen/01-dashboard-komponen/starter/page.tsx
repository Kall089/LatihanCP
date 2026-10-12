import CourseCard from "./components/CourseCard";
import StudyCounter from "./components/StudyCounter";

const courses = [
  { id: 1, title: "HTML", description: "Struktur halaman", completed: true },
  { id: 2, title: "CSS", description: "Tampilan halaman", completed: true },
  { id: 3, title: "React", description: "Component dan state", completed: false },
];

export default function Page() {
  return (
    <main className="mx-auto max-w-5xl p-6">
      <h1 className="text-3xl font-bold">Dashboard Belajar</h1>

      <section className="mt-6 grid gap-4 md:grid-cols-3">{courses.map((course) => <CourseCard key={course.id} title={course.title} description={course.description} completed={course.completed} />)}</section>
      <StudyCounter />
    </main>
  );
}
