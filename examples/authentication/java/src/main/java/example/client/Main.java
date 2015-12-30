/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 Noavaran Tejarat Gostar NAEEM Co.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

package example.client;

import example.generated.AuthenticationService;
import example.generated.AuthenticationServiceProxyBuilder;
import example.generated.Credential;
import example.generated.Token;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {
  public static void main(String[] args) throws InterruptedException {


    final AuthenticationService proxy = AuthenticationServiceProxyBuilder.create("127.0.0.1", 8080);

//    for(int i = 0 ; i < 1000 ; i++){
//      Credential credential = new Credential();
//      credential.setUsername("zoro");
//      credential.setPassword("12345");
//      Token token = proxy.authenticate(credential);
//      System.out.println(token.getValue());
//      System.out.println(Arrays.toString(token.getSampleData()));
//      AuthenticationServiceProxyBuilder.destroy();
//    }

    class MyRunnable implements Runnable{

      private int number;
      public MyRunnable(int number) {
        this.number = number;
      }

      public void run() {
        System.out.println("thread number : " + Thread.currentThread());
        Credential credential = new Credential();
        credential.setUsername("zoro");
        credential.setPassword("12345");
        Token token = proxy.authenticate(credential);
        System.out.println(token.getValue());
        System.out.println(Arrays.toString(token.getSampleData()));
        AuthenticationServiceProxyBuilder.destroy();
      }
    }
    List<Thread> threads = new ArrayList<Thread>();
    for(int i = 1 ; i <= 1000 ; i++) {
      //Thread.sleep(100);
      Runnable runnable = new MyRunnable(i);
      Thread t = new Thread(runnable);
      t.start();
      threads.add(t);
    }

    for(Thread t : threads){
      t.join();
    }
  }
}
