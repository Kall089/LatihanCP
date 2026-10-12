type Pizza = {
  name: string;
  ingredients: string;
  price: number;
  photoName: string;
  soldOut: boolean;
};

type PizzaProps = {
  pizza: Pizza;
};

type OrderProps = {
  openHour: number;
  closeHour: number;
};

const pizzaData: Pizza[] = [
  {
    name: "Focaccia",
    ingredients: "Bread with Italian olive oil and rosemary",
    price: 6,
    photoName: "/pizzas/focaccia.jpg",
    soldOut: false,
  },
  {
    name: "Pizza Margherita",
    ingredients: "Tomato and mozzarella",
    price: 10,
    photoName: "/pizzas/margherita.jpg",
    soldOut: false,
  },
  {
    name: "Pizza Spinaci",
    ingredients: "Tomato, mozzarella, spinach, and ricotta cheese",
    price: 12,
    photoName: "/pizzas/spinaci.jpg",
    soldOut: false,
  },
  {
    name: "Pizza Funghi",
    ingredients: "Tomato, mozzarella, mushrooms, and onion",
    price: 12,
    photoName: "/pizzas/funghi.jpg",
    soldOut: false,
  },
  {
    name: "Pizza Salamino",
    ingredients: "Tomato, mozzarella, and pepperoni",
    price: 15,
    photoName: "/pizzas/salamino.jpg",
    soldOut: true,
  },
  {
    name: "Pizza Prosciutto",
    ingredients: "Tomato, mozzarella, ham, arugula, and burrata cheese",
    price: 18,
    photoName: "/pizzas/prosciutto.jpg",
    soldOut: false,
  },
];

export default function App() {
  return (
    <div className="mx-auto flex min-h-screen max-w-5xl flex-col items-center gap-12 px-6 py-12 sm:px-10">
      <Header />
      <Menu />
      <Footer />
    </div>
  );
}

function Header() {
  return (
    <header className="w-full">
      <h1 className="text-center text-4xl font-light uppercase tracking-[0.18em] text-amber-400 sm:text-5xl">
        Fast React Pizza Co.
      </h1>
    </header>
  );
}

function Menu() {
  return (
    <main className="flex w-full flex-col items-center gap-10">
      <h2 className="border-y-2 border-stone-800 py-2 text-2xl font-medium uppercase tracking-[0.16em]">
        Our menu
      </h2>

      {pizzaData.length > 0 ? (
        <>
          <p className="max-w-2xl text-center leading-7 text-stone-700">
            Authentic Italian cuisine. Six creative dishes, all from our stone
            oven, all organic, and all delicious.
          </p>
          <ul className="grid w-full list-none gap-10 md:grid-cols-2">
            {pizzaData.map((pizza) => (
              <PizzaCard pizza={pizza} key={pizza.name} />
            ))}
          </ul>
        </>
      ) : (
        <p>We&apos;re still working on our menu. Please come back later.</p>
      )}
    </main>
  );
}

function PizzaCard({ pizza }: PizzaProps) {
  return (
    <li
      className={`flex gap-6 ${pizza.soldOut ? "text-stone-400" : "text-stone-800"}`}
    >
      <img
        className={`size-28 shrink-0 object-cover sm:size-32 ${pizza.soldOut ? "grayscale opacity-70" : ""}`}
        src={pizza.photoName}
        alt={pizza.name}
      />
      <div className="flex flex-col gap-2 py-1">
        <h3 className="text-xl font-medium">{pizza.name}</h3>
        <p className="mb-auto text-sm italic leading-6">{pizza.ingredients}</p>
        <span className="font-medium">
          {pizza.soldOut ? "SOLD OUT" : `$${pizza.price}`}
        </span>
      </div>
    </li>
  );
}

function Footer() {
  const hour = new Date().getHours();
  const openHour = 12;
  const closeHour = 22;
  const isOpen = hour >= openHour && hour < closeHour;

  return (
    <footer className="text-center text-sm">
      {isOpen ? (
        <Order closeHour={closeHour} openHour={openHour} />
      ) : (
        <p>
          We&apos;re happy to welcome you between {openHour}:00 and {closeHour}:00.
        </p>
      )}
    </footer>
  );
}

function Order({ closeHour, openHour }: OrderProps) {
  return (
    <div className="flex flex-col items-center gap-6">
      <p>
        We&apos;re open from {openHour}:00 to {closeHour}:00. Come visit us or
        order online.
      </p>
      <button
        className="bg-amber-400 px-8 py-3 font-medium transition hover:bg-amber-500"
        type="button"
      >
        Order
      </button>
    </div>
  );
}
