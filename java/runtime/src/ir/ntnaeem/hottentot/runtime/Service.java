package ir.ntnaeem.hottentot.runtime;


public interface Service {

    RequestHandler makeRequestHandler();
    int getServiceId();
}
