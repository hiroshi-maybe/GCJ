package kori.gdd.slidingpuzzle.state.move;

import kori.gdd.slidingpuzzle.state.BoardState;

public class StateMoveResult {
	public StateMoveResult(BoardState state, char action) {
		super();
		this.state = state;
		this.action = action;
	}
	private BoardState state = null;
	private char action = ' ';
	
	public BoardState getState() {
		return state;
	}
	public void setState(BoardState state) {
		this.state = state;
	}
	public char getAction() {
		return action;
	}
	public void setAction(char action) {
		this.action = action;
	}
	
	
}
