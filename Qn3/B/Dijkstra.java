import java.util.*;
import java.io.*;

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
        try {
            BufferedReader br = new BufferedReader(new FileReader("testCase1.txt"));
            String[] firstLine = br.readLine().split(" ");
            int n = Integer.parseInt(firstLine[0]);  // Number of vertices
            int m = Integer.parseInt(firstLine[1]);  // Number of edges

            List<List<int[]>> adjList = new ArrayList<>();
            for (int i = 0; i < n; i++) adjList.add(new ArrayList<>());

            for (int i = 0; i < m; i++) {
                String[] edgeInfo = br.readLine().split(" ");
                int u = Integer.parseInt(edgeInfo[0]);
                int v = Integer.parseInt(edgeInfo[1]);
                int weight = Integer.parseInt(edgeInfo[2]);
                adjList.get(u).add(new int[]{v, weight});
                adjList.get(v).add(new int[]{u, weight}); 
            }

            int src = 0;  

            dijkstras obj = new dijkstras();
            int[] distances = obj.dijkstra(n, adjList, src);

            System.out.println("Shortest distances from vertex " + src + " are:");
            for (int i = 0; i < distances.length; i++) {
                System.out.print(distances[i] + " ");
            }
            System.out.println();
        } catch (IOException e) {
            System.out.println("Error reading input file.");
        }
    }
}