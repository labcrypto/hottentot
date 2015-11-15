package ir.ntnaeem.hottentot.generatedBackup;


public class Credential {
    private String username;
    private String password;

    public byte[] serialize(){
        //TODO
        return new byte[]{ 99 };
    }

    public void deserialize(byte[] serializedCredential){
        //TODO
        //Credential credential = new Credential();
        setUsername("zoro");
        setPassword("12345");
    }
    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }
}
