package kori.gdd.slidingpuzzle.state.move.exception;

public class MoveImpossibleException extends Exception {

	private char action = ' ';
	/**
	 * 
	 */
	private static final long serialVersionUID = 555658279238259785L;
	
	public MoveImpossibleException(char action) {
		super();
		this.action = action;
	}

	public char getAction() {
		return action;
	}
}
