package runtime;


import runtime.exception.TcpClientConnectException;
import runtime.exception.TcpClientReadException;
import runtime.exception.TcpClientWriteException;
import sun.awt.SunToolkit;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class DefaultTcpClient implements TcpClient  {

    private Socket socket;
    private final int BUFFER_SIZE = 10;
    public void connect(String host, int port) throws TcpClientConnectException {
        //TODO
        try {
            System.out.println(port);
            socket = new Socket( host , port);
        } catch (IOException e) {
            throw new TcpClientConnectException(e);
        }
    }



    public void write(byte[] data) throws TcpClientWriteException {
        OutputStream os = null;
        try {
            os = socket.getOutputStream();
            os.write(data , 0 , data.length);
        } catch (IOException e) {
            throw new TcpClientWriteException(e);
        }
    }

    public byte[] read() throws TcpClientReadException {
        //TODO
        InputStream is = null;
        byte[] buffer = new byte[256];
        try {
            //*****

            //*****
            is = socket.getInputStream();
            System.out.println(is);
            byte b = (byte)is.read();
            buffer[0] = b;
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
