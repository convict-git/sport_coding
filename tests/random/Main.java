import java.io.*;
import java.util.*;

public class Main {
   public static void main(String[] args) {
      /*{{{*/ InputStream inputStream = System.in;
      OutputStream outputStream = System.out;
      InputReader in = new InputReader(inputStream);
      OutputWriter out = new OutputWriter(outputStream); /*}}}*/
      Task solver = new Task();
      int tc = in.nextInt();
      for (int t = 1; t <= tc; ++t) {
         solver.solve(t, in, out);
      }
      out.close();
   }

   static class Task {
      public void solve(int testNumber, InputReader in, OutputWriter out) {
         int N = in.nextInt(), M = in.nextInt();

         if (M < N) {
            out.println(-1);
            return;
         }

         ArrayList <ArrayList <Integer>> div =
            new ArrayList <ArrayList <Integer>> (M - N + 2);

         for (int i = N; i <= M; ++i) {
            div.add(new ArrayList <Integer> ());
         }

         for (int i = 2; i <= M; ++i) {
            for (int j = 0; j <= M; j += i) {
               if (j >= N) {
                  div.get(j - N).add(i);
               }
            }
         }

         Integer[] dp = new Integer[M - N + 2];
         Arrays.fill(dp, Integer.MAX_VALUE);

         dp[0] = 0;

         for (int i = N; i <= M; ++i) {
            for (int j = 0; j < div.get(i - N).size(); ++j) {
               Integer x = div.get(i - N).get(j);
               if (x != i &&
                     x % 2 == 0 &&
                     i + x - N <= M - N &&
                     dp[i - N] != Integer.MAX_VALUE)
               {
                  dp[i + x - N] = Math.min(dp[i + x - N], dp[i - N] + (i / x));
               }
            }
         }

         Integer res = dp[M - N];

         if (res == Integer.MAX_VALUE) {
            out.println(-1);
         }
         else {
            out.println(res);
         }
         return;
      }
   }

   /*{{{*/
   static class InputReader {
      public final BufferedReader reader;
      public StringTokenizer tokenizer = null;

      public InputReader(Reader reader) {
         this.reader = new BufferedReader(reader, 32767);
      }

      public InputReader(InputStream inputStream) {
         this(new InputStreamReader(inputStream));
      }

      public String next() {
         if (hasNext()) return tokenizer.nextToken();
         else throw new NoSuchElementException();
      }

      public int nextInt() {
         return Integer.parseInt(next());
      }

      public int[] nextInts(int n) {
         int[] res = new int[n];
         for (int i = 0; i < n; i++) res[i] = nextInt();
         return res;
      }

      public boolean hasNext() {
         while (tokenizer == null || !tokenizer.hasMoreTokens()) {
            try {
               String nextLine = reader.readLine();
               if (nextLine == null) return false;
               tokenizer = new StringTokenizer(nextLine);
            } catch (IOException e) {
               throw new RuntimeException(e);
            }
         }
         return tokenizer.hasMoreTokens();
      }

   }

   static class OutputWriter {
      private final PrintWriter writer;

      private OutputWriter(Writer writer, boolean autoFlush) {
         this.writer = new PrintWriter(new BufferedWriter(writer, 32767), autoFlush);
      }

      public OutputWriter(Writer writer) {
         this(writer, true);
      }

      public OutputWriter(OutputStream outputStream) {
         this(new OutputStreamWriter(outputStream), false);
      }

      public OutputWriter println() {
         writer.println();
         return this;
      }

      public OutputWriter println(int value) {
         writer.println(value);
         return this;
      }

      public OutputWriter print(Object object) {
         writer.print(object);
         return this;
      }

      public void close() {
         writer.close();
      }
   }
   /*}}}*/

}

