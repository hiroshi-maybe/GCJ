package kori.gdd.slidingpuzzle.state.move;

import kori.gdd.slidingpuzzle.constant.Constant;
import kori.gdd.slidingpuzzle.state.BoardState;
import kori.gdd.slidingpuzzle.state.move.exception.MoveImpossibleException;

public abstract class AbstractMove implements StateMove {
	protected abstract MoveParams getParams(int emptyPos, int width);
	@Override
	public StateMoveResult move(BoardState state) throws MoveImpossibleException {

		MoveParams params = getParams(state.getPosmap().get(Constant.EMPTY_CHAR), state.getInfo().getWidth());
		
		// 動かせない条件
		if(params.getNewEmptyPos()<0 || params.getNewEmptyPos()>state.getInfo().getSeqnum()-1
				|| state.getSeq()[params.getNewEmptyPos()]==Constant.WALL_CHAR
				|| (state.getInfo().get_x(state.getPosmap().get(Constant.EMPTY_CHAR))==0 && params.getAction()==Constant.L_ACTION) // 左端
				|| (state.getInfo().get_x(state.getPosmap().get(Constant.EMPTY_CHAR))==state.getInfo().getWidth()-1 && params.getAction()==Constant.R_ACTION) //右端
				|| (state.getInfo().get_y(state.getPosmap().get(Constant.EMPTY_CHAR))==0 && params.getAction()==Constant.U_ACTION) // 上端
				|| (state.getInfo().get_x(state.getPosmap().get(Constant.EMPTY_CHAR))==state.getInfo().getHeight()-1 && params.getAction()==Constant.D_ACTION) /*下端*/){
			throw new MoveImpossibleException(params.getAction()); 
		}
		
		char[] newseq = state.getSeq().clone();
		char temp = newseq[state.getPosmap().get(Constant.EMPTY_CHAR)];
		newseq[state.getPosmap().get(Constant.EMPTY_CHAR)] = newseq[params.getNewEmptyPos()];
		newseq[params.getNewEmptyPos()] = temp;
		
		return new StateMoveResult(new BoardState(newseq, state.getInfo()), params.getAction());
	}

}
