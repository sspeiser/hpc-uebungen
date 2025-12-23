public class FloatRange {
    public static void main(String args[]) {
        float geld = 1.0e9f;
        float joghurt = 0.99f;
        geld += joghurt;
        System.out.println("Geld: " + geld);


        double masseSonne = 5.0e15;
        double masseAtom = 1.0e-9;

        double produkt = masseSonne * masseAtom;
        System.out.println("Produkt: " + produkt);
    }
}
