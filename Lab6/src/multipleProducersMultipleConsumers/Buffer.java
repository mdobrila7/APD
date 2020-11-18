package multipleProducersMultipleConsumers;

import java.util.concurrent.ArrayBlockingQueue;

public class Buffer {
    private static final int CAPACITY = 5;
    private ArrayBlockingQueue<Integer> v;

    Buffer() {
        v = new ArrayBlockingQueue<Integer>(CAPACITY, true);
    }

    void put(int value) {
        try {
            v.put(value);
        }
        catch(InterruptedException e) {
            e.printStackTrace();
        }
    }

    int get() {
        int value = -1;

        try {
            value = v.take();
        }
        catch(InterruptedException e) {
            e.printStackTrace();
        }

        return value;
    }
}
