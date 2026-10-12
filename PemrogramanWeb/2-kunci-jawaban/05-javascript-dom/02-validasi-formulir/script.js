const form = document.querySelector("#register-form");
const nameInput = document.querySelector("#name");
const emailInput = document.querySelector("#email");
const message = document.querySelector("#message");

form.addEventListener("submit", (event) => {
  event.preventDefault();
  const name = nameInput.value.trim();
  const email = emailInput.value.trim();
  if (name.length < 3) { message.textContent = "Nama minimal 3 karakter."; return; }
  if (!email || !emailInput.validity.valid) { message.textContent = "Masukkan email yang valid."; return; }
  message.textContent = `Selamat datang, ${name}!`;
  form.reset();
});
