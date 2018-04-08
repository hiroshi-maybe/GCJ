package kori.gdd.slidingpuzzle.node.move;

import java.util.ArrayList;
import java.util.List;

import kori.gdd.slidingpuzzle.node.StateNode;
import kori.gdd.slidingpuzzle.state.BoardState;
import kori.gdd.slidingpuzzle.state.move.exception.MoveImpossibleException;

public abstract class AbstractNodeMove implements NodeMove {

	abstract protected NodeMoveParams createParams(BoardState s) throws MoveImpossibleException;
	
	@Override
	public StateNode execute(StateNode n) throws MoveImpossibleException {
		NodeMoveParams param = createParams(n.getState());
		List<Character> newHistory = new ArrayList<Character>(n.getHistory());
		newHistory.add(param.getAction());
		return new StateNode(new BoardState(param.getState().getSeq(), n.getState().getInfo()), n, newHistory);
	}

}
