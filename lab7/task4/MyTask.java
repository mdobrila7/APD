package task4;


import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.RecursiveTask;

public class MyTask extends RecursiveTask<Void> {
    ArrayList<Integer> path;
    private final int dest;

    public MyTask(ArrayList<Integer> myPath, int destination) {
        this.path = myPath;
        this.dest = destination;
    }

    @Override
    protected Void compute() {
        if (path.get(path.size() - 1) == dest) {
            System.out.println(path);
            return null;
        }
        int lastNodeInPath = path.get(path.size() - 1);
        List<MyTask> tasks = new ArrayList<>();
        for (int[] ints : MyMain.graph) {
            if (ints[0] == lastNodeInPath) {
                if (path.contains(ints[1]))
                    continue;
                ArrayList<Integer> newPartialPath = new ArrayList<>(path);
                newPartialPath.add(ints[1]);
                MyTask t = new MyTask(newPartialPath, dest);
                tasks.add(t);
                t.fork();
            }
        }
        for (MyTask task: tasks) {
            task.join();
        }
        return null;
    }
}
