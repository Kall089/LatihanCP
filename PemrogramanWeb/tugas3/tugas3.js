const destinasiList = {
  rajaampat: {
    nama: "Raja Ampat",
    lokasi: "Papua Barat Daya",
    info: "Kepulauan dengan laut jernih dan terumbu karang yang indah.",
    harga: 500000,
  },
  bromo: {
    nama: "Gunung Bromo",
    lokasi: "Probolinggo, Jawa Timur",
    info: "Gunung berapi aktif yang terkenal dengan pemandangan sunrise.",
    harga: 35000,
  },
  borobudur: {
    nama: "Candi Borobudur",
    lokasi: "Magelang, Jawa Tengah",
    info: "Candi Buddha terbesar di dunia dan situs warisan budaya.",
    harga: 50000,
  },
  dufan: {
    nama: "Dufan",
    lokasi: "Ancol, Jakarta Utara",
    info: "Taman hiburan dengan berbagai wahana permainan keluarga.",
    harga: 275000,
  },
  toba: {
    nama: "Danau Toba",
    lokasi: "Sumatera Utara",
    info: "Danau vulkanik terbesar di Indonesia dengan Pulau Samosir di tengahnya.",
    harga: 25000,
  },
  safari: {
    nama: "Taman Safari",
    lokasi: "Cisarua, Bogor",
    info: "Kebun binatang safari tempat pengunjung melihat satwa dari dalam kendaraan.",
    harga: 185000,
  },
};

const pilihan = document.getElementById("pilihan");
const jumlah = document.getElementById("jumlah");
const ringkasan = document.getElementById("ringkasan");
const hasil = document.getElementById("hasil");

let totalTerakhir = 0;
let destinasiTerpilih = "";

function formatRupiah(angka) {
  return "Rp " + angka.toLocaleString("id-ID");
}

function scrollKe(id) {
  const tujuan = document.getElementById(id);
  tujuan.scrollIntoView({ behavior: "smooth" });
}

function tampilkanInfo(kode) {
  const data = destinasiList[kode];

  if (!data) {
    ringkasan.innerHTML =
      "<h3>Pilih destinasi dulu</h3><p>Klik salah satu destinasi di halaman Info, atau pilih dari menu di samping.</p>";
    destinasiTerpilih = "";
    totalTerakhir = 0;
    return;
  }

  destinasiTerpilih = kode;
  ringkasan.innerHTML =
    "<h3>" +
    data.nama +
    "</h3>" +
    "<p><strong>Lokasi:</strong> " +
    data.lokasi +
    "</p>" +
    "<p><strong>Informasi:</strong> " +
    data.info +
    "</p>" +
    "<p><strong>Harga tiket:</strong> " +
    formatRupiah(data.harga) +
    " / orang</p>";
}

function pilihDestinasi(kode) {
  pilihan.value = kode;
  tampilkanInfo(kode);
  hasil.innerHTML = "";
  hasil.className = "";
  totalTerakhir = 0;
  scrollKe("tiket");
}

function hitungTiket() {
  const kode = pilihan.value;
  const orang = Number(jumlah.value);
  const data = destinasiList[kode];

  hasil.className = "";

  if (!kode || !data) {
    hasil.className = "error";
    hasil.innerHTML = "Pilih destinasi terlebih dahulu.";
    totalTerakhir = 0;
    return;
  }

  if (!orang || orang < 1) {
    hasil.className = "error";
    hasil.innerHTML = "Jumlah orang minimal 1.";
    totalTerakhir = 0;
    return;
  }

  let total = data.harga * orang;
  let teksDiskon = "";

  if (orang >= 5) {
    const diskon = total * 0.1;
    total = total - diskon;
    teksDiskon = "<p>Diskon 10% untuk 5 orang atau lebih.</p>";
  }

  totalTerakhir = total;
  destinasiTerpilih = kode;

  hasil.innerHTML =
    "<p><strong>Destinasi:</strong> " +
    data.nama +
    "</p>" +
    "<p><strong>Jumlah orang:</strong> " +
    orang +
    "</p>" +
    "<p><strong>Harga satuan:</strong> " +
    formatRupiah(data.harga) +
    "</p>" +
    teksDiskon +
    "<p><strong>Total bayar:</strong> " +
    formatRupiah(total) +
    "</p>";
}

function beliTiket() {
  if (!destinasiTerpilih || totalTerakhir <= 0) {
    hasil.className = "error";
    hasil.innerHTML = "Hitung total tiket dulu sebelum membeli.";
    return;
  }

  hasil.className = "sukses";
  hasil.innerHTML =
    "Pembelian tiket " +
    destinasiList[destinasiTerpilih].nama +
    " berhasil. Total " +
    formatRupiah(totalTerakhir) +
    ".";
}

document.querySelectorAll("[data-scroll]").forEach(function (link) {
  link.addEventListener("click", function (event) {
    event.preventDefault();
    scrollKe(link.getAttribute("data-scroll"));
  });
});

document.querySelectorAll(".btn-pilih").forEach(function (tombol) {
  tombol.addEventListener("click", function () {
    const kartu = tombol.closest(".card");
    pilihDestinasi(kartu.getAttribute("data-destinasi"));
  });
});

pilihan.addEventListener("change", function () {
  tampilkanInfo(pilihan.value);
  hasil.innerHTML = "";
  hasil.className = "";
  totalTerakhir = 0;
});

document.getElementById("btn-hitung").addEventListener("click", hitungTiket);
document.getElementById("btn-beli").addEventListener("click", beliTiket);

const tombolMenu = document.querySelector(".menu-toggle");
const navigasi = document.querySelector("nav");

function tombol() {
  navigasi.classList.toggle("buka");
}

tombolMenu.addEventListener("click", tombol);

document.querySelectorAll(".tombol a").forEach(function (link) {
  link.addEventListener("click", function () {
    setTimeout(function () {
      navigasi.classList.remove("buka");
    }, 50);
  });
});
