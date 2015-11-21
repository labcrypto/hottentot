package example.runtime;


public interface Service {

    RequestHandler makeRequestHandler();
    int getServiceId();
}
