package shortestPathsFloyd_Warshall;
/**
 * @author cristian.chilipirea
 *
 */
import java.util.*;

class MyThread extends Thread{
    private int thread_id;
    private int start;
    private int end;
    int[][] graph2;

    public MyThread(int i, int N, int P, int[][] graph3){
        thread_id = i;
        start = (int) Math.ceil((float) N / P * thread_id);
        end = (int) Math.min(Math.ceil((float)N/P * (thread_id + 1)), N);
        graph2 = graph3;
    }

    public void run() {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                graph2[i][j] = Math.min(graph2[i][thread_id] + graph2[thread_id][j], graph2[i][j]);
            }
        }
    }
}

public class Main {
    public static int M = 9;
    public static int graph[][] = { { 0, 1, M, M, M },
            { 1, 0, 1, M, M },
            { M, 1, 0, 1, 1 },
            { M, M, 1, 0, M },
            { M, M, 1, M, 0 } };


    public static void main(String[] args) {

        // Parallelize me (You might want to keep the original code in order to compare)
//        for (int k = 0; k < 5; k++) {
//            for (int i = 0; i < 5; i++) {
//                for (int j = 0; j < 5; j++) {
//                    graph[i][j] = Math.min(graph[i][k] + graph[k][j], graph[i][j]);
//                }
//            }
//        }

        List<MyThread> list = new LinkedList<MyThread>();

        for (int i = 0; i < 5; i++) {
            list.add(new MyThread(i, 5, 5, graph));
        }

        for (int i = 0; i < 5; i++) {
            list.get(i).start();
        }

        for (int i = 0; i < 5; i++) {
            try {
                list.get(i).join();
            } catch(Exception ex) {}
        }

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                System.out.print(graph[i][j] + " ");
            }
            System.out.println();
        }
    }
}
