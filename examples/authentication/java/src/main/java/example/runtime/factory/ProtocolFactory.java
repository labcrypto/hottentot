package example.runtime.factory;


import example.runtime.protocol.Protocol;
import example.runtime.protocol.ProtocolV1;

public class ProtocolFactory {
    public static Protocol create(){

        Protocol protocol = new ProtocolV1();
       return protocol;
    }
}
