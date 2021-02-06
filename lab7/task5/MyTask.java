package task5;


import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.RecursiveTask;

public class MyTask extends RecursiveTask<Void> {
    int[] colors;
    private final int step;

    public MyTask(int[] myColors, int myStep) {
        this.colors = myColors;
        this.step = myStep;
    }

    @Override
    protected Void compute() {
        if (step == MyMain.N) {
            MyMain.printColors(colors);
            return null;
        }
        List<MyTask> tasks = new ArrayList<>();
        for (int i = 0; i < MyMain.COLORS; i++) {
            int[] newColors = colors.clone();
            newColors[step] = i;
            if (MyMain.verifyColors(newColors, step)) {
                MyTask t = new MyTask(newColors, step + 1);
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