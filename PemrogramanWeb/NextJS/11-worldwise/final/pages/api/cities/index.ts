import type { NextApiRequest, NextApiResponse } from "next";
import { addCity, getCities } from "../../../src/server/citiesStore";

export default function handler(
  request: NextApiRequest,
  response: NextApiResponse,
) {
  if (request.method === "GET") {
    return response.status(200).json(getCities());
  }

  if (request.method === "POST") {
    return response.status(201).json(addCity(request.body));
  }

  response.setHeader("Allow", ["GET", "POST"]);
  return response.status(405).json({ message: "Method not allowed" });
}
