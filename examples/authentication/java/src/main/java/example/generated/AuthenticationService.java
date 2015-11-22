package example.generated;

import ir.ntnaeem.hottentot.runtime.Service;

public interface AuthenticationService extends Service {
    Token authenticate(Credential credential);
}
