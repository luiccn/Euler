import java.time.Duration;
import java.time.Instant;

public class Main {
    public static void main(String[] args) {

        long LIMIT = 100_000;
        long MINIMUM = 4;


        Instant s = Instant.now();
//        Solver.Data data = Solver.solve(LIMIT, MINIMUM);
//        System.out.println(Duration.between(s, Instant.now()).toMillis());
//        System.out.println(data.count);

        s = Instant.now();
        long count = PrimeSolver.solve(LIMIT, MINIMUM);
        System.out.println(Duration.between(s, Instant.now()).toMillis());
        System.out.println(count);

    }
}
