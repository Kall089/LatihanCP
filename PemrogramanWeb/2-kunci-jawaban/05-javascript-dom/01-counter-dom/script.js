let count = 0;

const countOutput = document.querySelector("#count");
const message = document.querySelector("#message");
const decreaseButton = document.querySelector("#decrease");
const increaseButton = document.querySelector("#increase");
const resetButton = document.querySelector("#reset");

function render() {
  countOutput.textContent = count;
  if (count >= 5) {
    message.textContent = "Hebat! Target lima sesi tercapai.";
    message.classList.add("success");
  } else {
    message.textContent = "";
    message.classList.remove("success");
  }
}

increaseButton.addEventListener("click", () => { count += 1; render(); });

decreaseButton.addEventListener("click", () => { count = Math.max(0, count - 1); render(); });

resetButton.addEventListener("click", () => { count = 0; render(); });

render();
