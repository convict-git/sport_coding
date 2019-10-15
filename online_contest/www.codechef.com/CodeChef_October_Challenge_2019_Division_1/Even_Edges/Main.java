import java.io.*;
import java.util.*;

public class Main {
   public static void main(String[] args) {
      InputStream inputStream = System.in;
      OutputStream outputStream = System.out;
      InputReader in = new InputReader(inputStream);
      OutputWriter out = new OutputWriter(outputStream);
      Task solver = new Task();
      int t = in.nextInt();
      for (int tc = 1; tc <= t; ++tc) {
         solver.solve(tc, in, out);
      }
      out.close();
   }

   static class Task {
      public void solve(int testNumber, InputReader in, OutputWriter out) {
         int n = in.nextInt();
         int m = in.nextInt();

         int [] deg = new int [n];
         ArrayList <Integer> [] T = new ArrayList [n];

         int u, v;
         for (int i = 0; i < n; ++i) {
            T[i] = new ArrayList <Integer>();
         }
         for (int e = 0; e < m; ++e) {
            u = in.nextInt();
            v = in.nextInt();
            --u; --v;
            ++deg[u];
            ++deg[v];
            T[u].add(v);
            T[v].add(u);
         }

         int [] answer = new int [n];
         Arrays.fill(answer, 1);
         int k = -1;
         if (m % 2 == 0) {
            k = 1;
         }
         else {
            boolean k2 = false;
            for (int i = 0; !k2 && i < n; ++i) {
               if ((deg[i] & 1) != 0) {
                  k2 = true;
                  k = 2;
                  answer[i] = 2;
               }
            }
            if (k2 == false) {
               int even_non_zero_deg = -1;
               for (int i = 0; i < n; ++i) {
                  if (deg[i] >= 1) {
                     even_non_zero_deg = i;
                     answer[i] = 1;
                     for (int vv : T[i]) {
                        --deg[vv];
                     }
                     break;
                  }
               }
               int cnt = 1;
               for (int i = 0; i < n; ++i) {
                  if (i != even_non_zero_deg && (deg[i] % 2 != 0)) {
                     answer[i] = 2;
                     ++cnt;
                     break;
                  }
               }
               for (int i = 0; i < n; ++i) {
                  if (i != even_non_zero_deg && answer[i] != 2) {
                     answer[i] = 3;
                     if (cnt == 2) ++cnt;
                  }
               }
               k = cnt;
            }
         }
         out.println(k);
         for (int i = 0; i < n; ++i) {
            if (i > 0) out.print(" ");
            out.print(answer[i]);
         }
         out.print("\n");
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
