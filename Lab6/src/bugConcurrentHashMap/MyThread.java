package bugConcurrentHashMap;

import java.util.concurrent.ConcurrentHashMap;

public class MyThread implements Runnable {
    static ConcurrentHashMap<Integer, Integer> hashMap;
    private final int id;

    MyThread(int id) {
        this.id = id;
    }

	/*
	void addValue(int key, int value) {
		if(hashMap.containsKey(key))
			hashMap.put(key, hashMap.get(key) + value);
		else
			hashMap.put(key, value);
	}
	*/

    void addValue(int key, int value) {

        Integer pair = hashMap.putIfAbsent(key, value);

        if(pair != null) {
            hashMap.put(key, pair + value);
        }
    }

    @Override
    public void run() {
        if (id == 0) {
            for (int i = 0; i < Main.N; i++) {
                addValue(i, 2*i);
            }
        } else {
            for (int i = 0; i < Main.N; i++) {
                addValue(i, 3*i);
            }
        }
    }
}