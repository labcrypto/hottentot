package example.runtime;


public class Argument {

    //data length can be 1byte or 3 byte
    private int dataLength;
    private byte[] data;


    public int getDataLength() {
        return dataLength;
    }

    public void setDataLength(int dataLength) {
        this.dataLength = dataLength;
    }

    public byte[] getData() {
        return data;
    }

    public void setData(byte[] data) {
        this.data = data;
    }

    public Argument() {
        this.dataLength = dataLength;
        this.data = data;
    }
}
