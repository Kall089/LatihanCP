import cityData from "../../data/cities.json";
import type { City } from "../contexts/CitiesContext";

let cities = cityData.cities as City[];

export function getCities() {
  return cities;
}

export function getCity(id: number) {
  return cities.find((city) => city.id === id);
}

export function addCity(city: Omit<City, "id">) {
  const newCity: City = { ...city, id: Date.now() };
  cities = [...cities, newCity];
  return newCity;
}

export function removeCity(id: number) {
  const cityExists = cities.some((city) => city.id === id);
  cities = cities.filter((city) => city.id !== id);
  return cityExists;
}
