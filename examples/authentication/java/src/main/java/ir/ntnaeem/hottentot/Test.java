package ir.ntnaeem.hottentot;

import ir.ntnaeem.hottentot.runtime.Argument;
import ir.ntnaeem.hottentot.runtime.Request;

import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.List;


public class Test {

    private byte[] getByteArrayFromIntegerDataLength(int dataLength) {
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
        } else if (request.getType().equals(Request.RequestType.InvokeStateful)) {
            serializedRequest[counter++] = 2;
        } else if (request.getType().equals(Request.RequestType.InvokeStateless)) {
            serializedRequest[counter++] = 3;
        } else if (request.getType().equals(Request.RequestType.ServiceListQuery)) {
            serializedRequest[counter++] = 4;
        }
        List<Argument> args = request.getArgs();
        for (Argument arg : args) {
            byte[] byteArrayFromArgLength = getByteArrayFromIntegerDataLength(arg.getDataLength());
            for(byte b : byteArrayFromArgLength){
                serializedRequest[counter++] = b;
            }
            for(byte b : arg.getData()){
                serializedRequest[counter++] = b;
            }
        }
        return serializedRequest;
    }

    public static void main(String[] args) {
        Request request = new Request();
        request.setLength(255);
        request.setServiceId((byte) 1);
        request.setMethodId((byte) 1);
        request.setType(Request.RequestType.InvokeStateless);
        request.setArgumentCount((byte) 1);
        Argument arg = new Argument();
        arg.setDataLength(2);
        arg.setData(new byte[]{97, 98});
        request.addArgument(arg);

        byte[] bytes = new Test().serializeRequest(request);
        System.out.println(Arrays.toString(bytes));

    }
}
