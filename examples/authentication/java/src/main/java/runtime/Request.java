package runtime;


import java.util.ArrayList;
import java.util.List;

public class Request {

    public static enum RequestType{
        Unknown,
        ServiceListQuery,
        InvokeStateless,
        InvokeStateful
    }


    private RequestType type;
    private byte methodId;
    private byte serviceId;
    private byte argumentCount;
    private List<Argument> args = new ArrayList<Argument>();

    public RequestType getType() {
        return type;
    }

    public void setType(RequestType type) {
        this.type = type;
    }

    public byte getMethodId() {
        return methodId;
    }

    public void setMethodId(byte methodId) {
        this.methodId = methodId;
    }

    public byte getServiceId() {
        return serviceId;
    }

    public void setServiceId(byte serviceId) {
        this.serviceId = serviceId;
    }

    public byte getArgumentCount() {
        return argumentCount;
    }

    public void setArgumentCount(byte argumentCount) {
        this.argumentCount = argumentCount;
    }

    public void addArgument(Argument arg){
        args.add(arg);
    }

    public List<Argument> getArgs() {
        return args;
    }
}
