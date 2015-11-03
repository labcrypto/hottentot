package runtime;



public interface Protocol {
    byte[] serializeRequest(Request request);
    Request deserializeRequest(byte[] request);
    byte[] serializeResponse(Response response);
    void processDataForRequest(byte[] dataChunk);
    void processDataForResponse(byte[] dataChunk);
    void setRequestCallBack(RequestCallBack requestCallBack);
    boolean IsResponseComplete();
    Response getResponse();
    void setResponseCallback(ResponseCallback responseCallback);
}
