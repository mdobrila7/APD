package oneProducerOneConsumer;

import java.util.concurrent.Semaphore;

public class Buffer {
    int a;
    Semaphore s1 = new Semaphore(1);
    Semaphore s2 = new Semaphore(0);

    void put(int value)
    {
        try
        {
            s1.acquire();
        }
        catch (Exception e) {}

        a = value;
        s2.release();
    }

    int get()
    {
        try
        {
            s2.acquire();
        }
        catch (Exception e) {}

        int b = a;
        s1.release();
        return b;
    }
}