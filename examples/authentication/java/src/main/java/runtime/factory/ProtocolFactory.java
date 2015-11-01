package runtime.factory;


import runtime.Protocol;
import runtime.ProtocolV1;

public class ProtocolFactory {
    public static Protocol create(){
        return new ProtocolV1();
    }
}
