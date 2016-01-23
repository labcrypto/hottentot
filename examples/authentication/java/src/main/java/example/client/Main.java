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

import example.generated.*;

import java.util.Arrays;
import java.util.List;

public class Main {
  public static void main(String[] args) throws InterruptedException {
    final AuthenticationService proxy = AuthenticationServiceProxyBuilder.create("127.0.0.1", 8080);
    List<DataWrapper> wrapperList = proxy.test();
    System.out.println("size : " + wrapperList.get(0).getDigi().length);
    System.out.println("size : " + Arrays.toString(wrapperList.get(0).getDigi()));
    System.out.println("size : " + wrapperList.get(1).getDigi().length);
//    //
//    List<StringWrapper> stringWrapperList = proxy.test2();
//    System.out.println(" stringWrapperList size : " + stringWrapperList.get(0).getValue().length());
////    //
//    StringWrapper stringWrapper = proxy.test3();
//    System.out.println("stringWrapper size : " + stringWrapper.getValue().length());
////    //
//    DataWrapper dataWrapper = proxy.test4();
//    System.out.println("dataWrapper size : " + dataWrapper.getDigi().length);
    //
//    List<DataWrapper> dataWrapperList = new ArrayList<DataWrapper>();
//    dataWrapperList.add(new DataWrapper());
//    DataWrapper dataWrapper1 = proxy.test6(dataWrapperList);
//    System.out.println(Arrays.toString(dataWrapper1.getDigi()));
    //
    AuthenticationServiceProxyBuilder.destroy();
  }
}
