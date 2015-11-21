package example.runtime.protocol;
import example.runtime.RequestCallback;
import example.runtime.Response;
import example.runtime.ResponseCallback;
import example.runtime.Request;

public interface Protocol {
    byte[] serializeRequest(Request request);
    Request deserializeRequestBody(byte[] serializedRequestBody);
    Response deserializeResponseBody(byte[] serializedResponseBody);
    byte[] serializeResponse(Response response);
    void processDataForRequest(byte[] dataChunk);
    void processDataForResponse(byte[] dataChunk);
    void setRequestCallback(RequestCallback requestCallback);
    boolean IsResponseComplete();
    Response getResponse();
    void setResponseCallback(ResponseCallback responseCallback);
}
