import { ErrorBoundary } from "react-error-boundary";
import App from "./App";
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
