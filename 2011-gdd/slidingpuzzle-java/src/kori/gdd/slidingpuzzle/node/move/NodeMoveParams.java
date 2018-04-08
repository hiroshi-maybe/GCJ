package kori.gdd.slidingpuzzle.node.move;

import kori.gdd.slidingpuzzle.state.BoardState;

public class NodeMoveParams {
	private char action = ' ';
	private BoardState state = null;
	
	public NodeMoveParams(char action, BoardState state) {
		super();
		this.action = action;
		this.state = state;
	}
	public char getAction() {
		return action;
	}
	public void setAction(char action) {
		this.action = action;
	}
	public BoardState getState() {
		return state;
	}
	public void setState(BoardState state) {
		this.state = state;
	}
	
}
