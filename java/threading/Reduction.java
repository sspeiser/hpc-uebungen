public class Reduction {
    
    public static final int N_THREADS = 4;
    public static final int N = 1 << 28;
    static double sum = 0.0;
    public static void main(String[] args) {
        
        double[] a = new double[N];
        for(int i = 0; i < N; i++) {
            a[i] = Math.random() / N;
        }

        // sequenziell
        long start = System.currentTimeMillis();
        
        for(int i = 0; i < N; i++) {
            sum += a[i];
        }

        long end = System.currentTimeMillis();
        long duration = end - start;
        System.out.println("Result: " + sum);
        System.out.println("Duration: " + duration);

        sum = 0.0;
        start = System.currentTimeMillis();
        final Object lock = new Object();
        Thread[] forks = new Thread[N_THREADS];
        double[] sums = new double[N_THREADS];
        for(int j = 0; j < N_THREADS; j++) {
            sums[j] = 0.0; 
        }
        int numbers_per_thread = N / N_THREADS;
        for(int j = 0; j < forks.length; j++) {
            final int start_idx = j * numbers_per_thread;
            final int end_idx = start_idx + numbers_per_thread - 1;
            final int thread_nr = j;
            forks[j] = new Thread(() -> {
                for(int i = start_idx; i <= end_idx; i++) {
                        sums[thread_nr] += a[i];
                }
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
        for(double x : sums) {
            sum += x;
        }

        end = System.currentTimeMillis();
        duration = end - start;
        System.out.println("Fork Result: " + sum);
        System.out.println("Fork Duration: " + duration);


        // System.out.println("Done!");

    }
}
