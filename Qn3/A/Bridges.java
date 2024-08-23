import java.util.*;
import java.io.*;

class Bridges {
    int timer = 1;

    public void DFS(List<List<Integer>> adjList, int server, int parent, int[] tin, int[] low, boolean[] visited, List<List<Integer>> bridges) {
        visited[server] = true;
        low[server] = tin[server] = timer;
        timer += 1;

        for (int it : adjList.get(server)) {
            if (it == parent) continue;
            if (!visited[it]) {
                DFS(adjList, it, server, tin, low, visited, bridges);
                low[server] = Math.min(low[server], low[it]);
                if (low[it] > tin[server]) bridges.add(Arrays.asList(server, it));
            } else {
                low[server] = Math.min(low[server], low[it]);
            }
        }
    }

    public List<List<Integer>> criticalConnections(int n, List<List<Integer>> connections) {
        List<List<Integer>> adjList = new ArrayList<>();
        for (int i = 0; i <= n; i++) adjList.add(new ArrayList<>());

        for (List<Integer> edge : connections) {
            adjList.get(edge.get(0)).add(edge.get(1));
            adjList.get(edge.get(1)).add(edge.get(0));
        }

        int[] low = new int[n + 1];
        int[] tin = new int[n + 1];
        boolean[] visited = new boolean[n + 1];
        List<List<Integer>> bridges = new ArrayList<>();
        DFS(adjList, 1, -1, tin, low, visited, bridges);
        return bridges;
    }
}

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("testCase1.txt"));
        String[] firstLine = br.readLine().split(" ");
        int n = Integer.parseInt(firstLine[0]);
        int m = Integer.parseInt(firstLine[1]);

        List<List<Integer>> connections = new ArrayList<>();
        for (int i = 0; i < m; i++) {
            String[] edge = br.readLine().split(" ");
            int u = Integer.parseInt(edge[0]);
            int v = Integer.parseInt(edge[1]);
            connections.add(Arrays.asList(u, v));
        }
        br.close();

        Bridges obj = new Bridges();
        List<List<Integer>> bridges = obj.criticalConnections(n, connections);

        System.out.println("Bridges (Critical Connections) in the graph are: " + bridges);
    }
}