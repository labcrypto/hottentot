package ir.ntnaeem.hottentot.runtime;


import java.util.Arrays;

public class Response {
    private byte statusCode;
    private byte[] data;
    private int responseLength;

    public int getResponseLength() {
        return responseLength;
    }

    public void setResponseLength(int responseLength) {
        this.responseLength = responseLength;
    }

    public byte getStatusCode() {
        return statusCode;
    }

    public void setStatusCode(byte statusCode) {
        this.statusCode = statusCode;
    }

    public byte[] getData() {
        return data;
    }

    public void setData(byte[] data) {
        this.data = data;
    }

    @Override
    public String toString() {
        return "Response{" +
                "statusCode=" + statusCode +
                ", data=" + Arrays.toString(data) +
                ", responseLength=" + responseLength +
                '}';
    }
}
