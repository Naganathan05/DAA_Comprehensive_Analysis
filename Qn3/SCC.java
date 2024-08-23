import java.util.*;
import java.io.*;

class SCC {
    private void getSortedOrder(List<List<Integer>> adj, int vertex, boolean[] visited, Stack<Integer> sortedOrder) {
        visited[vertex] = true;
        for (int node : adj.get(vertex)) {
            if (!visited[node]) {
                getSortedOrder(adj, node, visited, sortedOrder);
            }
        }
        sortedOrder.push(vertex);
    }

    private void DFS(List<List<Integer>> adjList, int vertex, boolean[] visited) {
        visited[vertex] = true;
        for (int node : adjList.get(vertex)) {
            if (!visited[node]) {
                DFS(adjList, node, visited);
            }
        }
    }

    public int kosaraju(int V, List<List<Integer>> adj) {
        Stack<Integer> sortedOrder = new Stack<>();
        boolean[] visited = new boolean[V];

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                getSortedOrder(adj, i, visited, sortedOrder);
            }
        }

        // Reverse the graph
        List<List<Integer>> reversedAdj = new ArrayList<>(V);
        for (int i = 0; i < V; i++) {
            reversedAdj.add(new ArrayList<>());
        }

        for (int i = 0; i < V; i++) {
            for (int j : adj.get(i)) {
                reversedAdj.get(j).add(i);
            }
        }

        Arrays.fill(visited, false);

        int numSCC = 0;
        while (!sortedOrder.isEmpty()) {
            int currVertex = sortedOrder.pop();
            if (!visited[currVertex]) {
                numSCC++;
                DFS(reversedAdj, currVertex, visited);
            }
        }
        return numSCC;
    }

    public static void main(String[] args) {
        try {
            BufferedReader br = new BufferedReader(new FileReader("testCase1.txt"));
            String[] firstLine = br.readLine().split(" ");
            int V = Integer.parseInt(firstLine[0]);  // Number of vertices
            int E = Integer.parseInt(firstLine[1]);  // Number of edges

            List<List<Integer>> adj = new ArrayList<>(V);
            for (int i = 0; i < V; i++) {
                adj.add(new ArrayList<>());
            }

            for (int i = 0; i < E; i++) {
                String[] edgeInfo = br.readLine().split(" ");
                int u = Integer.parseInt(edgeInfo[0]);
                int v = Integer.parseInt(edgeInfo[1]);
                adj.get(u).add(v);
            }

            SCC solution = new SCC();
            int result = solution.kosaraju(V, adj);
            System.out.println("Number of Strongly Connected Components (SCCs): " + result);
        } catch (IOException e) {
            System.out.println("Error reading input file.");
        }
    }
}