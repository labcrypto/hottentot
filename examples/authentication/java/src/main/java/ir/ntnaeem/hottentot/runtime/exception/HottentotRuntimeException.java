package ir.ntnaeem.hottentot.runtime.exception;

public class HottentotRuntimeException  extends RuntimeException{
    public HottentotRuntimeException(Throwable cause) {
        super(cause);
    }
    public HottentotRuntimeException() {
    }
    public HottentotRuntimeException(String message) {
        super(message);
    }
}
