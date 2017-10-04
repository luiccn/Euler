import java.util.HashMap;
import java.util.Map;

public class Solver {
    public static Data solve(long limit, long minimum) {

        HashMap<Long, Long> map = new HashMap<>();
        long c = 0;
        for (int i = 1; i < limit; i++) {
            for (int j = 1; j < i; j++) {
                c++;
                long k = f(i,j);
                if (k < limit) map.merge(k, 1L, Long::sum);

            }
        }
        System.out.println(c);
        long count = map.entrySet().parallelStream().filter(e -> e.getValue() == minimum).count();
        return new Data(count, map);
    }

    public static long f(long x, long y) {
        return x*x + 3*x*y + y*y;
    }


    public static class Data {

        public long count;
        public Map<Long, Long> map;

        public Data(long count, Map<Long, Long> map) {
            this.count = count;
            this.map = map;
        }
    }
}
