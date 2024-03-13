package project;

import java.util.ArrayList;
import java.util.HashMap;

public class DataParser {
	
	public native HashMap<String, String> parseData(ArrayList<ArrayList<String>> events, ArrayList<ArrayList<String>> athletes, int mode, String year, String filterSport, String filterYear, String filterType, String filterMedal, String metric, int param);
	
	public DataParser() {
		System.loadLibrary("DllOlimpycs");
		
	}
	public static void main(String[] args) {
		new DataParser();
		System.out.println(1);
	}
}
