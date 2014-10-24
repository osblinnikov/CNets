package com.github.airutech.cnets.runnablesContainer;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;

class Kernel extends Thread{
  private RunnableStoppable objectToRun;
  private Boolean isSeparateThread = false;
  private AtomicBoolean isRunning = new AtomicBoolean(false);
  private AtomicBoolean stopFlag = new AtomicBoolean(false);
  public void launch(RunnableStoppable objectToRun, boolean lockLaunch){
    stopFlag.set(false);
    if(!isRunning.getAndSet(true)){
      this.objectToRun = objectToRun;
      objectToRun.onStart();
      if(lockLaunch){
        isSeparateThread = false;
        this.run();
      }else{
        isSeparateThread = true;
        this.start();
      }
    }
  }

  public void stopThread(){
    stopFlag.set(true);
    if(isSeparateThread) {
      this.interrupt();
    }
    while(isRunning.get()){
      stopFlag.set(true);/*make sure that nobody will start the kernel before we finish the waiting*/
      try{Thread.sleep(1);}catch(InterruptedException e){e.printStackTrace();}
    }
    try {
      if (isSeparateThread) {
        this.join();
      }
    } catch (InterruptedException e) {
      e.printStackTrace();
    }
    objectToRun.onStop();
  }

  @Override
  public void run(){
    while(!stopFlag.get()){
        try{
            objectToRun.run();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
    isRunning.set(false);
  }

}