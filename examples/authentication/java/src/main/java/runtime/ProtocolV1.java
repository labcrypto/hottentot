package runtime;


import generated.Argument;
import runtime.factory.RequestCallbackFactory;

import java.io.IOException;
import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.List;


public class ProtocolV1 implements Protocol {

    private RequestCallBack requestCallBack;
    private ResponseCallback responseCallback;
    private Response response;
    private boolean IsResponseComplete = false;
    public byte[] serializeRequest(Request request) {
        List<Argument> args = request.getArgs();
        Argument arg0 = args.get(0);
        //TODO maybe some section consist more than one byte !
        int serializedRequestLength = 4;
        for(Argument arg : request.getArgs()) {
            serializedRequestLength += arg.getDataLength() + 1;
        }
        byte[] serializedRequest = new byte[serializedRequestLength];
        if(request.getType().equals(Request.RequestType.Unknown)){
            serializedRequest[0] = 0;
        }else if(request.getType().equals(Request.RequestType.InvokeStateful)){
            serializedRequest[0] = 1;
        }else if(request.getType().equals(Request.RequestType.InvokeStateless)){
            serializedRequest[0] = 2;
        }else if(request.getType().equals(Request.RequestType.ServiceListQuery)){
            serializedRequest[0] = 3;
        }
        serializedRequest[1] = request.getMethodId();
        serializedRequest[2] = request.getServiceId();
        serializedRequest[3] = request.getArgumentCount();

        int counter = 4;
        for(Argument argument : request.getArgs()){
            serializedRequest[counter++] = (byte)argument.getDataLength();
            for(byte b : argument.getData()){
                serializedRequest[counter] = b;
            }
        }

        return serializedRequest;
    }

    public Request deserializeRequest(byte[] request) {
        return null;
    }

    public byte[] serializeResponse(Response response) {

        return new byte[]{97};
    }


    public void setResponseCallback(ResponseCallback responseCallback){
        this.responseCallback = responseCallback;
    }

    public void processDataForRequest(byte[] dataChunk) {
        //some process until the entire request completely read
        //make a request object from byte array read
        System.out.println("----"+Arrays.toString(dataChunk));
        Request request = new Request();
        request.setType(Request.RequestType.InvokeStateful);
        request.setServiceId((byte)1);
        request.setMethodId((byte)1);
        request.setArgumentCount((byte)1);
        request.addArgument(new Argument((byte)1 , new byte[]{97}));
        Response response = requestCallBack.onRequest(request);

        try {
            responseCallback.onResponse(serializeResponse(response));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void processDataForResponse(byte[] dataChunk) {
        //TODO
        //fake impl
        response = new Response();
        response.setStatusCode((byte)100);
        response.setResponseLength((byte)2);
        response.setData(new byte[] {97});
        IsResponseComplete = true;
    }

    public boolean IsResponseComplete() {
        //TODO(ali)
        //fake impl
        return IsResponseComplete;
    }

    public Response getResponse() {
        //TODO
        return response;
    }

    public void setRequestCallBack(RequestCallBack requestCallBack) {
        this.requestCallBack = requestCallBack;
    }




}
