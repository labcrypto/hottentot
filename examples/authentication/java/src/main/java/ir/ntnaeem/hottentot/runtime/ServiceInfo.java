package ir.ntnaeem.hottentot.runtime;


public class ServiceInfo {

    public String host;
    public int port;
    public Service service;
    public int id;

    public ServiceInfo(String host, int port, Service service , int serviceId) {
        this.host = host;
        this.port = port;
        this.service = service;
        this.id = serviceId;
    }
}
