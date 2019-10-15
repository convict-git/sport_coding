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
      static final long X_MAX = (long)1000 * 1000 * 1000 * 1000;
      int m_base (String str) {
         int base = 1;
         for (int i = 0; i < str.length(); ++i) {
            char ch = str.charAt(i);
            if (ch - '0' >= 0 && ch - '0' <= 9)
               base = Math.max(base, ch - '0');
            else base = Math.max(base, ch - 'A' + 10);
         }
         return base + 1;
      }

      long val (String str, int base) {
         long ret = 0;
         long bp = 1;
         for (int i = 0; i < str.length(); ++i) {
            char ch = str.charAt(i);
            if (bp > X_MAX) return -2;
            if (ch - '0' >= 0 && ch - '0' <= 9)
               ret += bp * (ch - '0');
            else ret += bp * (ch - 'A' + 10);
            bp *= base;
            if (ret > X_MAX) return -2;
         }
         return ret;
      }

      boolean check (String str, long v) {
         int low = m_base(str);
         int high = 36;
         while (low <= high) {
            int mid = (low + high)/2;
            long guess = val (str, mid); if (guess == -2) high = mid - 1;
            else if (v == guess) return true;
            else if (v > guess) low = mid + 1;
            else high = mid - 1;
         }
         return false;
      }

      boolean total_check(long v, int start_index, ArrayList <String> Y) {
         for (int i = start_index; i < Y.size(); ++i) {
            if (check(Y.get(i), v) == false)
               return false;
         }
         return true;
      }

      public void solve(int testNumber, InputReader in, OutputWriter out) {
         int n = in.nextInt();
         ArrayList <Integer> B_have = new ArrayList <Integer>();
         ArrayList <String> Y_have = new ArrayList <String>();
         ArrayList <String> Y_not = new ArrayList <String>();

         for (int i = 0; i < n; ++i) {
            int b = in.nextInt();
            String s = in.next();
            s = new StringBuffer(s).reverse().toString();
            if (b == -1) {
               Y_not.add(s);
            }
            else {
               B_have.add(b);
               Y_have.add(s);
            }
         }
         boolean fine = true;
         long true_value = -1;

         if (Y_have.size() >= 1) {
            true_value = val (Y_have.get(0), B_have.get(0));
            if (true_value == -2) fine = false;

            for (int i = 1; fine && i < Y_have.size(); ++i) {
               long is_it = val(Y_have.get(i), B_have.get(i));
               if (is_it == -2 || true_value != is_it) {
                  fine = false;
                  break;
               }
            }
         }
         if (fine) {
            fine = false;
            if (true_value == -1) {
               for (int base = m_base(Y_not.get(0)); base <= 36; ++base) {
                  long current_value = val(Y_not.get(0), base);
                  if (current_value == -2) continue;
                  if (total_check(current_value, 1, Y_not) == true) {
                     true_value = current_value;
                     fine = true;
                     break;
                  }
               }
            }
            else if (total_check(true_value, 0, Y_not)) {
               fine = true;
            }
         }
         if (fine == true) {
            out.print(true_value);
            out.print("\n");
         }
         else {
            out.println(-1);
         }
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

