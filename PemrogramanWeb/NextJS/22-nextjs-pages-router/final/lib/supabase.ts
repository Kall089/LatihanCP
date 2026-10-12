import { createClient } from "@supabase/supabase-js";

export const supabase = createClient(
  process.env.SUPABASE_URL ?? "https://example.supabase.co",
  process.env.SUPABASE_KEY ?? "development-anon-key",
);
