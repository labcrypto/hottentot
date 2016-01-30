package client;

import java.util.Arrays;

public class Test {
  public static void main(String[] args) {
    int[] arr1 = new int[] {1 ,2 , 3};
    int[] arr2 = new int[] {4 ,5 , 6};
    System.arraycopy(arr2,1,arr1,1,2);
    System.out.println(Arrays.toString(arr1));
  }
}
