import java.util.concurrent.TimeUnit;

public class Volatile {
    static volatile boolean running = true;

    public static void main(String[] args) throws InterruptedException {
        Thread runner = new Thread(() -> {
            while (running) {

            }
            System.out.println("Runner done");
        });
        runner.start();
        TimeUnit.SECONDS.sleep(1);
        running = false;
        System.out.println("Running is false.");
    }
}
