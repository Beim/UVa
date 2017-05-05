import java.util.Scanner;

public class uva {
  public static void main(String[] args) {
    Scanner fin = new Scanner(System.in);
    int lele = 0;
    while (fin.hasNext()) {
      int n = fin.nextInt();
      if (n == 0) {
        break;
      }
      int[] a = new int[n];
      String b;
      for (int i = 0; i < n; i++) {
        String x = fin.next();
          a[i] = Integer.parseInt(x.substring(1));
      }
    }
  }
}
