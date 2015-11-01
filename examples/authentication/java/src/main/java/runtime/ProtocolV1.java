package runtime;


public class ProtocolV1 implements Protocol {

    private RequestCallBack requestCallBack;
    private ResponseCallBack responseCallBack;
    public byte[] serializeRequest(Request request) {
        //TODO maybe some section consist more than one byte !
        int serializedRequestLength = 4;
        for(Argument arg : request.getArgs()){
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
        return new byte[0];
    }

    public Response deserializeResponse(byte[] serializedResponse) {
        //TODO done
        Response response = new Response();
        response.setStatusCode(serializedResponse[0]);
        byte[] responseBody = new byte[serializedResponse.length -1 ];
        for(int i = 1; i < serializedResponse.length ; i++ ){
            responseBody[i - 1] = serializedResponse[i];
        }
        response.setResponseBody(responseBody);
        return response;
    }



    public void processDataForRequest(byte[] dataChunk) {
        //some process until the entire request completely read
        //make a request object from byte array read
        Request request = new Request();
        request.setType(Request.RequestType.InvokeStateful);
        request.setServiceId((byte)1);
        request.setMethodId((byte)1);
        request.setArgumentCount((byte)1);
        byte[] arg1 = new byte[]{ 97 , 98 };
        request.addArgument(new Argument(2,arg1));
        System.out.println(request);
        requestCallBack.onRequest(request);
    }

    public void processDataForResponse(byte[] dataChunk) {

    }

    public void setRequestCallBack(RequestCallBack requestCallBack) {
        this.requestCallBack = requestCallBack;
    }

    public void setResponseCallBack(ResponseCallBack requestCallBack) {
        this.responseCallBack = responseCallBack;
    }
}
