package task6;



import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.RecursiveTask;

public class MyTask extends RecursiveTask<Void> {
    int[] graph;
    private final int step;

    public MyTask(int[] myGraphs, int myStep) {
        this.graph = myGraphs;
        this.step = myStep;
    }

    @Override
    protected Void compute() {
        if (MyMain.N == step) {
            MyMain.printQueens(graph);
            return null;
        }
        List<MyTask> tasks = new ArrayList<>();
        for (int i = 0; i < Main.N; ++i) {
            int[] newGraph = graph.clone();
            newGraph[step] = i;

            if (MyMain.check(newGraph, step)) {
                MyTask t = new MyTask(newGraph, step + 1);
                tasks.add(t);
                t.fork();
            }

        }
        for (MyTask task : tasks) {
            task.join();
        }
        return null;
    }
}