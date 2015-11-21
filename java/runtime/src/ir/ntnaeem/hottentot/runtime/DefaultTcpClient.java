package ir.ntnaeem.hottentot.runtime;

import ir.ntnaeem.hottentot.runtime.exception.TcpClientConnectException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientReadException;
import ir.ntnaeem.hottentot.runtime.exception.TcpClientWriteException;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Arrays;

public class DefaultTcpClient implements TcpClient {

    private Socket socket;
    private final int BUFFER_SIZE = 10;

    public void connect(String host, int port) throws TcpClientConnectException {
        //TODO
        try {
            socket = new Socket(host, port);
        } catch (IOException e) {
            throw new TcpClientConnectException(e);
        }
    }


    public void write(byte[] data) throws TcpClientWriteException {
        OutputStream os = null;
        try {
            os = socket.getOutputStream();
            os.write(data, 0, data.length);
        } catch (IOException e) {
            throw new TcpClientWriteException(e);
        }
    }

    public byte[] read() throws TcpClientReadException {
        //TODO
        InputStream is = null;
        byte[] buffer = new byte[256];
        try {
            is = socket.getInputStream();
            int numReadBytes = is.read(buffer, 0, buffer.length);
            if(numReadBytes < 256){
                byte[] readBytes = Arrays.copyOf(buffer, numReadBytes);
                return readBytes;
            }
            //byte b = (byte)is.read();
            //buffer[0] = b;
            return buffer;
        } catch (IOException e) {
            e.printStackTrace();
            throw new TcpClientReadException();
        }
    }

    public void close() {
        //TODO
    }
}
