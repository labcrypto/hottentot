package naeem.hottentot.examples.auth.hotgen.server;

import naeem.hottentot.examples.auth.hotgen.*;

class AuthenticateImpl extends AbstractAuthenticateService {
    @Override
    public Token authenticate(Credential credential) {
        return null;
    }

    @Override
    public String f() {
        String str = "";
        for(int i = 0 ; i < 100000 ; i++){
            str += "a";
        }
        return str;
    }

    @Override
    public int g() {
        return 1;
    }

    @Override
    public byte[] h() {
        byte[] bytes = new byte[100000];
        for(int i = 0 ; i < 100000 ; i++){
            bytes[i] = 1;
        }
        return bytes;
    }
    //implementation
}