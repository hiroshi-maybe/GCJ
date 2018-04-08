package kori.gdd.slidingpuzzle;

import java.util.HashMap;

import kori.gdd.slidingpuzzle.state.BoardState;

public class BoardInfo {
    private int width = 0;
    private int height = 0;
    private int seqnum = 0;
    private BoardState goal = null;
    
    public BoardInfo(int width, int height, char[] initSeq, char[] goal){
    	this.width = width;
    	this.height = height;
    	this.seqnum = initSeq.length;
    	this.goal = new BoardState(goal, this);
    }
    
    public int get_x(int index) {
    	return index % width;
    }
    public int get_y(int index) {
    	return index / width;
    }
    public int index_at(int x, int y) {
    	return width*y+x;
    }
    
    public boolean valid(int x, int y) {
    	return x>width-1 || y>height-1 || x<0 || y<0 ? false : true;
    }
    
    public int neighbor_x (int index) {
    	
    	int x = get_x(index);
        int y = get_y(index);
        if (valid(x,y)) {
        	if (x==width-1){
                x = 0;
                y = y==height-1 ? 0 : y+1;        		
        	} else {
                x += 1;        		
        	}
        	return index_at(x,y);
        } else {
        	throw new RuntimeException();
        } 
    }
    
    public int neighbor_y (int index) {
    	
    	int x = get_x(index);
        int y = get_y(index);
        if(valid(x,y)) {
	        if (y==height-1) {
	        	y = 0;
	        	x = x==width-1 ? 0 : x+1;
	        } else {
	        	y += 1;        	
	        }
	        return index_at(x,y);
        } else {
        	throw new RuntimeException();
        } 
    }

	public int getWidth() {
		return width;
	}

	public void setWidth(int width) {
		this.width = width;
	}

	public int getHeight() {
		return height;
	}

	public void setHeight(int height) {
		this.height = height;
	}

	public int getSeqnum() {
		return seqnum;
	}

	public void setSeqnum(int seqnum) {
		this.seqnum = seqnum;
	}

	public BoardState getGoal() {
		return goal;
	}

	public void setGoal(BoardState goal) {
		this.goal = goal;
	}
}
