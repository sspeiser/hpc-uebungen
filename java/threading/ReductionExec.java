import java.util.Collection;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class ReductionExec {
    public static final int N_THREADS = 4;
    public static final int N = 1 << 28;

    public static Callable<Double> partialSum(double[] values, int nPartitions, int partitionNr) {
        int partitionSize = values.length / nPartitions;
        int startIdx = partitionNr * partitionSize;
        int endIdx = startIdx + partitionSize - 1;
        return () -> {
            double sum = 0.0;
            for (int i = startIdx; i <= endIdx; i++) {
                sum += values[i];
            }
            return sum;
        };
    }

    public static void main(String[] args) throws InterruptedException, ExecutionException {
        double[] a = new double[N];
        for(int i = 0; i < N; i++) {
            a[i] = Math.random() / N;
        }

        long start = System.currentTimeMillis();

        double sum = 0.0;

        ExecutorService runner = Executors.newFixedThreadPool(N_THREADS);

        Collection<Callable<Double>> partialSums = IntStream.range(0, N_THREADS)
                        .mapToObj(j -> partialSum(a, N_THREADS, j))
                        .collect(Collectors.toList());
        
        List<Future<Double>> sums = runner.invokeAll(partialSums);
        for(var future_sum : sums) {
            sum += future_sum.get();
        }

        long end = System.currentTimeMillis();
        long duration = end - start;
        System.out.println("Result: " + sum);
        System.out.println("Duration: " + duration);
    }
}