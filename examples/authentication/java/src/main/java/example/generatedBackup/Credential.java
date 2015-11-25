/*  The MIT License (MIT)
 *
 *  Copyright (c) 2015 Noavaran Tejarat Gostar NAEEM Co.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTAB_STRILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 */

package example.generatedBackup;

import ir.ntnaeem.hottentot.serializerHelper.PDTSerializer;

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
        byte[] serializedUsername = PDTSerializer.getString(username);
        byte[] serializedPassword = PDTSerializer.getString(password);
        byte[] output = new byte[serializedUsername.length + serializedPassword.length];
        int counter = 0;
        //use a loop for every property
        for (int i = 0; i < serializedUsername.length; i++) {
            output[counter++] = serializedUsername[i];
        }
        for (int i = 0; i < serializedPassword.length; i++) {
            output[counter++] = serializedPassword[i];
        }
        return output;
    }
    public void deserialize(byte[] serializedToken) {
	//TODO(ali)
	//fake implementation

    }
}
