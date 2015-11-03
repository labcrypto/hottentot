package runtime;



public abstract class RequestHandler {


    protected Service service;
    public RequestHandler(Service service) {
        this.service = service;
    }
    abstract public Response handleRequest(Request request);
}
