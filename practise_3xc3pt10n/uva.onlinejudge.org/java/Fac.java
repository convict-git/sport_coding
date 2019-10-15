import java.util.Scanner;
import java.math.BigInteger;

class Main {
  public static void main (String [] args) {
	 Scanner sc = new Scanner(System.in);
	 BigInteger x = sc.nextBigInteger();
	 BigInteger y = sc.nextBigInteger();

	 BigInteger ans = BigInteger.ZERO;
	 ans = ans.add(x);
	 ans = ans.add(y);
	 System.out.println (ans);
  }
}
