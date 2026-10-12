"use client";

import { useState, type FormEvent } from "react";

export default function StudyForm() {
  const [topic, setTopic] = useState("");
  const [submittedTopic, setSubmittedTopic] = useState("");
  function handleSubmit(event: FormEvent<HTMLFormElement>) {
    event.preventDefault();
    const cleanTopic = topic.trim();
    if (!cleanTopic) return;
    setSubmittedTopic(cleanTopic);
    setTopic("");
  }

  return (
    <section>
      <form onSubmit={handleSubmit}>
        <label htmlFor="topic">Materi berikutnya</label>
        <input id="topic" value={topic} onChange={(event) => setTopic(event.target.value)} />
        <button type="submit">Simpan</button>
      </form>
      {submittedTopic && <p>Materi tersimpan: {submittedTopic}</p>}
    </section>
  );
}
