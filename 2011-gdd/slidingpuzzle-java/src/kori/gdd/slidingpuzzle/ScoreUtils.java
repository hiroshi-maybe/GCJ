package kori.gdd.slidingpuzzle;

public class ScoreUtils {

	public static double manhattan_distance(int x1, int y1, int x2, int y2) {
		return Math.abs(x1-x2) + Math.abs(y1-y2);
	}
}
