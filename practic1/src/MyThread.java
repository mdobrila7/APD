import java.util.ArrayList;
import java.util.concurrent.BrokenBarrierException;

public class MyThread implements Runnable {
    int id;

    public MyThread(int id) {
        this.id = id;
    }

    @Override
    public void run() {
        // iau start si end initiale
        int start = (int) (id * (double) Main.N / Main.P);
        int end = Math.min((int) ((id + 1) * (double) Main.N / Main.P), Main.N);

        // sterg elementele impare, adaug valoarea 0, la sfarsitul vectorului la fiecare stergere
        // pentru a nu modifica lungimea vectorului la operatia asta (ar trebui sa recalculez
        // start si end la fiecare stergere si ar fi costisitor)
        for (int i = start; i < end; i++) {
            if (Main.arr.get(i) % 2 == 1) {
                synchronized (Main.arr) {
                    Main.arr.remove(i);
                    Main.arr.add(0);
                    Main.deletedElemsCounter++;
                }
            }
        }
        // astept toate treadurile
        try {
            Main.barrier.await();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (BrokenBarrierException e) {
            e.printStackTrace();
        }
        // in treadul 0 pastrez doar elementele pe care nu le am sters (adica renunt la 0 urile de la final)
        if (id == 0) {
            Main.arr = new ArrayList(Main.arr.subList(0, Main.N - Main.deletedElemsCounter));
            Main.N = Main.arr.size();
        }
        // astept sa se termine din nou executia pe treadul 0
        try {
            Main.barrier.await();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } catch (BrokenBarrierException e) {
            e.printStackTrace();
        }
        // updatez start si end pt fiecare tread
        start = (int) (id * (double) Main.N / Main.P);
        end = Math.min((int) ((id + 1) * (double) Main.N / Main.P), Main.N);
        // calculez suma
        for (int i = start; i < end; i++) {
            Main.sum += Main.arr.get(i);
        }
    }
}
