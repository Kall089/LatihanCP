let count = 0;

// TODO 1: Ambil elemen count, message, dan ketiga tombol dengan querySelector.
const Output = document.querySelector("#count");
const increase = document.querySelector("#increase");
const decrease = document.querySelector("#decrease");
const message = document.querySelector("#message");
const reset = document.querySelector("#reset");

function render() {
  // TODO 2: Tampilkan nilai count ke elemen output.
  Output.textContent = count;

  if (count >= 5) {
    message.textContent = "Selamat anda berhasil";
    message.classList.add("success");
  } else {
    message.textContent = "";
    message.classList.remove("success");
  }
  // TODO 3: Jika count >= 5, tampilkan pesan motivasi dan class "success".
  // TODO 4: Jika count < 5, kosongkan pesan dan hapus class "success".
}

// TODO 5: Saat tombol tambah diklik, tambah count lalu panggil render().

increase.addEventListener("click", () => {
  if (count >= 0 && count < 5) {
    count += 1;
  }
  render();
});
// TODO 6: Saat tombol kurang diklik, kurangi count tanpa melewati nol.

decrease.addEventListener("click", () => {
  if (count > 0 && count <= 5) {
    count -= 1;
  }
  render();
});

// TODO 7: Saat tombol reset diklik, ubah count menjadi nol lalu render().

reset.addEventListener("click", () => {
  ((count = 0), render());
});

render();
