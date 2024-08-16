import java.util.*;

class bridges {
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
            } 
            else low[server] = Math.min(low[server], low[it]);
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
    public static void main(String[] args) {

        int n = 12;
        List<List<Integer>> connections = new ArrayList<>();
        connections.add(Arrays.asList(1, 2));
        connections.add(Arrays.asList(2, 3));
        connections.add(Arrays.asList(3, 4));
        connections.add(Arrays.asList(1, 4));
        connections.add(Arrays.asList(4, 5));
        connections.add(Arrays.asList(5, 6));
        connections.add(Arrays.asList(6, 7));
        connections.add(Arrays.asList(7, 8));
        connections.add(Arrays.asList(8, 9));
        connections.add(Arrays.asList(9, 6));
        connections.add(Arrays.asList(8, 10));
        connections.add(Arrays.asList(10, 11));
        connections.add(Arrays.asList(10, 12));

        bridges obj = new bridges();
        List<List<Integer>> bridges = obj.criticalConnections(n, connections);

        System.out.println("Bridges (Critical Connections) in the graph are: " + bridges);
    }
}