import java.util.Arrays;
import java.util.Queue;
import java.util.Scanner;

public class Priority_Inversion_Assignment {
    public static void main(String args[]){
        System.out.println("Input example: 1,2");
        System.out.print("Input number of job requests:");

        Scanner scanner = new Scanner(System.in);
        while(!scanner.hasNextInt()){
            System.out.println("Input a Valid Integer. Try Again");
            scanner.next();
            System.out.print("Input number of job requests:");
        }
        int length = scanner.nextInt();
        Integer[][] jobRequests = new Integer[length][2];

        System.out.println("Input example:1,2");
        System.out.println("Enter in ascending order");
        System.out.print("Input job request:");
        int count = 0;
        while(scanner.hasNext()){
            String input = scanner.next();
            String[] inputArray = input.split(",");
            jobRequests[count][0] = Integer.parseInt(inputArray[0]);
            jobRequests[count][1] = Integer.parseInt(inputArray[1]);
            count++;
            if(count == length){
                scanner.close();
                System.out.println("");
                break;
            }
            System.out.print("Input job request:");
        }

        Job[] jobs = new Job[length];
        for(int i = 0; i < length; i++){
            jobs[i] = new Job(jobRequests[i][1], jobRequests[i][0]);
        }
        int time = 0;
        boolean active = false;
        boolean done = false;
        while(!done){
            for(Job job : jobs){
                if(job.getCallTime() <= time && !job.isFinished()){
                    job.setRunning(true);
                }
                if(job.getCallTime() == time && !job.isFinished()){
                    for(Job job2 : jobs){
                        if(job2.getCallTime() < time){
                            if(job2.isRunning()){
                                int job2Prio = job2.getPriority();
                                int jobPrio = job.getPriority();
                                if((jobPrio > job2Prio) && (jobPrio != 3 && job2Prio != 1) || (jobPrio != 1 && job2Prio != 3)){
                                    if((job2.getCallTime() + (job2.getTimeToRun()-1)) == time){
                                        job.setRunning(true);
                                        job2.setRunning(false);
                                        job2.setFinished(true);
                                        System.out.print(job2.getBufferToPrint() + " ");
                                        System.out.print(job2.getName() + "\n");
                                    }else{
                                        job.setRunning(true);
                                        job2.setRunning(false);
                                        int timeLeftToRun = time - job2.getCallTime()-1;
                                        job2.setTimeRun(timeLeftToRun);

                                        int newCall = (time + job.getTimeToRun()-1);
                                        job2.setCallTime(newCall);

                                        //job2.setFinished(true);
                                        System.out.print(job2.getBufferToPrint() + " ");
                                        System.out.print(job2.getName() + "\n");
                                    }
                                }else if(jobPrio <= job2Prio && (job.getCallTime() != job2.getCallTime())){
                                    if(job.getCallTime() == time && job2.getTimeRun() == 1){
                                        job.setRunning(true);
                                        job2.setRunning(false);
                                        job2.setFinished(true);
                                        System.out.print(job2.getBufferToPrint() + " ");
                                        System.out.print(job2.getName() + "\n");
                                    }else{
                                        job.setRunning(false);
                                        //job.setCallTime(job.getCallTime()+job2.getTimeToRun()+1);
                                        int newCall = (time + job2.getTimeRun()-1);
                                        job.setCallTime(newCall);
                                        System.out.print("\nCANT INTERRUPT CHANGED JOB ARRIVAL TIME\n");
                                        //job.setFinished(true);
                                    }
                                }
                            }
                        }
                    }
                }

            }

            for(Job job : jobs){
                if(job.isRunning()){
                    if(job.getTimeRun() != 0){
                        if(job.getCallTime() == time){
                            System.out.print("time " + time + ", " + job.getName() + " ");
                        }
                        if((job.getCallTime() + (job.getTimeToRun()-1)) == time){
                            System.out.print(job.getBufferToPrint() + " ");
                            System.out.print(job.getName() + "\n");
                            job.setFinished(true);
                            job.setRunning(false);
                        }else{
                            System.out.print(job.getBufferToPrint() + " ");
                            job.setTimeRun(job.getTimeRun()-1);
                        }
                    }else if(job.getTimeRun() == 0 && job.isFinished()){
                        System.out.print(job.getName() + "\n");
                        job.setTimeRun(1);
                    }
                }
            }

            int numFinished = 0;
            for(Job job : jobs){
                if(job.isFinished()){
                    numFinished++;
                }
            }
            if(numFinished == length){
                done = true;
            }
            time++;
        }
    }
}
