import java.util.Scanner;

public class FungsiLuas {

    public static void main(String[] args) {
        float panjang, lebar, luas, keliling, diagonal;

        panjang = inputFloat("Masukkan panjang: ");
        lebar = inputFloat("Masukkan Lebar: ");

        luas = cariLuas(panjang, lebar);
        keliling = cariKeliling(panjang, lebar);                                  
        diagonal = cariDiagonal(panjang, lebar);

        System.out.println("Luas persegi panjang: " + luas);
        System.out.println("Keliling persegi panjang: " + keliling);
        System.out.println("Diagonal persegi panjang: " + diagonal);
    }

    static float inputFloat(String pesan) {
        Scanner input = new Scanner(System.in);

        System.out.print(pesan);
        float hasilInput = input.nextFloat();
        return hasilInput;
    }

    static float cariLuas(float panjang, float lebar) {
        float hasilLuas = panjang * lebar;
        return hasilLuas;
    }

    static float cariKeliling(float panjang, float lebar) {
        float hasilKeliling = 2 * (panjang + lebar);
        return hasilKeliling;
    }

    static float cariDiagonal(float panjang, float lebar) {
        float hasilDiagonal = (float) Math.sqrt((panjang * panjang) + (lebar * lebar));
        return hasilDiagonal;
    }
}