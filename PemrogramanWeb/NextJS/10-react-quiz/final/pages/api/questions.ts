import type { NextApiRequest, NextApiResponse } from "next";
import questions from "../../data/questions.json";

export default function handler(
  request: NextApiRequest,
  response: NextApiResponse,
) {
  if (request.method !== "GET") {
    response.setHeader("Allow", "GET");
    return response.status(405).json({ message: "Method not allowed" });
  }

  return response.status(200).json(questions);
}
