package kori.gdd.slidingpuzzle.node;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import kori.gdd.slidingpuzzle.ScoreUtils;
import kori.gdd.slidingpuzzle.constant.Constant;
import kori.gdd.slidingpuzzle.node.move.NodeMove;
import kori.gdd.slidingpuzzle.node.move.extend.D_NodeMove;
import kori.gdd.slidingpuzzle.node.move.extend.L_NodeMove;
import kori.gdd.slidingpuzzle.node.move.extend.R_NodeMove;
import kori.gdd.slidingpuzzle.node.move.extend.U_NodeMove;
import kori.gdd.slidingpuzzle.state.BoardState;

public class StateNode {

	private BoardState state=null;
	private StateNode parent=null;
	private StateNode[] children=null;
	private List<Character> history=null;
	private double score=0;
	public double manhattanScore = 0;
	public double hisotryScore = 0;
	public double partMatchScore = 0;
	public double horizonScore = 0;
	public double verticalScore = 0;
	  
	public StateNode(BoardState state, StateNode parent, List<Character> history) {
		this.state = state;
		this.parent = parent;
		this.history = history;
		this.score = get_score();
	}
	
	private double get_score() {
		double g = this.history.size();
		double manhattan_score = get_manhattan_score();
		this.manhattanScore = manhattan_score;

		this.hisotryScore = g;
		double part_match_score = 0;
		int partTryCount = 0;
		for(int i=2; i<state.getInfo().getWidth(); i++) {
			for(int j=2; j<state.getInfo().getHeight(); j++) {
				score = get_partial_block_score(i, j);
				part_match_score += score;
				partTryCount+=1;
			}
		}
		part_match_score /= partTryCount;
		this.partMatchScore = part_match_score;
		this.horizonScore = horizon_pos_score();
		this.verticalScore = vertical_pos_score();
		return g+manhattan_score+part_match_score+horizonScore+verticalScore;
	}
    private double vertical_pos_score() {
    	double score = 0;
    	//TODO: neighbor is WALL_CHAR case ??
    	for(int i=0; i<state.getSeq().length-1; i+=1) {
    		if(state.getSeq()[i] != Constant.WALL_CHAR) {
    			score += state.getSeq()[state.getInfo().neighbor_x(i)]
    		                           ==state.getInfo().getGoal().getSeq()[state.getInfo().neighbor_x(state.getInfo().getGoal().getPosmap().get(state.getSeq()[i]))]
    		                                                                ? 0 : Constant.VERTICAL_SCORE;
    		}
    	}
    	return score;
    }
    private double horizon_pos_score() {
    	double score = 0;
    	//TODO: neighbor is WALL_CHAR case ??
    	for(int i=0; i<state.getSeq().length-1; i+=1) {
    		if(state.getSeq()[i] != Constant.WALL_CHAR) {
    			score += state.getSeq()[state.getInfo().neighbor_y(i)]
    		                           ==state.getInfo().getGoal().getSeq()[state.getInfo().neighbor_y(state.getInfo().getGoal().getPosmap().get(state.getSeq()[i]))]
    		                                                                ? 0 : Constant.HORIZON_SCORE;
    		}
    	}
    	return score;
    }

	private double get_manhattan_score() {
		double score = 0;
		char[] seq=this.state.getSeq();
		for(int i=0; i<seq.length; i+=1) {
			if (seq[i] != Constant.WALL_CHAR) {
				int now_y = this.state.getInfo().get_y(i);
				int now_x = this.state.getInfo().get_x(i);
				
				int goal_y = this.state.getInfo().get_y(this.state.getInfo().getGoal().getPosmap().get(seq[i]));
				int goal_x = this.state.getInfo().get_x(this.state.getInfo().getGoal().getPosmap().get(seq[i]));
				
				score += ScoreUtils.manhattan_distance(now_x, now_y, goal_x, goal_y);
			}
		}
		
		return score;
	}
	
	private double get_partial_block_score(int x_band, int y_band) {
		int score = 0;
		double score_weight =  Math.sqrt(x_band*y_band);
		
		for(int org_x=0; org_x<state.getInfo().getWidth()-x_band+1; org_x+=1) {
			for(int org_y=0; org_y<state.getInfo().getHeight()-y_band+1; org_y+=1) {
				boolean match = true;
				for(int i=org_x; i<org_x+x_band-1; i+=1) {
					if (!match) {
						break;
					}
					for(int j=org_y; j<org_y+y_band-1; j+=1) {
						int idx = state.getInfo().index_at(i, j);
						if(state.getSeq()[idx]
						                  !=state.getInfo().getGoal().getSeq()[idx]) {
							match = false;
							break;
						}
					}
				}
				score += score_weight;
			} 
		}
		return score;
	}
	  
	public Iterator<NodeMove> validMove(){
		List<NodeMove> moves = new ArrayList<NodeMove>();
		
		NodeMove u = new U_NodeMove(); 
		if (!u.isNeedlessMove(this)) {
			moves.add(u);
		}
		NodeMove d = new D_NodeMove(); 
		if (!d.isNeedlessMove(this)) {
			moves.add(d);
		}
		NodeMove l = new L_NodeMove(); 
		if (!l.isNeedlessMove(this)) {
			moves.add(l);
		}
		NodeMove r = new R_NodeMove(); 
		if (!r.isNeedlessMove(this)) {
			moves.add(r);
		}
		
		return moves.iterator();
		 
	}

	public BoardState getState() {
		return state;
	}

	public void setState(BoardState state) {
		this.state = state;
	}

	public StateNode getParent() {
		return parent;
	}

	public void setParent(StateNode parent) {
		this.parent = parent;
	}

	public StateNode[] getChildren() {
		return children;
	}

	public void setChildren(StateNode[] children) {
		this.children = children;
	}

	public List<Character> getHistory() {
		return history;
	}

	public void setHistory(List<Character> history) {
		this.history = history;
	}

	public double getScore() {
		return score;
	}

	public void setScore(double score) {
		this.score = score;
	}
	public String printScore(){
		return String.valueOf(this.getScore())+"("+hisotryScore
		+","+manhattanScore
		+","+partMatchScore
		+","+horizonScore
		+","+verticalScore+")";
	}
	
}
