import java.io.*;
import java.util.*;

public class Main {
   public static void main(String[] args) {
      InputStream inputStream = System.in;
      OutputStream outputStream = System.out;
      InputReader in = new InputReader(inputStream);
      OutputWriter out = new OutputWriter(outputStream);
      Task solver = new Task();
      solver.solve(1, in, out);
      out.close();
   }

   static class Task {
      public void solve(int testNumber, InputReader in, OutputWriter out) {
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
