"use client";

import { useState } from "react";

type LikeButtonProps = { initialLikes: number };

export default function LikeButton({ initialLikes }: LikeButtonProps) {
  const [likes, setLikes] = useState(initialLikes);
  return <button type="button" onClick={() => setLikes((value) => value + 1)}>Suka ({likes})</button>;
}
