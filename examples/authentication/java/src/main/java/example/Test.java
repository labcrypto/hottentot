package example;

import example.runtime.Response;
import example.runtime.Argument;
import example.runtime.Request;

import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.List;

import static java.lang.Math.pow;


public class Test {

    private static byte[] getByteArrayFromIntegerDataLength(int dataLength) {
        byte[] byteArray;
        if (dataLength >= 0x80) {
            if (dataLength <= 0xff) {
                //ex 0x81 0xff
                byteArray = new byte[2];
                byteArray[0] = (byte) 0x81;
                byteArray[1] = (byte) dataLength;
            } else if (dataLength <= 0xffff) {
                //ex 0x82 0xff 0xff
                byteArray = new byte[3];
                byteArray[0] = (byte) 0x82;
                byte[] byteBuffer = ByteBuffer.allocate(2).putInt(dataLength).array();
                byteArray[1] = byteBuffer[0];
                byteArray[2] = byteBuffer[1];
            } else if (dataLength <= 0xffffff) {
                //ex 0x83 0xff 0xff 0xff
                byteArray = new byte[4];
                byteArray[0] = (byte) 0x83;
                byte[] byteBuffer = ByteBuffer.allocate(3).putInt(dataLength).array();
                byteArray[1] = byteBuffer[0];
                byteArray[2] = byteBuffer[1];
                byteArray[3] = byteBuffer[2];
            } else {
                //ex 0x84 0xff 0xff 0xff 0xff
                byteArray = new byte[5];
                byteArray[0] = (byte) 0x84;
                byte[] byteBuffer = ByteBuffer.allocate(4).putInt(dataLength).array();
                byteArray[1] = byteBuffer[0];
                byteArray[2] = byteBuffer[1];
                byteArray[3] = byteBuffer[2];
                byteArray[4] = byteBuffer[3];
            }
        } else {
            //ex 0x7f
            byteArray = new byte[1];
            byteArray[0] = (byte) dataLength;
        }
        return byteArray;
    }

    public byte[] serializeRequest(Request request) {
        //TODO test this function
        int counter = 0;
        byte[] serializedRequest = new byte[request.getLength()];
        byte[] byteArrayFromSerializedRequestLength = getByteArrayFromIntegerDataLength(request.getLength());
        for (byte b : byteArrayFromSerializedRequestLength) {
            serializedRequest[counter++] = b;
        }
        serializedRequest[counter++] = request.getServiceId();
        serializedRequest[counter++] = request.getMethodId();
        if (request.getType().equals(Request.RequestType.Unknown)) {
            serializedRequest[counter++] = 1;
        } else if (request.getType().equals(Request.RequestType.InvokeStatefull)) {
            serializedRequest[counter++] = 2;
        } else if (request.getType().equals(Request.RequestType.InvokeStateless)) {
            serializedRequest[counter++] = 3;
        } else if (request.getType().equals(Request.RequestType.ServiceListQuery)) {
            serializedRequest[counter++] = 4;
        }
        List<Argument> args = request.getArgs();
        for (Argument arg : args) {
            byte[] byteArrayFromArgLength = getByteArrayFromIntegerDataLength(arg.getDataLength());
            for (byte b : byteArrayFromArgLength) {
                serializedRequest[counter++] = b;
            }
            for (byte b : arg.getData()) {
                serializedRequest[counter++] = b;
            }
        }
        return serializedRequest;
    }

    public Request deserializeRequest(byte[] serializedRequest) {
        //TODO
        int counter = 0;
        Request request = new Request();
        byte firstByte = serializedRequest[0];
        if (((int) firstByte & 0x80) == 0) {
            request.setLength(serializedRequest[0]);
            counter++;
        } else {
            int numOfByteForLength = (int) firstByte & 0x0f;
            int requestLength = 0;
            for (int i = numOfByteForLength; i > 0; i--) {
                counter++;
                requestLength += (int) pow(256, (numOfByteForLength - 1)) * serializedRequest[i];
            }
            request.setLength(requestLength);
        }
        request.setServiceId(serializedRequest[counter++]);
        request.setMethodId(serializedRequest[counter++]);
        if (serializedRequest[counter] == 1) {
            request.setType(Request.RequestType.Unknown);
        } else if (serializedRequest[counter] == 2) {
            request.setType(Request.RequestType.InvokeStatefull);
        } else if (serializedRequest[counter] == 3) {
            request.setType(Request.RequestType.InvokeStateless);
        } else if (serializedRequest[counter] == 4) {
            request.setType(Request.RequestType.ServiceListQuery);
        }
        counter++;
        request.setArgumentCount(serializedRequest[counter++]);
        //make arguments
        while (counter < serializedRequest.length) {
            Argument arg = new Argument();
            firstByte = serializedRequest[counter];
            if (((int) firstByte & 0x80) == 0) {
                int dataLength = serializedRequest[counter];
                arg.setDataLength(serializedRequest[counter]);
                counter++;
                //fill data
                byte[] data = new byte[dataLength];
                for (int i = 0; i < dataLength; i++) {
                    data[i] = serializedRequest[counter++];
                }
                arg.setData(data);
            } else {
                int numOfByteForLength = (int) firstByte & 0x0f;
                int dataLength = 0;
                counter++;
                for (int i = numOfByteForLength; i > 0; i--) {
                    counter++;
                    dataLength += (int) pow(256, (numOfByteForLength - 1)) * serializedRequest[i];
                }
                arg.setDataLength(dataLength);
                //fill data
                byte[] data = new byte[dataLength];
                for (int i = 0; i < dataLength; i++) {

                    data[i] = serializedRequest[counter++];
                }
                arg.setData(data);
            }
            request.addArgument(arg);
        }
        return request;
    }


    public Response deserializeResponse(byte[] serializedResponse) {
        //tested :)
        int counter = 0;
        Response response = new Response();
        byte firstByte = serializedResponse[0];
        if (((int) firstByte & 0x80) == 0) {
            response.setLength(serializedResponse[0]);
            counter++;
        } else {
            int numOfByteForLength = (int) firstByte & 0x0f;
            int responseLength = 0;
            for (int i = numOfByteForLength; i > 0; i--) {
                counter++;
                responseLength += (int) pow(256, (numOfByteForLength - 1)) * serializedResponse[i];
            }
            response.setLength(responseLength);
        }
        byte[] data = new byte[response.getLength() - 1 ];

        response.setStatusCode(serializedResponse[counter++]);

        for(int i = 0 ; counter < serializedResponse.length ; i++){

            data[i] = serializedResponse[counter++];
        }
        response.setData(data);
        return response;

    }


    public static byte[] serializeResponse(Response response) {
        //tested ! :)
        int counter = 0;
        byte[] serializedResponse = new byte[response.getLength()];
        byte[] byteArrayFromSerializedResponseLength = getByteArrayFromIntegerDataLength(response.getLength());
        for (byte b : byteArrayFromSerializedResponseLength) {
            serializedResponse[counter++] = b;
        }
        serializedResponse[counter++] = response.getStatusCode();
        for (byte b : response.getData()) {
            serializedResponse[counter++] = b;
        }
        return serializedResponse;
    }


    public static void main(String[] args) {

        //test serializeRequest

//        Request request = new Request();
//        request.setLength(255);
//        request.setServiceId((byte) 1);
//        request.setMethodId((byte) 1);
//        request.setType(Request.RequestType.InvokeStateless);
//        request.setArgumentCount((byte) 1);
//        Argument arg = new Argument();
//        arg.setDataLength(2);
//        arg.setData(new byte[]{97, 98});
//        request.addArgument(arg);
//
//        byte[] bytes = new Test().serializeRequest(request);
//        System.out.println(Arrays.toString(bytes));

        //test deserialize request

//        byte[] serializedRequest = new byte[]{ 7 , 1, 1, 1,2, 2, 97, 98 , 1 , 100};
//        Request request1 = new Test().deserializeRequest(serializedRequest);
//        System.out.println(request1.toString());
//        System.out.println(request1.getArgs().get(1).getDataLength());
//        System.out.println(Arrays.toString(request1.getArgs().get(1).getData()));

        //testing deserialized response

//        byte[] serializedResponse = new byte[]{8, 2 , 1, 2, 3, 4, 5, 6,7};
//        System.out.println(Arrays.toString(serializedResponse));
//        Response response = new Test().deserializeResponse(serializedResponse);
//        System.out.println(response.toString());
//        System.out.println(Arrays.toString(response.getData()));

        //testing serializing response
        Response response1 = new Response();
        response1.setLength(5);
        response1.setStatusCode((byte)0);
        response1.setData(new byte[]{97, 98, 99});
        System.out.println(Arrays.toString(serializeResponse(response1)));
    }
}
