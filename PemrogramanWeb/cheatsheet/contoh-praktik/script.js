const produk = [
  { id: 1, nama: "Buku JavaScript", harga: 45000 },
  { id: 2, nama: "Buku CSS", harga: 40000 },
  { id: 3, nama: "Tas Kuliah", harga: 90000 },
];

const favorit = new Set();
const inputCari = document.querySelector("#cari");
const inputHarga = document.querySelector("#harga-max");
const daftar = document.querySelector("#daftar");
const status = document.querySelector("#status");

function formatRupiah(nilai) {
  return new Intl.NumberFormat("id-ID", {
    style: "currency",
    currency: "IDR",
    maximumFractionDigits: 0,
  }).format(nilai);
}

function render() {
  const kata = inputCari.value.trim().toLowerCase();
  const batas = Number(inputHarga.value);
  const hasil = produk.filter((item) => {
    const namaCocok = item.nama.toLowerCase().includes(kata);
    const hargaCocok = !Number.isFinite(batas) || inputHarga.value === "" || item.harga <= batas;
    return namaCocok && hargaCocok;
  });

  status.textContent = `${hasil.length} produk ditampilkan.`;
  daftar.replaceChildren();

  if (hasil.length === 0) {
    const kosong = document.createElement("li");
    kosong.textContent = "Tidak ada yang cocok. Coba kata lain.";
    daftar.append(kosong);
    return;
  }

  for (const item of hasil) {
    const kartu = document.createElement("li");
    kartu.className = "kartu";
    if (favorit.has(item.id)) kartu.classList.add("favorit");

    const info = document.createElement("div");
    const judul = document.createElement("h2");
    judul.textContent = item.nama;
    const harga = document.createElement("p");
    harga.className = "harga";
    harga.textContent = formatRupiah(item.harga);
    info.append(judul, harga);

    const tombol = document.createElement("button");
    tombol.type = "button";
    tombol.className = "tombol-favorit";
    tombol.textContent = favorit.has(item.id) ? "Favorit" : "Tandai";
    tombol.addEventListener("click", () => {
      if (favorit.has(item.id)) favorit.delete(item.id);
      else favorit.add(item.id);
      render();
    });

    kartu.append(info, tombol);
    daftar.append(kartu);
  }
}

inputCari.addEventListener("input", render);
inputHarga.addEventListener("input", render);
render();
