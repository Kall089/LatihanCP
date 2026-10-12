"use client";

import { useState } from "react";

export default function StudyCounter() {
  const [sessions, setSessions] = useState(0);
  return <section className="mt-8"><h2 className="text-xl font-bold">Sesi belajar: {sessions}</h2><div className="mt-3 flex gap-3"><button onClick={() => setSessions((value) => value + 1)}>Tambah</button><button onClick={() => setSessions(0)}>Reset</button></div></section>;
}
