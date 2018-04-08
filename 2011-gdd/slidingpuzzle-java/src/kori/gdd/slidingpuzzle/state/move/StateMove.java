package kori.gdd.slidingpuzzle.state.move;

import kori.gdd.slidingpuzzle.state.BoardState;
import kori.gdd.slidingpuzzle.state.move.exception.MoveImpossibleException;

public interface StateMove {
	public StateMoveResult move(BoardState state) throws MoveImpossibleException;
}
