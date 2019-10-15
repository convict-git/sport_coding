import java.io.*;
import java.util.*;

public class Main {
   public static void main(String[] args) {
      InputStream inputStream = System.in;
      OutputStream outputStream = System.out;
      Task solver = new Task();
      int tc = System.in.nextInt();
      for (int t = 1; t <= tc; ++t) {
         solver.solve(t, inputStream, outputStream);
      }
      out.close();
   }

   static class Task {
      public void solve(int testNumber, InputStream in, OutputStream out) {
         int n = in.nextInt();
         long k = in.nextLong();
         int [] A = in.nextInts(n);
         int t = (n % 2 == 0 ? 2 : 3);
         out.println(t);
      }
   }
}

