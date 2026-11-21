import java.util.*;
public class LettersDown {
    public static void main (String[] args) {
		Scanner scanner = new Scanner (System.in);
		int t = scanner.nextInt ();
		while (t-- > 0) {
			int n = scanner.nextInt();
			String s = scanner.next();
			List<Boolean> conversions = new ArrayList<>(25);
			for (char c = 'b'; c <= 'z'; ++c) {
				conversions.add(false);
			}
			for (int i = 0; i <= (n - 1) / 2; ++i) {
				char smaller = s.charAt(i),
					greater = s.charAt(n - 1 - i);
				if (greater < smaller) {
					char temp = smaller;
					smaller = greater;
					greater = temp;
				}
				// System.out.format("smaller, greater: %c, %c\n", smaller, greater);
				for (; smaller < greater; --greater) {
					conversions.set(greater - 'b', true);
					// System.out.format("%c ", greater);
				}
				// System.out.println("loop");
			}
			int count = 0;
			for (int i = 0; i < 25; ++i)
				if (conversions.get(i))
					++count;
			System.out.println(count);
		}
    }
}
