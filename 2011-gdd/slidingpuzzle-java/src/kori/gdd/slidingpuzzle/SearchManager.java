package kori.gdd.slidingpuzzle;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.PriorityQueue;

import kori.gdd.slidingpuzzle.constant.Constant;
import kori.gdd.slidingpuzzle.node.StateNode;
import kori.gdd.slidingpuzzle.node.move.NodeMove;
import kori.gdd.slidingpuzzle.state.BoardState;
import kori.gdd.slidingpuzzle.state.move.exception.MoveImpossibleException;

import org.apache.commons.lang3.StringUtils;

public class SearchManager {
	private int id = 0;
	private StateNode root = null;
	private PriorityQueue<StateNode> open = null;
	private Map<BoardState, Double> closed = null;
	private StateNode current = null;
	private static boolean dumpEmabled = true;
	
	public SearchManager(int id, StateNode root) {
		this.id = id;
		this.root = root;
		
		this.open = new PriorityQueue<StateNode>(Constant.OPEN_LIMIT_INIT_QUE_SIZE, 
				new Comparator<StateNode>(){
			@Override
			public int compare(StateNode a, StateNode b) {
				int result = 0;
				if (a.getScore()-b.getScore()>0) {
					result = 1;
				} else if (a.getScore()==b.getScore()) {
					result =0;
				} else {
					result = -1;
				}
				return result;
			}
		});
		this.closed = new HashMap<BoardState, Double>();
		this.open.add(root);
	}
	
	public StateNode search() {
		
		while (!this.open.isEmpty()) {
			
			current = open.poll();
			closed.put(current.getState(), current.getScore());

			if (closed.size()>Constant.CLOSED_LIMIT_NUM) {
				dump(current);
				return null;
			}
						
			if(current.getState().isComplete()) {
				dump(current);
				return current;
			}
			getChildWithDepth(current.getHistory().size()/30+1, 0, current);
			//System.out.println(current.getHistory().size()/20+1);
			//getChildWithDepth(1, 0, current);
		}
		dump(current);
		return null;
	}
	
	// 反復深化用メソッド
	private void getChildWithDepth(int max_depth, int current_depth, StateNode org) {
		current_depth+=1;
		if(current_depth > max_depth) {
			return;
		}
		//System.out.println(current_depth+"/"+max_depth);
		for(Iterator<NodeMove> it = org.validMove(); it.hasNext(); ) {
			NodeMove mover = it.next();
			try {
				StateNode child = mover.execute(org);
				if (closed.keySet().contains(child.getState())) {
					if (closed.get(child.getState()) > child.getScore()) {
						closed.remove(child.getState());
						open.add(child);
					}
				} else {
					open.add(child);
				}
				/*if (child.getScore()<=org.getScore()) {
					getChildWithDepth(max_depth, current_depth, child);
				}*/
			} catch (MoveImpossibleException e) {
			}
		}
	}
	
	private void dump(StateNode current) {
		if(!this.dumpEmabled) {return;}
		File file = new File("./dump/"+StringUtils.leftPad(String.valueOf(this.id), 3, '0'));
		PrintWriter pw = null;
		try {
			pw = new PrintWriter(new BufferedWriter(new FileWriter(file)));
			pw.println(root.getState());
			pw.println(current.getHistory());
			pw.println(current.printScore());
			pw.println(current.getState());
			pw.println(open.size()+":"+closed.size());
			
			StateNode n = current;
			while(n!=null) {
				pw.println(n.getState());
				if(n.getHistory().size()==0) {
					pw.println("init");
				} else {
					pw.println(n.getHistory().get(n.getHistory().size()-1));
				}
				n = n.getParent();
			}
			/*while(!open.isEmpty()) {
				StateNode n = open.poll();
				pw.println(n.printScore());
				pw.println(n.getState().toString());
			}*/

		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally {
			pw.close();
		}
	}

}
