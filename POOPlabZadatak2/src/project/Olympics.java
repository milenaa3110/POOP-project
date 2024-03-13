package project;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Olympics {
	
	private static Olympics instance;
	
	public static Olympics getInstance() {
		if(instance == null) {
			instance = new Olympics();
		}
		return instance;
	}
	
	public ArrayList<ArrayList<String>> ucitaj(File file) {
		try {
			BufferedReader br = new BufferedReader(new FileReader(file));
			ArrayList<ArrayList<String>> lines = new ArrayList<>();
			String line = br.readLine();
			while (line!=null) {
				String[] resLine = line.split("!");
				ArrayList<String> resArray = new ArrayList<>();
				for (String obj : resLine) {
					resArray.add(obj);
				}
				if (resArray.size()<8) resArray.add("None");
				lines.add(resArray);
				line = br.readLine();
			}
			br.close();
			return lines;
		} catch (FileNotFoundException e) {
			System.err.println("Fajl nije pronadjen...");
		} catch (IOException e) {
		}
		return null;
		}
	}
		

