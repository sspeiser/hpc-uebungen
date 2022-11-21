public class MemoryModel {

    public int counter = 0;
    public boolean done = false;

    public static void main(String[] args) {
        final MemoryModel m = new MemoryModel();
        
        Thread t1 = new Thread(() -> {
            int i = 0;
            while(m.counter < 100) {
                // wait
                i++;
            }
            m.done = true;
            System.out.println("Done");
        });
        t1.start();

        Thread t2 = new Thread(() -> {
            while(!m.done) {
                m.counter++;
            }
            System.out.println("Counted to " + m.counter);
        });
        t2.start();
    }
    
}