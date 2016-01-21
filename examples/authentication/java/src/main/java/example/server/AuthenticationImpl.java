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
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTAB_STRILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

package example.server;


import example.generated.*;

import java.util.ArrayList;
import java.util.List;

public class AuthenticationImpl extends AbstractAuthenticationService {

  public List<Token> auth(Credential credential) {
    return null;
  }

  public List<DataWrapper> test() {
    return null;
  }

  public List<StringWrapper> test2() {
    StringWrapper stringWrapper = new StringWrapper();
    String str = "";
    for(int i = 0; i < 1000 ; i++){
      str += i;
    }
    stringWrapper.setValue(str);

    List<StringWrapper> stringWrapperList = new ArrayList<StringWrapper>();
    stringWrapperList.add(stringWrapper);
    return stringWrapperList;
  }

  public StringWrapper test3() {
    StringWrapper stringWrapper = new StringWrapper();
    String str = "";
    for(int i = 0; i < 1000 ; i++){
      str += i;
    }
    stringWrapper.setValue(str);
    return stringWrapper;
  }

  public DataWrapper test4() {
    DataWrapper dataWrapper = new DataWrapper();
    byte[] data = new byte[100000];
    for(int i = 0 ; i < 100000 ; i++){
      data[i] = (byte)i;
    }
    dataWrapper.setDigi(data);
    return dataWrapper;
  }
}
