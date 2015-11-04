package ir.ntnaeem.hottentot.runtime.factory;


import ir.ntnaeem.hottentot.runtime.Protocol;
import ir.ntnaeem.hottentot.runtime.ProtocolV1;

public class ProtocolFactory {
    public static Protocol create(){

        Protocol protocol = new ProtocolV1();
       return protocol;
    }
}
