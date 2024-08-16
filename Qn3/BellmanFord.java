import java.util.*;

class Solution {
    public int[] bellmanFord(int n, List<int[]> edges, int src) {
        int[] dist = new int[n];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[src] = 0;

        for (int i = 1; i < n; i++) {
            for (int[] edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int weight = edge[2];

                if (dist[u] != Integer.MAX_VALUE && dist[u] + weight < dist[v]) dist[v] = dist[u] + weight;
            }
        }

        for (int[] edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];

            if (dist[u] != Integer.MAX_VALUE && dist[u] + weight < dist[v]) {
                System.out.println("Graph contains a negative-weight cycle");
                return null;
            }
        }
        return dist;
    }
}

public class Main {
    public static void main(String[] args) {
        int n = 9;

        List<int[]> edges = new ArrayList<>();
        
        edges.add(new int[]{0, 1, 4});
        edges.add(new int[]{0, 7, 8});
        edges.add(new int[]{1, 2, 8});
        edges.add(new int[]{1, 7, 11});
        edges.add(new int[]{2, 3, 7});
        edges.add(new int[]{2, 8, 2});
        edges.add(new int[]{2, 5, 4});
        edges.add(new int[]{3, 4, 9});
        edges.add(new int[]{4, 5, 10});
        edges.add(new int[]{5, 6, 2});
        edges.add(new int[]{6, 7, 1});
        edges.add(new int[]{6, 8, 6});
        edges.add(new int[]{7, 0, 8});
        edges.add(new int[]{7, 1, 11});
        edges.add(new int[]{7, 8, 7});
        edges.add(new int[]{8, 6, 6});

        int src = 0;

        Solution obj = new Solution();
        int[] distances = obj.bellmanFord(n, edges, src);

        if (distances != null) {
            System.out.println("Shortest distances from vertex " + src + " are:");
            for (int i = 0; i < distances.length; i++) System.out.print(distances[i] + " ");
        }
        return;
    }
}
