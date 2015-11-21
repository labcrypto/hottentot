package example.runtime;


import java.util.Arrays;

public class Response {
    private byte statusCode;
    private byte[] data;

    private int length;


    public int getLength() {
        return length;
    }


    public void setLength(int length) {
        this.length = length;
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
                ", length=" + length +
                '}';
    }
}
