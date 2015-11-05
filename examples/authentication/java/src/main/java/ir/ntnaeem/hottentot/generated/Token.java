package ir.ntnaeem.hottentot.generated;


public class Token {

    private String value;

    public void setValue(String value){
        this.value = value;
    }
    public String getValue(){
        return value;
    }

    public byte[] serialize(){
        //TODO(ali)
        return new byte[]{ 97 };
    }
    public void deserialize(byte[] serializedToken){
        //TODO(ali)
        setValue("test-token");
    }
}
