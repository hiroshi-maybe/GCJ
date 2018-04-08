
public class CopyTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		char[] a = new char[]{'x','y'};
		char[] b = a.clone();
		
		a[0]='X';
		for(int i=0; i<b.length; i+=1) {
			System.out.println("a:"+a[i]+", b:"+b[i]);			
		}
		
		Character[] c = new Character[]{'x','y'};
		Character[] d = c.clone();
		c[0] = 'X';
		for(int i=0; i<b.length; i+=1) {
			System.out.println("c:"+c[i]+", d:"+d[i]);			
		}
	}

}
