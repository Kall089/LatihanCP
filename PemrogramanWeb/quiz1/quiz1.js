const form = document.querySelector("#form-mhs");
const semuaInput = document.querySelectorAll(".input-nilai, .input-mhs input");
const inputNilai = document.querySelectorAll(".input-nilai");
const pesan = document.querySelector("#pesan-error");
const hasil = document.querySelector("#hasil");
const angkaMutu = { A: 4, B: 3, C: 2, D: 1, E: 0 };
const nilaiYangValid = ["A", "B", "C", "D", "E"];

form.addEventListener("submit", function (event) {
  event.preventDefault();
  hasil.hidden = true;
  let semuaValid = true;

  for (const input of semuaInput) {
    input.value = input.value.trim();
    let valid = input.value !== "";

    if (input.classList.contains("input-nilai")) {
      valid = nilaiYangValid.includes(input.value);
    }

    input.classList.toggle("input-error", !valid);
    if (!valid) semuaValid = false;
  }

  if (!semuaValid) {
    pesan.textContent =
      "Lengkapi data mahasiswa dan pilih semua nilai A–E. Periksa kolom merah.";
    document.querySelector(".input-error").focus();
    return;
  }

  let totalSKS = 0;
  let totalMutu = 0;
  let totalMatkul = 0;

  for (const input of inputNilai) {
    const baris = input.closest("tr");
    const sks = Number(baris.cells[3].textContent);
    totalMatkul += 1;
    totalSKS += sks;
    totalMutu += angkaMutu[input.value] * sks;
  }

  document.querySelector("#total-sks").textContent = totalSKS;
  document.querySelector("#total-matkul").textContent = totalMatkul;
  document.querySelector("#nilai-ip").textContent = (
    totalMutu / totalSKS
  ).toFixed(2);
  pesan.textContent = "";
  hasil.hidden = false;
});

for (const input of semuaInput) {
  input.addEventListener("input", function () {
    hasil.hidden = true;
    if (input.classList.contains("input-nilai")) {
      const valid = nilaiYangValid.includes(input.value);
      input.classList.toggle("input-error", !valid);
    }
  });
}
