package ir.ntnaeem.hottentot.runtime.protocol;

import ir.ntnaeem.hottentot.runtime.Request;
import ir.ntnaeem.hottentot.runtime.RequestCallback;
import ir.ntnaeem.hottentot.runtime.Response;
import ir.ntnaeem.hottentot.runtime.ResponseCallback;
import ir.ntnaeem.hottentot.runtime.exception.ProtocolProcessException;

public interface Protocol {
    byte[] serializeRequest(Request request);
    Request deserializeRequestBody(byte[] serializedRequestBody);
    Response deserializeResponseBody(byte[] serializedResponseBody);
    byte[] serializeResponse(Response response);
    void processDataForRequest(byte[] dataChunk) throws ProtocolProcessException;
    void processDataForResponse(byte[] dataChunk);
    void setRequestCallback(RequestCallback requestCallback);
    boolean IsResponseComplete();
    Response getResponse();
    void setResponseCallback(ResponseCallback responseCallback);
}
