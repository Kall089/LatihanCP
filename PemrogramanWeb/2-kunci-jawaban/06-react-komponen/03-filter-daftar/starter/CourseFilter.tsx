"use client";

import { useState } from "react";

const courses = [
  { id: 1, title: "HTML", completed: true },
  { id: 2, title: "CSS", completed: true },
  { id: 3, title: "React", completed: false },
];

type Filter = "all" | "done" | "todo";

export default function CourseFilter() {
  const [filter, setFilter] = useState<Filter>("all");
  const visibleCourses = courses.filter((course) => filter === "all" || (filter === "done" ? course.completed : !course.completed));
  return <section><div><button onClick={() => setFilter("all")}>Semua</button><button onClick={() => setFilter("done")}>Selesai</button><button onClick={() => setFilter("todo")}>Belum selesai</button></div><ul>{visibleCourses.map((course) => <li key={course.id}>{course.title}</li>)}</ul></section>;
}
