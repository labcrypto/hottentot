package ir.naeem.hottentot.generated;

public class Token {
	private string value;
	public void setValue(string value) {
		this.value = value;
	}
	public string getValue() {
		return value;
	}
	
	public byte[] serialize() {
		//TODO(ali)
		//fake implementation
		return new byte[]{ 97 };
	}
	public void deserialize(byte[] serializedToken) {
		//TODO(ali)
		//fake implementation
		setValue("test-token");
	}
}
