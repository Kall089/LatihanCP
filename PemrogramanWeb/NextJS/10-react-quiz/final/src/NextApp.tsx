import App from "./components/App";
import { QuizProvider } from "./contexts/QuizContext";

export default function NextApp() {
  return (
    <QuizProvider>
      <App />
    </QuizProvider>
  );
}
