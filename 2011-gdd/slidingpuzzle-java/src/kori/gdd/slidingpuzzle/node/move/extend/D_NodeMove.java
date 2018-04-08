package kori.gdd.slidingpuzzle.node.move.extend;

import kori.gdd.slidingpuzzle.node.StateNode;
import kori.gdd.slidingpuzzle.node.move.AbstractNodeMove;
import kori.gdd.slidingpuzzle.node.move.NodeMoveParams;
import kori.gdd.slidingpuzzle.state.BoardState;
import kori.gdd.slidingpuzzle.state.move.StateMoveResult;
import kori.gdd.slidingpuzzle.state.move.exception.MoveImpossibleException;

public class D_NodeMove extends AbstractNodeMove {

	@Override
	protected NodeMoveParams createParams(BoardState s) throws MoveImpossibleException {
		StateMoveResult result = s.d_move();
		return new NodeMoveParams(result.getAction(), result.getState());
	}

	@Override
	public boolean isNeedlessMove(StateNode n) {
		return n.getHistory().size()>0 && n.getHistory().get(n.getHistory().size()-1)=='U'
			? true : false;
	}

}
