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

package ir.ntnaeem.hottentot.runtime;


import java.util.ArrayList;
import java.util.List;

public class Request {

  public static enum RequestType {
    Unknown,
    ServiceListQuery,
    InvokeStateless,
    InvokeStatefull
  }


  private RequestType type;
  private long methodId;
  private long serviceId;
  private byte argumentCount;
  private int length;


  public int getLength() {
    return length;
  }

  public void setLength(int length) {
    this.length = length;
  }

  private List<Argument> args = new ArrayList<Argument>();

  public RequestType getType() {
    return type;
  }

  public void setType(RequestType type) {
    this.type = type;
  }

  public long getMethodId() {
    return methodId;
  }

  public void setMethodId(long methodId) {
    this.methodId = methodId;
  }

  public long getServiceId() {
    return serviceId;
  }

  public void setServiceId(long serviceId) {
    this.serviceId = serviceId;
  }

  public byte getArgumentCount() {
    return argumentCount;
  }

  public void setArgumentCount(byte argumentCount) {
    this.argumentCount = argumentCount;
  }

  public void addArgument(Argument arg) {
    args.add(arg);
  }

  public List<Argument> getArgs() {
    return args;
  }

  @Override
  public String toString() {
    return "Request{" +
            "type=" + type +
            ", methodId=" + methodId +
            ", serviceId=" + serviceId +
            ", argumentCount=" + argumentCount +
            ", length=" + length +
            ", args=" + args +
            '}';
  }

}
