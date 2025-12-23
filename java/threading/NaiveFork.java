public class NaiveFork {
    public static final int N_THREADS = 6;
    public static void main(String[] args) {
        
        System.out.println("Hello");

        Thread[] forks = new Thread[N_THREADS];

        for(int i = 0; i < forks.length; i++) {
            final int thread_nr = i; 
            forks[i] = new Thread(() -> {
                System.out.println("World from " + thread_nr);
            });
        }

        for(Thread fork : forks) {
            fork.start();
        }

        for(Thread fork : forks) {
            try { 
                fork.join();
            } catch(InterruptedException e) {

            }
        }

        System.out.println("Done!");

    }
}