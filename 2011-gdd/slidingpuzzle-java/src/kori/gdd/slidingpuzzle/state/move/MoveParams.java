package kori.gdd.slidingpuzzle.state.move;

public class MoveParams {
	private int newEmptyPos=0;
	private char action = ' ';
	
	public MoveParams(int newEmptyPos, char action) {
		super();
		this.newEmptyPos = newEmptyPos;
		this.action = action;
	}
	public int getNewEmptyPos() {
		return newEmptyPos;
	}
	public void setNewEmptyPos(int newEmptyPos) {
		this.newEmptyPos = newEmptyPos;
	}
	public char getAction() {
		return action;
	}
	public void setAction(char action) {
		this.action = action;
	}
	
	
}
