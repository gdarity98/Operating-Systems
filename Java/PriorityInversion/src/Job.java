public class Job {
    private int priority;
    private int timeToRun;
    private int timeRun;
    private String bufferToPrint;
    private String name;
    private int callTime;
    private int originalCallTime;
    private boolean finished = false;
    private boolean running = false;


    public Job(int n, int t){
        String TN = String.valueOf(n);
        callTime = t;
        originalCallTime = t;
        if(TN.equals("1")){
            priority = 3;
            timeToRun = 3;
            timeRun = 3;
            bufferToPrint = "1";
            name = "T1";

        }else if (TN.equals("2")){
            priority = 2;
            timeToRun = 10;
            timeRun = 10;
            bufferToPrint = "N";
            name = "T2";
        }else{
            priority = 1;
            timeToRun = 3;
            timeRun = 3;
            bufferToPrint = "3";
            name = "T3";
        }
    }

    public int getCallTime() {
        return callTime;
    }

    public int getPriority() {
        return priority;
    }

    public int getTimeToRun() {
        return timeToRun;
    }

    public String getBufferToPrint() {
        return bufferToPrint;
    }

    public String getName() {
        return name;
    }

    public boolean isFinished() {
        return finished;
    }

    public void setFinished(boolean finished) {
        this.finished = finished;
    }

    public boolean isRunning() {
        return running;
    }

    public void setRunning(boolean running) {
        this.running = running;
    }

    public void setCallTime(int callTime) {
        this.callTime = callTime;
    }

    public int getOriginalCallTime() {
        return originalCallTime;
    }

    public void setTimeRun(int timeRun) {
        this.timeRun = timeRun;
    }

    public int getTimeRun() {
        return timeRun;
    }
}
