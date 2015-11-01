package runtime.service;


import runtime.RequestHandler;

public interface Service {

    RequestHandler getRequestHandler();
    int getServiceId();
}
