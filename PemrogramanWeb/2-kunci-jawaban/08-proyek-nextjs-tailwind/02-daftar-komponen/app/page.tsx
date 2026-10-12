import MaterialCard from "../components/MaterialCard";
import { materials } from "../data/materials";

export default function Page() {
  return <main className="mx-auto max-w-6xl p-6"><h1 className="text-3xl font-bold">Learning Tracker</h1><section className="mt-8 grid gap-5 md:grid-cols-2 lg:grid-cols-3">{materials.map((material) => <MaterialCard key={material.slug} material={material} />)}</section></main>;
}
