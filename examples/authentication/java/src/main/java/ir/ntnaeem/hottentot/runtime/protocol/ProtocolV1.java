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

package ir.ntnaeem.hottentot.runtime.protocol;

import ir.ntnaeem.hottentot.runtime.*;
import ir.ntnaeem.hottentot.runtime.config.Config;
import ir.ntnaeem.hottentot.runtime.exception.*;
import ir.ntnaeem.hottentot.serializerHelper.ByteArrayToInteger;
import ir.ntnaeem.hottentot.serializerHelper.DataLengthByteArrayMaker;
import java.lang.reflect.Array;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.List;

import static java.lang.Math.pow;

public class ProtocolV1 implements Protocol {

  public class RequestProcessor {
    private short currentState = 0;
    private int lStateCounter = 0;
    private int dStateCounter = 0;
    private int lStateLength = 0;
    private int dataLength;
    private byte[] data;

    public void resetStates() {
      currentState = 0;
      lStateCounter = 0;
      dStateCounter = 0;
      lStateLength = 0;
      dataLength = 0;
    }

    public void process(byte[] dataChunk) throws ProtocolProcessException {
      for (byte b : dataChunk) {
        if (currentState == 0) {
          if ((b & 0x80) == 0) {
            dataLength = b;
            data = new byte[dataLength];
            currentState = 2;
          } else {
            lStateLength = b & 0x0f;
            currentState = 1;
          }
        } else if (currentState == 2) {
          if (dStateCounter < dataLength - 1) {
            data[dStateCounter++] = b;
          } else {
            data[dStateCounter] = b;
            //TODO use logger
            //System.out.println("request has been read ... ");
            //System.out.println("request data : " +Arrays.toString(data));
            //
            Response response = null;
            try {
              response = requestCallback.onRequest(deserializeRequestBody(data));
            } catch (TcpClientReadException e) {
              throw new ProtocolProcessException(e);
            } catch (TcpClientConnectException e) {
              throw new ProtocolProcessException(e);
            } catch (TcpClientWriteException e) {
              throw new ProtocolProcessException(e);
            } catch (MethodNotSupportException e) {
              throw new ProtocolProcessException(e);
            }
            try {
              responseCallback.onResponse(serializeResponse(response));
            } catch (TcpServerReadException e) {
              throw new ProtocolProcessException(e);
            }
            isRequestComplete = true;
            //reset states
            resetStates();
          }
        } else if (currentState == 1) {
          if (lStateCounter < lStateLength) {
            if (b < 0) {
              dataLength += pow(256, (lStateLength - lStateCounter - 1)) * (b + 256);
            } else {
              dataLength += pow(256, (lStateLength - lStateCounter - 1)) * b;
            }
            lStateCounter++;
          } else {
            data = new byte[dataLength];
            currentState = 2;
            data[dStateCounter++] = b;
          }
        }
      }
    }
  }

  public class ResponseProcessor {

    private short currentState = 0;
    private int lStateCounter = 0;
    private int dStateCounter = 0;
    private int lStateLength = 0;
    private int dataLength;
    private byte[] data;

    public void resetStates() {
      currentState = 0;
      lStateCounter = 0;
      dStateCounter = 0;
      lStateLength = 0;
      dataLength = 0;
    }

    public void process(byte[] dataChunk) {
      for (byte b : dataChunk) {
        if (currentState == 0) {
          if ((b & 0x80) == 0) {
            dataLength = b;
            data = new byte[dataLength];
            currentState = 2;
          } else {
            lStateLength = b & 0x0f;
            currentState = 1;
          }
        } else if (currentState == 2) {
          if (dStateCounter < dataLength - 1) {
            data[dStateCounter++] = b;
          } else {
            data[dStateCounter] = b;
            //TODO use logger
            response = deserializeResponseBody(data);
            isResponseComplete = true;
            //reset states
            resetStates();
          }
        } else if (currentState == 1) {
          if (lStateCounter < lStateLength) {
            if (b < 0) {
              dataLength += pow(256, (lStateLength - lStateCounter - 1)) * (b + 256);
            } else {
              dataLength += pow(256, (lStateLength - lStateCounter - 1)) * b;
            }
            lStateCounter++;
          } else {
            data = new byte[dataLength];
            currentState = 2;
            data[dStateCounter++] = b;
          }
        }
      }
    }
  }

  private RequestCallback requestCallback;
  private ResponseCallback responseCallback;
  private Response response;
  private boolean isResponseComplete = false;
  private boolean isRequestComplete = false;

  private RequestProcessor requestProcessor;
  private ResponseProcessor responseProcessor;

  public ProtocolV1() {
    requestProcessor = new RequestProcessor();
    responseProcessor = new ResponseProcessor();
  }


//  private byte[] getByteArrayFromIntegerDataLength(int dataLength) {
//    byte[] byteArray;
//    if (dataLength >= 0x80) {
//      if (dataLength <= 0xff) {
//        //ex 0x81 0xff
//        byteArray = new byte[2];
//        byteArray[0] = (byte) 0x81;
//        byteArray[1] = (byte) dataLength;
//      } else if (dataLength <= 0xffff) {
//        //ex 0x82 0xff 0xff
//        byteArray = new byte[3];
//        byteArray[0] = (byte) 0x82;
//
//        byte[] byteBuffer = ByteBuffer.allocate(2).putShort((short) dataLength).array();
//        byteArray[1] = byteBuffer[0];
//        byteArray[2] = byteBuffer[1];
//      } else if (dataLength <= 0xffffff) {
//        //ex 0x83 0xff 0xff 0xff
//        byteArray = new byte[5];
//        byteArray[0] = (byte) 0x84;
//        byte[] byteBuffer = ByteBuffer.allocate(4).putInt(dataLength).array();
//        byteArray[1] = byteBuffer[0];
//        byteArray[2] = byteBuffer[1];
//        byteArray[3] = byteBuffer[2];
//      } else {
//        //ex 0x84 0xff 0xff 0xff 0xff
//        byteArray = new byte[5];
//        byteArray[0] = (byte) 0x84;
//        byte[] byteBuffer = ByteBuffer.allocate(4).putInt(dataLength).array();
//        byteArray[1] = byteBuffer[0];
//        byteArray[2] = byteBuffer[1];
//        byteArray[3] = byteBuffer[2];
//        byteArray[4] = byteBuffer[3];
//      }
//    } else {
//      //ex 0x7f
//      byteArray = new byte[1];
//      byteArray[0] = (byte) dataLength;
//    }
//    return byteArray;
//  }

  public byte[] serializeRequest(Request request) {
    //tested ! :)
    if(Config.isVerboseMode){
      System.out.println("REQUEST : \n" + request);
    }
    int counter = 0;
    byte[] byteArrayFromSerializedRequestLength = DataLengthByteArrayMaker.getByteArray(request.getLength());
    byte[] serializedRequest = new byte[request.getLength() + byteArrayFromSerializedRequestLength.length];
    //req length
    for (byte b : byteArrayFromSerializedRequestLength) {
      serializedRequest[counter++] = b;
    }
    //req type
    if (request.getType().equals(Request.RequestType.Unknown)) {
      serializedRequest[counter++] = 1;
    } else if (request.getType().equals(Request.RequestType.InvokeStatefull)) {
      serializedRequest[counter++] = 2;
    } else if (request.getType().equals(Request.RequestType.InvokeStateless)) {
      serializedRequest[counter++] = 3;
    } else if (request.getType().equals(Request.RequestType.ServiceListQuery)) {
      serializedRequest[counter++] = 4;
    }

    byte[] serviceIdByteArray = ByteBuffer.allocate(Long.SIZE / Byte.SIZE).putLong(request.getServiceId()).array();
    byte[] methodIdByteArray = ByteBuffer.allocate(Long.SIZE / Byte.SIZE).putLong(request.getMethodId()).array();
    System.arraycopy(serviceIdByteArray, 4, serializedRequest, counter, 4);
    counter += 4;
    System.arraycopy(methodIdByteArray, 4, serializedRequest, counter, 4);
    counter += 4;
    //serializedRequest[counter++] = request.getServiceId();
    //serializedRequest[counter++] = request.getMethodId();



    serializedRequest[counter++] = request.getArgumentCount();
    List<Argument> args = request.getArgs();

    for (Argument arg : args) {
      byte[] byteArrayFromArgLength = DataLengthByteArrayMaker.getByteArray(arg.getDataLength());
      for (byte b : byteArrayFromArgLength) {
        serializedRequest[counter++] = b;
      }
      for (byte b : arg.getData()) {
        serializedRequest[counter++] = b;
      }
    }
    if(Config.isVerboseMode) {
      System.out.println("SERIALIZED REQUEST : \n" + bytesToHex(serializedRequest));
    }
    return serializedRequest;
  }

  private static char[] hexArray = "0123456789ABCDEF".toCharArray();
  private static String bytesToHex(byte[] bytes) {
    char[] hexChars = new char[bytes.length * 2];
    for ( int j = 0; j < bytes.length; j++ ) {
      int v = bytes[j] & 0xFF;
      hexChars[j * 2] = hexArray[v >>> 4];
      hexChars[j * 2 + 1] = hexArray[v & 0x0F];
    }
    return new String(hexChars);
  }

  public Request deserializeRequestBody(byte[] serializedRequestBody) {
    //tested :)
    if(Config.isVerboseMode){
      System.out.println("SERIALIZED REQ BODY : \n" + bytesToHex(serializedRequestBody));
    }
    int counter = 0;
    Request request = new Request();
    request.setLength(serializedRequestBody.length);
    //req type
    if (serializedRequestBody[counter] == 1) {
      request.setType(Request.RequestType.Unknown);
    } else if (serializedRequestBody[counter] == 2) {
      request.setType(Request.RequestType.InvokeStatefull);
    } else if (serializedRequestBody[counter] == 3) {
      request.setType(Request.RequestType.InvokeStateless);
    } else if (serializedRequestBody[counter] == 4) {
      request.setType(Request.RequestType.ServiceListQuery);
    }
    counter++;
    //
    byte[] serviceIdByteArray = new byte[8];
    serviceIdByteArray[0]=0;
    serviceIdByteArray[1]=0;
    serviceIdByteArray[2]=0;
    serviceIdByteArray[3]=0;
    for (int i = 4; i < 8; i++) {
      serviceIdByteArray[i] = serializedRequestBody[counter++];
    }
    byte[] methodIdByteArray = new byte[8];
    methodIdByteArray[0] = 0;
    methodIdByteArray[1] = 0;
    methodIdByteArray[2] = 0;
    methodIdByteArray[3] = 0;
    for (int i = 4; i < 8; i++) {
      methodIdByteArray[i] = serializedRequestBody[counter++];
    }
    request.setServiceId(ByteBuffer.wrap(serviceIdByteArray).getLong());
    request.setMethodId(ByteBuffer.wrap(methodIdByteArray).getLong());
//    request.setServiceId(serializedRequestBody[counter++]);
//    request.setMethodId(serializedRequestBody[counter++]);

    request.setArgumentCount(serializedRequestBody[counter++]);
    //make arguments
    while (counter < serializedRequestBody.length) {
      byte firstByteInReqArgsData;
      int argLength;
      firstByteInReqArgsData = serializedRequestBody[counter];
      if (((int) firstByteInReqArgsData & 0x80) == 0) {
        argLength = firstByteInReqArgsData;
        counter++;
      }else{
        int numOfByteForArgsDataLength = (int) firstByteInReqArgsData & 0x0f;
        counter++;
        byte[] reqDataLengthByteArray = new byte[numOfByteForArgsDataLength];
        for(int i = 0 ; i < numOfByteForArgsDataLength ; i++) {
          reqDataLengthByteArray[i] = serializedRequestBody[counter++];
        }
        argLength = ByteArrayToInteger.getInt(reqDataLengthByteArray);
      }
      Argument arg = new Argument();
      byte[] argData = new byte[argLength];
      for(int i = 0 ; i < argLength ; i++){
        argData[i] = serializedRequestBody[counter++];
      }
      arg.setData(argData);
      request.addArgument(arg);
    }
    if(Config.isVerboseMode) {
      System.out.println("REQUEST : \n" + request);
    }
    return request;
  }

  public Response deserializeResponseBody(byte[] serializedResponseBody) {

    //tested :)
    int counter = 0;
    if(Config.isVerboseMode){
      System.out.println("SERIALIZED RESPONSE BODY : \n" + bytesToHex(serializedResponseBody));
    }
    Response response = new Response();
//        byte firstByte = serializedResponse[0];
//        if (((int) firstByte & 0x80) == 0) {
//            response.setLength(serializedResponse[0]);
//            counter++;
//        } else {
//            int numOfByteForLength = (int) firstByte & 0x0f;
//            int responseLength = 0;
//            for (int i = numOfByteForLength; i > 0; i--) {
//                counter++;
//                responseLength += (int) pow(256, (numOfByteForLength - 1)) * serializedResponse[i];
//            }
//            response.setLength(responseLength);
//        }
    response.setStatusCode(serializedResponseBody[counter++]);
    //set response data length
    int dataLength;
    if((serializedResponseBody[counter] & 0x80) == 0){
      dataLength = serializedResponseBody[counter++];
    }else{
      int numOfBytesForDataLength = serializedResponseBody[counter] & 0x0f;
      counter++;
      byte[] dataLengthByteArray = new byte[numOfBytesForDataLength];
      for(int i = 0 ; i < numOfBytesForDataLength ; i++){
        dataLengthByteArray[i] = serializedResponseBody[counter++];
      }
      dataLength = ByteArrayToInteger.getInt(dataLengthByteArray);
    }
    byte[] data = new byte[dataLength];
    for (int i = 0; i < dataLength; i++) {
      data[i] = serializedResponseBody[counter++];
    }
    response.setData(data);
    if(Config.isVerboseMode){
      System.out.println("RESPONSE :\n" + response);
    }
    return response;
  }

  public byte[] serializeResponse(Response response) {
    //tested ! :)
    int counter = 0;
    if(Config.isVerboseMode){
      System.out.println("RESPONSE : \n" + response);
    }
    //
    byte[] data = response.getData();
    int responseDataLength = data.length;
    byte[] responseDataLengthByteArray = DataLengthByteArrayMaker.getByteArray(responseDataLength);
    //1 -- > status code
    int responseLength = 1 + responseDataLengthByteArray.length + response.getData().length;
    byte[] byteArrayFromSerializedResponseLength = DataLengthByteArrayMaker.getByteArray(responseLength);
    byte[] serializedResponse = new byte[byteArrayFromSerializedResponseLength.length + responseLength];
    for (byte b : byteArrayFromSerializedResponseLength) {
      serializedResponse[counter++] = b;
    }
    serializedResponse[counter++] = response.getStatusCode();
    //
    for(byte b : responseDataLengthByteArray){
      serializedResponse[counter++] = b;
    }
    for (byte b : response.getData()) {
      serializedResponse[counter++] = b;
    }
    if(Config.isVerboseMode){
      System.out.println("SERIALIZED RESPONSE : \n" + bytesToHex(serializedResponse));
    }
    return serializedResponse;
  }


  public void setResponseCallback(ResponseCallback responseCallback) {
    this.responseCallback = responseCallback;
  }

  public void processDataForRequest(byte[] dataChunk) throws ProtocolProcessException {
    requestProcessor.process(dataChunk);
  }

  public void processDataForResponse(byte[] dataChunk) {
    responseProcessor.process(dataChunk);
  }

  public boolean isResponseComplete() {
    return isResponseComplete;
  }

  public boolean isRequestComplete() {
    return isRequestComplete;
  }

  public Response getResponse() {
    //TODO
    return response;
  }

  public void setRequestCallback(RequestCallback requestCallback) {
    this.requestCallback = requestCallback;
  }


}
