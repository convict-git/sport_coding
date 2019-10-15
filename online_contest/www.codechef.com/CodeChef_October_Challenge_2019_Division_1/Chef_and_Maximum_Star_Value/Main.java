import java.io.*;
import java.util.*;

public class Main {
   public static void main(String[] args) {
      InputStream inputStream = System.in;
      OutputStream outputStream = System.out;
      InputReader in = new InputReader(inputStream);
      OutputWriter out = new OutputWriter(outputStream);
      Task solver = new Task();
      int tc = in.nextInt();
      for (int t = 1; t <= tc; ++t) {
         solver.solve(t, in, out);
      }
      out.close();
   }

   static class Task {

      static final int MAXN = 1000*1000;
      public void solve(int testNumber, InputReader in, OutputWriter out) {
         int n = in.nextInt();
         int [] A = in.nextInts(n);
         int N = 0;
         for (int i = 0; i < n; ++i) {
            N = Math.max(N, A[i]);
         }
         // out.println(N);
         int [] idx = new int [N + 1];
         Arrays.fill(idx, -1);
         for (int i = 0; i < n; ++i) {
            idx[A[i]] = Math.max(idx[A[i]], i);
         }

         int [] dp = new int [N + 1];
         for (int i = 1; i <= N; ++i) {
            dp[i] = i;
         }

         for (int i = 1; i <= N; ++i) {
            if (idx[i] == -1) continue;
            for (int j = i; j <= N; j += i) {
               if (idx[j] == -1) continue;
               if (idx[i] >= idx[j]) dp[j] = Math.min(i, dp[j]);
            }
         }
         // long calc = 0;
         Set <Integer> set = new HashSet <Integer>();
         for (int i = 1; i <= N; ++i) {
            if (dp[i] >= i) continue;
            if (idx[i] != -1) {
               // int sz = set.size();
               set.add(dp[i]);
               // if (sz < set.size()) calc += idx[i];
            }
         }
         // out.print(calc);
         // out.println(set.size());
         int answer = 0;
         for (int i : set) {
            int cur_cnt = 0;
            for (int j = 0; j < idx[i]; ++j){
               if (A[j] % i == 0) ++cur_cnt;
            }
            answer = Math.max(answer, cur_cnt);
         }
         out.println(answer);
      }
   }

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
}

