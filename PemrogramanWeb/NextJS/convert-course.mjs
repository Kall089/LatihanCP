import { copyFile, mkdir, readFile, readdir, rename, rm, writeFile } from "node:fs/promises";
import path from "node:path";

const root = path.resolve(import.meta.dirname);
const nextVersion = "16.3.5";

const projects = [
  ["03-pizza-menu/final", "./App"],
  ["04-steps/final", "./App"],
  ["05-travel-list/final", "./components/App"],
  ["06-eat-n-split/final", "./App"],
  ["07-usepopcorn/final", "./App"],
  ["08-how-react-works/final", "./App"],
  ["08-how-react-works/starter", "./App"],
  ["09-classy-weather/final", "./App"],
  ["10-react-quiz/final", "./components/App", "quiz"],
  ["11-worldwise/final", "./App", "worldwise"],
  ["12-atomic-blog/final", "./App", "style"],
  ["12-atomic-blog/starter", "./App", "style"],
  ["13-workout-timer/final", "./App"],
  ["13-workout-timer/starter", "./App"],
  ["15-redux-intro/final", "./App", "redux"],
  ["16-fast-react-pizza/final-1-after-tailwind", "./App"],
  ["16-fast-react-pizza/final-2-final", "./App", "redux"],
  ["17-the-wild-oasis/final-1-after-setup", "./App", "no-css"],
  ["17-the-wild-oasis/final-2-after-supabase", "./App", "no-css"],
  ["17-the-wild-oasis/final-3-after-react-query", "./App", "no-css"],
  ["17-the-wild-oasis/final-4-after-advanced-patterns", "./App", "no-css"],
  ["17-the-wild-oasis/final-5-after-sort-filter-pagination", "./App", "no-css"],
  ["17-the-wild-oasis/final-6-final", "./App", "error-boundary"],
];

const page = `import dynamic from "next/dynamic";

const CourseApp = dynamic(() => import("../src/NextApp"), { ssr: false });

export default function Page() {
  return <CourseApp />;
}
`;

function nextAppSource(appImport, kind) {
  if (kind === "quiz") {
    return `import App from "${appImport}";
import { QuizProvider } from "./contexts/QuizContext";

export default function NextApp() {
  return (
    <QuizProvider>
      <App />
    </QuizProvider>
  );
}
`;
  }

  if (kind === "redux") {
    return `import { Provider } from "react-redux";
import App from "${appImport}";
import store from "./store";

export default function NextApp() {
  return (
    <Provider store={store}>
      <App />
    </Provider>
  );
}
`;
  }

  if (kind === "error-boundary") {
    return `import { ErrorBoundary } from "react-error-boundary";
import App from "${appImport}";
import ErrorFallback from "./ui/ErrorFallback";

export default function NextApp() {
  return (
    <ErrorBoundary
      FallbackComponent={ErrorFallback}
      onReset={() => window.location.replace("/")}
    >
      <App />
    </ErrorBoundary>
  );
}
`;
  }

  return `export { default } from "${appImport}";
`;
}

function appShell(kind) {
  const imports = [];
  imports.push(kind === "style" ? 'import "../src/style.css";' : 'import "../src/index.css";');
  if (kind === "worldwise") {
    imports.push('import "react-datepicker/dist/react-datepicker.css";');
  }

  return `${imports.join("\n")}${imports.length ? "\n\n" : ""}export default function MyApp({ Component, pageProps }) {
  return <Component {...pageProps} />;
}
`;
}

async function convertPackage(projectDir) {
  const packagePath = path.join(projectDir, "package.json");
  const packageJson = JSON.parse(await readFile(packagePath, "utf8"));

  packageJson.private = true;
  packageJson.scripts = {
    dev: "next dev",
    build: "next build --webpack",
    start: "next start",
    ...(packageJson.scripts?.server ? { server: packageJson.scripts.server } : {}),
  };
  packageJson.dependencies ??= {};
  packageJson.dependencies.next = nextVersion;
  delete packageJson.dependencies["react-scripts"];

  packageJson.devDependencies ??= {};
  packageJson.devDependencies.typescript = "^5.6.3";
  packageJson.devDependencies["@types/node"] = "^20.17.0";
  packageJson.devDependencies["@types/react"] = "^18.3.12";
  packageJson.devDependencies["@types/react-dom"] = "^18.3.1";
  packageJson.devDependencies.tailwindcss = "^3.4.17";
  packageJson.devDependencies.postcss = "^8.4.49";
  packageJson.devDependencies.autoprefixer = "^10.4.20";
  for (const dependency of ["@vitejs/plugin-react", "vite", "vite-plugin-eslint"]) {
    delete packageJson.devDependencies[dependency];
  }

  await writeFile(packagePath, `${JSON.stringify(packageJson, null, 2)}\n`);
  await rm(path.join(projectDir, "package-lock.json"), { force: true });
}

const tsconfig = {
  compilerOptions: {
    target: "ES2017",
    lib: ["dom", "dom.iterable", "esnext"],
    allowJs: false,
    skipLibCheck: true,
    strict: false,
    noEmit: true,
    esModuleInterop: true,
    module: "esnext",
    moduleResolution: "bundler",
    baseUrl: ".",
    paths: {
      "@/*": ["./*"],
      "ui/*": ["./src/ui/*"],
      "features/*": ["./src/features/*"],
      "hooks/*": ["./src/hooks/*"],
      "services/*": ["./src/services/*"],
      "utils/*": ["./src/utils/*"],
      "styles/*": ["./src/styles/*"],
      "context/*": ["./src/context/*"],
    },
    resolveJsonModule: true,
    isolatedModules: true,
    jsx: "preserve",
    incremental: true,
    plugins: [{ name: "next" }],
  },
  include: ["next-env.d.ts", "**/*.ts", "**/*.tsx", ".next/types/**/*.ts"],
  exclude: [
    "node_modules",
    "starter",
    "**/App-v*.tsx",
    "**/*-memo.tsx",
    "**/src-no-context/**",
    "**/starter.ts",
  ],
};

async function addTypeScript(projectDir) {
  await writeFile(
    path.join(projectDir, "tsconfig.json"),
    `${JSON.stringify(tsconfig, null, 2)}\n`,
  );
  await writeFile(
    path.join(projectDir, "next-env.d.ts"),
    '/// <reference types="next" />\n/// <reference types="next/image-types/global" />\n',
  );
}

const tailwindDirectives = `@tailwind base;
@tailwind components;
@tailwind utilities;
`;

async function ensureTailwind(projectDir, cssRelativePath) {
  const tailwindConfig = path.join(projectDir, "tailwind.config.cjs");
  try {
    await readFile(path.join(projectDir, "tailwind.config.js"), "utf8");
  } catch {
    await writeFile(
      tailwindConfig,
      `/** @type {import("tailwindcss").Config} */
module.exports = {
  content: [
    "./pages/**/*.{ts,tsx}",
    "./app/**/*.{ts,tsx}",
    "./src/**/*.{ts,tsx}",
    "./components/**/*.{ts,tsx}",
  ],
  theme: { extend: {} },
  plugins: [],
};
`,
    );
  }

  try {
    await readFile(path.join(projectDir, "postcss.config.js"), "utf8");
  } catch {
    await writeFile(
      path.join(projectDir, "postcss.config.cjs"),
      `module.exports = {
  plugins: {
    tailwindcss: {},
    autoprefixer: {},
  },
};
`,
    );
  }

  const cssPath = path.join(projectDir, cssRelativePath);
  await mkdir(path.dirname(cssPath), { recursive: true });
  let css = "";
  try {
    css = await readFile(cssPath, "utf8");
  } catch {
    // A new Tailwind entry file will be created.
  }
  if (!css.includes("@tailwind base")) {
    await writeFile(cssPath, `${tailwindDirectives}\n${css}`);
  }
}

async function migrateCodeFiles(directory) {
  let entries;
  try {
    entries = await readdir(directory, { withFileTypes: true });
  } catch {
    return;
  }

  for (const entry of entries) {
    if (["node_modules", ".next", "public"].includes(entry.name)) continue;

    const filePath = path.join(directory, entry.name);
    if (entry.isDirectory()) {
      await migrateCodeFiles(filePath);
      continue;
    }

    if (!entry.name.endsWith(".js") && !entry.name.endsWith(".jsx")) continue;
    if (
      [
        "next.config.js",
        "postcss.config.js",
        "tailwind.config.js",
        "vite.config.js",
      ].includes(entry.name)
    ) {
      continue;
    }

    let source = await readFile(filePath, "utf8");
    source = source
      .replace(/(from\s+["'][^"']+)\.(?:js|jsx)(["'])/g, "$1$2")
      .replace(/(import\s*\(\s*["'][^"']+)\.(?:js|jsx)(["']\s*\))/g, "$1$2");
    const containsJsx = /<\/?[A-Za-z][^>]*>|<>|<\/>/.test(source);
    const extension = containsJsx || entry.name.endsWith(".jsx") ? ".tsx" : ".ts";
    const destination = filePath.replace(/\.(?:js|jsx)$/, extension);
    await writeFile(filePath, source);
    await rename(filePath, destination);
  }
}

for (const [relativeDir, appImport, kind = "default"] of projects) {
  const projectDir = path.join(root, relativeDir);
  await convertPackage(projectDir);
  await addTypeScript(projectDir);
  await ensureTailwind(
    projectDir,
    kind === "style" ? "src/style.css" : "src/index.css",
  );
  await mkdir(path.join(projectDir, "pages"), { recursive: true });
  await writeFile(path.join(projectDir, "pages", "[[...slug]].tsx"), page);
  await writeFile(path.join(projectDir, "pages", "_app.tsx"), appShell(kind));
  await writeFile(
    path.join(projectDir, "src", "NextApp.jsx"),
    nextAppSource(appImport, kind),
  );
}

const pizzaDir = path.join(root, "03-pizza-menu/final");
try {
  const pizzaEntry = await readFile(path.join(pizzaDir, "src", "index.js"), "utf8");
  const pizzaApp = pizzaEntry
    .replace('import ReactDOM from "react-dom/client";\n', "")
    .replace('import "./index.css";\n', "")
    .split("// React v18")[0]
    .concat("export default App;\n");
  await writeFile(path.join(pizzaDir, "src", "App.jsx"), pizzaApp);
} catch {
  // The app was already extracted during an earlier conversion run.
}

for (const formName of ["Form.jsx", "Form.tsx"]) {
  const formPath = path.join(root, "11-worldwise/final/src/components", formName);
  try {
    const form = await readFile(formPath, "utf8");
    await writeFile(
      formPath,
      form.replace('import "react-datepicker/dist/react-datepicker.css";\n', ""),
    );
  } catch {
    // Try the other extension.
  }
}

const manualSsrDir = path.join(root, "20-manual-ssr/final");
await convertPackage(manualSsrDir);
await addTypeScript(manualSsrDir);
await mkdir(path.join(manualSsrDir, "pages"), { recursive: true });
await writeFile(
  path.join(manualSsrDir, "pages", "index.tsx"),
  `import { useState } from "react";

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
            <h4>{pizza.name} ($\${pizza.price})</h4>
            <Counter />
          </li>
        ))}
      </ul>
    </div>
  );
}
`,
);

const pureReactDir = path.join(root, "01-pure-react/final");
await mkdir(path.join(pureReactDir, "pages"), { recursive: true });
await writeFile(
  path.join(pureReactDir, "package.json"),
  `${JSON.stringify(
    {
      name: "01-pure-react-nextjs",
      version: "1.0.0",
      private: true,
      scripts: { dev: "next dev", build: "next build --webpack", start: "next start" },
      dependencies: { next: nextVersion, react: "^18.2.0", "react-dom": "^18.2.0" },
      devDependencies: {
        typescript: "^5.6.3",
        "@types/node": "^20.17.0",
        "@types/react": "^18.3.12",
        "@types/react-dom": "^18.3.1",
        tailwindcss: "^3.4.17",
        postcss: "^8.4.49",
        autoprefixer: "^10.4.20",
      },
    },
    null,
    2,
  )}\n`,
);
await addTypeScript(pureReactDir);
await ensureTailwind(pureReactDir, "styles/globals.css");
await writeFile(
  path.join(pureReactDir, "pages", "_app.tsx"),
  `import "../styles/globals.css";
import type { AppProps } from "next/app";

export default function MyApp({ Component, pageProps }: AppProps) {
  return <Component {...pageProps} />;
}
`,
);
await writeFile(
  path.join(pureReactDir, "pages", "index.tsx"),
  `import { useEffect, useState } from "react";

export default function Home() {
  const [time, setTime] = useState("");

  useEffect(() => {
    const updateTime = () => setTime(new Date().toLocaleTimeString());
    updateTime();
    const timer = setInterval(updateTime, 1000);
    return () => clearInterval(timer);
  }, []);

  return <header>Hello React! It&apos;s {time}</header>;
}
`,
);

const existingNextProjects = [
  "21-the-wild-oasis-website/final-1-after-overview",
  "21-the-wild-oasis-website/final-2-after-start",
  "21-the-wild-oasis-website/final-3-after-data",
  "21-the-wild-oasis-website/final-4-after-interactions",
  "21-the-wild-oasis-website/final-5-after-auth",
  "21-the-wild-oasis-website/final-6-after-server-actions",
  "22-nextjs-pages-router/final",
];

for (const relativeDir of existingNextProjects) {
  const projectDir = path.join(root, relativeDir);
  const packagePath = path.join(projectDir, "package.json");
  const packageJson = JSON.parse(await readFile(packagePath, "utf8"));
  packageJson.dependencies.next = nextVersion;
  packageJson.scripts.build = "next build --webpack";
  if (packageJson.scripts?.lint === "next lint") {
    delete packageJson.scripts.lint;
  }
  packageJson.devDependencies ??= {};
  packageJson.devDependencies.typescript = "^5.6.3";
  packageJson.devDependencies["@types/node"] = "^20.17.0";
  packageJson.devDependencies["@types/react"] = "^18.3.12";
  packageJson.devDependencies["@types/react-dom"] = "^18.3.1";
  packageJson.devDependencies.tailwindcss = "^3.4.17";
  packageJson.devDependencies.postcss = "^8.4.49";
  packageJson.devDependencies.autoprefixer = "^10.4.20";
  await writeFile(packagePath, `${JSON.stringify(packageJson, null, 2)}\n`);
  await addTypeScript(projectDir);
  const existingGlobalCss = relativeDir.startsWith("21-")
    ? "app/_styles/globals.css"
    : "styles/globals.css";
  await ensureTailwind(projectDir, existingGlobalCss);
  await rm(path.join(projectDir, "jsconfig.json"), { force: true });
}

for (const [relativeDir] of projects) {
  const projectDir = path.join(root, relativeDir);
  await rm(path.join(projectDir, "src", "index.js"), { force: true });
  await rm(path.join(projectDir, "src", "main.jsx"), { force: true });
  await rm(path.join(projectDir, "vite.config.js"), { force: true });
  await migrateCodeFiles(path.join(projectDir, "src"));
  await migrateCodeFiles(path.join(projectDir, "pages"));
}

const progressiveSnapshotProjects = [
  "17-the-wild-oasis/final-1-after-setup",
  "17-the-wild-oasis/final-2-after-supabase",
  "17-the-wild-oasis/final-3-after-react-query",
  "17-the-wild-oasis/final-4-after-advanced-patterns",
  "17-the-wild-oasis/final-5-after-sort-filter-pagination",
  "17-the-wild-oasis/final-6-final",
];

for (const relativeDir of progressiveSnapshotProjects) {
  const projectDir = path.join(root, relativeDir);
  const stageName = relativeDir.split("/").at(-1);
  await writeFile(
    path.join(projectDir, "src", "StagePage.tsx"),
    `export default function StagePage() {
  return (
    <main className="mx-auto flex min-h-screen max-w-3xl items-center px-6 py-16">
      <section className="w-full rounded-3xl border border-slate-200 bg-white p-8 shadow-xl sm:p-12">
        <p className="text-sm font-bold uppercase tracking-[0.2em] text-emerald-600">
          Progressive course snapshot
        </p>
        <h1 className="mt-3 text-3xl font-bold text-slate-900 sm:text-5xl">
          ${stageName}
        </h1>
        <p className="mt-5 leading-7 text-slate-600">
          Folder ini menyimpan kode pada tahap pembelajaran tersebut. Gunakan
          final-6-final untuk menjalankan aplikasi Wild Oasis yang lengkap.
        </p>
      </section>
    </main>
  );
}
`,
  );
  await writeFile(
    path.join(projectDir, "pages", "[[...slug]].tsx"),
    `export { default } from "../src/StagePage";
`,
  );
  const projectTsconfig = JSON.parse(
    await readFile(path.join(projectDir, "tsconfig.json"), "utf8"),
  );
  projectTsconfig.include = [
    "next-env.d.ts",
    "pages/**/*.ts",
    "pages/**/*.tsx",
    "src/StagePage.tsx",
    ".next/types/**/*.ts",
  ];
  await writeFile(
    path.join(projectDir, "tsconfig.json"),
    `${JSON.stringify(projectTsconfig, null, 2)}\n`,
  );
}

for (const relativeDir of existingNextProjects) {
  const projectDir = path.join(root, relativeDir);
  await migrateCodeFiles(path.join(projectDir, "app"));
  await migrateCodeFiles(path.join(projectDir, "pages"));
  await migrateCodeFiles(path.join(projectDir, "components"));
  await migrateCodeFiles(path.join(projectDir, "lib"));
  await migrateCodeFiles(path.join(projectDir, "starter"));

  const middleware = path.join(projectDir, "middleware.js");
  try {
    const source = (await readFile(middleware, "utf8")).replace(
      "export const middleware = auth;",
      "export const proxy = auth;",
    );
    await writeFile(path.join(projectDir, "proxy.ts"), source);
    await rm(middleware);
  } catch {
    // This project does not have middleware.
  }
}

for (const chapter of await readdir(root, { withFileTypes: true })) {
  if (!chapter.isDirectory()) continue;
  await migrateCodeFiles(path.join(root, chapter.name, "starter"));
  await migrateCodeFiles(path.join(root, chapter.name, "final"));
}

await migrateCodeFiles(path.join(root, "10-react-quiz/final/src-no-context"));

for (const relativeDir of ["13-workout-timer/starter", "13-workout-timer/final"]) {
  const projectDir = path.join(root, relativeDir);
  await mkdir(path.join(projectDir, "public"), { recursive: true });
  await copyFile(
    path.join(projectDir, "src", "ClickSound.m4a"),
    path.join(projectDir, "public", "click-sound.m4a"),
  );
  const calculatorPath = path.join(projectDir, "src", "Calculator.tsx");
  const calculator = (await readFile(calculatorPath, "utf8")).replace(
    /import clickSound from ["']\.\/ClickSound\.m4a["'];\n/,
    'const clickSound = "/click-sound.m4a";\n',
  );
  await writeFile(calculatorPath, calculator);
}

for (const legacyFile of [
  "client.js",
  "server.js",
  "start.js",
  "starter.js",
  "index.html",
  ".babelrc",
]) {
  await rm(path.join(manualSsrDir, legacyFile), { force: true });
}
await migrateCodeFiles(path.join(root, "20-manual-ssr/starter"));
await rm(path.join(pureReactDir, "index.html"), { force: true });

await ensureTailwind(manualSsrDir, "styles/globals.css");
await writeFile(
  path.join(manualSsrDir, "pages", "_app.tsx"),
  `import "../styles/globals.css";
import type { AppProps } from "next/app";

export default function MyApp({ Component, pageProps }: AppProps) {
  return <Component {...pageProps} />;
}
`,
);

const starterProjects = [
  "02-JS-review/starter",
  "03-pizza-menu/starter",
  "04-steps/starter",
  "05-travel-list/starter",
  "06-eat-n-split/starter",
  "07-usepopcorn/starter",
  "09-classy-weather/starter",
  "10-react-quiz/starter",
  "11-worldwise/starter",
  "15-redux-intro/starter",
  "16-fast-react-pizza/starter",
  "17-the-wild-oasis/starter",
  "20-manual-ssr/starter",
  "21-the-wild-oasis-website/starter",
  "22-nextjs-pages-router/starter",
];

for (const relativeDir of starterProjects) {
  const projectDir = path.join(root, relativeDir);
  const chapter = relativeDir.split("/")[0];
  await mkdir(path.join(projectDir, "app"), { recursive: true });
  await writeFile(
    path.join(projectDir, "package.json"),
    `${JSON.stringify(
      {
        name: `next-course-${chapter.toLowerCase()}-starter`,
        version: "1.0.0",
        private: true,
        scripts: { dev: "next dev", build: "next build --webpack", start: "next start" },
        dependencies: { next: nextVersion, react: "^18.2.0", "react-dom": "^18.2.0" },
        devDependencies: {
          typescript: "^5.6.3",
          "@types/node": "^20.17.0",
          "@types/react": "^18.3.12",
          "@types/react-dom": "^18.3.1",
          tailwindcss: "^3.4.17",
          postcss: "^8.4.49",
          autoprefixer: "^10.4.20",
        },
      },
      null,
      2,
    )}\n`,
  );
  await addTypeScript(projectDir);
  const starterTsconfig = JSON.parse(await readFile(path.join(projectDir, "tsconfig.json"), "utf8"));
  starterTsconfig.include = ["next-env.d.ts", "app/**/*.ts", "app/**/*.tsx", ".next/types/**/*.ts"];
  await writeFile(path.join(projectDir, "tsconfig.json"), `${JSON.stringify(starterTsconfig, null, 2)}\n`);
  await ensureTailwind(projectDir, "app/globals.css");
  await writeFile(
    path.join(projectDir, "app", "layout.tsx"),
    `import "./globals.css";
import type { Metadata } from "next";
import type { ReactNode } from "react";

export const metadata: Metadata = {
  title: "${chapter} Starter",
  description: "Template latihan Next.js, TypeScript, dan Tailwind CSS",
};

export default function RootLayout({ children }: { children: ReactNode }) {
  return (
    <html lang="id">
      <body className="min-h-screen bg-slate-950 text-slate-100 antialiased">
        {children}
      </body>
    </html>
  );
}
`,
  );
  await writeFile(
    path.join(projectDir, "app", "page.tsx"),
    `export default function HomePage() {
  return (
    <main className="mx-auto flex min-h-screen max-w-3xl items-center px-6 py-16">
      <section className="w-full rounded-3xl border border-slate-800 bg-slate-900 p-8 shadow-2xl sm:p-12">
        <p className="mb-3 text-sm font-bold uppercase tracking-[0.25em] text-sky-400">
          Starter project
        </p>
        <h1 className="text-3xl font-bold tracking-tight sm:text-5xl">
          ${chapter}
        </h1>
        <p className="mt-5 max-w-2xl text-lg leading-8 text-slate-300">
          Template sudah siap dengan Next.js, TypeScript, dan Tailwind CSS.
          Mulai latihan dengan mengubah file app/page.tsx.
        </p>
        <div className="mt-8 rounded-2xl bg-slate-950 p-5 font-mono text-sm text-emerald-300">
          npm run dev
        </div>
      </section>
    </main>
  );
}
`,
  );
}

const workspaceProjects = [
  "01-pure-react/final",
  ...projects.map(([relativeDir]) => relativeDir),
  "20-manual-ssr/final",
  ...existingNextProjects,
  ...starterProjects,
];

for (const relativeDir of workspaceProjects) {
  const packagePath = path.join(root, relativeDir, "package.json");
  const packageJson = JSON.parse(await readFile(packagePath, "utf8"));
  packageJson.name = `next-course-${relativeDir
    .toLowerCase()
    .replace(/[^a-z0-9]+/g, "-")
    .replace(/^-|-$/g, "")}`;
  await writeFile(packagePath, `${JSON.stringify(packageJson, null, 2)}\n`);
}

const remoteFontFiles = [
  ...existingNextProjects
    .filter((project) => project.startsWith("21-"))
    .map((project) => path.join(root, project, "app", "layout.tsx")),
  path.join(root, "22-nextjs-pages-router/final/pages/_app.tsx"),
];

for (const fontFile of remoteFontFiles) {
  try {
    let source = await readFile(fontFile, "utf8");
    source = source
      .replace(/import \{ Josefin_Sans \} from "next\/font\/google";\n\n/, "")
      .replace(
        /const josefin = Josefin_Sans\(\{\n  subsets: \["latin"\],\n  display: "swap",\n\}\);\n\n/,
        "",
      )
      .replace(/\$\{josefin\.className\} /g, "font-sans ");
    await writeFile(fontFile, source);
  } catch {
    // Earlier snapshots may not contain this layout yet.
  }
}

await writeFile(
  path.join(root, "package.json"),
  `${JSON.stringify(
    {
      name: "ultimate-nextjs-typescript-course",
      version: "1.0.0",
      private: true,
      scripts: {
        typecheck: "npm exec --workspaces -- tsc --noEmit --pretty false",
      },
      workspaces: workspaceProjects,
    },
    null,
    2,
  )}\n`,
);

console.log(`Prepared ${workspaceProjects.length} Next.js TypeScript projects.`);
