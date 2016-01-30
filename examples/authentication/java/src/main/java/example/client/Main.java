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

import javax.xml.crypto.Data;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {
  public static void main(String[] args) throws InterruptedException {
    final AuthenticationService proxy = AuthenticationServiceProxyBuilder.create("127.0.0.1", 8080);
//    List<StringWrapper> stringWrapperList = new ArrayList<StringWrapper>();
//    StringWrapper stringWrapper = new StringWrapper();
//    String str = "";
//    for(int i = 0 ; i < 1000 ; i++) {
//      str += "a";
//    }
//    stringWrapper.setValue(str);
//    //
//    StringWrapper stringWrapper2 = new StringWrapper();
//    String str2 = "";
//    for(int i = 0 ; i < 10000 ; i++) {
//      str2 += "a";
//    }
//    stringWrapper2.setValue(str2);
//    //
//    stringWrapperList.add(stringWrapper);
//    stringWrapperList.add(stringWrapper2);
//    DataWrapper dataWrapper = proxy.test5(stringWrapperList);
//    System.out.println(" res : " + Arrays.toString(dataWrapper.getDigi()));
//    Result result = proxy.test7();
//    System.out.println("status 8 : " + result.getStatus8());
//    System.out.println("status 16 : " + result.getStatus16());
//    System.out.println("status 32 : " + result.getStatus32());
//    System.out.println("status 64 : " + result.getStatus64());
////    //
//    System.out.println("ustatus 8 : " + result.getUstatus8());
//    System.out.println("ustatus 16 : " + result.getUstatus16());
//    System.out.println("ustatus 32 : " + result.getUstatus32());
//    System.out.println("ustatus 64 : " + result.getUstatus64());
//
//    //
    Credential credential = new Credential();
    credential.setUsername("a");
    String pass = "";
    for(int i = 0 ; i < 1000 ; i++){
      pass += "a";
    }
    credential.setPassword("a");
    List<Token> tokenList = proxy.auth(credential);
    System.out.println("token id : " + tokenList.get(0).getId());
//    //
//    List<DataWrapper> wrapperList = proxy.test();
//    System.out.println(" 0 size : " + wrapperList.get(0).getDigi().length);
//    System.out.println(" 0 digi : " + Arrays.toString(wrapperList.get(0).getDigi()));
//    System.out.println(" 0 value  : " + wrapperList.get(0).getValue());
//    System.out.println(" 1 size : " + wrapperList.get(1).getDigi().length);
//    System.out.println(" 1 value : " + wrapperList.get(1).getValue());
////    //
//    List<StringWrapper> stringWrapperList2 = proxy.test2();
//    System.out.println("TEST2 stringWrapperList2 size : " + stringWrapperList2.size());
//    System.out.println("TEST2 stringWrapperList2 : " + stringWrapperList2);
//////    //
//    StringWrapper stringWrapper3 = proxy.test3();
//    System.out.println("TEST 3 stringWrapper size : " + stringWrapper3.getValue().length());
////    //
//    DataWrapper dataWrapper4 = proxy.test4();
//    System.out.println("TEST4 dataWrapper size : " + dataWrapper4.getDigi().length);
//    System.out.println("TEST4 dataWrapper size : " + Arrays.toString(dataWrapper4.getDigi()));

//    List<DataWrapper> dataWrapperList = new ArrayList<DataWrapper>();
//    DataWrapper dr = new DataWrapper();
//    dr.setDigi(new byte[]{1});
//    dataWrapperList.add(dr);
//    DataWrapper dataWrapper1 = proxy.test6(dataWrapperList);
//    System.out.println("TEST6 : " + dataWrapper1);
    //
    AuthenticationServiceProxyBuilder.destroy();
  }
}
