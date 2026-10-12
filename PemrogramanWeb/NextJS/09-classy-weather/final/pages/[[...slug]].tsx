import dynamic from "next/dynamic";

const CourseApp = dynamic(() => import("../src/NextApp"), { ssr: false });

export default function Page() {
  return <CourseApp />;
}
