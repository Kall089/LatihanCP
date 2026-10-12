// ! DON'T MODIFY
public class Item {
    private Produk produk;
    private int jumlah;
    private double subTotal;

    public Item(Produk produk, int jumlah) {
        this.produk = produk;
        this.jumlah = jumlah;
        this.subTotal = produk.getHarga() * jumlah;
    }

    public Produk getProduk() {
        return produk;
    }

    public void setProduk(Produk produk) {
        this.produk = produk;
    }

    public int getJumlah() {
        return jumlah;
    }

    public void setJumlah(int jumlah) {
        this.jumlah = jumlah;
    }

    public double getSubTotal() {
        return subTotal;
    }

    public void setSubTotal(double subTotal) {
        this.subTotal = subTotal;
    }
}
