package task1;

import java.io.File;
import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.atomic.AtomicInteger;

public class MyRunnable implements Runnable {
    ArrayList<Integer> path;
    ExecutorService tpe;
    AtomicInteger inQueue;
    private final int dest;
    public MyRunnable(ArrayList<Integer> partialPath, ExecutorService tpe, AtomicInteger inQueue, int destination) {
        this.path = partialPath;
        this.tpe = tpe;
        this.inQueue = inQueue;
        this.dest = destination;
    }

    @Override
    public void run() {
        if (path.get(path.size() - 1) == dest) {
            System.out.println(path);
        }
        int lastNodeInPath = path.get(path.size() - 1);
        for (int[] ints : MyMain.graph) {
            if (ints[0] == lastNodeInPath) {
                if (path.contains(ints[1]))
                    continue;
                ArrayList<Integer> newPartialPath = new ArrayList<>(path);
                newPartialPath.add(ints[1]);
                inQueue.incrementAndGet();
                tpe.submit(new MyRunnable(newPartialPath, tpe, inQueue, dest));
            }
        }
        int left = inQueue.decrementAndGet();
        if (left == 0) {
            tpe.shutdown();
        }
    }
}