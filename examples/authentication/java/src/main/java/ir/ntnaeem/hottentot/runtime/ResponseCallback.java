package ir.ntnaeem.hottentot.runtime;


import ir.ntnaeem.hottentot.runtime.exception.TcpServerReadException;

import java.io.IOException;

public interface ResponseCallback {

    void onResponse(byte[] serializedResponse) throws TcpServerReadException;
}
