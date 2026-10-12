import styles from "./Button.module.css";
import type { MouseEventHandler, ReactNode } from "react";

function Button({
  children,
  onClick,
  type,
}: {
  children: ReactNode;
  onClick?: MouseEventHandler<HTMLButtonElement>;
  type: string;
}) {
  return (
    <button onClick={onClick} className={`${styles.btn} ${styles[type]}`}>
      {children}
    </button>
  );
}

export default Button;
