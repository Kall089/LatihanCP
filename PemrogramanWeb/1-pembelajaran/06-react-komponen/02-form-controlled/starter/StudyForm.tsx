"use client";

import { useState, type FormEvent } from "react";

export default function StudyForm() {
  // TODO 1: Buat state topic dan submittedTopic.
  function handleSubmit(event: FormEvent<HTMLFormElement>) {
    // TODO 2: Cegah reload, validasi topic, simpan hasil, dan kosongkan input.
  }

  return (
    <section>
      <form onSubmit={handleSubmit}>
        <label htmlFor="topic">Materi berikutnya</label>
        {/* TODO 3: Jadikan input controlled. */}
        <input id="topic" />
        <button type="submit">Simpan</button>
      </form>
      {/* TODO 4: Tampilkan submittedTopic secara kondisional. */}
    </section>
  );
}
