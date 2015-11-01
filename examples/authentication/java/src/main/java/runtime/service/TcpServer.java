package runtime.service;


import runtime.Protocol;

import java.util.List;

public interface TcpServer {

    void bindAndStart();
    void setProtocol(Protocol protocol);

}
