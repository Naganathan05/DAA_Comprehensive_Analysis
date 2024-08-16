import java.util.*;

class ArticulationPoint {
    private int timer = 1;

    private void dfs(int node, int parent, int[] vis, int[] tin, int[] low, int[] mark, ArrayList<ArrayList<Integer>> adj) {
        vis[node] = 1;
        tin[node] = low[node] = timer;
        timer += 1;
        int child = 0;

        for (Integer it : adj.get(node)) {
            if (it == parent) continue;

            if (vis[it] == 0) {
                dfs(it, node, vis, tin, low, mark, adj);
                low[node] = Math.min(low[node], low[it]);

                // Check if node is an articulation point
                if (low[it] >= tin[node] && parent != -1) mark[node] = 1;
                child += 1;
            } 
            else low[node] = Math.min(low[node], tin[it]);
        }

        // Special case for root node
        if (child > 1 && parent == -1) mark[node] = 1;
    }

    public ArrayList<Integer> articulationPoints(int n, ArrayList<ArrayList<Integer>> adj) {
        int[] vis = new int[n];
        int[] tin = new int[n];
        int[] low = new int[n];
        int[] mark = new int[n];

        for (int i = 0; i < n; i++) {
            if (vis[i] == 0) dfs(i, -1, vis, tin, low, mark, adj);
        }

        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            if (mark[i] == 1) ans.add(i);
        }

        if (ans.size() == 0) ans.add(-1);
        return ans;
    }
}

public class Main {
    public static void main(String[] args) {
        Runtime runtime = Runtime.getRuntime();
        // Start measuring time and memory
        long startTime = System.nanoTime();
        long startMemory = runtime.totalMemory() - runtime.freeMemory();
        long maxMemoryUsed = startMemory;

        int n = 15;  // Updated number of vertices
        int[][] edges = {
            {1, 2}, {1, 3}, {2, 4}, {3, 4}, {1, 4},
            {4, 9}, {4, 5}, {9, 12}, {9, 13}, {9, 14}, {12, 14},
            {13, 14}, {5, 6}, {5, 7}, {6, 7}, {7, 8}, {8, 11},
            {11, 10}, {8, 10}
        };
        ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            adj.add(new ArrayList<>());
            long currentMemory = runtime.totalMemory() - runtime.freeMemory();
            maxMemoryUsed = Math.max(maxMemoryUsed, currentMemory);
        }
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1];
            adj.get(u).add(v);
            adj.get(v).add(u);
            long currentMemory = runtime.totalMemory() - runtime.freeMemory();
            maxMemoryUsed = Math.max(maxMemoryUsed, currentMemory);
        }

        ArticulationPoint obj = new ArticulationPoint();
        ArrayList<Integer> nodes = obj.articulationPoints(n, adj);

        // End measuring time and memory
        long endTime = System.nanoTime();
        long endMemory = runtime.totalMemory() - runtime.freeMemory();

        maxMemoryUsed = Math.max(maxMemoryUsed, endMemory);

        long timeElapsed = endTime - startTime;

        System.out.println("Articulation points in the graph are: " + nodes);
        System.out.println("Time taken : " + timeElapsed / 1000 + " ms");
        System.out.println("Maximum memory used: " + maxMemoryUsed  / 1000 + " KB");
    }
}
