import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.concurrent.CyclicBarrier;

public class Main {
    // vectorul principal
    public static ArrayList<Integer> arr;

    // nr treaduri
    public static int P;

    // dimensiunea vectorului
    public static int N = 20;

    public static CyclicBarrier barrier;

    // numarul de elemente sterse (pentru sublist)
    public static int deletedElemsCounter = 0;

    // suma finala
    public static int sum = 0;
    public static void main(String[] args) {
        P = Runtime.getRuntime().availableProcessors();
        arr = new ArrayList<>();
        barrier = new CyclicBarrier(P);

        // creez vectorul
        for (int i = 1; i <= N; i++) {
            arr.add(i);
        }

        // creez si pornesc treadurile
        Thread[] threads = new Thread[P];
        for (int i = 0; i < P; i++) {
            threads[i] = new Thread(new MyThread(i));
            threads[i].start();
        }

        // opresc treadurile
        for (int i = 0; i < P; i++) {
            try {
                threads[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println(arr);
        System.out.println("Sum: " + sum);
    }
}
