package example.runtime;


import java.io.IOException;

public interface TcpServer{
    void bindAndStart() throws IOException;
}
