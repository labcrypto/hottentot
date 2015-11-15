package ir.naeem.hottentot.generated;

public class Credential {
	private string username;
	private string password;
	public void setUsername(string username) {
		this.username = username;
	}
	public string getUsername() {
		return username;
	}
	public void setPassword(string password) {
		this.password = password;
	}
	public string getPassword() {
		return password;
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
