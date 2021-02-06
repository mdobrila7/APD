package task3;

import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.atomic.AtomicInteger;

public class MyRunnable implements Runnable {
    int[] graph;
    ExecutorService tpe;
    AtomicInteger inQueue;
    private final int step;

    public MyRunnable(int[] mygraph, ExecutorService tpe, AtomicInteger inQueue, int myStep) {
        this.graph = mygraph;
        this.tpe = tpe;
        this.inQueue = inQueue;
        this.step = myStep;
    }

    @Override
    public void run() {
        if (MyMain.N == step) {
            MyMain.printQueens(graph);
            int left = inQueue.decrementAndGet();
            if (left == 0) {
                tpe.shutdown();
            }
            return;
        }
        for (int i = 0; i < MyMain.N; ++i) {
            int[] newGraph = graph.clone();
            newGraph[step] = i;

            if (MyMain.check(newGraph, step)) {
                inQueue.incrementAndGet();
                tpe.submit(new MyRunnable(newGraph, tpe, inQueue, step+1));
            }
        }
        int left = inQueue.decrementAndGet();
        if (left == 0) {
           tpe.shutdown();
        }
    }
}