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
  // TODO 1: Turunkan visibleCourses dari courses dan filter.
  return <section>{/* TODO 2: Buat 3 tombol dan render visibleCourses. */}</section>;
}
