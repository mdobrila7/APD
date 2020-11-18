package ex1;

public class NoCores extends Thread{
    private int threadNo;
    NoCores(int no) {
        this.threadNo = no;
    }
    public void run() {
        System.out.println("Hello World from thread " + threadNo);
    }
    public static void main(String[] args) {

        int threadsNo = 4;
        for (int i = 0; i < threadsNo; i++) {
            (new NoCores(i)).start();
        }
    }
}