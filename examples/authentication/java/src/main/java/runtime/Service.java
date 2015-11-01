package runtime;


import runtime.RequestHandler;

public interface Service {

    RequestHandler makeRequestHandler();
    int getServiceId();
}
