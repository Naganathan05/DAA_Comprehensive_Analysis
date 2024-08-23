import java.util.*;
import java.io.*;

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
        try {
            BufferedReader br = new BufferedReader(new FileReader("testCase1.txt"));
            String[] firstLine = br.readLine().split(" ");
            int n = Integer.parseInt(firstLine[0]); 
            int m = Integer.parseInt(firstLine[1]); 

            List<int[]> edges = new ArrayList<>();
            for (int i = 0; i < m; i++) {
                String[] edgeInfo = br.readLine().split(" ");
                int u = Integer.parseInt(edgeInfo[0]);
                int v = Integer.parseInt(edgeInfo[1]);
                int weight = Integer.parseInt(edgeInfo[2]);
                edges.add(new int[]{u, v, weight});
            }

            int src = 0;

            Solution obj = new Solution();
            int[] distances = obj.bellmanFord(n, edges, src);

            if (distances != null) {
                System.out.println("Shortest distances from vertex " + src + " are:");
                for (int i = 0; i < distances.length; i++) {
                    System.out.print(distances[i] + " ");
                }
                System.out.println();
            }
        } catch (IOException e) {
            System.out.println("Error reading input file.");
        }
    }
}