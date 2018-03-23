import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.Deque;
import java.util.LinkedList;
import java.util.Scanner;

public class Stablemarriage {
	
	public static void main(String[] args) {
		long startTimeTot = System.nanoTime();
		File file = new File(args[0]);
		
		Stablemarriage bond = new Stablemarriage();
		
		if(readFromFile(file, bond) == false)
			return;
		
		long startTimeProc = System.nanoTime();
		bond.marriageProcedure();
		long endTimeProc = System.nanoTime();
		
		System.out.println(bond);
		long startTimeEnd = System.nanoTime();
		
		System.out.println("diff a: " + (startTimeEnd - startTimeTot)/1000000);
		System.out.println("diff b: " + (endTimeProc - startTimeProc)/1000000);
		
		
	}

	private static boolean readFromFile(File file, Stablemarriage bond) {
		Scanner scr = null;
		
		try {
			if(file.exists() == false) {
				throw new IOException("File not found!");
			}
			scr = new Scanner(file);
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}
		
		String line;
		
		while(scr.hasNextLine()) {
			line = scr.nextLine();
			bond.treatLine(line);
		}
		
		scr.close();
		return true;
	}
	
	int n;
	
	Man[] me;
	Woman[] fe;
	
	private void treatLine(String line) {
		if(line.isEmpty())
			return;
		
		if(line.charAt(0) == '#')
			return;
		
		if(line.substring(0, 2).equals("n=")) { 
			n = Integer.parseInt(line.replaceFirst("n=", ""));
			me = new Man[n];
			fe = new Woman[n];
			return;
		}
		
		String[] data = line.split(" ");
		
		if(data[0].contains(":")) {
			addPreference(data);
		} else {
			addName(Integer.parseInt(data[0]), data[0].length() + 1, line);
		}
	}

	private void addName(int id, int split, String line) {
		if(id % 2 == 1) {
			me[id/2] = new Man(id, line.substring(split));
		} else {
			fe[id/2 - 1] = new Woman(id, line.substring(split));	//Minus one due to smallest id of a woman is 2 and 2/2 = 1 
		}
	}

	private void addPreference(String[] data) {
		int id = Integer.parseInt(data[0].substring(0, data[0].length() - 1));
		
		if(id % 2 == 1) {
			me[id/2].addPreference(data);
		} else {
			fe[id/2 - 1].addPreference(data);
		}
	}

	private void marriageProcedure() {
		Deque<Man> singleMen = new LinkedList<>(Arrays.asList(me));	
		Deque<WeddingPair> married = new LinkedList<>();
		
		int i = 0;
		
		while(singleMen.isEmpty() == false) {
			singleMen.pop().propose(fe, singleMen, married);
			if(i != singleMen.size()) {
				i = singleMen.size();
			}
		}
		
	}
	
	@Override
	public String toString() {
		String tmp = "";
		
		for(Person m: me) {
			tmp += m.toString() + "\n";
		}
		
		return tmp;
	}
	
	private static class WeddingPair {
		Person p1, p2;
		
		public WeddingPair(Person p1, Person p2) {
			this.p1 = p1;
			this.p2 = p2;
		}
		
		@Override
		public boolean equals(Object obj) {
			if(obj instanceof WeddingPair) {
				WeddingPair tmp = ((WeddingPair) obj);
				return tmp.p1.equals(p1) && tmp.p2.equals(p2);
			}
			return false;
		}
	}
	
	private abstract static class Person{
		String name;
		int id;
		
		Person matched = null;
		
		public Person(int id, String name) {
			this.name = name;
			this.id = id;
		}

		abstract void addPreference(String[] rowData);
		
		@Override
		public boolean equals(Object obj) {
			if(obj instanceof Person) {
				return ((Person) obj).id == this.id;
			}
			return false;
		}
		
		public void dumped() {
			this.matched = null;
		}
		
		public WeddingPair match(Person man) {
			this.matched = man;
			man.matched = this;
			return new WeddingPair(man, this);
		}
		
		@Override
		public String toString() {
			return this.name + " -- " + matched.name;
		}
	}
	
	private static class Man extends Person {
		int i = 0;
		int[] preferedWomenOrder;
		
		public Man(int id, String name) {
			super(id, name);
		}

		public void propose(Woman[] females, Deque<Man> p, Deque<WeddingPair> pairs) {
			females[preferedWomenOrder[i]].propose(this, p, pairs);
			i++;
		}
		
		@Override
		void addPreference(String[] rowData) {
			this.preferedWomenOrder = new int[rowData.length - 1];
			
			for(int i = 1; i < rowData.length; i++) {
				preferedWomenOrder[i - 1] = Integer.parseInt(rowData[i]) / 2 - 1; 
			}
		}
	}
	
	private static class Woman extends Person {
		int[] preferedManIndices;
		
		public Woman(int id, String name) {
			super(id, name);
		}
		
		private boolean prefersThisMan(Man man) {
			return this.preferedManIndices[this.matched.id/2] >= this.preferedManIndices[man.id/2];
		}

		public boolean propose(Man man, Deque<Man> p, Deque<WeddingPair> pairs) {
			if(matched == null) {
				pairs.add(this.match(man));
				return true;
			} else if(prefersThisMan(man)) {
				Man currMan = (Man) this.matched;
				pairs.removeFirstOccurrence(new WeddingPair(currMan, this));
				pairs.add(this.match(man));
				currMan.dumped();
				p.add(currMan);
				return true;
			} else {
				p.add(man);
				return false;
			}
		}

		@Override
		void addPreference(String[] rowData) {
			this.preferedManIndices = new int[rowData.length - 1];
			
			for(int i = 1; i < rowData.length; i++) {
				this.preferedManIndices[Integer.parseInt(rowData[i])/2] = i;
			}
		}
	}
	
}
