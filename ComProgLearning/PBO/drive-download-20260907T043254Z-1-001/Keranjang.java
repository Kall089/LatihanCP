// ! DON'T MODIFY
public class Keranjang {
    private Item[] daftarItem;
    private double total;

    public Keranjang(Item[] daftarItem) {
        this.daftarItem = daftarItem;
        this.hitungTotalAwal();
    }

    private void hitungTotalAwal() {
        for (int i = 0; i < daftarItem.length; i++) {
            total += daftarItem[i].getSubTotal();
        }
    }

    public Item[] getDaftarItem() {
        return daftarItem;
    }

    public void setDaftarItem(Item[] daftarItem) {
        this.daftarItem = daftarItem;
    }

    public double getTotal() {
        return total;
    }

    public void setTotal(double total) {
        this.total = total;
    }
}
