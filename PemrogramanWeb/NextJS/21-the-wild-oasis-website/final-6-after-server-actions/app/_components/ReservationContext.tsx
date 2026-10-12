"use client";

import {
  createContext,
  type Dispatch,
  type ReactNode,
  type SetStateAction,
  useContext,
  useState,
} from "react";

type DateRange = { from: Date | undefined; to?: Date };
type ReservationContextValue = {
  range: DateRange;
  setRange: Dispatch<SetStateAction<DateRange>>;
  resetRange: () => void;
};

const ReservationContext = createContext<ReservationContextValue | undefined>(
  undefined,
);

const initialState: DateRange = { from: undefined, to: undefined };

function ReservationProvider({ children }: { children: ReactNode }) {
  const [range, setRange] = useState(initialState);
  const resetRange = () => setRange(initialState);

  return (
    <ReservationContext.Provider value={{ range, setRange, resetRange }}>
      {children}
    </ReservationContext.Provider>
  );
}

function useReservation() {
  const context = useContext(ReservationContext);
  if (context === undefined)
    throw new Error("Context was used outside provider");
  return context;
}

export { ReservationProvider, useReservation };
