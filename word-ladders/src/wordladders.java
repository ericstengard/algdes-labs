import java.io.File;
import java.util.LinkedList;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class wordladders {
	public static void main(String[] args) {
	/*
	 * arg0 == words-size-file, arg1 == in file (wanted maps).
	 * Connections: if v[1,4] is a part of w[0,4] => connection v -> w
	 */

		File words = new File(args[0]);
		File wantedPaths = new File(args[1]);

		if(words.exists() == false || wantedPaths.exists() == false) {
			System.out.println("File not found");
			return;
		}



		int size = Integer.parseInt(args[0].split("words-")[1].split(".txt")[0]);
    long graphA = System.nanoTime();
		wordladders graph = new wordladders(words, size);
    long graphB = System.nanoTime();
    System.out.println("Graph: " + (graphB - graphA)/1000000 + "ms");

		long algoA = System.nanoTime();
		graph.calcForInput(wantedPaths);											//FASTER: Just connect for wanted words.
        long algoB = System.nanoTime();



		System.out.print(graph.toString());
		System.out.println("Graph: " + (graphB - graphA)/1000000 + "ms");
		System.out.println("Algo: " + (algoB - algoA)/1000000 + "ms");
	}

	String output = "If this is shown then no input was specified";

	Node[] nodes;
	Map<String, Integer> connectors;

	public wordladders(File words, int size) {
		nodes = new Node[size];
        connectors = new HashMap<>(size);
		Scanner scr;
		try {
			scr = new Scanner(words);
		} catch (Exception e) {
			return;
		}

		// long readA = System.nanoTime();

		int i = 0;
		while(scr.hasNextLine()) {
            String tmp = scr.nextLine();
			nodes[i] = new Node(tmp);
            connectors.put(tmp, i);
			i++;
		}
		// long readB = System.nanoTime();
		scr.close();

		//System.out.println("Read: " + (readB - readA)/1000000 + "ms");


		long connectA = System.nanoTime();
		calcConnections(size);
		long connectB = System.nanoTime();


		System.out.println("Connect: " + (connectB - connectA)/1000000 + "ms");
	}

	private void calcConnections(int size) {
		for(int i = 0; i < size; i++) {
			for(int j = i; j < size; j++) {
				if(i != j) {
					addPossibleArc(i,j);
					addPossibleArc(j,i);
				}
			}
		}
	}

	private void calcConnectionsForSelected(String word) {
		if(nodes[connectors.get(word)].calculated == false) {
			calcConnectionsForSelected(nodes[connectors.get(word)]);
		}
	}

	private void calcConnectionsForSelected(Node node) {
		if(node.calculated)
			return;

		for(Node n: nodes) {
			addPossibleArc(node, n);
		}

		node.calculated = true;
	}

	private void addPossibleArc(int a, int b) {
		if(a == b)
			return;
		addPossibleArc(nodes[a], nodes[b]);
	}

	private void addPossibleArc(Node a, Node b) {

        if(a.equals(b))
            return;

		char[] dataOfA = a.word.toCharArray();
		char[] dataOfB = b.word.toCharArray();

		int nbrCorr = 0;

		for(int i = 1; i < 5; i++) { //Last four of a
            boolean isPart = false;
			for(int j = 0; j < 5; j++) {
				if(dataOfB[j] != '\u0000') {
					if(dataOfB[j] == dataOfA[i]) {
						dataOfB[j] = '\u0000';      //sets to empty
                        j = 5;                      //sets j to max so two of e's wont be removed in a row
                        isPart = true;              //sets that a character was found.
					}
				}
			}
            if(isPart == false) return;             //If one of the four characters werent found, stop.
        }
        a.addConnection(b);
	}

    public List<Node> breadthFirstAlgoritm(String s, String t) {
        return breadthFirstAlgoritm(nodes[connectors.get(s)], nodes[connectors.get(t)]);
    }


    private List<Node> breadthFirstAlgoritm(Node start, Node finish) {
        LinkedList<Node> q = new LinkedList<Node>();
        q.add(start);

        if(start.equals(finish)) {
            return q;
        }

        for(Node v: nodes) {
            v.visited = false;
            v.pred = null;
        }

        start.visited = true;

        while(q.isEmpty() == false) {

            Node v = q.pop();

            for(Node w : v.connections) {
                if(w.visited == false) {
                    w.visited = true;
                    q.addLast(w);
                    w.pred = v;

                    if(w.equals(finish)) {
                        return w.getNodePathFromThis(start);
                    }
                }
            }
        }
        return new LinkedList<Node>(); // returns an empty list here.
    }

	private void calcForInput(File wantedPaths) {
        Scanner scr = null;
        try {
            scr = new Scanner(wantedPaths);
        } catch (Exception e) {

        }

        output = "";
        while(scr.hasNextLine()) {
            String[] pairST = scr.nextLine().split(" ");
			//calcConnectionsForSelected(pairST[0]);
            List<Node> nodes = breadthFirstAlgoritm(pairST[0], pairST[1]);
            //for(Node n: nodes) {

            // }
            //if(nodes.size() == 0) output += "can't find path.";
            output += (nodes.size() - 1);   // CHANGE HERE TO PRINT PATH

            output += "\n";
        }
	}

	@Override
	public String toString() {
		return output;
	}

	private static class Node {
		String word;
        Node pred = null;
		List<Node> connections;     // MIGHT NOT BE IDEAL.
		boolean visited;
		boolean calculated;

		public Node(String word) {
			this.word = word;
			connections = new ArrayList<Node>();
		}

		public void addConnection(Node n) {
			connections.add(n);
		}

        public List<Node> getNodePathFromThis(Node end) {
            return getNodePathFromThis(end, new LinkedList<Node>());
        }

        private List<Node> getNodePathFromThis(Node end, List<Node> nodes) {
            if(end.equals(this)) {
                nodes.add(this);
                return nodes;
            }

            nodes.add(this);
            return this.pred.getNodePathFromThis(end, nodes);
        }

        @Override
        public boolean equals(Object obj) {
            if(obj instanceof Node) {
                return (((Node) obj).word.equals(this.word));
            }
            return false;
        }
	}
}
