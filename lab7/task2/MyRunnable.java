package task2;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.atomic.AtomicInteger;

public class MyRunnable implements Runnable {
    int[] colors;
    ExecutorService tpe;
    AtomicInteger inQueue;
    private final int step;

   public MyRunnable( int[] myColors, ExecutorService tpe, AtomicInteger inQueue, int myStep) {
        this.colors = myColors;
        this.tpe = tpe;
        this.inQueue = inQueue;
        this.step = myStep;
    }

    @Override
    public void run() {
        if (step == MyMain.N) {
            MyMain.printColors(colors);
            int left = inQueue.decrementAndGet();
            if (left == 0) {
                tpe.shutdown();
            }
            return;
        }
        // for the node at position step try all possible colors
        for (int i = 0; i < MyMain.COLORS; i++) {
            int[] newColors = colors.clone();
            newColors[step] = i;
            if (MyMain.verifyColors(newColors, step)) {
                inQueue.incrementAndGet();
                tpe.submit(new MyRunnable(newColors, tpe, inQueue,  step + 1));
            }
        }
        int left = inQueue.decrementAndGet();
        if (left == 0) {
            tpe.shutdown();
        }
    }
}