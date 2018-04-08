package kori.gdd.slidingpuzzle.state;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import kori.gdd.slidingpuzzle.BoardInfo;
import kori.gdd.slidingpuzzle.constant.Constant;
import kori.gdd.slidingpuzzle.state.move.StateMove;
import kori.gdd.slidingpuzzle.state.move.StateMoveResult;
import kori.gdd.slidingpuzzle.state.move.exception.MoveImpossibleException;
import kori.gdd.slidingpuzzle.state.move.extend.D_Move;
import kori.gdd.slidingpuzzle.state.move.extend.L_Move;
import kori.gdd.slidingpuzzle.state.move.extend.R_Move;
import kori.gdd.slidingpuzzle.state.move.extend.U_Move;

public class BoardState {
	private char[] seq = null;
    private BoardInfo info = null;
    private Map<Character, Integer> posmap = new HashMap<Character, Integer>(); 
    List<StateMove> moveList = new ArrayList<StateMove>();
    private U_Move u_move = new U_Move();
    private D_Move d_move = new D_Move();
    private L_Move l_move = new L_Move();
    private R_Move r_move = new R_Move();
    
    public BoardState(char[] seq, BoardInfo info) {
    	this.seq = seq;
    	this.info = info;
    	for(int i=0; i<seq.length; i++) {
    		if(seq[i] != Constant.WALL_CHAR) {
    			posmap.put(seq[i], i);
    		}
    	}
    }
    
    @Override
	public int hashCode() {
		return new String(seq).hashCode();
	}
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		if (getClass() != obj.getClass())
			return false;
		BoardState other = (BoardState) obj;
		if (!Arrays.equals(seq, other.seq))
			return false;
		return true;
	}

	public Map<Character, Integer> getPosmap() {
		return posmap;
	}

	public void setPosmap(Map<Character, Integer> posmap) {
		this.posmap = posmap;
	}

	public boolean isComplete() {
    	boolean result = true;
    	char[] goal = this.info.getGoal().getSeq();
    	for(int i=0; i<seq.length; i++) {
    		if(seq[i]!=goal[i]) {
    			result = false;
    			break;
    		}
    	}
    	return result;
    }

	public char[] getSeq() {
		return seq;
	}

	public void setSeq(char[] seq) {
		this.seq = seq;
	}

	public BoardInfo getInfo() {
		return info;
	}

	public void setInfo(BoardInfo info) {
		this.info = info;
	}
	
	public StateMoveResult u_move() throws MoveImpossibleException {
		return u_move.move(this);
	}
	public StateMoveResult d_move() throws MoveImpossibleException {
		return d_move.move(this);
	}
	public StateMoveResult l_move() throws MoveImpossibleException {
		return l_move.move(this);
	}
	public StateMoveResult r_move() throws MoveImpossibleException {
		return r_move.move(this);
	}

	public String toString() {
		String result = "";
		for(int i=0; i<seq.length; i+=1) {
			result+=String.valueOf(seq[i]);
			if((i+1)%info.getWidth()==0) {
				result += "\n";
			}
		}
		return result;
	}
	
}
