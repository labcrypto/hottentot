package runtime;


import runtime.service.ResponseCallBack;
import runtime.service.ServiceInfo;

public interface Protocol {
    byte[] serializeRequest(Request request);
    Request deserializeRequest(byte[] request);
    byte[] serializeResponse(Response response);
    Response deserializeResponse(byte[] serializedRequest);
    void processDataForRequest(byte[] dataChunk);
    void processDataForResponse(byte[] dataChunk);
    void setRequestCallBack(RequestCallBack requestCallBack);
    void setResponseCallBack(ResponseCallBack requestCallBack);
}
