package multipleProducersMultipleConsumers;

import java.util.ArrayList;

public class Buffer {
    int maxSize = 100;
    int current = 0;
    ArrayList<Integer> list = new ArrayList<>(maxSize);

    synchronized void put(int value) {
        while (current == maxSize) {
            try {
                wait();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        ++current;
        list.add(value);
        notifyAll();
    }

    synchronized int get() {
        while (current == 0) {
            try {
                wait();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        --current;
        int x = list.get(0);
        list.remove(0);
        notifyAll();
        return x;
    }
}