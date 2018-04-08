package kori.gdd.slidingpuzzle.node.move;

import kori.gdd.slidingpuzzle.node.StateNode;
import kori.gdd.slidingpuzzle.state.move.exception.MoveImpossibleException;

public interface NodeMove {
	public StateNode execute(StateNode n) throws MoveImpossibleException;
	public boolean isNeedlessMove(StateNode n);
}
