package ir.ntnaeem.hottentot.runtime.exception;

/**
 * Created by developer on 11/21/15.
 */
public class TcpServerReadException extends Exception {
    public TcpServerReadException(String message) {
        super(message);
    }

    public TcpServerReadException() {
    }
}
