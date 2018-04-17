import java.io.File;
import java.util.LinkedList;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Vector;
import java.util.Collections;
import java.util.Arrays;

public class wordladders {
	public static void main(String[] args) {
    File words = new File(args[0]);
		File wantedPaths = new File(args[1]);

    if(words.exists() == false || wantedPaths.exists() == false) {
			System.out.println("File not found");
			return;
		}
    int size = Integer.parseInt(args[0].split("words-")[1].split(".list")[0]);

    wordladders graph = new wordladders(words, size);
    graph.calcForInput(wantedPaths);
    System.out.print(graph.toString());
  }
  Node[] nodes;
	Map<String, Integer> nameToIndex;
  String output = "";

  public wordladders(File words, int size) {
		nodes = new Node[size];
    nameToIndex = new HashMap<>(size);
		Scanner scr;
    try {
		    scr = new Scanner(words);
    } catch (Exception e) {
      return;
    }

		int i = 0;
		while(scr.hasNextLine()) {
      String tmp = scr.nextLine();
			nodes[i] = new Node(tmp, size);
      nameToIndex.put(tmp, i);
			i++;
		}
		scr.close();

		calcConnections(size);
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
  private void addPossibleArc(int numa, int numb) {
    Node a = nodes[numa];
    Node b = nodes[numb];
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
    a.addNeighbour(numb);
    a.addConnection(b);
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
      int soul = breadthFirstAlgoritm(pairST[0], pairST[1]);
      output += (soul - 1) + "\n";
    }
	}

  private int breadthFirstAlgoritm(String a, String b) {
    LinkedList<Node> q = new LinkedList<Node>();
    Node start = nodes[nameToIndex.get(a)];
    Node finish = nodes[nameToIndex.get(b)];
    q.add(start);

    if(start.equals(finish)) {
        return 1;
    }

    for(Node v: nodes) {
        v.visited = false;
        v.numJ = 0;
    }

    start.visited = true;

    while(q.isEmpty() == false) {

      Node v = q.pop();
      if (v.neighbours[nameToIndex.get(b)] == 1){
        v.numJ ++;
        v.numJ ++;
        return v.numJ;
      }

      for(Node w : v.connections) {
        if(w.visited == false) {
          w.visited = true;
          q.addLast(w);
          w.numJ = v.numJ + 1;
        }
      }
    }
    return 0; // returns an empty list here.
  }

  @Override
	public String toString() {
		return output;
	}

  private static class Node {
		String word;
    int numJ;
    int[] neighbours;
		List<Node> connections;     // MIGHT NOT BE IDEAL.
		boolean visited;

		public Node(String word, int size) {
			this.word = word;
      numJ = 0;
			connections = new ArrayList<Node>();
      visited = false;
      neighbours = new int[size];
      Arrays.fill(neighbours, 0);
		}
    public void addConnection(Node n) {
			connections.add(n);
		}
    public void addNeighbour(int n) {
			neighbours[n] = 1;
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
