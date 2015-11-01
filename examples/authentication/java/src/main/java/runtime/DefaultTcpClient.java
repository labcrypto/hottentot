package runtime;


import runtime.exception.TcpClientConnectException;
import runtime.exception.TcpClientReadException;
import runtime.exception.TcpClientWriteException;

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
            socket = new Socket( host , port);
        } catch (IOException e) {
            throw new TcpClientConnectException(e);
        }
    }



    public void write(byte[] data) throws TcpClientWriteException {
        OutputStream os = null;
        try {
            os = socket.getOutputStream();
            byte[] buffer = new byte[BUFFER_SIZE];
            int bufferCounter = 0;
            //TODO use buffer byte array to write
            for(byte b : data){
                os.write(b);
            }
        } catch (IOException e) {
            throw new TcpClientWriteException(e);
        }finally {
            try {
                os.close();
            } catch (IOException e) {}
        }
    }

    public byte[] read() throws TcpClientReadException {
        //TODO
        InputStream is = null;
        byte[] readData = null;


        try {
            is = socket.getInputStream();
            System.out.println(is);
            int responseLength = is.read();
            readData = new byte[responseLength];
            //TODO(ali) replace buffered read
            int b;
            int counter =0;
            while( (b = is.read()) != -1){
                readData[counter++] = (byte) b;
            }

            if(readData.length != responseLength){
                //TODO(ali) throw suitable exception
            }
            is.close();
        } catch (IOException e) {
            e.printStackTrace();
            throw new TcpClientReadException();

        }finally {
            try {
                is.close();
            } catch (Exception e) {
            }
        }
        return readData;
    }

    public void close() {
        //TODO
    }
}
