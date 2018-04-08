package kori.gdd.slidingpuzzle.constant;

public class Constant {
	public static final char[] BASE_ORDER = {'1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	public static final char EMPTY_CHAR = '0';
	public static final char WALL_CHAR = '=';

	public static final int CLOSED_LIMIT_NUM = 1000000;
	public static final int OPEN_LIMIT_INIT_QUE_SIZE = 4000;
	public static final int MOVE_LIMIT = 200;

	public static final double VERTICAL_SCORE = 1.0;
	public static final double HORIZON_SCORE = 1.0;

	public static final double HISTORY_SCORE_WEIGHT = 1.0;                                                                                                                                                  
	public static final double MANHATTAN_SCORE_WEIGHT = 1.0;
	public static final double SEQUENCE_SCORE_WEIGHT = 1.0;
	
	public static final char U_ACTION = 'U';
	public static final char D_ACTION = 'D';
	public static final char R_ACTION = 'R';
	public static final char L_ACTION = 'L';
}
