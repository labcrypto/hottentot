package example.generated;

public class Credential {
	private String username;
	private String password;
	public void setUsername(String username) {
		this.username = username;
	}
	public String getUsername() {
		return username;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	public String getPassword() {
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
		setUsername("test-token");
		setPassword("test-token");
	}
}
