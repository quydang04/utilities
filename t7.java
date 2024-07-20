package t2;
import java.util.*;
class GraphNode { //đại diện cho một nút (đỉnh) trong đồ thị.
    String name; //Tên của nút.
    List<Edge> edges; //Danh sách các cạnh nối từ nút hiện tại đến các nút khác.
    public GraphNode(String name) {
        this.name = name; 
        this.edges = new ArrayList<>(); 
    }
    public void addEdge(String to, int cost) {
        this.edges.add(new Edge(to, cost));
    }
}
class Edge { //đại diện cho một cạnh trong đồ thị.
    String to; //Tên của nút đích mà cạnh này nối đến
    int cost; //Chi phí của cạnh
    public Edge(String to, int cost) {
        this.to = to;
        this.cost = cost; 
    }
}
public class t7 {
    public static class Node { //đại diện cho một trạng thái trong quá trình duyệt BFS
        String name;
        List<String> path; //Danh sách các nút đã đi qua để đến nút hiện tại.
        int cost; //Chi phí tổng để đi đến nút hiện tại
        public Node(String name, List<String> path, int cost) {
            this.name = name;
            this.path = new ArrayList<>(path);
            this.path.add(name);
            this.cost = cost;
        }
    }
    public static String[] bfsShortestPath(Map<String, GraphNode> graph, String start, String goal) {
        Queue<Node> queue = new LinkedList<>(); //Hàng đợi để duyệt các nút theo thứ tự BFS
        Map<String, Integer> visited = new HashMap<>();
        queue.add(new Node(start, new ArrayList<>(), 0));
        visited.put(start, 0); //Bản đồ lưu trữ chi phí nhỏ nhất để đến mỗi nút
        String[] shortestPath = null; //Biến lưu trữ đường đi ngắn nhất và chi phí nhỏ nhất tương ứng
        int minCost = Integer.MAX_VALUE;
        while (!queue.isEmpty()) {
            Node current = queue.poll();
            String currentNode = current.name;
            List<String> path = current.path;
            int currentCost = current.cost;
            if (currentNode.equals(goal)) {
                if (currentCost < minCost) {
                    shortestPath = path.toArray(new String[0]);
                    minCost = currentCost;
                }
                continue;
            }
            for (Edge edge : graph.get(currentNode).edges) {
                int newCost = currentCost + edge.cost;
                if (!visited.containsKey(edge.to) || newCost < visited.get(edge.to)) {
                    visited.put(edge.to, newCost);
                    queue.add(new Node(edge.to, path, newCost));
                }
            }
        }
        return shortestPath;
    }
    public static void main(String[] args) {
        Map<String, GraphNode> graph = new HashMap<>();
        GraphNode start = new GraphNode("START");
        start.addEdge("d", 3);
        start.addEdge("p", 1);
        start.addEdge("e", 9);
        graph.put("START", start);
        
        GraphNode d = new GraphNode("d");
        d.addEdge("b", 1);
        d.addEdge("c", 8);
        d.addEdge("e", 2);
        graph.put("d", d);

        GraphNode p = new GraphNode("p");
        p.addEdge("q", 15);
        graph.put("p", p);

        GraphNode b = new GraphNode("b");
        b.addEdge("a", 2);
        graph.put("b", b);

        GraphNode a = new GraphNode("a");
        graph.put("a", a);

        GraphNode c = new GraphNode("c");
        c.addEdge("a", 2);
        graph.put("c", c);

        GraphNode e = new GraphNode("e");
        e.addEdge("r", 9);
        e.addEdge("h", 1);
        graph.put("e", e);

        GraphNode h = new GraphNode("h");
        h.addEdge("q", 4);
        h.addEdge("p", 4);
        graph.put("h", h);

        GraphNode q = new GraphNode("q");
        q.addEdge("r", 3);
        graph.put("q", q);

        GraphNode r = new GraphNode("r");
        r.addEdge("f", 5);
        graph.put("r", r);

        GraphNode f = new GraphNode("f");
        f.addEdge("c", 5);
        f.addEdge("GOAL", 5);
        graph.put("f", f);

        String[] shortestPath = bfsShortestPath(graph, "START", "GOAL");
        if (shortestPath != null) {
            System.out.println("Đường đi ngắn nhất: " + String.join(" -> ", shortestPath));
        } else {
            System.out.println("Không tìm thấy đường đi.");
        }
    }
}