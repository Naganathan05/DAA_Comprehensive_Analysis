import java.util.*;

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
        SCC solution = new SCC();

        int V = 15;  // Number of vertices (including 0 to 14)
        List<List<Integer>> adj = new ArrayList<>(V);
        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }

        adj.get(0).add(1);  
        adj.get(1).addAll(Arrays.asList(2, 3, 4));
        adj.get(2).add(5);
        adj.get(3).addAll(Arrays.asList(4, 6)); 
        adj.get(4).addAll(Arrays.asList(1, 6, 7));
        adj.get(5).add(2);
        adj.get(6).addAll(Arrays.asList(8, 9));   
        adj.get(7).add(6); 
        adj.get(8).add(7);            
        adj.get(9).add(10);   
        adj.get(10).addAll(Arrays.asList(11, 12));   
        adj.get(11).add(13); 
        adj.get(12).add(14);   
        adj.get(13).add(14);        

        int result = solution.kosaraju(V, adj);
        System.out.println("Number of Strongly Connected Components (SCCs): " + result);
    }
}