// Dashboard interaktif — pola state → render.
// Cek sintaks: node --check script.js

// TODO 1: array pesanan minimal 6 objek { id, nama, kategori, harga }
const pesanan = [];

// TODO 2: state filter ("semua" | "kopi" | "nonkopi" | "snack")
let filterKategori = "semua";

const daftarEl = document.querySelector("#daftar");
const totalEl = document.querySelector("#total");
const formEl = document.querySelector("#form-pesanan");
const pesanEl = document.querySelector("#pesan");
const filterEl = document.querySelector("#filter");

function formatRupiah(n) {
  return "Rp" + Number(n).toLocaleString("id-ID");
}

function render() {
  // TODO 3: saring pesanan sesuai filterKategori
  // TODO 4: kosongkan #daftar, buat <li> per item (nama, kategori, harga, tombol hapus)
  //         pakai textContent / createElement — jangan innerHTML dari input user
  // TODO 5: update #total dari jumlah item yang tampil (atau total semua — pilih, konsisten)
}

// TODO 6: klik tombol [data-kategori] → set filterKategori → render()

// TODO 7: submit form → preventDefault, validasi nama trim & harga angka > 0,
//         tampilkan pesan error di #pesan, jika valid push objek baru + render + reset

// TODO 8: delegasi klik tombol hapus di #daftar → hapus by id → render()

render();
