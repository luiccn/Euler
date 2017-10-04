import java.util.*;

public class PrimeSolver {


    public static long solve(long limit, long minimum) {

        SieveOfEratosthenes primes = new SieveOfEratosthenes();

        long DEPTH = 30L;
        long n = 0;

        List<Map.Entry<Long, Long>> list = new LinkedList<>();

        Set<Long> tried = new HashSet<>();

        while(primes.hasNext() && n < limit) {

            Set<Long> tries = new HashSet<>();
            long prime = primes.next();

            for (long i = prime; i < prime + DEPTH; i++) {

                if (!tried.contains(i)) {
                    tries.add(i);
                    tried.add(i);
                }
            }

            for (long i = prime; i > prime - DEPTH && i > 0; i--) {

                if (!tried.contains(i)) {
                    tries.add(i);
                    tried.add(i);
                }
            }


            for (Long aTry : tries) {

                if (aTry > n) n = aTry;
                HashMap<Long, Long> map = new HashMap<>();
                for (long i = 2; i <= aTry; i++) {
                    for (long j = 1; j < i; j++) {
                        long k = f(i,j);
                        if (k > aTry) break;
                        if (k == aTry) {
                            if (!map.containsKey(k)) {
                                map.put(k, 1L);
                            } else {
                                map.put(k, map.get(k) + 1);
                            }
                        }

                    }
                }
                map.entrySet().parallelStream().filter(e -> e.getValue() == minimum).forEach(list::add);


            }

            tried.addAll(tries);

        }

        Map<Long, Long> map = new HashMap<>();
        for (Map.Entry<Long, Long> entry : list) {
            map.merge(entry.getKey(), entry.getValue(), Long::sum);
        }

        return map.size();
    }

    public static long f(long x, long y) {
        return x*x + 3*x*y + y*y;
    }
}
