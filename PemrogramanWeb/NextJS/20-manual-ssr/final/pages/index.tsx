import { useState } from "react";

const pizzas = [
  { name: "Focaccia", price: 6 },
  { name: "Pizza Margherita", price: 10 },
  { name: "Pizza Spinaci", price: 12 },
  { name: "Pizza Funghi", price: 12 },
  { name: "Pizza Prosciutto", price: 15 },
];

function Counter() {
  const [count, setCount] = useState(0);
  return (
    <div>
      <button onClick={() => setCount((value) => value + 1)}>+1</button>
      <span>{count}</span>
    </div>
  );
}

export default function Home() {
  return (
    <div>
      <h1>🍕 Fast React Pizza Co.</h1>
      <p>This page has been rendered with Next.js on the server 🤯</p>
      <h2>Menu</h2>
      <ul>
        {pizzas.map((pizza) => (
          <li key={pizza.name}>
            <h4>{pizza.name} ($${pizza.price})</h4>
            <Counter />
          </li>
        ))}
      </ul>
    </div>
  );
}
