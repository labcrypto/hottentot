package example.runtime;


import java.io.IOException;

public interface ResponseCallback {

    void onResponse(byte[] serializedResponse) throws IOException;
}
