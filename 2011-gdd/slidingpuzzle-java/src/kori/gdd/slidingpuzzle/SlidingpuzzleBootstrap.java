package kori.gdd.slidingpuzzle;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Date;

import kori.gdd.slidingpuzzle.node.StateNode;

import org.apache.commons.lang3.StringUtils;

public class SlidingpuzzleBootstrap {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		PrintWriter pw = null;
        try {
            FileReader in = new FileReader("./input.dat");
            BufferedReader br = new BufferedReader(in);
            String line;
            int i=0;
            
            int l_limit = 0;
            int r_limit = 0;
            int u_limit = 0;
            int d_limit = 0;
            int board_num = 0;
            
    		File file = new File("./result.txt");
    		pw = new PrintWriter(new BufferedWriter(new FileWriter(file)));
            
            while ((line = StringUtils.chomp(br.readLine())) != null) {
            	if(i==0) {
            		String[] limits = line.split(" ");
            		l_limit = Integer.valueOf(limits[0]);
            		r_limit = Integer.valueOf(limits[1]);
            		u_limit = Integer.valueOf(limits[2]);
            		d_limit = Integer.valueOf(limits[3]);
                    i += 1;
            		continue;
            	} else if (i==1) {
            		board_num = Integer.valueOf(line);
                    i += 1;
                    continue;
            	}
            	int id = i-2;

            	if(id>11) {
            		pw.println();
            		continue;
            	};

                Board b = new Board(id, line);
                i += 1;
                StateNode result = b.search();
                SimpleDateFormat f = new SimpleDateFormat("yyyy'/'MM'/'dd' 'HH':'mm':'ss");
                if (result == null) {
                	pw.println();
                	System.out.println(f.format(new Date())+" "+String.valueOf(id)+": failure");
                } else {
                	StringBuilder sb = new StringBuilder();
                	for(Character c : result.getHistory()) {
                		sb.append(c);
                	}
                	pw.println(sb.toString());
                	System.out.println(f.format(new Date())+" "+String.valueOf(id)+": success");
                }
            }
        	br.close();
            in.close();            
        } catch (IOException e) {
            System.out.println("input.datを実行ディレクトリに配置してください");
            System.out.println(e);
        } finally {
            pw.close();
        }

		
	}

}
