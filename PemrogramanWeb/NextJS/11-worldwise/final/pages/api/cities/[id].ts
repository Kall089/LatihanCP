import type { NextApiRequest, NextApiResponse } from "next";
import { getCity, removeCity } from "../../../src/server/citiesStore";

export default function handler(
  request: NextApiRequest,
  response: NextApiResponse,
) {
  const id = Number(request.query.id);

  if (request.method === "GET") {
    const city = getCity(id);
    return city
      ? response.status(200).json(city)
      : response.status(404).json({ message: "City not found" });
  }

  if (request.method === "DELETE") {
    return removeCity(id)
      ? response.status(204).end()
      : response.status(404).json({ message: "City not found" });
  }

  response.setHeader("Allow", ["GET", "DELETE"]);
  return response.status(405).json({ message: "Method not allowed" });
}
