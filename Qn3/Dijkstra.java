import java.util.*;

class dijkstras {
    public int[] dijkstra(int n, List<List<int[]>> adjList, int src) {
        int[] dist = new int[n];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[src] = 0;

        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[1]));
        pq.offer(new int[]{src, 0});

        while (!pq.isEmpty()) {
            int[] node = pq.poll();
            int u = node[0];
            int d = node[1];

            if (d > dist[u]) continue;

            for (int[] neighbor : adjList.get(u)) {
                int v = neighbor[0];
                int weight = neighbor[1];

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.offer(new int[]{v, dist[v]});
                }
            }
        }
        return dist;
    }
}

public class Main {
    public static void main(String[] args) {
        int n = 9;

        List<List<int[]>> adjList = new ArrayList<>();
        for (int i = 0; i < n; i++) adjList.add(new ArrayList<>());

        // Add edges: (src, dest, weight)
        adjList.get(0).add(new int[]{1, 4});
        adjList.get(0).add(new int[]{7, 8});
        adjList.get(1).add(new int[]{0, 4});
        adjList.get(1).add(new int[]{2, 8});
        adjList.get(1).add(new int[]{7, 11});
        adjList.get(2).add(new int[]{1, 8});
        adjList.get(2).add(new int[]{3, 7});
        adjList.get(2).add(new int[]{8, 2});
        adjList.get(2).add(new int[]{5, 4});
        adjList.get(3).add(new int[]{2, 7});
        adjList.get(3).add(new int[]{4, 9});
        adjList.get(4).add(new int[]{3, 9});
        adjList.get(4).add(new int[]{5, 10});
        adjList.get(5).add(new int[]{2, 4});
        adjList.get(5).add(new int[]{4, 10});
        adjList.get(5).add(new int[]{6, 2});
        adjList.get(6).add(new int[]{5, 2});
        adjList.get(6).add(new int[]{7, 1});
        adjList.get(6).add(new int[]{8, 6});
        adjList.get(7).add(new int[]{0, 8});
        adjList.get(7).add(new int[]{1, 11});
        adjList.get(7).add(new int[]{6, 1});
        adjList.get(7).add(new int[]{8, 7});
        adjList.get(8).add(new int[]{2, 2});
        adjList.get(8).add(new int[]{6, 6});
        adjList.get(8).add(new int[]{7, 7});

        int src = 0;

        dijkstras obj = new dijkstras();
        int[] distances = obj.dijkstra(n, adjList, src);

        System.out.println("Shortest distances from vertex " + src + " are:");
        for (int i = 0; i < distances.length; i++) {
            System.out.print(distances[i] + " ");
        }
    }
}
