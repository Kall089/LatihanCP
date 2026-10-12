const pesanan = [
  { id: 1, nama: "Kopi Susu Senja", kategori: "kopi", harga: 18000 },
  { id: 2, nama: "Americano", kategori: "kopi", harga: 14000 },
  { id: 3, nama: "Teh Tarik", kategori: "nonkopi", harga: 12000 },
  { id: 4, nama: "Cokelat Panas", kategori: "nonkopi", harga: 15000 },
  { id: 5, nama: "Roti Bakar", kategori: "snack", harga: 15000 },
  { id: 6, nama: "Pisang Goreng", kategori: "snack", harga: 10000 },
];

let filterKategori = "semua";
let idBerikutnya = 7;

const daftarEl = document.querySelector("#daftar");
const totalEl = document.querySelector("#total");
const formEl = document.querySelector("#form-pesanan");
const pesanEl = document.querySelector("#pesan");
const filterEl = document.querySelector("#filter");
const inputNama = document.querySelector("#nama");
const inputKategori = document.querySelector("#kategori");
const inputHarga = document.querySelector("#harga");

function formatRupiah(n) {
  return "Rp" + Number(n).toLocaleString("id-ID");
}

function itemTampil() {
  if (filterKategori === "semua") return pesanan;
  return pesanan.filter((item) => item.kategori === filterKategori);
}

function perbaruiTombolFilter() {
  filterEl.querySelectorAll("button[data-kategori]").forEach((tombol) => {
    const aktif = tombol.dataset.kategori === filterKategori;
    tombol.classList.toggle("bg-slate-900", aktif);
    tombol.classList.toggle("text-white", aktif);
    tombol.classList.toggle("bg-white", !aktif);
    tombol.classList.toggle("ring-1", !aktif);
    tombol.classList.toggle("ring-slate-200", !aktif);
  });
}

function render() {
  const data = itemTampil();
  totalEl.textContent = String(data.length);
  daftarEl.replaceChildren(
    ...data.map((item) => {
      const li = document.createElement("li");
      li.className = "rounded-2xl border border-slate-200 bg-white p-4 shadow-sm";

      const nama = document.createElement("h2");
      nama.className = "font-semibold";
      nama.textContent = item.nama;

      const meta = document.createElement("p");
      meta.className = "mt-1 text-sm text-slate-500";
      meta.textContent = item.kategori + " · " + formatRupiah(item.harga);

      const hapus = document.createElement("button");
      hapus.type = "button";
      hapus.className = "mt-3 text-sm font-medium text-rose-600";
      hapus.textContent = "Hapus";
      hapus.dataset.id = String(item.id);

      li.append(nama, meta, hapus);
      return li;
    }),
  );

  if (data.length === 0) {
    const kosong = document.createElement("li");
    kosong.className = "rounded-2xl border border-dashed border-slate-300 p-6 text-center text-slate-500 md:col-span-2";
    kosong.textContent = "Tidak ada pesanan di kategori ini.";
    daftarEl.append(kosong);
  }

  perbaruiTombolFilter();
}

filterEl.addEventListener("click", (event) => {
  const tombol = event.target.closest("button[data-kategori]");
  if (!tombol) return;
  filterKategori = tombol.dataset.kategori;
  render();
});

formEl.addEventListener("submit", (event) => {
  event.preventDefault();
  const nama = inputNama.value.trim();
  const kategori = inputKategori.value;
  const harga = Number(inputHarga.value);

  if (nama.length < 2) {
    pesanEl.textContent = "Nama item minimal 2 karakter.";
    return;
  }
  if (!Number.isFinite(harga) || harga <= 0) {
    pesanEl.textContent = "Harga harus angka lebih dari 0.";
    return;
  }

  pesanan.push({ id: idBerikutnya, nama, kategori, harga });
  idBerikutnya += 1;
  pesanEl.textContent = "";
  formEl.reset();
  render();
});

daftarEl.addEventListener("click", (event) => {
  const tombol = event.target.closest("button[data-id]");
  if (!tombol) return;
  const id = Number(tombol.dataset.id);
  const index = pesanan.findIndex((item) => item.id === id);
  if (index === -1) return;
  pesanan.splice(index, 1);
  render();
});

render();
