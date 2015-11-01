package runtime;


public class Response {
    private byte statusCode;
    private byte[] responseBody;
    private byte responseLength;

    public byte getResponseLength() {
        return responseLength;
    }

    public void setResponseLength(byte responseLength) {
        this.responseLength = responseLength;
    }

    public byte getStatusCode() {
        return statusCode;
    }

    public void setStatusCode(byte statusCode) {
        this.statusCode = statusCode;
    }

    public byte[] getResponseBody() {
        return responseBody;
    }

    public void setResponseBody(byte[] responseBody) {
        this.responseBody = responseBody;
    }
}
