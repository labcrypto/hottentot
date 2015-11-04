package ir.ntnaeem.hottentot.runtime.protocol;


import ir.ntnaeem.hottentot.generated.Argument;
import ir.ntnaeem.hottentot.runtime.Request;
import ir.ntnaeem.hottentot.runtime.RequestCallback;
import ir.ntnaeem.hottentot.runtime.Response;
import ir.ntnaeem.hottentot.runtime.ResponseCallback;

import java.io.IOException;
import java.util.Arrays;
import java.util.List;

import static java.lang.Math.pow;


public class ProtocolV1 implements Protocol {


    private RequestProcessor requestProcessor;
    private ResponseProcessor responseProcessor;
    public ProtocolV1() {
        requestProcessor = new RequestProcessor();
        responseProcessor = new ResponseProcessor();
    }

    public class RequestProcessor{

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

        public void process(byte[] dataChunk ) {
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
                } else if (currentState == 2 ) {
                    if (dStateCounter < dataLength - 1) {
                        data[dStateCounter++] = b;
                    } else {
                        data[dStateCounter] = b;
                        //TODO use logger
                        System.out.println("request has been read ... ");
                        System.out.println(Arrays.toString(data));
                        //
                        Response response = requestCallback.onRequest(deserializeRequest(data));
                        try {
                            responseCallback.onResponse(serializeResponse(response));
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
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
                    } else{
                        currentState = 2;
                        data[dStateCounter++] = b;
                    }
                }
            }
        }
    }

    public class ResponseProcessor{

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

        public void process(byte[] dataChunk ) {
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
                } else if (currentState == 2 ) {
                    if (dStateCounter < dataLength - 1) {
                        data[dStateCounter++] = b;
                    } else {
                        data[dStateCounter] = b;
                        //TODO use logger
                        System.out.println("request has been read ... ");
                        System.out.println(Arrays.toString(data));
                        //
                        response = deserializeResponse(data);
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
                    } else{
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
        //TODO
        return null;
    }
    public Response deserializeResponse(byte[] response){
        //TODO
        return null;
    }

    public byte[] serializeResponse(Response response) {

        return new byte[]{97};
    }


    public void setResponseCallback(ResponseCallback responseCallback){
        this.responseCallback = responseCallback;
    }

    public void processDataForRequest(byte[] dataChunk) {
        requestProcessor.process(dataChunk);
    }

    public void processDataForResponse(byte[] dataChunk) {
        responseProcessor.process(dataChunk);
    }

    public boolean IsResponseComplete() {
        return isResponseComplete;
    }

    public Response getResponse() {
        //TODO
        return response;
    }

    public void setRequestCallback(RequestCallback requestCallback) {
        this.requestCallback = requestCallback;
    }




}
