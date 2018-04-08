package kori.gdd.slidingpuzzle;

import java.util.ArrayList;

import kori.gdd.slidingpuzzle.constant.Constant;
import kori.gdd.slidingpuzzle.node.StateNode;
import kori.gdd.slidingpuzzle.state.BoardState;

public class Board {
	private int id = 0;
	private BoardState goal=null;
	private StateNode root=null;
	private BoardInfo info=null;
	
	public Board(int id, String line) {
		this.id = id;
		String[] data = line.split(",");
		String width = data[0];
		String height = data[1];
		char[] seq = data[2].toCharArray();
		this.info = new BoardInfo(Integer.parseInt(width), Integer.parseInt(height)
				, seq, goal(seq));
		this.root = new StateNode(new BoardState(seq, info), null, new ArrayList<Character>());
	}
	
	public StateNode search() {
		SearchManager sm = new SearchManager(id, root);
		return sm.search();
	}
	
	private char[] goal(char[] seq) {
		char[] goalSeq = new char[seq.length];
		for(int i=0; i<seq.length; i++) {
			if (Constant.WALL_CHAR == seq[i]) {
				goalSeq[i] = Constant.WALL_CHAR;
			} else if (i == seq.length-1) {
				goalSeq[i] = Constant.EMPTY_CHAR;
			} else {
				goalSeq[i] = Constant.BASE_ORDER[i];
			}
		}
		return goalSeq;
	}
}
