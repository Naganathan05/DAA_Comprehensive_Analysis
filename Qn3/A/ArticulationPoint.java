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
        try {
            File file = new File("testCase1.txt");
            Scanner scanner = new Scanner(file);

            int n = scanner.nextInt();
            ArrayList<ArrayList<Integer>> adj = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                adj.add(new ArrayList<>());
            }

            while (scanner.hasNextInt()) {
                int u = scanner.nextInt();
                int v = scanner.nextInt();
                adj.get(u).add(v);
                adj.get(v).add(u);
            }

            scanner.close();

            ArticulationPoint obj = new ArticulationPoint();
            ArrayList<Integer> nodes = obj.articulationPoints(n, adj);

            System.out.println("Articulation points in the graph are: " + nodes);
        } catch (FileNotFoundException e) {
            System.out.println("File not found.");
        }
    }
}
